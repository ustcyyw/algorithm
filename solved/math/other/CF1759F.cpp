/**
 * @Time : 2024/8/21-10:21 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1759F 数学 找规律
 */
/*
 * 对于p进制数 执行p-1次+1操作 一定能出现所有p进制下的单一数字
 * 比如8进制数 有0～7这个8个单一数字
 * 由5进行+1操作 7次分别得到 6 7 0 1 2 3 4
 * 因此本题答案的上界就是p-1，也就是说最多需要一次进位操作
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 9;
typedef long long ll;
int T, n, p, a[105];
set<int> st;

// 检查是否需要进位操作
bool check() {
    int num = 0;
    while(num < a[n] && st.count(num))
        num++;
    return num != a[n]; // 如果比个位数小的数字有缺失 那必须都有进位操作才能获取所有数字
}
// 从hi开始查找，找到[lo + 1, hi]上缺失的第一个数 没有缺失的数 会返回lo
int find_miss(int lo, int hi) {
    while(hi > lo && st.count(hi))
        hi--;
    return hi;
}

// 添加至进一位的情况 个位变为0 十位+1 并且开始查看是否连续进位
void add() {
    a[n] = 0;
    for(int i = n - 1, flag = 1; flag == 1; i--) {
        a[i] = (a[i] + flag) % p;
        flag = a[i] == 0;
    }
    // 进位操作后更新已经出现过的数字
    if(a[0] > 0) st.insert(a[0]);
    for(int i = 1; i <= n; i++)
        st.insert(a[i]);
}

int solve() {
    if(!check()) { // 不需要进位的情况 从p-1开始找到缺失的最大的数
        int num = find_miss(a[n], p - 1);
        return num - a[n];
    }
    // 需要进位一次的情况
    int t = a[n], cnt = p - t; // cnt 此时的值就是将个位+1到可以进位所需的操作次数
    add();
    int num = find_miss(0, t); // 从原本的个位数开始向下找缺失的最大的数
    return cnt + num;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> p;
        st = {};
        a[0] = 0;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            st.insert(a[i]);
        }
        cout << solve() << "\n";
    }
};