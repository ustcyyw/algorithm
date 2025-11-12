/**
 * @Time : 2024/12/16-10:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1848C 1800 数学 找规律 数论
 */
 /*
  * 首先按照题目定义的操作 观察几组 a[i],b[i]
  * 发现第一次a[i]为0后，a[i]以周期为3出现0。记a[i]通过ci次操作第一次变为0
  * 因此要让a全部为0需要满足
  * ci + 3 * mi = cj + 3 * mj， 对于所有的i,j成立
  * 整理为 ci - cj = 3 * (mj - mi) 也就是说ci - cj是3的倍数
  * ci % 3 == cj % 3
  * 后续重点就是求ci 通过打表一些数据来找规律快速计算（找规律的过程 恶心）
  *
  * 还要注意特别地：如果a[i] = b[i] = 0那么无论操作多少次都保持a[i] = 0
  * 这一组数就不用参与讨论了
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int T, n, a[N], b[N];

int dfs(int a, int b) {
    if(a == 0) return 0;
    if(b == 0) return 1;
    if(a <= b) return 2 + dfs(b - a, a);
    int c = a / b;
    if(c == 1) return 1 + dfs(b, a - b);
    if(c % 2 == 0) {
        int t = dfs(a % b, b);
        return c / 2 * 3 + t;
    }
    else {
        int t = dfs(a % b + b, b);
        return (c - 1) / 2 * 3 + t;
    }
}

bool solve() {
    for(int i =1, pre = -1; i <= n; i++) {
        if(a[i] == 0 && b[i] == 0) continue;
        int c = dfs(a[i], b[i]), mod = c % 3;
        if(pre == -1) pre = mod;
        else if(pre != mod) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            cin >> b[i];
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};