/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
 /*
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        vector<vector<int>> pos;
        pos.push_back({1, 1});
        pos.push_back({n, n});
        if(n > 2) pos.push_back({n, n - 1});
        for(int i = 3; i <= n - 1; i++)
            pos.push_back({1, i});
        for(auto& p : pos)
            cout << p[0] << " " << p[1] << "\n";
        cout << "\n";
    }
};