/**
 * @Time : 2022/5/30-2:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class SortedStack {
private:
    stack<int> arr, aux;
public:
    SortedStack() {

    }

    void push(int val) {
        while (!arr.empty() && arr.top() < val)
            aux.push(stackPop(arr));
        arr.push(val);
        while (!aux.empty())
            arr.push(stackPop(aux));
    }

    void pop() {
        if(!arr.empty()) arr.pop();
    }

    int peek() {
        return arr.empty() ? -1 : arr.top();
    }

    bool isEmpty() {
        return arr.empty();
    }

    int stackPop(stack<int>& stack){
        int res = stack.top();
        stack.pop();
        return res;
    }
};

int main(){

}