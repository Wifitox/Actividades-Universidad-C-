#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ArcListGraph {
    // Define Vertex/Arc and store them.
public:
    explicit ArcListGraph(int n) {
        // your code here
    }

    void addEdge(int u, int v) {
        // your code here
    }

    bool hasEdge(int u, int v) const {
        // your code here
        return false;
    }

    vector<int> outNeighbors(int u) const {
        // your code here
        return {};
    }

    vector<int> inNeighbors(int v) const {
        // your code here
        return {};
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
