/**
 * @Time : 2024/7/1-3:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1367D 构造
 */
 /*
  * 关键就是搞清楚位置为0的地方 就是放置当前最大字母的地方
  * 放置之后 他对其它位置的字母都有贡献 要减去它的贡献
  * 然后继续看什么地方为0 就是次大的字母
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 55;
typedef long long ll;
int T, n, m, nums[N], cnt[26];
string s, ans;

vector<int> find_zero() {
    vector<int> arr;
    for(int i = 0; i < m; i++) {
        if(ans[i] == '.' && nums[i] == 0)
            arr.push_back(i);
    }
    return arr;
}

void solve() {
    for(char c : s)
        cnt[c - 'a']++;
    vector<int> arr = find_zero();
    int idx = 25;
    while(arr.size() != 0) {
        while(idx >= 0 && cnt[idx] < arr.size())
            idx--;
        for(int i : arr) {
            ans[i] = (char)(idx + 'a');
            for(int j = 0; j < m; j++)
                nums[j] -= abs(i - j);
        }
        idx--;
        arr = find_zero();
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> s >> m;
        for(int i = 0; i < m; i++)
            cin >> nums[i];
        memset(cnt, 0, sizeof(cnt));
        ans.assign(m, '.');
        solve();
    }
};