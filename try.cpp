#include <iostream>
#include "dickback.h"

using namespace std;
using namespace dichbackset;

const char jb[100] = "jjjjjxjjjjjooooooooooooobbbbbbbbbbbjjjjjjjjjjjjjjjjjjssssssssssjjjjjjjjjjwkwwwwwwwww";

class dichtest:public AlgorithmSet{
private:
    bool logic_unit(int array[], int len);
};

bool dichtest::logic_unit(int array[], int len){
    for (int i = 0; i < len; i++){
        int k = array[i];
        if (jb[k] != 'j'){
            cout<<0;
            return false;
        }
    }
    cout<<1;
    return true;
}

int main(){
    dichtest test;
    int *array = new int[50];
    for (int i = 0; i < 50; i++){
        array[i] = i;
    }
    simple_struct ret = test.dichotomy_backtracking_algorithm(array, 50);
    cout<<endl;
    for (int i = 0; i < ret.len; i++){
        cout<<ret.array[i]<<' ';
    }

    int *bjj = NULL;
    delete bjj; 

}
