// hashTable.h
// Purpose: to establish and define the hashTable class
// By: Dylan Park
// Date: 11/19/16
//
//
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "wordNode.h"
#include <vector>

using namespace std;

class hashTable {
        public: 
                hashTable();
                ~hashTable();
                void checkSize();
                void readFromFile(string filename, bool isInsensitive);
                // store line and word strings and then call createNode passing
                // in stored data
                void addWords(istream &infile, bool isInsensitive); 
                string capitalize(string word);
                // create and add nodes to hashTable for the file
                void createNode(string word, int lineNum, size_t binNum);
                wordNode *fillNode(string word, int lineNum);
                // search through file and hashTable for specified word
                //void search(string word, string filepath);
                int search(string word, string filepath, size_t binNum); 
                size_t hash(string word); // hash function
        private:
                wordNode **hashArray; // fill array with pointers to wordNodes
                vector<string> lines;
                void expand();
                const int INIT_CAP = 200;
                int size, capacity;
};
#endif
