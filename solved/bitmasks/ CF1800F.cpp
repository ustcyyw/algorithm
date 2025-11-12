/**
 * @Time : 2024/2/2-9:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 *
 * 25个字母 每个字母都出现奇数次 25个奇数的和 确实也是奇数
 * 因此条件2和3保证了条件1成立 那其实只需要满足条件2和3即可
 *
 * 条件2：出现25种字符 换句话说就是只出现一种字符 可以枚举没出现的字符k
 * 条件3：要保证出现的字符都是奇数次 奇偶性 25个字符 状态压缩 0表示偶数次出现
 * 那么s1中某一位是0，s2中该位就得是1。 也就是说 s1 ^ s2 = u （u中有25个1，1个0）
 * s2 = u ^ s1
 *
 * 将不含字符k的字符串都放入同一个集合中 在此特定集合中求解
 * 1.如何保证不重，就是不会出现同一对合法字符被放入到不同集合中 从而被计算两次
 * 如果他们能被放如不同集合，也就说他们缺少了k1、k2两个字符
 * 那么k1、k2对应的两个二进制位都是0（没出现过等价于0）
 * 那么s1 ^ s2就会有至少两个0，绝对不会得到只有1个0的状态。因此不会重复计算
 * 2.如何保证不多算 就是没有出现25个字符 但被计算到。与1同理 此不合法情形下 s1 ^ s2就会有至少两个0
 */
#include<bits/stdc++.h>

using namespace std;
int n, cnt[26];
vector<vector<int>> status;
string word;

void get_status() {
    memset(cnt, 0, sizeof(cnt));
    for(char c : word)
        cnt[c - 'a']++;
    int s = 0;
    for(int i = 0; i < 26; i++)
        if(cnt[i] % 2 == 1) s |= 1 << i;
    for(int i = 0; i < 26; i++)
        if(cnt[i] == 0) status[i].push_back(s);
}

void solve() {
    long long res = 0ll;
    for(int i = 0; i < 26; i++) { // 枚举不存在的字符
        unordered_map<int, int> map;
        int u = (1 << 26) - 1 - (1 << i);
        for(int s : status[i]) {
            res += map[u ^ s];
            map[s]++;
        }
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    status = vector(26, vector(0, 0));
    for(int i = 1; i <= n; i++) {
        cin >> word;
        get_status();
    }
    solve();
};