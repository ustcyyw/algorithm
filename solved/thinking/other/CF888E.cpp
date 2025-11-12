/**
 * @Time : 2025/3/26-9:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF888E 1800 状态压缩 meet-in-the-middle算法
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15, mod = 1e9 + 7;
ll T = 1e9 + 10, n, m;
vector<int> arr1, arr2;

vector<ll> init(vector<int>& arr) {
    vector<ll> ans;
    for(int s = 0, t = arr.size(), full = (1 << t) - 1; s <= full; s++) {
        ll sum = 0;
        for(int i = 0; i < t; i++) {
            if((1 << i) & s)
                sum += arr[i];
        }
        ans.push_back(sum % m);
    }
    sort(ans.begin(), ans.end());
    return ans;
}

ll solve() {
    if(n == 1) return arr2.back() % m;
    vector<ll> aux1 = init(arr1), aux2 = init(arr2);
    ll ans = (aux1.back() + aux2.back()) % m;
    for(ll num : aux1) {
        ll t = *(--lower_bound(aux2.begin(), aux2.end(), m - num));
        ans = max(t + num, ans);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 0, num; i < n; i++) {
        cin >> num;
        if(i < n / 2) arr1.push_back(num);
        else arr2.push_back(num);
    }
    cout << solve();
}