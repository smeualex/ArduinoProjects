#pragma once

class Utils {
public:
    static void print_binary(int v, int bits)
    {
        int mask = 0;

        for (int n = 1; n <= bits; n++)
            mask = (mask << 1) | 0x0001;
        v = v & mask;

        while (bits)
        {
            if (v & (0x0001 << bits - 1))
                Serial.print("1");
            else
                Serial.print("0");
            --bits;
        }
    }
};