/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
/*
 * 只有Sasha的操作让数组长度-1，因此游戏必须执行n-1论
 * 有n-1次翻转 有n-1次拼接
 * Sasha要让最终结果数位最多 Anna则要让数位最少
 *
 * Anna的策略 显然应该优先翻转末尾0多的
 * Sasha的策略 尽可能保住0 优先将末尾0多的数 接在末尾0少的数前面
 * 由于是Anna先手 因此在Sasha操作时 总会有一个数末尾没有0的 就用它来作为拼接的第二个数
 * 二者都要优先选择0多的数来操作 那么操作n次后 末尾有0的数肯定没有来
 * 此时继续无论怎么操作 都不再影响最终结果的数位大小 不必再考虑
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, A = 1e9 + 1;
int T, n, m, total_len, zero, cnt[N];

int suf_zero(string& num) {
    for(int n = num.size(), i = n - 1; i >= 0; i--) {
        if(num[i] != '0') return n - (i + 1);
    }
    return -1;
}

bool check() {
    sort(cnt + 1, cnt + n + 1);
    for(int i = n; i >= 1; i -= 2)
        zero += cnt[i];
    return total_len - zero - 1 >= m;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        total_len = 0, zero = 0;
        string num;
        for(int i = 1; i <= n; i++) {
            cin >> num;
            total_len += num.size();
            cnt[i] = suf_zero(num);
        }
        cout << (check() ? "Sasha" : "Anna") << "\n";
    }
};