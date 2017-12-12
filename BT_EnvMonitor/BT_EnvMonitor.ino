/*
 Name:		BT_EnvMonitor.ino
 Created:	12/12/2017 12:05:55 PM
 Author:	asm

 Description:   The main purpose of this project is to provide local environment data
                via a 2x16 LCD and via bluetooth to any connected devices.

 Components:    
    1602    LCD with I2C Interface
    DS1307  RTC I2C module
    HC-05   Bluetooth module
    BME680  Enviroment sensor (temp, humidity, pressure and air quality)
*/

// comment this line to turn Serial logging off
#define _DEBUGGING_ON_

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include "SoftwareSerial.h"
#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)
#define BME680_I2C_ADDR       0x76

Adafruit_BME680 bme;

#define HW_BAUDRATE         115200
#define BLUETOOTH_BAUDRATE    9600 

#define LCD_I2C_ADDR    0x3F                  /* LCD I2C Address                          */
#define LCD_WIDTH       16
#define LCD_HEIGHT      2

DateTime dt;
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(LCD_I2C_ADDR, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

inline void lcd1() { lcd.setCursor(0, 0); }
inline void lcd2() { lcd.setCursor(0, 1); }

uint32_t RTC_BME680_LastReading;
uint32_t RTC_CurrentReading;

const uint32_t BME_READ_INTERVAL = 5;
const unsigned int LCD_SWITCH_INTERVAL = 10;

const char* months[12] = { "Ian", "Feb", "Mar", "Apr", "Mai", "Iun", "Iul", "Aug", "Sep", "Oct", "Nov", "Dec" };

SoftwareSerial BTSerial(10, 11);

/* Bluetooth commands   */
#define BT_GET_DATE     '1'
#define BT_GET_ENVDATA  '2'

void _callFunctionOnTimer(void(*fun)(void), const uint32_t timerValue, uint32_t *timer);

void printStartupMessage()
{
    lcd1();
    lcd.print("Starting");
    delay(300); lcd.print('.');
    delay(300); lcd.print('.');
    delay(300); lcd.print('.');
    delay(300); lcd.clear();
}

void setup()
{
    // initialize the lcd for 16 chars 2 lines
    // turn on backlight
    lcd.begin(LCD_WIDTH, LCD_HEIGHT, 1);
    printStartupMessage();

    Serial.begin(HW_BAUDRATE);
    BTSerial.begin(BLUETOOTH_BAUDRATE);

    if (!bme.begin(BME680_I2C_ADDR))
    {
        lcd.clear();
        lcd1(); lcd.print("Could not find");
        lcd2(); lcd.print("BME260 sensor");
        Serial.println("Could not find a valid BME680 sensor, check wiring!");
        while (1);
    }

    // Set up oversampling and filter initialization
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_4X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_63);

    // leave the gas sensor disabled
    // bme.setGasHeater(320, 150); // 320*C for 150 ms

    // no RTC found
    if (!rtc.begin())
    {
        lcd.clear();
        lcd1();
        lcd.print("No RTC module!");
        Serial.println("Couldn't find RTC");
        while (1);
    }

    // set the RTC if not set already
    if (!rtc.isrunning())
    {
        Serial.println("RTC is NOT running!");
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }

    RTC_CurrentReading = rtc.now().unixtime();
    // set last reading in the past to force the display of data
    RTC_BME680_LastReading = RTC_CurrentReading - BME_READ_INTERVAL;
}

void loop()
{
    dt = rtc.now();
    RTC_CurrentReading = dt.unixtime();
    // always display the date
    displayDate();
    // update the env. data on timer
    _callFunctionOnTimer(BME680_DisplayData, BME_READ_INTERVAL, &RTC_BME680_LastReading);
    // check for BT
    BT_CheckForData();
}

/*
 Utility function to call another function after certain amount of time has passed
 Time is checked with an RTC rather than millis() so we have 1s resolution

 Params:
    void(*fun)(void) - function to call 
                     - usually a display update function

     timerValue      - timer value in seconds

     timer           - the timer to store the specific readings

*/
void _callFunctionOnTimer(void(*fun)(void), const uint32_t timerValue, uint32_t *timer)
{
    if (RTC_CurrentReading - (*timer) >= timerValue)
    {
        fun();
        *timer = RTC_CurrentReading;
    }
}
// LCD Data Format
// |----------------|
// |09:56   07-12-17| HH:MM   DD-MM-YY
// |25.6*C 34%  1013| TT.TT*C HH% PPPP
// |----------------|

void displayDate()
{
    char row1[16 + 1];
    lcd1();
    sprintf(row1, "%2.2d:%2.2d:%2.2d  %2.2d %3.3s",
        dt.hour(), dt.minute(), dt.second(),
        dt.day(), months[dt.month() - 1]);
    lcd.print(row1);
}

// round 2 decimals to 1
inline int roundTo1Decimal(int val)
{
    return ((val % 10 >= 5) ? ((val / 10) + 1) : (val / 10));
}

/* BME Display Data */
void BME680_DisplayData()
{
    char row2[16 + 1];
    if (!bme.performReading())
    {
        Serial.println("Failed to perform reading :(");
        return;
    }

    lcd2();
    int hum_DEC = static_cast<int> (bme.humidity * 100);
    int temp_DEC = static_cast<int> (bme.temperature * 100);
    int pres_DEC = static_cast<int> (bme.pressure);
    sprintf(row2, "%2.2d.%1.1d\337C  Hum:%2.2d.%1.1d%%",
        temp_DEC / 100, roundTo1Decimal(temp_DEC % 100),
        hum_DEC / 100, roundTo1Decimal(hum_DEC % 100));
    lcd.print(row2);

#ifdef _DEBUGGING_ON_
    // -------------------------------------------------------//
    {
        char tmp[20 + 1];
        lcd1();
        sprintf(tmp, "%4.4d.%2.2d.%2.2d %2.2d:%2.2d:%2.2d",
            dt.year(), dt.month(), dt.day(),
            dt.hour(), dt.minute(), dt.second());
        Serial.println("--------------------------------");
        Serial.println(tmp);

        Serial.print("Temperature = ");
        Serial.print(bme.temperature);
        Serial.println(" *C");

        Serial.print("Pressure = ");
        Serial.print(bme.pressure / 100.0);
        Serial.println(" hPa");

        Serial.print("Humidity = ");
        Serial.print(bme.humidity);
        Serial.println(" %");

        //Serial.print("Gas = ");
        //Serial.print(bme.gas_resistance / 1000.0);
        //Serial.println(" KOhms");

        Serial.print("Approx. Altitude = ");
        Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
        Serial.println(" m");
    }
    // -------------------------------------------------------//
#endif
}

void BT_CheckForData()
{
    if (BTSerial.available())
    {
        char btData = BTSerial.read();

        if (btData == BT_GET_DATE)
        {
            DateTime now = rtc.now();

            BTSerial.print("DATE:");
            BTSerial.print("h="); BTSerial.print(now.hour()); BTSerial.print(";");
            BTSerial.print("m="); BTSerial.print(now.minute()); BTSerial.print(";");
            BTSerial.print("s="); BTSerial.print(now.second()); BTSerial.print(";");

            BTSerial.print("y="); BTSerial.print(now.year()); BTSerial.print(";");
            BTSerial.print("m="); BTSerial.print(now.month()); BTSerial.print(";");
            BTSerial.print("d="); BTSerial.print(now.day()); BTSerial.print(";");

            BTSerial.println("#");
        }
        else if (btData == BT_GET_ENVDATA)
        {
            if (!bme.performReading())
            {
                Serial.println("Failed to perform reading :(");
                return;
            }
            float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

            BTSerial.print("Temperature: "); BTSerial.print(bme.temperature);    BTSerial.println();
            BTSerial.print("Humidity:    "); BTSerial.print(bme.humidity);       BTSerial.println();
            BTSerial.print("Pressure:    "); BTSerial.print(bme.pressure / 100.0); BTSerial.println();
            BTSerial.print("Altitude:    "); BTSerial.print(altitude);
            BTSerial.println("#");
        }
    }
}