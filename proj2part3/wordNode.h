// wordNode.h
// Purpose: to establish and define the wordNode class
// By: Dylan Park
// Date: 11/19/16
//
//
#ifndef WORDNODE_H
#define WORDNODE_H

using namespace std;

struct wordNode {
        int lineNumber;
        string word;
        wordNode *next;
};
#endif
