/**
 * @Time : 2022/6/29-8:37 PM
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
     * 枚举第一个字符串s1的时候，仅从让s1交换后不是原有的角度来说
     * 只需要对第一个字母枚举26个小写字母，然后判断是否是存在的词
     * 于是只需要关注另一个字符串s2的首字母是什么即可，很显然可以将其先预处理，按首字母i归类
     *
     * 比如s1的第一个字母换成a不是原有词，那么所有以a开头的s2都是可行的
     *
     * 但是还要保证s2第一个字母换成s1的第一个字母后，也不是原有的
     * 上述例子就是s2第一个字母换成a后，也不是原有的。
     * 因而，在按首字母归了一类之后，还需要第二个维度的细分，看交换之后s2是否满足题意
     * 第二个维度则是 交换首字母为j后，s2不是已存在单词。
     *
     * 定义： f[i][j]：首字母为i，替换为j后不是已存在单词的数量
     *
     * 那么最后的答案就是
     * 枚举每一个s1，针对s1首字母枚举，如果s1（假定首字母是a）换字母为b后，不是已存在的单词
     * 那么看首字母为b的，并且换为a后不是已存在单词的数量的其它字符串有多少，显然就是 f[b][a]
     */
    long long distinctNames(vector<string>& ideas) {
        unordered_set<string> set;
        for(auto & idea : ideas)
            set.insert(idea);
        int f[26][26] = {0};
        for(string idea : ideas){
            int a = idea[0] - 'a';
            for(int i = 0; i < 26; i++){
                idea[0] = i + 'a';
                if(!set.count(idea)) f[a][i]++; // 替换为i字母后，不是已存在单词
            }
        }
        long long res = 0;
        for(string idea : ideas){
            int a = idea[0] - 'a';
            for(int i = 0; i < 26; i++){
                idea[0] = i + 'a';
                // s1的首字母a可以换为i，然后再找首字母为i的组中，换为a不是已存在单词
                if(!set.count(idea)) res += f[i][a];
            }
        }
        return res;
    }

    long long distinctNames2(vector<string>& ideas) {
        unordered_set<string> set;
        for(auto & idea : ideas)
            set.insert(idea);
        int f[26][26] = {0};
        for(string idea : ideas){
            int a = idea[0] - 'a';
            for(int i = 0; i < 26; i++){
                idea[0] = i + 'a';
                if(!set.count(idea)) f[a][i]++; // 替换为i字母后，不是已存在单词
            }
        }
        // 上述对f[i][j]的预处理一致
        // 但是对于字符串，我们并不需要关注具体是哪个字符串作为s1来进行替换
        // 只需要关注第一个字符串，以什么字母开头。如以a开头，然后再考虑可以替换为哪一个字母，如替换为b
        // 那么第一个字符串，在这种情形下满足条件的有 f[a][b]
        // 第二个字符串要能给其提供交换的字母b，并且得到a之后满足条件，这样的字符串有f[b][a]
        // 因此要枚举第一个字母，再枚举可以替换的字母
        long long res = 0;
        for(int i = 0; i < 26; i++){
            for(int j = 0; j < 26; j++)
                res += f[i][j] * f[j][i];
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}