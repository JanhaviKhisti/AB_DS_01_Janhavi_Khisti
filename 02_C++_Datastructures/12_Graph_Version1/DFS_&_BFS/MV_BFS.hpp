
#pragma	once

#include	"mv_dcll.hpp"
#include	"mv_dequeue.hpp"
#include	"mv_igraph.hpp"

template<typename T_BFS>
class MV_BFS
{
public:

	// GRAPH TRAVERSAL MEMBER FUNCTIONS

	class Visited
	{
	private:
		Vertex<T_BFS>* m_vertex;
		bool	m_visited;

		Visited(Vertex<T_BFS>* vertex) : m_vertex(vertex), m_visited(false)
		{
		}

		friend void MV_BFS::BreadthFirstSearchTraversal(MV_IGraph<T_BFS>&, T_BFS source);

		friend Vertex<T_BFS>* MV_BFS::GetNonVisitedVertex(MV_DCLL<Visited*>&, MV_DCLL<Edge<T_BFS>*>&);
	};

	void	BreadthFirstSearchTraversal(MV_IGraph<T_BFS>& graph)
	{
		// Code
		for(auto vitr = graph.m_vertices.begin();
			vitr != graph.m_vertices.end();
			++vitr)
		{
			BreadthFirstSearchTraversal(graph, (*vitr)->m_data );
		}
	}

	void	BreadthFirstSearchTraversal(MV_IGraph<T_BFS>& graph, T_BFS source)
	{
		// Code
		Vertex<T_BFS>* source_vertex = graph.LocateVertex(source);

		if( NULL == source_vertex )
		{
			std::cerr << "ERROR: Source not found." << std::endl;
			std::cout << std::endl;
			return;
		}

		MV_DCLL<Visited*>	bfs_vertices_list;
		MV_DeQueue<Vertex<T_BFS>*> dequeue;

		//	Create a list of all vertices and mark them unvisited
		for(auto vitr = graph.m_vertices.begin();
			vitr != graph.m_vertices.end();
			++vitr )
		{
			bfs_vertices_list.InsertBack( new Visited((*vitr)) );
		}

		std::cout << "Breadth First Search Traversal:"<< std::endl;
		std::cout << "{START}->";
		//	PushBack The Source Vertex To Queue
		dequeue.PushBack(source_vertex);
		//	Mark The Source Vertex as Visited
		for(auto vitr = bfs_vertices_list.begin();
			vitr != bfs_vertices_list.end();
			++vitr )
		{
			if( (*vitr)->m_vertex->m_data == source_vertex->m_data )
				(*vitr)->m_visited = true;
		}

		while(1)	// This Loop Runs till a vertex is still not visited
		{
			//	HERE WE DO THE BREADTH FIRST SEARCH
			while(dequeue.Size())
			{
				source_vertex = dequeue.GetFront();

				// Check for non visited adjacent vertex 
				Vertex<T_BFS>* adjacent_vertex = NULL;
				while( 1 )
				{
					adjacent_vertex = GetNonVisitedVertex(bfs_vertices_list, source_vertex->m_edges);
					
					if( !adjacent_vertex )
						break;

					dequeue.PushBack(adjacent_vertex);
				}

				source_vertex = dequeue.PopFront();
				std::cout << "{"<< source_vertex->m_data << "}->";
			}

			for(auto vitr = bfs_vertices_list.begin();
				vitr != bfs_vertices_list.end();
				++vitr )
			{
				if(!((*vitr)->m_visited))
				{
					source_vertex = (*vitr)->m_vertex;
					(*vitr)->m_visited = true;
					dequeue.PushBack(source_vertex);
				}
			}

			if( !(dequeue.Size()) )
				break;
		}

		std::cout << "{END}" << std::endl;

		//	Delete all the dynamically allocated Visited objects
		for(auto vitr = bfs_vertices_list.begin();
			vitr != bfs_vertices_list.end();
			++vitr )
		{
			delete((*vitr));
		}
		std::cout << std::endl;
	}

	Vertex<T_BFS>* GetNonVisitedVertex(MV_DCLL<Visited*>& visited_list, MV_DCLL<Edge<T_BFS>*>& edges)
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
					//std::cout << "-->" << (*vitr)->m_vertex->m_data << std::endl;
					(*vitr)->m_visited = true;
					return((*eitr)->m_vertex);
				}
			}
		}
		return(NULL);
	}

};
