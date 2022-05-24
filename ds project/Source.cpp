#include <iostream>
#include <list>
#include <vector>
#include<fstream>
#include<queue>
//#include "graph.h"
//#include "vertex.h"
using namespace std;
# define INF 0x3f3f3f3f
#define INF INT_MAX

typedef pair<int, int> iPair;
typedef long long ll;

using namespace std;
bool visited[10000];

class edge
{
public:
	int destVertex;
	int weight;

	edge(int dest, int w)
	{
		destVertex = dest;
		weight = w;
	}

	void setWeight(int w)
	{
		weight = w;
	}

};

class vertex
{
public:
	int vid;
	string vname;
	list < edge > edgeList;

	vertex()
	{
		vid = 0;
		vname = "";
	}

	vertex(int id, string name)
	{
		vid = id;
		vname = name;
	}

	void setID(int id)
	{
		vid = id;
	}

	void setStateName(string sname)
	{
		vname = sname;
	}

	void printEdges()
	{
		cout << "[";
		for (auto i = edgeList.begin(); i != edgeList.end(); i++) {
			cout << i->destVertex << "(" << i->weight << ") => ";
		}
		cout << "]";
		cout << endl;
	}

	void updateVertexName(string name)
	{
		vname = name;
		cout << "Vertex Name Updated Successfully";
	}
};

class Graph
{
public:
	vector < vertex > vertices;

	// check if vertex exist
	bool checkVertex(int vid)
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			if (vertices.at(i).vid == vid)
			{
				return true;
			}
		}
		return false;
	}

	// to get vertex
	vertex getVertex(int vid)
	{
		vertex tmp;
		for (int i = 0; i < vertices.size(); i++)
		{
			tmp = vertices.at(i);
			if (tmp.vid == vid)
			{
				return tmp;
			}
		}
		return tmp;
	}

	bool checkEdge(int fromVertex, int toVertex)
	{
		vertex v = getVertex(fromVertex);
		list < edge > e;
		e = v.edgeList;
		for (auto i = e.begin(); i != e.end(); i++)
		{
			if (i->destVertex == toVertex)
			{
				return true;
				break;
			}
		}
		return false;
	}

	//================================================
	//================================================

	// to add Vertex
	void addVertex(vertex newVertex)
	{
		bool check = checkVertex(newVertex.vid);
		if (check == true)
		{
			cout << "Vertex with this ID already exist" << endl;
		}
		else
		{
			vertices.push_back(newVertex);
			cout << "New Vertex Added Successfully" << endl;
		}
	}


	// to update vertex
	void updateVertex(int oldVID, string vname)
	{
		bool check = checkVertex(oldVID);
		if (check == true)
		{
			for (int i = 0; i < vertices.size(); i++)
			{
				if (vertices.at(i).vid == oldVID)
				{
					vertices.at(i).setStateName(vname);
					break;
				}
			}
			cout << "Vertex(State) Updated Successfully " << endl;
		}
	}

	// to delete vertex
	void deleteVertex(int vid)
	{
		int vIndex = 0;
		for (int i = 0; i < vertices.size(); i++)
		{
			if (vertices.at(i).vid == vid)
			{
				vIndex = i;
			}
		}
		// to delete list of edges
		for (int i = 0; i < vertices.size(); i++)
		{
			for (auto j = vertices.at(i).edgeList.begin(); j != vertices.at(i).edgeList.end(); j++)
			{
				if (j->destVertex == vid)
				{
					vertices.at(i).edgeList.erase(j);
					break;
				}
			}
		}
		vertices.erase(vertices.begin() + vIndex);
		cout << "Vertex Deleted Successfully" << endl;
	}

	//================================================
	//================================================

	// to add edge
	void addEdge(int fromVertex, int toVertex, int weight)
	{
		// check if this two verticies is exist or not
		bool checkSrc = checkVertex(fromVertex);
		bool checkdst = checkVertex(toVertex);

		// check if exist edge between this two vertices or not
		bool checkIfExistEdge = checkEdge(fromVertex, toVertex);

		if (checkSrc && checkdst == true)
		{
			if (checkIfExistEdge == true)
			{
				cout << "Edge between " << getVertex(fromVertex).vname << "(" << fromVertex << ") and " << getVertex(toVertex).vname << "(" << toVertex << ") Already Exist" << endl;
			}
			else
			{

				for (int i = 0; i < vertices.size(); i++)
				{
					if (vertices.at(i).vid == fromVertex)
					{
						edge e(toVertex, weight);
						//edgeList.push_back(e); 
						//vertices.at(i).addEdgeToEdgelist(toVertex,weight);
						vertices.at(i).edgeList.push_back(e);
					}
					else if (vertices.at(i).vid == toVertex)
					{
						edge e(fromVertex, weight);
						//edgeList.push_back(e); 
						//vertices.at(i).addEdgeToEdgelist(fromVertex,weight);
						vertices.at(i).edgeList.push_back(e);
					}

				}

				cout << "Edge between " << fromVertex << " and " << toVertex << " added Successfully" << endl;
			}
		}
		else
		{
			cout << "Invalid Vertex ID entered.";
		}
	}

	// to update edge
	void updateEdge(int fromVertex, int toVertex, int newWeight)
	{
		bool check = checkEdge(fromVertex, toVertex);
		if (check == true)
		{
			for (int i = 0; i < vertices.size(); i++)
			{
				if (vertices.at(i).vid == fromVertex)
				{
					for (auto j = vertices.at(i).edgeList.begin(); j != vertices.at(i).edgeList.end(); j++)
					{
						if (j->destVertex == toVertex)
						{
							j->setWeight(newWeight);
							break;
						}
					}
				}
				else if (vertices.at(i).vid == toVertex)
				{
					for (auto j = vertices.at(i).edgeList.begin(); j != vertices.at(i).edgeList.end(); j++)
					{
						if (j->destVertex == fromVertex)
						{
							j->setWeight(newWeight);
							break;
						}

					}
				}
			}
			cout << "Edge Weight Updated Successfully " << endl;
		}
		else
		{
			cout << "Edge between " << getVertex(fromVertex).vname << "(" << fromVertex << ") and " << getVertex(toVertex).vname << "(" << toVertex << ") DOES NOT Exist" << endl;
		}
	}

	// to delete edge
	void deleteEdge(int fromVertex, int toVertex)
	{
		bool check = checkEdge(fromVertex, toVertex);
		if (check == true)
		{
			for (int i = 0; i < vertices.size(); i++)
			{
				if (vertices.at(i).vid == fromVertex)
				{
					for (auto j = vertices.at(i).edgeList.begin(); j != vertices.at(i).edgeList.end(); j++)
					{
						if (j->destVertex == toVertex)
						{
							vertices.at(i).edgeList.erase(j);
							//cout<<"First erase"<<endl;
							break;
						}
					}
				}

				if (vertices.at(i).vid == toVertex)
				{

					for (auto k = vertices.at(i).edgeList.begin(); k != vertices.at(i).edgeList.end(); k++)
					{
						if (k->destVertex == fromVertex)
						{
							vertices.at(i).edgeList.erase(k);
							//cout<<"second erase"<<endl;
							break;
						}
					}
				}
			}
			cout << "Edge Between " << fromVertex << " and " << toVertex << " Deleted Successfully." << endl;
		}
	}


	//================================================
	//================================================

	// to print graph
	void printGraph()
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			vertex v;
			v = vertices.at(i);
			cout << v.vname << " (" << v.vid << ") --> ";
			v.printEdges();
		}

	}
	/*
	void shortestPath(vector<pair<int, int> > adj[], int V, int src)
	{

		priority_queue<iPair, vector <iPair>, greater<iPair> > pq;

		vector<int> dist(V, INF);


		pq.push(make_pair(0, src));
		dist[src] = 0;


		while (!pq.empty())
		{

			int u = pq.top().second;
			pq.pop();


			for (auto x : adj[u])
			{

				int v = x.first;
				int weight = x.second;


				if (dist[v] > dist[u] + weight)
				{
					dist[v] = dist[u] + weight;
					pq.push(make_pair(dist[v], v));
				}
			}
		}


		printf("Vertex Distance from Source\n");
		for (int i = 0; i < V; ++i)
			printf("%d \t\t %d\n", i, dist[i]);
	}
	*/

	void dijk(int source, vector<vector<pair<int, int>>>& graph)
	{
		int n = graph.size();
		vector<int>dist(n, INF), pre(n, -1);
		priority_queue<pair<int, int>>nextToVisit;
		dist[source] = 0;
		pre[source] = source;
		nextToVisit.push({ 0,source });

		while (!nextToVisit.empty())
		{
			int u = nextToVisit.top().second; //u is node where i will visit next
			nextToVisit.pop();
			if (visited[u])
				continue;
			visited[u] = 1;
			for (auto e : graph[u]) //e is edges of this node 
			{
				int t = e.first; // t is the target
				int w = e.second; //c is the cost
				if (dist[u] + w < dist[t])
				{
					dist[t] = dist[u] + w;
					pre[t] = u;
					nextToVisit.push({ -dist[t],t });
				}
			}
		}
		for (int i = 1; i < n; i++)
			cout << i << "  :  " << dist[i] << endl;

	}

};

int main()
{
	Graph g;
	string sname;
	int id1, id2, w;
	int choice;
	bool check;

	int V;
	vector <iPair>adj[10];

	do {
		cout << "What operation do you want to perform? " <<
			" Select Option number. Enter 0 to exit.\n";
		cout << "[1] Add Vertex\n";
		cout << "[2] Update Vertex\n";
		cout << "[3] Delete Vertex\n";
		cout << "[4] Add Edge\n";
		cout << "[5] Update Edge\n";
		cout << "[6] Delete Edge\n";
		cout << "[7] Check if 2 Vertices are Neigbors or not\n";
		cout << "[8] Print Graph\n";
		cout << "[9] Shortest path\n";
		cout << "[0] Exit Program\n";

		cout << "\nEnter Choice : ";
		cin >> choice;
		cout << endl;

		vertex v1;
		if (choice == 0)
		{
			break;
		}
		else if (choice == 1)
		{
			ofstream vertex("addvertex.txt", ios::app);
			vertex << "    ***adding operation***     " << endl;
			vertex << "*...................................* " << endl;
			//ifstream vertex("vertex.txt", ios::app);
			cout << "Add Vertex Operation -" << endl;
			cout << "Enter State ID :";
			cin >> id1;
			vertex << "the id is:" << id1 << "  ";
			cout << "Enter State Name :";
			cin >> sname;
			vertex << "the state name is:" << sname << "  " << endl;
			v1.setID(id1);
			v1.setStateName(sname);
			g.addVertex(v1);

			//break;
		}
		else if (choice == 2)
		{
			ofstream vertex("addvertex.txt", ios::app);
			vertex << "    ***updating operation***     " << endl;
			vertex << "*...................................* " << endl;

			cout << "Update Vertex Operation -" << endl;
			cout << "Enter State ID of Vertex(State) to update :";
			cin >> id1;
			vertex << "the id of updated state is :" << id1 << " ";
			cout << "Enter State Name :";
			cin >> sname;
			vertex << "the new state is:" << sname << " " << endl;
			g.updateVertex(id1, sname);

			//break;
			vertex.close();
		}
		else if (choice == 3)
		{
			ofstream vertex("addvertex.txt", ios::app);
			vertex << "     ***deleting operation***     " << endl;
			vertex << "*-----*------*------*-----*-----* " << endl;

			cout << "Delete Vertex Operation -" << endl;
			cout << "Enter ID of Vertex(State) to Delete : ";
			cin >> id1;
			vertex << "the id of deleted state is :" << id1 << "  this state is no longer available   " << endl;
			g.deleteVertex(id1);
			
			//vertex << "the new state is:" << sname << " ";
			//break;
			vertex.close();
		}
		else if (choice == 4)
		{
			ofstream vertex("addvertex.txt", ios::app);
			vertex << "     ***adding edge  operation ***    " << endl;
			vertex << "*-----*------*------*-----*-----* " << endl;

			cout << "Add Edge Operation -" << endl;
			cout << "Enter ID of Source Vertex(State): ";
			cin >> id1;
			vertex << "the id of the source state is :" << id1 << "    " << endl;

			cout << "Enter ID of Destination Vertex(State): ";
			cin >> id2;
			vertex << "the id of the destination state is :" << id2 << "  " << endl;

			cout << "Enter Weight of Edge: ";
			cin >> w;
			vertex << "the weight of the edge is:" << w << "  " << endl;

			g.addEdge(id1, id2, w);

			//break;
			vertex.close();
		}
		else if (choice == 5)
		{
			ofstream vertex("addvertex.txt", ios::app);
			vertex << "     ***updating edge  operation ***    " << endl;
			vertex << "*-----*------*------*-----*-----* " << endl;

			cout << "Update Edge Operation -" << endl;
			cout << "Enter ID of Source Vertex(State): ";
			cin >> id1;
			vertex << "the id of the update source state is :" << id1 << "    " << endl;

			cout << "Enter ID of Destination Vertex(State): ";
			cin >> id2;
			vertex << "the id of the update destination state is :" << id2 << "    " << endl;

			cout << "Enter UPDATED Weight of Edge: ";
			cin >> w;
			vertex << "the id of the update weight of edge :" << w << "    " << endl;

			g.updateEdge(id1, id2, w);
			//break;
			vertex.close();
		}
		else if (choice == 6)
		{
			ofstream vertex("addvertex.txt", ios::app);
			vertex << "     ***deleting edge  operation ***    " << endl;
			vertex << "*-----*------*------*-----*-----* " << endl;

			cout << "Delete Edge Operation -" << endl;
			cout << "Enter ID of Source Vertex(State): ";
			cin >> id1;
			vertex << "the id of the update source state is :" << id1 << "    " << endl;

			cout << "Enter ID of Destination Vertex(State): ";
			cin >> id2;
			vertex << "the id of the update source state is :" << id2 << "    " << endl;

			g.deleteEdge(id1, id2);

			//break;
			vertex.close();
		}
		else if (choice == 7)
		{
			ofstream vertex("addvertex.txt", ios::app);
			vertex << "     ***checking operation ***    " << endl;
			vertex << "*-----*------*------*-----*-----* " << endl;
			
			cout << "Check if 2 Vertices are Neigbors -" << endl;
			cout << "Enter ID of Source Vertex(State): ";
			cin >> id1;
			//vertex << "the id of the source state is :" << id1 << "    " << endl;

			cout << "Enter ID of Destination Vertex(State): ";
			cin >> id2;
			//vertex << "the id of the destination state is :" << id2 << "    " << endl;

			check = g.checkEdge(id1, id2);
			if (check == true)
			{
				vertex << "the id of the source state is :" << id1 << "    " << endl;
				vertex << "the id of the destination state is :" << id2 << "    " << endl;
				vertex << "" << " Vertices are Neigbors (Edge does NOT exist)   " << endl;

				cout << "Vertices are Neigbors (Edge exist)";


			}
			else
			{
				vertex << "the id of the source state is :" << id1 << "    " << endl;
				vertex << "the id of the destination state is :" << id2 << "    " << endl;
				vertex << "" << " Vertices are NOT Neigbors (Edge does NOT exist)   " << endl;


				cout << "Vertices are NOT Neigbors (Edge does NOT exist)";
			}

			//break;
			vertex.close();
		}
		else if (choice == 8)
		{
			ofstream vertex("addvertex.txt", ios::app);
			vertex << "     ***printing graph operation ***    " << endl;
			vertex << "*-----*------*------*-----*-----* " << endl;

			cout << "Print Graph Operation -" << endl;
			g.printGraph();

			//break;
			vertex << "printing graph operation done  " << endl;

			vertex.close();
		}
		else if (choice == 9)
		{
			int n;
			int m;
			cout << "Enter numbers of vertex:" << endl;
			cin >> n;
			cout << "Enter numbers of Edges:" << endl;
			cin >> m;

			vector<vector<pair<int, int>>>adj(n + 1);
			for (int i = 0; i < m; i++)
			{
				int u, t, c;
				cout << "Enter the vertex(Source):" << endl;
				cin >> u;
				cout << "Enter the vertex (Destination):" << endl;
				cin >> t;
				cout << "Enter the distance between them:" << endl;
				cin >> c;
				adj[u].push_back({ t,c });
			}
			cout << "The Shortest path between all of vertex is:";
			g.dijk(1, adj);
		}
		else
		{
			cout << "Envalid choice! " << endl;
		}

		cout << endl;

	} while (choice != 0);

	cout << "=================================================\n";
	cout << "\tThank you for using we project.\n";
	cout << "=================================================\n";
	return 0;
}

/*
void addEdge(vector<int> adj[], int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}
void printGraph(vector<int> adj[], int V)
{
	for (int i = 0; i < V; ++i) {
		cout << "\n Adjacency list of vertex " << i
			<< "\n head ";
		for (auto x : adj[i])
			cout << "-> " << x;
		printf("\n");
	}
}
*/

/*
class graph {
public:
	list<int>* adjlist;
	int n;

	graph(int v) {
		adjlist = new list<int>[v];
		n = v;
	}

	void addedge(int u, int v, bool bi) {
		adjlist[u].push_back(v);
		if (bi) {
			adjlist[v].push_back(u);
		}
	}

	void print() {
		for (int i = 0; i < n; i++) {
			cout << i << "-->";
			for (auto it : adjlist[i]) {
				cout << it << " ";
			}
			cout << endl;
		}
		cout << endl;
	}


};

int main() {
	graph g(5);
	g.addedge(1, 2, true);
	g.addedge(4, 2, true);
	g.addedge(1, 3, true);
	g.addedge(4, 3, true);
	g.addedge(1, 4, true);

	g.print();
}
*/


/*
const int v = Vertex::get_no_v();
int graph::minDistance(int dist[], bool sptSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;
	for (int i = 0; i < v; i++)
		if (sptSet[i] == false && dist[i] <= min)
			min = dist[i], min_index = i;
	return min_index;
}
void graph::printSolution(int dist[])
{
	cout << "Vertex \t Distance from Source" << endl;
	for (int i = 0; i < v; i++)
		cout << i << " \t\t" << dist[i] << endl;
}
void graph::dijkstra(int graph[v][v], int src)
{
	int dist[v]; // The output array. dist[i] will hold the shortest
	// distance from src to i
	bool sptSet[v]; // sptSet[i] will be true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized
	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < v; i++)
		dist[i] = INT_MAX, sptSet[i] = false;
	// Distance of source vertex from itself is always 0
	dist[src] = 0;
	// Find shortest path for all vertices
	for (int count = 0; count < v - 1; count++) {
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in the first iteration.
		int u = minDistance(dist, sptSet);
		// Mark the picked vertex as processed
		sptSet[u] = true;
		// Update dist value of the adjacent vertices of the picked vertex.
		for (int i = 0; i < v; i++)
			// Update dist[v] only if is not in sptSet, there is an edge from
			// u to v, and total weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!sptSet[i] && graph[u][i] && dist[u] != INT_MAX
				&& dist[u] + graph[u][i] < dist[i])
				dist[i] = dist[u] + graph[u][i];
	}
	printSolution(dist);
}
*/