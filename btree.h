#ifndef BTREE_H
#define BTREE_H

#include "methods.h"

class BTreeNode {
    public:
        vector<string> keys;
        vector<int> recordIndices;
        vector<BTreeNode*> children;

        BTreeNode() {}

        bool search(const string& key);
        void modify(const string& key);
        void delCar(const string& key);
        void printCar(const string& chave);
    private:
        static const int MAX_KEYS = 3;
};


#endif