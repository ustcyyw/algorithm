/**
 * @Time : 2025/2/21-9:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF797D 2100 思维题 启发式合并
 */
 /*
  * 当前结点是v
  * 如果其左边的结点 vl > v, 那这个结点就查找不到
  * 如果其右边的结点 vr < v, 那这个结点就查找不到
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5;
ll n, root, degree[N], nodes[N][2], val[N];

void merge(multiset<int>& less, multiset<int>& more, int v) {
    for(int num : less)
        more.insert(num);
    more.insert(v);
}

// 返回以结点c为查找的起点 能查找到的数值的集合
multiset<int> dfs(int c) {
    if(c == -1) return {};
    int v = val[c], l = nodes[c][0], r = nodes[c][1];
    if(l == -1 && r == -1) return {v};
    multiset<int> left = dfs(l), right = dfs(r);
    while(!left.empty() && *left.rbegin() > v)
        left.erase((--left.end()));
    while(!right.empty() && *right.begin() < v)
        right.erase(right.begin());
    if(left.size() < right.size()) {
        merge(left, right, v);
        return right;
    } else {
        merge(right, left, v);
        return left;
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n;
    for(int i = 1, l, r; i <= n; i++) {
        cin >> val[i] >> l >> r;
        nodes[i][0] = l, nodes[i][1] = r;
        if(l != -1) degree[l] = 1;
        if(r != -1) degree[r] = 1;
    }
    for(int i = 1; i <= n; i++) {
        if(degree[i] == 0) {
            root = i;
            break;
        }
    }
    multiset<int> set = dfs(root); // 能查找到到数值
    int cnt = 0;
    for(int i = 1; i <= n; i++) { // 还要计算一共有多少数在这些数值集合中
        if(set.count(val[i]))
            cnt++;
    }
    cout << n - cnt << "\n";
};