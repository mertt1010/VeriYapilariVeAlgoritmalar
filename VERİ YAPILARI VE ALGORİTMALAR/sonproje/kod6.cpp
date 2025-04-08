#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Grafý temsil eden sýnýf
class Graph {
public:
    int V;  // Düðüm sayýsý
    vector<vector<pair<int, int>>> adj; // Kenarlar ve aðýrlýklar için liste

    // Diðer fonksiyonlar...

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Kenar ekleme fonksiyonu
    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
    }

    // Maksimum yayýlan aðacý (maximum spanning tree) bulma fonksiyonu
    void maximumSpanningTree(vector<int>& maxDist) {
        maxDist.assign(V, INT_MIN); // En uzak mesafeleri sýnýrlayýcý deðerle baþlatma

        priority_queue<pair<int, int>> pq; // Öncelik kuyruðu kullanarak aðýrlýklarý sýralama
        pq.push(make_pair(0, 0)); // Baþlangýç düðümü

        while (!pq.empty()) {
            int u = pq.top().second;
            int dist = pq.top().first;
            pq.pop();

            if (dist > maxDist[u]) {
                maxDist[u] = dist;

                for (auto& edge : adj[u]) {
                    int v = edge.first;
                    int weight = edge.second;
                    pq.push(make_pair(dist - weight, v));
                }
            }
        }
    }
};

// Proje yöneticisi sýnýfý
class ProjectManager {
    int V; // Düðüm sayýsý
    vector<int> spct; // Mümkün olan en kýsa tamamlanma süresi (SPCT)
    vector<int> est; // Her bir faaliyet için en erken baþlangýç zamaný (EST)
    vector<int> lst; // Her bir faaliyet için en son baþlangýç zamaný (LST)
    vector<int> critPath; // Projenin kritik yolu

public:
    ProjectManager(int V) {
        this->V = V;
        spct.assign(V, INT_MIN);
        est.assign(V, INT_MIN);
        lst.assign(V, INT_MAX);
    }

    // Projenin kritik yolunu bulma fonksiyonu
    void findCriticalPath(Graph& graph) {
        vector<int> maxDist; // En uzak mesafeleri depolamak için
        graph.maximumSpanningTree(maxDist);

        for (int u = 0; u < V; u++) {
            for (auto& edge : graph.adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (maxDist[u] - weight == maxDist[v]) {
                    critPath.push_back(u);
                    break;
                }
            }
        }
    }

    // Proje yöneticisinin sorularýný yanýtlama fonksiyonu
    void answerQuestions() {
        cout << "Ev projesinin Mümkün olan en kýsa tamamlanma süresi (SPCT): " << spct[V - 1] << endl;
        cout << "Her bir faaliyet için en erken baþlangýç zamaný (EST):" << endl;
        for (int i = 0; i < V; i++) {
            cout << "Activity " << i << ": " << est[i] << endl;
        }
        cout << "Her bir faaliyet için en son baþlangýç zamaný (LST):" << endl;
        for (int i = 0; i < V; i++) {
            cout << "Activity " << i << ": " << lst[i] << endl;
        }
        cout << "Projenin kritik yolu: ";
        for (int node : critPath) {
            cout << node << " ";
        }
        cout << V - 1 << endl;
    }
};

int main() {
    int V; // Düðüm sayýsý
    cout << "Dugum sayisini girin: ";
    cin >> V;

    Graph graph(V);
    ProjectManager projectManager(V);

    // Dosyadan deðerleri oku
    ifstream input("graph.txt");
    for (int i = 0; i < V - 1; i++) {
        int u, v, weight;
        input >> u >> v >> weight;
        graph.addEdge(u, v, weight);
    }
    input.close();

    // Projenin kritik yolunu bulun
    projectManager.findCriticalPath(graph);

    // Sorularýn yanýtlarýný görüntüleyin
    projectManager.answerQuestions();

    return 0;
}

