/**
 * @Time : 2023/5/18-1:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

string arr_to_string(vector<int>& arr) {
    string res = "";
    for(int i = 0, n = arr.size(); i < arr.size(); i++){
        res += to_string(arr[i]);
        if(i != n -1) res += " ";
    }
    return res;
}

int main(){

    cout << 0 << endl;
}