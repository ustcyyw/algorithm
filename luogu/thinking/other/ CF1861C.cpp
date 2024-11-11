/**
 * @Time : 2023/12/6-9:32 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * +和- 影响了当前长度 使用cl表示当前序列的长度
 * 用len1表示现在已知的上升序列长度，用len0表示索引最小的下降元素的位置
 * （因为上升序列需要非递减，而非上升序列只要有一个位置的元素比上一个元素小即可）
 *
 * 当前遇到0
 * 1. cl < 2: 不可能完成，因为题目定义0或1个元素的序列是上升序列
 * 2. cl <= len1:  不可能完成，因为已知的上升序列长度已经超过或等于cl，那么[0,cl]上一定是上升序列
 * 如果已知的上升序列长度 >= cl 那就不可能完成
 * 3. 在可以完成的情况下 可能要更新 len0， 如果len0 == maxL，还没有设置索引最小下降元素元素，记len0 = cl
 * 为何要设置len0在序列最末端 是因为考虑遇到1判断的情况
 * 当前遇到1
 * 1. cl < 2: 满足
 * 2. cl >= len0: 不满足 因为在要求上升序列的[0,cl]区间，已经因为要满足0判断而设置了一个下降元素
 * 为了尽可能地通过判定，应当让len0大 所以回答了len0要更新为cl
 * 3. 在可以完成的情况下 更新len1 = cl
 *
 * 且注意 并且随着cl的变化 len1 和 len0 都会改变
 * 遇到-号，序列长度-1，那么已知的上升序列长度就得减小，最多是cl那么长 if(len1 > cl) len1 = cl;
 * 索引最小下降元素元素的位置已经小于cl的话，即if(len0 > cl)，说明当前序列无下降元素，设置len0 = maxL;
 */
#include<bits/stdc++.h>
using namespace std;

const int maxL = 1e9;
int T;
string s;

string solve() {
    int n = s.size(), len1 = 0, len0 = maxL, cl = 0;
    for(int i = 0; i < n; i++) {
        char c = s[i];
        if(c == '+') cl++;
        else if(c == '-') {
            cl--;
            if(len1 > cl) len1 = cl;
            if(len0 > cl) len0 = maxL;
        } else if(c == '1') {
            if(cl < 2 || cl < len0) len1 = cl;
            else return "NO";
        } else { // 遇到0的判定
            if(cl < 2 || cl <= len1) return "NO";
            else if(len0 == maxL) len0 = cl;
        }
    }
    return "YES";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> s;
        cout << solve() << endl;
    }
}