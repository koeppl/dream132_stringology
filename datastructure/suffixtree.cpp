#include "suffixtree.h"

UkkonenSTree::UkkonenSTree() {
    root = new Node;
    active_point = Point(root, NULL, 0);
    next_leaf = 0;
    aux = new Edge(0, 0, root);
}

UkkonenSTree::UkkonenSTree(const string &t) {
    root = new Node;
    active_point = Point(root, NULL, 0);
    next_leaf = 0;
    aux = new Edge(0, 0, root);
    T = t;
    addPrefix(0);
}

UkkonenSTree::Point UkkonenSTree::readEdge(Point ap, char c) {
    if (ap.edge != NULL) {
        if (T[ap.edge->start + ap.l] == c) {
            // cout << "edge exists" << endl;
            if (ap.edge->start + ap.l == ap.edge->end) {
                return Point(ap.edge->child, NULL, 0);
            } else {
                ap.l++;
                return ap;
            }
        } else {
            // cout << "edge not exists" << endl;
            return Point(NULL, NULL, 0);
            // no path labeled by c
        }
    } else {
        if (ap.node->edges.find(c) != ap.node->edges.end()) {
            // cout << "edge exists" << endl;
            auto eg = ap.node->edges[c];
            if (eg->start == eg->end) {
                return Point(eg->child, NULL, 0);
            } else {
                return Point(ap.node, eg, 1);
            }
        } else {
            // no path labeled by c
            // cout << "edge not exists" << endl;
            return Point(NULL, NULL, 0);
        }
    }
}

void UkkonenSTree::addPrefix(int pos) {
    for (int i = pos; i < T.size(); i++) {
        // printTree();
        char c = T[i];
        // cout << c << endl;
        Point next_ap = readEdge(active_point, c);
        Node *last_node = NULL;
        // cout << "got next ap" << endl;
        while (next_ap.node == NULL) {
            if (active_point.edge == NULL) {
                // cout << "add leaf" << endl;
                Node *new_leaf = new Node;
                Edge *new_edge = new Edge(i, 1000000, new_leaf);
                active_point.node->edges[c] = new_edge;
                if (last_node != NULL) {
                    last_node->slink = active_point.node;
                }
                last_node = NULL;
                if (active_point.node == root) {
                    next_ap = active_point;
                } else {
                    active_point.node = active_point.node->slink;
                    next_ap = readEdge(active_point, c);
                }
            } else {
                // cout << "split edge" << endl;

                Node *new_leaf = new Node;
                Node *new_node = new Node;
                Edge *new_edge_to_leaf = new Edge(i, 1000000, new_leaf);
                Edge *new_edge_to_node = new Edge(active_point.edge->start + active_point.l,
                                                  active_point.edge->end, active_point.edge->child);
                int depth = active_point.l;

                // split edge and add leaf
                new_node->edges[c] = new_edge_to_leaf;
                new_node->edges[T[active_point.edge->start + active_point.l]] = new_edge_to_node;
                active_point.edge->end = active_point.edge->start + active_point.l - 1;
                active_point.edge->child = new_node;
                if (last_node != NULL) {
                    last_node->slink = new_node;
                }

                last_node = new_node;

                // cout << "next ap" << endl;

                // next_active_point
                Node *temp;
                if (active_point.node == root) {
                    depth--;
                    temp = root;
                } else {
                    temp = active_point.node->slink;
                }

                // cout << depth << endl;
                // cout << temp << endl;

                char d = T[active_point.edge->start + active_point.l - depth];
                while (temp->edges[d]->end - temp->edges[d]->start < depth) {
                    depth -= temp->edges[d]->end - temp->edges[d]->start + 1;
                    temp = temp->edges[d]->child;
                    d = T[active_point.edge->start + active_point.l - depth];
                    // cout << depth << endl;
                    // cout << temp << endl;
                }

                active_point.node = temp;
                if (depth == 0) {
                    active_point.edge = NULL;
                    // cout << active_point.node << endl;
                } else {
                    active_point.edge = temp->edges[d];
                    // cout << active_point.node << " " << active_point.edge->child << endl;
                }

                active_point.l = depth;
                next_ap = readEdge(active_point, c);
                // cout << "got next ap" << endl;
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

pair<int, int> UkkonenSTree::matching(const string &p) {
    pair<int, int> ans = pair<int, int>(0, 0);
    Point pt(root, NULL, 0);
    for (int i = 0; i < p.size(); i++) {
        char c = p[i];
        Point next_ap = readEdge(active_point, c);
        if (next_ap.node == NULL) {
            return ans;
        }
        ans.first++;
        if (pt.edge != NULL) {
            ans.second = pt.edge->start + pt.l;
        } else {
            ans.second = pt.node->edges[c]->start;
        }
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
            cout << it->first << ":";
            if (it->second->end != 1000000) {
                for (int i = it->second->start; i <= it->second->end; i++) {
                    cout << T[i];
                }
                cout << " " << it->second->child;
            } else {
                for (int i = it->second->start; i < T.size(); i++) {
                    cout << T[i];
                }
                cout << " " << it->second->child;
            }
            st.push(it->second->child);
            cout << endl;
        }
        cout << endl;
    }
}