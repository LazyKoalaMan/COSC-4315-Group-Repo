#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//Run commands to make executable
//g++ -o mypython mypython.cpp
//./mypython example1.txt

string replace_string(const std::string& original_string, const std::string& target, const std::string& replacement) {
    std::string modified_string = original_string;
    size_t index = modified_string.find(target);
    while (index != std::string::npos) {
        modified_string.replace(index, target.length(), replacement);
        index = modified_string.find(target, index + replacement.length());
    }
    return modified_string;
}

int occurrenceCounter(const std::vector<std::string>& listX, const std::string& elemToCheck, size_t size) {
    int count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (listX[i] == elemToCheck) {
            count++;
        }
    }
    return count;
}

std::vector<std::string> deletion(const std::vector<std::string>& listX, const std::string& elemToCheck, int numOccurrences, size_t size) {
    std::vector<std::string> result;
    for (size_t i = 0; i < size; ++i) {
        if (listX[i] != elemToCheck || numOccurrences <= 0) {
            result.push_back(listX[i]);
        } else {
            numOccurrences--;
        }
    }
    return result;
}

// bool checkahead(string list,string word){
//     string wordTemp=word;
//     string sentence=list;
//     if (sentence.empty() || sentence.length() < wordTemp.length()) {
//         return false;
//     }

//     if (sentence.substr(0, word.length()) == wordTemp) {
//         return true;
//     }

//     return checkahead(sentence.substr(1), wordTemp);
// }

//Push if, while, 
vector<string> bracketMaker(vector<string> list){
    vector<string> tempList;
    vector<string> list={"if","for","while","return",}
    stack<string> stack;
    for(int x=0;x<list.length();x++)
        for(int y=0;yM)
    if(list[x].find){

    }

    return tempList;
}


vector<string> categorizeFunc3(string list) {
    vector<string> organized;
    string tempList=list;
    size_t pos = 0;
    int endLst=0;

    while ((pos = tempList.find("def ", pos)) != string::npos) {
        // Find the end of the function definition after def
        size_t endPos = tempList.find("\n\n", pos);
        if (endPos == string::npos) {
            endPos = tempList.length();
        }
        // Extract the entire function definition
        string functionDef = tempList.substr(pos, endPos - pos);
        organized.push_back(functionDef);
        pos = endPos;
        endLst=pos;
    }
    organized.push_back(tempList.substr(endLst));
    
    return organized;
}


// vector<string> categorizeFunc(string list) {
//     vector<string> organized;
    
//     int amount = 0;
//     bool funcExist = false;
//     string tempList=list;

//     while (checkahead(tempList, "def")) {
//         // Find the position of the next "def" keyword
//         size_t defPos = tempList.find("def");
//         if (defPos == string::npos) {
//             funcExist = false;
//             break; // Exit the loop if no more "def" keywords are found
//         }
//         else {
//             amount++;
//             funcExist = true;
//         }

//         // Find the position of the next "return" keyword after the "def"
//         size_t returnPos = tempList.find("return", defPos);
//         if (returnPos == string::npos) {
//             funcExist = false;
//             break; // Exit the loop if no "return" keyword is found after the "def"
//         }
//         else {
//             amount++;
//             funcExist = true;
//         } 

//         // Extract the content between the "def" and "return" keywords
//         string functionContent = tempList.substr(defPos, returnPos - defPos);
//         organized.push_back(functionContent);


//         // if(checkahead(tempList, "def")){    
//         //     int defPosCheck = tempList.find("def");
//         //     if(defPosCheck>2){
//         //         organized[amount]=tempList.substr(0, defPosCheck);
//         //     }
//         // }

//         // Remove the extracted content from the input string
//         tempList.erase(defPos, returnPos - defPos);
//     }

//     // Add the remaining content (after the last "return" keyword) to the list
//     organized.push_back(tempList);
//     cout<<amount<<endl;
//     return organized;
// }


/*

    for (std::string line; list) {
        if (line[0] != '#') {
            lines1.push_back(line);
        }

        if (funcExist) {
            if (line.find("return") != std::string::npos) {
                funcExist = false;
            }
            func[amount].push_back(line);
        } else {
            if (line.find("def") == std::string::npos && !funcExist && amount >= 1) {
                func[amount].push_back(line);
            }
            size_t start_index = line.find("def");
            if (start_index != std::string::npos && !funcExist) {
                amount++;
                func[amount] = {line};
                funcExist = true;
            }
        }
    }


*/

class Simplifier {
public:
    // Add member functions and variables here
    //bool checkAhead();
    
};

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

    vector<string> func;
    string lines1;
    
    int amount = 0;
    bool funcExist = false;

    if (file.is_open()) {
        for (std::string line; std::getline(file, line);) {
            if (line[0] != '#') {
                lines1 += line + '\n'; // Append the line to the lines1 string
            }
        }
        file.close();
    } else {
        std::cerr << "Failed to open file!" << std::endl;
        return 1;
    }
    //Process 

    //cout<<"lines "<<lines1<<endl<<endl;
    func=categorizeFunc3(lines1);
    //cout<<"Func "<<func<<endl<<endl;//
    
    
    //PRINTING

    // cout << "Lines from file:" << endl;
    // for (const auto& line : func) {
    //     cout << line << endl;
    // }

    //
    for (const auto& f : func) {
            output <<amount<< f << endl;
            amount++;
    }
    file.close();
    output.close();
    
    return 0;
}



/*

ifstream file("example1.txt");
    


*/
