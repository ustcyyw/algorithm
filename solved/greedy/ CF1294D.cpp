/**
 * @Time : 2024/6/19-11:38 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1294D 贪心 数学
 */
 /*
  * 要尽可能得将没出现的小的数占住
  * 并且注意到加减x的操作 得到的一系列数 余数是相同的
  * 只需要考虑同余的一系列数中缺少的最小的那个即可。
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 4e5 + 5;
typedef long long ll;
int T, n, x, pick[N], lo = 0;
vector<int> arr[N];

void solve(int num) {
    int mod = num % x;
    vector<int>& temp = arr[mod];
    int nm = temp.empty() ? mod : temp.back() + x;
    if(nm < N) {
        temp.push_back(nm);
        pick[nm] = 1;
    }
    while(pick[lo]) lo++;
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> x;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        solve(num);
    }
};