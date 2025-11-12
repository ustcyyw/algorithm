/**
 * @Time : 2023/12/9-9:13 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    string s;
    cin >> s;
    int res = 0, n = s.size();
    for(int i = 0, left = 0; i < n; i++) {
        if(s[i] == '(') left++;
        if(s[i] == ')' && left > 0) {
            left--;
            res += 2;
        }
    }
    cout << res << endl;
}
