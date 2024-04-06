#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Scanner.h"
#include "Token.h"
#include "parseEval.h"

using namespace std;

//NOTE: main function is at the bottom

//the following is for error report; can implement if time available
/*class python
{
    private:
        bool hadError = false;
    public:
        void report(int line, string where, string message)
        {
            cout << "[Line " + line "] Error" + where + ": " + message << endl;//FIXME: not a System.error sort of print
        }
        void error(int line, string message)
        {
            report(line, "", message);
        }
}*/

string runFile(string filePath)
{
    ifstream inputStream(filePath);
    string code = "";

    while (!inputStream.eof())
    {
        code += inputStream.get();
    }
    return code;
}

void run(string code)
{
    Scanner scanner(code);
    vector<Token> tokens = scanner.scanTokens();
    parser(tokens, 0, tokens.size(), 0);
}

int main (int argc, char * argv[])
{
    /*second element of argv will contain filepath.
    its contents will be extracted as a char array*/
    string filePath = argv[1];
    string code = runFile(filePath);
    run(code);
}