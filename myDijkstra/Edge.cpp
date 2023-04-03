#include "Edge.h"

Edge::Edge()
{
}

Edge::Edge(Node* node1, Node* node2, int weight)
{
	this->node1 = node1;
	this->node2 = node2;
	this->weight = weight;
}
