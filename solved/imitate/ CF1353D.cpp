/**
 * @Time : 2024/6/26-11:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1353D 模拟 优先队列
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, k, ans[N];

struct cmp{
    bool operator()(vector<int>& a, vector<int>& b){
        int t1 = a[1] - a[0], t2 = b[1] - b[0];
        return t1 != t2 ? t1 < t2 : a[0] > b[0];
    }
};
priority_queue<vector<int>, vector<vector<int>>, cmp> pq;

void solve() {
    pq = {};
    pq.push({1, n});
    for(int i = 1; i <= n; i++) {
        vector<int> p = pq.top();
        pq.pop();
        int l = p[0], r = p[1], mid = (l + r) / 2;
        ans[mid] = i;
        if(l <= mid - 1) pq.push({l, mid - 1});
        if(mid + 1 <= r) pq.push({mid + 1, r});
    }
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        solve();
    }
};