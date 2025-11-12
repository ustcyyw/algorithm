/**
 * @Time : 2025/3/13-10:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF150B 1600 并查集
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, m, k;

struct UF {
    vector<int> id;
    UF(int total) {
        for(int i = 0; i <= total; i++)
            id.push_back(i);
    }

    int find(int p) {
        return id[p] == p ? p : id[p] = find(id[p]);
    }

    void connect(int p, int q) {
        p = find(p), q = find(q);
        if(p == q) return;
        id[p] = q;
    }
};

ll qPow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

void solve() {
    UF uf(n);
    for(int i = 1; i + k - 1 <= n; i++) {
        for(int lo = i, hi = i + k - 1; lo < hi; lo++, hi--)
            uf.connect(lo, hi);
    }
    set<int> st;
    for(int i = 1; i <= n; i++)
        st.insert(uf.find(i));
    cout << qPow(m, st.size());
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> m >> k;
        solve();
    }
}