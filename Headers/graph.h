#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <vector>
class Node {

	int index;
public:
	std::set<Node*> connections;
	std::vector<Node*> conIndxs;
	Node(int index) {
		this->index = index;
	}
	void connectTo(Node* node) {
		conIndxs.push_back(node);
		connections.insert(node);
	}
	void disconnectFrom(Node* node) {
		connections.erase(node);
	}
	bool connectedTo(Node* node) {
		std::set<Node*>::iterator it = connections.find(node);
		if (it != connections.end())return true;
		return false;
	}
	int getIndex() {
		return index;
	}
};

class Graph {
	std::set<Node*> vertices;
public:
	void createNode(int index) {
		vertices.insert(new Node(index));
	}

	void connectTwo(int a, int b) {
		Node* nA = findByIndex(a);
		Node* nB = findByIndex(b);

		nA->connectTo(nB);
		nB->connectTo(nA);
	}
	Node* findByIndex(int index) {
		Node* res=nullptr;
		for (Node* nd : vertices) {
			if (nd->getIndex() == index)res = nd;
		}
		return res;
	}

};

class DFS {

	int depth;
public:
	std::set<Node*> visited;
	DFS() {
		srand(time(0));
	}
	//void traverse(Node* node) {
	//	//if (depth > 0)
	//	//	--depth;
	//	//else return;
	//	for (int q = 0; q < node->connections.size();++q) {
	//		int indx=  rand() % node->conIndxs.size();
	//		Node* tempNode = node->conIndxs[indx];
	//		node->conIndxs.erase(node->conIndxs.begin()+indx);
	//		int takenNeighbours = 0;
	//		for (Node* explorer : tempNode->connections) {
	//			if (visited.find(explorer) != visited.end()) {
	//				++takenNeighbours;
	//			}
	//		}
	//		if (takenNeighbours > 1)return;
	//		if (visited.find(tempNode) == visited.end()) {
	//			visited.insert(tempNode);
	//			traverse(tempNode);

	//		}
	//	}
	//}
	void traverse(Node* node) {
		visited.insert(node);

		Node* successor;

		//pick unvisited  successor
		do {
			int randIndex = rand() % node->conIndxs.size();
			successor = node->conIndxs[randIndex];
			node->conIndxs.erase(node->conIndxs.begin() + randIndex);

			int neighbourCount=0;
			for (Node* explore : successor->conIndxs)
				if (visited.find(explore) != visited.end())
					++neighbourCount;
			if (neighbourCount >= 2)successor = node;




		} while (node->conIndxs.size() > 0 && visited.find(successor) != visited.end());

		if (node->conIndxs.size() <= 0)return; //if there is none then go back to previous

		traverse(successor);
		traverse(node);
	}
	void traverse(Graph* g, int index, int depth) {
		this->depth = depth;
		traverse(g->findByIndex(index));


	}


};


#endif