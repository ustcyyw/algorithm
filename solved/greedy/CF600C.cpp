/**
 * @Time : 2024/4/3-3:31 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 从小的字母开始遍历
 * 发现一个字母出现了偶数次 那就成对直接排在头尾即可（字典序最小 先排小的字母）
 * 如果出现了奇数次 记原本字符串的长度是len
 * 1.len是偶数 所有字母都得成对，那么就从后往前找一个也是奇数次的字母 改成小的这个
 * 保证了修改次数最少 字典序最小
 * 2.len是奇数 允许有一个字母不成对。如果还有3个及以上的字母不成对 就修改。
 * 只有一个字母不成对的时候 取该字母放中间即可。这样也能保证修改最少 字典序最小
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
int T, n, cnt[26];
string s;

int find_odd() {
    for(int i = 25; i >= 0; i--)
        if(cnt[i] % 2 == 1) return i;
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s;
    memset(cnt, 0, sizeof(cnt));
    for(char c : s)
        cnt[c - 'a']++;
    int midC = -1;
    string t;
    for(int i = 0; i < 26; i++) {
        if(cnt[i] == 0) continue;
        if(cnt[i] % 2 == 1) {
            int j = find_odd();
            cnt[j]--, cnt[i]++;
            if(i == j) midC = i;
        }
        for(int k = 0; k < cnt[i] / 2; k++) t.push_back((char)(i + 'a'));
    }
    s = t;
    if(midC != -1) s.push_back((char)(midC + 'a'));
    reverse(t.begin(), t.end());
    s += t;
    cout << s;
};