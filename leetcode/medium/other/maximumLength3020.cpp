/**
 * @Time : 2024/1/29-12:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        map<long long, int> cnt;
        for(int num : nums)
            cnt[num]++;
        unordered_set<long long> marked;
        int res = 0;
        if(cnt.count(1)) {
            res = cnt[1] % 2 == 0 ? cnt[1] - 1 : cnt[1];
            marked.insert(1);
        }
        function<int(long long)> count = [&](long long num) -> int {
            int temp = 1;
            while(cnt[num] >= 2 && cnt[num * num] > 0) {
                temp += 2, num = num * num;
                marked.insert(num);
            }
            return temp;
        };
        for(auto& pair : cnt) {
            if(marked.count(pair.first)) continue;
            res = max(res, count(pair.first));
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}