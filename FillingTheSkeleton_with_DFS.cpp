#include <iostream>
#include <vector>
#include <stack>
#include <string>

class Graph 
{
public:
    Graph(int v) : V(v), adj(v) {}
    void addEdge(int v, int w) { adj[v].push_back(w); }
    int getVertexCount() const { return V; }
    const std::vector<std::vector<int>>& getAdjList() const { return adj; }

private:
    int V;
    std::vector<std::vector<int>> adj;
};

class GraphSearch 
{
public:
    static std::vector<int>* process(Graph* graph, int startNode, const std::string& method) {
        GraphSearch* searcher = createSearcher(method);
        if (!searcher) return nullptr;
        
        std::vector<int>* result = searcher->run(graph, startNode);
        delete searcher;
        return result;
    }

protected:
    virtual std::vector<int>* run(Graph* graph, int start) = 0;

private:
    static GraphSearch* createSearcher(const std::string& method);
};

class DFSSearch : public GraphSearch {
protected:
    std::vector<int>* run(Graph* graph, int start) override 
    {
        std::cout << "Performing DFS" << std::endl;
        // DFS implementation would go here
        auto result = new std::vector<int>();
        
        // place the whole logic here
        std::vector<bool> visited(graph->getVertexCount(), false);
        std::stack<int> stk;
        
        stk.push(start);
        
        while(!stk.empty())
        {
            int currentNode = stk.top();
            stk.pop();
            
            if (!visited[currentNode])
            {
                result->push_back(currentNode);
                visited[currentNode] = true;
                
                // find adjacent nodes and push them into stack along flagging
                const auto& neighbors = graph->getAdjList()[currentNode];
                for(const auto& neighbor : neighbors)
                {
                    if(!visited[neighbor]) stk.push(neighbor);
                }
                
            }
            
        }
        return result;
    }
};

class BFSSearch : public GraphSearch {
protected:
    std::vector<int>* run(Graph* graph, int start) override {
        std::cout << "Performing BFS" << std::endl;
        // BFS implementation would go here
        return new std::vector<int>{start}; // Placeholder
    }
};

GraphSearch* GraphSearch::createSearcher(const std::string& method) {
    if (method == "DFS") return new DFSSearch();
    if (method == "BFS") return new BFSSearch();
    return nullptr;
}

int main() {
    Graph* g = new Graph(4);
    g->addEdge(0, 1);
    g->addEdge(0, 2);
    g->addEdge(1, 2);
    g->addEdge(2, 0);
    g->addEdge(2, 3);
    g->addEdge(3, 3);

    std::string searchMethod;
    std::cout << "Enter search method (DFS or BFS): ";
    std::cin >> searchMethod;

    std::vector<int>* searchResult = GraphSearch::process(g, 2, searchMethod);

    if (searchResult) {
        std::cout << "Search result: ";
        for (int v : *searchResult) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
        delete searchResult;
    } else {
        std::cout << "Invalid search method" << std::endl;
    }

    delete g;
    return 0;
}
