/**
 * @Time : 2024/7/31-4:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1675D
 */
 /*
  * 按题意模拟即可
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, p[N], degree[N], marked[N];

void path(vector<int>& nodes, int s) {
    if(s == -1 || marked[s]) return;
    marked[s] = 1;
    nodes.push_back(s);
    path(nodes, p[s]);
}

void solve() {
    vector<int> arr;
    for(int i = 1; i <= n; i++) {
        if(degree[i] == 0) arr.push_back(i);
    }
    cout << arr.size() << "\n";
    for(int s : arr) {
        vector<int> nodes;
        path(nodes, s);
        reverse(nodes.begin(), nodes.end());
        cout << nodes.size() << "\n";
        for(int node : nodes)
            cout << node << " ";
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        fill(degree, degree + n + 1, 0), fill(marked, marked + n + 1, 0);
        for(int i = 1; i <= n; i++) {
            cin >> p[i];
            if(p[i] != i) degree[p[i]]++;
            if(p[i] == i) p[i] = -1;
        }
        solve();
    }
};