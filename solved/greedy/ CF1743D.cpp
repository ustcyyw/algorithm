/**
 * @Time : 2024/6/12-1:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1743D 贪心
 */
 /*
  * 要让结果最大 肯定要保留原本s中最高位的1 然后想办法尽量将高位的0变成1
  * 注意是随机数据 因此可以暴力枚举s2 看看怎么取尽可能将s1中高位的0变成1
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n;
string s;

int find_first(int start, char c) {
    for(int i = start; i < n; i++)
        if(s[i] == c) return i;
    return -1;
}

bool compare(int is, int i1, int i2) {
    while(is < n) {
        if(s[is] == '1' || s[i1] == s[i2]) {
            i1++, i2++, is++;
            continue;
        }
        if(s[i1] == '1') return true;
        else return false;
    }
    return false;
}

string solve() {
    int i1 = find_first(0, '1');
    if(i1 == -1) return "0";
    int i2 = find_first(i1 + 1, '0');
    string s1 = s.substr(i1);
    if(i2 == -1) return s1;
    int start = i1;
    for(int i = i1; i < i2; i++) {
        if(compare(i2, i, start))
            start = i;
    }
    for(int i = i2 - i1, j = start; i < n; i++, j++) {
        if(s1[i] == '1') continue;
        if(s[j] == '1') s1[i] = '1';
    }
    return s1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    cin >> s;
    cout << solve() << endl;
};