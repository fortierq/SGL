#include <iostream>
#include "..\Structures.h"
#include "..\Search.h"
#include "..\Flow.h"
#include "..\IO.h"

using namespace std;
using namespace sgl;

typedef Edge_Flow<> Flow;
typedef Graph_List<Flow> Network;

int main()
{
	Network G(5, false); 
	/* The graph MUST be not oriented (ie digraph == false), if you want to have non oriented capacities, 
	add two edges: G.insert(new Flow(u, v, cap)) and G.insert(new Flow(v, u, cap)) */
	G.insert(new Flow(0, 1, 10));
	G.insert(new Flow(0, 2, 1));
	G.insert(new Flow(1, 2, 1));
	G.insert(new Flow(1, 3, 2));
	G.insert(new Flow(2, 4, 7));
	G.insert(new Flow(3, 4, 1));
	G.insert(new Flow(3, 0, 3));
	G.insert(new Flow(4, 2, 2));

	int s = 0, t = 4; /* Source and sink */
	NoNullCap<> noNull(G.V(), t); 
	Fulkerson<int, Flow> ful(G, noNull, s, t);
	ful(0);
	
	Network H(5, false); 
	/* The graph MUST be not oriented (ie digraph == false), if you want to have non oriented capacities, 
	add two edges: H.insert(new Flow(u, v, cap)) and H.insert(new Flow(v, u, cap)) */
	H.insert(new Flow(0, 1, 10));
	H.insert(new Flow(0, 2, 1));
	H.insert(new Flow(1, 2, 1));
	H.insert(new Flow(1, 3, 2));
	H.insert(new Flow(2, 4, 7));
	H.insert(new Flow(3, 4, 1));
	H.insert(new Flow(3, 0, 3));
	H.insert(new Flow(4, 2, 2));

	Preflow<> pre(H, s, t);
	pre();
	IO<Flow, Network>::show_flow(G);
	IO<Flow, Network>::show_flow(H);
	return 0;
}