/**
 * @Time : 2022/11/11-4:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * even是偶数
     * 01字符串
     * 1.奇数位置要么都是0（相应的偶数位置都是1）
     * 2.要么奇数位置都是1（相应的偶数位置都是0）
     * 用odd0,even0分别表示奇数/偶数位置的0的数量；odd1,even1分别表示奇数/偶数位置的1的数量
     * 那么1这种情况，不用改变的元素数量就是 odd0 + even1，要改变的数量就是 n - (odd0 + even1)
     * 情况2，同理要改变的数量就是 n - (odd1 + even0)
     *
     * 随着操作1的进行，每次将第一个元素放到末尾
     * 奇数位置和偶数位置的1，0相互转换。
     * 只要注意位置0的元素，左移1位变成-1，但会被放到末尾n-1这个位置，这导致了奇偶的转换是不一定的
     * base的情况是 odd1 = even1, odd0 = even0;
     *
     * 但是第一个元素的特殊性
     * 如果索引0的元素是1，被放到末尾索引是偶数
     * 那么奇数0本该是 odd1 = even1的，但-1的元素又被放在末尾偶数位置，因此odd1再减少1
     * 变换之后的even1，就通过 even1 = total1 - odd1来计算
     *
     * 0的统计类似地计算。
     *
     * 执行用时：20 ms, 在所有 C++ 提交中击败了96.83%的用户
     * 内存消耗：11.1 MB, 在所有 C++ 提交中击败了80.95%的用户
     */
    int minFlips(string s) {
        int odd0 = 0, odd1 = 0, even0 = 0, even1 = 0, n = s.size();
        bool flag = (n - 1) % 2 == 0; // 最后一个索引是否为奇数
        for(int i = 0; i < n; i++){
            if(i % 2 == 0) {
                if(s[i] == '0') even0++;
                else even1++;
            } else {
                if(s[i] == '0') odd0++;
                else odd1++;
            }
        }
        int total0 = odd0 + even0, total1 = odd1 + even1, res = INT_MAX;
        for(char c : s){
            int t1 = n - (even1 + odd0); // 偶数位置都是1的情况，那么奇数位置就都是0
            int t2 = n - (even0 + odd1); // 偶数位置都是0的情况，那么奇数位置就都是1
            res = min(res, min(t1, t2));
            odd1 = even1, odd0 = even0;
            // 移动一个位置，偶数位置都变奇数位置，但是0变-1之后调到尾部，尾部是偶数的话，奇数位置的就减少1
            if(c == '1' && flag) odd1--;
            if(c == '0' && flag) odd0--;
            even1 = total1 - odd1, even0 = total0 - odd0;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}