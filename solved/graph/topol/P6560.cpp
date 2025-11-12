/**
 * @Time : 2023/5/18-10:28 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 如果某个人开始时在终点（意味着上一次已经有人将棋子移动到终点），那么这个人就输了
 * 如果某个人开始时在出度为0的点，它没法移动，也输了
 * 因此 终点或者出度为0的点，是(当前先手的)必输点。
 * 走一步可以到达必输点的点，就是(当前先手的)必赢点，因为先手方一定会选择移动到必输点
 * 再往前推，如果某个点只能走到必赢点，那该点就是必输点；如果某个点可以走到一个必输点，该点就必赢
 *
 * 从终点倒推前置点的状态 不方便 所以逆向建图 正着推
 * 入度为0或者终点，是必输点
 * 必输点一步到达的点为必赢点；如果某个点没有必输点走过来，它就是必输点
 *
 * 某个点的状态被确定，就可以作为前置结点去给别的结点定义输赢 因此放入队列中
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;
int n, m, q, degree[N], aux[N], win[N];
vector<vector<int>> graph;

void topol_sort(int s) {
    queue<int> queue;
    for(int i = 1; i <= n; i++) {
        if(degree[i] == 0 || i == s)
            queue.push(i), win[i] = -1;
        aux[i] = degree[i];
    }
    while (queue.size()) {
        int v = queue.front(); queue.pop();
        for(int w : graph[v]) {
            if(win[w] != 0) continue; // 被确定了就不用再判断
            aux[w]--;
            if(win[v] == -1) { // v 是必输点
                win[w] = 1;
                queue.push(w);
            } else if(aux[w] == 0){
                // v是必赢点，且通向w的所有边都考虑过了（入度已经为0），没有一个必输点走向w，那么w是必输
                win[w] = -1;
                queue.push(w);
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m >> q;
    fill(degree, degree + n + 1, 0);
    graph.assign(n + 1, {});
    for (int i = 1, v, w; i <= m; i++) {
        cin >> v >> w;
        graph[w].push_back(v), degree[v]++;
    }
    for(int i = 1, s, t; i <= q; i++) {
        cin >> s >> t;
        fill(win, win + n + 1, 0);
        topol_sort(t);
        cout << win[s] << endl;
    }
}