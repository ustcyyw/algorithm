/**
 * @Time : 2023/4/26-12:01 AM
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
     * 数组中最多有16个数，那么最多枚举到17，就能找到一个不存在的数
     * 重点就是进制转换了
     */
    string findDifferentBinaryString(vector<string>& nums) {
        int n = nums.size();
        unordered_set<int> arr;
        for(string num : nums)
            arr.insert(change(num));
        for(int i = 0; i < 20; i++){
            if(!arr.count(i)) {
                bitset<16> digit(i);
                string res;
                for(int j = n - 1; j >= 0; j--)
                    res.push_back((char)(digit[j] + '0'));
                return res;
            }
        }
        return "";
    }

    int change(string& s){
        int res = 0;
        for(int i = s.size() - 1, j = 0; i >= 0; i--, j++)
            if(s[i] == '1') res |= 1 << j;
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}