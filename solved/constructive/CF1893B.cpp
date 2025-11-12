/**
 * @Time : 2024/5/30-10:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1893B 构造 dp
 */
 /*
  * b可以以任意顺序插入 那么将b降序排列
  * 并且保持这个相对顺序 保证至少b本身不制造任何递增序列
  *
  * 然后先考虑a原本的最长递增序列 其长度为ml 并且是以元素 last1, last2 .. last_i .. last_x结尾
  * 这一步可以使用dp来计算
  * 对于b中的当前元素b[j] > last_i
  * 如果将b[j]放在last_i的右边 那么lis长度+1
  * 所以要将b[j]放在last_i的左边 这样至少以last_i结尾的lis长度不变
  * 而last_i右边存在last_t > b[j]也只是让以last_t结尾的lis长度+1
  * 如果不存在 lis的长度保持不变
  * 因此发现 只要b[j] > last_i就将b[j]放在last_i左边至少不会更坏
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, len[N], a[N], b[N];

void solve() {
    sort(b + 1, b + m + 1);
    vector<int> dp; // dp[i]:长度为i的递增序列尾元素的最小值
    dp.push_back(a[1]), len[1] = 1;
    for(int i = 2; i <= n; i++) {
        int num = a[i], lo = 0, hi = dp.size();
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            if(dp[mid] >= num) hi = mid;
            else lo = mid + 1;
        }
        if(lo == dp.size()) dp.push_back(num);
        else dp[lo] = num;
        len[i] = lo + 1;
    }
    int ml = dp.size(), j = m;
    for(int i = 1; i <= n; i++) {
        while(len[i] == ml && j >= 1 && a[i] <= b[j]) {
            cout << b[j--] << " ";
        }
        cout << a[i] << " ";
    }
    while(j >= 1)
        cout << b[j--] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= m; i++)
            cin >> b[i];
        solve();
    }
};