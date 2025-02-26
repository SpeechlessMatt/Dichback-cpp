#include "iostream"
#include "base64.h"
using namespace std;
#include "fstream"

int main(){
    char* sb="sbcnm";
    ofstream outfile("testout.bin", ios::out | ios::binary);
    outfile<<"sb";
    outfile.close();
    return 0;
}

