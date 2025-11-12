/**
 * @Time : 2023/5/6-4:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 105;
int n, p, marked[N];
long long c[N];
vector<vector<vector<int>>> graph;

void topol(queue<int>& queue) {
    while (queue.size()) {
        int sz = queue.size();
        for(int i = 0; i < sz; i++) {
            int v = queue.front(); queue.pop();
            for(auto& edge : graph[v]) {
                int w = edge[0], weight = edge[1];
                c[w] += c[v] * weight;
                if(!marked[w] && c[w] > 0) {
                    queue.push(w);
                    marked[w] = true;
                }
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> p;
    memset(c, 0, sizeof(c));
    memset(marked, 0, sizeof(marked));
    queue<int> queue;
    for(int i = 1, a, b; i <= n; i++){
        cin >> a >> b;
        if(a) {
            queue.push(i);
            c[i] = a;
        } else c[i] = -b;
    }
    graph.assign(n + 1, {});
    for(int i = 1, a, b, w; i <= p; i++) {
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
    }
    topol(queue);
    bool flag = false;
    for(int i = 1; i <= n; i++) {
        if(c[i] > 0 && graph[i].empty()) {
            cout << i << " " << c[i] << endl;
            flag = true;
        }
    }
    if(!flag) cout << "NULL" << endl;
}