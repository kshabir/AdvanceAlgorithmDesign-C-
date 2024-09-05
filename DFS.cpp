#include <iostream>
#include <vector>
#include <stack>
#include <memory>

// Graph class
class Graph 
{
    // Data: Nodes/Vertices, adjacency list
    private:
    int Vertices;
    std::vector<std::vector<int>> adj;
    
    public:
    // constructor and addEdge()
    Graph(int v) : Vertices(v), adj(v) {}
    
    void addEdge(int v, int w)
    {
        // Undirected graph
        adj[v].push_back(w);
        adj[w].push_back(v);
    }
    
    // getters
   const std::vector<std::vector<int>>& getAdjacency() const
   {
       return adj;
   }
    
    int getVerticesCount() const
    {
        return Vertices;
    }

};

// DFS class (API/Processing Unit)
class DFS 
{
    public:
    static std::vector<int>* process(Graph* graph, int startNode)
    {
      // the run signature need to be carefully selected. Either Static or singelton pattern to get an instance*  
      return run(graph, startNode);
    }
    
    private:
    static std::vector<int>* run(Graph* graph, int startNode)
    {
        auto result = new std::vector<int>();
        
        // place the whole logic here
        std::vector<bool> visited(graph->getVerticesCount(), false);
        std::stack<int> stk;
        
        stk.push(startNode);
        
        while(!stk.empty())
        {
            int currentNode = stk.top();
            stk.pop();
            
            if (!visited[currentNode])
            {
                result->push_back(currentNode);
                visited[currentNode] = true;
                
                // find adjacent nodes and push them into stack along flagging
                const auto& neighbors = graph->getAdjacency()[currentNode];
                for(const auto& neighbor : neighbors)
                {
                    if(!visited[neighbor]) stk.push(neighbor);
                }
                
            }
            
        }
        return result;
        
    }
    

};

// Customer code (main)
int main() {
    // Create a graph
    Graph* g = new Graph(4);
    g->addEdge(0, 1);
    g->addEdge(0, 2);
    g->addEdge(1, 2);
    g->addEdge(2, 0);
    g->addEdge(2, 3);
    g->addEdge(3, 3);

    // Use DFS API to traverse the graph
    std::cout << "Depth First Traversal (starting from vertex 2): ";
    //DFS dfs;
    std::vector<int>* dfsResult = DFS::process(g, 2);

    // Print the result
    for (int v : *dfsResult) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    // Clean up
    delete g;
    delete dfsResult;

    return 0;
}

/*
* Both approaches have their merits and drawbacks. Let's compare them:

Marking run as static:
Pros:

Simpler implementation
No need for instance management
Straightforward to understand and use
No overhead of creating or managing instances
Cons:

Cannot maintain state between calls (if needed in the future)
Less flexible if you need to extend or modify behavior
Harder to mock or replace in unit tests
Using an instance (Singleton or similar pattern):
Pros:

Allows for potential stateful operations
More flexible for future extensions (e.g., adding instance variables)
Easier to mock or replace in unit tests
Can implement interfaces or be part of inheritance hierarchies
Cons:

Slightly more complex implementation
Small overhead of instance management
Can be misused as a global state holder
In this specific case, for a simple DFS implementation, marking run as static is likely the better choice. Here's why:

Simplicity: The DFS algorithm doesn't inherently require maintaining state between calls.
Performance: Static methods have a tiny performance advantage (though negligible in most cases).
Clear Intent: It clearly communicates that the method doesn't depend on instance state
*/
