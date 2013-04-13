#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cstdio>
using namespace std;

class Graph {
public:
    Graph(int n) {
        W = vector<vector<int> >(n, vector<int>(n));
        N = n;
    }
    void addEdge(int u, int v, int weight) {
        W[u][v] = W[v][u] = weight;
    }
    pair<int, vector<int> > minimumCut() {
        // heads[i]: i番目のグループを代表するノードのindex
        // members[i]: i番目のグループに含まれるノードのindexの集合
        vector<int> heads(N);
        vector<vector<int> > members(N); 
        for (int i=0; i<N; i++) {
            heads[i] = i;
            members[i].push_back(i);
        }

        int best_cut = 1000000000;
        vector<int> best_members;
        for (int n = N; n > 1; n--) {
            // 最大隣接順序の計算
            vector<int> sum(n);
            int u, v, w;
            for (int k = 0; k < n; k++) {
                u = v;
                v = max_element(sum.begin(), sum.end()) - sum.begin();
                w = sum[v];
                sum[v] = -1;
                for (int i = 0; i < n; i++)
                    if (sum[i] >= 0)
                        sum[i] += W[heads[v]][heads[i]];
            }
            // 最小カットの更新チェック
            if (best_cut > w) {
                best_cut = w;
                best_members = members[v];
            }
            // 縮退 (頂点vを頂点uにマージする)
            for (int i = 0; i < n; i++) {
                W[heads[i]][heads[u]] += W[heads[i]][heads[v]];
                W[heads[u]][heads[i]] += W[heads[v]][heads[i]];
            }
            members[u].insert(members[u].begin(), members[v].begin(), members[v].end());
            heads.erase(heads.begin() + v);
            members.erase(members.begin() + v);
        }
        return make_pair(best_cut, best_members); 
    }
private:
    vector<vector<int> > W;
    int N;
};

int main() {
    // read input
    vector<string> spiceA, spiceB;
    string a, b;
    vector<string> spices;
    while (cin >> a >> b) {
        spiceA.push_back(a);
        spiceB.push_back(b);
        spices.push_back(a);
        spices.push_back(b);
    }

    // construct map for spices
    sort(spices.begin(), spices.end());
    spices.erase(unique(spices.begin(), spices.end()), spices.end());
    map<string, int> idx;
    for (int i = 0; i < spices.size(); i++)
        idx[spices[i]] = i;

    // solve problem by finding minimum-cut
    Graph G(spices.size());
    for (int i = 0; i < spiceA.size(); i++) {
        G.addEdge(idx[spiceA[i]], idx[spiceB[i]], 1);
    }
    pair<int, vector<int> > result = G.minimumCut();

    // make output text
    vector<bool> group(spices.size(), false);
    vector<int> members = result.second;
    for (int i = 0; i < members.size(); i++)
        group[members[i]] = true;
    vector<int> points(2, 0);
    for (int i = 0; i < spiceA.size(); i++)
        if (group[idx[spiceA[i]]] == group[idx[spiceB[i]]]) {
            int gIndex = group[idx[spiceA[i]]] ? 1 : 0;
            points[gIndex]++;
        }

    printf("Minimum Cut: %d\n", result.first);

    printf("Groups0: %d\n", points[0]);
    for (int i = 0; i < spices.size(); i++)
        if (group[i] == false)
            cout << spices[i] << " ";
    cout << endl;

    printf("Groups1: %d\n", points[1]);
    for (int i = 0; i < spices.size(); i++)
        if (group[i] == true)
            cout << spices[i] << " ";
    cout << endl;
}
