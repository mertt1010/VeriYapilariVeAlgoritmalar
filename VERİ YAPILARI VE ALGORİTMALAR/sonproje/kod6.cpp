#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Graf� temsil eden s�n�f
class Graph {
public:
    int V;  // D���m say�s�
    vector<vector<pair<int, int>>> adj; // Kenarlar ve a��rl�klar i�in liste

    // Di�er fonksiyonlar...

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Kenar ekleme fonksiyonu
    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
    }

    // Maksimum yay�lan a�ac� (maximum spanning tree) bulma fonksiyonu
    void maximumSpanningTree(vector<int>& maxDist) {
        maxDist.assign(V, INT_MIN); // En uzak mesafeleri s�n�rlay�c� de�erle ba�latma

        priority_queue<pair<int, int>> pq; // �ncelik kuyru�u kullanarak a��rl�klar� s�ralama
        pq.push(make_pair(0, 0)); // Ba�lang�� d���m�

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

// Proje y�neticisi s�n�f�
class ProjectManager {
    int V; // D���m say�s�
    vector<int> spct; // M�mk�n olan en k�sa tamamlanma s�resi (SPCT)
    vector<int> est; // Her bir faaliyet i�in en erken ba�lang�� zaman� (EST)
    vector<int> lst; // Her bir faaliyet i�in en son ba�lang�� zaman� (LST)
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
        vector<int> maxDist; // En uzak mesafeleri depolamak i�in
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

    // Proje y�neticisinin sorular�n� yan�tlama fonksiyonu
    void answerQuestions() {
        cout << "Ev projesinin M�mk�n olan en k�sa tamamlanma s�resi (SPCT): " << spct[V - 1] << endl;
        cout << "Her bir faaliyet i�in en erken ba�lang�� zaman� (EST):" << endl;
        for (int i = 0; i < V; i++) {
            cout << "Activity " << i << ": " << est[i] << endl;
        }
        cout << "Her bir faaliyet i�in en son ba�lang�� zaman� (LST):" << endl;
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
    int V; // D���m say�s�
    cout << "Dugum sayisini girin: ";
    cin >> V;

    Graph graph(V);
    ProjectManager projectManager(V);

    // Dosyadan de�erleri oku
    ifstream input("graph.txt");
    for (int i = 0; i < V - 1; i++) {
        int u, v, weight;
        input >> u >> v >> weight;
        graph.addEdge(u, v, weight);
    }
    input.close();

    // Projenin kritik yolunu bulun
    projectManager.findCriticalPath(graph);

    // Sorular�n yan�tlar�n� g�r�nt�leyin
    projectManager.answerQuestions();

    return 0;
}

