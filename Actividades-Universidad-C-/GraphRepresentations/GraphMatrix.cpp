#include <iostream>
#include <string>
#include <vector>
using namespace std;

class MatrixGraph {                    
    int n;
    vector<vector<bool>> adj;          
public:
    explicit MatrixGraph(int n) : n{n}, adj(n + 1, vector<bool>(n + 1, false)) {}

    void addEdge(int u, int v) { adj[u][v] = true; }

    bool hasEdge(int u, int v) const { return adj[u][v]; }

    vector<int> neighbors(int u) const {
        vector<int> out;
        for (int v = 1; v <= n; ++v)
            if (adj[u][v]) out.push_back(v);
        return out;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    MatrixGraph g(n);

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
            vector<int> out = g.neighbors(u);
            if (out.empty()) {
                cout << "(empty)\n";
            } else {
                for (int j = 0; j < (int)out.size(); ++j) {
                    cout << (j ? " " : "") << out[j];
                }
                cout << '\n';
            }
        }
    }
    return 0;
}
