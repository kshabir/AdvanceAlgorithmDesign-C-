#include <iostream>
#include <vector>
#include <string>
#include <memory>

/*
The factory method (based on user input) returns a unique pointer either dfs or bfs. That return pointer is stored in searcher variable, which can ultimately process run based on this returned pointer.
Factod Method: "Create a product using related compoenents" --> One object is created per iteration
Abstract family: "Create families of related products" --> More than one object (to create families later) created per iteration
*/

class Graph {
public:
    Graph(int v) : V(v), adj(v) {}
    void addEdge(int v, int w) { adj[v].push_back(w); }
    int getVertexCount() const { return V; }
    const std::vector<std::vector<int>>& getAdjList() const { return adj; }

private:
    int V;
    std::vector<std::vector<int>> adj;
};

class GraphSearch {
public:
    virtual ~GraphSearch() = default;
    virtual std::vector<int> run(const Graph& graph, int start) = 0;
};

class DFSSearch : public GraphSearch {
public:
    std::vector<int> run(const Graph& graph, int start) override {
        std::cout << "Performing DFS" << std::endl;
        // DFS implementation would go here
        return std::vector<int>{start}; // Placeholder
    }
};

class BFSSearch : public GraphSearch {
public:
    std::vector<int> run(const Graph& graph, int start) override {
        std::cout << "Performing BFS" << std::endl;
        // BFS implementation would go here
        return std::vector<int>{start}; // Placeholder
    }
};

class SearchFactory {
public:
    static std::unique_ptr<GraphSearch> createSearcher(const std::string& method) {
        if (method == "DFS") return std::make_unique<DFSSearch>();
        if (method == "BFS") return std::make_unique<BFSSearch>();
        return nullptr;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    std::string searchMethod;
    std::cout << "Enter search method (DFS or BFS): ";
    std::cin >> searchMethod;

    //auto searcher = SearchFactory::createSearcher(searchMethod);
    std::unique_ptr<GraphSearch> searcher = SearchFactory::createSearcher(searchMethod);


    if (searcher) {
        std::vector<int> searchResult = searcher->run(g, 2);
        std::cout << "Search result: ";
        for (int v : searchResult) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Invalid search method" << std::endl;
    }

    return 0;
}
