/**
 * @Time : 2025/2/23-4:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF792D 1900 dfs 找规律
 */
 /*
  * 照着给的示意图
  * 首先确定这是一颗完全的平衡bst
  * 然后找结点的与儿子结点 父亲结点 同一层结点之间值、层级的关系 按照规律dfs
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5, M = 400;
ll n, q, root, p[64], rl;
unordered_map<ll, int> rp;
string s;

int init = []() -> int {
    p[0] = 1, rp[1] = 0;
    for(int i = 1; i < 64; i++) {
        p[i] = p[i - 1] * 2;
        rp[p[i]] = i;
    }
    return 0;
}();
// 找到指定值对应的层级
int dfs1(ll v, ll target, int layer) {
    if(v == target) return layer;
    ll d = p[layer - 2];
    if(target > v) return dfs1(v + d, target, layer - 1);
    else return dfs1(v - d, target, layer - 1);
}

ll dfs2(ll v, int idx, int layer) {
    if(idx == s.size()) return v;
    char c = s[idx];
    if(c == 'U') {
        if(layer == rl) return dfs2(v, idx + 1, layer);
        else {
            ll first = p[layer - 1], d = first * 2;
            ll rank = (v - first) / d + 1; // 计算当前结点在该层排第几
            ll add = rank % 2 == 1 ? p[layer - 1] : -p[layer - 1];
            return dfs2(v + add, idx + 1, layer + 1);
        }
    } else {
        if(layer == 1) return dfs2(v, idx + 1, layer);
        ll nl = layer - 1, add = p[layer - 2];
        if(c == 'L') return dfs2(v - add, idx + 1, nl);
        else return dfs2(v + add, idx + 1, nl);
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n >> q;
    root = (n + 1) / 2, rl = rp[n + 1];
    for(ll i = 1, v; i <= q; i++) {
        cin >> v >> s;
        int cl = dfs1(root, v, rl);
        cout << dfs2(v, 0, cl) << "\n";
    }
};