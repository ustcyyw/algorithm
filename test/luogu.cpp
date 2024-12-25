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
const int N = 2e5 + 5;
int T, n, k, nums[N], arr[N];

void solve() {
    sort(arr + 1, arr + n + 1);
    int m = (n + k + 1) / 2, diff = INT_MAX, x, y;
    for(int i = 1, j = i + m - 1; j <= n; i++, j++) {
        int temp = arr[j] - arr[i];
        if(diff > temp)
            diff = temp, x = arr[i], y = arr[j];
    }
    cout << x << " " << y << "\n";
    int i = 1, j, cnt;
    while(k > 1) {
        j = i, cnt = 0;
        while(j <= n && cnt < 1) {
            cnt += nums[j] >= x && nums[j] <= y ? 1 : -1;
            j++;
        }
        cout << i << " " << j - 1 << "\n";
        k--, i = j;
    }
    cout << i << " " << n << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            arr[i] = nums[i];
        }
        solve();
    }
};