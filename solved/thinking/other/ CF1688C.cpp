/**
 * @Time : 2024/6/16-10:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1688C 思维题 结论题
 */
/*
 * 答案是单个字母 那么其它不是答案的字母有什么特征呢
 * 每一轮替换操作 替换前记为sa，替换后记为sb
 * 1.压根都没出现过的字母
 * 2.在替换途中出现过 但是在最后答案中不见了
 * 假设该字符在替换过程中出现过k次（在各个sb中出现了k次）
 * 最终不见 他一定是被替换了k次（在各个sa中出现了k次）
 * 它又不在最终答案s中 因此所有字符串中他一共出现了2k次
 * 3.该字符出现在最终答案中 在s中出现了k次
 * 除开类似2中的情况 这个字符在过程中出现后又被替换 最终在sb中还要出现k次，这样才能留在最终答案中
 * 中途出现又被替换是成对出现对 s中出现k次 sb中未被替换的也出现k次
 * 因此在所有给出的字符串中一共出现了偶数次
 *
 * 综上所述 不是答案的字母 都是出现了偶数次
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1048576 + 5, mod = 998244353;
typedef long long ll;
int T, n, cnt[26];
string s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i <= 2 * n; i++) {
            cin >> s;
            for(char c : s)
                cnt[c - 'a']++;
        }
        for(int i = 0; i < 26; i++) {
            if(cnt[i] % 2 == 1) {
                cout << (char)(i + 'a') << "\n";
                break;
            }
        }
    }
};