/**
 * @Time : 2022/12/15-9:50 AM
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
     * 在k >= 2的情况下
     * 如果想交换两个相邻的字母
     * 1.可以不断把第一个字母移动到最后,直到将两个要交换的字母移动到前两个位置
     * 这个过程中其它字母在环中的顺序没有改变
     * 2.要交换的两个字母现在顺序为ab。然后将b先移动到最后，再将a移动到最后
     * 这两个字母在字符串末尾顺序就变成了ba。
     * 这个过程中其它字母在环中的顺序没有改变
     *
     * 于是我们可以在保证其它字母顺序的情况下，交换任意两个相邻的字母
     * 这样就可以通过冒泡排序将整个字符串进行排序
     *
     * 在k = 1时，就是简单的轮转
     */
    string orderlyQueue(string s, int k) {
        if(k >= 2) {
            sort(s.begin(), s.end());
            return s;
        }
        int n = s.size();
        string t = s;
        for(int i = 0; i < n - 1; i++){
            s.push_back(s.back());
            s.erase(0, 1);
            if(s < t) t = s;
        }
        return t;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}