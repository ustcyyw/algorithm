/**
 * @Time : 2024/2/15-4:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 第k个字符 尽可能小
  * 先排前k个字符 字典序由前缀确定 所以一位一位地排 从小的字母开始排
  * 如果 ans[i].back() != ans[k - 1].back()。就说明序号为i的字符 一定排在第k个字符之前了
  * 那么ans[i]后面放什么字母都行 那就先不管
  * 继续在与ans[k - 1]前缀完全一样的字符串中安排字母
  * 直到ans[k - 1]已经排满了或者 ans[k - 1] 已经与其它字符前缀不同时停止
  * 此时ans[k - 1]就一定是第k大的字符
  *
  * 然后贪心地优先将剩余字母中最小的分配给ans[k - 1]
  * 然后对剩余没有构造完成的字符 随意分配即可
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
int n, l, k, cnt[26];

void fill(string& s) {
    for(int i = 0; s.size() < l; ) {
        while(cnt[i] == 0) i++;
        s.push_back((char)(i + 'a'));
        cnt[i]--;
    }
}

void solve() {
    vector<string> ans(n);
    for(int i = 0, lo = 0; lo < k - 1 && ans[k - 1].size() < l; ) {
        for(int j = lo; j < k; j++) {
            while(cnt[i] == 0) i++;
            ans[j].push_back((char)(i + 'a'));
            cnt[i]--;
        }
        while(lo < k - 1 && ans[lo].back() != ans[k - 1].back()) lo++;
    }
    fill(ans[k - 1]);
    for(int i = 0; i < n; i++) {
        fill(ans[i]);
        cout << ans[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> l >> k;
    memset(cnt, 0, sizeof(cnt));
    string temp;
    cin >> temp;
    for(char c : temp)
        cnt[c - 'a']++;
    solve();
};