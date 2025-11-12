/**
 * @Time : 2024/5/7-1:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, T = 1e9 + 1;
ll n, nums1[N], nums2[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    ll mc = 0, add = 0;
    unordered_map<ll, ll> map;
    for(int i = 0; i < n; i++)
        cin >> nums1[i];
    for(int i = 0; i < n; i++)
        cin >> nums2[i];
    for(int i = 0; i < n; i++) {
        ll a = nums1[i], b = nums2[i];
        add += a == 0 && b == 0;
        if(a == 0 && b == 0) continue;
        if(b == 0) {
            mc = max(mc, ++map[0]);
        } else {
            if(a == 0) continue;
            ll g = gcd(a, b), sign = a * b / abs(a * b);
            a = abs(a) / abs(g), b = abs(b) / abs(g);
            ll key = sign * (a * T + b);
            mc = max(mc, ++map[key]);
        }
    }
    cout << mc + add;
};