#ifndef LEXICAL_ANALYSIS__H
#define LEXICAL_ANALYSIS__H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using std::string;
using std::ifstream;
using std::ofstream;
enum SymbolType {
    ILLEGAL,            // 非法字符
    FINISH,             // 文件结尾

    IDENFR,     // 标识符
    INTCON,     // 整数常量
    CHARCON,    // 字符常量
    STRCON,     // 字符串

    CONSTTK,    //const关键字
    INTTK,      //int关键字
    CHARTK,     //char关键字
    VOIDTK,     //void关键字
    MAINTK,     //main关键字
    IFTK,       //if关键字
    ELSETK,     //else关键字
    DOTK,       //do关键字
    WHILETK,    //while关键字
    FORTK,      //for关键字
    SCANFTK,    //scanf关键字
    PRINTFTK,   //printf关键字
    RETURNTK,   //return关键字

    PLUS,       //加号 +
    MINU,       //减号 -
    MULT,       //乘号 *
    DIV,        //除号 /
    LSS,        //小于号 <
    LEQ,        //小于等于号 <=
    GRE,        //大于号 >
    GEQ,        //大于等于号 >=
    EQL,        //等于号 ==
    NEQ,        //不等号 !=
    ASSIGN,     //赋值号 =
    SEMICN,     //分号 ;
    COMMA,      //逗号 ,
    LPARENT,    //左圆括号 (
    RPARENT,    //右园括号 )
    LBRACK,     //左方括号 [
    RBRACK,     //右方括号 ]
    LBRACE,     //左尖括号 {
    RBRACE      //右尖括号 }
};
class Lexical_analysis
{
public:
	static Lexical_analysis& initialLexicalanalysis(ifstream& file,ofstream& ofs);
	void nextSymbol();
    void nextString();
    void nextChar();
	//void nextNum();
	SymbolType getSymbol();
private:
	ifstream &sourceFile;
	SymbolType symbolType;
	ofstream& fout;
	friend class Grammar_analysis;
	string save;
	Lexical_analysis(ifstream& file,ofstream& ofs);
	Lexical_analysis(const Lexical_analysis&);
	Lexical_analysis& operator  = (const Lexical_analysis&);
};


using std::ostream;
ostream& operator<< (ostream& ofs, SymbolType st);


#endif