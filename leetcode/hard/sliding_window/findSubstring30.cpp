/**
 * @Time : 2023/3/22-3:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, m, len;
    unordered_map<string, int> map;
    unordered_map<int, int> counts;
    vector<int> findSubstring(string s, vector<string>& words) {
        n = s.size(), m = words.size(), len = words[0].size();
        // 将word进行编号，并且记录word的出现次数，words中会出现重复
        for(int i = 0; i < m; i++){
            string& word = words[i];
            if(!map.count(word)) map[word] = i;
            int id = map[word];
            counts[id] = counts.count(id) ? counts[id] + 1 : 1;
        }
        vector<int> res;
        // 字符子串以len为宽度分割，分割起点不同，分割出来的子串就不同。
        // 但是超过了len，就重复了。比如以0为起点与以len为起点分割，后者第一个子串是前者的第二个子串
        for(int i = 0; i < len; i++)
            check(s, res, i);
        return res;
    }

    void check(string& s, vector<int>& res, int start){
        vector<int> nums; // 处理出子串编号
        for(int i = start; i + len <= n; i += len){
            string temp = s.substr(i, len);
            nums.push_back(map.count(temp) ? map[temp] : -1);
        }
        vector<int> aux(5005, 0); // 用于计数 某一个子串在区间内的出现次数
        int left = 0, right = 0, sz = nums.size(), cnt = 0; // cnt是有效子串的数目，cnt = m时，words中所有word都拼接上了
        while (right < sz){
            int id1 = nums[right], id2 = nums[left];
            if(id1 != -1){
                aux[id1]++;
                // 如果添加后 某个单词出现数量没有超，则该子串是所需的
                if(aux[id1] <= counts[id1]) cnt++;
            }
            if(right - left + 1 > m) {
                if(id2 != -1){
                    aux[id2]--;
                    // 从窗口移除后，某个单词数量小于words中该单词的数量，有效子串数目就减少1
                    if(aux[id2] < counts[id2]) cnt--;
                }
                left++;
            }
            if(right - left + 1 == m && cnt == m)
                res.push_back(start + left * len); // 起点在原字符串的偏移量 + 前置子串的长度 = 当前子串的起点
            right++;
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}