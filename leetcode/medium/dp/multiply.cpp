/**
 * @Time : 2022/6/9-5:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    unordered_map<int, int> cache;
    int multiply(int A, int B) {
        if(A == 1) return B;
        if(B == 1) return A;
        return mul(A, B);
    }

    int mul(int a, int b){
        if(a == 1) return b;
        if(cache.find(a) != cache.end()) return cache[a];
        int half = a >> 1, temp = mul(half, b);
        int res = half << 1 == a ? temp << 1 : (temp << 1) + b;
        cache[a] =  res;
        return res;
    }
};

int main(){

}