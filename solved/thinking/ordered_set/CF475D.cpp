/**
 * @Time : 2025/11/12-17:19
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF475D 2000(老题虚高) 有序集合
 */
/*
  * 有序集合处理gcd问题
  * 集合中二元组为 <gcd值, 该gcd值对应的子数组数目>
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, q, nums[N];
map<int, ll> mp;

void solve() {
    vector<vector<int>> arr;
    // 枚举子数组的左端点
    for(int i = n; i >= 1; i--) {
        int k = 0, num = nums[i];
        arr.push_back({num, 1});
        arr[0][0] = gcd(arr[0][0], num);
        for(int j = 1; j < arr.size(); j++) {
            arr[j][0] = gcd(arr[j][0], num);
            if(arr[j][0] == arr[k][0]) arr[k][1] += arr[j][1];
            else arr[++k] = arr[j];
        }
        arr.resize(k + 1);
        for(auto& p : arr)
            mp[p[0]] += p[1];
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
        cin >> q;
        for(int i = 1, num; i <= q; i++) {
            cin >> num;
            cout << mp[num] << "\n";
        }
    }
}