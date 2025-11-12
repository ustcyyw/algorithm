/**
 * @Time : 2024/9/27-10:41 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1899F 构造 + 猜结论
 */
/*
 * 观察test case发现 初始的树都是一个单链
 * 假设我们就以单链为初始的树 单链长度为n-1
 * 对于任意的d <= n - 1，都可以将结点n移动到 结点d上
 * (移动就是将结点n与当前结点断开，并且添加一条边到结点d)
 * 结点d到结点1的距离为 d - 1， n到d的距离为1 这两个叶子结点的距离刚好是d
 * 于是我们可以将结点d视为一个游标，整个链视为一个卡尺，根据d调整刻度
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e5 + 5, mod = 998244353;
int T, n, q, p_node;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> q;
        p_node = n - 1;
        for(int i = 1; i < n; i++)
            cout << i << " " << i + 1 << "\n";
        for(int i = 1, d; i <= q; i++) {
            cin >> d;
            if(d == p_node) cout << "-1 -1 -1\n";
            else {
                cout << n << " " << p_node << " " << d << "\n";
                p_node = d;
            }
        }
    }
};