#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

//#pragma once
//#pragma execution_character_set("utf-8")
using namespace std;

struct sym { int kind; int type; string value; int addr; };
struct midcode { string result; string left; int op; string right; set<string> out; };

enum classnum {
	IDENFR, INTCON, CHARCON, STRCON, CONSTTK, INTTK, CHARTK, VOIDTK, MAINTK, IFTK, ELSETK, DOTK, WHILETK, FORTK, SCANFTK, PRINTFTK,
	RETURNTK, PLUS, MINU, MULT, DIV, LSS, LEQ, GRE, GEQ, EQL, NEQ, ASSIGN, SEMICN, COMMA, LPARENT, RPARENT, LBRACK, RBRACK, LBRACE, RBRACE
};
enum midop {
	NEG, ADD, SUB, MUL, DIVI, ASS, GETARR, PUTARR, SETLABEL, GOTO, BNZ, BZ, LESS, LE, GREAT,
	GE, EQUAL, UNEQUAL, READ, WSTRING, WEXP, WSE, RET, RETX, PARA, FUNCALL, FUN, PAR, ASSRET
}; 

ifstream in;
ofstream newout;
ofstream out;
ofstream err;
ofstream mips;
ofstream mid;
ofstream optmid;
bool haveReturn;
bool haveReturnInt;
bool haveReturnChar;

int enter;
char c;
int line_num;
string level;
int tmpnum;
int labelnum;
int stringnum;
map<string, int> reserved;
int symnum;
string word;
string classCode[36];
map<string, int> fun_idenfr;
map<string, vector<string> > fun_para;
map<string, map<string, struct sym> > symList;
map<string, map<string, struct sym> > tmpList;
vector <struct midcode> midCodes;
map<string, vector<int> > fun_mids;


int getsym();
void outputsym();
void isConst();
void isVar(int type, string idenfr);
void isFun_return(int type, string idenfr);
void isParaList(string name);
void isCompound();
void isFun_void();
void isMain();
void symInsert(string name, struct sym sym);
void error(char errNum);
void addMidCode(string result, string left, int op, string right);
bool isAlpha(char ch);
string isIdenfr();
string isInteger();
string isString();
int isReserved(string s);
int getsym();
void outputsym();
void isProgram();
void init_code(string classCode[36]);
void init_reserved();
void error(char errNum);
void test_symList();
void outputMidcodes();
void outputMidcode(struct midcode m, ostream& file);
int getsym();
void outputsym();
void isConst();
int isTerm(string& var);
int isFactor(string& var);
string isFun_call(string idenfr);
void error(char errNum);
string getTmp();
void addMidCode(string result, string left, int op, string right);


int main() {
	map<string, struct sym> all;
	map<string, struct sym> all_tmp;
	line_num = 1;
	tmpnum = 0;
	labelnum = 1;
	level = "$all";
	symList[level] = all;
	tmpList[level] = all_tmp;
	init_code(classCode);
	// ??????????????????
	init_reserved();

	in.open("testfile.txt", ios_base::in);
	out.open("output.txt", ios_base::out | ios_base::trunc);

	err.open("error.txt", ios_base::out | ios_base::trunc);

	// ???????????????????????????
	c = in.get();
	word = "";
	// ????????????
	symnum = getsym();
	// ????????????
	isProgram();

	// ????????????????????????
	if (in.get() != EOF) { error('0'); }
	in.close();
	out.close();
	mid.close();
	err.close();

	return 0;
}

// ?????????????????????????????????
void init_code(string classCode[36]) {
	classCode[0] = "IDENFR";
	classCode[1] = "INTCON";
	classCode[2] = "CHARCON";
	classCode[3] = "STRCON";
	classCode[4] = "CONSTTK";
	classCode[5] = "INTTK";
	classCode[6] = "CHARTK";
	classCode[7] = "VOIDTK";
	classCode[8] = "MAINTK";
	classCode[9] = "IFTK";
	classCode[10] = "ELSETK";
	classCode[11] = "DOTK";
	classCode[12] = "WHILETK";
	classCode[13] = "FORTK";
	classCode[14] = "SCANFTK";
	classCode[15] = "PRINTFTK";
	classCode[16] = "RETURNTK";
	classCode[17] = "PLUS";
	classCode[18] = "MINU";
	classCode[19] = "MULT";
	classCode[20] = "DIV";
	classCode[21] = "LSS";
	classCode[22] = "LEQ";
	classCode[23] = "GRE";
	classCode[24] = "GEQ";
	classCode[25] = "EQL";
	classCode[26] = "NEQ";
	classCode[27] = "ASSIGN";
	classCode[28] = "SEMICN";
	classCode[29] = "COMMA";
	classCode[30] = "LPARENT";
	classCode[31] = "RPARENT";
	classCode[32] = "LBRACK";
	classCode[33] = "RBRACK";
	classCode[34] = "LBRACE";
	classCode[35] = "RBRACE";
}

void outputsym() {
	if (symnum >= 0 && symnum < 36)
	{
		// ?????????????????????????????????
		cout << classCode[symnum] << " " << word << endl;
		out << classCode[symnum] << " " << word << endl;
	}

	if (symnum == 1)
	{
		cout << "<???????????????>" << endl;
		out << "<???????????????>" << endl;
	}

}

string getTmp() {
	stringstream ss;  
	string s;
	struct sym dead = { 0,5 };
	ss << "t$" << tmpnum++;
	s = ss.str();
	map<string, struct sym> k = tmpList[level];
	k[s] = dead;
	//tmpList[level][s] = { 0, 5};
	return s;
}

string getLabel() {
	stringstream ss;
	string s;
	ss << "label$" << labelnum++;
	s = ss.str();
	return s;
}

// ??????????????????
void addMidCode(string result, string left, int op, string right) {
	struct midcode midcode = { result, left, op, right };
	vector<int> p;
	if (fun_mids.find(level) == fun_mids.end())
		fun_mids[level] = p;
	fun_mids[level].push_back(midCodes.size());
	midCodes.push_back(midcode);
}

void outputMidcodes() {
	for (auto m : midCodes)
		outputMidcode(m, mid);
}

void outputMidcode(struct midcode m, ostream& file) {
	string result = m.result;
	string left = m.left;
	int op = m.op;
	string right = m.right;
	enum midop {
		NEG, ADD, SUB, MUL, DIVI, ASS, GETARR, PUTARR, SETLABEL, GOTO, BNZ, BZ, LESS, LE, GREAT,
		GE, EQUAL, UNEQUAL, READ, WSTRING, WEXP, WSE, RET, RETX, PARA, FUNCALL, FUN, PAR, ASSRET
	};
	if (op == NEG) file << result << " = -" << left << endl;
	else if (op == ADD) file << result << " = " << left << " + " << right << endl;
	else if (op == SUB) file << result << " = " << left << " - " << right << endl;
	else if (op == MUL) file << result << " = " << left << " * " << right << endl;
	else if (op == DIVI) file << result << " = " << left << " / " << right << endl;
	else if (op == ASS) file << result << " = " << left << endl;
	else if (op == GETARR) file << result << " = " << left << "[" << right << "]" << endl;
	else if (op == PUTARR) file << result << "[" << left << "] = " << right << endl;
	else if (op == SETLABEL) file << result << ":" << endl;
	else if (op == GOTO) file << "GOTO " << result << endl;
	else if (op == BNZ) file << "BNZ " << result << endl;
	else if (op == BZ) file << "BZ " << result << endl;
	else if (op == LESS) file << left << " < " << right << endl;
	else if (op == LE) file << left << " <= " << right << endl;
	else if (op == GREAT) file << left << " > " << right << endl;
	else if (op == GE) file << left << " >= " << right << endl;
	else if (op == EQUAL) file << left << " == " << right << endl;
	else if (op == UNEQUAL) file << left << " != " << right << endl;
	else if (op == READ) file << "scanf " << left << endl;
	else if (op == WSTRING) file << "printf \"" << tmpList["$all"][left].value << "\"" << endl;
	else if (op == WEXP) file << "printf " << left << endl;
	else if (op == WSE) file << "printf \"" << tmpList["$all"][left].value << "\"" << right << endl;
	else if (op == RET) file << "ret" << endl;
	else if (op == RETX) file << "ret " << left << endl;
	else if (op == PARA) file << "push " << left << endl;
	else if (op == FUNCALL) file << "call " << left << endl;
	else if (op == FUN) file << left << " " << right << "()" << endl;
	else if (op == PAR) file << "para " << left << " " << right << endl;
	else if (op == ASSRET) file << result << " = RET" << endl;
	else  mid << "error!" << endl;
}

void test_symList() {
	// ?????????????????????
	cout << "symList:" << endl;
	for (auto& lev : symList) {
		cout << "level:" << lev.first << endl;
		for (auto& n : lev.second) {
			cout << "\tname:" << n.first << "\t kind:";
			if (n.second.kind == 0) cout << "var\ttype:";
			else if (n.second.kind == 1) cout << "const\ttype:";
			else if (n.second.kind == 2) cout << "fun\ttype:";
			else if (n.second.kind == 3) cout << "para\ttype:";
			else cout << "error\ttype:";
			if (n.second.type == 5) cout << "int";
			else if (n.second.type == 6) cout << "char";
			else if (n.second.type == 3) cout << "int[]";
			else if (n.second.type == 4) cout << "char[]";
			else if (n.second.type == 0) cout << "void";
			else cout << "error";
			cout << "\taddr:" << n.second.addr;
			if (n.second.kind == 1 || n.second.kind == 2) cout << "\tvalue:" << n.second.value;
			else if (n.second.type == 3 || n.second.type == 4) cout << "\tsize:" << n.second.value;
			cout << endl;
		}
	}
	cout << "tmpList:" << endl;
	for (auto& lev : tmpList) {
		cout << "level:" << lev.first << endl;
		if (lev.first == "$all") {
			for (auto& n : lev.second) {
				cout << "\tname:" << n.first << "\t value:";
				cout << n.second.value << endl;
			}
		}
		else {
			for (auto& n : lev.second) {
				cout << "\tname:" << n.first << "\t kind:";
				if (n.second.kind == 0) cout << "var\ttype:";
				else if (n.second.kind == 1) cout << "const\ttype:";
				else if (n.second.kind == 2) cout << "fun\ttype:";
				else if (n.second.kind == 3) cout << "para\ttype:";
				else cout << "error\ttype:";
				if (n.second.type == 5) cout << "int";
				else if (n.second.type == 6) cout << "char";
				else if (n.second.type == 3) cout << "int[]";
				else if (n.second.type == 4) cout << "char[]";
				else if (n.second.type == 0) cout << "void";
				else cout << "error";
				cout << "\taddr:" << n.second.addr << endl;
			}
		}
	}
}



int getsym() {
	word = "";
	enter = 0;
	while (isspace(c)) {
		if (c == '\n') {
			line_num++;
			enter++;
		}
		c = in.get();
	}
	// ????????????????????????????????????c????????????????????????
	// ???????????????????????????????????????????????????????????????????????????word
	if (isAlpha(c)) {
		word = isIdenfr();
		return isReserved(word);
	}
	// ???????????????????????????????????????word
	else if (isdigit(c)) {
		word = isInteger();
		return 1;
	}
	// ???????????????????????????????????????????????????word
	else if (c == '\'') {
		c = in.get();
		if (c == '+' || c == '-' || c == '*' || c == '/' || isdigit(c) || isAlpha(c)) {
			word = word + c;
		}
		else {
			error('a');
		}
		c = in.get();
		if (c != '\'') {
			error('a');
		}
		else {
			c = in.get();
		}
		return 2;
	}
	// ?????????????????????????????????????????????????????????word
	else if (c == '\"') {
		c = in.get();
		word = isString();
		if (c != '\"') {
			error('a');
		}
		else {
			c = in.get();
		}
		return 3;
	}
	else if (c == '+') {
		word = word + c;
		c = in.get();
		return 17;
	}
	else if (c == '-') {
		word = word + c;
		c = in.get();
		return 18;
	}
	else if (c == '*') {
		word = word + c;
		c = in.get();
		return 19;
	}
	else if (c == '/') {
		word = word + c;
		c = in.get();
		return 20;
	}
	else if (c == '<') {
		word = word + c;
		c = in.get();
		if (c != '=') {
			return 21;
		}
		else {
			word = word + c;
			c = in.get();
			return 22;
		}
	}
	else if (c == '>') {
		word = word + c;
		c = in.get();
		if (c != '=') {
			return 23;
		}
		else {
			word = word + c;
			c = in.get();
			return 24;
		}
	}
	else if (c == '=') {
		word = word + c;
		c = in.get();
		if (c != '=') {
			return 27;
		}
		else {
			word = word + c;
			c = in.get();
			return 25;
		}
	}
	else if (c == '!') {
		word = word + c;
		c = in.get();
		if (c != '=') {
			error('a');
			return 26;
		}
		else {
			word = word + c;
			c = in.get();
			return 26;
		}
	}
	else if (c == ';') {
		word = word + c;
		c = in.get();
		return 28;
	}
	else if (c == ',') {
		word = word + c;
		c = in.get();
		return 29;
	}
	else if (c == '(') {
		word = word + c;
		c = in.get();
		return 30;
	}
	else if (c == ')') {
		word = word + c;
		c = in.get();
		return 31;
	}
	else if (c == '[') {
		word = word + c;
		c = in.get();
		return 32;
	}
	else if (c == ']') {
		word = word + c;
		c = in.get();
		return 33;
	}
	else if (c == '{') {
		word = word + c;
		c = in.get();
		return 34;
	}
	else if (c == '}') {
		word = word + c;
		c = in.get();
		return 35;
	}
	else {
		error('a');
		return -1;
	}
}


void error(char errNum) {
	if (errNum == 'k') err << line_num - enter;
	else err << line_num;
	err << " " << errNum << endl;
	return;
}


// ?????????
// ???????????????
int isExpression(string& var) {
	int type = -1;
	int opcode = -1;
	string tmp1, tmp2, tmp3;
	//[+|-]// ??????????????????????????????
	if (symnum == PLUS || symnum == MINU) {
		if (symnum == MINU) opcode = NEG;  // NEG??????-
		outputsym(); // ??????
		symnum = getsym();  // ????????????
	}
    //????????? <???>
	type = isTerm(tmp1);
    // ????????? -<???>
	if (opcode == 0) {
		tmp3 = getTmp();   // ?????????????????????
		addMidCode(tmp3, tmp1, opcode, "");
		tmp1 = tmp3;
	}

	// ?????????????????? 
	while (symnum == PLUS || symnum == MINU) {
		if (symnum == PLUS) opcode = ADD;
		else if (symnum == MINU) opcode = SUB;
		outputsym();
		symnum = getsym();
		isTerm(tmp2);
		tmp3 = getTmp();
		addMidCode(tmp3, tmp1, opcode, tmp2);
		tmp1 = tmp3;
		type = 5;
	}
	var = tmp1;
	out << "<?????????>" << endl;
	cout << "<?????????>" << endl;
	return type;
}

// ???
int isTerm(string& var) {
	string tmp1, tmp2, tmp3;
	int type = isFactor(tmp1);
	int opcode = -1;
	while (symnum == MULT || symnum == DIV) {
		if (symnum == MULT) opcode = MUL;
		else if (symnum == DIV) opcode = DIVI;
		outputsym();
		symnum = getsym();
		isFactor(tmp2);
		tmp3 = getTmp();
		addMidCode(tmp3, tmp1, opcode, tmp2);
		tmp1 = tmp3;
		type = 5;
	}
	var = tmp1;
	out << "<???>" << endl;
	cout << "<???>" << endl;
	return type;
}

// ??????
int isFactor(string& var) {
	extern map<string, int> fun_idenfr;
	string idenfr;   // ?????????
	int type = -1;
	int opcode = -1;
	string tmp;
	// ????????????????????????
	if (symnum == LPARENT) { //????????????
		// ???????????????
		outputsym();  //??????????????????????????????
		symnum = getsym();
		type = isExpression(var);  //???????????????
		if (symnum != RPARENT) { error('0'); }  // ????????????????????????????????????
		outputsym();
		symnum = getsym();
	}
	else if (symnum == PLUS || symnum == MINU) {
		// ???+-????????????
		type = 5;
		if (symnum == MINU) opcode = NEG; // ??????
		outputsym();
		symnum = getsym();
		if (symnum != INTCON) { error('0'); }// ????????????????????????????????????????????????
		outputsym();
		if (opcode == NEG) var = "-" + word;
		else var = word;
		out << "<??????>" << endl;
		cout << "<??????>" << endl;
		symnum = getsym();
	}
	else if (symnum == INTCON) { //?????????????????????
		// ???????????????
		type = 5;
		outputsym();
		var = word;
		out << "<??????>" << endl;
		cout << "<??????>" << endl;
		symnum = getsym();
	}
	else if (symnum == CHARCON) {
		// ??????
		type = 6;
		outputsym();
		var = (int)(word[0]) + '0';//to_string((int)(word[0]));
		symnum = getsym();
	}
	else if (symnum == IDENFR) {  //?????????
		if (symList[level].find(word) == symList[level].end()) {
			if (symList["$all"].find(word) == symList["$all"].end()) {
				error('c'); type = 5;
			}
			else { type = symList["$all"][word].type; }
		}
		else { type = symList[level][word].type; }
		idenfr = word;
		outputsym();
		symnum = getsym();
		if (symnum == LPARENT) {
			// ??????????????????????????????
			if (fun_idenfr.find(idenfr) == fun_idenfr.end() || fun_idenfr[idenfr] == 0) { error('0'); }
			var = isFun_call(idenfr);
			if (symList["$all"][idenfr].value == "f") {
				var = getTmp();
				addMidCode(var, "", ASSRET, "");
			}
		}
		else if (symnum == LBRACK) {
			// ?????? ?????????[?????????]
			symList["$all"][level].value = "f";
			outputsym();
			symnum = getsym();
			if (isExpression(tmp) != 5) { error('i'); }
			if (symnum != RBRACK) { error('0'); }
			var = getTmp();
			addMidCode(var, idenfr, GETARR, tmp);
			type = type + 2;
			outputsym();
			symnum = getsym();
		}
		else {
			// ?????????????????????
			if (symList[level].find(idenfr) != symList[level].end()) {
				if (symList[level][idenfr].kind == 1)
					var = symList[level][idenfr].value;
				else
					var = idenfr;
			}
			else if (symList["$all"].find(idenfr) != symList["$all"].end() && symList["$all"][idenfr].kind == 1)
				var = symList["$all"][idenfr].value;
			else {
				if (symList["$all"].find(idenfr) != symList["$all"].end() && symList["$all"][idenfr].kind == 0)
					symList["$all"][level].value = "f";
				var = idenfr;
			}
		}
	}
	else { error('0'); }
	out << "<??????>" << endl;
	cout << "<??????>" << endl;
	return type;
}


// ????????????   :: = ??????a???????????????z???A???????????????Z
bool isAlpha(char ch) {
	if (isalpha(ch) || ch == '_')
		return true;
	else
		return false;
}

// ???????????????::=?????????????????????????????????????????????
string isIdenfr() {
	string s = "";
	s = s + c;
	c = in.get();
	while (isAlpha(c) || isdigit(c)) {
		s = s + c;
		c = in.get();
	}
	return s;
}

// ????????????   :: = ????????????????????????
// ??????????????????  :: = ?????????????????????
// ?????????????????????::=?????????????????????????????????| 0
string isInteger() {
	//int n = c - '0';
	string s = "";
	s = s + c;
	c = in.get();
	if (s == "0")
		return s;
	while (isdigit(c)) {
		//n = n * 10 + (c - '0');
		s = s + c;
		c = in.get();
	}
	return s;
}

// ???????????????::="?????????????????????32,33,35-126???ASCII?????????"
string isString() {
	string s = "";
	while ((int)c == 32 || (int)c == 33 || ((int)c >= 35 && (int)c <= 126)) {
		if (c == '\\') 
		{
			s = s + "\\";
		}
		else
			s = s + c;
		cout<<"aa:"+s<<endl;
		c = in.get();
	}
	return s;
}

// ?????????map?????????
void init_reserved() {
	reserved["const"] = 4;
	reserved["int"] = 5;
	reserved["char"] = 6;
	reserved["void"] = 7;
	reserved["main"] = 8;
	reserved["if"] = 9;
	reserved["else"] = 10;
	reserved["do"] = 11;
	reserved["while"] = 12;
	reserved["for"] = 13;
	reserved["scanf"] = 14;
	reserved["printf"] = 15;
	reserved["return"] = 16;
}

// ????????????????????????
int isReserved(string s) {
	if (reserved.find(s) == reserved.end())
		return 0;
	else
		return reserved[s];
}




// ?????????????????????while??????????????????????????????
void isProgram() {
    int type;
    string idenfr;
    bool isval = false;
    // ??????????????????
    if (symnum == CONSTTK) {
        isConst();
    }
    // ??????????????????????????????????????????????????????
    if (symnum == INTTK || symnum == CHARTK) {
        type = symnum;  // ??????????????????symnum
        symnum = getsym();
        if (symnum == IDENFR) {
            idenfr = word;
            symnum = getsym();
            // ????????????????????????
            while (symnum == COMMA || symnum == SEMICN || symnum == LBRACK) {
                isval = true;
                isVar(type, idenfr);
                if (symnum == INTTK || symnum == CHARTK) {
                    type = symnum;
                    symnum = getsym();
                    if (symnum == IDENFR) {
                        idenfr = word;
                        symnum = getsym();
                    }
                    else { error('0'); }
                }
                else {
                    // ??????void??????????????????????????????????????????
                    if (isval) {
                        out << "<????????????>" << endl; cout << "<????????????>" << endl;
                    }
                    break;
                }
            }
            // ?????????????????????while????????????????????????????????????????????????
            if (symnum == LPARENT) {
                if (isval) { out << "<????????????>" << endl; cout << "<????????????>" << endl; }
                isFun_return(type, idenfr);
            }
        }
        else { error('0'); }
    }
    // ???????????????????????????????????????????????????
    while (symnum == VOIDTK || symnum == INTTK || symnum == CHARTK) {
        if (symnum == VOIDTK) {
            outputsym();
            symnum = getsym();
            // ??????????????????????????????
            if (symnum == MAINTK) {
                isMain();
                {out << "<??????>" << endl; cout << "<??????>" << endl; }
                return;
                // ?????????????????????????????????????????????
            }
            else if (symnum == IDENFR) {
                isFun_void();
            }
            else { error('0'); }
            // ?????????????????????????????????
        }
        else {
            type = symnum;
            symnum = getsym();
            if (symnum == IDENFR) {
                idenfr = word;
                symnum = getsym();
                isFun_return(type, idenfr);
            }
            else { error('0'); }
        }
    }
    // ????????????????????????
    error('0');
    return;
}

// ????????????
void isConst() {
    int type;
    string name;
    struct sym sym = { 1, 5, "" };
    if (symnum != CONSTTK) { error('0'); }
    outputsym();

    symnum = getsym();
    if (symnum != INTTK && symnum != CHARTK) { error('0'); }
    type = symnum;
    sym.type = symnum;
    outputsym();

    symnum = getsym();
    if (symnum != IDENFR) { error('0'); }
    while (symnum == IDENFR) {
        sym.value = "";
        name = word;
        outputsym();

        symnum = getsym();
        if (symnum != ASSIGN) { error('0'); }
        outputsym();

        symnum = getsym();
        if (symnum == PLUS || symnum == MINU) {
            if (symnum == MINU) sym.value = word;
            outputsym();
            symnum = getsym();
        }
        if (!(symnum == INTCON && type == INTTK) &&
            !(symnum == CHARCON && type == CHARTK)) {
            error('o');
        }
        if (symnum == INTCON) sym.value = sym.value + word;
        else sym.value = (int)(word[0]) + '0';//sym.value = to_string((int)(word[0]));
        outputsym();
        if (symnum == INTCON)
        {
            out << "<??????>" << endl;
            cout << "<??????>" << endl;
        }


        symInsert(name, sym);
        symnum = getsym();
        if (symnum == COMMA) {
            // ?????????????????????????????????
            outputsym();
            symnum = getsym();
        }
        else if (symnum == SEMICN) {
            break;
        }
        else { error('k');  break; }
    }
    // ????????????????????????????????????
    out << "<????????????>" << endl;
    cout << "<????????????>" << endl;
    outputsym();
    symnum = getsym();
    if (symnum == CONSTTK) {
        isConst();
    }
    else {
        // ?????????????????????????????????????????????????????????.
        out << "<????????????>" << endl;
        cout << "<????????????>" << endl;
        return;
    }
}

// ????????????
void isVar(int type, string idenfr) {
    string name = idenfr;
    struct sym sym = { 0, type };
	// int?????????
    if (type == INTTK) {
        out << "INTTK int" << endl;
        cout << "INTTK int" << endl;
    }
	// char?????????
    else if (type == CHARTK) { out << "CHARTK char" << endl; cout << "CHARTK char" << endl; }

	// ???????????????
    out << "IDENFR" << " " << idenfr << endl;
    cout << "IDENFR" << " " << idenfr << endl;
    while (symnum == SEMICN || symnum == COMMA || symnum == LBRACK) {
		// ??????????????????????????????
        if (symnum == SEMICN) {
            // ????????????????????????
            symInsert(name, sym);
            out << "<????????????>" << endl;
            cout << "<????????????>" << endl;
			// ????????????
            outputsym();
            symnum = getsym();
            return;
        }
		// ?????????????????????????????????????????????????????????????????????????????????????????????
        else if (symnum == COMMA) {
			// ???????????????
            symInsert(name, sym);
			// ??????????????????
            sym.type = type;
            outputsym();
            symnum = getsym();
            if (symnum == IDENFR) {
                name = word;
                outputsym();
                symnum = getsym();
                // ???????????????????????????
            }
            else { error('0'); }
        }
		// ?????????????????????????????????
        else if (symnum == LBRACK) {
            if (level != "$all") symList["$all"][level].value = "f";
            sym.type = type - 2;
            outputsym();
            symnum = getsym();
            if (symnum != INTCON || word == "0") { error('i'); }
            sym.value = word;
            outputsym();
            symnum = getsym();
            if (symnum == RBRACK) {
                outputsym();
                symnum = getsym();
                // ???????????????????????????
            }
            else { error('m'); }
        }
    }
    error('k');
}

// ????????????????????????
void isFun_return(int type, string idenfr) {
    extern bool haveReturn;
    extern bool haveReturnInt;
    extern bool haveReturnChar;
    map<string, struct sym> map1;
    map<string, struct sym> map_tmp;
    if (type == INTTK) {
        out << "INTTK int" << endl;
        cout << "INTTK int" << endl;
		// ??????????????????
        addMidCode("", "int", FUN, idenfr);
    }
    else if (type == CHARTK) {
        out << "CHARTK char" << endl;
        cout << "CHARTK char" << endl;
        addMidCode("", "char", FUN, idenfr);
    }
    out << "IDENFR" << " " << idenfr << endl;
    out << "<????????????>" << endl;
    cout << "IDENFR" << " " << idenfr << endl;
    cout << "<????????????>" << endl;
    fun_idenfr[idenfr] = 1;
    sym dad = { 2, type, "t" };
    symInsert(idenfr, dad);

    level = idenfr;
    symList[level] = map1;
    tmpList[level] = map_tmp;

    if (symnum != LPARENT) { error('0'); }
    outputsym();
    symnum = getsym();

	// ???????????????,??????????????????????????????????????????????????????'{'
    isParaList(idenfr);

    if (symnum != RPARENT) { error('l'); }
    else {
        outputsym();
        symnum = getsym();
    }

    if (symnum != LBRACE) { error('0'); }
    outputsym();
    symnum = getsym();

    haveReturn = false;
    haveReturnInt = false;
    haveReturnChar = false;
	// ??????????????????
    isCompound();

    if (symnum != RBRACE) { error('0'); }
    outputsym();
    out << "<????????????????????????>" << endl;
    cout << "<????????????????????????>" << endl;
    symnum = getsym();
    level = "$all";
}

// ?????????
void isParaList(string name) {
    vector<string> para;
    struct sym sym = { 3, 0 };
    string type;
    while (symnum == INTTK || symnum == CHARTK) {
        type = word;
        sym.type = symnum;
        outputsym();

        symnum = getsym();
        if (symnum != IDENFR) { error('0'); }
        symInsert(word, sym);
        para.push_back(word);
        addMidCode("", type, PAR, word);
        outputsym();

        symnum = getsym();
        if (symnum != COMMA) {
            fun_para[name] = para;
            out << "<?????????>" << endl;
            cout << "<?????????>" << endl;
            return;
        }
        outputsym();

        symnum = getsym();
    }
    if (symnum == RPARENT) {
        fun_para[name] = para;
        out << "<?????????>" << endl;
        cout << "<?????????>" << endl;
    }
    else
        error('0');
}

// ????????????????????????
void isFun_void() {
    extern bool haveReturn;
    extern bool haveReturnInt;
    extern bool haveReturnChar;
    string name = word;
    map<string, struct sym> map1;
    map<string, struct sym> map_tmp;
    if (symnum != IDENFR) { error('0'); }
    outputsym();
    fun_idenfr[word] = 0;
    sym dadad = { 2, 0, "t" };
    symInsert(word, dadad);
    addMidCode("", "void", FUN, word);
    level = word;
    symList[level] = map1;
    tmpList[level] = map_tmp;
    symnum = getsym();

    if (symnum != LPARENT) { error('0'); }
    outputsym();
    symnum = getsym();

    isParaList(name);

    if (symnum != RPARENT) { error('l'); }
    else {
        outputsym();
        symnum = getsym();
    }

    if (symnum != LBRACE) { error('0'); }
    outputsym();
    symnum = getsym();

    haveReturn = false;
    haveReturnInt = false;
    haveReturnChar = false;
    isCompound();

    addMidCode("", "", RET, "");
    if (symnum != RBRACE) { error('0'); }
    outputsym();
    out << "<????????????????????????>" << endl;
    cout << "<????????????????????????>" << endl;
    symnum = getsym();
    level = "$all";
}

// ?????????
void isMain() {
    extern bool haveReturn;
    extern bool haveReturnInt;
    extern bool haveReturnChar;
    map<string, struct sym> map1;
    map<string, struct sym> map_tmp;
    sym dad = { 2, 0, "t" };
    symInsert("main", dad);
    addMidCode("", "void", FUN, "main");
    level = "main";
    symList[level] = map1;
    tmpList[level] = map_tmp;
    if (symnum != MAINTK) { error('0'); }
    outputsym();
    symnum = getsym();

    if (symnum != LPARENT) { error('0'); }
    outputsym();
    symnum = getsym();

    if (symnum != RPARENT) { error('l'); }
    else {
        outputsym();
        symnum = getsym();
    }

    if (symnum != LBRACE) { error('0'); }
    outputsym();
    symnum = getsym();

    haveReturn = false;
    haveReturnInt = false;
    haveReturnChar = false;
    isCompound();

    if (symnum != RBRACE) { error('0'); }
    outputsym();
    out << "<?????????>" << endl;
    cout << "<?????????>" << endl;
    level = "$all";
}

// ????????????
void symInsert(string name, struct sym sym) {
    if (symList[level].find(name) == symList[level].end()) {
        symList[level][name] = sym;
    }
    else { error('b'); }
}


int getsym();
void outputsym();
bool isNumber(string s);

void isConst();
void isVar(int type, string idenfr);
void isStatements();
void isStatement();
void isConditional();
void isLoop();
void isCondition(string& con);
void isScanf();
void isPrintf();
void isReturn();
string isFun_call(string idenfr);
map<string, string> isValueList(string name);
void isAssign(string idenfr);
int isExpression(string& var);
void error(char errNum);
string getTmp();
string getLabel();
string getString(string s);
void addMidCode(string result, string left, int op, string right);
void outputMidcode(struct midcode m, ostream& file);

// ????????????
void isCompound() {
	bool isval = false;
	int type;
	string idenfr;
	// ????????????
	if (symnum == CONSTTK) {
		isConst();
	}
	// ????????????
	while (symnum == INTTK || symnum == CHARTK) {
		isval = true;
		type = symnum;
		symnum = getsym();

		if (symnum != IDENFR) { error('0'); }
		idenfr = word;
		symnum = getsym();

		isVar(type, idenfr);
	}
	if (isval) { cout << "<????????????>" << endl; out << "<????????????>" << endl; }
	// ?????????
	isStatements();
	cout << "<????????????>" << endl;
	out << "<????????????>" << endl;
}

// ?????????
void isStatements() {
	while (symnum == IFTK || symnum == WHILETK || symnum == DOTK ||
		symnum == FORTK || symnum == LBRACE || symnum == IDENFR ||
		symnum == SCANFTK || symnum == PRINTFTK ||
		symnum == RETURNTK || symnum == SEMICN) {
		isStatement();
	}
	cout << "<?????????>" << endl;
	out << "<?????????>" << endl;
}

// ??????
void isStatement() {
	string idenfr;
	if (symnum == IFTK) {
		// ????????????
		isConditional();
		cout << "<??????>" << endl;
		out << "<??????>" << endl;
		return;
	}
	else if (symnum == WHILETK || symnum == DOTK || symnum == FORTK) {
		// ????????????
		isLoop();
		cout << "<??????>" << endl;
		out << "<??????>" << endl;
		return;
	}
	else if (symnum == LBRACE) {
		outputsym();
		//?????????
		symnum = getsym();
		isStatements();
		if (symnum != RBRACE) { error('0'); }
		outputsym();
		symnum = getsym();
		cout << "<??????>" << endl;
		out << "<??????>" << endl;
		return;
	}
	else if (symnum == IDENFR) {
		idenfr = word;
		outputsym();
		symnum = getsym();
		if (symnum == LPARENT) {
			// ???/??????????????????????????????
			if (symList[level].find(idenfr) == symList[level].end()
				&& symList["$all"].find(idenfr) == symList["$all"].end()) {
				error('c');
			}
			isFun_call(idenfr);
		}
		else if (symnum == ASSIGN || symnum == LBRACK) {
			// ????????????
			if (symList[level].find(idenfr) == symList[level].end()) {
				if (symList["$all"].find(idenfr) == symList["$all"].end()) { error('c'); }
				else if (symList["$all"][idenfr].kind == 1) { error('j'); }
			}
			else if (symList[level][idenfr].kind == 1) { error('j'); }
			isAssign(idenfr);
		}
		else { error('0'); }
	}
	else if (symnum == SCANFTK) {
		// ?????????
		isScanf();
	}
	else if (symnum == PRINTFTK) {
		// ?????????
		isPrintf();
	}
	else if (symnum == RETURNTK) {
		// ????????????
		isReturn();
	}
	if (symnum != SEMICN) { error('k'); }
	else {
		outputsym();
		symnum = getsym();
	}
	cout << "<??????>" << endl;
	out << "<??????>" << endl;
}

// ????????????
void isConditional() {
	string con;
	string label1 = getLabel(), label2;
	symList["$all"][level].value = "f";
	if (symnum != IFTK) { error('0'); }
	outputsym();
	symnum = getsym();

	if (symnum != LPARENT) { error('0'); }
	outputsym();
	symnum = getsym();

	isCondition(con);
	addMidCode(label1, con, BZ, "");

	if (symnum != RPARENT) { error('l'); }
	else {
		outputsym();
		symnum = getsym();
	}

	isStatement();

	if (symnum == ELSETK) {
		label2 = getLabel();
		addMidCode(label2, "", GOTO, "");
		addMidCode(label1, "", SETLABEL, "");
		outputsym();
		symnum = getsym();
		isStatement();
		addMidCode(label2, "", SETLABEL, "");
	}
	else {
		addMidCode(label1, "", SETLABEL, "");
	}
	cout << "<????????????>" << endl;
	out << "<????????????>" << endl;
}

// ????????????
void isLoop() {
	int opcode=-1, i, j;
	string idenfr, idenfr2, step, con;
	string label1 = getLabel(), label2;
	vector<int> midTmpIndex;
	vector<struct midcode> midTmp;
	extern vector <struct midcode> midCodes;

	symList["$all"][level].value = "f";
	if (symnum == WHILETK) {
		label2 = getLabel();
		midTmpIndex.push_back(midCodes.size());
		addMidCode(label1, "", SETLABEL, "");
		outputsym();
		symnum = getsym();

		if (symnum != LPARENT) { error('0'); }
		outputsym();
		symnum = getsym();

		midTmpIndex.push_back(midCodes.size());
		isCondition(con);

		midTmpIndex.push_back(midCodes.size());
		addMidCode(label2, con, BZ, "");

		if (symnum != RPARENT) { error('l'); }
		else {
			outputsym();
			symnum = getsym();
		}

		midTmpIndex.push_back(midCodes.size());
		isStatement();

		midTmpIndex.push_back(midCodes.size());
		addMidCode(label1, "", GOTO, "");
		midTmpIndex.push_back(midCodes.size());
		addMidCode(label2, "", SETLABEL, "");
		midTmpIndex.push_back(midCodes.size());
		// ????????????????????????
		for (i = midTmpIndex[4]; i < midTmpIndex[6]; i++)
			midTmp.push_back(midCodes[i]);
		for (i = midTmpIndex[3]; i < midTmpIndex[4]; i++)
			midTmp.push_back(midCodes[i]);
		for (i = midTmpIndex[0]; i < midTmpIndex[2]; i++)
			midTmp.push_back(midCodes[i]);
		struct midcode m = midCodes[midTmpIndex[2]];
		m.op = BNZ;
		midTmp.push_back(m);
		for (i = midTmpIndex[0], j = 0; i < midTmpIndex[6]; i++, j++)
			midCodes[i] = midTmp[j];
	}
	else if (symnum == DOTK) {
		addMidCode(label1, "", SETLABEL, "");
		outputsym();
		symnum = getsym();

		isStatement();

		if (symnum != WHILETK) {
			error('n');
		}
		else {
			outputsym();
			symnum = getsym();
		}

		if (symnum != LPARENT) { error('0'); }
		outputsym();
		symnum = getsym();

		isCondition(con);
		addMidCode(label1, con, BNZ, "");

		if (symnum != RPARENT) { error('l'); }
		else {
			outputsym();
			symnum = getsym();
		}
	}
	else if (symnum == FORTK) {
		label2 = getLabel();
		outputsym();
		symnum = getsym();

		if (symnum != LPARENT) { error('0'); }
		outputsym();
		symnum = getsym();

		if (symnum != IDENFR) { error('0'); }
		if (symList[level].find(word) == symList[level].end()) {
			if (symList["$all"].find(word) == symList["$all"].end()) { error('c'); }
			else if (symList["$all"][word].kind == 1) { error('j'); }
		}
		else if (symList[level][word].kind == 1) { error('j'); }
		idenfr = word;
		outputsym();
		symnum = getsym();

		if (symnum != ASSIGN) { error('0'); }
		outputsym();
		symnum = getsym();

		isExpression(idenfr2);
		midTmpIndex.push_back(midCodes.size());
		addMidCode(idenfr, idenfr2, ASS, "");

		if (symnum != SEMICN) { error('k'); }
		else {
			outputsym();
			symnum = getsym();
		}

		midTmpIndex.push_back(midCodes.size());
		addMidCode(label1, "", SETLABEL, "");

		midTmpIndex.push_back(midCodes.size());
		isCondition(con);

		midTmpIndex.push_back(midCodes.size());
		addMidCode(label2, con, BZ, "");

		if (symnum != SEMICN) { error('k'); }
		else {
			outputsym();
			symnum = getsym();
		}

		if (symnum != IDENFR) { error('0'); }
		if (symList[level].find(word) == symList[level].end()) {
			if (symList["$all"].find(word) == symList["$all"].end()) { error('c'); }
			else if (symList["$all"][word].kind == 1) { error('j'); }
		}
		else if (symList[level][word].kind == 1) { error('j'); }
		idenfr = word;
		outputsym();
		symnum = getsym();

		if (symnum != ASSIGN) { error('0'); }
		outputsym();
		symnum = getsym();

		if (symnum != IDENFR) { error('0'); }
		if (symList[level].find(word) == symList[level].end()
			&& symList["$all"].find(word) == symList["$all"].end()) {
			error('c');
		}
		idenfr2 = word;
		outputsym();
		symnum = getsym();

		if (symnum != PLUS && symnum != MINU) { error('0'); }
		if (symnum == PLUS) opcode = ADD;
		else if (symnum == MINU) opcode = SUB;
		outputsym();
		symnum = getsym();

		if (symnum != INTCON) { error('0'); }
		step = word;
		outputsym();
		cout << "<??????>" << endl;
		out << "<??????>" << endl;
		symnum = getsym();

		if (symnum != RPARENT) { error('l'); }
		else {
			outputsym();
			symnum = getsym();
		}

		midTmpIndex.push_back(midCodes.size());
		isStatement();

		midTmpIndex.push_back(midCodes.size());
		addMidCode(idenfr, idenfr2, opcode, step);
		midTmpIndex.push_back(midCodes.size());
		addMidCode(label1, "", 9, "");
		midTmpIndex.push_back(midCodes.size());
		addMidCode(label2, "", 8, "");
		midTmpIndex.push_back(midCodes.size());
		// ????????????????????????
		for (i = midTmpIndex[0]; i < midTmpIndex[1]; i++)
			midTmp.push_back(midCodes[i]);
		for (i = midTmpIndex[6]; i < midTmpIndex[8]; i++)
			midTmp.push_back(midCodes[i]);
		for (i = midTmpIndex[4]; i < midTmpIndex[6]; i++)
			midTmp.push_back(midCodes[i]);
		for (i = midTmpIndex[1]; i < midTmpIndex[3]; i++)
			midTmp.push_back(midCodes[i]);
		struct midcode m = midCodes[midTmpIndex[3]];
		m.op = BNZ;
		midTmp.push_back(m);
		/*
		for (i = midTmpIndex[0], j = 0; i < midTmpIndex[8]; i++, j++) {
			outputMidcode(midCodes[i], cout);
		}
		cout << "-------------------------" << endl;
		for (i = midTmpIndex[0], j = 0; i < midTmpIndex[8]; i++, j++) {
			outputMidcode(midTmp[j], cout);
		}
		cout << "########################" << endl;*/
		for (i = midTmpIndex[0], j = 0; i < midTmpIndex[8]; i++, j++)
			midCodes[i] = midTmp[j];
	}
	else { error('0'); }
	cout << "<????????????>" << endl;
	out << "<????????????>" << endl;
}

// ??????
void isCondition(string& con) {
	string tmp1, tmp2;
	int type = isExpression(tmp1);
	int opcode;
	if (type != 5) { error('f'); }
	if (symnum >= LSS && symnum <= NEQ) {
		opcode = symnum - LSS + LESS;
		outputsym();
		symnum = getsym();
		type = isExpression(tmp2);
		con = getTmp();
		addMidCode(con, tmp1, opcode, tmp2);
		if (type != 5) { error('f'); }
	}
	else {
		con = tmp1;
	}
	cout << "<??????>" << endl;
	out << "<??????>" << endl;
}

// ?????????
void isScanf() {
	// symList["$all"][level].value = "f";
	if (symnum != SCANFTK) { error('0'); }
	outputsym();
	symnum = getsym();

	if (symnum != LPARENT) { error('0'); }
	outputsym();
	symnum = getsym();

	if (symnum != IDENFR) { error('0'); }
	if (symList[level].find(word) == symList[level].end()) {
		if (symList["$all"].find(word) == symList["$all"].end()) { error('c'); }
		else if (symList["$all"][word].kind == 1) { error('j'); }
	}
	else if (symList[level][word].kind == 1) { error('j'); }
	addMidCode("", word, READ, "");
	outputsym();
	symnum = getsym();

	while (symnum == COMMA) {
		outputsym();
		symnum = getsym();
		if (symnum != IDENFR) { error('0'); }
		if (symList[level].find(word) == symList[level].end()) {
			if (symList["$all"].find(word) == symList["$all"].end()) { error('c'); }
			else if (symList["$all"][word].kind == 1) { error('j'); }
		}
		else if (symList[level][word].kind == 1) { error('j'); }
		addMidCode("", word, READ, "");
		outputsym();
		symnum = getsym();
	}

	if (symnum != RPARENT) { error('l'); }
	else {
		outputsym();
		symnum = getsym();
	}
	cout << "<?????????>" << endl;
	out << "<?????????>" << endl;
}

// ?????????
void isPrintf() {
	string str, tmp, type;
	// symList["$all"][level].value = "f";
	if (symnum != PRINTFTK) { error('0'); }
	outputsym();
	symnum = getsym();

	if (symnum != LPARENT) { error('0'); }
	outputsym();
	symnum = getsym();

	if (symnum == STRCON) {
		str = getString(word);
		outputsym();
		cout << "<?????????>" << endl;
		out << "<?????????>" << endl;
		symnum = getsym();

		if (symnum == COMMA) {
			outputsym();
			symnum = getsym();
			if (isExpression(tmp) == 5) type = "int";
			else type = "char";
			addMidCode(type, str, WSE, tmp);
		}
		else {
			addMidCode("", str, WSTRING, "");
		}
	}
	else {
		if (isExpression(tmp) == 5) type = "int";
		else type = "char";
		addMidCode("", tmp, WEXP, type);
	}

	if (symnum != RPARENT) { error('l'); }
	else {
		outputsym();
		symnum = getsym();
	}
	cout << "<?????????>" << endl;
	out << "<?????????>" << endl;
}

// ????????????
void isReturn() {
	int type;
	string tmp;
	if (symnum != RETURNTK) { error('0'); }
	outputsym();
	symnum = getsym();

	if (symnum == LPARENT) {
		outputsym();
		symnum = getsym();
		type = isExpression(tmp);
		if (type == 5 && !haveReturnInt) {
			haveReturnInt = true;
			if (symList["$all"][level].type == 0) { error('g'); }
			else if (symList["$all"][level].type == 6) { error('h'); }
		}
		else if (type == 6 && !haveReturnChar) {
			haveReturnChar = true;
			if (symList["$all"][level].type == 0) { error('g'); }
			else if (symList["$all"][level].type == 5) { error('h'); }
		}
		if (symnum != RPARENT) { error('l'); }
		else {
			outputsym();
			symnum = getsym();
		}
		addMidCode("", tmp, RETX, "");
	}
	else {
		if (!haveReturn) {
			haveReturn = true;
			if (symList["$all"][level].type != 0) { error('h'); }
		}
		if (level != "main") addMidCode("", "", RET, "");
	}
	cout << "<????????????>" << endl;
	out << "<????????????>" << endl;
}

// ???/??????????????????????????????
string isFun_call(string idenfr) {
	string ret = "";
	extern map<string, int> fun_idenfr;
	extern vector <struct midcode> midCodes;
	extern map<string, vector<int> > fun_mids;
	if (symList["$all"][idenfr].value == "f") symList["$all"][level].value = "f";

	if (symnum != LPARENT) { error('0'); }
	outputsym();
	symnum = getsym();

	map<string, string> funVar = isValueList(idenfr);
	if (symList["$all"][idenfr].value == "f") addMidCode("", idenfr, FUNCALL, "");
	// ????????????
	else {
		for (auto i : fun_mids[idenfr]) {
			struct midcode m = midCodes[i];
			// ??????result??????????????????tmp?????????tmp????????????????????????
			if (funVar.find(m.result) != funVar.end());
			else if (symList[idenfr].find(m.result) != symList[idenfr].end() ||
				tmpList[idenfr].find(m.result) != tmpList[idenfr].end())
				funVar[m.result] = getTmp();
			else
				funVar[m.result] = m.result;
			// ??????left??????????????????????????????????????????tmp???????????????
			if (funVar.find(m.left) != funVar.end());
			else if (symList[idenfr].find(m.left) != symList[idenfr].end()) {
				if (symList[idenfr][m.left].kind == 1) funVar[m.left] = symList[idenfr][m.left].value;
				else if (symList[idenfr][m.left].kind == 0) funVar[m.left] = getTmp();
			}
			else if (tmpList[idenfr].find(m.left) != tmpList[idenfr].end()) {
				funVar[m.left] = getTmp();
			}
			else
				funVar[m.left] = m.left;
			// ??????right??????????????????????????????????????????tmp???????????????
			if (funVar.find(m.right) != funVar.end());
			else if (symList[idenfr].find(m.right) != symList[idenfr].end()) {
				if (symList[idenfr][m.right].kind == 1) funVar[m.right] = symList[idenfr][m.right].value;
				else if (symList[idenfr][m.right].kind == 0) funVar[m.right] = getTmp();
			}
			else if (tmpList[idenfr].find(m.right) != tmpList[idenfr].end()) {
				funVar[m.right] = getTmp();
			}
			else
				funVar[m.right] = m.right;
			// ??????????????????
			if (m.op == RET || m.op == PAR);
			else if (m.op == RETX) ret = funVar[m.left];
			else addMidCode(funVar[m.result], funVar[m.left], m.op, funVar[m.right]);
		}
	}

	if (symnum != RPARENT) { error('l'); }
	else {
		outputsym();
		symnum = getsym();
	}

	if (fun_idenfr.find(idenfr) == fun_idenfr.end()) { error('0'); }
	else if (fun_idenfr[idenfr]) {
		cout << "<??????????????????????????????>" << endl;
		out << "<??????????????????????????????>" << endl;
	}
	else {
		cout << "<??????????????????????????????>" << endl;
		out << "<??????????????????????????????>" << endl;
	}
	return ret;
}

// ????????????
map<string, string> isValueList(string name) {
	extern map<string, vector<string> > fun_para;
	extern vector <struct midcode> midCodes;
	vector<int> valueList;
	vector <struct midcode> midTmp;
	map<string, string> funPara;
	int i = 0, type = 0, j = 0;
	string tmp;
	if (symnum != RPARENT) {
		valueList.push_back(midCodes.size() - 1);
		type = isExpression(tmp);
		if (i >= fun_para[name].size()) { error('d'); while (getsym() != RPARENT); return funPara; }
		if (symList[name][fun_para[name][i]].type != type) error('e');
		valueList.push_back(midCodes.size());
		addMidCode(name, tmp, PARA, fun_para[name][i++]);
		while (symnum == COMMA) {
			outputsym();
			symnum = getsym();
			type = isExpression(tmp);
			if (i >= fun_para[name].size()) {
				error('d');
				while (getsym() != RPARENT);
				return funPara;
			}
			if (symList[name][fun_para[name][i]].type != type) error('e');
			valueList.push_back(midCodes.size());
			addMidCode(name, tmp, PARA, fun_para[name][i++]);
		}
		if (i < fun_para[name].size()) { error('d'); return funPara; }
		// ????????????????????????????????????
		for (i = valueList.size() - 1; i > 0; i--) {
			for (j = valueList[i - 1] + 1; j < valueList[i]; j++)
				midTmp.push_back(midCodes[j]);
		}
		// ????????????????????????push??????????????????paraList?????????tmp??????
		for (i = valueList.size() - 1, j = fun_para[name].size() - 1; i > 0 && j >= 0; i--, j--) {
			if (symList["$all"][name].value == "f")
				midTmp.push_back(midCodes[valueList[i]]);
			else {
				tmp = getTmp();
				midcode sad ={ tmp, midCodes[valueList[i]].left, ASS, "" };
				midTmp.push_back(sad);
				funPara[fun_para[name][j]] = tmp;
			}
		}
		for (i = valueList[0] + 1, j = 0; i < midCodes.size() && j < midTmp.size(); i++, j++) {
			midCodes[i] = midTmp[j];
			// outputMidcode(midTmp[j], cout);
		}
		while (i != midCodes.size())
			midCodes.pop_back();
		// cout << endl;
	}
	cout << "<????????????>" << endl;
	out << "<????????????>" << endl;
	return funPara;
}

// ????????????
void isAssign(string idenfr) {
	string tmp1, tmp2;
	if (symnum == ASSIGN) {
		outputsym();
		symnum = getsym();
		isExpression(tmp1);
		addMidCode(idenfr, tmp1, ASS, "");
	}
	else if (symnum == LBRACK) {
		outputsym();
		symnum = getsym();
		if (isExpression(tmp1) != 5) { error('i'); };
		if (symnum != RBRACK) { error('m'); }
		else {
			outputsym();
			symnum = getsym();
		}
		if (symnum != ASSIGN) { error('0'); }
		outputsym();
		symnum = getsym();
		isExpression(tmp2);
		addMidCode(idenfr, tmp1, PUTARR, tmp2);
	}
	else { error('0'); }
	cout << "<????????????>" << endl;
	out << "<????????????>" << endl;
}

string getString(string s) {
	extern map<string, map<string, struct sym> > tmpList;
	stringstream ss;
	string str;
	ss << "string$" << stringnum++;
	str = ss.str();
	sym dead = { 1, 4, s };
	tmpList["$all"][str] = dead;
	return str;
}

