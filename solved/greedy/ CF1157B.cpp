/**
 * @Time : 2024/5/11-10:49 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1157B 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
ll n, nums[10];
string s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    cin >> s;
    for(int i = 1; i <= 9; i++)
        cin >> nums[i];
    for(int i = 0, flag = 0; i < n; i++) {
        int num = s[i] - '0';
        if(num < nums[num]) {
            s[i] = (char)('0' + nums[num]);
            flag = 1;
        }
        else if(num > nums[num] && flag == 1) break;
    }
    cout << s;
};