/**
 * @Time : 2022/6/21-5:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 将非负整数 num 转换为其对应的英文表示。

 

示例 1：

输入：num = 123
输出："One Hundred Twenty Three"
示例 2：

输入：num = 12345
输出："Twelve Thousand Three Hundred Forty Five"
示例 3：

输入：num = 1234567
输出："One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
 

提示：

0 <= num <= 231 - 1


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/integer-to-english-words
 */
class Solution {
public:
    /**
     * 执行用时：4 ms, 在所有 C++ 提交中击败了69.13%的用户
     * 内存消耗：7.1 MB, 在所有 C++ 提交中击败了55.60%的用户
     */
    vector<string> base_map1 = {"Zero","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten",
                               "Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen",
                               "Eighteen","Nineteen","Twenty"};
    vector<string> base_map2 = {"0","1","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"};
    vector<string> base_map3 = {"","Thousand","Million","Billion"};
    string numberToWords(int num) {
        if(num == 0) return "Zero";
        string str = to_string(num), res = "";
        for(int n = str.size(), i = 1; 3 * (i - 1) < n; i++){
            // start 当前组别的开始索引，n - 3 * (i - 1)上一个组别的开始索引，减去当前的开始索引，得到当前组别的长度
            int start = max(0, n - 3 * i), len = n - 3 * (i - 1) - start;
            string sub = str.substr(start, len);
            // 具体调用哪个解析函数，根据当前组别的长度来判断
            string temp = len == 3 ? threeBase(sub) : len == 2 ? twoBase(sub) : oneBase(sub[0]);
            if(temp != "Zero"){ // 除了特殊处理的0，其它中间过程的0都没意义
                // 如果i是1，第一个组别没有后缀词，所以不用添加空格；否则添加空格。
                // 注意base_map3[0]为空串，也就是无后缀词
                if(res == "") res = temp.append(i != 1 ? " ": "").append(base_map3[i - 1]);
                else res = temp.append(" ").append(base_map3[i - 1]).append(" ").append(res);
            }
        }
        return res;
    }
    // 三个数字的解析
    string threeBase(string str){
        if(str[0] == '0') return twoBase(str.substr(1));
        string res = base_map1[str[0] - '0'] + " Hundred"; // 百位数字
        string temp = twoBase(str.substr(1));
        if(temp == "Zero") return res;
        else return res + " " + temp;
    }
    // 两个数字的解析
    string twoBase(string str){
        if(str[0] == '0') return oneBase(str[1]);
        int num = stoi(str);
        if(num <= 20) return base_map1[num];
        string res = base_map2[str[0] - '0']; // 十位数字
        if(oneBase(str[1]) == "Zero") return res;
        else return res + " " + oneBase(str[1]);
    }
    // 一个数字的解析
    string oneBase(char c){
        int num = c - '0';
        return base_map1[num];
    }
};

int main(){
    Solution s;
    cout << s.numberToWords(1000000009) << endl;
}