/**
 * @Time : 2022/5/19-9:22 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * target的长度最长为15，因此可以用一个int表示target每一个字符是否已经被拼接出来了
 * state(i)：第i位二进制数。 state(i) = 1表示还没完成匹配。
 * target长度为n，则初始状态每一个字母都未匹配 state = 1 << n - 1 刚好是n位为1的二进制数
 *
 * 对于某个状态，能让其最小拼接成功，就需要尝试当前用所有贴纸拼接一次，继续去看拼接后的状态
 */
class Solution {
public:
    /**
     * 执行用时：340 ms, 在所有 C++ 提交中击败了68.48%的用户
     * 内存消耗：11.4 MB, 在所有 C++ 提交中击败了82.23%的用户
     */
    int MAX_VALUE = 10000;
    unordered_map<int, int> cache; // state -> minStep
    int minStickers(vector<string>& stickers, string target) {
        int n = target.size(), state = (1 << n) - 1;
        int res = minStep(stickers, target, n, state);
        return res == MAX_VALUE ? -1 : res;
    }

    int minStep(vector<string>& stickers, string target, int n, int state){
        if(state == 0) return 0;
        if(cache.find(state) != cache.end()) return cache[state];
        int res = MAX_VALUE ;
        for(string& sticker : stickers){
            int next = state;
            for(char c : sticker){
                for(int j = 0, mask = 1; j < n; j++, mask <<= 1){
                    if(target[j] == c && (next & mask) != 0){
                        next = next ^ mask;
                        break;
                    }
                }
            }
            if(next != state)
               res = min(res, minStep(stickers, target, n, next) + 1);
        }
        cache[state] = res;
        return res;
    }
};

int main(){
    Solution s;
    vector<string> v = {"with","example","science"};
    s.minStickers(v, "thehat");
}