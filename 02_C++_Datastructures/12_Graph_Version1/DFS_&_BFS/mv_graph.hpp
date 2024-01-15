
#pragma	once

#include	<iostream>
#include	"mv_dcll.hpp"
#include	"mv_stack.hpp"
#include	"mv_igraph.hpp"

//	Class Type Definitions
enum class TYPE
{
	NONE = 0,
	DIRECTED = 1,
	UNDIRECTED
};

template<typename T_GRAPH>
class MV_Graph : public MV_IGraph<T_GRAPH>
{
private:
	TYPE type;

	long long LocateVertexIndex(T_GRAPH new_data)
	{
		// Code
		long long index = 0;
		for( auto itr = m_vertices.begin();
			itr != m_vertices.end();
			++itr, ++index)
		{
			if( (*itr)->m_data == new_data)
			{
				return(index);
			}
		}

		return(-1);
	}

	void AddGenericEdge(Vertex<T_GRAPH>* v1, Vertex<T_GRAPH>* v2, size_t weight)
	{
		// Code
		for(auto eitr = v1->m_edges.begin();
			eitr != v1->m_edges.end();
			++eitr )
		{
			if((*eitr)->m_vertex->m_data == v2->m_data)
			{
				std::cerr << "ERROR : Edge already Prenset" << std::endl;
				return;
			}
		}

		v1->m_edges.InsertBack( new Edge<T_GRAPH>(v2, weight) );
	}

	long long GenericRemoveEdge(Vertex<T_GRAPH>* v1, Vertex<T_GRAPH>* v2)
	{
		// Code
		long long to_return_weight = 0 ;

		//	Remove v2 from v1's edge
		for( int le = 0; le < v1->m_edges.Size(); ++le )
		{
			if(v1->m_edges[le]->m_vertex->m_data == v2->m_data)
			{
				auto edge = v1->m_edges.RemoveAt(le);
				to_return_weight = edge->m_weight;
				delete(edge);
				break;
			}
		}

		//	Remove v1 from v2's edge
		for( int le = 0; le < v2->m_edges.Size(); ++le )
		{
			if(v2->m_edges[le]->m_vertex->m_data == v1->m_data)
			{
				auto edge = v2->m_edges.RemoveAt(le);
				to_return_weight = edge->m_weight;
				delete(edge);
				break;
			}
		}

		return(to_return_weight);
	}

	T_GRAPH GenericRemoveVertex(Vertex<T_GRAPH>* vertex)
	{
		// Code
		while( vertex->m_edges.Size() )
		{
			Vertex<T_GRAPH>* v2 = vertex->m_edges[0]->m_vertex;
			GenericRemoveEdge(vertex, v2);
		}

		m_vertices.RemoveAt( LocateVertexIndex(vertex->m_data) );

		T_GRAPH to_return_vertex = vertex->m_data;
		delete(vertex);

		return(to_return_vertex);
	}

public:
	MV_Graph() : type(TYPE::UNDIRECTED)
	{
	}

	MV_Graph(TYPE type) : type(type)
	{
	}

	// GRAPH INSERTION MEMBER FUNCTION 

	ret_t	AddVertex(T_GRAPH data)
	{
		// Code
		Vertex<T_GRAPH>* vertex = LocateVertex(data);
		if( vertex )
		{
			std::cerr << "ERROR: Vertex already existing." << std::endl;
			return(FAILURE);
		}

		m_vertices.InsertBack( new Vertex<T_GRAPH>(data) );
		return(SUCCESS); 
	}

	ret_t	AddEdge(T_GRAPH vdata1, T_GRAPH vdata2, size_t weight)
	{
		// Code
		Vertex<T_GRAPH>* vertex1 = LocateVertex(vdata1);
		Vertex<T_GRAPH>* vertex2 = LocateVertex(vdata2);
	
		if( !vertex1 )
		{
			AddVertex(vdata1);
			vertex1 = LocateVertex(vdata1);
		}
	
		if( !vertex2 )
		{
			AddVertex(vdata2);
			vertex2 = LocateVertex(vdata2);
		}

		if( TYPE::DIRECTED == type )
		{
			AddGenericEdge(vertex1, vertex2, weight);
		}
		else if( TYPE::UNDIRECTED == type )
		{
			AddGenericEdge(vertex1, vertex2, weight);
			AddGenericEdge(vertex2, vertex1, weight);
		}

		return(SUCCESS);
	}

	// GRAPH REMOVAL MEMBER FUNCTIONS 

	long long RemoveEdge(T_GRAPH vdata1, T_GRAPH vdata2)
	{
		// Code
		Vertex<T_GRAPH>* vertex1 = LocateVertex(vdata1);
		Vertex<T_GRAPH>* vertex2 = LocateVertex(vdata2);
	
		if( !vertex1 || !vertex2 )
		{
			std::cerr << "ERROR: This edge does not exist." << std::endl;
			return(0);
		}

		return( GenericRemoveEdge(vertex1, vertex2) );
	}

	long long RemoveVertex(T_GRAPH vdata)
	{
		// Code
		Vertex<T_GRAPH>* vertex = LocateVertex(vdata);
	
		if( !vertex )
		{
			std::cerr << "ERROR: The vertex does not exists ." << std::endl;
			return(0);
		}

		return( GenericRemoveVertex(vertex) );
	}

	void DepthFirstSearchTraversal()
	{
		MV_DFS<T_GRAPH> dfs;

		dfs.DepthFirstSearchTraversal((*this));
	}

	void DepthFirstSearchTraversal(T_GRAPH single_source)
	{
		MV_DFS<T_GRAPH> dfs;

		dfs.DepthFirstSearchTraversal((*this), single_source);
	}

	void BreadthFirstSearchTraversal()
	{
		MV_BFS<T_GRAPH> bfs;

		bfs.BreadthFirstSearchTraversal((*this));
	}

	void BreadthFirstSearchTraversal(T_GRAPH single_source)
	{
		MV_BFS<T_GRAPH> bfs;

		bfs.BreadthFirstSearchTraversal((*this), single_source);
	}

	template<typename T_GRAPH>
	friend std::ostream& operator << (std::ostream& out, MV_Graph<T_GRAPH>& graph);
};

template<typename T_DATA>
std::ostream& operator << (std::ostream& out, MV_Graph<T_DATA>& graph)
{
	for(auto vitr = graph.m_vertices.begin();
		vitr != graph.m_vertices.end();
		++vitr )
	{
		out << (*vitr)->m_data << ":->";
		
		for( auto eitr = (*vitr)->m_edges.begin();
			 eitr != (*vitr)->m_edges.end();
			 ++eitr)
		{
			out << "{" << (*eitr)->m_vertex->m_data << "|" << (*eitr)->m_weight << "}-> ";
		}

		out << std::endl;
	}

	return(out);

}

