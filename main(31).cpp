#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string removeTextInBrackets(const string& input) {
    string result = "";
    int bracketLevel = 0;

    for (char c : input) {
        if (c == '(') {
            bracketLevel++;
        } else if (c == ')') {
            if (bracketLevel > 0) {
                bracketLevel--;
            }
        } else {
            if (bracketLevel == 0) {
                result += c;
            }
        }
    }
    return result;
}

void processFiles(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Pomylka pry vidkrytti fajliv!" << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        string processedLine = removeTextInBrackets(line);
        outputFile << processedLine << endl;
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    string t1 = "t1.txt";
    string t2 = "t2.txt";

    processFiles(t1, t2);

    cout << "Opracyuvannya zaversheno. Perevirte fajl " << t2 << endl;

    return 0;
}
Результат:


Результат UnitTest:
TEST_METHOD(TestRemoveTextInBrackets)
{
    ofstream t1_v1("t1.txt");
    t1_v1 << "Hello (secret (inside)) world!";
    t1_v1.close();
    
    processFiles("t1.txt", "t2.txt");
    
    ifstream res1("t2.txt");
    string line1;
    getline(res1, line1);
    res1.close();
    Assert::AreEqual(string("Hello  world!"), line1);

    ofstream t1_v2("t1.txt");
    t1_v2 << "No brackets here";
    t1_v2.close();
    
    processFiles("t1.txt", "t2.txt");
    
    ifstream res2("t2.txt");
    string line2;
    getline(res2, line2);
    res2.close();
    Assert::AreEqual(string("No brackets here"), line2);

    ofstream t1_v3("t1.txt");
    t1_v3 << "(one) and (two)";
    t1_v3.close();
    
    processFiles("t1.txt", "t2.txt");
    
    ifstream res3("t2.txt");
    string line3;
    getline(res3, line3);
    res3.close();
    Assert::AreEqual(string(" and "), line3);

    remove("t1.txt");
    remove("t2.txt");
}
