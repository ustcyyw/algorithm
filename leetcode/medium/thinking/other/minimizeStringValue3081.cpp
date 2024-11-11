/**
 * @Time : 2024/3/24-4:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 不同字母之间完全不影响cost
     * 相同字母cost与顺序无关 只与出现次数有关
     * 某个字母出现次数是m，则其cost为1 + 2 + ... + m - 1 = m * (m-1) / 2
     * 出现次数越多 cost增加得越多
     * 因此无论?的位置在哪 添加字母对cost的影响都只和放置的字母相关
     * 放置的字母原本出现得多 cost增加就越多 所以要贪心地将?替换为出现次数少的字母
     */
    string minimizeStringValue(string s) {
        vector<int> cnt(26, 0), arr, picked;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '?') arr.push_back(i);
            else cnt[s[i] - 'a']++;
        }
        function<int(void)> pick = [&]() -> int {
            int ans = -1, v = INT_MAX;
            for(int i = 0; i < 26; i++)
                if(cnt[i] < v) v = cnt[i], ans = i;
            cnt[ans]++;
            return ans;
        };
        for(int i = 0; i < arr.size(); i++)
            picked.push_back(pick());
        sort(picked.begin(), picked.end());
        for(int i = 0; i < arr.size(); i++)
            s[arr[i]] = (char)(picked[i] + 'a');
        return s;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}