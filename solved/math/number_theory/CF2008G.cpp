/**
 * @Time : 2024/10/25-10:47 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2008G 数论 + 二分
 */
/*
  * 找几个数试一下规律 发现如果gcd(a,b) = c
  * 那么通过操作可以将a和b变为0和c 原因是线性操作 两个数的gcd没有变化
  * 因此可以先计算所有数的gcd = c
  * 于是数组的元素就可以转化为一系列0,c,2c,3c 然后再二分看缺失的第k个数
  *
  * 需要特殊处理只有一个元素的情况
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e5 + 5;
int T, n, k, c;

bool check(int val) {
    int tmp = min(val / c + 1, n);
    return val + 1 - tmp >= k;
}

// 找最小的数 使得小等于他的不存在的数 数量 >= k
int solve() {
    if(n == 1) {
        return k <= c ? k - 1 : k;
    }
    int lo = 0, hi = k + n + 10;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        cin >> c;
        for(int i = 1, num; i < n; i++) {
            cin >> num;
            c = gcd(c, num);
        }
        cout << solve() << "\n";
    }
};