/**
 * @Time : 2024/12/19-11:25 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 注意数据范围 3e5以内的数 因子数量并不多
  * 可以将数与他们的因子建图
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5;
int T, n, s, t, nums[N], mp[N], path[2 * N], marked[2 * N];
vector<int> graph[2 * N];

vector<int> divisors[N];
int init = []() {
    for (int i = 2; i < N; ++i)
        for (int j = i; j < N; j += i)
            divisors[j].push_back(i);
    return 0;
}();

int bfs(int s) {
    queue<int> queue;
    queue.push(s), marked[s] = 1, path[s] = -1;
    int step = 1;
    while(!queue.empty()) {
        int sz = queue.size();
        while(sz-- > 0) {
            int v = queue.front(); queue.pop();
            for(int w : graph[v]) {
                if(marked[w]) continue;
                path[w] = v;
                if(w < N && mp[w] == t) return step;
                queue.push(w), marked[w] = 1;
            }
        }
        step++;
    }
    return -1;
}

void solve() {
    if(s == t) {
        cout << 1 << "\n" << s;
        return;
    }
    if(nums[s] == nums[t] && nums[s] != 1) {
        cout << 2 << "\n" << s << " " << t;
        return;
    }
    int temp = bfs(nums[s]);
    if(temp == -1) {
        cout << -1;
        return;
    }
    cout << temp / 2 + 1 << "\n";
    vector<int> nodes;
    for(int v = nums[t]; v != -1; v = path[v])
        if(v < N) nodes.push_back(mp[v]);
    for(int i = nodes.size() - 1; i >= 0; i--)
        cout << nodes[i] << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cin >> s >> t;
        for(int i = 1; i <= n; i++) {
            if(mp[nums[i]] != 0 && i != s && i != t) continue;
            mp[nums[i]] = i; // 腿数到编号的印射
            for(int f : divisors[nums[i]]) {
                int w = f + N;
                graph[w].push_back(nums[i]), graph[nums[i]].push_back(w);
            }
        }
        mp[nums[s]] = s, mp[nums[t]] = t;
        solve();
    };
};