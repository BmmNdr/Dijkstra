#include "Node.h"

Node::Node()
{
	this->id = "";
	this->distFromOrigin = INT_MAX;
}

Node::Node(string id)
{
	this->id = id;
	this->distFromOrigin = INT_MAX;
}
