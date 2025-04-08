 #include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int id;
    int duration;
    vector<int> edges;
};

vector<Node> graph;
vector<int> indegree;
vector<int> earliestStart;
vector<int> latestStart;

void calculateInDegree() {
    for (const auto& node : graph) {
        for (const auto& edge : node.edges) {
            indegree[edge]++;
        }
    }
}

void calculateEarliestStart() {
    queue<int> q;
    for (int i = 0; i < indegree.size(); i++) {
        if (indegree[i] == 0) {
            q.push(i);
            earliestStart[i] = 0;
        }
    }

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (const auto& edge : graph[current].edges) {
            if (earliestStart[edge] < earliestStart[current] + graph[current].duration) {
                earliestStart[edge] = earliestStart[current] + graph[current].duration;
            }

            indegree[edge]--;
            if (indegree[edge] == 0) {
                q.push(edge);
            }
        }
    }
}

void calculateLatestStart() {
    int lastNode = graph.size() - 1;
    latestStart[lastNode] = earliestStart[lastNode];

    for (int i = lastNode - 1; i >= 0; i--) {
        for (const auto& edge : graph[i].edges) {
            if (latestStart[edge] - graph[i].duration < latestStart[i]) {
                latestStart[i] = latestStart[edge] - graph[i].duration;
            }
        }
    }
}

int main() {
    ifstream inputFile("graph.txt"); // Metin dosyasý olarak verilen grafiði oku
    int numNodes;
    inputFile >> numNodes;

    graph.resize(numNodes);
    indegree.resize(numNodes);
    earliestStart.resize(numNodes);
    latestStart.resize(numNodes);

    for (int i = 0; i < numNodes; i++) {
        int id, duration, numEdges;
        inputFile >> id >> duration >> numEdges;

        graph[i].id = id;
        graph[i].duration = duration;

        for (int j = 0; j < numEdges; j++) {
            int edge;
            inputFile >> edge;
            graph[i].edges.push_back(edge);
        }
    }

    inputFile.close();

    calculateInDegree();
    calculateEarliestStart();
    calculateLatestStart();

    // 1. Ev projesinin Mümkün olan en kýsa tamamlanma süresi (SPCT)
    int SPCT = earliestStart.back() + graph.back().duration;
    cout << "1. Ev projesinin Mumkun olan en kisa tamamlanma suresi (SPCT): " << SPCT << " gun" << endl;

    // 2. Her bir faaliyet için en erken baþlangýç zamaný (EST)
    cout << "2. Her bir faaliyet icin en erken baslangic zamani (EST):" << endl;
    for (int i = 0; i < numNodes; i++) {
        cout << "Faaliyet " << graph[i].id << ": " << earliestStart[i] << " gun" << endl;
    }

    // 3. Her bir faaliyet için en son baþlangýç zamaný (LST)
    cout << "3. Her bir faaliyet için en son baslangic zamani (LST):" << endl;
    for (int i = 0; i < numNodes; i++) {
        int LST = latestStart[i] - graph[i].duration;
        cout << "Faaliyet " << graph[i].id << ": " << LST << " gun" << endl;
    }

    // 4. Projenin kritik yol nedir?
    cout << "4. Projenin kritik yolunun faaliyetleri:" << endl;
    for (int i = 0; i < numNodes; i++) {
        if (earliestStart[i] == latestStart[i]) {
            cout << "Faaliyet " << graph[i].id << endl;
        }
    }

    return 0;
}
