#include <iostream>
#include <string>
#include <vector>
using namespace std;

class MatrixGraph {
    // Add the data members you need.
public:
    explicit MatrixGraph(int n) {
        // your code here
    }

    void addEdge(int u, int v) {
        // your code here
    }

    bool hasEdge(int u, int v) const {
        // your code here
        return false;
    }

    vector<int> neighbors(int u) const {
        // your code here
        return {};
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
