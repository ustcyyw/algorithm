/**
 * @Time : 2024/4/14-11:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 考虑交换某一位 不管怎么交换 两个数之和是相同的
  * 那么要让两个数的积更大 由均值不等式可知 要让两个数尽可能的一样大
  * 那么可以预设让s >= t。从高位开始遍历
  * 在s小于t的前提下 某一位上 s[i] < t[i]，就进行交换，这样就保证s更大
  * 之后的每一位上 都让t更大 这样就能保证两个数尽可能的一样大
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 3e5 + 5;
int T, n, a[N];
string s, t;

void solve() {
    int m = s.size();
    for(int i = 0, flag = 0; i < m; i++) {
        if(s[i] == t[i]) continue;
        if(!flag) { // s 更小的时候
            if(s[i] < t[i]) swap(s[i], t[i]);
            flag = 1;
        } else { // 前面已经保证s更大了
            if(s[i] > t[i]) swap(s[i], t[i]);
        }
    }
    cout << s << "\n" << t << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> s >> t;
        solve();
    }
};