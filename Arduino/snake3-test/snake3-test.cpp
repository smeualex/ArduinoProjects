// snake3-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Board.h"

#include <iostream>

using namespace std;

void printArray(const int w, const int h, const int *arr)
{
    int i;
    
    for (i = 0; i < w; i++)
        cout << "--";
    cout << endl;

    for (i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
            cout << arr[i*w + j] << " ";
        cout << endl;
    }

    for (i = 0; i < w; i++)
        cout << "--";
    cout << endl;
}

int main()
{
    int* m;
    int h = 8;
    int w = 8;
    int size = h * w;

    m = new(std::nothrow) int[w*h];

    if (m == nullptr)
    {
        cout << "could not allocate memory" << endl;
        exit(1);
    }

    for (int i = 0; i < size; i++)
        m[i] = 0;

    printArray(w, h, m);

    delete[] m;
    return 0;
}

