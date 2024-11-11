/**
 * @Time : 2024/6/11-4:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1699C 构造 组合数学
 */
/*
mex(0) = 1
a中0的位置为i0，如果b[i0] != 0，那么mex(b[i1]) = 0 就不对了
所以b[i0] = 0 a和b中0的位置必须相同

任何包含了i0但是不包含i1的子数组 mex = 1
如果b[i1] != 1, b中为1的位置在别处，记为j， mex(b[i0, j]) = 2, mex(a[i0, j]) = 1
所以a中为1的位置 b中也要为1

包含了i0、i1 但不包含i2的 mex = 2
如果a中i2在i0和i1之间：mex(a[i0,j]) = 1, mex(a[j,i1]) = 0, mex(a[i0,i1]) = 3
i2在[i0,i1]上具体哪个位置都不影响这些子数组的mex值
那么在b中i2也只需要放在[i0,i1]上任意一个位置 都和a的相应子数组的mex值保持一致
如果a中i2在i0和i2之外 b中i2和a中i2不相同，放在了j位置
假设 i0 < i1 < j < i2: mex(a[i0,j]) = 2, mex(b[i0,j]) = 3, 二者不想等
也可以假设 i0 < i1 < i2 < j: mex(a[i0,j - 1]) = 3, mex(b[i0,j - 1]) = 2, 二者不想等
所以ab中2的位置也必须相同

类推得出 一个数在所有比他小的数的中间，那这个数就有很多位置可以放
（比它小的数所确定的区间上任意空位置选一个放置即可）
如果在所有比他小的数的外面，那在b中就只能和a保持相同位置。
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, nums[N], mp[N];

int solve() {
    if(n <= 3) return 1;
    int lo = mp[0], hi = lo;
    ll ans = 1;
    for(int i = 1; i < n; i++) {
        int t = mp[i];
        if(t > lo && t < hi) ans = (hi - lo + 1 - i) * ans % mod;
        else if(t > hi) hi = t;
        else lo = t;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            mp[nums[i]] = i;
        }
        cout << solve() << "\n";
    }
};