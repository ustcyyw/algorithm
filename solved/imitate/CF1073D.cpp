/**
 * @Time : 2025/5/21-4:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1073D 1700 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 5, mod = 998244353;
ll T, n, t, sum, temp;
vector<int> nums;

void change() {
    temp = t, sum = 0;
    vector<int> aux;
    for(int num : nums) {
        if(temp >= num) {
            temp -= num, sum += num;
            aux.push_back(num);
        }
    }
    swap(aux, nums);
}

void solve() {
    ll ans = 0;
    while(!nums.empty()) {
        if(t >= sum) {
            ll cnt = t / sum;
            ans += cnt * nums.size();
            t -= cnt * sum;
        }
        change();
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//    cin >> T;
    cin >> n >> t;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        sum += num;
        nums.push_back(num);
    }
    solve();
}