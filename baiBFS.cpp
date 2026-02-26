#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <iomanip>
using namespace std;
map<string, vector<string>> adj;
map<string, bool> visited;
map<string, string> parent;
int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, m;
    string start, goal;
    fin >> n >> m >> start >> goal;
    for (int i = 0; i < m; i++) {
        string u, v;
        fin >> u >> v;
        adj[u].push_back(v);
    }
    queue<string> q;
    q.push(start);
    visited[start] = true;
    fout << left<< setw(12) << "Expanded" << setw(20) << "Adjacency" << setw(20) << "Queue"<< endl;
    while (!q.empty()) {
        string u = q.front();
        q.pop();
        fout << left << setw(12) << u;
        string adjList = "";
        for (auto v : adj[u]) {
            adjList += v + " ";
        }
        fout << setw(20) << adjList;
        for (auto v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
        queue<string> temp = q;
        string queueState = "";
        while (!temp.empty()) {
            queueState += temp.front() + " ";
            temp.pop();
        }
        fout << setw(20) << queueState << endl;

        if (u == goal)
            break;
    }
    vector<string> path;
    string current = goal;
    if (!visited[goal]) {
        fout << "\nKhong tim thay duong di.\n";
    } else {
        while (current != start) {
            path.push_back(current);
            current = parent[current];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        fout << "\nDuong di tim duoc:\n";
        for (int i = 0; i < path.size(); i++) {
            fout << path[i];
            if (i != path.size() - 1)
                fout << " -> ";
        }
        fout << endl;
    }
    fin.close();
    fout.close();
    return 0;
}