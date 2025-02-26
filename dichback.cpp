#include "dickback.h"
#include <iostream>
using namespace dichbackset;

#ifndef LOGIC_UNIT_MAX
#define LOGIC_UNIT_MAX 500
#endif

/*本文件是经过作者人工转译，由python->c++实现的，所以没啥注释*/

simple_struct::simple_struct(){
    allow_copy = false;
}

simple_struct::simple_struct(int* array_, int len_){
    allow_copy = true;
    array = array_;
    len = len_;
}

AlgorithmSet::AlgorithmSet(){
    // 初始化
    counts = 0;
    dba_lm_default = 3;
}

simple_struct AlgorithmSet::simple_exhaustion_algorithm(int unit_effective_array[], int effective_len){
    /*简单穷举法，默认使用逻辑与函数单元
    返回一个指针 指向yes_array的地址，即逻辑元判断为true的所有元素的地址*/
    counts = 0;
    
    // 手动回收堆
    int *yes_array = new int[effective_len];

    int yes_list_len = 0;

    for (int i = 0; i < effective_len; i++){

        int tmp_array[1] = {unit_effective_array[i]};
        bool ret = logic_unit(tmp_array, 1);

        if (ret){
            yes_array[yes_list_len++] = unit_effective_array[i];
            // private define
            counts++;
        }
    }
    if (yes_list_len == 0){
        delete []yes_array;
        simple_struct ret_struct(NULL, 0);
        return ret_struct;
    }

    simple_struct ret_struct(yes_array, yes_list_len);
    return ret_struct;
}

int AlgorithmSet::dichotomy_algorithm(int unit_effective_list[], int len){
    /*二分法，默认使用逻辑或函数单元，仅适用于寻找一个目标元素*/
    counts = 0;
    int min_num = 0;
    int max_num = len/2;
    int mark = len;

    if (len > LOGIC_UNIT_MAX){
        std::cerr<<"warning: input len is larger than LOGIC_UNIT_MAX: "<<LOGIC_UNIT_MAX<<std::endl;
        return -1;
    }

    while (1){
        int sub_unit[LOGIC_UNIT_MAX];
        int u = 0;
        for (int i = min_num; i < max_num; i++)
            sub_unit[u++] = unit_effective_list[i];

        bool ret = logic_unit(sub_unit, u);
        counts++;
        
        if (ret){
            mark = max_num;
            max_num = (mark + min_num)/2;
            // last one
            if (min_num == max_num){
                return unit_effective_list[min_num];
            }
            
        }else{

            min_num = max_num;
            max_num = (mark + min_num) / 2;

            if (min_num == max_num){
                int tmp[1] = {unit_effective_list[min_num]};
                if (logic_unit(tmp, 1)){
                    return unit_effective_list[min_num];
                }else{
                    std::cout<<"warning: dichback.dichtomy_algorithm: it is not an effective array"<<std::endl;
                    status = false;
                    return -1;
                }
            }
        }
    }
}

simple_struct AlgorithmSet::dichotomy_backtracking_algorithm(int unit_effective_list[], int len){
    // 如果<6别用
    if (len < 6){
        std::cout<<"unsuitable choice. len < 6"<<std::endl;
        simple_struct ret;
        return ret;
    }
    int min_num = 0;
    int max_num = len;
    int lm = len / dba_lm_default - 1;
    if (lm == 0){
        std::cout<<"unsuitable choice. (lm == 0)"<<std::endl;
        simple_struct ret;
        return ret;
    }
    counts = 0;
    int mark = max_num;
    int* mark_steps = new int[len];
    int mark_steps_index = 0;

    int* yes_list = new int[len];
    int yes_list_index = 0;

    while(1){

        int sub_unit[LOGIC_UNIT_MAX];
        int u = 0;
        for (int i = min_num; i < max_num; i++){
            sub_unit[u++] = unit_effective_list[i];
        }

        bool ret = logic_unit(sub_unit, u);
        counts++;

        if (ret){

            for (int i = min_num; i < max_num; i++){
                yes_list[yes_list_index++] = i;
            }
            if (mark == max_num){
                break;
            }
            min_num = max_num;
            if (mark_steps_index > 1){
                // 缩短界限
                mark_steps_index--;
                // 指向最后一个
                mark = mark_steps[mark_steps_index - 1];
                max_num = (min_num + mark)/2;
            }
            else{
                mark = mark_steps[mark_steps_index - 1];
                max_num = mark;
                mark_steps_index--;
            }
        }
        else{

            if (max_num - min_num <= lm){
                for (int i = min_num; i < max_num; i++){

                    int tmp_array[1] = {unit_effective_list[i]};

                    if (logic_unit(tmp_array, 1)){
                        yes_list[yes_list_index++] = i;
                        // private define
                        counts++;
                    }
                }

                min_num = max_num;
                max_num = mark;

                if (mark_steps_index > 1){
                    mark_steps_index--;
                    mark = mark_steps[mark_steps_index - 1];
                }
                else if(mark_steps_index == 1){
                    mark = mark_steps[mark_steps_index - 1];
                    mark_steps_index--;
                }
                else{
                    break;
                }

            }
            else{
                mark = max_num;
                mark_steps[mark_steps_index++] = mark;
                max_num = (mark + min_num) / 2;
            }

        }
    }
    // 收尾工作
    if (yes_list_index == 0){
        simple_struct ret_struct(NULL, 0);
        return ret_struct;
    }

    int* ret_yes_array = new int[yes_list_index];
    for (int i = 0; i < yes_list_index; i++){
        int tmp = yes_list[i];
        ret_yes_array[i] = unit_effective_list[tmp];
    }

    delete []yes_list;
    delete []mark_steps;

    // 不删ret_yes_array 因为要返回他
    simple_struct ret_struct(ret_yes_array, yes_list_index);
    return ret_struct;

}
