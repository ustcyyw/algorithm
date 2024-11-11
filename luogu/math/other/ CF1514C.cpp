/**
 * @Time : 2024/3/16-5:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 1个数学结论：假设有一个数num与mod，gcd(num, mod) = x > 1，那么 num * y % mod的值是x的倍数
  * 即 0，x, 2x ...
  *
  * 本题要求最终对n取模为1，那么根据结论 所选的因子都要和x互质
  * 考虑将所有与n互质的数取出相乘 乘积为mul与n互质
  * 记 k = mul % n，如果 k != 1 说明相乘的过程中多选了一个数k
  * 将这个数去掉, 就会有mul % n = 1
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int T = 2e5, N = 1e5 + 5;
int n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    vector<int> arr;
    ll mul = 1;
    for(int i = 1; i < n; i++) {
        if(gcd(i, n) == 1) {
            arr.push_back(i);
            mul = mul * i % n;
        }
    }
    int k = mul % n;
    if(k != 1) cout << arr.size() - 1 << "\n";
    else cout << arr.size() << "\n";
    for(int num : arr) {
        if(num != 1 && num == k) continue;
        cout << num << " ";
    }
};