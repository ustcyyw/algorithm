/**
 * @Time : 2024/4/5-9:19 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 2e5 + 5;
int T, n, m, k, s, money1[N], day1[N], money2[N], day2[N], m1, m2;
vector<vector<int>> p1, p2;
ll sum1[N] = {0}, sum2[N] = {0};

void product_f(ll* sum, vector<vector<int>>& p, int mi) {
    sort(p.begin(), p.end());
    for(int i = 1; i <= mi; i++)
        sum[i] = sum[i - 1] + p[i][0];
}

void money_in(int* money, int* day) {
    for(int i = 1, cost; i <= n; i++) {
        cin >> cost;
        if(cost < money[i - 1]) day[i] = i;
        else day[i] = day[i - 1];
        money[i] = min(cost, money[i - 1]);
    }
}

vector<int> check(int day) {
    int cost1 = money1[day], cost2 = money2[day]; // 两种花销的最小消费
    for(int i = 0, j = m2; i <= m1; i++) { // 枚举美元购买的商品
        ll s1 = sum1[i] * cost1;
        while(j >= 0 && sum2[j] * cost2 + s1 > s) j--;
        if(j != -1 && i + j >= k) return {i, j};
    }
    return {-1, -1};
}

void solve() {
    int lo = 1, hi = n + 1;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid)[0] != -1) hi = mid;
        else lo = mid + 1;
    }
    if(lo == n + 1) {
        cout << -1;
        return;
    }
    cout << lo << "\n";
    vector<int> info = check(lo);
    int i = 1, j = 1, it = info[0], d1 = day1[lo], d2 = day2[lo];
    while(k-- > 0) {
        if(i <= it) cout << p1[i++][1] << " " << d1 << "\n";
        else cout << p2[j++][1] << " " << d2 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k >> s;
    money1[0] = money2[0] = INT_MAX;
    money_in(money1, day1), money_in(money2, day2);

    p1.push_back({-1, -1}), p2.push_back({-1, -1});
    for(int i = 1, type, money; i <= m; i++) {
        cin >> type >> money;
        if(type == 1) p1.push_back({money, i}), m1++;
        else p2.push_back({money, i}), m2++;
    }
    product_f(sum1, p1, m1), product_f(sum2, p2, m2);
    solve();
};