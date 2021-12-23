#ifndef GRAMMAR_ANALYSIS__H
#define GRAMMAR_ANALYSIS__H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include"Lexical_analysis.h"
using namespace std;

class Grammar_analysis{

private:
    Lexical_analysis* lexical_analysis;
    ofstream& fout;
    SymbolType symbolType;
    string word;  


    // 各种分析
    void passProgram();  // 处理主程序
    void passConst();    // 处理常量说明
    void passVar();      // 处理变量定义
    


public:
    Grammar_analysis (Lexical_analysis &lexical_analysis, ofstream &ofs);  //构造函数
    void text();
    void getSymbol();  // 读取一个识别码
    
    
    


   
    
};







#endif