/**
 * @Time : 2022/9/20-10:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 数位dp
 * 采用记忆化搜索的方式求解
 */
class Solution {
public:
    /**
     * 数位dp的记忆化搜索，其实就是暴力backTrack加上记忆化
     * 从前往后按位置递归，每一个位置从可选的数字中依次尝试，递归到末尾根据情况返回方案数，满足要求就是1
     *
     * 可以选用的数字位0-9，刚好可以使用10位二进制位表示数字的使用情况
     * 比如 10100，可以表示数字2和数字4已经被使用过了
     * 因此可以使用mask来表示数字的选择情况，如同状态压缩dp中的那样
     *
     * 数字的选择从高位开始，因为高位的选择，会影响低位的选择范围
     * 比如 题目给的上限是 235。 第0位选择1，那么后两位从0-9任意选都不会超过235
     * 但如果第0位选择了2，那么第2位最大选择3
     * 因此需要参数i，表示当前要选择的是哪一位，那么前面[0,i-1]就已经选好了
     *
     * 由于高位的选择，影响下一位的数字范围
     * 还需要参数limit来表示，前置位j是否每一位数字都与相应的s[j]相等
     * 比如s = 2357, i = 2时
     * limit为true，就说明第0，1两为分别选了2，3，那么第2位，就只能选0-5
     * 反之，前面选的数字就保证了小于2357，第2位就可以任选0-9
     * （limit就可以粗略理解为前置位选到了极限大的情况）
     * 因此，当前位可选数字最大为 up = limit ? s[i] : 9
     * 在递归中，limit = limit && num[i] == up
     *
     * 还有一个特殊的点，要求没有前置0
     * 因此，还需要参数is_num来表示 前置位是否有选择数字，如果is_num为true表示前置位已选数字
     * 如果is_num为true，前面已选数字，当前位就能从0开始选
     * 否则，前面还没选择数字，当前位就继续不选（相当于填充无效的前导0），或者选择1-9中的数字做为开头
     * 因此:
     * 1.递归结束时，is_num为true才表示选择出一个数字，返回1；否则就是一个全是0的无效数字，返回0
     * 2.递归中，is_num为true，就不会再变为false；当前位继续不选，is_num保持为false，选了数字就变为true
     *
     * @param s: 给定的数字上界，即满足要求的数字 <= s
     * @param i: 表示当前要选择的是哪一位
     *      如果i == s.size()，说明所有位值的数字都已选完，此时要返回0或者1（is_num为true时），表示数字的数目
     * @param mask：表示数字的选择情况，即i前面所填数字集合为mask
     * @param is_limit：表示[0,i-1]上数字选择是否都与相应的s[j]相等
     *      如果为true，当前位数字最大为s[i];否则可以选0-9任意
     * @param is_num: 前置位是否有选择数字
     *
     * @return 从第i位开始填数字，且已用数字集合为mask，能构造出的满足题意的数字的 个数
     * 从返回值的定义也可以知道，此类问题是一个二维的记忆化搜索，用一个二维数组来做记忆化即可
     */
    string s;
    vector<vector<int>> dp;
    int solve(int n){
        s = to_string(n);
        dp = vector(s.size(), vector((1 << 10), - 1));
        // 初状态，要选第0位数字i = 0,；前面没有选择任何数字，数字集合的状态是mask = 0
        // 第0位数字不能超过s[0],所以limit=true；前面还没有任何数字，is_num = false
        return count(0, 0, true, false);
    }
    /**
     * 不需要对limit, is_num来进行记忆化
     * limit为true表示每一位都选到了s[i]，这样的情况不存在重复子问题，所以不需要对这个维度记忆化
     * 而is_num为false表示前置位全都不选任何数字，这样的情况也不存在重复子问题
     * 所以只有当 !limit && is_num的时候存在重复子问题，也只有此时才需要缓存
     */
    int count(int i, int mask, bool limit, bool is_num){
        if(i == s.size()) return is_num ? 1 : 0;
        if(!limit && is_num && dp[i][mask] != -1) return dp[i][mask];
        int cnt = 0;
        // 前置位没有选择数字，当前位的一种方案就是也不选择，那么is_num继续为false
        // 并且limit = false，因为前置位都跳过了，那么后面每一位如果要选数字，都可以任选
        if(!is_num) cnt = count(i + 1, mask, false, false);
        int up = limit ? s[i] - '0' : 9, down = is_num ? 0 : 1;
        for(int j = down; j <= up; j++){
            if(condition(j, mask)){
                int next_mask = (1 << j) | mask; // 更新所选集合
                cnt += count(i + 1, next_mask, limit && j == up, true);
            }
        }
        if(!limit && is_num) dp[i][mask] = cnt;
        return cnt;
    }

    // 重写：当前位所选数字与前置位已选集合mask是否满足题目要求
    bool condition(int j, int mask){
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}