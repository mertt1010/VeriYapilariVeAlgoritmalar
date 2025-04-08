#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Aktivite d���m�n� temsil eden s�n�f
class ActivityNode {
public:
    char label;
    int duration;
    int earliestStartTime;
    int latestStartTime;
    vector<ActivityNode*> dependencies;

    ActivityNode(char label, int duration) {
        this->label = label;
        this->duration = duration;
        this->earliestStartTime = 0;
        this->latestStartTime = 0;
    }
};

// Grafik s�n�f�
class Graph {
public:
    vector<ActivityNode*> nodes;

    // Aktivite d���m� ekleme fonksiyonu
    void addNode(ActivityNode* node) {
        nodes.push_back(node);
    }

    // Ba��ml�l�k ekleme fonksiyonu
    void addDependency(ActivityNode* dependent, ActivityNode* dependency) {
        dependent->dependencies.push_back(dependency);
    }

    // Kritik yol bulma fonksiyonu
    void findCriticalPath() {
        // Topolojik s�ralama i�in indeks hesaplama
        vector<int> indegree(nodes.size(), 0);
        for (ActivityNode* node : nodes) {
            for (ActivityNode* dependency : node->dependencies) {
                indegree[dependency->label - 'A']++;
            }
        }

        // Ba�lang�� d���m�n� bulma
        queue<ActivityNode*> q;
        for (ActivityNode* node : nodes) {
            if (indegree[node->label - 'A'] == 0) {
                q.push(node);
            }
        }

        // En erken ba�lang�� zamanlar�n� hesaplama
        while (!q.empty()) {
            ActivityNode* current = q.front();
            q.pop();

            for (ActivityNode* dependency : current->dependencies) {
                indegree[dependency->label - 'A']--;
                dependency->earliestStartTime = max(dependency->earliestStartTime, current->earliestStartTime + current->duration);

                if (indegree[dependency->label - 'A'] == 0) {
                    q.push(dependency);
                }
            }
        }

        // En ge� ba�lang�� zamanlar�n� hesaplama
        int projectDuration = 0;
        for (ActivityNode* node : nodes) {
            projectDuration = max(projectDuration, node->earliestStartTime + node->duration);
        }

        for (ActivityNode* node : nodes) {
            node->latestStartTime = projectDuration - node->earliestStartTime - node->duration;
        }
    }
};

int main() {
    // Aktivite d���mlerini ve ba��ml�l�klar�n� olu�turma
    ActivityNode* A = new ActivityNode('A', 5);
    ActivityNode* B = new ActivityNode('B', 3);
    ActivityNode* C = new ActivityNode('C', 4);
    ActivityNode* D = new ActivityNode('D', 2);

    Graph graph;
    graph.addNode(A);
    graph.addNode(B);
    graph.addNode(C);
    graph.addNode(D);

    graph.addDependency(B, A);
    graph.addDependency(C, A);
    graph.addDependency(D, B);
    graph.addDependency(D, C);

    // Kritik yolu bulma
    graph.findCriticalPath();

    // Sonu�lar� g�r�nt�leme
    cout << "En k�sa tamamlanma s�resi (SPCT): " << D->earliestStartTime + D->duration << endl;
    cout << "Her bir faaliyet i�in en erken ba�lang�� zaman� (EST):" << endl;
    for (ActivityNode* node : graph.nodes) {
        cout << "Activity " << node->label << ": " << node->earliestStartTime << endl;
    }
    cout << "Her bir faaliyet i�in en ge� ba�lang�� zaman� (LST):" << endl;
    for (ActivityNode* node : graph.nodes) {
        cout << "Activity " << node->label << ": " << node->latestStartTime << endl;
    }
    cout << "Projenin kritik yolu: ";
    for (ActivityNode* node : graph.nodes) {
        if (node->earliestStartTime + node->duration == D->earliestStartTime + D->duration) {
            cout << node->label << " ";
        }
    }
    cout << D->label << endl;

    return 0;
}

