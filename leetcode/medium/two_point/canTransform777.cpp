/**
 * @Time : 2022/10/20-1:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 在一个由 'L' , 'R' 和 'X' 三个字符组成的字符串（例如"RXXLRXRXL"）中进行移动操作。一次移动操作指用一个"LX"替换一个"XL"，或者用一个"XR"替换一个"RX"。现给定起始字符串start和结束字符串end，请编写代码，当且仅当存在一系列移动操作使得start可以转换成end时， 返回True。

 

示例 :

输入: start = "RXXLRXRXL", end = "XRLXXRRLX"
输出: True
解释:
我们可以通过以下几步将start转换成end:
RXXLRXRXL ->
XRXLRXRXL ->
XRLXRXRXL ->
XRLXXRRXL ->
XRLXXRRLX
 

提示：

1 <= len(start) = len(end) <= 10000。
start和end中的字符串仅限于'L', 'R'和'X'。


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/swap-adjacent-in-lr-string
 */
class Solution {
public:
    bool canTransform(string start, string end) {
        int n = start.size();
        for(int i = n - 1, j = i; i >= 0; i--, j--){
            while (i >= 0 && end[i] != 'R') i--;
            while (j >= 0 && start[j] != 'R') {
                if(start[j] == 'L' && j <= i) break;
                j--;
            }
            if(i == 0 && j == -1) return false;
            if(j > i || (j != - 1 && start[j] == 'L')) return false;
        }
        for(int i = 0, j = 0; i < n; i++, j++){
            while (i < n && end[i] != 'L') i++;
            while (j < n && start[j] != 'L') {
                if(start[j] == 'R' && j >= i) break;
                j++;
            }
            if(i == n - 1 && j == n) return false;
            if(j < i || (j != n && start[j] == 'R')) return false;
        }
        return true;
    }
};

int main(){
    Solution s;
    s.canTransform("RXXLRXRXL", "XRLXXRRLX");
    cout << 0 << endl;
}