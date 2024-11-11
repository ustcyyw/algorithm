/**
 * @Time : 2024/1/19-12:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 贪心地想 要优先将右边的括号移除
 * 比如 (())()(())，先将最右边的部分处理(())完，然后处理单独的()，然后再处理第一部分的(())
 * 并列的括号 相互之间不影响cost 因此只要独立地处理即可
 *
 * 给定一个独立匹配括号
 * 比如 ((())) 最外层括号的存在 使得删除内部括号的cost为2，刚好是内部括号对的数量
 * 比如 (()()) 最外层括号的存在 使得删除内部括号的cost为2
 * 因此可以先找到每对匹配括号内部有多少个括号 将这些值加起来 就是总的cost
 *
 * 有k次移动机会，就应该用在内部括号最多的括号对 让他们直接相邻
 */
#include<bits/stdc++.h>
using namespace std;
long long T, k;
string s;

void solve() {
    vector<int> arr;
    stack<int> stack;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(') stack.push(i);
        else {
            arr.push_back((i - stack.top() - 1) / 2);
            stack.pop();
        }
    }
    sort(arr.begin(), arr.end());
    long long res = accumulate(arr.begin(), arr.end() - min(k, (long long)arr.size()), 0ll);
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T--) {
        cin >> k;
        cin >> s;
        solve();
    }
}