/**
 * @Time : 2024/4/8-5:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 要计算 (n - i) * abs(di + i - n)
 * 贪心地想 i 越小 就让 abs(di + i - n) 越小
 * i = 1，就让abs(di + 1 - n)为0，就是 d1 = n - 1
 * i = 2，也类似 d2 = n - 2
 * ...
 * 然后发现总是可以让 di = n - i 让每一项都为0
 * 除了i = n的情况，但此时 n - i = 0，因此两个n可以放在任意位置补齐空位
 *
 * 具体做法就是将前n个位置（索引[0,n-1]）用于安排 1、3、5等奇数
 * 相差为2的两个数字 刚好其d也相差2，因此最外面安排了1之后，次外层就能安排3
 * 然后再内一层安排5...
 * 将索引[n, 2n - 2]用于安排 2、4、6等偶数
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 1e6 + 5;
int n, k, m, nums[N] = {0};

void fill(int lo, int hi) {
    while(lo < hi) {
        int d = hi - lo, num = n - d;
        nums[lo++] = num, nums[hi--] = num;
    }
}

void solve() {
    fill(0, n - 1);
    fill(n, 2 * n - 2);
    for(int i = 0; i < 2 * n; i++) {
        if(nums[i] != 0) cout << nums[i];
        else cout << n;
        cout << " ";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    solve();
};