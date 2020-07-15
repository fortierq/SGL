/*!
 * \file Transformation.h
 *  Algorithms processing a graph
 */

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <vector>
#include <iterator>

#include "Structures.h"

namespace sgl
{
/*! \param inGraph Graph to be transposed
\param outGraph The transposed matrix */
template<class Edge, class Graph> void transpose(const Graph &inGraph, Graph &outGraph)
{
	typename Graph::iterator_all it(inGraph);
	for(Edge *e = it.beg(); !it.end(); e = it.nxt())
		outGraph.insert(new Edge(e->w(), e->v(), e->wt()));
}

/*! Transitive closure 
\param[in] Graph Type of the graph transitive closure will be computed
\param[out] tcGraph Type of the transitive closure graph */
template <class Edge = Edge_Base, class tcGraph = Graph_Matrix<Edge>, class Graph = Graph_List<Edge> > class TC 
{ 
public:
	/*! Transitive closure of G */
	tcGraph T;

	/*! Copy G in T */
	TC(const Graph &G) : T(G) {  }

	/*! Compute the transitive closure */
	void operator()
	{
		for (int s = 0; s < T.V(); s++) 
			T.insert(new Edge(s, s, 0));
		for (int i = 0; i < T.V(); i++)
			for (int s = 0; s < T.V(); s++)
				if (T.edge(s, i))
					for (int t = 0; t < T.V(); t++)
						if (T.edge(i, t))
							T.insert(new Edge(s, t, 0));
	}
};

/*! Strongly connected components 
\todo Comment */
template<class Edge = Edge_Base, class Graph = Graph_List<Edge> > class SCC
{
	const Graph &G;
	class Proc
	{
	public:
		int V;
		std::vector<bool> visited; 
		Proc(int V) : V(V) {}
		void init(int source) 
		{
			visited.clear();
			visited.resize(V, false);
			visited[source] = true;
		}
		inline bool trait(int v) { return false; }
		bool toVisit(Edge *e, int toVertex)
		{ 
			if(visited[toVertex] == true) 
				return false;
			visited[toVertex] = true; 
			return true; 
		}
	};
public:
	std::vector<int> represSCC;
	SCC(const Graph &G) : G(G) { }
	void operator()()
	{
		represSCC.clear();
		represSCC.resize(G.V(), -1);
		Graph Gtransposed(G.V(), G.directed());
		transpose<Edge, Graph>(G, Gtransposed);
		Proc proc(G.V());
		Proc proc_rev(Gtransposed.V());
		BFS<Edge, Proc, Graph_List<Edge> > bfs(G, proc);
		BFS<Edge, Proc, Graph_List<Edge> > bfs_rev(Gtransposed, proc_rev);
		for(int i = 0; i < G.V(); i++)
			if(represSCC[i] == -1)
			{
				bfs(i);
				bfs_rev(i);
				for(int j = 0; j < G.V(); j++)
					if(proc.visited[j] && proc_rev.visited[j])
						represSCC[j] = i;
			}
	}
};
}
#endif