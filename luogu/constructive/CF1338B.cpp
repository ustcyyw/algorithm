/**
 * @Time : 2025/1/20-12:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1338B 1800 构造
 */
 /*
  * 找最少 如果所有叶子结点的距离都是偶数 那路径全部取相同值即可
  * 如果有叶子结点距离是奇数 就得用3个值才能保证奇数长度路径为0
  * 长度超过3的奇数路径，只要3个值都分别出现奇数次即可
  * 同一个图中的偶数长度路径 也有可以安排3个值都出现偶数次
  *
  * 最多 距离为2的子结点必须安排相同的值 其余每条路径随便安排都能刚好凑出来
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7, R = 26;
int T, n, c, depth[N], degree[N], cnt[N];
vector<vector<int>> graph;

void dfs(int v, int f, int d) {
    depth[v] = d;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v, d + 1);
    }
}

int cal_min() {
    for(int i = 1; i <= n; i++) {
        if(degree[i] == 1) {
            dfs(i, -1, 0);
            break;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(degree[i] == 1 && depth[i] % 2 == 1)
            return 3;
    }
    return 1;
}

int cal_max() {
    for(int i = 1; i <= n; i++) {
        if(degree[i] == 1)
            cnt[graph[i].back()]++;
    }
    int same = 0;
    for(int i = 1; i <= n; i++) {
        if(degree[i] != 1 && cnt[i] >= 2)
            same += cnt[i] - 1;
    }
    return n - 1 - same;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        graph.assign(n + 1, {});
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
            degree[v]++, degree[w]++;
        }
        cout << cal_min() << " " << cal_max() << "\n";
    }
};