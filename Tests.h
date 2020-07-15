/*!
 * \file Tests.h
 *  Tests on functions to compare performances
 */

#ifndef TESTS_H
#define TESTS_H

#include <time.h>
#include <iostream>
#include <assert.h>
#include <list>
#include "Structures.h"

namespace sgl
{
/*! Create a random graph of type Graph */
template<typename type_wt = int, class Edge = Edge_Base<type_wt>, class Graph = Graph_List<Edge> > class Rdm_Graph : public Graph
{
public:
	/*! \param V Number of vertices
	\param E Number of edges
	\param max_wt Maximum possible weight of an edge
	\param min_wt Minimum \b absolute possible weight of an edge 
	\param neg_wt Allow negative weights
	\param digraph Specify if the graph is directed */
	Rdm_Graph(int V = 4, int E = 2*V,  type_wt max_wt = 10, type_wt min_wt = 0, bool neg_wt = false, bool digraph = false) : 
	  Graph(V, digraph)
	{
		assert(V < RAND_MAX);
		for(int i = 0; i < E; i++)
		{
			int v = rand() % V, w = rand() % V;
			if(v != w)
			{
				type_wt wt = min_wt + (rand() % (max_wt - min_wt + 1)) * (rand() % (neg_wt+1) ? -1 : 1); 
				insert(new Edge(v, w, wt));
				insert(new Edge(w, v, wt)); // WARNING
			}
		}
	}
};

/*! \todo: Random Bipartite */
//template<typename type_wt = int, class Edge = Edge_Base<type_wt>, int V_ = 4, int E_ = 2*V_,  type_wt max_wt = 10, type_wt min_wt = 0, 
//	bool neg_wt = false, bool digraph_ = false, class Bipartite = Bipartite_list<Edge> >
//class Rdm_Bipartite : public Bipartite
//{
//public:
//	/// Génère un graphe aléatoire Bipartite à 2V sommets, E arêtes
//	/// max_wt : poids maximum des arêtes de poids positif
//	/// min_wt : poids minimum des arêtes de poids positif
//	/// min_wt doit être inférieur à max_wt
//	/// neg_wt : autorise des poids négatifs
//	/// digraph : crée un graphe orienté
//	Rdm_Bipartite() : Bipartite(2*V_, digraph_)
//	{
//		assert(V_ < RAND_MAX);
//		for(int i = 0; i < V_; i++)
//			this->X.push_back(i);
//		for(int i = V_; i < 2*V_; i++)
//			this->Y.push_back(i);
//		for(int i = 0; i < E_; i++)
//		{
//			int v = rand() % V_, w = V_ + rand() % V_;
//			type_wt wt = min_wt + (rand() % (max_wt - min_wt + 1)) * (rand() % (neg_wt+1) ? -1 : 1); 
//			insert(new Edge(v, w, wt));
//		}
//	}
//};


/*! Compare two minimum spanning tree algorithms
\see compare */
template<class MST1, class MST2> class Comp_MST
{
public:
	bool sameResult(const MST1 &st1, const MST2 &st2) 
	{ 
		int min1 = st1.get_min_MST(), min2 = st2.get_min_MST(); 
		if(min1 != min2)
			std::cout<<"Minimums: "<<min1<<" != "<<min2<<"\n";
		return min1 == min2;
	}
};
/*! Compare two shortest path algorithms
\see compare */
template<class SP1, class SP2> class Comp_SP
{
public:
	bool sameResult(const SP1 &sp1, const SP2 &sp2)
	{
		assert(sp1.dist.size() == sp2.dist.size());
		for(int i = 0; i < sp2.dist.size(); i++)
			if(sp1.dist[i] != sp2.dist[i])
				return false;
		return true;
	}
};
/*! Compare two max flow algorithms
\see compare_proc */
template<class Flow1, class Flow2> class Comp_Flow
{
public:
	bool sameResult(const Flow1 &flow1, const Flow2 &flow2) { return flow1.get_outflow() == flow2.get_outflow(); }
};

/*! Used by compare and compare_proc */
void show_results(int time_Fun1, int time_Fun2, int nDifferentResult, int max1, int max2)
{
	if(nDifferentResult)
		std::cout<<"WARNING : "<<nDifferentResult<<" different results!"<<"\n";
	else
		std::cout<<"All results were identicals"<<"\n";
	std::cout<<"Execution time:\n";
	std::cout<<"Fun1 : "<<time_Fun1<<"ms\tmax:"<<max1<<"ms"<<"\n";
	std::cout<<"Fun2 : "<<time_Fun2<<"ms\tmax:"<<max2<<"ms"<<"\n";
	std::cout<<"\n";
}

/*! Compare the results of two functions and their time executions
\param comp Functor with a member function bool sameResult(Fun1, Fun2) which is true iff the instances of Fun1 and Fun2 are considered equal 
\param nTests Number of tests 
\see compare_proc */
template<class Fun1, class Fun2, class Comp, class Graph_Generator> void compare(Comp &comp, int nTests)
{
	for(int i = 0; i < 40; i++) std::cout<<"-";
	std::cout<<"\n\tResults of the "<<nTests<<" tests :\n\n";
	int time_Fun1 = 0, time_Fun2 = 0, maxFun1 = 0, maxFun2 = 0;
	int nDifferentResult = 0;
	for(int i = 0; i < nTests; i++)
	{
		Graph_Generator G;
		int t1 = clock();
		Fun1 f1(G);
		f1();
		int t2 = clock();
		Fun2 f2(G);
		f2();
		int t3 = clock();
		time_Fun1 += (t2 - t1);
		time_Fun2 += (t3 - t2);
		maxFun1 = std::max(maxFun1, (t2 - t1));
		maxFun2 = std::max(maxFun2, (t3 - t2));
		if(!comp.sameResult(f1, f2))
			nDifferentResult++;
	}
	show_results(time_Fun1, time_Fun2, nDifferentResult, maxFun1, maxFun2);
	for(int i = 0; i < 40; i++) std::cout<<"-";
	std::cout<<"\n";
}
/*! Compare the results of two functions <b> with functor Proc </b> and their time executions
\param comp Functor with a member function bool sameResult(Fun1, Fun2) which is true iff the instances of Fun1 and Fun2 are considered equal 
\param nTests Number of tests 
\param proc1_ Functor to call for an instance of Fun1 ( ie Fun1 f1(G, proc1_) )
\param proc2_ Functor to call for an instance of Fun2 ( ie Fun1 f2(G, proc2_) ) 
\see compare */
template<class Fun1, class Fun2, class Comp, class Graph_Generator, int nTests, class Proc1, class Proc2> 
void compare_proc(Comp &comp, int nTests, Proc1 &proc1_, Proc2 &proc2_)
{
	for(int i = 0; i < 40; i++) std::cout<<"-";
	std::cout<<"\n\tResults of the "<<nTests<<" tests :\n\n";
	int time_Fun1 = 0, time_Fun2 = 0, maxFun1 = 0, maxFun2 = 0;
	int nDifferentResult = 0;
	for(int i = 0; i < nTests; i++)
	{
		Proc1 proc1 = proc1_;
		Proc2 proc2 = proc2_;
		Graph_Generator G;
		int t1 = clock();
		Fun1 f1(G, proc1);
		f1();
		int t2 = clock();
		Fun2 f2(G, proc2);
		f2();
		int t3 = clock();
		time_Fun1 += (t2 - t1);
		time_Fun2 += (t3 - t2);
		maxFun1 = std::max(maxFun1, (t2 - t1));
		maxFun2 = std::max(maxFun2, (t3 - t2));
		if(!comp.sameResult(f1, f2))
			nDifferentResult++;
	}
	show_results(time_Fun1, time_Fun2, nDifferentResult, maxFun1, maxFun2);
	for(int i = 0; i < 40; i++) std::cout<<"-";
	std::cout<<"\n";
}
}
#endif