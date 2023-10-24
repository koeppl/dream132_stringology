#include "suffixtree.h"

UkkonenSTree::UkkonenSTree() {
    root = new Node;
    active_point = Point(root, NULL, 0);
    aux = new Edge(0, 0, root);
}

UkkonenSTree::UkkonenSTree(const string &t) {
    root = new Node;
    active_point = Point(root, NULL, 0);
    string T = t;
    addPrefix(0);
}

UkkonenSTree::Point UkkonenSTree::readEdge(Point ap, char c) {
    if (ap.edge != NULL) {
        if (T[ap.edge->start + ap.l] == c) {
            if (ap.edge->start + ap.l == ap.edge->end) {
                return Point(ap.edge->child, NULL, 0);
            } else {
                ap.l++;
                return ap;
            }
        } else {
            return Point(NULL, NULL, 0);
            // no path labeled by c
        }
    } else {
        if (ap.node->edges.find(c) != ap.node->edges.end()) {
            auto eg = ap.node->edges[c];
            if (eg->start == ap.edge->end) {
                return Point(eg->child, NULL, 0);
            } else {
                return Point(ap.node, eg, 1);
            }
        } else {
            // no path labeled by c
            return Point(NULL, NULL, 0);
        }
    }
}

void UkkonenSTree::addPrefix(int pos) {
    for (int i = pos; i < T.size(); i++) {
        char c = T[i];
        Point next_ap = readEdge(active_point, c);
    }
}