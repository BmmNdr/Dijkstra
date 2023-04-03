#include "Edge.h"
#include <vector>

void Dijkstra(vector<Node*> &nodes, vector<Edge> edges);
Node* findOrigin(vector<Node*> nodes);
Node* getSmallest(vector<Node*> &queue);
vector<Edge> findAdiacent(Node* centralNode, vector<Edge> edges);

/*
Ogni nodo deve avere: una distanza dall'origine (inizialmente infinita o 0 se si tratta dell'origine), un nome

Ogni collegamento deve avere due nodi ed un peso

Funzionamento:
Prendo l'origine, controllo I vicini assegnando la distanza dall'origine uguale al peso. Inserisco I vicini nella lista da controllare. (Rimuovo l'origine dalla lista dei nodi l'origine)
Prendo il nodo con il peso minore dalla lista da controllare. Controllo I vicini e assegno la distanza dall'origine uguale alla distanza del nodo piu' il peso. Inserisco I nodi adiacenti nella lista da controllare.
Rimuovo il nodo dalla lista dei nodi.
Ripeto il processo fino che la lista dei nodi e' vuota.
*/

void main() {
	
	/*
	//All the nodes in the graph
	Node* nodeA = new Node("A");
	Node* nodeB = new Node("B");
	Node* nodeC = new Node("C");
	Node* nodeD = new Node("D");
	vector<Node*> nodes {nodeA, nodeB , nodeC ,nodeD };
	//All the connection between nodes in the graph
	vector<Edge> edges;

	//		    1
	//		A ----- B
	//		|       |
	//	  4 |       | 1
	//		|       |
	//		D ----- C
	//          1
	
	edges.push_back(Edge(nodeA, nodeB, 1));
	edges.push_back(Edge(nodeB, nodeC, 1));
	edges.push_back(Edge(nodeC, nodeD, 1));
	edges.push_back(Edge(nodeD, nodeA, 4));
	nodeA->distFromOrigin = 0;
	*/
	
	Node* nodeA = new Node("A");
	Node* nodeB = new Node("B");
	Node* nodeC = new Node("C");
	Node* nodeD = new Node("D");
	Node* nodeE = new Node("E");
	Node* nodeF = new Node("F");
	Node* nodeG = new Node("G");
	vector<Node*> nodes{ nodeA, nodeB , nodeC ,nodeD, nodeE, nodeF, nodeG};

	vector<Edge> edges;
	edges.push_back(Edge(nodeA, nodeC, 1));
	edges.push_back(Edge(nodeA, nodeD, 2));
	edges.push_back(Edge(nodeC, nodeD, 1));
	edges.push_back(Edge(nodeC, nodeB, 2));
	edges.push_back(Edge(nodeC, nodeE, 3));
	edges.push_back(Edge(nodeF, nodeB, 3));
	edges.push_back(Edge(nodeF, nodeE, 2));
	edges.push_back(Edge(nodeF, nodeG, 1));
	edges.push_back(Edge(nodeD, nodeG, 1));

	nodeA->distFromOrigin = 0; //define origin

	Dijkstra(nodes, edges);

	for (int i = 0; i < nodes.size(); i++)
	{
		cout << "Node " << nodes.at(i)->id << " Dist " << nodes.at(i)->distFromOrigin << endl;
	}
}

void Dijkstra(vector<Node*> &nodes, vector<Edge> edges) {
	//Nodes checked during Dijkstra that still needs to be visited
	vector<Node*> queue;

	Node* origin = findOrigin(nodes);
	queue.push_back(origin);

	while (queue.size() > 0)
	{
		try
		{
			Node* visitingNode = getSmallest(queue);
			vector<Edge> adiacentNodes = findAdiacent(visitingNode, edges);

			for (int i = 0; i < adiacentNodes.size(); i++)
			{
				Edge visitingEdge = adiacentNodes.at(i);
				Node* endNode = (visitingEdge.node1 == visitingNode ? visitingEdge.node2 : visitingEdge.node1);

				int w = visitingNode->distFromOrigin + visitingEdge.weight;

				if (w < endNode->distFromOrigin) {
					endNode->distFromOrigin = w;
					queue.push_back(endNode);
				}
			}
		}
		catch (const std::exception&)
		{
			cout << "Queue dimension less then 0";
			return;
		}
	}
}

//Find the origin node. Origin Node MUST have 0 as distance from origin
Node* findOrigin(vector<Node*> nodes) {

	auto is_origin = [](Node* n) {return n->distFromOrigin == 0; };

	return *find_if(nodes.begin(), nodes.end(), is_origin);
}

//get the node with the smallest distance from origin in queue vector
//Could be opt using a ordered queue
Node* getSmallest(vector<Node*> &queue) {

	if (queue.size() <= 0)
		return NULL;

	Node* toRet = queue.at(0);
	int index = 0;

	for(int i = 1; i < queue.size(); i++){
		if (queue.at(i)->distFromOrigin < toRet->distFromOrigin) {
			toRet = queue.at(i);
			index = i;
		}
	}

	queue.erase(queue.begin() + index);
	return toRet;
}

string centralNodeId; //Global Variable needed for lambda expr (is_adiacent). I wanted to use a lambda fun :)
vector<Edge> findAdiacent(Node* centralNode, vector<Edge> edges) {

	centralNodeId = centralNode->id;

	//Check if node1 or node2 of the edge is equal to visiting node
	auto is_adiacent = [](Edge e) {return e.node1->id == centralNodeId || e.node2->id == centralNodeId; };

	vector<Edge> adiacentNodes;

	//iterator from the begin
	vector<Edge>::iterator iter = edges.begin();
	//if i reach the end, return the adicent nodes list
	while ((iter = find_if(iter, edges.end(), is_adiacent)) != edges.end())
	{
		adiacentNodes.push_back(*iter);
		//if i find a match, add 1 to the iterator to find all the matches after this one
		iter++;
	}

	return adiacentNodes;
}

