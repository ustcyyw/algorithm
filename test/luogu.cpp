/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e6, mod = 1e9 + 7, R = 26;
int T, n, c, nums[N];
set<ll> pickL, pickR, rv;

ll init() {
    vector<vector<int>> arr;
    for(int i = 1; i <= n; i++)
        arr.push_back({nums[i] + i, i});
    sort(arr.begin(), arr.end());
    for(ll i = 0, sum = 0; i < n; i++) {
        if(sum + arr[i][0] > c) return sum;
        sum += arr[i][0];
        pickL.insert((ll)arr[i][0] * N + arr[i][1]);
    }
    return -1;
}

void addToRight(ll& sum, ll vc, ll val) {
    sum += val;
    pickR.insert(vc), rv.erase(vc);
}

ll solve() {
    ll sum = init();
    if(pickL.size() == n || pickL.empty()) return pickL.size();
    int ans = pickL.size();
    for(int i = n; i >= 1 && !pickL.empty(); i--) {
        ll key = (ll)(nums[i] + i) * N + i;
        if(pickL.count(key)) {
            pickL.erase(key);
            sum -= nums[i] + i;
        }
        rv.insert((ll)(nums[i] + n + 1 - i) * N + i);
        // 将右边备选的最小值和左边、右边已经选择的进行比较
        while(!rv.empty()) {
            ll cnt = rv.size(), vc = *rv.begin(), val = vc / N;
            if(sum + val <= c) {
                addToRight(sum, vc, val);
                continue;
            }
            if(pickL.empty() && pickR.empty()) {
                if(val <= c) addToRight(sum, vc, val);
                else break;
            } else if(!pickL.empty() && !pickR.empty()) {
                ll vl = *pickL.rbegin(), vr = *pickR.rbegin();
                if(vc < max(vl, vr)) addToRight(sum, vc, val);
                if(vl >= vr && vl > vc) {
                    pickL.erase(vl), sum -= vl / N;
                } else if(vr > vl && vr > vc)
                    pickR.erase(vr), sum -= vr / N;
            } else if(!pickL.empty()) {
                ll vl = *pickL.rbegin();
                if(vl > vc) {
                    pickL.erase(vl), sum -= vl / N;
                    addToRight(sum, vc, val);
                }
            } else {
                ll vr = *pickR.rbegin();
                if(vr > vc) {
                    pickR.erase(vr), sum -= vr / N;
                    addToRight(sum, vc, val);
                }
            }
            if(cnt == rv.size()) break;
        }
        ans = max(ans, (int)(pickL.size() + pickR.size()));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n >> c;
        pickL = {}, pickR = {}, rv = {};
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << solve() << "\n";
    }
};