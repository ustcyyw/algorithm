/**
 * @Time : 2024/3/19-2:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 特殊地 如果初始状态时 x的度数就为1或者0，那么先手玩家直接拿走就好
  * 先从简单case入手
  * 1.如果x的有4个相邻结点 并且这些结点度数都是1（就是直接可以拿走了）
  * 那么先手拿一个，后手拿一个后，x还剩2个相邻结点，这个时候先手无论拿走哪个，后手接下来都会拿走x
  * 发现如果x有偶数个相邻结点，在仅剩2个相邻结点前，都是一组2个地拿，最终都是后手获胜
  * 2.如果x有奇数个相邻结点，在仅剩1个相邻结点前，都是一组2个地拿，最终先手获胜
  *
  * 将x定为根 如果x的相邻结点度数不为1，那么先手和后手都可以通过拿分支末端的结点来调整
  * 使得最后x的相邻结点度数为1，且保持x的子结点奇偶性不变 就回到了简单情况
  * 因此只需要判断x的子结点个数的奇偶性即可。
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 4e5 + 5;
int T, n, x, degree[N];
vector<vector<int>> graph;

string solve() {
    if(degree[x] <= 1) return "Ayush";
    function<int(int, int)> dfs = [&](int v, int f) -> int {
        int cnt = 1;
        for(int w : graph[v])
            if(w != f) cnt += dfs(w, v);
        return cnt;
    };
    return (dfs(x, -1) - 1) % 2 == 0 ? "Ashish" : "Ayush";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> x;
        memset(degree, 0, sizeof(degree));
        graph.assign(n + 1, vector(0, 0));
        for(int i = 0, v, w; i < n - 1; i++) {
            cin >> v >> w;
            degree[v]++, degree[w]++;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        cout << solve() << "\n";
    }
};