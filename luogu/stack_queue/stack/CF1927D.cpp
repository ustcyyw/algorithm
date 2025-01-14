/**
 * @Time : 2024/11/9-11:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1927D 栈
 */
 /*
  * 用栈的思路找上一个不想等的元素
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, M = 4e2;
int T, n, q, nums[N], pre[N]; // 用于记录上一个不相等的元素

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        stack<int> stack;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        for(int i = 1; i <= n; i++) {
            while(!stack.empty() && nums[stack.top()] == nums[i])
                stack.pop();
            pre[i] = stack.empty() ? 0 : stack.top();
            stack.push(i);
        }
        cin >> q;
        for(int i = 1, l, r; i <= q; i++) {
            cin >> l >> r;
            if(pre[r] < l) cout << "-1 -1" << "\n";
            else cout << pre[r] << " " << r << "\n";
        }
        cout << "\n";
    }
};