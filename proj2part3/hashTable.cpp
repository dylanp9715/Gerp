// hashTable.cpp
// Purpose: to implement the hashTable class which has an array of pointers that
// point to a linked list of wordNodes that specify every instance that the word
// appears in the file
// By: Dylan Park
// Date: 11/19/16
//
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <cctype>
#include <vector>
#include "hashTable.h"
#include "wordNode.h"

using namespace std;

// constructor
hashTable::hashTable() {
        hashArray = new wordNode *[INIT_CAP]; // create array of pointers to 
        capacity = INIT_CAP;                  // wordNodes
        for (int i = 0; i < capacity; i++) {
                hashArray[i] = NULL;
        } // initially set pointers in array to null
        size = 0;
}

// destructor
hashTable::~hashTable() {
        wordNode *remove = NULL;
        for (int i = 0; i < capacity; i++) {
                remove = hashArray[i];
                while (remove != NULL) { // delete each node chained in linked 
                        wordNode *temp = remove; // list
                        remove = remove->next;
                        delete temp;
                }
        } 
        delete[] hashArray;
}

// checkSize
// Purpose: to see if the array needs to be expanded
// Arguments: none
// Return Value: none
void hashTable::checkSize() {
        int loadFactor = 0.7 * capacity;// expand if 70% full
        if (size == loadFactor) { 
                expand();
        }
}

// expand
// Purpose: to increase the size of the array when necessary
// Arguments: none
// Return Value: none
void hashTable::expand() {
        int oldCap = capacity;
        capacity = capacity*2;
        wordNode **newArray = new wordNode *[capacity]; // create new array
        for (int i = 0; i < capacity; i++) { // of pointers to linked list
                newArray[i] = NULL; // fill it with null initially
        }
        for (int j = 0; j < oldCap; j++) { // for each elt of old array
                wordNode *wn = hashArray[j];
                while (wn != NULL) { // go through and move each node that's 
                        wordNode *temp = wn; // chained
                        size_t bin = hash(wn->word);
                        if (newArray[bin] == NULL) {
                                wordNode *newnode = fillNode(wn->word, 
                                wn->lineNumber);
                                newArray[bin] = newnode;// add it to new array
                                wn = wn->next;
                                delete temp; 
                        } else {
                                wordNode *newnode = fillNode(wn->word,
                                wn->lineNumber);
                                wordNode *traverse = newArray[bin];
                                while (traverse->next != NULL) {
                                        traverse = traverse->next;
                                } // go to last node in linked list of newarray
                                traverse->next = newnode; // append newnode
                                wn = wn->next;
                                delete temp; // delete after moving to new array
                        }
                } 
        }
        delete[] hashArray;
        hashArray = newArray;
}

// readFromFile
// Purpose: to read the file and put the words into the array
// Arguments: the string of the filename and a bool isInsensitive to pass into 
// createNode function
// Return Value: none
void hashTable::readFromFile(string filename, bool isInsensitive) {
        ifstream input;
        input.open(filename);
        addWords(input, isInsensitive);
        input.close();
}

// addWords
// Purpose: to store the line and word strings and then calling createNode  
// passing in the stored data
//Arguments: istream and bool that determines whether or not to capitalize words
// in file
// Return Value: none
void hashTable::addWords(istream &infile, bool isInsensitive) {
        size_t lineNum = 0;
        string line;
        while (getline(infile,line)) { // get each line in file
                lines.push_back(line);
                lineNum++; // increment lineNum for each line you read
                istringstream iss(line);
                string word;
                while (iss >> word) { // get each word in line
                        checkSize();
                        if (isInsensitive) {//if user wants an insensitiveSearch
                                word = capitalize(word); // capitalize each word
                                createNode(word, lineNum, hash(word));
                        } else {
                                createNode(word, lineNum, hash(word));
                        }
                        size++;
                }
        }
}

// capitalize
// Purpose: to capitalize each letter in the passed in word
// Arguments: word to capitalize
// Return Value: updated string
string hashTable::capitalize(string word) {
        for (size_t i = 0; i < word.length(); i++) {
               word[i] = toupper(word[i]); // capitalize each letter
        }
        return word; 
}

// createNode
// Purpose: to create a new wordNode, update it, and place it into correct spot
// of array
// Arguments: string of word, int of lineNum, and size_t of binNum to place it 
// into
// Return Value: none
void hashTable::createNode(string word, int lineNum, size_t binNum) {
        if (hashArray[binNum] == NULL) { // if the spot in the array is empty
                wordNode *wn = fillNode(word, lineNum);
                hashArray[binNum] = wn; // place node in empty spot
        }else { // otherwise, you must append it to linked list 
                wordNode *wn = fillNode(word, lineNum); // append
                wordNode *traverse = hashArray[binNum]; // it to last node
                while (traverse->next != NULL) {
                        traverse = traverse->next;
                }
                if (traverse->lineNumber != lineNum) {
                        traverse->next = wn; // to prevent lines with two 
                } else { // instances of the word from being printed twice
                        return;
                }
        }
}        

// addToEmpty
// Purpose: to create a new node 
// Arguments: string of word and int line number
// Return Value: pointer to word node
wordNode *hashTable::fillNode(string word, int lineNum) {
        wordNode *wn = new wordNode; // create new node
        wn->word = word;
        wn->lineNumber = lineNum;
        wn->next = NULL;
        return wn;
}

// search
// Purpose: to go through spot in array and see if the word is there. If it is, 
// then the filepath, lineNum, and the line is printed
// Arguments: string of the filepath and the word and the binNum
// Return Value: bool if word is found
int hashTable::search(string word, string filepath, size_t binNum) {
        int numFound = 0;
        wordNode *wn = hashArray[binNum]; // set a pointer to the specified 
        if (wn == NULL) { // place in array
                return numFound; //if it's empty, it's not there so return false
        }else { // otherwise...
                wordNode *traverse = wn;
                while (traverse != NULL) { // traverse to the end of the list
                        if (traverse->word == word) {
                                cout << filepath << ":" << traverse->lineNumber 
                                << ": " << lines[traverse->lineNumber-1] <<endl;
                                numFound++;
                        }
                        traverse = traverse->next;
                }
        }
        return numFound;
}

// hash
// Purpose: to hash the word to provide a binNum
// Arguments: string of word
// Return Value: size_t for the binNum 
size_t hashTable::hash(string word) {
        size_t binNumber = std::hash<std::string> {}(word);
        binNumber = binNumber%capacity; // to avoid going past capacity
        return binNumber;
}
