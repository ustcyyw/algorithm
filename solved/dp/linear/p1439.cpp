/**
 * @Time : 2023/10/16-2:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 问题转化
 * 借鉴lis 二分优化的思路
 * 用第一个数组来定义元素的相对大小
 */
#include<bits/stdc++.h>
using namespace std;
int n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    vector<int> rank(n + 1, 0), arr(n, 0);
    for(int i = 0, num = 0; i < n; i++) {
        cin >> num;
        rank[num] = i;
    }
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    vector<int> tail; // tail[i] : 表示长度为i+1的上升子序列最后一个元素的可能的最小值
    for(int num : arr) {
        int rk = rank[num], lo = 0, hi = tail.size();
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if(tail[mid] < rk) lo = mid + 1;
            else hi = mid;
        }
        if(lo == tail.size()) tail.push_back(rk);
        else tail[lo] = rk;
    }
    cout << tail.size() << endl;
}