#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

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
    Graph graph;
    ifstream file("koduc.txt"); // Metin dosyas�n� oku

    if (!file) {
        cout << "Dosya okunamad�." << endl;
        return 0;
    }

    string line;
    while (getline(file, line)) {
        if (line == "D���mler (Nodes):") {
            while (getline(file, line) && !line.empty()) {
                char label = line[0];
                int duration;
                stringstream ss(line.substr(2));
                ss >> duration;
                ActivityNode* node = new ActivityNode(label, duration);
                graph.addNode(node);
            }
        }
        else if (line == "Kenarlar (Edges):") {
            while (getline(file, line) && !line.empty()) {
                char dependentLabel = line[0];
                char dependencyLabel = line[2];
                ActivityNode* dependent = nullptr;
                ActivityNode* dependency = nullptr;
                for (ActivityNode* node : graph.nodes) {
                    if (node->label == dependentLabel) {
                        dependent = node;
                    }
                    if (node->label == dependencyLabel) {
                        dependency = node;
                    }
                }
                if (dependent && dependency) {
                    graph.addDependency(dependent, dependency);
                }
            }
        }
    }

    file.close();

    // Kritik yolu bulma
    graph.findCriticalPath();

    // Sonu�lar� g�r�nt�leme
    cout << "En k�sa tamamlanma s�resi (SPCT): " << graph.nodes.back()->earliestStartTime + graph.nodes.back()->duration << endl;
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
        if (node->earliestStartTime + node->duration == graph.nodes.back()->earliestStartTime + graph.nodes.back()->duration) {
            cout << node->label << " ";
        }
    }
    cout << graph.nodes.back()->label << endl;

    return 0;
}

