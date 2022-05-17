#include "huffman_encoder.h"

node::node(char character, int weight){
    this->character = character;
    this->weight = weight;
    left = nullptr;
    right = nullptr;
}

huffman_encoder::huffman_encoder(const frequency_table &table){
    
    priority_queue<node*, vector<node*>, Comparator> minHeap;
    
    for(int i = 0; i < 128; ++i) {
        int freq = table.get_frequency(static_cast<char>(i));
        if (freq > 0)
        {
            node* newNode = new node(static_cast<char>(i), freq);
            minHeap.push(newNode);
        }
    }

    while (minHeap.size() != 1) {

        node* left = minHeap.top();
        minHeap.pop();
        node* right = minHeap.top();
        minHeap.pop();

        node* addedNode = new node('$', left->weight + right->weight);

        addedNode->left = left;
        addedNode->right = right;

        minHeap.push(addedNode);
    }

    finalRoot = minHeap.top();
    string code;
    if (finalRoot->left == nullptr && finalRoot->right == nullptr)
    {
        binaryMap[finalRoot->character] = "0";
    }
    else 
    {
        recursiveSetCode(finalRoot, binaryMap, code);
    }

}

huffman_encoder::~huffman_encoder(){
    eraseNodes(finalRoot);
}

void huffman_encoder::eraseNodes(node* current) {
    if (current == nullptr)
        return;
    
    eraseNodes(current->left);
    eraseNodes(current->right);
    delete current;
}

std::string huffman_encoder::get_character_code(char c) const {
    if (binaryMap.find(c) == binaryMap.end())
    {
        return "";
    }
    else 
    {
        return binaryMap.at(c);
    }
}

std::string huffman_encoder::encode(const std::string &file_name) const {
    string total = "";
    
    ifstream file;
    file.open(file_name);
    if (file.fail())
        throw runtime_error("File not found or cannot be opened");

    char readC;


    while (file.get(readC)) 
    {
        if (get_character_code(readC) != "")
        {
            total += get_character_code(readC);
        }
        else 
        {
            total = "";
            readC = file.eof();
        }
    }

    return total;

}

std::string huffman_encoder::decode(const std::string &string_to_decode) const {
    
    string total = "";
    node* current = finalRoot;

    if (string_to_decode.size() == 1)
    {
        total += current->character;
        return total;
    }

    for (unsigned int i = 0; i < string_to_decode.size(); i++)
    {
        if (string_to_decode[i] == '0')
            current = current->left;
        else 
            current = current->right;

        if (current->left == nullptr && current->right == nullptr)
        {
            total += current->character;
            current = finalRoot;
        }

    }

    return total; 
    
}

bool Comparator::operator()(node* first, node* second){
    return first->weight > second->weight;
}

void huffman_encoder::recursiveSetCode(node* root, unordered_map<char, string>& binaryMap, std::string code){
    if (root->left != nullptr) {

        recursiveSetCode(root->left, binaryMap, code + "0");
    }

    if (root->right != nullptr) {

        recursiveSetCode(root->right, binaryMap, code + "1");
    }

    if (root->left == nullptr && root->right == nullptr) {
        binaryMap[root->character] = code;
    }
}


