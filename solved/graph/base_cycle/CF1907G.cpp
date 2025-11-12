/**
 * @Time : 2024/9/24-3:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1907G
 */
 /*
  * 基环树深林
  * 枝条的处理和 环的处理要分开
  * 并且应该先处理枝条
  * 可以画图观察规律
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, degree[N], con[N];
string s;
vector<int> ans;

void topol_bfs() {
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 0) queue.push(i);
    while (queue.size()) {
        int v = queue.front(), w = con[v]; queue.pop();
        if(s[v] == '1') {
            ans.push_back(v);
            s[w] = s[w] == '0' ? '1' : '0';
        }
        if(--degree[w] == 0) queue.push(w);
    }
}
// 会将开头第一个结点在结尾再放进去一次
void dfs(vector<vector<int>>& aux, int start, int v, int dis) {
    if(s[v] == '1') aux.push_back({v, dis});
    degree[v] = -1; // 可以标识已经处理过
    if(v == start && dis != 0) return;
    dfs(aux, start, con[v], dis + 1);
}
// 贪心 相邻的两个开着的灯最后要一起关闭
int cal(vector<vector<int>>& aux, int base) {
    int res = 0;
    for(int m = aux.size(), i = base; i < m - 1 + base && i + 1 < m; i += 2)
        res += aux[i + 1][1] - aux[i][1];
    return res;
}

void add(vector<vector<int>>& aux, int base) {
    for(int m = aux.size(), i = base; i < m - 1 + base && i + 1 < m; i += 2) {
        int v = aux[i][0], w = aux[i + 1][0];
        while(v != w) {
            ans.push_back(v);
            v = con[v];
        }
    }
}

bool solve() {
    topol_bfs();
    // 找到第一个开着的且在环中的灯
    for(int i = 1; i <= n; i++) {
        if(degree[i] > 0 && s[i] == '1') {
            vector<vector<int>> aux;
            dfs(aux, i, i, 0);
            // 开头结点放了两次 所以aux是偶数大小表明环中结点数量为奇数 没法都关灯
            if(aux.size() % 2 == 0) return false;
            int cnt1 = cal(aux, 0), cnt2 = cal(aux, 1);
            if(cnt1 < cnt2) add(aux, 0);
            else add(aux, 1);
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> s;
        s = '.' + s;
        ans = {}, fill(degree, degree + n + 1, 0);
        for(int i = 1; i <= n; i++) {
            cin >> con[i];
            degree[con[i]]++;
        }
        if(solve()) {
            cout << ans.size() << "\n";
            for(int v : ans)
                cout << v << " ";
            cout << "\n";
        }
        else cout << "-1\n";
    }
};