
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
#include <bitset>

using namespace std;

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(char ch, int freq, HuffmanNode* left = nullptr, HuffmanNode* right = nullptr);
    ~HuffmanNode();
};

struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r);
};

void printCodes(HuffmanNode* root, string str, map<char, string>& huffmanCode);
HuffmanNode* buildHuffmanTree(map<char, int>& freq);
void compressFile(string inputFilename, string outputFilename);
void decompressFile(string inputFilename, string outputFilename);

#endif // HUFFMAN_H
