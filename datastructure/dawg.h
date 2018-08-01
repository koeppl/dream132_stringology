#pragma once

#ifndef __DAWG_H__

#define __DAWG_H__

#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

class DAWG{
	private:
	typedef pair<Node*, bool> Edge;
	enum
	{
		PRIMARY = 0,
		SECONDARY = 1

	};
	
	struct Node{
		map<char,Edge> edges;
		Node* slink;
	};
	
	Node* root;
	Node* split(Node* parent, Node* child, char c);

	public:
	DAWG();
	DAWG(const string &t);
	void addString(const string &t);
};


#endif // __DAWG_H__ 
