# Huffman Coding Compression and Decompression Algorithm in C++

## Introduction
This project implements a file compression and decompression utility using the Huffman coding algorithm. The Huffman coding algorithm is a popular method for lossless data compression.

## Features
- Build a Huffman Tree based on the frequency of characters in the input file.
- Generate Huffman codes for each character.
- Compress the input file using the generated Huffman codes.
- Decompress the compressed file back to the original content.

## How It Works
1. **Frequency Analysis**: Read the input file and count the frequency of each character.
2. **Build Huffman Tree**: Construct a Huffman Tree based on the character frequencies.
3. **Generate Codes**: Traverse the Huffman Tree to generate binary codes for each character.
4. **Compression**: Encode the input file using the generated Huffman codes and write the compressed data to the output file.
5. **Decompression**: Read the compressed file, decode it using the Huffman Tree, and write the original content to the output file.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/starlord0104/HuffmanCodingCompressionDecompression.git
