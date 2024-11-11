/**
 * @Time : 2023/9/28-11:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull T1 = (ull)1e13;
class Solution {
public:
    /*
     * 后缀计算和前缀计算分开 并且单独去找有多少个末尾的0
     * 后缀只需要5位 即只需要保留低位的5位计算就能得到精确值 但是要注意在过程中不断去掉0
     * cpp精度不够 过不了这题 得python 见后面
     */
    string abbreviateProduct(int left, int right) {
        ull num1 = left, num2 = left;
        bool flag = 0;
        for(int i = left + 1; i <= right; i++){
            num1 *= i, num2 *= i;
            // 需要近似计算前缀 且此时前缀不能被10整除，那么之后就不应该处理前缀的0
            if(num1 > T1 && num1 % 10 != 0) flag = true;
            while (num1 > T1) num1 /= 10;
            while (num2 % 10 == 0) num2 /= 10;
            num2 %= T1;
        }
        string  zero = "e" + to_string(countZero(left, right));
        if(!flag) // 需要处理前缀中的0，此时前缀仍然代表完整的一个数 末尾0是简写形式的
            while (num1 % 10 == 0) num1 /= 10;
        cout << num1 << endl;
        if(num1 < (ull)1e10)
            return to_string((long) num1) + zero;
        while (num1 >= 1e5) num1 /= 10;
        string temp = to_string((long) num2);
        return to_string((long) num1) + "..." + temp.substr(temp.size() - 5) + zero;
    }

    int countZero(int left, int right) {
        int two = 0, five = 0;
        function<vector<int>(int)> f = [](int num) -> vector<int> {
            int two = 0, five = 0;
            while (num % 2 == 0) num /= 2, two++;
            while (num % 5 == 0) num /= 5, five++;
            return {two, five};
        };
        for(int num = left; num <= right; num++) {
            vector<int> temp = f(num);
            two += temp[0], five += temp[1];
        }
        return min(two, five);
    }
};

/*
 *
T1, T2 = int(10 ** 20), int(10 ** 10)
class Solution:
    def abbreviateProduct(self, left: int, right: int) -> str:
        num1, num2 = left, left
        flag = False
        for i in range(left + 1, right + 1):
            num1, num2 = num1 * i, num2 * i
            if num1 > T1 and num1 % 10 != 0:
                flag = True
            while num1 > T1:
                num1 /= 10
            while num2 % 10 == 0:
                num2 /= 10
            num2 %= T2
        zero = "e" + str(self.count_zero(left, right))
        if not flag:
            while num1 % 10 == 0:
                num1 /= 10
        num1 = int(num1)
        if num1 < 10 ** 10:
            return str(num1) + zero
        while num1 > 10 ** 5:
            num1 /= 10
        num1, num2 = int(num1), int(num2)
        temp = str(num2)
        return str(num1) + "..." + temp[len(temp) - 5:] + zero


    def count_zero(self, left, right):
        two, five = 0, 0

        def f(num):
            a, b = 0, 0
            while num % 2 == 0:
                num, a = num / 2, a + 1
            while num % 5 == 0:
                num, b = num / 5, b + 1
            return a, b

        for i in range(left, right + 1):
            temp = f(i)
            two, five = two + temp[0], five + temp[1]
        return min(two, five)
 */

int main(){
    Solution s;
    
    cout << 0 << endl;
}