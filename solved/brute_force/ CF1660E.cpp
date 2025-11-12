/**
 * @Time : 2024/7/29-10:34 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1660E
 */
 /*
  * 代价 对角线不为1的 + 其它位置为1的
1的数量固定 那么对角线1越多 其它位置的1越多 目标固定 就是要让对角线的1变多
记对角线1的数量为cnt，整个矩阵一共有total个1 则代价为 n - cnt + total - cnt
要让代价最小 就要调整矩阵使得cnt最大
通过尝试case发现 四种操作不管如何使用 能在对角线的n个元素组，组内的元素是固定的
因此可以暴力枚举哪一个组内的1最多
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, total;
string s[2005];

int cal(int x, int y) {
    int cnt = 0;
    while(x < n && y < n) {
        if(s[x][y] == '1') cnt++;
        x++, y++;
    }
    return cnt;
}

void solve() {
    int cnt = 0; // 记录对角线上最多的1的数量
    for(int i = 0; i < n; i++) {
        int temp = cal(0, i);
        if(i != 0) temp += cal(n - i, 0);
        cnt = max(temp, cnt);
    }
    cout << n - cnt + total - cnt << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        total = 0;
        for(int i = 0; i < n; i++) {
            cin >> s[i];
            for(char c : s[i])
                if(c == '1') total++;
        }
        solve();
    }
};