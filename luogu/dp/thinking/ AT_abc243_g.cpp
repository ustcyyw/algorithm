/**
 * @Time : 2023/12/20-8:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 1.第一位放的数为x，那么第二位可选的数为[1, floor(sqrt(x))]
 * 如 x = 9999, 那么第二位可选的数为[1, 99]
 * 如果第二位选99，那么第三位的可选范围是[1,9]
 * 如果第二位选98，那么第三位的可选范围是[1,9]
 * ...
 * 直到第二位选80，那么第三位可选的范围是[1,8]
 * 2.于是可以发现 在选择数的时候 有很多数的后置序列一致 是以完全平方数为分隔的
 * 也就是说 选择数只需要枚举完全平方数
 * 并且x 与 floor(sqrt(x)) * floor(sqrt(x))的方案数一致
 * 3.直到某一位选择了1，后面就是唯一确定的 全为1
 *
 * 可以记忆化搜索
 */

#include<bits/stdc++.h>
typedef unsigned long long ull;
using namespace std;
int T;
ull X;
unordered_map<ull, ull> cache;

ull format(ull num) {
    ull t = (ull)sqrt((long double)num);
    return t * t;
}

ull dfs(ull num) {
    num = format(num);
    if(cache.count(num)) return cache[num];
    ull cnt = 0, x2 = (ull)sqrt((long double)num);
    for(ull pre = x2, x = (ull)sqrt((long double)x2); x > 0; pre = x * x - 1, x--) {
        cnt += (pre - x * x + 1) * dfs(x * x);
    }
    cache[num] = cnt;
    return cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cache[1] = 1;
    cin >> T;
    while(T-- > 0) {
        cin >> X;
        cout << dfs(X) << endl;
    }
}