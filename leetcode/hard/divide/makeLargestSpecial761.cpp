/**
 * @Time : 2023/11/7-2:53 PM
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
     * 特殊序列：0和1的数量相等，并且任意前缀都是1的数量>=0的数量
     * 这意味着
     * 1.任何一个特殊序列以1开头 (取长度为1的前缀，要使其1的数量更多，那就只能是1)
     * 2.任何一个特殊序列以0为结尾 因为如果结尾是1，整个序列0和1数量相等，那么其前缀中0的数量就比1多了
     * 3.一个特殊序列 要么被分为多个特殊的子序列 要么就已经不可以分割
     * 可以分割的情况，s[0,i]中0和1的数量相等了
     * 那么s[i+1,n-1]中0和1的数量相等,并且任意s[i+1, j]，j >= i + 1中都有1的数量大于等于0的数量
     * 否则s[0,j] = s[0,i] + s[i+1, j]中0的数量更多 与s是特殊序列矛盾
     * 因此可以将s[0,i]拆分出去，并且依旧保证了s[i+1, n]是特殊序列
     * 再接着考虑s[i+1, n]能否进一步拆分。
     * 4.不可分割的特殊子序列，除去开头的1和结尾的0，是一个子特殊序列
     * 开头的1后面一定是1，如果是0，那直接就是可拆分的 头两个字符就能拆分出10
     * 结尾的0前面一定是1，否则这部分也能直接拆分出10
     *
     * 要通过交换两个相邻的特殊子序列 让字典序最大
     * 那么 对于不可分割的序列 除去头尾得到的特殊子序列应该排序为最大
     * 对于可分割的序列，将其分为多个子序列，每个子序列内部处理为最大序列后，再全部参与排序 字典序大的在前
     */
    string makeLargestSpecial(string s) {
        if(s.empty()) return s;
        int n = s.size(), one = 0;
        vector<string> sub;
        for(int i = 0, j = 0; i < n; i++){
            if(s[i] == '1') one++;
            else one--;
            if(one == 0) {
                if(j != 0 || i != n - 1)
                    sub.push_back(makeLargestSpecial(s.substr(j, i - j + 1)));
                j = i + 1;
            }
        }
        if(sub.empty()) return "1" + makeLargestSpecial(s.substr(1, n - 2)) + "0";
        sort(sub.begin(), sub.end());
        reverse(sub.begin(), sub.end());
        string res;
        for(string& son : sub)
            res += son;
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}