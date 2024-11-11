/**
 * @Time : 2023/12/7-8:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, k, q, arr[N], sum[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    memset(arr, 0, sizeof(arr)), memset(sum, 0, sizeof(sum));
    cin >> n >> k >> q;
    for(int i = 0, l, r; i < n; i++) {
        cin >> l >> r;
        arr[l]++, arr[r + 1]--;
    }
    for(int i = 1; i < N; i++) {
        arr[i] += arr[i - 1];
        sum[i] += sum[i - 1];
        if(arr[i] >= k) sum[i]++;
    }
    for(int i = 0, l, r; i < q; i++) {
        cin >> l >> r;
        cout << sum[r] - sum[l - 1] << "\n";
    }
}
