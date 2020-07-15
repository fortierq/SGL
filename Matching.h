/*!
 * \file Matching.h
 *  Matching algorithms
 */


#ifndef MATCHING_H
#define MATCHING_H

#include <list>
#include "Structures.h"
#include "Flow.h"

namespace sgl
{
/*! Computes the maximum matching cardinal using Fulkerson algorithm 
\remarks The maximum matching cardinal is equal to the minimum vertex cover cardinal 
\todo Output the edges of a maximum matching and the vertices of the minimum vertex cover */
template<typename type_flow = int, class Edge = Edge_Flow<type_flow>, class Bipartite = Bipartite_list<Edge> > class MaxMatching_Graph
{
public:
	int s, t;
	Bipartite &G;
	/*! Construct the associated std::max flow problem
	\param G: Bipartite graph, all edges must have capacity equals to one */
	MaxMatching_Graph(Bipartite &G) : G(G) 
	{ 
		s = G.V();
		t = G.V() + 1;
		G.resize(G.V() + 2); // on rajoute s et t
		for(std::list<int>::iterator it = G.X.begin(); it != G.X.end(); ++it)
			G.insert(new Edge(s, *it, 1));
		for(std::list<int>::iterator it = G.Y.begin(); it != G.Y.end(); ++it)
			G.insert(new Edge(*it, t, 1));
	};
	/*! \returns Maximum matching cardinal */
	int operator()()
	{
		NoNullCap<Edge> proc(G.V(), t);
		DFS<NoNullCap<Edge>, Edge, Bipartite> dfs(G, proc);

		Fulkerson<type_flow, Edge, NoNullCap<Edge>, Bipartite, DFS<NoNullCap<Edge>, Edge, Bipartite> > ful(G, proc);
			
		ful(s, t);
		return ful.get_outflow(s);
	}
};
}

#endif
