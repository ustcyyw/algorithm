/**
 * @Time : 2024/9/26-10:11 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1883D
 */
 /*
  * 问的是存在 只要找到一组不相交的即可
  * 最有可能不相交的一组线段 一左一右
  * 左边那个的右端点尽可能小 他就不容易和别的线段产生交集
  * 右边那个的左端点尽可能大 他就不容易和别的线段产生交集
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n;
char type;
multiset<int> ls, rs;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1, l, r; i <= n; i++) {
            cin >> type >> l >> r;
            if(type == '+') ls.insert(l), rs.insert(r);
            else ls.erase(ls.find(l)), rs.erase(rs.find(r));
            if(ls.size() <= 1) cout << "NO\n";
            else {
                int maxL = *ls.rbegin(), minR = *rs.begin();
                if(minR < maxL) cout << "YES\n";
                else cout << "NO\n";
            }
        }
    }
};