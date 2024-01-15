
#pragma	once

#include	<iostream>
#include	"mv_dcll.hpp"

//	Class Declaration
template<typename T_VER>
class Vertex;

template<typename T_EDGE>
class Edge;

template <typename T_EDGE>
class 	Edge
{
private:
	size_t	m_weight;
	Vertex<T_EDGE>*	m_vertex;

	Edge(Vertex<T_EDGE>* vertex, size_t weight) : m_vertex(vertex), m_weight(weight) 
	{}

	~Edge()
	{}

	template<typename T_EDGE>
	friend class MV_IGraph;

	template<typename T_EDGE>
	friend class MV_Graph;

	template<typename T_GRAPH>
	friend class MV_DFS;

	template<typename T_GRAPH>
	friend class MV_BFS;
	
	template<typename T_EDGE>
	friend std::ostream& operator << (std::ostream& out, MV_Graph<T_EDGE>& graph);
};

template<typename T_VER>
class 	Vertex
{
private:
	//	Data Member
	T_VER	m_data;

	//	List of edges
	MV_DCLL<Edge<T_VER>*> m_edges;

	Vertex(T_VER data) : m_data(data)
	{
	}

	template<typename T_EDGE>
	friend class MV_IGraph;

	template<typename T_EDGE>
	friend class MV_Graph;

	template<typename T_GRAPH>
	friend class MV_DFS;

	template<typename T_GRAPH>
	friend class MV_BFS;

	template<typename T_EDGE>
	friend std::ostream& operator << (std::ostream& out, MV_Graph<T_EDGE>& graph);
};

template <typename T_GRAPH>
class MV_IGraph
{
protected:
	MV_DCLL<Vertex<T_GRAPH>*> m_vertices;

	Vertex<T_GRAPH>* LocateVertex(T_GRAPH new_data)
	{
		// Code
		for( auto itr = m_vertices.begin();
			itr != m_vertices.end();
			++itr)
		{
			if( (*itr)->m_data == new_data)
				return(*itr);
		}

		return(NULL);
	}

	template<typename T_GRAPH>
	friend class MV_DFS;

	template<typename T_GRAPH>
	friend class MV_BFS;
};

#include "mv_graph_algorithms.hpp"

