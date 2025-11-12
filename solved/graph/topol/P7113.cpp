/**
 * @Time : 2023/5/19-11:04 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 计算害死人啊
 */
#include<bits/stdc++.h>

using namespace std;
# define u __int128
const int N = 1e5 + 5;
int n, m, degree[N];
u water[N][2];
vector<vector<int>> graph;

u gcd1(u a, u b) {
    if (a < b) return gcd1(b, a);
    if (b == 0) return a;
    return gcd1(b, a % b);
}

void add(u* arr1, u* arr2) {
    u a = arr1[0], b = arr1[1], c = arr2[0], d = arr2[1];
    if(b == 0)
        arr1[0] = c, arr1[1] = d;
    else {
        u t = b / gcd1(b, d) * d ;
        arr1[0] = a * (t / b) + c * (t / d) , arr1[1] = t;
    }
    u g = gcd1(arr1[0], arr1[1]);
    arr1[0] /= g, arr1[1] /= g;
}

void topol_sort() {
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 0) queue.push(i);
    while (queue.size()) {
        int v = queue.front(), d = (int)graph[v].size(); queue.pop();
        if(d == 0) continue;
        u g = gcd1(water[v][0], d);
        water[v][0] /= g;
        water[v][1] *= d / g; // 有出度 将水量修改为分给每一个下游管道的水量
        for(int w : graph[v]) {
            add(water[w], water[v]);
            if(--degree[w] == 0) queue.push(w);
        }
    }
}

void Write(u x) {
    if(x > 9) Write(x / 10);
    putchar('0' + (x % 10));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m;
    graph.assign(n + 1, {});
    memset(water, 0, sizeof(water));
    memset(degree, 0, sizeof(degree));
    for(int i = 1; i <= m; i++)
        water[i][0] = water[i][1] = 1;
    for (int i = 1, d, v; i <= n; i++) {
        cin >> d;
        for(int j = 1; j <= d; j++) {
            cin >> v;
            graph[i].push_back(v), degree[v]++;
        }
    }
    topol_sort();
    for(int i = 1; i <= n; i++) {
        if(graph[i].empty())
            Write(water[i][0]), putchar(' '), Write(water[i][1]), putchar('\n');
    }
}