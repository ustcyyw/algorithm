/**
 * @Time : 2024/12/2-8:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1922E 1800 构造 位运算
 */
/*
  * 总的上升子序列数量和 x = sum { 以数字nums[i]结尾的上升子序列数量 }
  * 相当于用有限的数凑出一个固定数 联想到lca到做法 用二进制来凑出确定的距离
  * 这题是否可以通过二进制的方式凑出x
  * 考虑序列 0 1 2 3。发现以这些数结尾的上升子序列数量1 2 4 8刚好对应二进制的一位
  * 那么对于x，通过1 2 4 8 ... 这样的累加 最后再加1，就能凑出最高位的1
  * 第二部分 凑其它低位的1，再从高到低选数即可。
  * 从高到低的理由是，这样后选的数 不会因为第二部分选的数得到更多上升子序列
  * 只能因为第一部分选的数得到上升子序列，从而保证这个数量是二进制的某一位
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
ll T, n, x;
vector<int> ans;

void solve() {
    int idx = -1;
    for(int i = 0; i < 63; i++) {
        if((1ll << i) & x) idx = i;
    }
    for(int i = 0; i < idx; i++)
        ans.push_back(i);
    for(int i = idx - 1; i >= 0; i--) {
        if((1ll << i) & x)
            ans.push_back(i);
    }
    ans.push_back(0); // 凑出最高位的1
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> x;
        x--, ans = {}; // x--是扣除空序列
        solve();
        cout << ans.size() << "\n";
        for(int num : ans)
            cout << num << " ";
        cout << "\n";
    };
};