#pragma once
#include <iostream>
using namespace std;

class Node
{
public:
	//Node previous;
	int distFromOrigin;
	string id;
	Node* prec;

	Node();
	Node(string id);
	string printPrec();
};

