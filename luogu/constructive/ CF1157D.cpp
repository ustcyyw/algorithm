/**
 * @Time : 2024/5/11-10:28 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1157D 构造+数学
 */
/*
 * 一个满足条件的最小的序列是 首项为1 公差为1的等差数列
 * 其和为 s_min = k * (k + 1) / 2, 如果s_min > n 那么没办法完成构造
 *
 * 如果首项是a 但是是公差为1的等差数列 sum = (2a + k - 1) * k / 2
 * 如果令 sum = n, 求出 a = (2 * n / k + 1 - k) / 2， 向下取整
 * 这样的等差数列 满足前两个条件 且和很接近n，但是sum <= n
 * 还需要向数列的项增加 n - sum的数值。
 * 如果从数列后面向前 给每一项依次+1，在满足 a[i] <= 2 * a[i - 1] 尽可能增加n - sum的数值
 * 可以完成这个过程 则构造成功 否则失败
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
ll n, k, nums[N];

bool build() {
    ll a = (ll)((2.0 * n / k + 1 - k) / 2);
    if(a <= 0) return false; // 说明最小的序列 首项为1 公差为1的等差数列之和都大于n了
    for(int i = 0; i < k; i++)
        nums[i] = a + i;
    ll need = n - (2 * a + k - 1) * k / 2;
    while(need > 0) {
        if(nums[k - 1] + 1 > nums[k - 2] * 2) return false;
        for(int i = k - 1; i >= 0 && need > 0; i--) {
            if(nums[i] + 1 <= nums[i - 1] * 2)
                nums[i]++, need--;
            else break;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    if(!build()) {
        cout << "NO";
    } else {
        cout << "YES\n";
        for(int i = 0; i < k; i++)
            cout << nums[i] << " ";
    }
};