/**
 * @Time : 2025/4/28-10:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1009D 1700 构造 数学 数论 暴力枚举
 */
/*
  * m至少为n-1，否则根本不可能连通，m最多为(n - 1) * n / 2，否则一定有重边
  * 在满足上述条件的情况下讨论
  * 连通性可以用1和其它结点来保证，然后就是补足边数到达m
  * 通过暴力计算可以发现，从1-1000内的数 就能找到超过1e5组互质的数
  * 在这个数据范围内 直接暴力找质数对即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, mod = 998244353;
ll T, n, m;
vector<vector<int>> arr;

bool check() {
    if(m < n - 1 || m > (n - 1) * n / 2) return false;
    for(int i = 2; i <= n; i++)
        arr.push_back({1, i});
    for(int i = 2; i <= n && arr.size() < m; i++) {
        for(int j = i + 1; j <= n && arr.size() < m; j++)
            if(gcd(i, j) == 1) arr.push_back({i, j});
    }
    return arr.size() == m;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    if(check()) {
        cout << "Possible\n";
        for(auto p : arr)
            cout << p[0] << " " << p[1] << "\n";
    } else cout << "Impossible\n";
}