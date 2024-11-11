/**
 * @Time : 2024/2/1-11:29 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 最大值记为maxV 最小值为minV； 前缀和为s
 * 如果s >= 0 找一个非正数添加到序列
 * 如果s < 0 找一个正数添加到序列
 * 因为nums的数组和为0，因此 s >= 0 时 必然还存在非正数；s < 0时 必然还存在正数
 * 在序列没有构造完成之前 上述取数方式一直可以进行
 *
 * 每次添加数
 * 1. s >= 0，加上一个非正数a， s + a >= minV
 * 2. s < 0，加上一个正数b， s + b < maxV
 *
 * 子数组的和 = s1 - s2
 * 极端情况下s2取下限minV，但s1的上限 < maxV，因此 abs(s1 - s2) < maxV - minV
 * 正确性得到保证
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 3e5 + 5;
int T, n, maxV, minV, nums[N];
vector<int> pos, neg;

void solve() {
    int diff = maxV - minV;
    for(int i = 0; i < n; i++) {
        if(abs(nums[i]) >= diff) {
            cout << "No" << "\n";
            return;
        }
    }
    long long sum = 0;
    int m1 = pos.size(), m2 = neg.size();
    for(int i = 0, j = 0, k = 0; k < n; ) {
        if(i == m1)  sum += neg[j], nums[k++] = neg[j++];
        else if(j == m2) sum += pos[i], nums[k++] = pos[i++];
        else if(sum >= 0)
            sum += neg[j], nums[k++] = neg[j++];
        else
            sum += pos[i], nums[k++] = pos[i++];
    }
    cout << "Yes" << "\n";
    for(int i = 0; i < n; i++)
        cout << nums[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        maxV = INT_MIN, minV = INT_MAX;
        pos = {}, neg = {};
        for(int i = 0; i < n; i++) {
            cin >> nums[i];
            minV = min(minV, nums[i]), maxV = max(maxV, nums[i]);
            if(nums[i] >= 0) pos.push_back(nums[i]);
            else neg.push_back(nums[i]);
        }
        solve();
    }
};