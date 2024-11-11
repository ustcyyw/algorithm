/**
 * @Time : 2024/6/14-11:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1272E bfs
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 998244353;
typedef long long ll;
int T, n, nums[N], ans[N], marked[N];
vector<int> graph[N];

void bfs(int flag) {
    queue<int> queue;
    memset(marked, 0, sizeof(marked));
    for(int i = 1; i <= n; i++) {
        if(nums[i] % 2 == flag)
            queue.push(i), marked[i] = 1;
    }
    int step = 1;
    while(!queue.empty()) {
        int sz = queue.size();
        while(sz-- > 0) {
            int v = queue.front();
            for(int w : graph[v]) {
                if(marked[w]) continue;
                if((nums[w] % 2 + flag) % 2 == 1) ans[w] = step;
                queue.push(w), marked[w] = 1;
            }
            queue.pop();
        }
        step++;
    }
}

void solve() {
    bfs(0), bfs(1);
    for(int i = 1; i <= n; i++) {
        cout << (ans[i] == 1e9 ? -1 : ans[i]) << " ";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    fill(ans, ans + n + 1, 1e9);
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
        int j1 = i + nums[i], j2 = i - nums[i];
        if(j1 <= n) graph[j1].push_back(i);
        if(j2 >= 1) graph[j2].push_back(i);
    }
    solve();
};