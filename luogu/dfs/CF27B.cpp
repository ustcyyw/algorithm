/**
 * @Time : 2025/1/30-10:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF27B 1300 图论 dfs
 */
 /*
  * 每个人都需要出现在比赛记录中n-1次 可以通过这个标准找到缺失的两个人
  * 再根据已有的比赛结果建有向图 看看谁在前面即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 50 + 5, M = 2 * N;
int n, cnt[N], marked[N], s = -1, t = -1;
vector<int> graph[N];

bool dfs(int v) {
    marked[v] = 1;
    if(v == t) return true;
    for(int w : graph[v]) {
        if(!marked[w] && dfs(w)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n;
    for(int i = 1, v, w; i <= n * (n - 1) / 2 - 1; i++) {
        cin >> v >> w;
        cnt[v]++, cnt[w]++;
        graph[v].push_back(w);
    }
    for(int i = 1; i <= n; i++) {
        if(cnt[i] == n - 1) continue;
        if(s == -1) s = i;
        else t = i;
    }
    if(dfs(s)) cout << s << " " << t;
    else cout << t << " " << s;
};