/**
 * @Time : 2024/11/22-10:05 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1196C 正难则反 1500
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e5;
int T, n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        int left = -N, right = N, up = -N, down = N;
        for(int i = 1, x, y, f1, f2, f3, f4; i <= n; i++) {
            cin >> x >> y >> f1 >> f2 >> f3 >> f4;
            if(f1 == 0) up = max(x, up); // 只能向下走
            if(f2 == 0) right = min(right, y);
            if(f3 == 0) down = min(x, down); // 只能往上
            if(f4 == 0) left = max(left, y); // 只能向右走
        }
        if(left <= right && up <= down) cout << 1 << " " << up << " " << left;
        else cout << 0;
        cout << "\n";
    }
};