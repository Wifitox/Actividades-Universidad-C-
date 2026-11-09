#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class EdgeListGraph {
    struct Edge { int from, to; };

    int n;
    vector<Edge> edges;

public:
    explicit EdgeListGraph(int n) {
        this->n = n;
    }

    void addEdge(int u, int v) {
        edges.push_back({u, v});
    }

    bool hasEdge(int u, int v) const {
        for (const Edge& e : edges)
            if (e.from == u && e.to == v) return true;
        return false;
    }

    vector<int> neighbors(int u) const {
        vector<int> res;
        for (const Edge& e : edges)
            if (e.from == u) res.push_back(e.to);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    EdgeListGraph g(n);

    for (int i = 0; i < q; ++i) {
        string cmd;
        cin >> cmd;
        if (cmd == "ADD") {
            int u, v;
            cin >> u >> v;
            g.addEdge(u, v);
        } else if (cmd == "HAS") {
            int u, v;
            cin >> u >> v;
            cout << (g.hasEdge(u, v) ? "true" : "false") << '\n';
        } else { // NEIGHBORS
            int u;
            cin >> u;
            vector<int> out = g.neighbors(u);
            if (out.empty()) cout << "(empty)\n";
            else {
                for (int i = 0; i < (int)out.size(); ++i) cout << (i ? " " : "") << out[i];
                cout << '\n';
            }
        }
    }
    return 0;
}
