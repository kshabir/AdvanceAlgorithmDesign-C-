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
      // the run signature need to be carefully selected. Either Static or singelton pattern to get an instance  
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
