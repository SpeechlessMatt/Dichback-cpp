#include <iostream>
#include <cstring>
#include <fstream>

#include "dickback.h"
#include "base64.h"

#ifndef MAX_SIZE
// 必须是6的倍数
#define MAX_SIZE 120
#endif

using namespace std;
using namespace oceanstar;
using namespace dichbackset;


int main(int argc, char* argv[]) {

    if (argc > 2){
        cout<<"NOT AVAILBALE.";
    }

    char* file_loc = argv[1];

    if (argc == 1){
        file_loc = (char *)"1.bin";
    }
    cout<<file_loc<<endl;

    // 以二进制形式打开资源文件 1.bin
    ifstream filestream(file_loc, ios::binary|ios::in);
    // 文件打开失败
    if (!filestream) {
        cerr << "error" << endl;
        return 1;
    }

    // 缓冲区buffer
    char buffer[MAX_SIZE];
    char *pbuffer = buffer;
    int part_num = 0;

    while (true){
        // 跳转到下一块
        filestream.seekg(part_num++ * MAX_SIZE);
        filestream.read(buffer, MAX_SIZE);
        // 实际读取字节数
        int actual_read_byte = filestream.gcount();
        if (actual_read_byte == 0){
            break;
        }

        char *enc_str = (char *)base64_encode(pbuffer, filestream.gcount());
        cout<<enc_str<<endl;
        cout<<strlen(enc_str)<<endl;

        free(enc_str);
    }

    filestream.close();
	return 0;
}