/**
 * @Time : 2024/7/29-1:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1660D
 */
 /*
  * 空️数组为1 因此含有0的得都删掉 并且要让保留下的数组是正数 带负号的数有偶数个 并且尽可能让2多一些
  * 两个0中间的子数组是一个可以进行进一步删减的子数组
  * 负号要么有偶数个 要么有奇数个
  * 是奇数个的情况 得删掉一个 自然是要么左边删掉第一个 要么右边删掉第一个
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, arr[N], cnt2, l, r, sum[N], sum2[N];

void cal(int lo, int hi) {
    int i = lo, j = hi;
    while((sum[j] - sum[i - 1]) % 2 != 0) i++;
    if(sum2[j] - sum2[i - 1] > cnt2) {
        cnt2 = sum2[j] - sum2[i - 1];
        l = i - 1, r = n - j;
    }
    i = lo, j = hi;
    while((sum[j] - sum[i - 1]) % 2 != 0) j--;
    if(sum2[j] - sum2[i - 1] > cnt2) {
        cnt2 = sum2[j] - sum2[i - 1];
        l = i - 1, r = n - j;
    }
}

void solve() {
    cnt2 = 0, l = n, r = 0;
    for(int i = 0, j; i <= n; ) {
        j = i + 1;
        while(j <= n && arr[j] != 0) j++;
        cal(i + 1, j - 1);
        i = j;
    }
    cout << l << " " << r << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            arr[i] = num;
            sum[i] = sum[i - 1] + (num < 0);
            sum2[i] = sum2[i - 1] + (abs(num) == 2);
        }
        arr[n + 1] = 0;
        solve();
    }
};