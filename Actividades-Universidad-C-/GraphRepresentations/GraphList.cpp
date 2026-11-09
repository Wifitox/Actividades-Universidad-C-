#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ListGraph {
    vector<vector<int>> adj;           
public:
    explicit ListGraph(int n) : adj(n + 1) {}


    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool hasEdge(int u, int v) const {
        for (int elem : adj[u])
            if (elem == v) return true;
        return false;
    }

    const vector<int>& neighbors(int u) const {
        return adj[u];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    ListGraph g(n);

    for (int i = 0; i < q; ++i) {
        string command;
        cin >> command;

        if (command == "ADD") {
            int u, v;
            cin >> u >> v;
            g.addEdge(u, v);
        } else if (command == "HAS") {
            int u, v;
            cin >> u >> v;
            cout << (g.hasEdge(u, v) ? "true" : "false") << '\n';
        } else { // NEIGHBORS
            int u;
            cin >> u;
            const vector<int>& out = g.neighbors(u);
            if (out.empty()) {
                cout << "(empty)\n";
            } else {
                for (int j = 0; j < static_cast<int>(out.size()); ++j) {
                    cout << (j == 0 ? "" : " ") << out[j];
                }
                cout << '\n';
            }
        }
    }
    return 0;
}
