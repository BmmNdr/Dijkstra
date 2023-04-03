#pragma once
#include "Node.h"

class Edge
{
public:
	Node* node1;
	Node* node2;
	int weight;

	Edge();
	Edge(Node* node1, Node* node2, int weight);
};

