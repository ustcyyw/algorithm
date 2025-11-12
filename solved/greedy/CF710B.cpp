/**
 * @Time : 2025/2/19-11:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF710B 1400 贪心 中位数贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 5;
ll n, nums[N];

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    sort(nums + 1, nums + n + 1);
    cout << (n % 2 == 1 ? nums[n / 2 + 1] : nums[n / 2]);
};