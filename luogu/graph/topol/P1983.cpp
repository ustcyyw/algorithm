/**
 * @Time : 2023/5/6-4:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */

/*
 * 将集合的度数引入 一个停车路线
 * 就是该路线区间内未停靠的站 对这个路线停靠的站 有一个次序关系
 * 集合的度数为0，集合中的结点度数不一定为0；
 * 但反之，集合的度数不为0，集合中的结点度数一定不为0
 * 所以只有在集合度数为0时，一次性将结点度数更新，才check结点度数是否为0
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int n, m, degree_set[N], aux[N], degree_node[N];
vector<vector<int>> graph; // node -> index of the nodes set
vector<unordered_set<int>> routes;

int topol_sort() {
    for(int i = 1; i <= m; i++) {
        int d = degree_set[i];
        aux[i] = d;
        for(int v : routes[i])
            degree_node[v] += d;
    }
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree_node[i] == 0) queue.push(i);
    int step = 0;
    while (queue.size()) {
        int sz = queue.size();
        for(int i = 0; i < sz; i++) {
            int v = queue.front(); queue.pop();
            for(int id : graph[v]) {
                if(--degree_set[id] == 0) { // 某个结点set的度数为0了，将里面对应的结点度数清0
                    int d = aux[id];
                    for(int w : routes[id]) {
                        degree_node[w] -= d;
                        if(degree_node[w] == 0) queue.push(w);
                    }
                }
            }
        }
        step++;
    }
    return step;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m;
    memset(degree_set, 0, sizeof(degree_set));
    memset(degree_node, 0, sizeof(degree_node));
    memset(aux, 0, sizeof(aux));
    graph.assign(n + 1, {}), routes.assign(n + 1, {});
    for(int i = 1, s, v, start, end; i <= m; i++){
        cin >> s;
        for(int j = 1; j <= s; j++) {
            cin >> v;
            if(j == 1) start = v;
            if(j == s) end = v;
            routes[i].insert(v);
        }
        for(int j = start; j <= end; j++) {
            if(!routes[i].count(j))
                graph[j].push_back(i);
        }
        degree_set[i] = end - start + 1 - (int)routes[i].size();
    }
    cout << topol_sort() << endl;
}