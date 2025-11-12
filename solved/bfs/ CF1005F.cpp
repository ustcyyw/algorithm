/**
 * @Time : 2024/4/18-8:39 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 要到各个点的距离和最小 那么到各点的距离最小 就一定能保证距离和最小
 * 并且边无权重 因此直接使用bfs就行。
 * 题目要求输出多组答案，思考为什么会出现多组答案 结合题目给的测试用例
 * 可以发现 在bfs的过程中 如果通过不同边到达了同一个结点的距离相同 都是最早的
 * 假如说这样子到达w结点的边的集合用pre[w]表示，一共有cnt条
 * 到w结点之前的方案已经有oc个，到达w的边共cnt个，那么到达w的方案就有oc * cnt个
 * 每oc个方案中，是选择pre[w]中的一条边。
 * 因为答案保证了 m * k < 1e6 因此每种方案选哪些边 都修改一遍时间复杂度也够
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, m, k, at[N];
vector<string> ans;
vector<int> pre[N]; // pre[w]: 能在同一最短时间到达w的边的集合
vector<vector<int>> graph[N];

void fill(int lo, int hi, int id) { // 将多组答案中编号为id的边设置为1
    for(int i = lo; i <= hi; i++)
        ans[i][id] = '1';
}

void copy(int cnt) {
    for(int i = 0; i < cnt; i++)
        ans.push_back(ans[i]);
}

void copy_fill(int w) {
    int oc = ans.size();
    if(pre[w].size() > 1 && oc < k) {
        int cnt = min((int)(pre[w].size() - 1) * oc, k - oc);
        copy(cnt);
    }
    for(int i = 0, cc = ans.size(); i < pre[w].size() && i * oc < cc; i++)
        fill(i * oc, min(i * oc + oc - 1, cc - 1), pre[w][i]);
}

void solve() {
    queue<int> queue;
    int step = 1;
    queue.push(1), at[1] = 0;
    while(!queue.empty()) {
        int sz = queue.size();
        unordered_set<int> set; // 这一轮到达的结点
        while(sz-- > 0) {
            int v = queue.front();
            for(vector<int>& edge : graph[v]) {
                int w = edge[0], id = edge[1];
                if(at[w] < step) continue;
                pre[w].push_back(id);
                if(!set.count(w)) {
                    queue.push(w), at[w] = step;
                    set.insert(w);
                }
            }
            queue.pop();
        }
        for(int w : set)
            copy_fill(w);
        step++;
    }
    cout << ans.size() << "\n";
    for(string& s : ans)
        cout << s << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    ans.push_back(string(m, '0'));
    fill(at, at + n + 1, 1e9);
    for(int i = 0, v, w; i < m; i++) {
        cin >> v >> w;
        graph[v].push_back({w, i}), graph[w].push_back({v, i});
    }
    solve();
};