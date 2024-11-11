/**
 * @Time : 2024/6/25-10:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1986G1 数学 数论
 */
/*
 * 根据题目要求 肯定是要用hashmap计数的套路 重点是怎么转换
 * pi*pj % i*j == 0
 * 改写为 (pi / i) * (pj / j)，如果将pi / i，pj / j都分别化成最简分数
 * 要让能整除 就要求 pi含有j这个因子，pj含有i这个因子
 * 注意到 n <= 1e5，也就是说这个范围内的数 因子个数最多100多点 并且大部分都是十几二十
 * 那么我们可以在枚举的时候 去找pj含有的因子i对应的集合中 有多少个数含有j这个因子
 * 记maps[i][j]: 因子i对应的集合中 含有因子j的数的个数
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;
typedef long long ll;
int T, n, nums[N];
vector<int> factor[N];

int init = []() -> int {
    for(int num = 1; num < N; num++) {
        for(int i = 1; i <= sqrt(num); i++) {
            if(num % i == 0) {
                factor[num].push_back(i);
                if(i * i != num) factor[num].push_back(num / i);
            }
        }
    }
    return 0;
}();

void solve() {
    vector<unordered_map<int, int>> maps(n + 1);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        int t = gcd(i, nums[i]), j = i / t, num = nums[i] / t;
        for(int ai : factor[num])
            ans += maps[ai][j];
        for(int aj : factor[num])
            maps[j][aj]++;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};