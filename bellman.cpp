#include <iostream>
#include "..\Structures.h"
#include "..\ShortestPaths.h"

using namespace std;
using namespace sgl;

int main()
{
	Graph_List<Edge_Weight<> > G(5, true); 
	Edge_Weight<> *e = new Edge_Weight<>(1,3,6); // Edge we will modify weight

	G.insert(new Edge_Weight<>(0,1,1));
	G.insert(e);
	G.insert(new Edge_Weight<>(3,0,3));
	G.insert(new Edge_Weight<>(1,2,2));
	G.insert(new Edge_Weight<>(4,2,2));
	G.insert(new Edge_Weight<>(4,3,1));
	G.insert(new Edge_Weight<>(0,2,4));
	G.insert(new Edge_Weight<>(2,4,2));

	Bellman<true> bellman1(G); // You can also use Bellman<true> since there is no negative edges
	bool noNegCycle = bellman1(0); 
	// noNegCycle == true
	cout<<"Vertex\t Distance to 0"<<endl;
	for(int i = 0; i < bellman1.dist.size(); i++)
		cout<<i<<"\t "<<bellman1.dist[i]<<endl;

	e->set_wt(-5); // We introduce a negative cycle
	Bellman<true> bellman2(G);
	noNegCycle = bellman2(0);
	// noNegCycle == false, bellman2.dist is not relevant

	return 0;
}