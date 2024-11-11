/**
 * @Time : 2023/3/29-11:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string strWithout3a3b(int a, int b) {
        string res;
        while (a + b > 0){
            int n = res.size();
            if(a >= b) {
                if(n < 2 || res[n - 1] == 'b' || res[n - 2] == 'b') push(res, 'a', a);
                else push(res, 'b', b);
            } else { // b > a
                if(n < 2 || res[n - 1] == 'a' || res[n - 2] == 'a') push(res, 'b', b);
                else push(res, 'a', a);
            }
        }
        return res;
    }

    void push(string& res, char c, int& a){
        res.push_back(c);
        a--;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}