/**
 * @Time : 2023/9/15-11:21 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, m, arr[N], cnt[N];

void solve(vector<int>& stack) {
    vector<bool> picked(m + 1, false);
    for(int i = 0; i < n; i++) {
        int num = arr[i];
        cnt[num]--;
        if(picked[num]) continue;
        while (!stack.empty() && cnt[stack.back()] > 0 && num < stack.back()) {
            picked[stack.back()] = false;
            stack.pop_back();
        }
        if(!picked[num]) {
            picked[num] = true;
            stack.push_back(num);
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m ;
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        cnt[arr[i]]++;
    }
    vector<int> stack;
    solve(stack);
    for(int num : stack)
        cout << num << " ";
    cout << endl;
}
