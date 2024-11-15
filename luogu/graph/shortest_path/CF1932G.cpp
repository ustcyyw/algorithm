/**
 * @Time : 2024/11/15-8:53 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1932G 图论 dijkstra变种 贪心 数论 2300
 */
 /*
  * 求最短路径
  * 越早到达某个点肯定越好 因为会多出一些选择
  * 因此是找到达每个点的最短时间 和dijkstra类似
  * 只不过这里的边长是不固定的 依赖于两个点之间何时达到相同高度
  * 所以和dijkstra的区别只是计算边长 在计算 v -> w 的时候
  * 余数相等的条件 l[v] + t * a[v] = l[w] + t * a[w]
  * 要找到大于等于distTo[V]的最小t使得等式成立
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e6 + 5;
int T, n, m, h, l[N], a[N], marked[N];
ll distTo[N];
vector<vector<int>> graph;

// 要比较经过某条边到达非树结点的距离，优先得到最小距离的边
struct cmp {
    bool operator()(vector<ll> &a, vector<ll> &b) {
        return a[2] - b[2] >= 0;
    }
};
priority_queue<vector<ll>, vector<vector<ll>>, cmp> pq;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// 计算从v走到w时 w所需要的时间
ll cal(int v, int w) {
    ll x, y, g = exgcd((a[v] - a[w] + h) % h, h, x, y), t;
    if ((l[w] - l[v]) % g != 0) return (ll)1e18; // 无解退出
    x = x * (l[w] - l[v]) / g; // 算出原方程的解
    t = abs(h / g), x = (x % t + t) % t; // 求出最小非负整数解
    if (distTo[v] > x) x = x + (distTo[v] - x + t - 1) / t * t; //调大 x
    return x + 1; // +1是因为移动也算是一次动作
}

void relax(int v) {
    marked[v] = true;
    for (int w: graph[v]) {
        ll temp = cal(v, w);
        if (distTo[w] > temp) {
            distTo[w] = temp;
            pq.push({v, w, temp});
        }
    }
}

void dijkstra(int s) {
    distTo[s] = 0;
    relax(s);
    while (!pq.empty()) {
        vector<ll> edge = pq.top();
        pq.pop();
        if (!marked[edge[1]])
            relax(edge[1]);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m >> h;
        graph.assign(n + 1, {}), pq = {};
        fill(marked, marked + n + 1, 0), fill(distTo, distTo + n + 1, (ll)1e18);
        for(int i = 1; i <= n; i++)
            cin >> l[i];
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1, v, w; i <= m; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dijkstra(1);
        if(distTo[n] == (ll)1e18) cout << "-1\n";
        else cout << distTo[n] << "\n";
    }
};