/**
 * @Time : 2024/3/13-9:10 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 相邻两个位置之间绝对值差为[2,4]
 * 如果第一个数排1，间隔为2排列 得到递增奇数序列
 * 还剩偶数序列 要和最大的奇数差距在[2,4]之间 可以将偶数序列倒叙排列
 * 这样最中间的两个元素会相差1 但是两个位置之间差可以为4
 * 也就是说交换偶数、奇数序列中任意两个相邻位置 仍然满足条件 所以尝试看是否能通过交换解决
 *
 * n = 8
 * 1 3 5 7 8 6 4 2 可以交换5和7, 1 3 7 5 8 6 4 2
 *
 * n = 10
 * 1 3 5 7 9 10 8 6 4 2 可以交换7 9, 1 3 5 9 7 10 8 6 4 2
 *
 * n = 7
 * 1 3 5 7 6 4 2, 1 3 5 7 4 6 2
 *
 * n = 9
 * 1 3 5 7 9 8 6 4 2, 1 3 5 7 9 6 8 4 2
 *
 * n为偶数，交换奇数序列最后两个数； n为奇数，交换偶数序列前两个数
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 1e3 + 5;
int T, n;

void solve() {
    if(n < 4) {
        cout << -1 << "\n";
        return;
    }
    int flag = n % 2 == 0, odd, even;
    if(flag) even = n, odd = n - 1;
    else even = n - 1, odd = n;
    for(int i = 1; i <= (flag ? odd - 4 : odd); i += 2)
        cout << i << " ";
    if(flag) cout << odd << " " << odd - 2 << " ";
    else cout << even - 2 << " " << even << " ";
    for(int i = (!flag ? even - 4 : even); i >= 2; i-= 2)
        cout << i << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        solve();
    }
};