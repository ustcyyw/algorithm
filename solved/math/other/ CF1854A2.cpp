/**
 * @Time : 2023/12/30-10:00 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 如果所有数都是正数或者0
a[2] += a[1], a[3] += a[2], ... 最多19次操作就能让序列非递减
如果所有数都是负数
a[n-1] += a[n], a[n - 2] += a[n - 1] ... a[1] += a[2] 也是最多19次操作就能让序列非递减

但是数组中有正有负怎么办
是否可以转化为全正 或者 全负的情况

假设 max(a) > abs(min(a))，最大正数的绝对值大于等于最小负数的绝对值
对于任意一个数 一次操作就能将其变为非负
一个比较直观的想法是 如果正数比较多 就将其全变为正数，记负数的个数为cnt
变为非负后还需要19次操作，因此将数组变为非负还可以有12次操作
那么cnt <= 12，就可以将数组全变为正
否则 cnt >= 13 正数比较少 想办法将数组变为负
还有最多7个正数需要变 还剩余5次操作 这五次操作都做用在最小值自己相加（就是不断*2）
由于a[i] <= 20，那么最小值经过5次操作（2^5 = 32）其绝对值大于最大值
对于任意的正数，与之相加就变为负 因此可以将数组变为非负

如果 max(a) < abs(min(a))，则情况与之刚好相反
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 21;
int T, n, a[N];

void check(vector<int>& res) {
    for(int t = 0; t < res.size(); t += 2)
        a[res[t]] += a[res[t + 1]];
    cout << "check: " ;
    for(int i = 1; i <= n; i++)
        cout << a[i] << " ";
}

void solve(int i, int j, int cnt) {
    vector<int> res;
    int k = n - 1, flag = 0;
    if(a[j] >= 0) flag = 1;
    else if(a[i] <= 0) flag = 0;
        // 后面a[i] > 0 且 a[j] < 0
    else if(a[i] >= abs(a[j])) {
        flag = cnt <= 12;
        if(flag == 0) {
            k += 5;
            for(int t = 0; t < 5; t++) // 最小数自身相加
                res.push_back(j), res.push_back(j);
        }
    }
    else {
        flag = cnt <= 7; // 负数小于等于7，可以用5次操作用于最大数相加，然后将数组变为非负
        if(flag) {
            k += 5;
            for(int t = 0; t < 5; t++) // 最大数自身相加
                res.push_back(i), res.push_back(i);
        }
    }
    if(flag) {
        for(int t = 1; t <= n; t++)
            if(a[t] < 0) res.push_back(t), res.push_back(i), k++;
        for(int t = 2; t <= n; t++)
            res.push_back(t), res.push_back(t - 1);
    } else {
        for(int t = 1; t <= n; t++)
            if(a[t] > 0) res.push_back(t), res.push_back(j), k++;
        for(int t = n; t >= 2; t--)
            res.push_back(t - 1), res.push_back(t);
    }
    cout << k << endl;
    for(int t = 0; t < res.size(); t += 2)
        cout << res[t] << " " << res[t + 1] << endl;
//    check(res);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        int cnt = 0, i1 = 1, i2 = 1; // i1记录最小值
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            if(a[i] > a[i1]) i1 = i;
            if(a[i] < a[i2]) i2 = i;
            if(a[i] < 0) cnt++;
        }
        solve(i1, i2, cnt);
    }
}