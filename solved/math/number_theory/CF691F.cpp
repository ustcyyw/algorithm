/**
 * @Time : 2025/2/17-9:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF691F 2200 数学 调和级数 差分算法 （卡常！一定要用快读）
 */
 /*
  * 对于给定的p 就是看有多少组数对(ai, aj) 满足 j != i 并且 ai * aj >= p
  * 先将a排序 枚举ai和aj，对于一组特定的ai, aj，所有的 p <= ai * aj，这组数对p都有贡献
  * ai = 1, aj 从2枚举到T
  * ai = 2, aj 从3枚举到T/2
  * ai = 3, aj 从4枚举到T/3
  * ai = 4, aj 从5枚举到T/4
  * ai * aj > T 就没必要继续枚举j了，因此后续的j 大于任何一个p的值
  * 直接将后续所有数对计数即可
  * T次计算 + T/2次计算 + T/3次计算 + ..
  * T(1 + 1/2 + 1/3 + ... + 1/T)
  * 调和级数求和
  * 用调和级数求和计算时间复杂度的时候 还要注意先统计，不然所有的ai都为1的时候 就超时了
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, M = 3e6 + 5, mod = 1e9 + 7;
ll T, n, m, val[M], ans[M], p[M], sum[N];
vector<vector<int>> arr;
map<int, int> mp;

#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

void solve() {
    for(int i = 0, sz = arr.size(); i < sz; i++) {
        ll num1 = arr[i][0], c1 = arr[i][1];
        val[1] += c1 * (c1 - 1);
        if(num1 * num1 + 1 < M) val[num1 * num1 + 1] -= c1 * (c1 - 1);
        for(int j = i + 1; j < sz; j++) {
            ll num2 = arr[j][0], c2 = arr[j][1];
            if(num1 * num2 + 1 >= M) {
                val[1] += 2 * c1 * sum[j];
                break;
            } else {
                val[1] += 2 * c1 * c2;
                val[num1 * num2 + 1] -= 2 * c1 * c2;
            }
        }
    }
    for(ll i = 1, s = 0; i < M; i++) {
        s += val[i];
        ans[i] = s;
    }
    for(int i = 1; i <= m; i++)
        cout << ans[p[i]] << "\n";
}

int main() {
//    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        n = read();
        for(int i = 1, num; i <= n; i++) {
            num = read();
            mp[num]++;
        }
        m = read();
        for(int i = 1; i <= m; i++)
            p[i]= read();
        for(auto& [num, c] : mp)
            arr.push_back({num, c});
        for(int i = arr.size() - 1; i >= 0; i--)
            sum[i] = sum[i + 1] + arr[i][1];
        solve();
    }
};