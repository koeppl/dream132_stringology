#include "suffixtree.h"

UkkonenSTree::UkkonenSTree() {
    root = new Node;
    active_point = Point(root, NULL, 0);
    next_leaf = 0;
    aux = new Edge(0, 0, root);
}

UkkonenSTree::UkkonenSTree(const strin g &t) {
    root = new Node;
    active_point = Point(root, NULL, 0);
    next_leaf = 0;
    aux = new Edge(0, 0, root);
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
        Node *last_node = NULL;
        while (next_ap.node == NULL) {
            if (active_point.edge = NULL) {
                Node *new_leaf = new Node;
                Edge *new_edge = new Edge(i, INT_MAX, new_leaf);
                active_point.node->edges[c] = new_edge;
                if (last_node != NULL) {
                    last_node->slink = active_point.node;
                    last_node = active_point.node;
                }
                if (active_point.node == root) {
                    next_ap = active_point;
                } else {
                    active_point.node = active_point.node->slink;
                    next_ap = readEdge(active_point, c);
                }
            } else {
                Node *new_leaf = new Node;
                Node *new_node = new Node;
                Edge *new_edge_to_leaf = new Edge(i, INT_MAX, new_leaf);
                Edge *new_edge_to_node =
                    new Edge(active_point.edge->start + active_point.l,
                             active_point.edge->end, new_leaf);

                // split edge and add leaf
                new_node->edges[c] = new_edge_to_leaf;
                new_node->edges[T[active_point.edge->start + active_point.l]] =
                    new_edge_to_node;
                active_point.edge->end =
                    active_point.edge->start + active_point.l - 1;
                if (last_node != NULL) {
                    last_node->slink = new_node;
                    last_node = new_node;
                }

                // next_active_point
                if (active_point.node == root) {
                    next_ap.node = root;
                    next_ap.node = root;

                    next_ap = active_point;
                } else {
                    active_point.node = active_point.node->slink;
                    next_ap = readEdge(active_point, c);
                }
            }
        }
    }
}