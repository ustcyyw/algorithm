/**
 * @Time : 2024/12/21-5:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1692H 1700 贪心 hashmap
 */
 /*
  * 选了[l,r]一共猜了 cnt = r - l + 1次 其中出现次数最多的数为 num, 一共出现了c次
  * 那么最后的结果是 2 ^ c / 2 ^ (cnt - c) = 2 ^ (2c - cnt)
  *
  * 枚举右端点i，该处的数字为num 并且是第ci次出现
  * 既让右端点是i，那么贡献答案的数字肯定是num，不然干脆不要这个右端点就好了
  * num 之前出现是 在j处 并且是第cj次出现
  * cnt = i - j + 1, c = ci - cj + 1
  * 2c - cnt = 2ci - 2cj + 2 - i + j - 1
  * = 2ci - i - (2cj - j) + 1
  * 所以应该记录每个num对应的2ci - i的最小值
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, nums[N];

void solve() {
    int a = nums[1], l = 1, r = 1, t = 1;
    map<int, int> mp, count, ls;
    for(int i = 1; i <= n; i++) {
        int num = nums[i];
        count[num]++;
        int temp = count[num] * 2 - i;
        if(mp.count(num)) {
            if(temp - mp[num] + 1 > t)
                t = temp - mp[num] + 1, a = num, l = ls[num], r = i;
            mp[num] = min(temp, mp[num]);
            if(temp == mp[num]) ls[num] = i;
        } else {
            mp[num] = temp;
            ls[num] = i;
        }
    }
    cout << a << " " << l << " " << r << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    };
};