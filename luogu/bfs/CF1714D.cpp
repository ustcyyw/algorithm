/**
 * @Time : 2024/3/6-10:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 因为染色允许重叠 如果当前需要染色的位置是i
  * 那么选择一个最长的可染色字符一定比短的好。
  * 因为一次染色操作覆盖了更多字符 而所有被覆盖的字符
  * （除了当前次操作被染色的第一个字符，因为以它为起点 无法让更多字符被染色）
  * 都可以成为下一次操作的起点
  * 未覆盖区域的第一个字符也可以成为下一次操作的起点
  * 也就是说长的染色字符可提供的选择囊括了短的字符 且更多
  *
  * 那么从1开始作为起点 选择最长的可染色字符 将相应字符染色后
  * 这些字符及未染色的第一个字符可以成为新的起点 进行下一次染色操作
  * 要求最少操作次数 也就是问多少次操作后覆盖到了最后一个字符
  * bfs
  *
  * 在bfs过程中记录点被访问时 是使用哪个字符来操作idx 以及起点start
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 3e5 + 5;
int n, m, T, marked[105], idx[105], start[105];
string t, ss[11];

void solve() {
    deque<int> dq;
    marked[0] = 0, dq.push_back(0);
    while(!dq.empty()) {
        int i = dq.front();
        for(int k = 1; k <= n; k++) {
            string& s = ss[k];
            int len = s.size();
            if(m - (i + 1) >= len && s == t.substr(i + 1, len)) {
                for(int j = i + len; j > i && marked[j] == -1; j--) {
                    marked[j] = marked[i] + 1;
                    idx[j] = k, start[j] = i + 1;
                    dq.push_back(j);
                }
            }
            if(marked[m - 1] != -1) break;
        }
        if(marked[m - 1] != -1) break;
        dq.pop_front();
    }
    if(marked[m - 1] == -1) {
        cout << -1 << "\n";
        return;
    }
    cout << marked[m - 1] << "\n";
    for(int i = m - 1; i; ) {
        cout << idx[i] << " " << start[i] << "\n";
        i = start[i] - 1;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> t;
        t = "." + t;
        m = t.size();
        cin >> n;
        fill(marked, marked + 101, -1);
        for(int i = 1; i <= n; i++)
            cin >> ss[i];
        solve();
    }
};