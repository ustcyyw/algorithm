/**
 * @Time : 2024/11/13-9:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1932C 思维 正难则反 1400
 */
 /*
  * 正着做不断删除元素不好做 那反着来等价于不断增加乘法的因子
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m, nums[N];
string s;

void solve() {
    vector<int> ans, idx;
    for(int i = 1, j = n, k = 0; k < n; k++) {
        if(s[k] == 'L') idx.push_back(i++);
        else idx.push_back(j--);
    }
    int temp = 1;
    for(int i = n - 1; i >= 0; i--) {
        temp = temp * nums[idx[i]] % m;
        ans.push_back(temp);
    }
    for(int i = n - 1; i >= 0; i--)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cin >> s;
        solve();
    }
};