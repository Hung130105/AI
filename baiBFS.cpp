#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <iomanip>
#include <sstream>
using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m;
    string start, goal;
    fin >> n >> m >> start >> goal;

    map<string, vector<string>> adj;
    for (int i = 0; i < m; i++) {
        string u, v;
        fin >> u >> v;
        adj[u].push_back(v);
    }

    // Sắp xếp danh sách kề theo thứ tự alphabet
    for (auto& entry : adj) {
        sort(entry.second.begin(), entry.second.end());
    }

    map<string, bool> visited;
    map<string, string> parent;
    queue<string> q;

    // In tiêu đề bảng bằng tiếng Việt theo yêu cầu đề
    fout << left
         << setw(14) << "Dinh xet"
         << setw(24) << "Dinh ke"
         << "Queue" << endl;
    fout << string(60, '-') << endl;

    // Trường hợp đặc biệt: start == goal
    if (start == goal) {
        fout << left << setw(14) << start
             << setw(24) << ""
             << start << endl;
        fout << string(60, '-') << endl;
        fout << "\nDuong di tim duoc:\n" << start << endl;
        fin.close();
        fout.close();
        return 0;
    }

    q.push(start);
    visited[start] = true;
    bool found = false;

    while (!q.empty()) {
        string u = q.front();
        q.pop();

        // Lấy danh sách đỉnh kề
        string adjList = "";
        for (auto& v : adj[u]) {
            adjList += v + " ";
        }
        if (!adjList.empty()) adjList.pop_back(); // bỏ dấu cách cuối

        // Thêm các đỉnh kề chưa visited vào queue
        for (auto& v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }

        // Lấy trạng thái queue hiện tại (sau khi đã thêm con)
        string queueState = "";
        if (u == goal) {
            // Đã tìm thấy goal, không in queue nữa
            queueState = "[Found!]";
            found = true;
        } else {
            queue<string> temp = q;
            while (!temp.empty()) {
                queueState += temp.front();
                temp.pop();
                if (!temp.empty()) queueState += " ";
            }
            if (queueState.empty()) queueState = "(rong)";
        }

        // In dòng bảng
        fout << left
             << setw(14) << u
             << setw(24) << adjList
             << queueState << endl;

        if (u == goal) {
            found = true;
            break;
        }
    }

    fout << string(60, '-') << endl;

    // In đường đi
    if (!found || !visited[goal]) {
        fout << "\nKhong tim thay duong di tu " << start << " den " << goal << ".\n";
    } else {
        vector<string> path;
        string current = goal;
        while (current != start) {
            path.push_back(current);
            current = parent[current];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        fout << "\nDuong di tu " << start << " den " << goal << ":\n";
        for (size_t i = 0; i < path.size(); i++) {
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