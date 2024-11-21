#include <iostream>
#include <fstream>

using namespace std;

//Change file names here if applicable
string inFileName = "input.txt";
string outFileName = "output.txt";


int main() {
        ifstream inFile; 
        inFile.open(inFileName);
        string newName;  
        DoublyLL* nameList = new DoublyLL;
        while (inFile >> newName) {
                newName = toLower(newName);
                if (newName == "delete") {
                        //Delete encountered, need to take in a new name before deletion
                        inFile >> newName;
                        newName = toLower(newName);
                        nameList->deleteNode(newName);
                } else {
                        nameList->insert(newName);
                }  
        }
        inFile.close();
        ofstream outFile;
        outFile.open(outFileName);
        nameList->traverseAscending(outFile);
        outFile << "=============" << endl;
        nameList->traverseDescending(outFile);
        outFile.close();
        delete nameList;
        return 0;
}
