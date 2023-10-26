#pragma once

#ifndef __SUFFIXTREE_H__

#define __SUFFIXTREE_H__

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class UkkonenSTree {
  private:
    struct Node;

    struct Edge {
        int start;
        int end;
        Node *child;
        Edge(){};
        Edge(int s, int e, Node *n) {
            start = s;
            end = e;
            child = n;
        };
    };

    struct Node {
        map<char, Edge *> edges;
        Node *slink;
    };

    struct Point {
        Node *node;
        Edge *edge;
        int l;
        Point(){};
        Point(Node *nd, Edge *eg, int c) {
            node = nd;
            edge = eg;
            l = c;
        }
    };

    // typedef pair<Node *, bool> Edge;

    Point active_point;

    string T;
    Node *root;
    Edge *aux;
    int next_leaf;
    Node *split(Node *parent, Node *child, char c);
    Point readEdge(Point ap, char c);
    void addPrefix(int pos);

  public:
    UkkonenSTree();
    UkkonenSTree(const string &t);
    void addString(const string &t);
    pair<int, int> matching(const string &p);
    void printTree();
};

#endif // __SUFFIXTREE_H__