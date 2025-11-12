/**
 * @Time : 2024/12/29-5:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3403 贪心
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 贪心的想 肯定是要找最大字母开头的 在这些相同的开头的子串中
     * 再找第二个字母相同的
     * 假设已经找到了答案为s[i,j]，显然s[i,j+1]字典序更大
     * 那为什么不取s[i,j+1]只有两种情况
     * 1.再多取一个字母给它 字母就不够分了 所以答案子串最长为 n - k + 1
     * 2.j+1已经超过了s的长度
     * 因此直接暴力取子串比大小即可
     *
     * 注意如果k=1，就直接返回s即可
     */
    string answerString(string word, int k) {
        if(k == 1) return word;
        int n = word.size();
        vector<string> arr;
        for(int i = 0, j = n - k; i < n; i++, j = min(j + 1, n - 1)) {
            int len = j - i + 1;
            arr.push_back(word.substr(i, len));
        }
        sort(arr.begin(), arr.end());
        return arr.back();
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}