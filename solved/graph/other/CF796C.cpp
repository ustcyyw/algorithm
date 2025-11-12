/**
 * @Time : 2023/5/6-4:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */

#include<bits/stdc++.h>

using namespace std;
const int N = 3e5 + 5;
int n, a, arr[N];
/*
 * 可以枚举根结点 然后查看所有子结点的权重
 * 并且将子结点剔除后，其余结点的值中最大的+2
 * 由于只有n-1条边，枚举每个点的时候，只会遍历该点的边，因此每条边遍历两次 时间复杂度是O(n)
 */
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    multiset<int> set;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a;
        set.insert(a), arr[i] = a;
    }
    vector<vector<int>> graph(n + 1);
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    int res = INT_MAX;
    for(int i = 1; i <= n; i++) { // 枚举根结点
        set.erase(set.find(arr[i]));
        int temp = arr[i] - 1;
        for(int w : graph[i]) {
            temp = max(temp, arr[w]);
            set.erase(set.find(arr[w]));
        }
        res = min(res, max(set.empty() ? INT_MIN : *set.rbegin() + 2, temp + 1));
        for(int w : graph[i])
            set.insert(arr[w]);
        set.insert(arr[i]);
    }
    cout << res << endl;
}