/**
 * @Time : 2024/5/8-2:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * q1 = p2 - p1
  * q2 = p3 - p2
  * q3 = p4 - p3
  * ..
  * qn-1 = pn - pn-1
  *
  * q1 = p2 - p1
  * q1 + q2 = p3 - p1
  * q1 + q2 + q3 = p4 - p1
  * q1 + q2 + q3 + ... qn-1 = pn - p1
  *
  * 前缀和之和 = p1 + p2 + ... + pn - n * p1
  * p1 + p2 + ... + pn = n * (n + 1) / 2
  * 可以算出p1 再逆向算出所有pi 还要检查pi是否在[1,n]范围内且不出现重复
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, T = 1e9 + 1;
ll n, sum[N], ss = 0, marked[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i < n; i++) {
        cin >> num;
        sum[i] += sum[i - 1] + num, ss += sum[i];
    }
    ss = n * (n + 1) / 2 - ss;
    if(ss % n == 0) {
        vector<ll> arr;
        ll p1 = ss / n;
        arr.push_back(p1);
        for(int i = 1; i < n; i++) {
            ll pi = p1 + sum[i];
            if(pi < 1 || pi > n || marked[pi]) {
                cout << -1;
                return 0;
            }
            marked[pi] = 1, arr.push_back(pi);
        }
        for(ll num : arr)
            cout << num << " ";
    } else cout << -1;
};