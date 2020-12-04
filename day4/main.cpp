// Brian Foster
// Advent of Code 2020 Day 4

// looking for 8 key:value pairs. if 'cid:****' is missing, that is okay.
// so, use a counter to check for 8. if there are 7,
// check to see if there are any with the key "cid". if there are, invalid! if not, "valid!"

// wrong answers: 5 (haha, I suspected it was)
// wrong answer: 128, too low. sheesh, what a mess this is when trying to get it at midnight.


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool debug = true;

int main() {
    cout << "Day 4!\n";

    fstream file("input.txt");
    bool newEntry = false;
    int validPassports = 0;
    int loopCounter = 0;

    if(file.is_open()) {
        vector<string> data;

        string line;
        while(getline(file, line)) {
            if(debug) {
                cout << "line: " << line << "\n";
                loopCounter += 1;
                // if(loopCounter > 10) {
                //     break;
                // }
            }

            if(line == "") {
                newEntry = true;
                if(debug) { 
                    cout << "New Entry detected!\n";
                    cout << "Here's the vector:\n";
                    for(int i = 0; i < data.size();i++) {
                        cout << i + 1 << " - '" << data[i] << "'\n";
                    }
                    cout << "\n\n";
                }

            }
            if(newEntry) {
                // reset newEntry
                newEntry = false;

                // Do the tests for valid/invalid
                if(data.size() == 8) {
                    validPassports += 1;
                    if(debug) cout << "\tpass has all 8!\n";
                }
                if(data.size() == 7) {
                    for(int i = 0; i < data.size(); i++) {
                        if(debug) cout << "\tChecking for 'cid'...\n";
                        if(data[i][0] == 'c' && data[i][1] == 'i' && data[i][2] == 'd') {
                            validPassports += 1;
                            if(debug) cout << "\tpass is missing cid.\n";
                            break;
                        }
                    }

                    if(debug) cout << "\tcid is present, pass is invalid.\n";
                }

                // reset the vector, we are looking again.
                if(debug) cout << "clearing the vector.\n";
                data.clear();
            }

            // do the regular stuff of adding things to the vector.
            string buffer;
            for(int i = 0; i < line.size(); i++) {
                if(line[i] == ' ' || line[i] == '\n') {
                    if(debug) cout << "adding '" << buffer << "' to data vector.\n";
                    data.push_back(buffer);
                    buffer.clear();
                } else {
                    if(debug) cout << ".";
                    buffer += line[i];
                }
            }
            if(buffer != "") {
                data.push_back(buffer);
                buffer.clear();
            }
            
            cout << "\n";
        }

        cout << "Total valid passports: " << validPassports << ".\n";

        file.close();
    } else {
        cout << "Could not read file.\n";
    }



    return 0;
}