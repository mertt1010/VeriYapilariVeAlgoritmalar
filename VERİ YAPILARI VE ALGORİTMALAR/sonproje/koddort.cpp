#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Edge {
    int source;
    int destination;
    int weight;
    std::string activity;
};

class Graph {
private:
    int numVertices;
    std::vector<std::vector<Edge>> adjList;

public:
    Graph(int vertices) : numVertices(vertices) {
        adjList.resize(numVertices);
    }

    void addEdge(int source, int destination, int weight, const std::string& activity) {
        Edge edge{source, destination, weight, activity};
        adjList[source].push_back(edge);
    }

    void dfs(int vertex, std::vector<bool>& visited, std::vector<int>& completionTimes) {
        visited[vertex] = true;

        for (const Edge& edge : adjList[vertex]) {
            if (!visited[edge.destination]) {
                dfs(edge.destination, visited, completionTimes);
            }

            completionTimes[vertex] = std::max(completionTimes[vertex], completionTimes[edge.destination] + edge.weight);
        }
    }

    void calculateSPCT() {
        std::vector<bool> visited(numVertices, false);
        std::vector<int> completionTimes(numVertices, 0);

        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i]) {
                std::vector<bool> tempVisited(numVertices, false); // Temporary visited array for each iteration
                dfs(i, tempVisited, completionTimes);
            }
        }

        int spct = *std::max_element(completionTimes.begin(), completionTimes.end());
        std::cout << "Shortest Possible Completion Time (SPCT): " << spct << std::endl;
    }

    void calculateEST(std::vector<int>& completionTimes) {
        std::vector<int> est(numVertices, 0);

        for (int i = 0; i < numVertices; ++i) {
            for (const Edge& edge : adjList[i]) {
                est[edge.destination] = std::max(est[edge.destination], completionTimes[i] + edge.weight);
            }
        }

        std::cout << "Earliest Start Time (EST) for each activity:\n";
        for (int i = 0; i < numVertices; ++i) {
            for (const Edge& edge : adjList[i]) {
                std::cout << edge.activity << ": " << est[i] << std::endl;
            }
        }
    }

    void calculateLST(std::vector<int>& completionTimes) {
        std::vector<int> lst(numVertices, 0);
        int spct = *std::max_element(completionTimes.begin(), completionTimes.end());

        for (int i = numVertices - 1; i >= 0; --i) {
            for (const Edge& edge : adjList[i]) {
                lst[i] = std::min(lst[i] - edge.weight, lst[edge.destination]);
            }
        }

        std::cout << "Latest Start Time (LST) for each activity:\n";
        for (int i = 0; i < numVertices; ++i) {
            for (const Edge& edge : adjList[i]) {
                std::cout << edge.activity << ": " << spct - lst[i] << std::endl;
            }
        }
    }

    void calculateCriticalPath(std::vector<int>& completionTimes) {
        int spct = *std::max_element(completionTimes.begin(), completionTimes.end());
        std::cout << "Critical Path for the project:\n";

        for (int i = 0; i < numVertices; ++i) {
            for (const Edge& edge : adjList[i]) {
                if (completionTimes[i] + edge.weight == completionTimes[edge.destination]) {
                    std::cout << edge.activity << " -> ";
                }
            }
        }
        std::cout << "End\n";
    }
};

int main() {
    // Read graph information from a text file
    std::ifstream inputFile("koddort.txt");
    int numVertices;
    inputFile >> numVertices;

    Graph graph(numVertices);

    int source, destination, weight;
    std::string activity;

    while (inputFile >> source >> destination >> weight >> activity) {
        graph.addEdge(source, destination, weight, activity);
    }

    // Perform CPM calculations
    std::vector<int> completionTimes(numVertices, 0);
    graph.calculateSPCT();
    graph.calculateEST(completionTimes);
    graph.calculateLST(completionTimes);
    graph.calculateCriticalPath(completionTimes);

    return 0;
}

