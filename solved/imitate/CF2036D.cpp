/**
 * @Time : 2024/11/21-1:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2036D 模拟 1300
 */

#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e3 + 5, M = 1000000;
int T, n, m;
string area[N];

int cal(vector<char>& arr) {
    int cnt = 0;
    for(int i = 0, len = arr.size(); i < len; i++) {
        if(arr[i] == '1' && arr[(i + 1) % len] == '5' &&
           arr[(i + 2) % len] == '4' && arr[(i + 3) % len] == '3')
            cnt++;
    }
    return cnt;
}

void solve() {
    int left = 0, right = m - 1, up = 0, down = n - 1, cnt = 0;
    while(left < right && up < down) {
        vector<char> arr;
        for(int i = left; i <= right; i++)
            arr.push_back(area[up][i]);
        up++;
        for(int i = up; i <= down; i++)
            arr.push_back(area[i][right]);
        right--;
        for(int i = right; i >= left; i--)
            arr.push_back(area[down][i]);
        down--;
        for(int i = down; i >= up; i--)
            arr.push_back(area[i][left]);
        left++;
        cnt += cal(arr);
    }
    cout << cnt << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T--) {
        cin >> n >> m;
        for(int i = 0; i < n; i++)
            cin >> area[i];
        solve();
    }
};