#define DEBUG

#include <iostream>
#include <cstring>
#include <fstream>

#include "dickback.h"
#include "base64.h"

#ifndef READ_MAX_SIZE
// 必须是6的倍数
#define READ_MAX_SIZE 120
#endif

using namespace std;
using namespace oceanstar;
using namespace dichbackset;

// 特殊量定义
char COND = ' ';
string origin_str = "aaaajjjj";
const char candidate[] = "+/0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const int candidate_len = strlen(candidate);
// 采用base64
const int max_str_len = READ_MAX_SIZE * 4 / 3;

class le_dich:public AlgorithmSet{
private:
    bool logic_unit(int array[], int len);
};

// 测试环境
// bool le_dich::logic_unit(int array[], int len){
//     // le_logic: 当全部<= cond 的时候才返回true 逻辑和形式
//     for (int i = 0; i < len; i++){
//         int k = array[i];
//         if (origin_str[k] > COND){
//             cout<<0;
//             return false;
//         }
//     }
//     cout<<1;
//     return true;
// }

bool le_dich::logic_unit(int array[], int len){
    // le_logic: 当全部<= cond 的时候才返回true 逻辑和形式
    cout<<"Input:";
    bool usr_inp;
    cin>>usr_inp;
    if (usr_inp){
        return true;
    }else{
        return false;
    }
}

#define INIT 0
void init_list(int input_len, int** big_list, char** possible_list){
    int* init_big_p = new int[max_str_len];
    for (int i = 0; i < input_len; i++){
        init_big_p[i] = i;
    }
    big_list[INIT] = init_big_p;

    char* init_possible_p = new char[candidate_len];
    for (int i = 0; i < candidate_len; i++){
        init_possible_p[i] = candidate[i];
    }
    possible_list[INIT] = init_possible_p;
}

void le_dib_main(int input_len, int least_split_degree = 1){
    le_dich getRangeLE;

    int* big_list[max_str_len];
    int big_list_len = 0;
    int* temp_big_list[max_str_len];
    int temp_big_list_len = 0;

    char* possible_chars[candidate_len];
    int possible_chars_len = 0;
    char* temp_possible_chars[candidate_len];
    int temp_possible_chars_len = 0;
    // Init
    init_list(input_len, big_list, possible_chars);
    big_list_len++;
    possible_chars_len++;

    // record length of every splited piece
    int rec_biglist_len[candidate_len] = {input_len};
    int temp_rec_biglist_len[candidate_len] = {};

    int rec_poschars_len[candidate_len] = {candidate_len};
    int temp_rec_poschars_len[candidate_len] = {};

    while (possible_chars_len != 0){

        for (int i = 0; i < possible_chars_len; i++){
            char* sublist = possible_chars[i];
            int split_1_len = rec_poschars_len[i]/2;
            int split_2_len = rec_poschars_len[i] - split_1_len;
            temp_rec_poschars_len[i*2] = split_1_len;
            temp_rec_poschars_len[i*2 + 1] = split_2_len;

            char* split_1 = new char[split_1_len];
            char* split_2 = new char[split_2_len];

            for (int j = 0, k = 0; j < split_1_len; j++){
                split_1[k++] = sublist[j];
            }
            temp_possible_chars[temp_possible_chars_len++] = split_1;

            for (int j = split_1_len, k = 0; j < split_1_len + split_2_len; j++){
                split_2[k++] = sublist[j];
            }
            temp_possible_chars[temp_possible_chars_len++] = split_2;
            delete []sublist;
            possible_chars[i] = NULL;
        }

        possible_chars_len = 0;

        // possible_chars 的所有子指针空间都已经被释放了
        for (int i = 0; i < big_list_len; i++){
            int* sublist = big_list[i];
            int end_index = temp_rec_poschars_len[i*2] - 1; 
            COND = temp_possible_chars[i*2][end_index];

            simple_struct ret_list;
            if (rec_biglist_len[i] > 6){
                ret_list = getRangeLE.dichotomy_backtracking_algorithm(sublist, rec_biglist_len[i]);
            }else{
                ret_list = getRangeLE.simple_exhaustion_algorithm(sublist, rec_biglist_len[i]);
            }
            // 初始化一下指针
            int* right_list = 0;
            int* left_list = 0;

            // 空的 全是false
            if (ret_list.len == 0){
                // 直接偷懒 不释放sublist空间
                right_list = sublist;
                delete []ret_list.array;
            // 全是true
            }else if (ret_list.len == rec_biglist_len[i]){
                // 直接偷懒 不释放sublist空间
                left_list = sublist;
                delete []ret_list.array;

            }else{
                // 记得释放sublist空间
                // 懒得复制过来，直接用simple_struct的空间
                left_list = ret_list.array;
                right_list = new int[rec_biglist_len[i] - ret_list.len];

                int sub_index = 0, tmp_index = 0;
                // 列表取补集
                for (int j = 0; j < ret_list.len; j++){

                    while (left_list[j] != sublist[sub_index]){
                        right_list[tmp_index++] = sublist[sub_index++];
                    }
                    sub_index++;
                }

                for (int j = sub_index; j < rec_biglist_len[i]; j++){
                    right_list[tmp_index++] = sublist[j];
                }

                delete []sublist;
            }

            // 重置big_list
            big_list[i] = NULL;

            temp_big_list[temp_big_list_len++] = left_list;
            temp_big_list[temp_big_list_len++] = right_list;

            temp_rec_biglist_len[i*2] = ret_list.len;
            temp_rec_biglist_len[i*2 + 1] = rec_biglist_len[i] - ret_list.len;

            rec_biglist_len[i] = 0;
        }

        big_list_len = 0;

        // 空列表清除 + 最小列表引出
        for (int i = 0; i < temp_big_list_len; i++){

            if (temp_rec_biglist_len[i] != 0 && temp_rec_poschars_len[i] > least_split_degree){
                rec_biglist_len[big_list_len] = temp_rec_biglist_len[i];
                rec_poschars_len[possible_chars_len] = temp_rec_poschars_len[i];
                possible_chars[possible_chars_len] = temp_possible_chars[i];
                big_list[big_list_len] = temp_big_list[i];

                possible_chars_len++;
                big_list_len++;
            // 如果rec里面记录biglist大小为0，则没有申请空间
            // temp_big_list和temp_possible一起释放了
            // 修改！
            // 引出结果:
            }else if (temp_rec_biglist_len[i] != 0 && temp_rec_poschars_len[i] <= least_split_degree){
                delete []temp_possible_chars[i];
                delete []temp_big_list[i];
            // 无候选 删除possible_chars对应的 不删big_list
            }else if (temp_rec_biglist_len[i] == 0){
                delete []temp_possible_chars[i];
            }
            
            // 初始化temp
            temp_rec_biglist_len[i] = 0;
            temp_rec_poschars_len[i] = 0;
            temp_big_list[i] = 0;
            temp_possible_chars[i] = 0;
        }
        // 初始化
        temp_big_list_len = 0;
        temp_possible_chars_len = 0;
    }
}

int main(int argc, char* argv[]){
    le_dib_main(8);
	return 0;
}