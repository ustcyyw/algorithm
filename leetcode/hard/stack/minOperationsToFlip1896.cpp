/**
 * @Time : 2023/11/18-2:22 PM
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
     * 如果是给定一个二叉树 二叉树的叶子结点是0/1 其它结点是或运输/与运算
     * 翻转二叉树的值，最小操作次数 显然是一个递归
     *
     * 0|0：左右子树的值都是0 要翻转整棵树的值 只需要将其中一个子树改为1即可
     * min(flip(x.left), flip(x.right))
     * 1|0 (0|1)：可以将1翻转为0 或者将|用一次操作变为&。
     * 将子树的1翻转为0 至少也需要一次操作，因此最优的办法就是将|变为&
     * 1|1：将一个子树的1变为0，并且改变|为&，同理 两个子树都变为1的操作次数不会少于前述方案
     * min(flip(x.left), flip(x.right)) + 1
     *
     * 0&0：将一个子树的0变为1，并且改变|为&
     * min(flip(x.left), flip(x.right)) + 1
     * 1&0 (0&1)：将&用一次操作变为|。
     * 1&1：将其中一个子树改为0即可 min(flip(x.left), flip(x.right))
     *
     * 但本题给的是一个逻辑表达式 如果将逻辑表达式先转化为二叉树 最坏是n^2的时间复杂度
     * 可以借鉴lc224 lc726 题的做法
     * 使用一个变量表示左子树的值 用一个变量表示操作符号 在遍历的过程中将当前值做为右子树的值。
     * 由于有括号的存在 需要使用两个栈 一个栈存值 一个栈存操作符号
     * 在计算完括号中的内容后才与前面的值进行计算
     *
     * 本题中不仅要计算表达式的值 同时也需要计算翻转值所用的次数
     * 因此应该使用一个二元的结构来表示信息 pair<int,int>。
     * p.first 为表达式的值 p.second 表示翻转该表达式最小操作次数
     */
    int minOperationsToFlip(string expression) {
        stack<pair<int, int>> s1;
        stack<char> s2; // 存放操作符号
        pair<int, int> cur = {-1, -1};
        char ope = '.';
        for(char c : expression) {
            if(c == '|' || c == '&') { // 相当于非叶子结点 要等后续拿到右子树的值才进行计算
                ope = c;
            } else if(c == '0' || c == '1') {
                int val = c - '0';
                cur = eval_flip(cur, ope, {val, 1});
            } else if(c == '(') {
                s1.push(cur), s2.push(ope);
                cur = {-1, -1}, ope = '.'; // 重制 表示当前括号这一层 还没有左子树
            } else { // 遇到右括号 表示当前层计算结束 要返回这个值与前置左子树（若存在）做计算
                pair<int, int>& pre = s1.top();
                ope = s2.top();
                cur = eval_flip(pre, ope, cur);
                s1.pop(), s2.pop();
            }
        }
        return cur.second;
    }

    pair<int,int> eval_flip(pair<int, int> left, char ope, pair<int, int> right) {
        if(ope == '.') return right; // 这是当前第一个值 不用计算直接返回
        int t1 = left.first + right.first, t2 = min(left.second, right.second);
        if(ope == '|') {
            if(t1 == 0) return {0, t2};
            if(t1 == 1) return {1, 1};
            if(t1 == 2) return {1, t2 + 1};
        } else { // 与运算
            if(t1 == 0) return {0, t2 + 1};
            if(t1 == 1) return {0, 1};
            if(t1 == 2) return {1, t2};
        }
        return {-1, -1};
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}