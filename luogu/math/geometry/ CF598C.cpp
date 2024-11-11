/**
 * @Time : 2024/4/3-2:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const long double pi = 3.1415926535897932384626433832;
int T, n;
// 选择正方向是(0, 1)
long double get_angle(long double x, long double y) {
    long double t = atan2(x, y);
    return t >= 0 ? t : t + 2 * pi;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    vector<pair<long double, int>> arr;
    for(int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        arr.push_back({get_angle(x, y), i});
    }
    sort(arr.begin(), arr.end());
    int idx = n - 1;
    long double val = 2 * pi - arr[n - 1].first + arr[0].first;
    for(int i = 0; i < n - 1; i++) {
        long double cur = arr[i + 1].first - arr[i].first;
        if(cur < val) val = cur, idx = i;
    }
    if(idx == n - 1) cout << arr[idx].second << " " << arr[0].second;
    else cout << arr[idx].second << " " << arr[idx + 1].second;
};