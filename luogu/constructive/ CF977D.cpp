/**
 * @Time : 2024/11/18-11:35 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF977D 构造 数学 1400
 */
 /*
  * 乘法操作 不会引入任何3的因子 从左到右3的因子一定是减少的
  * 如果因子中3的数量相同 那么这些数之间的链接通过*2操作完成 这个子集合第一个元素一定是其中最小的
  */

#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n;
map<int, set<ull>> mp;

int count(ull num) {
    int cnt = 0;
    while(num % 3 == 0) {
        num /= 3;
        cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    T = 1;
    while(T--) {
        cin >> n;
        ull num;
        for(int i = 1; i <= n; i++) {
            cin >> num;
            mp[count(num)].insert(num);
        }
        for(auto it = mp.rbegin(); it != mp.rend(); it++) {
            for(ull t : it->second)
                cout << t << " ";
        }
    }
};