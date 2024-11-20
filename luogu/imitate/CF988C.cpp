/**
 * @Time : 2024/11/19-10:44 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF988C 模拟 hash表简单运用 1400
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, k, nums[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    T = 1;
    while(T--) {
        cin >> k;
        map<ll, vector<int>> mp;
        for(int i = 1; i <= k; i++) {
            cin >> n;
            ll sum = 0;
            for(int j = 1; j <= n; j++) {
                cin >> nums[j];
                sum += nums[j];
            }
            map<ll, vector<int>> aux;
            for(int j = 1; j <= n; j++) {
                ll key = sum - nums[j];
                aux[key] = {i, j};
                if(mp.count(key)) {
                    cout << "YES\n" << mp[key][0] << " " << mp[key][1] << "\n";
                    cout << i << " " << j;
                    return 0;
                }
            }
            for(auto& p : aux)
                mp[p.first] = p.second;
        }
        cout << "NO";
    }
};