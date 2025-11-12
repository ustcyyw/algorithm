/**
 * @Time : 2025/10/29-10:07
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2167F 1700 思维题 贡献法
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, mod = 1e9 + 7;
int T, n, k;
ll ans;
vector<vector<int>> graph;

int dfs(int v, int f) {
    int sum = 1;
    for(int w : graph[v]) {
        if(w == f) continue;
        int c = dfs(w, v);
        sum += c;
        // w子树中的结点作为根结点，那么其它结点一共有 m = n - c 个
        // 如果 m >= k，那么选择v和m中的另外k-1个结点，w子树中的根的s集合中 就一定有v这个元素
        // v贡献的答案就要增加c
        if(n - c >= k) ans += c;
    }
    // 以f子树中的结点作为根结点，其它结点一共有sum个, sum >= k， v贡献的答案就要增加n-sum
    if(sum >= k) ans += n - sum;
    return sum;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        graph.assign(n + 1, {}), ans = n; // 从dfs的角度看 没有计算v自己为根时他对自己的贡献，所以要+n
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs(1, -1);
        cout << ans << "\n";
    }
}