/**
 * @Time : 2024/12/6-5:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 左端点lo 刚好有k和刚好有k+1个辅音字母对应的右端点hi1, hi2
1.如果lo是元音，无论lo+1是什么 辅音字母都没变化 那么hi1, hi2依旧可用
2.如果lo是辅音，无论lo+1是什么 那么辅音字母少了1个
前一个位置的hi2变为当前位置hi1，然后从这个位置开始找hi2

右端点hi3使得对元音字母的条件满足
hi3 <= hi1, 那么右端点[hi1, hi2-1]都是满足条件的
hi3 < hi2, 那么右端点[hi3, hi2-1]是满足条件的
否则hi3 >= hi2, 要满足元音的要求 辅音字母就超过k个了
  */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
class Solution {
public:
    int n;
    unordered_set<char> sc = {'a', 'e', 'i', 'o', 'u'};
    long long countOfSubstrings(string word, int k) {
        n = word.size();
        vector<int> hi1 = find_hi(word, k), hi2 = find_hi(word, k + 1);
        vector<int> hi3(n, n);
        unordered_map<char, int> map;
        for(int lo = 0, hi = 0; lo < n; lo++) {
            while(hi < n && map.size() < 5) {
                if(sc.count(word[hi])) map[word[hi]]++;
                hi++;
            }
            if(map.size() == 5) hi3[lo] = hi - 1;
            if(sc.count(word[lo])) {
                map[word[lo]]--;
                if(map[word[lo]] == 0) map.erase(word[lo]);
            }
        }
        ll ans = 0;
        for(int i = 0; i < n && hi1[i] != n && hi3[i] != n; i++) {
            if(hi3[i] < hi2[i])
                ans += hi2[i] - max(hi3[i], hi1[i]);
        }
        return ans;
    }

    vector<int> find_hi(string& word, int k) {
        vector<int> ans(n, n);
        for(int lo = 0, hi = 0, cnt = 0; lo < n; lo++) {
            while(hi < n && cnt < k) {
                if(!sc.count(word[hi])) cnt++;
                hi++;
            }
            if(cnt == k) ans[lo] = max(lo, hi - 1);
            if(!sc.count(word[lo])) cnt--;
        }
        return ans;
    }
};