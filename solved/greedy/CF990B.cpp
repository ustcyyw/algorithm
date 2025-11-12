/**
 * @Time : 2025/4/2-9:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF990B 1200 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 15, M = 30;
int n, k;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    map<int, int> mp;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        mp[num]++;
    }
    int cnt = 0;
    for(auto it = mp.begin(), nxt = ++mp.begin(); nxt != mp.end(); it++, nxt++) {
        if(it->first + k >= nxt->first)
            cnt += it->second;
    }
    cout << n - cnt;
}