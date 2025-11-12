/**
 * @Time : 2025/3/11-11:22 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF212E 1500 时间复杂度分析 背包dp
 */
/*
  * 不可能全部染色 因为要求至少有1个蓝一个红
  * 染色n-1是做得到的 将某个叶子结点染色成红色 其父亲结点不染色 别的都染色为蓝即可
  * 所以最终答案只允许一个结点不染色 枚举不染色的结点
  *
  * 进行背包dp的时候 看似 n^3
  * 但是枚举不染色结点 以这个结点为分割点 得出的分量总数是 2 * (n - 1) 一条边两个结点各能切割一次这条边
  * 这些分量就是背包dp的"物品"，因此时间复杂度是 n ^ 2
  * 背包dp的值域 n / 2，因为红蓝对称 没必要算超过 n / 2
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 5000 + 5, P = 13331;
int n, ans[N];
vector<int> graph[N];

void cal(vector<int>& arr) {
    unordered_set<int> st = {0};
    for(int i = 0; i < arr.size(); i++) {
        unordered_set<int> nst;
        for(int num : st) {
            int red = num + arr[i];
            nst.insert(num);
            if(red <= n / 2) nst.insert(red);
            ans[red] = 1, ans[n - 1 - red] = 1;
        }
        swap(nst, st);
    }
}

int dfs(int v, int f) {
    if(graph[v].size() == 1 && f != -1) return 1;
    int cnt = 1;
    vector<int> arr;
    for(int w : graph[v]) {
        if(w == f) continue;
        int temp = dfs(w, v);
        cnt += temp, arr.push_back(temp);
    }
    arr.push_back(n - cnt);
    cal(arr);
    return cnt;
}

void solve() {
    dfs(1, -1);
    int cnt = 0;
    for(int i = 1; i < n - 1; i++)
        cnt += ans[i];
    cout << cnt << "\n";
    for(int i = 1; i < n - 1; i++) {
        if(ans[i] > 0)
            cout << i << " " << n - 1 - i << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    solve();
}