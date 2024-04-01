
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
