/**
 * @Time : 2024/11/14-10:43 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1932E 数学 找规律 前缀和 1600
 */
 /*
  * 容易发现 答案就是不断把当前数相加后除以10 直到数变为0
  * 但是这样计算 大数的运算再加上数本身很大 超时
  * 考虑如何拆解
  * 以 12345 为例子
  * 用时 = 12345 + 1234 + 123 + 12 + 1
  * 1 * 1e4 + 1 * 1e3 + 1 * 1e2 + 1 * 10 + 1
  *           2 * 1e3 + 2 * 1e2 + 2 * 10 + 2
  *                     3 * 1e2 + 3 * 10 + 3
  *                               4 * 10 + 4
  *                                      + 5
  * 按位拆解 每个数位系数是前缀和
  * 然后倒着算 因为考虑进位
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 4e5 + 5;
int T, n, m, nums[N];
string s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> s;
        nums[0] = 0;
        for(int i = 1; i <= n; i++)
            nums[i] = nums[i - 1] + s[i - 1] - '0';
        for(int i = n, flag = 0; i >= 0; i--) {
            nums[i] += flag;
            flag = nums[i] / 10;
            nums[i] %= 10;
        }
        for(int i = 0, flag = 0; i <= n; i++) {
            if(nums[i] == 0 && !flag) continue; // 忽略前缀0
            flag = 1;
            cout << nums[i];
        }
        cout << "\n";
    }
};