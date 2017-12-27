#
# Makefile for proj2
#
CXX = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11
LDFLAGS = -g3

gerp: main.o FSTreeTraversal.o hashTable.o FSTree.o DirNode.o
	${CXX} ${LDFLAGS} -o gerp main.cpp FSTreeTraversal.o hashTable.o FSTree.o DirNode.o

main.o: main.cpp FSTreeTraversal.h
FSTreeTraversal.o: FSTreeTraversal.h FSTreeTraversal.cpp DirNode.h FSTree.h hashTable.h
hashTable.o: hashTable.h hashTable.cpp wordNode.h 
FSTree.o: FSTree.h
DirNode.o: DirNode.h
wordNode.o: wordNode.h
