// main.cpp
// Purpose: to run the program
// By: Dylan Park
// Date: 11/11/16
//
//
#include <iostream>
#include <string>
#include "FSTree.h"
#include "FSTreeTraversal.h"

using namespace std;

int main(int argc, char *argv[]) {
        string DirectoryToIndex;
        string query;
        FSTreeTraversal fst; //make instance of FSTreeTraversal class
        DirectoryToIndex = argv[1];
        FSTree fstree(DirectoryToIndex);
        cout << "Query? ";
        while (getline(cin,query)) { // while getting query from user
                if (argc == 2) { 
                        if (query == "@q" or query == "@quit") {
                                cout << endl;
                                cout << "Goodbye! Thank you and have a nice day"
                                << "." << endl;
                                return 0;
                        }
                        // traverse tree passing in directory to index, the 
                        // query, and the root
                        else { 
                                fst.traverse(fstree.getRoot(), DirectoryToIndex,
                                query);
                                fst.errorMessage(query);
                                cout << "Query? ";
                        }
                }
                else {
                        cerr << "Usage: gerp directory" << endl;
                        cerr << "            where: directory is a valid" 
                        "directory" << endl;
                        return 0;
                }
        }
        cout << endl;
        cout << "Goodbye! Thank you and have a nice day." << endl;
}
