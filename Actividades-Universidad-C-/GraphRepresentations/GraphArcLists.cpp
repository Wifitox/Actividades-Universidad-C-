#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ArcListGraph {
    struct Arc {
        int from, to;
        Arc* nextOut;   
        Arc* nextIn;    
    };
    struct Vertex {
        Arc* out = nullptr;
        Arc* in = nullptr;
    };

    vector<Vertex> g;

public:
    explicit ArcListGraph(int n) : g(n + 1) {}

    ~ArcListGraph() {
        for (int i = 0; i < (int)g.size(); ++i) {
            Arc* a = g[i].out;
            while (a != nullptr) {
                Arc* next = a->nextOut;
                delete a;
                a = next;
            }
        }
    }

    void addEdge(int u, int v) {
        if (hasEdge(u, v)) return;
        Arc* a = new Arc{u, v, g[u].out, g[v].in};
        g[u].out = a;
        g[v].in = a;
    }

    bool hasEdge(int u, int v) const {
        for (Arc* a = g[u].out; a != nullptr; a = a->nextOut)
            if (a->to == v) return true;
        return false;
    }

    vector<int> outNeighbors(int u) const {
        vector<int> res;
        for (Arc* a = g[u].out; a != nullptr; a = a->nextOut)
            res.push_back(a->to);
        return res;
    }

    vector<int> inNeighbors(int v) const {
        vector<int> res;
        for (Arc* a = g[v].in; a != nullptr; a = a->nextIn)
            res.push_back(a->from);
        return res;
    }
};


static void printVec(const vector<int>& a) {
    if (a.empty()) {
        cout << "(empty)\n";
        return;
    }
    for (int i = 0; i < (int)a.size(); ++i) cout << (i ? " " : "") << a[i];
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    ArcListGraph g(n);

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
        } else if (cmd == "OUT") {
            int u;
            cin >> u;
            printVec(g.outNeighbors(u));
        } else { // IN
            int v;
            cin >> v;
            printVec(g.inNeighbors(v));
        }
    }
    return 0;
}
