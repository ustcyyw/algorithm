/**
 * @Time : 2024/11/29-2:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1935D 1800 正难则反 数学 容斥定律
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e6 + 5, mod = 1e9 + 7;
ll T, n, c, nums[N];
/*
 * 计算 x + y 在s中的数对数量
 * x + y = nums[i], y = nums[i] - x
 * y >= x 也就是 nums[i] - x >= x, x <= nums[i] / 2
 * nums[j] > nums[i], 那么显然上述条件依旧成立 并且 nums[i] - x <= c 是一定的
 * 因此可以枚举nums[i]，然后计算x的范围 每个x都能找到一系列的y刚好使得 x + y = nums[i]
 */
ll set1() {
    ll sum = 0;
    for(int i = 1; i <= n; i++)
        sum += nums[i] / 2 + 1;
    return sum;
}

/*
 * 计算 y - x 在s中的数对数量
 * y - x = nums[i], y = x + nums[i]
 * y <= c 也就是 x + nums[i] <= c, x <= c - nums[i]
 */
ll set2() {
    ll sum = 0;
    for(int i = 1; i <= n; i++)
        sum += c - nums[i] + 1;
    return sum;
}

/*
 * 计算  x + y 在s中 且 y - x 也在s中的数对数量
 * y + x = nums[i], y - x = nums[j]
 * 也就是 2x = nums[i] - nums[j] 要能满足这个等式 要求 nums[i] >= nums[j] 并且奇偶性一致
 * 注意这里i可以等于j
 */
ll both() {
    ll zero = 0, one = 0, sum = 0;
    for(int i = 1; i <= n; i++) {
        if(nums[i] % 2 == 0) ++zero, sum += zero;
        else ++one, sum += one;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> c;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        ll total = (c + 1) * (c + 2) / 2;
        cout << total - set1() - set2() + both() << "\n";
    };
};