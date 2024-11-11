/**
 * @Time : 2024/3/6-11:35 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 记录每个点最后一次操作1的x1和时间戳 然后查看其时间戳后面操作2的最大值x2是多少
  * 有操作1和2则取max(x1, x2)
  * 只有操作2则取max(a[i], x2)
  * last[i]: 记录i元素最后一次操作1的时间点 -1表示没有操作1
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, q, a[N], ope[N][3], x[N], last[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    fill(last, last + n + 1, -1);
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    cin >> q;
    for(int i = 0, type, p, val; i < q; i++) {
        cin >> type;
        if(type == 1) {
            cin >> p >> val;
            ope[i][1] = p, last[p] = i;
        } else cin >> val;
        ope[i][0] = type, ope[i][2] = val;
    }
    for(int i = q - 1; i >= 0; i--) {
        x[i] = x[i + 1];
        if(ope[i][0] == 2) x[i] = max(x[i], ope[i][2]);
    }
    for(int i = 1; i <= n; i++) {
        if(last[i] == -1) a[i] = max(a[i], x[0]);
        else a[i] = max(ope[last[i]][2], x[last[i]]);
        cout << a[i] << " ";
    }
    cout << "\n";
};