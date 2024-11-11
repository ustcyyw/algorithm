/**
 * @Time : 2022/5/22-2:04 PM
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
     * 执行用时：176 ms, 在所有 C++ 提交中击败了51.42%的用户
     * 内存消耗：48.9 MB, 在所有 C++ 提交中击败了40.84%的用户
     *
     * 状态可以唯一地确定当前还需要多少分数
     */
    int maxPoint;
    vector<int> cache;
    bool canIWin(int maxPoint, int desiredTotal) {
        this -> maxPoint = maxPoint;
        if(maxPoint * (maxPoint + 1) / 2 < desiredTotal) return false;
        int status = (1 << maxPoint) - 1;
        cache.assign(status + 1, 0);
        return select(status, desiredTotal) == 1;
    }
    /**
     * 如果还需要的分数 need = total - statusToPoint(status) 已经小于当前的可选择一个数字
     * 或者当前选手挑选某个数字后，让下一个选手一定会输
     * 这两种情况下，当前选手一定能获胜。
     *
     * 如果所有备选的数字，都不能出现上述两种情况，说明当前选手一定会输，返回2
     */
    int select(int status, int total){
        if(cache[status] != 0) return cache[status];
        int res = 2, need = total - statusToPoint(status);
        // 这里的i就是备选的数字。mask & status查看该数字是否已经被使用
        for(int i = 1, mask = 1; i <= maxPoint; i++, mask <<= 1){
            if((mask & status) && (need <= i || select(mask ^ status, total) == 2)) {
                res = 1;
                break;
            }
        }
        cache[status] = res;
        return res;
    }

    int statusToPoint(int status){
        int point = 0;
        for(int i = 1, mask = 1; i <= maxPoint; i++, mask <<= 1)
            if(!(mask & status)) point += i;
        return point;
    }
};

int main(){
    Solution s;
    cout << s.canIWin(10, 11) << endl;
    cout << s.canIWin(10, 0) << endl;
    cout << s.canIWin(10, 1) << endl;
    cout << s.canIWin(4, 6) << endl;

}