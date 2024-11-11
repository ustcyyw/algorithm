/**
 * @Time : 2024/7/8-12:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1475F
 */
 /*
  * 如果a[i][j] != b[i][j]就说明这个点需要奇数次操作来变得相等
  * 将这个信息记录到base[i][j]中
  * 对于第一行 只有操作0次和1次这两种结果
  * 一旦第一行确定了 就要求剩下的行 都参照第一行base[0][j]的结果来选择操作情况
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1003, mod = 1e9 + 7;
typedef long long ll;
int T, n, base[N][N];
string a[N], b[N];

bool checkLine(int i, int change) {
    for(int j = 0; j < n; j++) {
        if((base[i][j] ^ change) != base[0][j])
            return false;
    }
    return true;
}

bool check() {
    for(int i = 1; i < n; i++) {
        if(!checkLine(i, 0) && !checkLine(i, 1))
            return false;
    }
    return true;
}

void solve() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(a[i][j] == b[i][j]) base[i][j] = 0;
            else base[i][j] = 1;
        }
    }
    cout << (check() ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> a[i];
        for(int i = 0; i < n; i++)
            cin >> b[i];
        solve();
    }
};