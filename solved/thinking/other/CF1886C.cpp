/**
 * @Time : 2023/12/16-3:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 每次只能去掉一个字符 假如现在要考虑是否去掉s[i]
 * 字符串s = pre + s[i] + s[i + 1] + suf
 * 如果去掉 s[i], st1 = pre + s[i + 1] + suf
 * 如果去掉的是i右边的字符 st2 = pre + s[i] + suf_t
 * st1 < st2 的条件就是 s[i] > s[i + 1]，此时去掉s[i]得到一个更小的序列
 * 这个序列是否为最小序列呢？
 * 在此条件下 去掉i右边的字符都不如去掉s[i]
 * 如果字符删除规则均按照"当前字符大于下一个字符 就去掉当前字符"
 * 那么i左边的字符均是 <= s[i]的，删掉他们会让序列更大
 * 因此删除s[i]得到的就是最小序列
 *
 * 按照拼接规则，每生成一个新字符，相当于pos减去上一个字符的长度
 * 然后看pos现在是否在新字符的范围内。如果是 就找到对应字符，不是就继续上述过程
 *
 * 要按照规则删除字符，可以使用单调栈，stack.back() > s[i]，说明上一个保留的字符应该删掉
 * 另外注意当i已经扫描完所有字符后，在stack中保留的字符是单调增的
 * 此时要删除一个字符得到更小序列，就是不断将最后一个字符删除
 */
#include<bits/stdc++.h>
using namespace std;

int T;

char solve() {
    string s; cin >> s;
    long long pos; cin >> pos;
    int n = s.size(), len = n, i = 0;
    vector<char> stack;
    while(pos > len) {
        // 出栈操作的时候 才是删除一个字符的时候
        if(i == n || (!stack.empty() && s[i] < stack.back())) {
            stack.pop_back();
            pos -= len, len--;
        }
        else stack.push_back(s[i++]);
    }
    if(pos <= stack.size()) return stack[pos - 1];
    i += pos - stack.size() - 1;
    return s[i];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cout << solve();
    }
}