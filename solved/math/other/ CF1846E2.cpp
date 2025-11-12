/**
 * @Time : 2024/7/15-12:04 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 满k叉树的结点和 就是一个等比数列求和
 * sum = (k ^ n - 1) / (k - 1)
 * 分子是一个指数函数 所以n不会很大 最大62就足够使得和一定超过1e18（k取2计算时也能超过）
 * 因此可以枚举究竟需要加和多少项n
 * 对于固定的n去找最大的k使得sum <= num
 * 为了找到这样的k 改写sum = 1 + k + k ^ 2 + ... k ^ (n - 1)
 * 于是可以在计算过程中一旦发现累加 >= num就终止 防止溢出
 * 然后看项数是否已经有n项即可
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef __int128 ll;
long long T, num;

int check(int n, int k) {
    int i = 1;
    ll sum = 0;
    for(ll val = 1; i <= n; val *= k, i++) {
        sum += val;
        if(sum >= num) break;
    }
    if(sum > num) i--;
    return i;
}

// 找到最大的k 使得 sum(k ^ i), for i in [0, n - 1] <= sum
int find_k(int n) {
    int lo = 2, hi = 1e9;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(n, mid) >= n) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

bool solve() {
    for(int n = 3; n < 63; n++) {
        int k = find_k(n);
        if(check(n, k) == n) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> num;
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};