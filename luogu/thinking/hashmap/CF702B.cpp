/**
 * @Time : 2024/3/30-3:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 1e5 + 5;
ll T, n, p[32];

int init = []() -> int {
    for(int i = 1, val = 1; i < 32; i++) {
        val *= 2;
        p[i] = val;
    }
    return 0;
}();

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    ll ans = 0;
    unordered_map<int, int> map;
    for(int i = 0, num; i < n; i++) {
        cin >> num;
        for(int j = 0; j < 32; j++)
            ans += map[p[j] - num];
        map[num]++;
    }
    cout << ans;
};