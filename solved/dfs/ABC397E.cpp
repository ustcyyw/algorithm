/**
 * @Time : 2025/3/15-10:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : ABC397E dfs 找结论
 */
 /*
  * 特判 k = 1, 每条路径仅1个结点 那直接全拆开就行
  * 如果某个节点有3个及分支没刚好凑够k，就肯定不行。
  * 有2个分支的话 看当前节点加2个分支是否刚好够k，不够就不行了
  * 有1个分支的话，这个节点肯定是该分支的一部分 就加起来mod k返回
  * 如果没有分支，该节点就是新分支的第一个节点 返回1
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7;
int n, k;
vector<int> graph[N];

int dfs(int v, int f) {
    if(graph[v].size() == 1 && f != -1) return 1;
    vector<int> arr;
    for(int w : graph[v]) {
        if(w == f) continue;
        int cnt = dfs(w, v);
        if(cnt == -1) return -1;
        if(cnt > 0) arr.push_back(cnt);
    }
    if(arr.empty()) return 1;
    if(arr.size() > 2) return -1;
    else if(arr.size() == 2) {
        if(arr[0] + arr[1] + 1 != k)
            return -1;
        return 0;
    } else return (arr[0] + 1) % k;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    if(k == 1) {
        cout << "Yes";
        return 0;
    }
    for(int i = 1, v, w; i <= n * k - 1; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    cout << (dfs(1, -1) == 0 ? "Yes" : "No");
}