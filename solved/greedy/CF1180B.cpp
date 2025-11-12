/**
 * @Time : 2023/12/8-4:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 一个数最多操作一次 两次就会变成原来的数
 * 正数：会将其绝对值变大 但变为负数; 负数：会将其绝对值变小 但变为正数
 * 如果考虑乘积的绝对值最大 那应该将所有正数变负数
 * 然后考虑将其变为正数
 * 1.如果数组长度是偶数，那么就有偶数个负数相乘 不用改
 * 2.如果数组长度是奇数，那么就调整一个数变为正 其它不改
 *
 * 假设有两个数相乘 a < b 只考虑绝对值
 * a * (b - 1) - (a - 1) * b = b - a > 0
 * 应该调整绝对值大的数 更利于乘积的绝对值大
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, arr[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    int v = -1e9, index = 0;
    for(int i = 0, num; i < n; i++) {
        cin >> num;
        arr[i] = num >= 0 ? -num - 1 : num;
        if(abs(arr[i]) > v) {
            v = abs(arr[i]);
            index = i;
        }
    }
    if(n % 2 == 1) arr[index] = -arr[index] - 1;
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
}