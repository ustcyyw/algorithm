/**
 * @Time : 2025/1/28-9:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF25D 1900 并查集
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, mod = 998244353;
int T, n;

struct UF {
    vector<int> id;
    UF(int total) {
        for(int i = 0; i <= total; i++)
            id.push_back(i);
    }

    int find(int p) {
        return id[p] == p ? p : id[p] = find(id[p]);
    }

    bool connect(int p, int q) {
        p = find(p), q = find(q);
        if(p == q) return true;
        id[p] = q;
        return false;
    }
};

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        UF uf(n);
        vector<vector<int>> edges;
        for(int i = 1, a, b; i < n; i++) {
            cin >> a >> b;
            if(uf.connect(a, b)) edges.push_back({a, b});
        }
        set<int> st;
        vector<int> nodes;
        for(int i = 1; i <= n; i++) {
            int p = uf.find(i);
            if(!st.count(p)) st.insert(p), nodes.push_back(p);
        }
        cout << edges.size() << "\n";
        for(int i = 0; i < edges.size(); i++) {
            cout << edges[i][0] << " " << edges[i][1] << " ";
            cout << nodes[i] << " " << nodes[i + 1] << "\n";
        }
    }
};