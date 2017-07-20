// CSCI 2530
// Assignment: 8
// Author:     Brandon Gachuz
// File:       unhuffman.cpp
// Tab stops:  4

/*
 * This module decompresses the huffman tree (read in as a binary file)
 * and prints the decoded tree to the standard output.
 */

#include <cstdio>
#include <iostream>
#include "binary.h"
#include "trace.h"
#include "tree.h"


using namespace std;

// Function Prototypes

Tree returnBinaryTree(BFILE *data);
int charAsInt(Tree t, BFILE* file);

int main(int argc, char** argv)
{
    setTracing(argc, argv);
    BFILE* openRead = openBinaryFileRead(argv[argc-2]);
    Tree t = returnBinaryTree(openRead);

    closeBinaryFileRead(openRead);

    if(tracelevel)
    {
        cout << "\nThe decoded huffman tree:" << endl;
        showTree(t);
        putchar('\n');
    }

    putchar('\n');

    return 0;
}

/**
 * returnBinaryTree(data) reads in the binary file 'data', builds a
 * binary tree and returns the binary tree.
 *
 * @param data
 *  Binary file to read from.
 * @return
 *  Binary Tree.
 */

Tree returnBinaryTree(BFILE *data)
{
    int bit = readBit(data);
    if(bit != EOF && bit == 1) {
        int byte = readByte(data);
        if(byte != EOF) {
            return new Node(byte);
        }
    }
    return new Node(returnBinaryTree(data),
                    returnBinaryTree(data));
}

/**
 *
 * @param t
 * @param file
 * @return
 */

int charAsInt(Tree t, BFILE* file)
{
    if(t->kind == leaf)
        return t->ch;
    else
    {
        int pop = readBit(file);
        if(pop == EOF)
            return EOF;
        else if(pop == 1)
            charAsInt(t->right, file);
        else
            charAsInt(t->left, file);
    }
}

void uncompression()
{

}