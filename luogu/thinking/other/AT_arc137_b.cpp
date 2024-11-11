/**
 * @Time : 2023/12/18-10:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 假设原始数组有cnt个1
 * 如果某个子区间上0比1 多1个 那么翻转这个子区间sum = cnt + 1
 * 如果某个子区间上0比1 多2个 那么翻转这个子区间sum = cnt + 2
 * ...
 * sum 最大就取决于 子区间上0最多比1多多少个
 * 同理 sum 最小取决于 子区间上0最多比1少多少个
 * 因此要求前缀和 还要找到0和1相差最大/最小是多少个
 */
#include<bits/stdc++.h>
using namespace std;
int n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    int sum = 0, maxV = 0, minV = 0, maxVV = 0, minVV = 0;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        sum += num == 1 ? -1 : 1;
        maxVV = max(maxVV, sum - minV), minVV = min(minVV, sum - maxV);
        maxV = max(maxV, sum), minV = min(minV, sum);
    }
    cout << (maxVV - minVV + 1) << endl;
}