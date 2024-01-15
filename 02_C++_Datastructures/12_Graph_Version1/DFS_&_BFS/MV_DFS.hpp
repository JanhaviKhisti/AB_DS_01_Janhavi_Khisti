
#pragma	once

#include	"mv_dcll.hpp"
#include	"mv_stack.hpp"
#include	"mv_igraph.hpp"

template<typename T_DFS>
class MV_DFS
{
public:
	
	// GRAPH TRAVERSAL MEMBER FUNCTIONS

	class Visited
	{
	private:
		Vertex<T_DFS>* m_vertex;
		bool	m_visited;

		Visited(Vertex<T_DFS>* vertex) : m_vertex(vertex), m_visited(false)
		{
		}

		friend void MV_DFS::DepthFirstSearchTraversal(MV_IGraph<T_DFS>&, T_DFS source);

		friend Vertex<T_DFS>* MV_DFS::GetNonVisitedVertex(MV_DCLL<Visited*>&, MV_DCLL<Edge<T_DFS>*>&);
	};

	void DepthFirstSearchTraversal(MV_IGraph<T_DFS>& graph)
	{
		// Code
		for(auto vitr = graph.m_vertices.begin();
			vitr != graph.m_vertices.end();
			++vitr)
		{
			DepthFirstSearchTraversal(graph, (*vitr)->m_data );
		}
	}

	void DepthFirstSearchTraversal(MV_IGraph<T_DFS>& graph, T_DFS source)
	{
		// Code
		Vertex<T_DFS>* source_vertex = graph.LocateVertex(source);

		if( NULL == source_vertex )
		{
			std::cerr << "ERROR: Source not found." << std::endl;
			std::cout << std::endl;
			return;
		}

		MV_DCLL<Visited*>	dfs_vertices_list;
		MV_Stack<Vertex<T_DFS>*> stack;

		//	Create a list of all vertices and mark them unvisited
		for(auto vitr = graph.m_vertices.begin();
			vitr != graph.m_vertices.end();
			++vitr )
		{
			dfs_vertices_list.InsertBack( new Visited((*vitr)) );
		}

		std::cout << "Depth First Search Traversal:"<< std::endl;
		std::cout << "{START}->";
		//	Push The Source Vertex To Stack
		stack.Push(source_vertex);
		std::cout << "{"<< source_vertex->m_data << "}->";
		//	Mark The Source Vertex as Visited
		for(auto vitr = dfs_vertices_list.begin();
			vitr != dfs_vertices_list.end();
			++vitr )
		{
			if( (*vitr)->m_vertex->m_data == source_vertex->m_data )
				(*vitr)->m_visited = true;
		}

		while(1)	// This Loop Runs till a vertex is still not visited
		{
			//	Here We Do The DEPTH FIRST SEARCH
			while(stack.Size())
			{
				source_vertex = stack.Peek();

				// Check for non visited adjacent vertex 
				Vertex<T_DFS>* adjacent_vertex = GetNonVisitedVertex(dfs_vertices_list, source_vertex->m_edges);

				if( adjacent_vertex )
				{
					stack.Push(adjacent_vertex);
					std::cout << "{"<< adjacent_vertex->m_data << "}->";
				}
				else
				{
					stack.Pop();
				}
			}

			for(auto vitr = dfs_vertices_list.begin();
				vitr != dfs_vertices_list.end();
				++vitr )
			{
				if(!((*vitr)->m_visited))
				{
					source_vertex = (*vitr)->m_vertex;
					(*vitr)->m_visited = true;
					stack.Push(source_vertex);
					std::cout << "{"<< source_vertex->m_data << "}->";
				}
			}

			if( !(stack.Size()) )
				break;
		}

		std::cout << "{END}" << std::endl;

		//	Delete all the dynamically allocated Visited objects
		for(auto vitr = dfs_vertices_list.begin();
			vitr != dfs_vertices_list.end();
			++vitr )
		{
			delete((*vitr));
		}
		std::cout << std::endl;
	}

	Vertex<T_DFS>* GetNonVisitedVertex(MV_DCLL<Visited*>& visited_list, MV_DCLL<Edge<T_DFS>*>& edges)
	{
		// Code
		for(auto eitr = edges.begin();
			eitr != edges.end();
			++eitr )
		{
			for( auto vitr = visited_list.begin();
				vitr != visited_list.end();
				++vitr )
			{
				if( ((*eitr)->m_vertex->m_data == (*vitr)->m_vertex->m_data) && !((*vitr)->m_visited))
				{
					(*vitr)->m_visited = true;
					return((*eitr)->m_vertex);
				}
			}
		}
		return(nullptr);
	}

};

