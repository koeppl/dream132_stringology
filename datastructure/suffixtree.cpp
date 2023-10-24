#include "suffixtree.h"

UkkonenSTree::UkkonenSTree() {
    root = new Node;
    active_point = pair<Node *, int>(root, 0);
    aux = new Edge(0, 0, root);
}

UkkonenSTree::UkkonenSTree(const string &t) {
    root = new Node;
    active_point = pair<Node *, int>(root, 0);
    string T = t;

    addPrefix(0);
}

UkkonenSTree::Point UkkonenSTree::readEdge(Point ap, char c) {
    if (ap.eg != NULL) {
        if (T[ap.eg->start + ap.l] == c) {
            if (ap.eg->start + ap.l == ap.eg->end) {
                return Point(ap.eg->child, NULL, 0);
            } else {
                ap.l++;
                return ap;
            }
        }
    }
}

void UkkonenSTree::addPrefix(int pos) {
    for (int i = pos; i < T.size(); i++) {
        char c = T[i];
    }
}