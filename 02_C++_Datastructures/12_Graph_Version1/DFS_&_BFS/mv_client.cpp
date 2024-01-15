
#include   <iostream>
#include   <ctime>

#include    "mv_graph.hpp"

MV_Graph<long long> llgraph;

int main(void)
{

    for( long long le = 1; le <= 5; ++le )
    {
        llgraph.AddVertex(le * 10);
    }

    srand(time(0));

    long long edges_count = rand() % 50;

    // for( long long le = 0; le < edges_count ; ++le)
    // {
    //     long long v1 = (rand() % 10 + 1 ) * 10; 
    //     long long v2 = (rand() % 10 + 1 ) * 10; 
    //     long long weight = rand() % 500 + 1; 
    //     llgraph.AddEdge(v1, v2, weight);
    // }

    /*llgraph.AddEdge(10, 20, 5);
      llgraph.AddEdge(20, 30, 5);
      llgraph.AddEdge(30, 10, 5);
      llgraph.AddEdge(30, 40, 5);
      llgraph.AddEdge(50, 10, 5);
      llgraph.AddEdge(50, 20, 5);
      llgraph.AddEdge(50, 40, 5);
      llgraph.AddEdge(50, 40, 5);
    */

    std::cout << "After Insertion:" << std::endl;
    std::cout << "Graph:" << std::endl;
    std::cout << llgraph << std::endl;

    llgraph.RemoveEdge(50, 40);

    std::cout << "After Remove Edge:" << std::endl;
    std::cout << "Graph:" << std::endl;
    std::cout << llgraph << std::endl;

    std::cout << "DFS For All Source:" << std::endl;
    llgraph.DepthFirstSearchTraversal(); // All Vertices as Source

    /*std::cout << "DFS For Single Source:" << std::endl;
    llgraph.DepthFirstSearchTraversal(10); // Single Source*/

    llgraph.RemoveVertex(30);

    std::cout << "After Remove Vertex:" << std::endl;
    std::cout << "Graph:" << std::endl;
    std::cout << llgraph << std::endl;

    std::cout << "DFS For All Source:" << std::endl;
    llgraph.DepthFirstSearchTraversal(); // All Vertices as Source

    std::cout << "BFS For All Source:" << std::endl;
    llgraph.BreadthFirstSearchTraversal(); // All Vertices as Source

    std::cout << "DFS For Single Source:" << std::endl;
    llgraph.DepthFirstSearchTraversal(10); // Single Source

    std::cout << "BFS For Single Source:" << std::endl;
    llgraph.BreadthFirstSearchTraversal(10); // Single Source

    exit(EXIT_SUCCESS);

}

