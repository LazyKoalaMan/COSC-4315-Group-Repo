#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "scanner.h"

using namespace std;


float processNumbers(int x,int y,char process){
    int result=0;

    if(process=='+'){
        result=x+y;
    }
    
    if(process=='*'){
        result=x*y;
    }
    
    if(process=='/'){
        result=x/y;
    }
    
    if(process=='-'){
        result=x-y;
    }

    return result;
}
string printer(string line, map<string, int>& lst) {
    string result = "";

    size_t pos1 = line.find("\"");
    size_t pos2 = line.find("\"", pos1 + 1); // Find the second occurrence of "

    if (pos1 != string::npos && pos2 != string::npos) { // Check if both " characters are found
        string content = line.substr(pos1 + 1, pos2 - pos1 - 1); // Extract content within quotes
        result += content;
        
        // Check if there's a comma after the closing quote
        size_t commaPos = line.find(",");
        if (commaPos != string::npos) {
            string variable = line.substr(commaPos + 1);
            // Remove spaces from the variable name
            variable.erase(remove_if(variable.begin(), variable.end(), ::isspace), variable.end());
            
            // Find the value corresponding to the variable name in the map
            if (lst.find(variable) != lst.end()) {
                result += to_string(lst[variable]);
            }
        }
    }

    return result;
}

bool ifManager(char operation,string line){
    if (operation != 'i') {
        cerr << "Invalid operation!" << endl;
        return false;
    }
    
    // Find the position of the "<" symbol
    size_t pos = line.find("<");
    if (pos == string::npos) {
        cerr << "Invalid condition!" << endl;
        return false;
    }
    
    // Extract the variable and the value
    string variable = line.substr(3, pos 
}



int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    string outfilename="output.txt";
    ofstream output;
    output.open(outfilename);
    ifstream file(argv[1]);//scans .\mypython example1.txt
    //*/
    //https://www.youtube.com/watch?v=SToUyjAsaFk

    vector<string> func;
    map<string,char> variables;
    string lines1,operators="+-/*";
    
    int amount = 0;
    bool funcExist = false;

    if (file.is_open()) {
        for (std::string line; std::getline(file, line);) {
            if (line[0] != '#') {
                lines1 += line + '\n'; // Append the line to the lines1 string
            }
            //Process 
           size_t pos = line.find('=');
           size_t posP = line.find('"');
           
           if(posP!=string::npos)
           {
                printer(lines1, variables);
           }else{
            if (pos != string::npos) {
                // Extract the variable name and value
                string varName = line.substr(0, pos);
                string varValueStr = line.substr(pos + 1);
                cout<<varValueStr<<endl;
                // Convert the value string to an integer
                int varValue = stoi(varValueStr);

                // Store the variable name and value in the map
                variables[varName] = varValue;
            }
           }
        }
        file.close();
    } else {
        std::cerr << "Failed to open file!" << std::endl;
        return 1;
    }
    


    for (const auto& f : func) {
            //output <<amount<< f << endl;
            amount++;
    }
    file.close();
    output.close();
    
    return 0;
}



/*

ifstream file("example1.txt");
    


*/
