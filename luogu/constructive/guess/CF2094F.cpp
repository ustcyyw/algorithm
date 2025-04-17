/**
 * @Time : 2025/4/16-11:00 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2094F 1597 构造算法 猜结论
 */
 /*
  * 如果m不能被k整除，从上到下从左到右 顺着放数即可
  * 否则 就第一行从1开始顺着放数 第二行则从2开始顺着放数 刚好能错开
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 15, M = 30;
int T, n, m, k;

void solve1() {
    for(int i = 1, num = 0; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cout << num + 1 << " ";
            num = (num + 1) % k;
        }
        cout << "\n";
    }
}

void solve2() {
    for(int i = 1; i <= n; i++) {
        int num = i % 2;
        for(int j = 1; j <= m; j++) {
            cout << num + 1 << " ";
            num = (num + 1) % k;
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> k;
        if(m % k == 0) solve2();
        else solve1();
    }
}