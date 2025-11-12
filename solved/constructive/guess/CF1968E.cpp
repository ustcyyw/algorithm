/**
 * @Time : 2024/12/9-9:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1968E 1600 构造 猜结论
 */
 /*
  * 通过test case发现 总能凑够0～2n-2的所有距离
  * 0这个和自身算出来的距离先不管
  * 要凑出2n-2，必须选(1,1), (n,n)
  * 然后凑2n-3，可以选(1,2)也可以选(n,n-1) 假设选了(n,n-1)
  * 选了(n,n-1)也就同时有了1
  * 接下来考虑凑2n-4 由于右下角已经有两个点了 再挨着右下角选会出现重复的距离1
  * 于是选第一行的(1,3) 同时也有了2和2n-5
  * 接下来发现顺着第一行一直选到(1,n-1)
  * 这一系列的点能和(1,1)依次得到3...n-2
  * 能和右下角的(n,n-1)依次得到2n-6...n-1 就凑齐了所有距离
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