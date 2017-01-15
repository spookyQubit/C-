/* Breadth first traversal for graphs */ 

#include <iostream>
#include <list>
#include <queue>
#include <set>

/*
      <---- 
     2---->0---->1
      <----------
     |
     |
     | 
     V
  C---3 
   ---> 
*/

using namespace std;

class Graph
{
    public:
    	Graph(int num_vertices);
    	~Graph();
    	void add_edge(int v_start, int v_end); // add edge from vertex v_start to v_end
    	void BFS(int v_s); // BreadthFirstSearch starting at vertex v_s 
    	void DFS(int v_s, set<int>& s_is_visited); // DeapthFirstSearch starting at vertex v_s
    	void print_edges();
    private:
    	int d_v; // Number of vertices 
    	list<int> *d_adj_list; // Adjacency list
};

Graph::Graph(int num_vertices)
{
	d_v = num_vertices;
	d_adj_list = new list<int>[d_v];
}

Graph::~Graph()
{
	delete[] d_adj_list;
}

void Graph::add_edge(int v_start, int v_end)
{
	d_adj_list[v_start].push_back(v_end); // this is a directed graph
}

void Graph::print_edges()
{
	for(int i=0; i<d_v; ++i)
	{
		for(list<int>::const_iterator iter = d_adj_list[i].begin(); 
			iter != d_adj_list[i].end();
			++iter)
		{
			cout << i << " ----> " << *iter << endl;
		}
	}
}

void Graph::BFS(int v_s)
{
	// assert that v_s in in the graph

	queue<int> q; // queue to push the vertices connected to each vertex. 
    set<int> s_is_visited; // set to store whehter the vertex is already visited

	q.push(v_s);
    s_is_visited.insert(v_s);
	while(!q.empty())
	{
		int current_vertex = q.front();
		cout << current_vertex << endl; // Printing the breadth first traversal
		for(list<int>::const_iterator iter = d_adj_list[current_vertex].begin();
			iter != d_adj_list[current_vertex].end();
			++iter)
		{
			if(s_is_visited.find(*iter) == s_is_visited.end())
			{
				q.push(*iter);
				s_is_visited.insert(*iter);
			}
		}
		q.pop();
	}
}


void Graph::DFS(int v_s, set<int>& s_is_visited)
{
	if(s_is_visited.find(v_s) != s_is_visited.end())
	{
		return;
	}

    cout << v_s << endl; // Print deapth first traversal
	s_is_visited.insert(v_s);
    for(list<int>::const_iterator iter = d_adj_list[v_s].begin();
    	iter != d_adj_list[v_s].end();
    	++iter)
    {
    	if(s_is_visited.find(*iter) != s_is_visited.end())
    	{
    		continue;
    	}
    	DFS(*iter, s_is_visited);
    }
}

int main()
{
	Graph g(4);

	g.add_edge(2, 0);
	g.add_edge(0, 2);
	g.add_edge(0, 1);
	g.add_edge(1, 2);
	g.add_edge(2, 3);
    g.add_edge(3, 3);

    cout << "Printing edges" << endl;
    g.print_edges();
    cout << "Printing BFS" << endl;
    g.BFS(2);
    cout << "Printing DFS" << endl;
    set<int> s_is_visited;
    g.DFS(2, s_is_visited);
}