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
        word=lexical_analysis->save;
	}
}

// 程序的分析
void Grammar_analysis::passProgram(){
    bool isval = false;
    
    // 处理常量说明
    if (symbolType == CONSTTK) {
        passConst();
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

                passVar();   // 进入变量定义
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
                passFun_return();
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


// 变量定义
void Grammar_analysis::passVar(){
    while (symbolType == SEMICN || symbolType == COMMA || symbolType == LBRACK) {
        //标志为';'时变量定义结束
        if (symbolType == SEMICN) {
            // 一遍变量定义结束
            fout << "<变量定义>" << endl;
            getSymbol();
            return;
        }
        else if (symbolType == COMMA) {  //标志为','
            getSymbol();
            if (symbolType == IDENFR) {
                getSymbol();
                // 变量定义大括号循环
            }
            else {  fout<<"syntax error";exit(0); }// ','后要跟标识符，否则报错
        }
        else if (symbolType == LBRACK) { // 标志为'['
            getSymbol();
            // 数组的元素要为大于0的无符号整数
            if (symbolType != INTCON || word == "0") { fout<<"syntax error";exit(0); }
            getSymbol();
            if (symbolType == RBRACK) {
                getSymbol();
                // 变量定义大括号循环
            }        
            else { fout<<"syntax error";exit(0); }//整数后非']'，则数组定义错误
        }
    }
    fout<<"syntax error";exit(0);  // 变量定义失败
}

// 有返回值的函数定义
// 待修改
void Grammar_analysis::passFun_return(){
    // 本分析从声明头部进入，先输出声明头部
    fout << "<声明头部>" << endl;
    
    //声明头部后面应该跟'('
    if (symbolType != LPARENT) { fout<<"syntax error";exit(0); } 
    getSymbol();
    

    // 判断参数表
    passParaList();
    
    // 参数表后是')'
    if (symbolType != RPARENT) { fout<<"syntax error";exit(0); }
    else {
        getSymbol();
    }
    
    //接着是'{'
    if (symbolType != LBRACE) { fout<<"syntax error";exit(0); }
    getSymbol();

    //复合语句
    //passCompound();

    if (symbolType != RBRACE) { fout<<"syntax error";exit(0); }
    
    fout << "<有返回值函数定义>" << endl;
    getSymbol(); //接受下一个
}

// 无返回值的函数定义
void Grammar_analysis::passFun_void(){

    string name = word;
    // void 后面是标识符
    if (symbolType != IDENFR) { fout<<"syntax error";exit(0); }
    getSymbol();

    // 与有返回差不多

    if (symbolType != LPARENT) { fout<<"syntax error";exit(0); }
    getSymbol();

    //passParaList(); // 参数表

    if (symbolType != RPARENT) { fout<<"syntax error";exit(0); }
    else {
        getSymbol();
    }

    if (symbolType != LBRACE) { fout<<"syntax error";exit(0); }
    getSymbol();

    //isCompound(); 复合语句

    if (symbolType != RBRACE) {fout<<"syntax error";exit(0); }
   
    fout << "<无返回值函数定义>" << endl;
    getSymbol();
}


// 参数表
void Grammar_analysis::passParaList(){
    
    string type;
    while (symbolType == INTTK || symbolType == CHARTK) {
        type = word;
        getSymbol();
        
        // 应是标识符
        if (symbolType != IDENFR) { fout<<"syntax error";exit(0); }
       
        getSymbol();
        // 后面没参数了
        if (symbolType != COMMA) {
            fout << "<参数表>" << endl;
            return;
        }
        getSymbol();
    }
    if (symbolType == RPARENT) {  // 参数为空
        fout << "<参数表>" << endl;
    }
    else{
        fout<<"syntax error";exit(0);
    }
}

void Grammar_analysis::passMain(){
   
     
     // 'main'
    if (symbolType != MAINTK) { fout<<"syntax error";exit(0); }
    getSymbol();


    //'('
    if (symbolType != LPARENT) { fout<<"syntax error";exit(0); }
    getSymbol();
    
    //')'
    if (symbolType != RPARENT) {fout<<"syntax error";exit(0); }
    else {
        getSymbol();
    }
    
    //'{'
    if (symbolType != LBRACE) { fout<<"syntax error";exit(0); }
    getSymbol();

    // 符合语句
    //passCompound();

    if (symbolType != RBRACE) { fout<<"syntax error";exit(0); }
    fout << "<主函数>" << endl;
}


// 复合语句
void Grammar_analysis::passCompound(){
    bool isval = false;

	string idenfr;
	// 常量说明
	if (symbolType == CONSTTK) {
		passConst();
	}
	// 变量定义
	while (symbolType == INTTK || symbolType == CHARTK) {
		isval = true; // 标记是变量 
		getSymbol();
		if (symbolType != IDENFR) { fout<<"syntax error";exit(0); }
		getSymbol();
        
        // 进入变量定义
		passVar();
	}
	if (isval) {  fout << "<变量说明>" << endl; }
	// 语句列
    passStatements();
	fout << "<复合语句>" << endl;

}

// 语句列
void Grammar_analysis::passStatements(){
    // 当符合进入语句的条件时，进入语句
    // 及当前字符在语句的select集中
    while (symbolType == IFTK || symbolType == WHILETK || symbolType == DOTK ||
		symbolType == FORTK || symbolType == LBRACE || symbolType == IDENFR ||
		symbolType == SCANFTK || symbolType == PRINTFTK ||
		symbolType == RETURNTK || symbolType == SEMICN) {
		passStatement();
	}
	fout << "<语句列>" << endl;
}


// 语句

void Grammar_analysis::passStatement(){
    
    // 条件语句
  	if (symbolType == IFTK) {
		passConditional();
		fout << "<语句>" << endl;
		return;
	}
    
    // 循环语句
	else if (symbolType == WHILETK || symbolType == DOTK || symbolType == FORTK) {
		passLoop();
		fout << "<语句>" << endl;
		return;
	}
	else if (symbolType == LBRACE) {  //为'{'时仍是语句列
		getSymbol();
		//语句列
		passStatements();
        // 应为'}'
		if (symbolType != RBRACE) { fout<<"syntax error";exit(0); }
		getSymbol();
		fout << "<语句>" << endl;
		return;
	}
	else if (symbolType == IDENFR) {
		getSymbol();
        // 统一分析有/无返回值函数调用语句
		if (symbolType == LPARENT) {
			passFun_call();
		}
		else if (symbolType == ASSIGN || symbolType == LBRACK) {
			// 赋值语句
			passAssign(idenfr);
		}
		else { fout << "<变量说明>" << endl;  }
	}
	else if (symbolType == SCANFTK) {// 读语句
		
		passScanf();
	}
	else if (symbolType == PRINTFTK) {// 写语句
		
		passPrintf();
	}
	else if (symbolType == RETURNTK) {// 返回语句
		
		passReturn();
	}
	if (symbolType != SEMICN) { fout<<"syntax error";exit(0); }
	else {
		getSymbol();
	}
	
	fout << "<语句>" << endl;
}


// 条件语句
void Grammar_analysis::passConditional() {
	string con;

    //应是'if'
	if (symbolType != IFTK) {  fout<<"syntax error";exit(0); }
	getSymbol();
     
    //应是'('
	if (symbolType != LPARENT) { fout<<"syntax error";exit(0); }
	getSymbol();
    
    // 条件
	passCondition();
    

    //应是')'
	if (symbolType != RPARENT) {fout<<"syntax error";exit(0); }
	else {
		getSymbol();
	}
    
    //语句
	passStatement();
    

	if (symbolType == ELSETK) {
		
		getSymbol();
		passStatement();
	}
	fout << "<条件语句>" << endl;
}


// 循环语句
void Grammar_analysis::passLoop(){

	// while语句
	if (symbolType == WHILETK) {
		
		getSymbol();

		if (symbolType != LPARENT) { fout<<"syntax error";exit(0); }
		getSymbol();

		// 条件
		passCondition();

		if (symbolType != RPARENT) { fout<<"syntax error";exit(0); }
		else {
			getSymbol();
		}

	    //  语句
		passStatement();
	
	}
	else if (symbolType == DOTK) {  // do语句
		getSymbol();
        
		// 语句
		passStatement();
        

		// 语句后应该是while
		if (symbolType != WHILETK) {
			fout<<"syntax error";exit(0);
		}
		else {
			getSymbol();
		}
        // '('
		if (symbolType != LPARENT) { fout<<"syntax error";exit(0); }
		getSymbol();

		passCondition();
        
		// ')'
		if (symbolType != RPARENT) { fout<<"syntax error";exit(0); }
		else {
			getSymbol();
		}
	}
	else if (symbolType == FORTK) {  // for语句
		getSymbol();
        
		// '('
		if (symbolType != LPARENT) {fout<<"syntax error";exit(0);}
		getSymbol();
       
	    // 标识符
		if (symbolType != IDENFR) { fout<<"syntax error";exit(0); }
		

		getSymbol();
        
		//''
		if (symbolType != ASSIGN) { fout<<"syntax error";exit(0); }
		getSymbol();
        
		// 表达式
		passExpression();
        
		// ';'
		if (symbolType != SEMICN) { fout<<"syntax error";exit(0); }
		else {
			getSymbol();
		}


		// 条件
		passCondition();

		
        // ';'
		if (symbolType != SEMICN) { fout<<"syntax error";exit(0); }
		else {
			getSymbol();
		}
        
		// 标识符
		if (symbolType != IDENFR) { fout<<"syntax error";exit(0); }
		getSymbol(); 


        // '='
		if (symbolType != ASSIGN) { fout<<"syntax error";exit(0); }
		getSymbol();

        // 标识符
		if (symbolType != IDENFR) { fout<<"syntax error";exit(0); }
		
		getSymbol();
        
		// (+|-)
		if (symbolType != PLUS && symbolType != MINU) { fout<<"syntax error";exit(0); }

		getSymbol();
        
		// 步长
		if (symbolType != INTCON) { fout<<"syntax error";exit(0); }
		
		fout << "<步长>" << endl;
		getSymbol();
        
		//')'
		if (symbolType != RPARENT) { fout<<"syntax error";exit(0);  }
		else {
			getSymbol();
		}
         
		// 语句
		passStatement();
	}
	else { fout<<"syntax error";exit(0); }
	fout << "<循环语句>" << endl;
}


// 条件
// 整形表达式之间才能进行关系运算！！！！！！！


void Grammar_analysis::passCondition(){
	int temptype; //表达式的类型  
	// 表达式
	passExpression(temptype);
	if(temptype!=){  // 不等于整形
    fout<<"syntax error";exit(0);
	}
    
	// 关系运算符
	if (symbolType >= LSS && symbolType <= NEQ) {
		
		passExpression(temptype);
		if(temptype!=){  // 不等于整形
        fout<<"syntax error";exit(0);
	}
	}
	fout << "<条件>" << endl;
}


// 读语句
void Grammar_analysis::passScanf(){
	
	if (symbolType != SCANFTK) {fout<<"syntax error";exit(0); }
	getSymbol();
    
	if (symbolType != LPARENT) { fout<<"syntax error";exit(0); }
	getSymbol();

	if (symbolType != IDENFR) {fout<<"syntax error";exit(0); }
	
	getSymbol();
    
	//','
	while (symbolType == COMMA) {
		getSymbol();
		if (symbolType != IDENFR) { fout<<"syntax error";exit(0); }
		
		getSymbol();
	}

	if (symbolType != RPARENT) { fout<<"syntax error";exit(0); }
	else {
		getSymbol();
	}
	fout << "<读语句>" << endl;

}
