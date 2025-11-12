/**
 * @Time : 2025/2/22-9:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF792B 1300 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5, M = 400;
int n, m, k, status[N];

void check(int& idx, int num) {
    num %= m;
    if(num > 0) idx = (idx + 1) % n;
    while(num > 0) {
        if(status[idx] == 0) num--;
        if(num > 0) idx = (idx + 1) % n;
    }
    status[idx] = -1;
    cout << idx + 1 << " ";
    while(status[idx] == -1)
        idx = (idx + 1) % n;
    m--;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n >> k;
    m = n;
    for(int i = 1, idx = 0, num; i <= k; i++) {
        cin >> num;
        check(idx, num);
    }
};