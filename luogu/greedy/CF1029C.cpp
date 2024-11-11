/**
 * @Time : 2024/4/22-4:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 枚举的是要删除的线段 其余线段 右端最小值 左端最大值
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5;
int n, l[N], r[N];

int find(priority_queue<int>& pq, int num) {
    if(pq.top() != num) return pq.top();
    pq.pop();
    int ans = pq.top();
    pq.push(num);
    return ans;
}

int find(priority_queue<int, vector<int>, greater<>>& pq, int num) {
    if(pq.top() != num) return pq.top();
    pq.pop();
    int ans = pq.top();
    pq.push(num);
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    priority_queue<int> lb; // 左边界 要看最大值
    priority_queue<int, vector<int>, greater<>> rb; // 右边界 看最小值
    for(int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
        lb.push(l[i]), rb.push(r[i]);
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int lo = find(lb, l[i]), hi = find(rb, r[i]);
        ans = max(hi - lo, ans);
    }
    cout << ans;
};