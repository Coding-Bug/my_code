#include "Grammar_analysis.h"
#include<iostream>
#include <fstream>
using namespace std;
using std::ofstream;



// 构造函数
Grammar_analysis::Grammar_analysis(Lexical_analysis &lexical_analysis, ofstream &ofs):fout(ofs){
    this->lexical_analysis=&lexical_analysis;
}

// 测试
void Grammar_analysis::text(){
    
}

// 获取类别码
void Grammar_analysis::getSymbol(){
    if (lexical_analysis->getSymbol() != FINISH) {
        lexical_analysis->nextSymbol();
        symbolType=lexical_analysis->getSymbol();
	}
}

// 程序的分析
void Grammar_analysis::passProgram(){
    bool isval = false;
    // 处理常量说明
    if (symbolType == CONSTTK) {
        //passConst();
    }
    // 处理变量说明和第一个有返回值函数定义
    // 变量说说明
    if (symbolType == INTTK || symbolType == CHARTK) {
        getSymbol();
        if (symbolType == IDENFR) {
            getSymbol();
            // 进入变量说明分支
            while (symbolType == COMMA || symbolType == SEMICN || symbolType == LBRACK) {
                isval = true;   // 有变量说明
                //passVar();   // 进入变量定义
                // 继续判断还有没有变量
                if (symbolType == INTTK || symbolType == CHARTK) {
                    getSymbol();
                    if (symbolType == IDENFR) {
                        getSymbol();
                    }
                    else { fout<<"syntax error";exit(0); }
                }
                else {
                    if (isval) {
                        fout << "<变量说明>" << endl;
                    }
                    break;
                }
            }
            // 对于正常结束的while循环，查看是否为有返回值函数定义
            // 因为有可能根本没有变量说明，这时候可能会有（有返回值函数）
            if (symbolType == LPARENT) {
                if (isval) { fout << "<变量说明>" << endl; }
                //passFun_return();
            }
        }
        else { fout<<"syntax error";exit(0); }// int和char后跟的不是标识符，则报错
    }

    // 处理有、无返回值的函数定义和主函数
    while (symbolType == VOIDTK || symbolType == INTTK || symbolType == CHARTK) {
        // 无返回值函数定义
        if (symbolType == VOIDTK) {
            getSymbol();
            // 主函数处理完直接返回
            if (symbolType == MAINTK) {
                //passMain();
                {fout << "<程序>" << endl; cout << "<程序>" << endl; }
                return;    
            }
            else if (symbolType == IDENFR) {// 无返回值函数定义处理完继续循环
                //passFun_void();
            }
            // void后面不是主函数也不是标识符，就退出
            else { fout<<"syntax error";exit(0); }
            // 有返回值函数定义的处理
        }
        else {  // 有返回值函数的定义
            getSymbol();
            if (symbolType == IDENFR) {
                getSymbol();
                //passFun_return();
            }
            else { fout<<"syntax error";exit(0); }
        }
    }
    // 没有主函数就报错
    fout<<"syntax error";exit(0);
    return;
}

// 常量说明
void Grammar_analysis::passConst() {
    int type;
    // 入口错误直接报错
    if (symbolType != CONSTTK) {fout<<"syntax error";exit(0); }

    getSymbol();
    // const不后是int或char
    if (symbolType != INTTK && symbolType != CHARTK) {              
        fout<<"syntax error";exit(0);
    }
    type = symbolType;   // 第一个常量的类型
    getSymbol();
    if (symbolType != IDENFR) { fout<<"syntax error";exit(0); }
    while (symbolType == IDENFR) {
        getSymbol();
        // 应是'='
        if (symbolType != ASSIGN) { fout<<"syntax error";exit(0); }
        getSymbol();

        //处理整数或者字符
        if (symbolType == PLUS || symbolType == MINU) {
           getSymbol();
        }

        // 如果取得的表值类型和常量定义的类型不一样，则报错
        if (!(symbolType == INTCON && type == INTTK) &&
            !(symbolType == CHARCON && type == CHARTK)) {
             fout<<"syntax error";exit(0);
        }
        

        // 整数要输出
        if (symbolType == INTCON)
        {
            fout << "<整数>" << endl;
        }

        getSymbol();
        

         // 逗号则还有常量，在内部循环，因为类型要和第一个类型一致
        if (symbolType == COMMA) {
            getSymbol();
        }
        else if (symbolType == SEMICN) {  //分豪则结束
            break;
        }
        else {  fout<<"syntax error";exit(0); }  // 其他非法
    }
    
    fout << "<常量定义>" << endl;
    getSymbol();
    
    //还是常量，则在定义内循环
    if (symbolType == CONSTTK) {
        passConst();
    }
    else {
        // 分号后不再是常量定义循环，常量说明结束.
        fout << "<常量说明>" << endl;
        return;
    }
}
