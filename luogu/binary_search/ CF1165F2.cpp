/**
 * @Time : 2024/5/13-4:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1165F2 二分+贪心
 */
/*
 * 显然可以二分答案 固定最后一个购买日
 * 不能用优惠购买的 直接在最后一天集中购买
 * 同一种物品有多种优惠的 也可以在购买日期限内的最后一个优惠日考虑购买
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int n, m, k[N];
vector<int> days[N], nums;
vector<vector<int>> discount;
ll sum = 0;

void init(ll last_day) {
    nums.assign(n + 1, 0);
    for(int i = 1; i <= n; i++)
        nums[i] = k[i];
    discount.clear();
    for(int i = 1; i <= n; i++) {
        int d = -1;
        for(int idx : days[i]) {
            if(idx <= last_day) d = idx;
            else break;
        }
        if(d !=-1) discount.push_back({d, i});
    }
    sort(discount.begin(), discount.end());
}

bool check(ll last_day) {
    init(last_day);
    ll st = sum, money = 0;
    int pd = 0;
    for(auto& p : discount) {
        int day = p[0], type = p[1];
        if(day > last_day) break;
        money += day - pd;
        ll buy = min(money, (ll)nums[type]);
        money -= buy, st -= buy, nums[type] -= buy;
        pd = day;
    }
    money += last_day - pd;
    return money >= st * 2;
}

void solve() {
    sum = accumulate(k, k + n + 1, 0ll);
    for(int i = 1; i <= n; i++)
        sort(days[i].begin(), days[i].end());
    ll lo = 0, hi = (ll)sum * 2;
    while(lo < hi) {
        ll mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> k[i];
    for(int i = 1, t, d; i <= m; i++) {
        cin >> d >> t;
        days[t].push_back(d);
    }
    solve();
};