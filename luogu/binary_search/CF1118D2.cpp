/**
 * @Time : 2024/5/6-10:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 二分 + 贪心
 */
 /*
  * 答案具有二分性 二分最后喝完的天数x
  * 问题的关键在于 咖啡的功效 max(a - j, 0) 其中j是当天喝的第j杯
  * 所以在某一天内应该先喝a值大的，这样咖啡功效 - j <= 0后将不再损失
  * 并且n杯咖啡应该均匀分在x天的每一天来喝
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, total, nums[N];

bool check(int x) {
    ll sum = 0;
    for(int i = n, j = 0; i >= 1; j++) {
        // x天 每天喝的第j杯咖啡
        for(int k = 0; k < x && i >= 1; k++, i--) {
            sum += max(0, nums[i] - j);
            if(sum >= total) return true;
        }
    }
    return false;
}

void solve() {
    int lo = 1, hi = n + 1;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << (lo == n + 1 ? -1 : lo);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> total;
    for(int i = 1, num; i <= n; i++)
        cin >> nums[i];
    sort(nums, nums + n + 1);
    solve();
};