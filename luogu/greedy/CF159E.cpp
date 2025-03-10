/**
 * @Time : 2025/3/9-10:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF159E 1700 贪心 排序 暴力枚举
 */
 /*
  * 最终答案中 一定有其中一种颜色是全部使用的
  * 所以可以枚举所有颜色 假设它是用完了的 一共有cnt个
  * 那么和它搭配的另外一种颜色 使用了cnt个或者cnt + 1个
  *
  * 预处理使用i个的最大长度 以及对应的颜色
  * 因为要使用两个颜色 避免重复选 要记录最大值、次大值和对应的颜色
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, P = 13331;
ll n, val1[N], val2[N], color1[N], color2[N], ans, c1, c2, t1, t2;
map<int, vector<vector<int>>> mp;
map<int, ll> c_sum;

void update(int c, int cnt, ll* color, ll* val) {
    if(color[cnt] != 0 && color[cnt] != c) {
        ll temp = c_sum[c] + val[cnt];
        if(temp > ans) {
            ans = temp;
            c1 = c, c2 = color[cnt];
            t1 = mp[c].size(), t2 = cnt;
        }
    }
}

void solve() {
    for(auto& p : mp) {
        int c = p.first, cnt = p.second.size();
        update(c, cnt, color1, val1);
        update(c, cnt, color2, val2);
        update(c, cnt + 1, color1, val1);
        update(c, cnt + 1, color2, val2);
    }
    cout << ans << "\n" << t1 + t2 << "\n";
    vector<vector<int>> arr1 = mp[c1], arr2 = mp[c2];
    for(int i = 0, j = 0; i < t1 || j < t2 ; i++, j++) {
        cout << arr2[j][1] << " ";
        if(i < t1) cout << arr1[i][1] << " ";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, c, s; i <= n; i++) {
        cin >> c >> s;
        mp[c].push_back({s, i});
    }
    for(auto& p : mp) {
        int c = p.first;
        vector<vector<int>>& aux = p.second;
        sort(aux.begin(), aux.end());
        reverse(aux.begin(), aux.end());
        ll sum = 0;
        for(int i = 1; i <= aux.size(); i++) {
            sum += aux[i - 1][0];
            if(sum > val1[i]) {
                val2[i] = val1[i], color2[i] = color1[i];
                val1[i] = sum, color1[i] = c;
            } else if(sum > val2[i])
                val2[i] = sum, color2[i] = c;
        }
        c_sum[c] = sum;
    }
    solve();
}