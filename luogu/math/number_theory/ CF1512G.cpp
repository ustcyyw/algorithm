/**
 * @Time : 2024/7/9-7:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1512G
 */
 /*
  * 还是那个近似公式的运用
  * 1/1 + 1/2 + 1/3 + ... 1 / n = logn
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e7 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, sum[N], mp[N];

int init = []() -> int {
    for(int i = 1; i < N; i++) {
        for(int j = 1; j * i < N; j++)
            sum[j * i] += i;
    }
    for(int i = 1; i < N; i++) {
        if(sum[i] < N && mp[sum[i]] == 0)
            mp[sum[i]] = i;
    }
    return 0;
}();

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        int num;
        cin >> num;
        cout << (mp[num] == 0 ? -1 : mp[num]) << "\n";
    }
};