/**
 * @Time : 2024/11/22-11:49 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2000G 图论 贪心 dijkstra 2100
 */
 /*
  * t1-t2期间要打电话 此时不可以坐车
  * 到某个点 肯定是越早越好 比如到某个点的时间为 time1 或者 time2， time1 < time2
  * 那么在time1到达该点后 可以立即出发 也可以等1、2、3...time2 - time1 秒再出发
  * 等待到time2的时候也不过是和time2才到达策略空间一致 因此先到达可能更好，或者至少不差
  * 行驶过程中不涉及[t1,t2]时间段的 显然应该坐车
  * 如果涉及到该时间段的
  * 1. 在站点等待至t2，然后坐车
  * 2. 直接步行
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e5 + 5;
int T, n, m, t1, t2, t0, marked[N];
ll distTo[N];
vector<vector<vector<int>>> graph;

ll cal(vector<int>& edge) {
    int v = edge[0], l1 = edge[2], l2 = edge[3];
    ll d1 = distTo[v] + l1, d2 = distTo[v] + l2; // 走路不受时间限制
    if((distTo[v] >= t1 && distTo[v] < t2) || (distTo[v] <= t1 && distTo[v] + l1 > t1))
        d1 = t2 + l1;
    return min(d1, d2);
}

struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) {
        return cal(a) >= cal(b); // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};
priority_queue<vector<int>, vector<vector<int>>, cmp> pq;

void relax(int v) {
    marked[v] = true;
    for (auto &edge: graph[v]) {
        ll temp = cal(edge);
        if (distTo[edge[1]] > temp) {
            distTo[edge[1]] = temp;
            pq.push(edge);
        }
    }
}

void dijkstra(int start_time) {
    fill(distTo, distTo + n + 1, (ll)1e18), fill(marked, marked + n + 1, 0);
    distTo[1] = start_time;
    pq = {};
    relax(1);
    while (!pq.empty()) {
        vector<int> edge = pq.top();
        pq.pop();
        if (!marked[edge[1]])
            relax(edge[1]);
    }
}

void solve() {
    int lo = -1, hi = t0;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        dijkstra(mid);
        if(distTo[n] <= t0) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> m >> t0 >> t1 >> t2;
        graph.assign(n + 1, {});
        for(int i = 1, v, w, l1, l2; i <= m; i++) {
            cin >> v >> w >> l1 >> l2;
            graph[v].push_back({v, w, l1, l2}), graph[w].push_back({w, v, l1, l2});
        }
        solve();
    }
};