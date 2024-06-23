#include "huffman.h"

// HuffmanNode constructor
HuffmanNode::HuffmanNode(char ch, int freq, HuffmanNode* left, HuffmanNode* right) {
    this->ch = ch;
    this->freq = freq;
    this->left = left;
    this->right = right;
}

// HuffmanNode destructor
HuffmanNode::~HuffmanNode() {
    delete left;
    delete right;
}

// Compare structure for priority queue
bool Compare::operator()(HuffmanNode* l, HuffmanNode* r) {
    return l->freq > r->freq;
}

// Function to print Huffman codes
void printCodes(HuffmanNode* root, string str, map<char, string>& huffmanCode) {
    if (!root)
        return;

    if (root->ch != '$')
        huffmanCode[root->ch] = str;

    printCodes(root->left, str + "0", huffmanCode);
    printCodes(root->right, str + "1", huffmanCode);
}

// Function to build Huffman Tree
HuffmanNode* buildHuffmanTree(map<char, int>& freq) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    for (auto pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        pq.push(new HuffmanNode('$', sum, left, right));
    }

    return pq.top();
}

// Function to compress a file
void compressFile(string inputFilename, string outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file!" << endl;
        return;
    }

    ofstream outputFile(outputFilename, ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file!" << endl;
        return;
    }

    map<char, int> freq;
    char ch;
    while (inputFile.get(ch)) {
        freq[ch]++;
    }

    if (freq.empty()) {
        cerr << "The input file is empty!" << endl;
        return;
    }

    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    HuffmanNode* root = buildHuffmanTree(freq);

    map<char, string> huffmanCode;
    printCodes(root, "", huffmanCode);

    outputFile << freq.size() << "\n";
    for (auto pair : freq) {
        outputFile << pair.first << " " << pair.second << "\n";
    }

    string encodedStr = "";
    while (inputFile.get(ch)) {
        encodedStr += huffmanCode[ch];
    }

    int padding = 8 - (encodedStr.size() % 8);
    if (padding == 8) padding = 0;
    for (int i = 0; i < padding; ++i) {
        encodedStr += "0";
    }
    outputFile << padding << "\n";

    for (size_t i = 0; i < encodedStr.size(); i += 8) {
        bitset<8> bits(encodedStr.substr(i, 8));
        outputFile.put((unsigned char)bits.to_ulong());
    }

    inputFile.close();
    outputFile.close();
    delete root;
}

// Function to decompress a file
void decompressFile(string inputFilename, string outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file!" << endl;
        return;
    }

    ofstream outputFile(outputFilename, ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file!" << endl;
        return;
    }

    int size;
    inputFile >> size;

    map<char, int> freq;
    char ch;
    int frequency;
    inputFile.ignore();
    for (int i = 0; i < size; ++i) {
        inputFile.get(ch);
        inputFile >> frequency;
        freq[ch] = frequency;
        inputFile.ignore();
    }

    HuffmanNode* root = buildHuffmanTree(freq);

    int padding;
    inputFile >> padding;
    inputFile.ignore();

    string encodedStr = "";
    char byte;
    while (inputFile.get(byte)) {
        bitset<8> bits(byte);
        encodedStr += bits.to_string();
    }
    encodedStr = encodedStr.substr(0, encodedStr.size() - padding);

    HuffmanNode* current = root;
    for (char bit : encodedStr) {
        if (bit == '0')
            current = current->left;
        else
            current = current->right;

        if (!current->left && !current->right) {
            outputFile.put(current->ch);
            current = root;
        }
    }

    inputFile.close();
    outputFile.close();
    delete root;
}

// Main function
int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <compress|decompress> <input file> <output file>" << endl;
        return 1;
    }

    string command = argv[1];
    string inputFilename = argv[2];
    string outputFilename = argv[3];

    if (command == "compress") {
        compressFile(inputFilename, outputFilename);
    } else if (command == "decompress") {
        decompressFile(inputFilename, outputFilename);
    } else {
        cerr << "Invalid command!" << endl;
        return 1;
    }

    cout << "Operation completed." << endl;

    return 0;
}