#pragma once

#ifndef __DAWG_H__

#define __DAWG_H__

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class DAWG {
private:
    enum {
        PRIMARY = 0,
        SECONDARY = 1

    };

    struct Node {
        map<char, pair<Node*, bool>> edges;
        Node* slink;
    };
    typedef pair<Node*, bool> Edge;

    Node* root;
    Node* split(Node* parent, Node* child, char c);

public:
    DAWG();
    DAWG(const string& t);
    void addString(const string& t);
    bool matching(const string& p);
};

#endif // __DAWG_H__
