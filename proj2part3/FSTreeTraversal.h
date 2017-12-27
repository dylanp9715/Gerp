// FSTreeTraversal.h
// Purpose: to establish and define the FSTreeTraversal class
// By: Dylan Park
// Date: 11/13/16
//
//
#ifndef FSTREETRAVERSAL_H
#define FSTREETRAVERSAL_H
#include "DirNode.h"
//#include "hashTable.h"

using namespace std;

class FSTreeTraversal {
        public:
                FSTreeTraversal();
                ~FSTreeTraversal();
                void traverse(DirNode *root, string directoryName, 
                string queryMode); // calls traverse_rec
                void traverse_rec(DirNode *current, string path, 
                string queryMode); // goes through the tree, reads files, 
                //creates hashTables for files, and searches hashTables for 
                // certain word
                void searchFiles(DirNode *current, string path,
                string queryMode);
                void errorMessage(string query);
        private:
                int numFound;
};
#endif
