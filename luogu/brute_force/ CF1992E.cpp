/**
 * @Time : 2024/7/16-9:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1992E 暴力枚举b和a
 */
 /*
  * b的取值范围最大1e4 且t <= 100 所以想到可以枚举b
  * 记n的数位长度为len
  * 首先有一个显然的限制 a * len > b 否则字符串表示形式计算时 不够移除后b个字符
  * 另外 a * len - b > 7 就意味着剩余的字符串表示的数字num > 1e6
  * 考虑到n最大为100 从数学计算的角度来看 a = (num + b) / n
  * 这会使得即便n最大 也让a超过了1e4
  * 因此在枚举b的情况下 再枚举a a的可能情况也就是最多7个
  * 枚举每一种情况都计算一下两种方式得出的结果是否矛盾 a b 是否在限制的范围内即可
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e4, mod = 1e9 + 7;
typedef long long ll;
int T, n, len, base[8];
vector<vector<int>> ans;

void init() {
    ans = {};
    string t = to_string(n);
    len = t.size();
    while(t.size() <= 7)
        t += t;
    for(int i = 1; i <= 7; i++)
        base[i] = stoi(t.substr(0, i));
}

void solve() {
    for(int b = 1; b <= N; b++) {
        for(int a = b / len + 1; a * len - b <= 7 && a <= N; a++) {
            int num = base[a * len - b], t = num + b;
            if(t % n == 0 && t / n == a && b <= a * n) {
                ans.push_back({a, b});
            }
        }
    }
    cout << ans.size() << "\n";
    for(auto& p : ans)
        cout << p[0] << " " << p[1] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        init();
        solve();
    }
};