/**
 * @Time : 2024/6/14-10:33 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1702F 数学
 */
 /*
  * 只有bi/2这个操作才能得到奇数
  * 偶数可以通过除2操作得到 或者乘2操作
  * 但是可以考虑先把a转化为奇数 就是当ai%2 == 0时 ai /= 2
  * 然后将bi不断除以2，看看bi为奇数时 是否可以和某个aj对上
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 998244353;
typedef long long ll;
int T, n, b[N];
multiset<int> as;

int cal(int num) {
    while(num % 2 == 0) {
        num /= 2;
    }
    return num;
}

bool solve() {
    for(int i = 1; i <= n; i++) {
        int num = b[i];
        while(num != 0) {
            if(as.count(num)) {
                as.erase(as.find(num));
                break;
            }
            num /= 2;
        }
        if(num == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        as.clear();
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            as.insert(cal(num));
        }
        for(int i = 1; i <= n; i++)
            cin >> b[i];
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};