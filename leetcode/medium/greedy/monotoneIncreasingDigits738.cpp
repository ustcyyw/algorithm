/**
 * @Time : 2023/3/18-4:26 PM
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
     * 贪心：尽可能地让高位的数字大
     * 从高位开始考虑
     * 如果下一个位置的数比当前位置大 当前位置不变，下一个位置的数-1也能保证递增性，且可以小于n
     *
     * 如果下一个位置的数比当前位置小，当前位置就需要减小1，否则就无法保证递增性，或者要保持递增性，就回比n大
     * 并且当前位置-1后，后续位置全部设置为9，满足递增性也一定比n小
     *
     * 如果下一个位置的数与当前相等，就取决于往后第一个不相等的数是多少，回到上述两种情况
     *
     */
    int monotoneIncreasingDigits(int n) {
        string num = to_string(n);
        int m = num.size();
        for(int i = 0; i < m - 1; i++){
            int j = i + 1;
            while (j < m && num[i] == num[j]) j++;
            if(j == m) break;
            if(num[i] > num[j]) {
                num[i] = (char)(num[i] - 1);
                while (++i < m) num[i] = '9';
                break;
            }
        }
        return stoi(num);
    }
};

int main(){
    Solution s;
    s.monotoneIncreasingDigits(10);
    cout << 0 << endl;
}