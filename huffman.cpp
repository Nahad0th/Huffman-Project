// CSCI 2530
// Assignment: 8
// Author:     Brandon Gachuz
// File:       huffman.cpp
// Tab stops:  4

/*
 * This module uses huffman's algorithm to create a huffman tree
 * from a .txt file entered in the command line. If the file cannot be
 * opened, the program terminates.
 *
 * Functions this module includes:
 *
 * bool freqCounts(int *arr, int argc, char **argv);
 * void setFreqToZero(int* arr);
 * void readFile(FILE* iFile, int* arr);
 * Tree huffmanTree(int *arr);
 * void insertIntoQueue(PriorityQueue& q, int* charArray);
 * Tree huffTreeBuilderHelp(PriorityQueue &q);
 * void buildCode(Tree t, char** code, char* pref);
 * void setArrayToNull(char** code);
 * void writeTreeBinary(BFILE* f, Tree t);
 * void encodeChar(char** code, BFILE* bF, const char* inputFile);
 *
 */


#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "trace.h"
#include "tree.h"
#include "binary.h"
#include "pqueue.h"

using namespace std;

const int maxChars = 256;

// Function prototypes

bool freqCounts(int *arr, int argc, char **argv);
void setFreqToZero(int* arr);
void readFile(FILE* iFile, int* arr);
Tree huffmanTree(int *arr);
void insertIntoQueue(PriorityQueue& q, int* charArray);
Tree huffTreeBuilderHelp(PriorityQueue &q);
void buildCode(Tree t, char** code, char* pref);
void setArrayToNull(char** code);
void writeTreeBinary(BFILE* f, Tree t);
void encodeChar(char** code, BFILE* bF, const char* inputFile);
void encodeCharHelper(BFILE* write, char** code, int x);

int main(int argc, char** argv)
{
    setTracing(argc, argv);

    int* chArr = new int[maxChars];
    bool result = freqCounts(chArr, argc, argv);

    if(result)
    {
        Tree test = huffmanTree(chArr);

        char** code = new char*[maxChars];
        char* zoom = new char[3];
        char* prefix = strcat(zoom, "01");
        setArrayToNull(code);
        buildCode(test, code, prefix);

        BFILE* openWriteFile = openBinaryFileWrite(argv[argc-1]);
        writeTreeBinary(openWriteFile, test);

        // Add something below
        encodeChar(code, openWriteFile, argv[argc-2]);

        if (tracelevel)
        {
            showFrequencies(chArr);
            cout << "\nThe huffman tree is as follows:" << endl;
            showTree(test);
            showCodeArray(code);

            cout << "\nInput File: " << argv[argc - 2] << endl;
            cout << "File two: " << argv[argc - 1] << endl;
        }

        closeBinaryFileWrite(openWriteFile);
    }
    else
    {
        puts("Opening file unsuccessful. Program terminating.");
    }

    putchar('\n');

    return 0;
}

/**
 * setFreqToZero sets each character frequency in array 'arr' to zero.
 * setFreqToZero is a helper function for function 'freqCounts'.
 *
 * @param arr
 *  The array of character frequencies
 */

void setFreqToZero(int* arr) {
    for(int i = 0; i < maxChars; i++) {
        arr[i] = 0;
    }
}

/**
 * readFile(iFile, arr) reads in characters from the file 'iFile'
 * and stores their frequency counts in array 'arr'.
 *
 * @param iFile
 *  The input file to read from
 * @param arr
 *  Character array
 */

void readFile(FILE* iFile, int* arr) {
    int ch;
    while((ch = getc(iFile)) != EOF)
    {
        arr[ch]++;
    }
}

/**
 * freqCounts(arr, argc, argv) computes the character counts from the first
 * file entered in the command line. The function returns true if it was
 * successful in opening the file, false otherwise.
 *
 * @param arr
 *  Array to store the frequency counts
 * @param argc
 *  Position in the command line to read from
 * @param argv
 *  File name
 * @return
 *  Boolean
 */

bool freqCounts(int *arr, int argc, char **argv)
{
    setFreqToZero(arr);
    FILE* inFile = fopen(argv[argc-2], "r");

    if(inFile != NULL)
    {
        readFile(inFile, arr);
        fclose(inFile);
        return true;
    }
    fclose(inFile);

    return false;
}

/**
 * huffTree(arr) takes an array of character frequencies and returns
 * the huffman tree of all present characters in 'arr'.
 *
 * @param arr
 *  Array of character frequencies.
 * @return
 *  Huffman tree generated from array 'arr'.
 */

Tree huffmanTree(int *arr)
{
    PriorityQueue queue = PriorityQueue();
    insertIntoQueue(queue, arr);

    Tree huffmanTree = huffTreeBuilderHelp(queue);
    return huffmanTree;
}

/**
 * insertIntoQueue(q, charArray) inserts the characters present
 * at least once in 'charArray' into priority queue 'q'.
 *
 * @param q
 *  Holds the trees inserted from the character array
 * @param charArray
 *  The character array
 */

void insertIntoQueue(PriorityQueue& q, int* charArray)
{
    for(int i = 0; i < maxChars; i++)
    {
        if(charArray[i] > 0)
        {
            Tree pop = new Node((unsigned char)i);
            insert(q, pop, i);
        }
    }
}

/**
 * huffTreeHelper(q) returns the huffman tree inside of priority
 * queue variable 'q'.
 *
 * @param q
 *  'q' holds the trees created by the helper function
 * @return
 *  The huffman tree created in the priority queue.
 */

Tree huffTreeBuilderHelp(PriorityQueue &q)
{
    Tree hanz = NULL;
    int nectar = 0;
    while(!isEmpty(q))
    {
        remove(q, hanz, nectar);
        if(!isEmpty(q))
        {
            Tree fuko;
            int pro;
            remove(q, fuko, pro);
            Tree t = new Node(hanz, fuko);
            insert(q, t, nectar + pro);
        }
    }
    return hanz;
}

/**
 * buildCode(t, code, pref) builds the character codes for tree 't'
 * and stores it in the string array 'code' starting with the prefix
 * value of 'pref'.
 *
 * @param t
 *  A subtree of the full huffman tree.
 * @param code
 *  An array of character codes.
 * @param pref
 *  Sequence of edge lables from the root of the huffman tree
 *  to the root of 't'.
 */

void buildCode(Tree t, char** code, char* pref)
{
    if(t != NULL)
    {
        if (t->kind == leaf)
        {
            char* cpyStr = new char[8];
            strcpy(cpyStr, pref);
            code[(int)(unsigned char) t->ch] = cpyStr;
        }
        else
        {
            char *cpyLeft = new char[8];
            strcpy(cpyLeft, pref);
            char* concatLeft = strcat(cpyLeft, "0");
            buildCode(t->left, code, concatLeft);
            delete[] cpyLeft;

            char *cpyRight = new char[8];
            strcpy(cpyRight, pref);
            char* catRight = strcat(cpyRight, "1");
            buildCode(t->right, code, catRight);
            delete[] cpyRight;
        }
    }
}

/**
 * setArrayToNull(code) sets the entire array 'code' to null.
 *
 * @param code
 *  The array of strings to holds the character codes of present
 *  characters.
 */

void setArrayToNull(char** code)
{
    for(int i = 0; i < maxChars; i++)
    {
        code[i] = NULL;
    }
}

/**
 * writeTreeBinary(f, t) writes a binary tree from 't' into
 * open binary file 'f'.
 *
 * @param f
 *  Open binary file for writing.
 * @param t
 *  Huffman tree.
 */

void writeTreeBinary(BFILE* f, Tree t)
{
    if(t->kind == leaf)
    {
        writeBit(f, 1);
        writeByte(f, t->ch);
    }
    else
    {
        writeBit(f, 0);
        writeTreeBinary(f, t->left);
        writeTreeBinary(f, t->right);
    }
}

/**
 * encodeChar(code, bF, inputFile) rereads the input file
 * 'inputFile' and writes the character code from
 * array 'code' for each character that reads
 * in the open binary file 'bF'. At the end, this function
 * closes the input file.
 *
 * @param code
 *  The array of strings that holds the character codes.
 * @param bF
 *  Open binary file for writing.
 * @param argv
 *  Name of file to read from.
 */

void encodeChar(char** code, BFILE* bF, const char* inputFile)
{
    FILE* reRead = fopen(inputFile, "r");

    if(reRead != NULL) {
        int ch;
        while ((ch = getc(reRead)) != EOF) {
            encodeCharHelper(bF, code, ch);
        }
    }
    fclose(reRead);
}

/**
 * This helper function encodes the character 'x' in
 * the open binary file 'write'.
 *
 * @param write
 *  Open binary file to write.
 * @param code
 *  Array of character codes
 * @param x
 *  Integer.
 */

void encodeCharHelper(BFILE* write, char** code, int x)
{
    for(int i = 0; code[x][i] != '\0'; i++)
    {
        int bit = (code[x][i] == '1');
        writeBit(write, bit);
    }
}