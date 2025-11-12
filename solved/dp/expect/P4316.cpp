/**
 * @Time : 2023/5/6-4:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */

/*
 * 期望dp 概率dp 转移一般是递推
 * 两种套路
 * 一种是从上一个状态转移得（填表法）。
 * 前置点的状态都算出来了，当前点一次计算就得到最终结果，所以是填状态表
 * 另一种是转移向下一个状态（刷表法）。
 * 已知当前点的状态，更新前置点的状态，会将前置点的答案都进行增/减之类的 前置结点会不断被修改 所以在不断刷新状态表
 * 逆推以当前结点更新前置结点，计算顺序应该按照拓扑排序进行
 *
 * 有时期望dp以最终状态为初始状态 进行逆推
 * f[i]表示到达最终状态n的期望xxx。本题中f[i]表示到达终点n的期望路径总长度
 * 转移方程形如 f[i] = sigma(p(i,j) * f[j] + w(i,j))
 * 其中p(i,j)是 i->j 的概率， w(i,j) 是i->j的转移对答案的贡献
 *
 * 本题中p(i,j) = 1 / degree[i]，概率均等
 * w(i,j) = 边长l * p(i,j)：走长度为l的路径，走的概率为p(i,j)，对总长度的贡献是 l * p(i,j)
 *
 * 初状态 f[n] = 0: n到n的期望路径总长为0
 * 答案 f[1], 从起点1到终点n的期望路径总长
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, m, degree[N], aux[N];
double f[N];
vector<vector<vector<int>>> graph;

void topol_sort() {
    fill(aux, aux + n + 1, 0);
    for(int i = 1; i <= n; i++)
        aux[i] = degree[i];
    queue<int> queue;
    queue.push(n);
    while (queue.size()) {
        int v = queue.front(); queue.pop();
        for(auto& edge : graph[v]) {
            int w = edge[0], l = edge[1];
            f[w] += (f[v] + l) / aux[w];
            if(--degree[w] == 0) queue.push(w);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m;
    fill(degree, degree + n + 1, 0);
    fill(f, f + n + 1, 0);
    graph.assign(n + 1, {});
    for(int i = 0, v, w, len; i < m; i++) {
        cin >> v >> w >> len;
        // 建反图 跑拓扑排序 就是进行逆推
        graph[w].push_back({v, len}), degree[v]++;
    }
    topol_sort();
    printf("%.2f", f[1]);
}