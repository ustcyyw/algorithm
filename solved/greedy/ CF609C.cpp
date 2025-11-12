/**
 * @Time : 2024/4/4-6:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 1e5 + 5;
int T, n, nums[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    int sum = accumulate(nums + 1, nums + n + 1, 0);
    int base = sum / n, mod = sum % n, cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(nums[i] <= base) continue;
        if(mod > 0) mod--, cnt += nums[i] - (base + 1);
        else cnt += nums[i] - base;
    }
    cout << cnt;
};