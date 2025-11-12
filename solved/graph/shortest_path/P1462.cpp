/**
 * @Time : 2023/5/8-3:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
int n, m, b, f[N], aux[N];
vector<vector<vector<int>>> graph;

vector<long long> dist;
struct cmp{
    bool operator()(vector<int>& a, vector<int>& b){
        long long t = dist[a[0]] + a[2] - dist[b[0]] - b[2];
        cout << dist[a[0]] + a[2] << "," << dist[b[0]] + b[2] << endl;
        return t >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};
bool check(int cost) {
    if(f[0] > cost || f[n - 1] > cost) return false;
    vector<bool> marked(n, false);
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    dist = vector(n, LONG_LONG_MAX);
    dist[0] = 0;
    function<void(int v)> relax = [&](int v) -> void {
        if(f[v] > cost) return;
        marked[v] = true;
        for(auto& edge : graph[v]) {
            int w = edge[1], c = edge[2];
            if(dist[w] > dist[v] + c) {
                dist[w] = dist[v] + c;
                pq.push(edge);
            }
        }
    };
    relax(0);
    while (!pq.empty()) {
        vector<int> edge = pq.top(); pq.pop();
        if(!marked[edge[1]])
            relax(edge[1]);
    }
    return dist[n - 1] <= b;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m >> b;
    for(int i = 0, c; i < n; i++) {
        cin >> c;
        f[i] = c;
    }
    if(n == 1) {
        cout << f[0] << endl;
        return 0;
    }
    memcpy(aux, f, sizeof f);
    sort(aux, aux + n);
    graph = vector(n, vector(0, vector(0, 0)));
    for(int i = 0, v, w, c; i < m; i++) {
        cin >> v >> w >> c;
        v--, w--;
        graph[v].push_back({v, w, c}), graph[w].push_back({w, v, c});
    }
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(aux[mid])) hi = mid;
        else lo = mid + 1;
    }
    if(hi == n) cout << "AFK" << endl;
    else cout << aux[lo] << endl;
}