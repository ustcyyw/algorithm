/**
 * @Time : 2025/1/26-10:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3435 贪心 状态压缩 暴力枚举 拓扑排序 卡常需要翻译为java才能通过
 */
#include<bits/stdc++.h>
using namespace std;

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
        // 没有环的条件就是 拓扑排序访问过的结点数 == 只出现一次的字母数量
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
//
//class Solution {
//    int n;
//    List<Character> arr;
//    int[] mp = new int[26];
//
//public List<List<Integer>> supersequences(String[] words) {
//        init(words);
//        this.n = arr.size();
//        int full = (1 << n) - 1, cnt = Integer.MAX_VALUE;
//        List<List<Integer>> ans = new ArrayList<>();
//
//        for (int s = 0; s <= full; s++) {
//            int cc = Integer.bitCount(s);
//            if (cc > cnt) continue;
//            if (!check(s, words)) continue;
//            List<Integer> temp = makeSeq(s);
//            if (cnt > cc) {
//                cnt = cc;
//                ans.clear();
//            }
//            ans.add(temp);
//        }
//
//        return ans;
//    }
//
//private boolean check(int s, String[] words) {
//        int[] degree = new int[n];
//        List<List<Integer>> graph = new ArrayList<>(n);
//        for (int i = 0; i < n; i++) {
//            graph.add(new ArrayList<>());
//        }
//
//        for (String word : words) {
//            int c1 = mp[word.charAt(0) - 'a'], c2 = mp[word.charAt(1) - 'a'];
//            int t1 = (1 << c1) & s, t2 = (1 << c2) & s;
//            if (t1 != 0 || t2 != 0) continue;
//            graph.get(c1).add(c2);
//            degree[c2]++;
//        }
//
//        Queue<Integer> queue = new LinkedList<>();
//        for (char c : arr) {
//            int j = mp[c - 'a'], t = (1 << j) & s;
//            if (t == 0 && degree[j] == 0) queue.add(j);
//        }
//
//        int cnt = 0;
//        while (!queue.isEmpty()) {
//            int v = queue.poll();
//            cnt++;
//            for (int w : graph.get(v)) {
//                if (--degree[w] == 0) {
//                    queue.add(w);
//                }
//            }
//        }
//
//        return cnt == arr.size() - Integer.bitCount(s);
//    }
//
//private List<Integer> makeSeq(int s) {
//        List<Integer> cnt = new ArrayList<>(Collections.nCopies(26, 0));
//        for (int i = 0; i < n; i++) {
//            int idx = arr.get(i) - 'a';
//            if (((1 << i) & s) > 0) cnt.set(idx, 2);
//            else cnt.set(idx, 1);
//        }
//        return cnt;
//    }
//
//private void init(String[] words) {
//        arr = new ArrayList<>();
//        for (String word : words) {
//            arr.add(word.charAt(0));
//            arr.add(word.charAt(1));
//        }
//        Collections.sort(arr);
//        arr = new ArrayList<>(new HashSet<>(arr)); // Remove duplicates
//        for (int i = 0; i < arr.size(); i++) {
//            mp[arr.get(i) - 'a'] = i;
//        }
//    }
//}