#include <iostream>
#include "..\Structures.h"
#include "..\ShortestPaths.h"

using namespace std;
using namespace sgl;

int main()
{
	Graph_List<Edge_Weight<> > G(5, true); 
	G.insert(new Edge_Weight<>(0,1,1));
	G.insert(new Edge_Weight<>(1,3,6));
	G.insert(new Edge_Weight<>(3,0,3));
	G.insert(new Edge_Weight<>(1,2,2));
	G.insert(new Edge_Weight<>(4,2,2));
	G.insert(new Edge_Weight<>(4,3,1));
	G.insert(new Edge_Weight<>(0,2,4));
	G.insert(new Edge_Weight<>(2,4,2));

	Dijkstra<> dijkstra(G);
	dijkstra(0);

	cout<<"Vertex\t Distance to 0"<<endl;
	for(int i = 0; i < dijkstra.dist.size(); i++)
		cout<<i<<"\t "<<dijkstra.dist[i]<<endl;

	/*! The shortest path tree is stored in dijkstra.SPT */

	return 0;
}