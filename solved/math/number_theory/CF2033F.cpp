/**
 * @Time : 2024/11/28-9:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2033F 1800 数论 找规律
 */
 /*
  * 斐波那契数列模k形成的序列是周期性的，称为 Pisano周期。
  * 所以找到第一项模k为0的下标即可 后续都是周期性出现。
  * 因为arr[0] % k = 0，所以周期就是第一项的下标
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e6 + 5, mod = 1e9 + 7;
ll T, n, k, arr[N];

ll find(int num) {
    if(num == 1) return 1;
    for(int i = 3; i < N; i++) {
        arr[i] = (arr[i - 1] + arr[i - 2]) % num;
        if(arr[i] == 0) return i;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    arr[1] = arr[2] = 1;
    while(T--) {
        cin >> n >> k;
        ll t = find(k);
        cout << (n % mod * t) % mod <<"\n";
    };
};