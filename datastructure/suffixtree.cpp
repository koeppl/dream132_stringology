#include "suffixtree.h"

UkkonenSTree::UkkonenSTree() {
    root = new Node;
    active_point = Point(root, NULL, 0);
    next_leaf = 0;
    last_leaf = NULL;
    start_leaf = NULL;
    aux = new Edge(0, 0, root);
}

UkkonenSTree::UkkonenSTree(const string &t) {
    root = new Node;
    active_point = Point(root, NULL, 0);
    next_leaf = 0;
    last_leaf = NULL;
    start_leaf = NULL;
    aux = new Edge(0, 0, root);
    T = t;
    addPrefix(0);
}

UkkonenSTree::Point UkkonenSTree::readEdge(Point ap, char c) {
    if (ap.edge != NULL) {
        if (ap.edge->start + ap.l >= T.size()) {
            return Point(NULL, NULL, 0);
        }
        if (T[ap.edge->start + ap.l] == c) {
            if (ap.edge->start + ap.l == ap.edge->end) {
                return Point(ap.edge->child, NULL, 0);
            } else {
                ap.l++;
                return ap;
            }
        } else {
            // no path labeled by c
            return Point(NULL, NULL, 0);
        }
    } else {
        if (ap.node->edges.find(c) != ap.node->edges.end()) {
            auto eg = ap.node->edges[c];
            if (eg->start == eg->end) {
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
            if (active_point.edge == NULL) {
                Node *new_leaf = new Node;
                Edge *new_edge = new Edge(i, 1000000000, new_leaf);
                active_point.node->edges[c] = new_edge;
                if (last_node != NULL) {
                    last_node->slink = active_point.node;
                }
                last_node = NULL;

                new_leaf->parent = new_edge;
                if (last_leaf == NULL) {
                    start_leaf = new_leaf;
                } else {
                    last_leaf->slink = new_leaf;
                }
                last_leaf = new_leaf;

                if (active_point.node == root) {
                    next_ap = active_point;
                } else {
                    active_point.node = active_point.node->slink;
                    next_ap = readEdge(active_point, c);
                }
            } else {
                Node *new_leaf = new Node;
                Node *new_node = new Node;
                Edge *new_edge_to_leaf = new Edge(i, 1000000000, new_leaf);
                Edge *new_edge_to_node = new Edge(active_point.edge->start,
                                                  active_point.edge->start + active_point.l - 1, new_node);
                int depth = active_point.l;

                // split edge and add leaf
                new_node->edges[c] = new_edge_to_leaf;
                new_node->edges[T[active_point.edge->start + active_point.l]] = active_point.edge;
                new_node->edges[T[active_point.edge->start + active_point.l]]->start = active_point.edge->start + active_point.l;

                active_point.node->edges[T[new_edge_to_node->start]] = new_edge_to_node;
                active_point.edge = new_edge_to_node;

                if (last_node != NULL) {
                    last_node->slink = new_node;
                }
                last_node = new_node;

                new_leaf->parent = new_edge_to_leaf;
                if (last_leaf == NULL) {
                    start_leaf = new_leaf;
                } else {
                    last_leaf->slink = new_leaf;
                }
                last_leaf = new_leaf;

                // next_active_point
                Node *temp;
                if (active_point.node == root) {
                    depth--;
                    temp = root;
                } else {
                    temp = active_point.node->slink;
                }

                char d = T[active_point.edge->start + active_point.l - depth];
                while (temp->edges[d]->end - temp->edges[d]->start < depth) {
                    depth -= temp->edges[d]->end - temp->edges[d]->start + 1;
                    temp = temp->edges[d]->child;
                    d = T[active_point.edge->start + active_point.l - depth];
                }

                active_point.node = temp;
                if (depth == 0) {
                    active_point.edge = NULL;
                } else {
                    active_point.edge = temp->edges[d];
                }

                active_point.l = depth;
                next_ap = readEdge(active_point, c);
            }
        }
        if (last_node != NULL) {
            last_node->slink = active_point.node;
        }

        active_point = next_ap;
    }
}

void UkkonenSTree::addString(const string &t) {
    T += t;
    addPrefix(T.size() - t.size());
}

void UkkonenSTree::terminal() {
    T += "$";
    Node *last_node = NULL;
    Node *leaf = start_leaf;
    while (leaf != NULL) {
        leaf->parent->end = T.size() - 2;
        last_node = leaf;
        leaf = leaf->slink;
    }

    while (active_point.edge != NULL) {
        Node *new_node = new Node;
        Edge *new_edge_to_node = new Edge(active_point.edge->start,
                                          active_point.edge->start + active_point.l - 1, new_node);
        int depth = active_point.l;

        new_node->edges[T[active_point.edge->start + active_point.l]] = active_point.edge;
        new_node->edges[T[active_point.edge->start + active_point.l]]->start = active_point.edge->start + active_point.l;

        active_point.node->edges[T[new_edge_to_node->start]] = new_edge_to_node;
        active_point.edge = new_edge_to_node;

        if (last_node != NULL) {
            last_node->slink = new_node;
        }

        last_node = new_node;

        // next_active_point
        Node *temp;
        if (active_point.node == root) {
            depth--;
            temp = root;
        } else {
            temp = active_point.node->slink;
        }

        char d = T[active_point.edge->start + active_point.l - depth];
        while (temp->edges[d]->end - temp->edges[d]->start < depth) {
            depth -= temp->edges[d]->end - temp->edges[d]->start + 1;
            temp = temp->edges[d]->child;
            d = T[active_point.edge->start + active_point.l - depth];
        }

        active_point.node = temp;
        if (depth == 0) {
            active_point.edge = NULL;
        } else {
            active_point.edge = temp->edges[d];
        }

        active_point.l = depth;
    }
    if (last_node != NULL) {
        last_node->slink = active_point.node;
    }
    active_point.node = root;

    start_leaf = NULL;
    last_leaf = NULL;
}

pair<int, int> UkkonenSTree::matching(const string &p) {
    pair<int, int> ans = pair<int, int>(0, 0);
    Point pt(root, NULL, 0);
    for (int i = 0; i < p.size(); i++) {
        char c = p[i];
        Point next_ap = readEdge(pt, c);
        if (next_ap.node == NULL) {
            return ans;
        }
        ans.first++;
        if (pt.edge != NULL) {
            ans.second = pt.edge->start + pt.l;
        } else {
            ans.second = pt.node->edges[c]->start;
        }
        pt = next_ap;
    }
    return ans;
}

pair<int, int> UkkonenSTree::matching(const string &p, int start) {
    pair<int, int> ans = pair<int, int>(0, 0);
    Point pt(root, NULL, 0);
    for (int i = start; i < p.size(); i++) {
        char c = p[i];
        Point next_ap = readEdge(pt, c);
        if (next_ap.node == NULL) {
            return ans;
        }
        ans.first++;
        if (pt.edge != NULL) {
            ans.second = pt.edge->start + pt.l;
        } else {
            ans.second = pt.node->edges[c]->start;
        }
        pt = next_ap;
    }
    return ans;
}

void UkkonenSTree::printTree() {
    stack<Node *> st;
    st.push(root);
    while (st.size()) {
        Node *node = st.top();
        st.pop();
        cout << node << ":" << endl;
        for (auto it = node->edges.begin(); it != node->edges.end(); it++) {
            cout << +it->first << ":";
            if (it->second->end != 1000000000) {
                for (int i = it->second->start; i <= it->second->end; i++) {
                    cout << +T[i];
                }
                cout << " " << it->second->child;
            } else {
                for (int i = it->second->start; i < T.size(); i++) {
                    cout << +T[i];
                }
                cout << " " << it->second->child;
            }
            st.push(it->second->child);
            cout << endl;
        }
        cout << endl;
    }
}