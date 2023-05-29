#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

void parallelDFS(const std::vector<std::vector<int> >& graph, int startVertex, std::vector<bool>& visited) {
    std::stack<int> dfsStack;
    dfsStack.push(startVertex);
    
    while (!dfsStack.empty()) {
        int currentVertex = dfsStack.top();
        dfsStack.pop();
        
        if (!visited[currentVertex]) {
            std::cout << "Visiting vertex: " << currentVertex << std::endl;
            visited[currentVertex] = true;
            
            #pragma omp parallel for num_threads(4)
            for (int i = 0; i < graph[currentVertex].size(); ++i) {
                int neighborVertex = graph[currentVertex][i];
                if (!visited[neighborVertex]) {
                    #pragma omp critical
                    dfsStack.push(neighborVertex);
                }
            }
        }
    }
}

int main() {
    int numVertices;
    std::cout << "Enter the number of vertices: ";
    std::cin >> numVertices;
    
    std::vector<std::vector<int> > graph(numVertices);
     
    std::cout << "Enter the adjacency list for each vertex:\n";
    for (int i = 0; i < numVertices; ++i) {
        int numNeighbors;
        std::cout << "Enter the number of neighbors for vertex " << i << ": ";
        std::cin >> numNeighbors;
        
        std::cout << "Enter the neighbors for vertex " << i << ": ";
        for (int j = 0; j < numNeighbors; ++j) {
            int neighborVertex;
            std::cin >> neighborVertex;
            graph[i].push_back(neighborVertex);
        }
    }
    
    int startVertex;
    std::cout << "Enter the start vertex: ";
    std::cin >> startVertex;
    
    std::vector<bool> visited(numVertices, false);
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelDFS(graph, startVertex, visited);
        }
    }
    
    return 0;
}
