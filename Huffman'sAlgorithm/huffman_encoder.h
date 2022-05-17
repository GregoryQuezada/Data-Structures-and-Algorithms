#pragma once

#include "frequency_table.h"
#include <queue>

// struct for the nodes of the tree?

struct node
{
    char character;
    int weight;
    node* left;
    node* right;

    node(char character, int weight);
};

class Comparator {
    public:
        bool operator()(node* first, node* second);
};

class huffman_encoder {
    unordered_map<char, string> binaryMap;
    node* finalRoot;

    public:
        huffman_encoder(const frequency_table &table);
        ~huffman_encoder();
        void eraseNodes(node* current);

        std::string get_character_code(char c) const;
        std::string encode(const std::string &file_name) const;
        std::string decode(const std::string &string_to_decode) const;

        void recursiveSetCode(node* root, unordered_map<char, string>& binaryMap, std::string code);
};
