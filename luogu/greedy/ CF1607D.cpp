/**
 * @Time : 2024/7/18-9:39 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1607D
 */
/*
  * 蓝色 -1    红色 + 1
  * 蓝色 > 红色 这两位置的数一定可以互换值 因此蓝色和红色都不必保持不变
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e6 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, nums[N];
string s;

bool check_red(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    for(int m = arr.size(), i = m - 1, j = n; i >= 0; j--, i--) {
        if(arr[i] > j) return false;
    }
    return true;
}

bool check_blue(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    for(int m = arr.size(), i = 0, j = 1; i < m; j++, i++) {
        if(arr[i] < j) return false;
    }
    return true;
}

void solve() {
    vector<int> blue, red;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'B') blue.push_back(nums[i]);
        else red.push_back(nums[i]);
    }
    if(check_blue(blue) && check_red(red)) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> nums[i];
        cin >> s;
        solve();
    }
};