/**
 * @Time : 2024/6/19-9:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1296E1 构造 贪心 模拟
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 5005, T = 1e4;
typedef long long ll;
int n, last[N];
string s, ans;

// 如果前面更大的字符被染色 当前字符需要跨过前面的字符 就需要使用另外一种颜色
// 如果前面没有更大的被染色的字符 就取当前字符为默认元素颜色1
char cur_color(char c) {
    for(int i = last[c - 'a']; i >= 0; i--) {
        if(s[i] > c && ans[i] != '.') {
            return ans[i] == '0' ? '1' : '0';
        }
    }
    return '1';
}

bool check(char c) {
    int r = last[c - 'a'];
    char color = ans[r] != '.' ? ans[r] : cur_color(c);
    char oc = color == '0' ? '1' : '0'; // 标记另外一种颜色
    for(int i = r; i >= 0; i--) {
        if(s[i] <= c) { // 比当前考虑的字符更小的字符不会妨碍跨域 不用检查颜色是否不同
            if(ans[i] == '.') ans[i] = color; // 如果遇到相同字母且未染色的 染成相同颜色和前面的进行对比
                // 如果遇到相同字母已经染色的 就将当前字符标记为此颜色 与前面进行对比
            else if(s[i] == c) color = ans[i];
            continue;
        }
        if(ans[i] == '.') ans[i] = oc; // 未染色且需要交换的字符 染成另外一种颜色
        else if(ans[i] == color) return false; // 已染色且需要交换的字符 还是同一种颜色 无法交换
    }
    return true;
}

bool solve() {
    for(int i = 0; i < n; i++)
        last[s[i] - 'a'] = i;
    for(int i = 0; i < 26; i++) {
        if(last[i] == -1) continue;
        if(!check((char)(i + 'a'))) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> s;
    ans.assign(n, '.');
    fill(last, last + 26, -1);
    if(!solve()) cout << "NO";
    else cout << "YES\n" << ans;
};