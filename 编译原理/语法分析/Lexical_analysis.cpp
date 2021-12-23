#include "Lexical_analysis.h"
#include <ctype.h>
#include <map>
#include <string>
#include <iostream>
#include<fstream>

using namespace std;
using std::ofstream;

static string strGot;
static char ch;
static map<string, SymbolType> reservedWords;

//单例
Lexical_analysis &Lexical_analysis::initialLexicalanalysis(ifstream &file,ofstream &ofs) {
    static Lexical_analysis theLexical_analysis(file,ofs);
    return theLexical_analysis;
}

//构造函数
Lexical_analysis::Lexical_analysis(ifstream &file,ofstream &ofs) : sourceFile(file),fout(ofs),save("") {
    ch = sourceFile.get();
    //fout.open("output.txt");
//保留字表
#define INSERT_RES(str, type)    \
        reservedWords.insert(pair<string, SymbolType>(str, type))   // 定义宏，简化填表代码
    INSERT_RES("const", CONSTTK);
    INSERT_RES("int", INTTK);
    INSERT_RES("char", CHARTK);
    INSERT_RES("void", VOIDTK);
    INSERT_RES("main", MAINTK);
    INSERT_RES("if", IFTK);
    INSERT_RES("else", ELSETK);
    INSERT_RES("do", DOTK);
    INSERT_RES("while", WHILETK);
    INSERT_RES("for", FORTK);
    INSERT_RES("scanf", SCANFTK);
    INSERT_RES("printf", PRINTFTK);
    INSERT_RES("return", RETURNTK);
#undef  INSERT_RES
}

SymbolType Lexical_analysis::getSymbol() {
    return symbolType;
}

#define GET     ch = sourceFile.get()   // 定义宏，简化从文件中读取一个字符的操作
#define PEEK    ch = sourceFile.peek()  // 定义宏，简化查看文件流第一个字符的操作
#define ADD(c)  save.append(1, c)     // 定义宏，简化往字符串结尾添加字符的操作


//词法分析部分
void Lexical_analysis::nextSymbol() {
    while (isspace(ch)) {
        GET;
    }
    if (isdigit(ch)) {  // 开头是数字
        symbolType = INTCON;
		save.clear();
		ADD(ch);
        for (GET; isdigit(ch); GET) {
			ADD(ch);
        }
    } else if (isalpha(ch) || ch == '_') {  // 开头是字母
        strGot.clear();
		save.clear();
        ADD(ch);
        for (GET; isalpha(ch) || isdigit(ch)|| ch == '_'; GET) {
            ADD(ch);
        }
        map<string, SymbolType>::iterator it = reservedWords.find(save);
        if (it == reservedWords.end()) {  // 非保留字则标识符
            symbolType = IDENFR;
        } else {
            symbolType = it->second;
        }
    } else {
		save.clear();
        ADD(ch);                            // 先把待判断的字符加入字符串

        switch (ch) {
            case '+':
				symbolType = PLUS;
                break;
            case '-':
				symbolType = MINU;
                break;
            case '*':
                symbolType = MULT;
                break;
            case '/':
                symbolType = DIV;
                break;
            case '<':
                PEEK;  // 流已向前移动，所以第一个就是下一个
                if (ch == '=') {
                    GET;
					ADD(ch);
                    symbolType = LEQ;
                } else {
                    symbolType = LSS;
                }
                break;
            case '>':
                PEEK;
                if (ch == '=') {
                    GET;
					ADD(ch);
                    symbolType = GEQ;
                } else {
                    symbolType = GRE;
                }
                break;
            case '=':
                PEEK;
                if (ch == '=') {
                    GET;
					ADD(ch);
                    symbolType = EQL;
                } else {
                    symbolType = ASSIGN;
                }
                break;
            case '!':
                PEEK;
                if (ch == '=') {
                    GET;
					ADD(ch);
                    symbolType = NEQ;
                }
                break;
            case ';':
                symbolType = SEMICN;
                break;
            case ',':
                symbolType = COMMA;
                break;
            case '(':
                symbolType = LPARENT;
                break;
            case ')':
                symbolType = RPARENT;
                break;
            case '[':
                symbolType = LBRACK;
                break;
            case ']':
                symbolType = RBRACK;
                break;
            case '{':
                symbolType = LBRACE;
                break;
            case '}':
                symbolType = RBRACE;
                break;
            case '\'':
                GET;
                nextChar();
                break;
            case '\"':
                GET;
                nextString();
                break;
            case EOF:
                symbolType = FINISH;
                fout.close();
                break;
            default:
                symbolType = ILLEGAL;
                break;
        }
        GET;
    }
	
	fout << symbolType << ' ' << save << endl;
	
}



void Lexical_analysis::nextString() {
	save.clear();
    while (ch == 32 || ch == 33 || (ch >= 35 && ch <= 126)) {
        ADD(ch);
        GET;
    }
    // 这里，循环跳出时，ch 是一个新的未处理的字符，逻辑正确
    if (ch != '\"') {           // 读到非法字符
        symbolType = ILLEGAL;   // 返回 ILLEGAL 类型
		save.clear();
        ADD(ch);                // 将非法的字符存入 token 中，
                                //  此时 token 中只有这一个非法字符
        GET;                    // 不要忘了再读一个备用！！！（因为下次直接在这个上分析）
    } else
        symbolType = STRCON;    // 正常，返回 STRING

}

void Lexical_analysis::nextChar() {
    while (isspace(ch))
        GET;                    // 跳过空白符
	save.clear();
    ADD(ch);
    if (isalnum(ch) || ch == '_'|| ch=='+' || ch =='-' || ch == '*' || ch=='/')            // 是合法字符，即字母或数字字符
        symbolType = CHARCON;
    else                        // 非法字符
        symbolType = ILLEGAL;
    GET;                        // get 一个新的字符备用！！
}
//SymbolType << 运算符重载,输出enum对应字符串
ostream &operator<<(ostream &ofs, SymbolType st) {
    switch (st) {

#define case(type) case type:       \
    ofs << #type;                   \
    break                           // 定义宏，简化 case 语句的输入， //#表示指向参数的type
        case(IDENFR);     // 标识符
        case(INTCON);     // 整数常量
        case(CHARCON);    // 字符常量
        case(STRCON);     // 字符串
        case(CONSTTK);    //const关键字
        case(INTTK);      //int关键字
        case(CHARTK);     //char关键字
        case(VOIDTK);     //void关键字
        case(MAINTK);     //main关键字
        case(IFTK);       //if关键字
        case(ELSETK);     //else关键字
        case(DOTK);       //do关键字
        case(WHILETK);    //while关键字
        case(FORTK);      //for关键字
        case(SCANFTK);    //scanf关键字
        case(PRINTFTK);   //printf关键字
        case(RETURNTK);   //return关键字

        case(PLUS);       //加号 +
        case(MINU);       //减号 -
        case(MULT);       //乘号 *
        case(DIV);        //除号 /
        case(LSS);        //小于号 <
        case(LEQ);        //小于等于号 <=
        case(GRE);        //大于号 >
        case(GEQ);        //大于等于号 >=
        case(EQL);        //等于号 ==
        case(NEQ);        //不等号 !=
        case(ASSIGN);     //赋值号 =
        case(SEMICN);     //分号 ;
        case(COMMA);      //逗号 ,
        case(LPARENT);    //左圆括号 (
        case(RPARENT);    //右园括号 )
        case(LBRACK);     //左方括号 [
        case(RBRACK);     //右方括号 ]
        case(LBRACE);     //左尖括号 {
        case(RBRACE);      //右尖括号 }
#undef case                       // 取消定义 case，让出这个名字（就是用完后还回去）
        default:
            break;
    }
    return ofs;
}