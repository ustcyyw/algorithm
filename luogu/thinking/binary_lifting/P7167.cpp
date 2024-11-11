/**
 * @Time : 2024/4/18-10:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 单调栈确定下一个流入的是哪个盘子
 * 可以发现 水流的流向构成一棵树 树的根就是大地（无限容量）
 *
 * 如果溢出的时候 一个一个盘子挨个看什么时候能装下太慢了
 * 所以想到倍增 （就和找第k个祖先一样 一个一个结点找很慢）
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5, D = 18;
int n, m, d[N], a[N], f[N][D], sum[N][D]; // 结点n到其2^d个父亲结点的路径上的结点和（不包括2^d这个父亲）

void init() {
    stack<int> stack;
    stack.push(n + 1);
    for(int i = n; i >= 1; i--) {
        while(d[stack.top()] <= d[i]) stack.pop();
        f[i][0] = stack.top();
        sum[i][0] = a[i];
        for(int j = 1; j < D; j++) {
            int v = f[i][j - 1];
            f[i][j] = f[v][j - 1];
            sum[i][j] = sum[i][j - 1] + sum[v][j - 1];
        }
        stack.push(i);
    }
}

int find(int i, int x) {
    if(sum[i][0] >= x) return i == n + 1 ? 0 : i;
    for(int j = 1; j < D; j++) {
        if(sum[i][j] >= x) { // 到第 2^j 个父结点(不包括) 容积已经 >= x。那么就应该从i的第 2^(j-1)个父亲开始找
            return find(f[i][j - 1], x - sum[i][j - 1]);
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> d[i] >> a[i];
    d[n + 1] = INT_MAX; // n + 1 表示地板
    sum[n + 1][0] = 1e9;
    init();
    for(int i = 1, r, v; i <= m; i++) {
        cin >> r >> v;
        cout << find(r, v) << "\n";
    }
};