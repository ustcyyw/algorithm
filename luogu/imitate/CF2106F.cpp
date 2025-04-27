/**
 * @Time : 2025/4/26-9:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2106F 1925 模拟
 */
 /*
  * 因为每一列中只有一个位置和其它位置不同，叫特殊位置
  * 并且相邻列这个特殊位置的行号只差1，因此想到观察每一列与相邻的列
  * 举一些例子可以看出
  * 1.连续的0，会有一个从左上到右下的1，使得这几列中的0分为上下两个部分 分别叫up和down
  * 这两个部分都是等差数列求和
  * 2.单一的1，左右两个部分的连续0，左边的down会和右边的up连起来 由这个1所在的列贡献了的0将二者连接
  * 3.超过1个连续的1，就会将0完全隔开
  *
  * 根据例子实现down和up的计算，并且将情况2进行计算
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, mod = 998244353;
int T, n, nxt[N];
vector<int> zero;
string s;

void init() {
    zero = {};
    for(int i = 0, j = 0; i < n; i = j) {
        while(i < n && s[i] == '1') i++;
        j = i;
        while(j < n && s[j] == '0') j++;
        zero.push_back(i), nxt[i] = j;
    }
}

ll cal_up(int lo, int hi) {
    ll cnt = hi - lo + 1;
    return cnt * (lo + lo + cnt - 1) / 2;
}

ll cal_down(int lo, int hi) {
    ll cnt = hi - lo + 1;
    return cnt * n - cnt - cal_up(lo, hi);
}

void solve() {
    init();
    ll ans = 0;
    for(int i = 0; i < zero.size(); i++) {
        int lo = zero[i], hi = nxt[lo] - 1;
        ll up = cal_up(lo, hi), down = cal_down(lo, hi);
        if(lo != 0) up++;
        if(hi != n - 1) down++;
        ans = max({ans, up, down});
        if(i + 1 < zero.size()) {
            int lo1 = zero[i + 1], hi1 = nxt[lo1] - 1;
            if(s[lo1 - 2] == '0') {
                ans = max(ans, down + cal_up(lo1, hi1));
            }
        }
    }
    cout << ans << "\n";
}

void out() {
    for(int i = 0; i < n; i++) {
        char o = s[i];
        s[i] = o == '1' ? '0' : '1';
        for(char c : s)
            cout << c << " ";
        cout << "\n";
        s[i] = o;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n >> s;
//        out();
        solve();
    }
}