#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    /*
     * 任何一个word的长度都是2
     * 在原序列中 如果有一个字母出现了两次 那么就将其排在最左和最右边
     * 比如a出现两次 这样就可能表示出所有 a* 和 *a
     * 比如序列的字母组成情况是 a(2), b(1) c(1) d(1)
     * a bcd a 关于a的word可以表示出 ab ac ad, ba ca da aa
     * bacad   关于a的word可以表示出 ba ca ac ad aa
     * 显然将a放在两边至少不差
     * 有多个字母出现2次 只要一次将他们放在最外面、次外面即可
     * 比如a和b都出现了2次 ab xxx ba, 和 ba xxx ab 能表示的word集合相同
     * 结论1：有一个字母出现了两次 那么就将其排在最左和最右边
     *
     * 因为word长度为2，2个a就已经能表示a* 和 *a
     * 那要第3个a 根本无法新增任何word 没有任何意义
     * 结论2：如果某个字母出现了 那么其最多需要出现2次
     * 因此在给定的words中 出现过的字母 要么在原序列中出现1次 要么出现2次
     * 题目中限定了words中最多有16个不同字母 就提示可以使用状态压缩表示字母出现的次数
     * 二进制位为1 则相应的字母出现了2次 枚举所有可能的状态
     *
     * 假设字母的出现次数用状态s表示
     * 那么s中二进制1对应的字母x 在原序列中出现2次 被放在最外侧
     * x*和*x一定能被表示出来 words中这一类word就一定能表示出来 不用考虑了
     * 剩下的word就得用仅出现一次的字母表示出来
     * 而word又规定了字母出现的先后顺序 相当于规定了拓扑序 用剩下的字母建图
     *
     * 结论3 图中不允许有环 否则就表示不出来还需要的所有word
     * 比如 a b c 都只能使用一次 word中有 ab bc ca 建图后存在abc的环
     * a b c三个字母无论什么顺序排列 总有一个word表示不出来
     */
    int n;
    vector<char> arr;
    vector<int> mp = vector(26, 0);
    vector<vector<int>> supersequences(vector<string>& words) {
        init(words);
        this->n = arr.size();
        int full = (1 << n) - 1, cnt = INT_MAX;
        vector<vector<int>> ans;
        for(int s = 0; s <= full; s++) {
            int cc = __builtin_popcount(s);
            if(cc > cnt) continue;
            if(!check(s, words)) continue;
            vector<int> temp = make_seq(s);
            if(cnt > cc) cnt = cc, ans.clear();
            ans.push_back(temp);
        }
        return ans;
    }

    bool check(int s, vector<string>& words) {
        vector<int> degree(n, 0);
        vector<vector<int>> graph(n);
        for(auto& word : words) {
            int c1 = mp[word[0] - 'a'], c2 = mp[word[1] - 'a'];
            int t1 = (1 << c1) & s, t2 = (1 << c2) & s;
            if(t1 || t2) continue;
            graph[c1].push_back(c2);
            degree[c2]++;
        }
        queue<int> queue;
        for(char c : arr) {
            int j = mp[c - 'a'], t = (1 << j) & s;
            if(t == 0 && degree[j] == 0) queue.push(j);
        }
        int cnt = 0;
        while(!queue.empty()) {
            int v = queue.front(); queue.pop();
            cnt++;
            for(int w : graph[v]) {
                if(--degree[w] == 0)
                    queue.push(w);
            }
        }
        return cnt == arr.size() - __builtin_popcount(s);
    }

    vector<int> make_seq(int s) {
        vector<int> cnt(26, 0);
        for(int i = 0; i < n; i++) {
            int idx = arr[i] - 'a';
            if((1 << i) & s) cnt[idx] = 2;
            else cnt[idx] = 1;
        }
        return cnt;
    }

    void init(vector<string>& words) {
        for(string& word : words)
            arr.push_back(word[0]), arr.push_back(word[1]);
        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        for(int i = 0; i < arr.size(); i++)
            mp[arr[i] - 'a'] = i;
    }
};

int main() {
    vector<int> arr1 = {-1};
    vector<ll> arr2 = {5,3,1,0};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"aa","ac"};
    vector<vector<int>> arr4 = {{3,0,5},{3,1,6},{2,3,5}};
//    vector<vector<int>> arr4 = {{1,0,8}};
    Solution s;
    s.supersequences(arr5);
}
