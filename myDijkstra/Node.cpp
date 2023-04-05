#include "Node.h"

Node::Node()
{
	this->id = "";
	this->distFromOrigin = INT_MAX;
	this->prec = NULL;
}

Node::Node(string id)
{
	this->id = id;
	this->distFromOrigin = INT_MAX;
	this->prec = NULL;
}

string Node::printPrec()
{
	string s = this->id;

	if (this->prec == NULL)
		return s;
	

	return s + " " + this->prec->printPrec();
}
