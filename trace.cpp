// CSCI 2530
// Assignment: 8
// Author:     Brandon Gachuz
// File:       trace.cpp
// Tab stops:  4

/*
 * This module provides tracing for the modules that include "trace.h".
 * Whenever '-t' is entered in the command line, tracing is enabled.
 *
 * Functions this module includes:
 *
 * void setTracing(int argc, char** argv);
 * void showFrequencies(int* arr);
 * void showChar(char b);
 * void spaceChar(int n);
 * void showTree(Tree b);
 * void showCodeArray(char** code);
 *
 */

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <iomanip>
#include <cctype>
#include "trace.h"

using namespace std;

int tracelevel = 0;

/**
 * setTracing(argc, argv) sets variable to 1 if '-t' is entered in
 * the command line.
 *
 * @param argc
 *  Position to read from in the command line.
 *
 * @param argv
 *  Array of strings.
 */

void setTracing(int argc, char** argv)
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-t") == 0) {
            tracelevel = 1;
        }
    }
}

/**
 * showFrequencies(arr) shows the frequencies of characters in the
 * array 'arr' that occur at least once.
 *
 * @param arr
 *  The array of stored character frequencies.
 */

void showFrequencies(int* arr)
{
    if(arr != NULL)
    {
        cout << "\nThe character frequencies are:" << endl;
        for (int i = 0; i < 256; i++)
        {
            if (arr[i] > 0)
            {
                cout << setw(5);
                showChar(i);
                cout << setw(5) << arr[i] << endl;
            }
        }
    }
}

/**
 * showChar(b) prints the character name associated with 'b'
 * to the standard output.
 *
 * @param b
 *  Character to test.
 */

void showChar(char b)
{
    int hdf = (int) b;
    if (isspace(hdf))
    {
        spaceChar(hdf);
    }
    else if (isprint(hdf))
    {
        cout << (unsigned char) b;
    }
    else
    {
        cout << b << "\\n";
    }
}

/**
 * spaceChar(n) checks if parameter 'n' is a space character, and if it
 * is, it prints out the type of space character to the standard output.
 *
 * Restrictions:
 *
 * This function only checks for: new line, space, and tab characters. If
 * character 'n' is not either of those, then the string "spaceChar" is
 * printed to the standard output.
 *
 * @param n
 *  Integer.
 */

void spaceChar(int n)
{
    switch (n)
    {
        case '\n':
            cout << "newline";
            break;
        case ' ':
            cout << "space";
            break;
        case '\t':
            cout << "tab";
            break;
        default:
            cout << "spaceChar";
            break;
    }
}

/**
 * showTree(b) prints the character tree contained in 'b' to the standard
 * output.
 *
 * @param b
 *  The character tree to be printed.
 *
 */

void showTree(Tree b)
{
    if(b->kind == leaf)
    {
        showChar(b->ch);
    }
    else
    {
        printf("(");
        showTree(b->left);
        printf(" , ");
        showTree(b->right);
        printf(")");
    }
}

/**
 * showCodeArray(code) displays the huffman code of each character
 * present inside the string array 'code'.
 *
 * @param code
 *  The array of strings.
 */

void showCodeArray(char** code)
{
    if(code != NULL) {
        cout << "\n\nThe huffman code is as follows:" << endl;
        for (int i = 0; i < 256; i++) {
            if (code[i] != NULL) {
                cout << setw(5);
                showChar(i);
                cout << setw(7) << code[i] << endl;
            }
        }
    }
}
