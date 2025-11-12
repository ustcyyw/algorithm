/**
 * @Time : 2024/11/24-4:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1256F 思维 构造 2000
 */
 /*
  * 两个字符串通过操作后相等必要条件是字符串对字符构成一摸一样
  * 如果选定L=2 相邻两个元素互换位置 可以考虑将字符串按交换排序的思路处理
  * 那么在字符构成一致的情况下 两个字符串都完成排序就相等了。
  * 但是题目中一次操作 两个字符串都要进行一次交换
  * 可能会存在两个字符串完成排序所需的交换次数不一样的情况
  * 1. 如果字符串中存在重复出现都字母 那么总是可以首先将重复字母交换到一起
  * 然后其中一个字符串总是选择两个相邻的相同字母来操作 另外一个字符串则正常走交换排序的流程
  * 这样就能抹平交换次数不一样的情况 此时就一定能最终让两个字符串相等
  * 2. 如果1的情况不满足 那么字符串最长只有26，因为但凡由27个字母组成 一定就会出现重复
  * 此时注意到同一个子字符串操作2次 还是原本的样子
  * 那么在所需交换次数少的字符串已经排序的情况下，选择其一个长度为2的子串不断操作
  * 抹平交换次数也可以 只不过要求两个字符串完成排序的交换次数之差为偶数
  *
  * 注意 这里字符串完成排序 可以是任意规定的排序顺序 只不过为了方便直接按照字母序即可
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n;
string s1, s2;

vector<int> statistic(string& s) {
    vector<int> cnt(26, 0);
    for(char c : s)
        cnt[c - 'a']++;
    return cnt;
}
// 计算逆序对
int count_reverse(string& s) {
    int ans = 0;
    for(int i = 1; i < s.size(); i++) {
        for(int j = 0; j < i; j++)
            if(s[i] < s[j]) ans++;
    }
    return ans;
}

bool solve() {
    vector<int> cnt1 = statistic(s1), cnt2 = statistic(s2);
    if(cnt1 != cnt2) return false;
    bool same = false; // 标识一个字符串中是否出现了相同的字母
    for(int num : cnt1) {
        same |= num > 1;
    }
    if(same) return true;
    // 字符串长度超过26， 一定会有相同字母出现， 可以断定现在字符串长度最多26
    int c1 = count_reverse(s1), c2 = count_reverse(s2);
    return abs(c1 - c2) % 2 == 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> s1 >> s2;
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};