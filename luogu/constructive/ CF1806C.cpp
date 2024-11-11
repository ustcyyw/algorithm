/**
 * @Time : 2024/3/8-9:51 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 对于每个子序列 任意取m个元素的积 都等于另外m个元素的和
 * 看起来是一个十分对称的结构 假设所有元素相等 得到等式 a^m = m * a
 * a = 0 or m = 1 or (a = 2 and m = 2) 一共三种可能 其中 a = 0是满足要求的通解
 *
 * 但如果有一个元素和其它元素不同，还是假设其余元素相同
 * b在选取的子序列时 b * a ^ (m - 1) = m * a
 * b不在选的子序列时 a * a ^ (m - 1) = b + (m - 1) * a
 * 两个式子相减 (b - a) * a ^ (m - 1) = a - b
 * (b - a) * (a ^ (m - 1) + 1) = 0, 且已经假设 b != a
 * 就说明 a ^ (m - 1) = -1，因而a = -1 并且m为偶数
 * 代入b * a ^ (m - 1) = m * a得 b = m
 *
 * 验证：这样的序列任意选m个元素，那么这个集合会有两种情况
 * 1. m和(m-1)个-1相加得到1，m个-1相乘，因为m为偶数 乘积为1
 * 2. m和(m-1)个-1相乘，因为m-1是奇数得到-m，m个-1相加和为-m
 *
 * 于是通过这个序列 我们可以枚举m放置的位置 看最小距离
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 4e5 + 5;
int T, n, m, nums[N];
string s;

ll cal(ll sum) {
    ll res = LONG_LONG_MAX;
    for(int i = 1; i <= 2 * n; i++) {
        ll temp = sum - (abs(nums[i] - (-1))) + abs(nums[i] - n);
        res = min(res, temp);
    }
    return res;
}

ll solve() {
    // m = 1的情况 序列任取两个相同的数都可以 距离就是abs(num1 - nums2)
    if(n == 1) return abs(nums[1] - nums[2]);
    ll res = 0, sum1 = 0, sum2 = 0;
    for(int i = 1; i <= 2 * n; i++) {
        res += abs(nums[i]); // 取通解都是0的情况
        sum1 += abs(nums[i] - (-1)); // 每个元素都取-1的情况，后续方便计算一个元素取m，其它元素取-1的情况
        sum2 += abs(nums[i] - 2); // 顺带计算 m = 2，每个元素取2的情况
    }
    if(n == 2) res = min(res, sum2);
    if(n % 2 == 0) res = min(res, cal(sum1));
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= 2 * n; i++)
            cin >> nums[i];
        cout << solve() << "\n";
    }
};