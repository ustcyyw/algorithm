/**
 * @Time : 2023/12/30-11:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * a[i] * a[j] * a[k]最小 那一定是最小的三个数相乘
 * 最小的三个数中 有元素重复出现多次 才会出现多组
 */
#include<bits/stdc++.h>
using namespace std;

int n;
map<int, int> mp;
long long solve() {
    auto it = mp.begin();
    long long a = (*it++).second;
    if(a >= 3) return a * (a - 1) * (a - 2) / 6;
    long long b = (*it++).second;
    if(a + b >= 3) return a == 1 ? b * (b - 1) / 2 : b;
    return (*it).second;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        mp[num]++;
    }
    cout << solve() << endl;
}