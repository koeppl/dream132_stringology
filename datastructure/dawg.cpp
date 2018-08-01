#include "dawg.h"

DAWG::DAWG(){
	root = new Node;
	root->slink = NULL;
}

DAWG::DAWG(const string &t){

}

DAWG::Node* DAWG::split(Node* parent, Node* child, char c){
	Node* new_node;
	parent->edges[c] = Edge (new_node,PRIMARY);
	for(auto it = child->edges.begin();it != child->edges.end();it++){
		new_node->edges[it->first] = Edge(it->second.first, SECONDARY);
	}
	new_node->slink = child->slink;
	child->slink = new_node;
	Node* current_node = parent;
	while(current_node != root){
		current_node = current_node->slink;
		auto it = current_node->edges.find(c);
		if(it != current_node->edges.end()
			&& it->second.first == child
			&& it->second.second == SECONDARY){
			it->second.first = new_node;
		} else{
			return new_node;
		}
	}
	return new_node;
}

void DAWG::addString(const string &t){
	int n = t.size();
	Node* active_node = root;
	for(int i = 0;i < n;i++){
		char c = t[i];
		auto it = active_node->edges.find(c);
		if(it != active_node->edges.end()){
			if(it->second.second == PRIMARY){
				active_node = it->first;
			} else{
				active_node = split(active_node, it->second.first, c);
			}
		} else{
			Node* new_node;
			Node* current_node = active_node;
			active_node->edges[c] = Edge(new_node, PRIMARY);
			while(current_node != NULL){
				current_node = current_node->suffix_link;
				auto it = current_node->edges.find(c);
				if(it == current_node->edges.end()){
					it->second = Edge(new_node, SECONDARY);
				} else if(it->second.second == PRIMARY){
					new_node->slink = it->second.second;
					break;
				} else{
					new_node->slink = split(current_node, it->second.first, c);
					break;
				}
			}
			if(current_node == NULL){
				new_node->slink = root;
			}
			active_node = new_node;
		}
	}
}