/*!
 * \file IO.h
 *  Income / outcome algorithms
 */

#ifndef IO_H
#define IO_H

#include <iostream>
#include "Structures.h"

namespace sgl
{
	/*! Income / outcome static class */
	template<class Edge = Edge_Base, class Graph = Graph_List<Edge> > class IO
	{
	public:
		/*! Show the edges of G */
		static void show(const Graph& G)
		{
			for (int v = 0; v < G.V(); v++)
			{
				std::cout << v << " : ";
				typename Graph::iterator it(G, v);
				for (Edge* e = it.beg(); !it.end(); e = it.nxt())
					if (e)
						std::cout << *e << " ; ";
				std::cout << "\n";
			}
		}
		/*! Show the flow of G
		\param G A network */
		static void show_flow(const Graph& G)
		{
			for (int v = 0; v < G.V(); v++)
			{
				std::cout << v << " : ";
				typename Graph::iterator it(G, v);
				for (Edge* e = it.beg(); !it.end(); e = it.nxt())
					if (e)
					{
						/*if(e->flow() == max_val<)
							std::cout<<e->v()<<" -- "<<"infty"<<" --> " <<e->w();
						else */
						if (e->flow())
							std::cout << e->v() << " -- " << e->flow() << " / " << e->cap() << " --> " << e->w();
						std::cout << " ; ";
					}
				std::cout << "\n";
			}
		}
		///*! Show the capacities of G
		//\param G A network */
		//static void show_cap(const Graph &G)
		//{
		//	for(int v = 0; v < G.V(); v++)
		//	{
		//		std::cout<<v<<" : ";
		//		typename Graph::iterator it(G, v);
		//		for(Edge *e = it.beg(); !it.end(); e = it.nxt())
		//			if(e)
		//			{
		//				/*if(e->cap() == infty)
		//				os<<e->v()<<" -- "<<"infty"<<" --> " <<e->w();
		//				else */
		//				std::cout<<e->v()<<" -- "<<e->cap()<<" --> " <<e->w();
		//				std::cout<<" ; ";
		//			}
		//			std::cout<<"\n";
		//	}
		//}
		/*! Show the residual capacities of G
		\param G A network */
		static void show_capR(const Graph& G)
		{
			for (int v = 0; v < G.V(); v++)
			{
				std::cout << v << " : ";
				typename Graph::iterator it(G, v);
				for (Edge* e = it.beg(); !it.end(); e = it.nxt())
					if (e)
					{
						/*if(e->cap() == infty)
						os<<e->v()<<" -- "<<"infty"<<" --> " <<e->w();
						else */
						std::cout << e->v() << " -- " << e->capRto(e->other(v)) << " --> " << e->w();
						std::cout << " ; ";
					}
				std::cout << "\n";
			}
		}
	};

	//#include <fstream>
	//void write_network(const Graph_List<Edge_Flow<> > &G)
	//{
	//	ofstream outfile ("graph.txt",ios::out | ios::binary);
	//	Graph_List<Edge_Flow<> >::iterator_all it(G);
	//	char *buffer = new char[100000];
	//	sprintf(buffer,e "Graph_List<Edge_Flow<> > G(%d);\n", G.V());
	//	outfile.write(buffer, strlen(buffer));
	//	delete buffer;
	//	for(Edge_Flow<> *e = it.beg(); !it.end(); e = it.nxt())
	//	{
	//		char *buffer = new char[100000];
	//		sprintf(buffer, "G.insert(new Edge_Flow<>(%d,%d,%d));\n", e->v(), e->w(), e->cap());
	//		outfile.write(buffer, strlen(buffer));
	//		delete buffer;
	//	}
	//}
}

#endif
