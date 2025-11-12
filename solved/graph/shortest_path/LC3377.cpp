/**
 * @Time : 2024/12/9-11:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3377 图论 dijkstra
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4, mod = 1e9 + 7;
vector<int> prime, isPrime(N + 1, 1);
vector<vector<vector<int>>> graph;

void add(int v) {
    for(int i = 1, temp = v; i < N && temp > 0; i *= 10, temp /= 10) {
        if(temp % 10 != 9 && !isPrime[v + i])
            graph[v].push_back({v, v + i});
        if(temp % 10 != 0 && !isPrime[v - i])
            graph[v].push_back({v, v - i});
    }
}
int init = []() {
    for (int i = 2; i <= N; ++i) {
        if (isPrime[i] == 1) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] <= N; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    graph.assign(N, {});
    for(int i = 1; i < N; i++) {
        if(!isPrime[i] || i == 1) add(i);
    }
    return 0;
}();

vector<int> distTo;
// 要比较经过某条边到达非树结点的距离，优先得到最小距离的边
struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) {
        int t = distTo[a[0]] + a[1] - distTo[b[0]] - b[1];
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};
void dijkstra(int s) {
    vector<bool> marked(N, false);
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    distTo = vector(N, INT_MAX);
    distTo[s] = 0;
    function<void(int)> relax = [&](int v) {
        marked[v] = true;
        for (auto &edge: graph[v]) {
            int w = edge[1];
            if (distTo[w] > distTo[v] + w) {
                distTo[w] = distTo[v] + w;
                pq.push(edge);
            }
        }
    };
    relax(s);
    while (!pq.empty()) {
        vector<int> edge = pq.top();
        pq.pop();
        if (!marked[edge[1]])
            relax(edge[1]);
    }
}

class Solution {
public:
    int minOperations(int n, int m) {
        if(n != 1 && (isPrime[n] || isPrime[m])) return -1;
        dijkstra(n);
        if(distTo[m] == INT_MAX) return -1;
        return n + distTo[m];
    }
};