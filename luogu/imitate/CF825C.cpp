/**
 * @Time : 2025/3/4-12:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF825C 1600 模拟 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, P = 13331;
ll n, k, nums[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    sort(nums, nums + n + 1);
    int cnt = 0;
    for(int i = 1; i <= n; ) {
        if(2 * k >= nums[i]) k = max(k, nums[i]), i++;
        else cnt++, k *= 2;
    }
    cout << cnt << "\n";
}