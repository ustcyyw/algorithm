/**
 * @Time : 2024/6/21-2:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1328D 贪心
 */
/*
 * 最多三种颜色就可以搞定
 * 注意相邻的数如果数值相同 可以涂相同颜色也可以不同颜色
 * 1. 如果首尾元素相同 可以直接将所有相邻的相同数染成同一颜色 遇到不同值就换颜色
 * 这样首尾元素被涂成什么颜色都无所谓
 * 2. 首尾元素不同 要尽可能让颜色少 用1中的方案可能会导致首尾颜色相同
 * 那么在首尾颜色相同的情况下 来修改方案 因为方案是交替涂色
 * 只要在前面某个地方多进行一次交替涂色 尾元素就会变成另外一个颜色 就和首元素不同了
 * 但是怎么多进行一次交替涂色 找一个长度 > 1的连续的数值 将其最后一个元素换一个颜色即可
 * 如果找不到这样的连续数值 那就只能将尾元素涂成颜色3了
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, nums[N], color[N];

void same() {
    for(int i = 1, c = 1, j; i <= n; c = c == 1 ? 2 : 1) {
        j = i;
        while(j <= n && nums[j] == nums[i])
            color[j++] = c;
        i = j;
    }
}

void not_same() {
    int change_idx = -1;
    for(int i = 1, c = 1, j; i <= n; c = c == 1 ? 2 : 1) {
        j = i;
        while(j <= n && nums[j] == nums[i])
            color[j++] = c;
        int len = j - i;
        if(len > 1 && change_idx == -1) change_idx = j - 1;
        i = j;
    }
    if(color[n] != color[1]) return;
    if(change_idx == -1) {
        color[n] = 3;
        return;
    }
    for(int i = 1, c = 1, j; i <= n; c = c == 1 ? 2 : 1) {
        j = i;
        while(j <= n && nums[j] == nums[i])
            color[j++] = c;
        if(j - 1 == change_idx) {
            c = c == 1 ? 2 : 1;
            color[change_idx] = c;
        }
        i = j;
    }
}

void solve() {
    if(nums[n] == nums[1]) same();
    else not_same();
    int cnt = 0;
    for(int i = 1; i <= n; i++)
        cnt = max(cnt, color[i]);
    cout << cnt << "\n";
    for(int i = 1; i <= n; i++)
        cout << color[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};