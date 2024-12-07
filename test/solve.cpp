#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, mod = 1e9 + 7;
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
            lo++;
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

int main() {
    vector<int> arr1 = {1,2,3};
    vector<int> arr2 = {2,3,4};
    vector<int> arr3 = {1,2,3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{0,1},{0,2},{0,3},{0,4}};
    vector<vector<int>> arr6 = {{0,1},{1,2},{1,3}};
    Solution s;
    s.countOfSubstrings("ieaouqqieaouqq", 1);
}
