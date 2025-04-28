/**
 * @Time : 2025/4/27-10:27 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1027C 1600 数学 几何 贪心
 */
 /*
  * 周长一定时，越接近正方形 面积越大
  * 所以要找尽可能接近正方形的矩形
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, mod = 998244353;
int T, n, nums[N];
map<int, int> cnt;

vector<int> find() {
    vector<int> arr;
    for(auto& [v, c] : cnt) {
        if(c >= 4) return {v, v};
        if(c >= 2)  arr.push_back(v);
    }
    int l1 = -1, l2 = -1;
    ld val = INT_MAX;
    for(int i = 0; i < arr.size() - 1; i++) {
        ll p = 2 * (arr[i] + arr[i + 1]), s = arr[i] * arr[i + 1];
        ld temp = (ld)1.0 * p * p / s;
        if(temp < val) {
            val = temp;
            l1 = arr[i], l2 = arr[i + 1];
        }
    }
    return {l1, l2};
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        cnt = {};
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            cnt[nums[i]]++;
        }
        vector<int> arr = find();
        cout << arr[0] << " " << arr[0] << " " <<arr[1] << " " << arr[1] << "\n";
    }
}