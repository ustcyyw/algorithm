/**
 * @Time : 2024/9/4-9:21 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1800E2
 */
 /*
  * 就是看哪些位置可以互相交换 找连通分量 可以用并查集
  * CF1800E1 easy版本代码一点不用改
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 2e5 + 5;
int T, n, k, id[N];
string s, t;

int find(int p) {
    return id[p] = id[p] == p ? p : find(id[p]);
}

void connect(int p, int q) {
    p = find(p), q = find(q);
    id[p] = q;
}

bool check() {
    map<int, map<char, int>> s_set, t_set;
    for(int i = 1; i <= n; i++) {
        int p = find(i);
        s_set[p][s[i]]++, t_set[p][t[i]]++;
    }
    for(auto& temp : s_set) {
        map<char, int>& s1 = temp.second, &s2 = t_set[temp.first];
        for(auto& p : s1) {
            if(s1[p.first] != s2[p.first])
                return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k >> s >> t;
        s = "." + s, t = "." + t;
        for(int i = 1; i <= n; i++)
            id[i] = i;
        for(int i = 1; i + k <= n; i++) {
            connect(i, i + k);
            if(i + k + 1 <= n) connect(i, i + k + 1);
        }
        cout << (check() ? "YES" : "NO") << "\n";
    }
};