/**
 * @Time : 2024/7/13-12:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1560E 构造
 */
/*
 * 倒着统计字母出现顺序 就能得出删除的顺序
 * 得到字母的删除顺序后 m = order.size()表示删除了多个字母
 * 最后一个被删除的 出现次数 c(m) * cnt
 * 倒数第二个被删除的 出现次数 c(m-1) * (cnt - 1)
 * ....
 * 第一个被删除的 出现次数 c(1) * 1
 * 这些是在t中的总出现次数，c计算的是在s中出现的次数
 * 于是可以推出每个字母在s出现了几次 必须能整除才行
 * 确定了s中各个字母出现的次数 也就确定了s的长度 s一定是t的前缀
 * 接下来就是按删除顺序检查 看看能不能得到t了
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2005, mod = 1e9 + 7;
typedef long long ll;
int T, n, cnt[26], single[26];
string s, ans, order;

void find_order() {
    for(int i = n - 1; i >= 0; i--) {
        cnt[s[i] - 'a']++;
        if(cnt[s[i] - 'a'] == 1) order.push_back(s[i]);
    }
    reverse(order.begin(), order.end());
}

bool check(int lo, int hi) {
    int i = 0, j = lo;
    for(; i < ans.size(); i++) {
        if(single[ans[i] - 'a'] == 0) continue;
        if(ans[i] != s[j]) return false;
        j++;
    }
    return i == ans.size() && j == hi + 1;
}

bool solve() {
    find_order();
    for(int m = order.size(), i = m - 1; i >= 0; i--) {
        int idx = order[i] - 'a';
        if(cnt[idx] % (i + 1) != 0) return false;
        single[idx] = cnt[idx] / (i + 1);
    }
    int sum = accumulate(single, single + 26, 0);
    ans = s.substr(0, sum);
    for(int i = 0, j = 0; i < n; j++) {
        if(!check(i, i + sum - 1)) return false;
        i += sum;
        sum -= single[order[j] - 'a'];
        single[order[j] - 'a'] = 0;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> s;
        order = {};
        memset(cnt, 0, sizeof(cnt)), memset(single, 0, sizeof(single));;
        n = s.size();
        if(!solve()) cout << "-1\n";
        else cout << ans << " " << order << "\n";
    }
};