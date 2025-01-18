/**
 * @Time : 2025/1/17-11:31 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1396B 1800 博弈
 */
/*
  * 只要有一堆石头 > 其它堆石头之和 那么先手一直拿这一堆石头就赢了
所以双方在过程中不会让某一堆石头特别多 都会想均匀地拿石头
一定会将所有石头都拿完 那么
有奇数个石头 先手方多拿一个 然后后手方没得拿就输了
有偶数个石头 双方拿一样多的 后手方最后一次拿了之后先手方就没有石头了
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n;

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n;
        int sum = 0, mv = -1;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            sum += num, mv = max(num, mv);
        }
        if(mv > sum - mv || sum % 2 == 1) cout << "T\n";
        else cout << "HL\n";
    }
};