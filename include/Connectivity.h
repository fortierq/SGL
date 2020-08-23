/*!
* \file Connectivity.h
* \author Quentin Fortier
*  Connectivity algorithms
*/

#ifndef CONNECT_H
#define CONNECT_H

#include <vector>
#include <queue>
#include <set>
#include <assert.h>
#include "Structures.h"
#include "Search.h"
#include "Flow.h"
#include <stdlib.h>    
#include <time.h>      
#include "IO.h"

namespace sgl
{
	template<class Edge = Edge_Base, class Graph = Graph_List<Edge> > 
	class Splitting
	{
	public: 
		static int f(int a, int b) { return a >= b ? a-1 : a; }
		// Complete splitting at v. G_split has G.V() - 1 vertices
		static void split(const Graph &G, Graph &G_split1, Graph &G_split2, int v)
		{
			// Trouver les edges concernés
			Edge *e1, *e2, *e_1, *e_2;
			e1 = e2 = e_1 = e_2 = NULL;
			Graph::iterator_all it(G);
			for(Edge *e = it.beg(); !it.end(); e = it.nxt())
			{
				if(e->w() == v)
				{
					if(e1 == NULL) e1 = e;
					else e2 = e;
				}
				else if(e->v() == v)
				{
					if(e_1 == NULL) e_1 = e;
					else e_2 = e;
				}
				else
				{
					G_split1.insert(new Edge(f(e->v(), v), f(e->w(), v)));
					G_split2.insert(new Edge(f(e->v(), v), f(e->w(), v)));
				}
			}
			G_split1.insert(new Edge(f(e1->v(), v), f(e_1->w(), v)));
			G_split1.insert(new Edge(f(e2->v(), v), f(e_2->w(), v)));
			G_split2.insert(new Edge(f(e1->v(), v), f(e_2->w(), v)));
			G_split2.insert(new Edge(f(e2->v(), v), f(e_1->w(), v)));
		}
	};


	template<class Edge = Edge_Base, class Graph = Graph_List<Edge> > 
	class Connectivity
	{
	private:
		const Graph &G;

		class AvoidVertex : public Proc_Base<Edge>
		{
			int avoid;
		public:
			inline int get_target() { return target; }
			void set_avoid(int t) { avoid = t; }

			AvoidVertex(int V, int avoid) : Proc_Base<Edge>(V), avoid(avoid) { }

			inline bool trait(int v) { return false; }

			bool toVisit(Edge *e, int toVertex)
			{ 
				if(!tPred.isolated(toVertex) || toVertex == avoid)
					return false;
				tPred.insert(e, toVertex);
				return true; 
			}
		};

	public:
		Connectivity(const Graph &G): G(G) { }

		bool isConnected(int forbidden = -1)
		{
			AvoidVertex proc(G.V(), forbidden);
			DFS<Edge, AvoidVertex, Graph> dfs(G, proc);
			for(int v = 0; v < G.V(); v++)
			{
				if(v == forbidden) continue;
				dfs(v);
				for(int w = 0; w < G.V(); w++)
				{
					if(w == v || w == forbidden)
						continue;
					if(proc.tPred.isolated(w))
					{
						cout<<w<<" non accessible depuis "<<v<<" si on supprime "<<forbidden<<endl;
						return false; // w n'est pas accessible
					}
				}
			}
			return true;
		}

		bool is2VertexConnected()
		{
			for(int v = 0; v < G.V(); v++)
				if(!isConnected(v))
					return false;
			return true;
		}

		int vertex_connectivity()
		{
			Graph_List<Edge_Flow<int> > G_(2*G.V(), false); // on double les sommets
			Graph_List<Edge>::iterator_all it(G);
			for(Edge *e = it.beg(); !it.end(); e = it.nxt())
				G_.insert(new Edge_Flow<>(G.V() + e->v(), e->w(), G_.V()*G_.V()));
			for(int i = 0; i < G.V(); i++)
				G_.insert(new Edge_Flow<>(i, G.V() + i, 1));
	
			int min_flow = -1;
			for(int s = G.V(); s < G_.V(); s++)
				for(int t = 0; t < G.V(); t++)
				{
					if(s == t) continue;
					Graph_List<Edge_Flow<int> >::iterator_all it(G_);
					for(Edge_Flow<int> *e = it.beg(); !it.end(); e = it.nxt())
						e->set_flow(0);

					//IO<Edge_Flow<int>, Graph_List<Edge_Flow<int> >>::show_capR(G_);
					NoNullCap<> noNull(G_.V(), t); 
					Fulkerson<int, Edge_Flow<> > ful(G_, noNull, s, t);
					ful(0);
					int flow = ful.get_outflow();
					//IO<Edge_Flow<int>, Graph_List<Edge_Flow<int> >>::show_flow(G_);
					if(min_flow == -1 || min_flow > flow)
						min_flow = flow;
					/*if(flow < 3)
						cout<<s<<"-"<<t<<endl;*/
				}
			return min_flow;
		}

		int edge_connectivity()
		{
			Graph_List<Edge_Flow<int> > G_(G.V(), false); // non orienté
			Graph_List<Edge>::iterator_all it(G);
			for(Edge *e = it.beg(); !it.end(); e = it.nxt())
				G_.insert(new Edge_Flow<>(e->v(), e->w(), 1));

			int min_flow = -1;
			for(int s = 0; s < G_.V(); s++)
				for(int t = 0; t < G_.V(); t++)
				{
					if(s == t) continue;
					Graph_List<Edge_Flow<int> >::iterator_all it(G_);
					for(Edge_Flow<int> *e = it.beg(); !it.end(); e = it.nxt())
						e->set_flow(0);

					NoNullCap<> noNull(G_.V(), t); 
					Fulkerson<int, Edge_Flow<> > ful(G_, noNull, s, t);
					ful(0);
					int flow = ful.get_outflow();
					//IO<Edge_Flow<int>, Graph_List<Edge_Flow<int> >>::show_flow(G_);
					if(min_flow == -1 || min_flow > flow)
						min_flow = flow;
					//cout<<s<<"-"<<t<<" flow: "<<flow<<endl;
					/*	if(flow < 3)
					{
					Cut_Vertices<> cut(G_);
					cut(1);
					cout<<"Edges in the computed min cut:"<<endl;
					for(std::list<Edge_Flow<>*>::iterator it = cut.cut.begin(); it != cut.cut.end(); ++it)
					cout<<(*it)->v()<<" "<<(*it)->w()<<endl;
					system("pause");
					}*/	
				}

				return min_flow;
		}

	};
}

#endif
