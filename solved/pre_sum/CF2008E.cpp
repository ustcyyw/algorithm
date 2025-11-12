/**
 * @Time : 2024/10/25-3:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2008E 前缀和
 */
/*
  * 字符串长度是偶数 那直接按位统计即可 不能进行删除操作
  * 如果字符串长度是奇数 那必须使用一次删除操作
  * 1 2 3 4 5 6 7 8 9
  * 1 2 4 5 6 7 8 9
  * 奇数位置：前半段奇数 后半段偶数下标
  * 偶数位置：前半段偶数 后半段奇数下标
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n;
vector<vector<int>> even, odd;
string s;

void init(vector<vector<int>>& arr, int start) {
    for(int i = start; i <= n; i += 2) {
        for(int j = 0; j < 26; j++) {
            arr[i][j] = arr[i - 1][j] + (s[i] - 'a' == j);
            arr[i + 1][j] = arr[i][j];
        }
    }
}
// 计算指定范围内最少的操作次数 也就是找出现次数最多的字母 将其它字母变为他
int range1(vector<vector<int>>& arr, int lo, int hi) {
    if(hi == 0 || lo == n + 1) return 0;
    int total = (hi - lo + 1) / 2, val = -1;
    for(int j = 0; j < 26; j++)
        val = max(val, arr[hi][j] - arr[lo - 1][j]);
    return total - val;
}

void len_even() {
    int c1 = range1(odd, 1, n), c2 = range1(even, 1, n);
    cout << c1 + c2 << "\n";
}

int sum_of(vector<vector<int>>& arr, int lo, int hi, int j) {
    if(hi == 0 || lo == n + 1) return 0;
    return arr[hi][j] - arr[lo - 1][j];
}

void len_odd() {
    int ans = INT_MAX;
    for(int i = 1; i <= n; i++) {
        int lo1 = 1, hi1 = i - 1, lo2 = i + 1, hi2 = n;
        int c1 = -1, c2 = -1;
        for(int j = 0; j < 26; j++) {
            c1 = max(c1, sum_of(even, lo1, hi1, j) + sum_of(odd, lo2, hi2, j));
            c2 = max(c2, sum_of(odd, lo1, hi1, j) + sum_of(even, lo2, hi2, j));
        }
        ans = min(ans, n - (c1 + c2));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> s;
        s = '.' + s;
        even.assign(n + 5, vector(26, 0)), odd.assign(n + 5, vector(26, 0));
        init(even, 2), init(odd, 1);
        if(n % 2 == 0) len_even();
        else len_odd();
    }
};