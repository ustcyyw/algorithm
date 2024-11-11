/**
 * @Time : 2023/8/15-10:38 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 贪心
 * 1. 相等的一对元素直接剔除 不需要任何操作
 * 2. 大于等于10的元素，且不相等的，要变为相等，至少经过一次操作变到2~9
 *    那么就直接计数有多少大于10的元素，有多少个就操作多少次
 *    小于10的元素，暂时不操作。
 *    然后所有元素都小于10了，统计
 * 3. 小于10的元素，1已经无法操作了 直接不管。剩下2~9，配对了的无需操作，多余的操作一次变为1即可。
 */
#include<bits/stdc++.h>

using namespace std;
int T, n;

void arr_cin(map<int, int>& map) {
    for(int i = 1, t; i <= n; i++) {
        cin >> t;
        map[t]++;
    }
}

void statistic(map<int, int>& map, vector<int>& num, int& res) {
    for(auto& pair : map) {
        int key = pair.first, val = pair.second;
        if(key < 10) num[key] += val;
        else {
            num[(int) to_string(key).size()] += val;
            res += val;
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    for(int t = 1; t <= T; t++) {
        cin >> n;
        map<int, int> arr1, arr2;
        arr_cin(arr1), arr_cin(arr2);
        for(auto& pair : arr1) {
            int key = pair.first, val = pair.second, same_cnt = min(val, arr2[key]);
            arr1[key] -= same_cnt, arr2[key] -= same_cnt;
        }
        vector<int> num1(10), num2(10);
        int res = 0;
        statistic(arr1, num1, res), statistic(arr2, num2, res);
        for(int i = 2; i <= 9; i++)
            res += abs(num1[i] - num2[i]);
        cout << res << endl;
    }
}