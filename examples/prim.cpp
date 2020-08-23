#include <iostream>
#include "../Structures.h"
#include "../ShortestPaths.h"

using namespace std;
using namespace sgl;

int main()
{
	Graph_List<Edge_Weight<> > G(5, false); /* The graph must be not oriented */
	G.insert(new Edge_Weight<>(0,1,1));
	G.insert(new Edge_Weight<>(1,3,6));
	G.insert(new Edge_Weight<>(3,0,3));
	G.insert(new Edge_Weight<>(1,2,2));
	G.insert(new Edge_Weight<>(4,2,2));
	G.insert(new Edge_Weight<>(4,3,1));
	G.insert(new Edge_Weight<>(0,2,4));
	G.insert(new Edge_Weight<>(2,4,2));

	Prim<> prim(G);
	prim(0);

	cout<<"Edges in the computed minimum spanning tree: "<<endl;
	Tree_List<Edge_Weight<> >::iterator_all it(prim.MST);
	for(Edge_Weight<> *e = it.beg(); !it.end(); e = it.nxt())
		cout<<*e<<endl;

	cout<<endl<<"Minimum spanning tree weight: "<<prim.get_wt_MST()<<endl;
	return 0;
}
