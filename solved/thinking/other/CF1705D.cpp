/**
 * @Time : 2024/12/17-8:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1705D 1800 贪心 思维
 */
/*
  * 1. 位置1和n无法修改 所以这两个位置必须相同
  * 2. 将连续的1称为一个块，那么块的数量不会变换 只能通过操作变化位置及大小
  * 因此s能变成t的条件是 1、n两个位置本来就相等 并且块的数量一致
  * 找到最少的变换次数 就是分别找到s和t中块的位置及大小 依次一一对应
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int T, n;
string s, t;

vector<vector<int>> search(string& str) {
    vector<vector<int>> arr;
    for(int i = 0, j; i < n; i = j) {
        while(i < n && str[i] == '0') i++;
        j = i + 1;
        while(j < n && str[j] == '1') j++;
        if(i != n) arr.push_back({i, j - 1});
    }
    return arr;
}

ll solve() {
    if(s[0] != t[0] || s[n - 1] != t[n - 1]) return -1;
    vector<vector<int>> arr1 = search(s), arr2 = search(t);
    if(arr1.size() != arr2.size()) return -1;
    ll cnt = 0;
    for(int i = 0; i < arr1.size(); i++) {
        int lo1 = arr1[i][0], hi1 = arr1[i][1], lo2 = arr2[i][0], hi2 = arr2[i][1];
        cnt += abs(lo1 - lo2) + abs(hi1 - hi2);
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> s >> t;
        cout << solve() << "\n";
    }
};