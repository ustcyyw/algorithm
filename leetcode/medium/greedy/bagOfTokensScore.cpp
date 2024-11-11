/**
 * @Time : 2022/5/9-5:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 贪心
 * 如果能量够用来换分，此时通过减分去换能量，再把能量去换分
 * 这样的做法不如先换分，等能量不足再去换能量。
 *
 * 比较直观的是 应该先换能量消耗低的分，在用分换能量的时候，应该换能量最多的。
 */
class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        int res = 0, point = 0, lo = 0, hi = tokens.size() - 1;
        sort(tokens.begin(), tokens.end());
        while (lo <= hi && (power >= tokens[lo] || point > 0)){
            if(tokens[lo] <= power){
                point++;
                power -= tokens[lo++];
                res = max(res, point);
            } else {
                point--;
                power += tokens[hi--];
            }
        }
        return res;
    }
};

int main(){

}