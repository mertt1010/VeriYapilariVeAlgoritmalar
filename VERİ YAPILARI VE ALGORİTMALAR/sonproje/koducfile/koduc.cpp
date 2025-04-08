#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

// Aktivite düðümünü temsil eden sýnýf
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

// Grafik sýnýfý
class Graph {
public:
    vector<ActivityNode*> nodes;

    // Aktivite düðümü ekleme fonksiyonu
    void addNode(ActivityNode* node) {
        nodes.push_back(node);
    }

    // Baðýmlýlýk ekleme fonksiyonu
    void addDependency(ActivityNode* dependent, ActivityNode* dependency) {
        dependent->dependencies.push_back(dependency);
    }

    // Kritik yol bulma fonksiyonu
    void findCriticalPath() {
        // Topolojik sýralama için indeks hesaplama
        vector<int> indegree(nodes.size(), 0);
        for (ActivityNode* node : nodes) {
            for (ActivityNode* dependency : node->dependencies) {
                indegree[dependency->label - 'A']++;
            }
        }

        // Baþlangýç düðümünü bulma
        queue<ActivityNode*> q;
        for (ActivityNode* node : nodes) {
            if (indegree[node->label - 'A'] == 0) {
                q.push(node);
            }
        }

        // En erken baþlangýç zamanlarýný hesaplama
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

        // En geç baþlangýç zamanlarýný hesaplama
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
    ifstream file("koduc.txt"); // Metin dosyasýný oku

    if (!file) {
        cout << "Dosya okunamadý." << endl;
        return 0;
    }

    string line;
    while (getline(file, line)) {
        if (line == "Düðümler (Nodes):") {
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

    // Sonuçlarý görüntüleme
    cout << "En kýsa tamamlanma süresi (SPCT): " << graph.nodes.back()->earliestStartTime + graph.nodes.back()->duration << endl;
    cout << "Her bir faaliyet için en erken baþlangýç zamaný (EST):" << endl;
    for (ActivityNode* node : graph.nodes) {
        cout << "Activity " << node->label << ": " << node->earliestStartTime << endl;
    }
    cout << "Her bir faaliyet için en geç baþlangýç zamaný (LST):" << endl;
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

