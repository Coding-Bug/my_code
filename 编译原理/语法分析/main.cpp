#include "Lexical_analysis.h"
#include "Grammar_analysis.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int main() {
	ifstream fin;
	fin.open("test/testfile.txt");
	ofstream fout;
	fout.open("test/output.txt");
	if (!fin.is_open() || !fout.is_open()) {
		cerr << "err: cannot open file: "<< endl;
		cerr << "Please check the path and file name." << endl;
		return 0;
	}
	Lexical_analysis &lexical_analysis = Lexical_analysis::initialLexicalanalysis(fin,fout);
	Grammar_analysis grammar_analysis(lexical_analysis,fout);
    grammar_analysis.getSymbol();
	// while (lexical_analysis.getSymbol() != FINISH) {
	// 	lexical_analysis.nextSymbol();
	// }
	//grammar_analysis.grammarAnalyze();
	//grammar_analysis.stringAnalysis();
	//grammar_analysis.intAnalysis();
}