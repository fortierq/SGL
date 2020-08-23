#include "../Structures.h"
#include "../Search.h"
#include <iostream>
#include <list>

using namespace std;
using namespace sgl;

/* Processor for DFS, makes the ordered list of visited vertices */
class ListVisited : public Proc_Base<>
{
public :
	list<int> visited;
	ListVisited(int V) : Proc_Base<>(V), visited() { }
	bool trait(int i)
	{
		visited.push_back(i);
		return false;
	}
};

int main()
{
	Graph_List<Edge_Base> G(5, true);
	G.insert(new Edge_Base(0,1));
	G.insert(new Edge_Base(1,3));
	G.insert(new Edge_Base(3,0));
	G.insert(new Edge_Base(1,2));
	G.insert(new Edge_Base(4,2));
	G.insert(new Edge_Base(3,4));


	ListVisited l(G.V());
	DFS<Edge_Base, ListVisited> dfs(G, l);
	dfs(0);
	cout<<"Vertices visited in this order:"<<endl;
	for(list<int>::iterator it = l.visited.begin(); it != l.visited.end(); ++it)
		cout<<*it<<endl;

	return 0;
}
