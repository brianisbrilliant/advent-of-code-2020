// Brian Foster
// Advent of Code 2020 Day 4

// part 1
// looking for 8 key:value pairs. if 'cid:****' is missing, that is okay.
// so, use a counter to check for 8. if there are 7,
// check to see if there are any with the key "cid". if there are, invalid! if not, "valid!"

// wrong answers: 5 (haha, I suspected it was)
// wrong answer: 128, too low. sheesh, what a mess this is when trying to get it at midnight.
// wrong answer: 188, too low. sheesh. time to read the prompt again. 
// wrong answer: 188, too low. I think my solution is correct.
// wrong answer: 231. yikes.
// right answer: 202. huzzah!

/*part 2: extra validation
    byr (Birth Year) - four digits; at least 1920 and at most 2002
    iyr (Issue Year) - four digits; at least 2010 and at most 2020
    eyr (Expiration Year) - four digits; at least 2020 and at most 2030
    hgt (Height) - a number followed by either cm or in:
        If cm, the number must be at least 150 and at most 193
        If in, the number must be at least 59 and at most 76
    hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f
    ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth
    pid (Passport ID) - a nine-digit number, including leading zeroes
    cid (Country ID) - ignored, missing or not
*/

// wrong answer: 155, too high.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool debug = false;


bool checkNumInRange(int num, int min, int max) {
    if(num < min || num > max) return false;
    else return true;
}

// should work for int, eyr, byr, pid, cid
// removes code, converts to int, returns int.
int stringToInt(string input) {
    input.erase(0,4);

    try { 
        return stoi(input); 
    } catch(invalid_argument& e) { 
        return -1; 
    }
}

// bool byr(string input) {
//     int birthYear = stoi(input);
//     if(birthYear < 1920 || birthYear > 2002) return false;
//     else return true;
// }

// bool iyr(string input) {
//     int issuedYear = stoi(input);
//     if(issuedYear < 2010 || issuedYear > 2020) return false;
//     else return true;
// }

bool validatePass(vector<string> parts) {
    // if the size is 6 or less, return false.
    if(parts.size() < 7) return false;

    bool hasCID = false;

    // BUT even if it has all 8, we need to check each part.
    for(int i = 0; i < parts.size(); i++) {
        //string code = parts[i][0] + parts[i][1] + parts[i][2];
        string code = "nil";
        code[0] = parts[i][0];
        code[1] = parts[i][1];
        code[2] = parts[i][2];
        if(debug) cout << "in validatePass(), code = " << code << ".\n";
        // an if looking for each bit, with their own checks for each.
        // if they are ever false, return false.
        if(code == "byr") {
            if(checkNumInRange(stringToInt(parts[i]), 1920, 2002)) continue;     // if it all checks out, keep validating
            else return false;              // if it fails, return false out of the validate function.
        }
        else if(code == "iyr") {
            if(checkNumInRange(stringToInt(parts[i]), 2010, 2020)) continue;
            else return false;
        }
        else if(code == "eyr") {
            if(checkNumInRange(stringToInt(parts[i]), 2020, 2030)) continue;
            else return false;
        }
        else if(code == "cid") {
            hasCID = true;
            continue;
        }
        else if(code == "pid") {
            string input = parts[i];
            input.erase(0,4);       // erasing code

            if(input.size() == 9) continue;
            else {
                if(debug) cout << "size of pid: " << input.size() << endl;
                return false;
            }
        }
        else if(code == "hgt") {
            bool isInches = true;
            if(parts[i][parts[i].size() - 1] == 'm') isInches = false;

            // removing the units at the end.
            string input = parts[i];
            input.pop_back();
            input.pop_back();
            
            if(isInches) {
                if(checkNumInRange(stringToInt(input), 59, 76)) continue;
                else return false;
            }
            else {
                if(checkNumInRange(stringToInt(input), 150, 193)) continue;
                else return false;
            }
        }
        else if(code == "hcl") {
            string nums = "0123456789";     // bahaha, using a string as an array of chars 
            string letters = "abcdef";
            string input = parts[i];
            input.erase(0,4);               // erase the 'key', leaving the value.

            if(input.size() != 7) return false;     // is the size correct?
            if(input[0] != '#') return false;       // is there a # at the beginning?

            for(int i = 1; i < input.size(); i++) {
                bool charIsNum = false;
                bool charIsLetter = false;

                // loop through numbers and letters, breaking out of the loop if success.
                for(int j= 0; j < nums.size(); j++) {
                    if(input[i] == nums[j]) {
                        charIsNum = true;
                        break;
                    }
                }
                for(int k = 0; k < letters.size(); k++) {
                    if(input[i] == letters[k]) {
                        charIsLetter = true;
                        break;
                    }
                }

                if(charIsNum || charIsLetter) continue;
                else return false;
            }

            
        }
        else if(code == "ecl") {
            string colors[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
            bool colorIsValid = false;
            string input = parts[i];
            input.erase(0,4);

            for(int i = 0; i < 7; i++) {
                if(input == colors[i]) colorIsValid = true;
            }

            if(colorIsValid) continue;
            else return false;
        }
        else {
            cout << "Validation error for code: " << code << ".\n";
            return false;
        }    
    }

    if(parts.size() == 7 && hasCID) return false; 
    
    // if the code gets this far, all tests have passed!
    return true;
}


int main() {
    cout << "Day 4!\n";

    if(debug) {
        cout << "Testing the validate function.\n";
        vector<string> testPass;
        testPass.push_back("cid:110");
        testPass.push_back("hgt:76in");
        testPass.push_back("iyr:2018");
        testPass.push_back("eyr:2029");
        testPass.push_back("pid:474429956");
        testPass.push_back("byr:2002");
        testPass.push_back("hcl:#866857");
        testPass.push_back("ecl:amb");
        
        if(validatePass(testPass)) cout << "Successful test!\n";
        else cout << "Test failed.\n";

        //return 0;
    }

    fstream file("input.txt");
    bool newEntry = false;      // when an empty line is detected, we "start over" for a new passport
    int validPassports = 0;     // the total number of valid passports.
    int loopCounter = 0;        // for debugging part of the data instead of the whole
    int passCounter = 0;        // number each passport for hand validation

    if(file.is_open()) {
        vector<string> data;    // we'll add each data point to this vector of strings.

        string line;            // the entire line, read in by getline()
        while(getline(file, line)) {
            if(debug) {
                cout << "line: " << line << "\n";
                loopCounter += 1;
                if(loopCounter > 100) {
                    break;
                }
            }

            if(line == "") {
                newEntry = true;
                passCounter += 1;

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
                if(validatePass(data)) {
                    validPassports += 1;
                    cout << "Passport #" << passCounter << " is VALID\n";
                } else {
                    cout << "Passport #" << passCounter << " is INVALID\n";
                }
                // if(data.size() == 8) {
                //     validPassports += 1;
                //     cout << "Passport #" << passCounter << " is VALID\n";
                // } else if(data.size() == 7) {
                //     bool hasCID = false;

                //     for(int i = 0; i < data.size(); i++) {
                //         if(debug) cout << "\tChecking for 'cid'...\n";
                //         if(data[i].find("cid") != string::npos) {
                //             if(debug) cout << "\tpass has cid.\n";
                //             hasCID = true;
                //             break;
                //         }
                //     }

                //     if(hasCID) {
                //         cout << "Passport #" << passCounter << " is INVALID\n";
                //         // reset the vector, we are looking again.
                //         if(debug) cout << "clearing the vector, valids = " << validPassports << ".\n";
                //         data.clear();
                //         continue;
                //     }
                //     else {
                //         cout << "Passport #" << passCounter << " is \"VALID\".\n";
                //         validPassports += 1;
                //     }
                // } else {
                //     cout << "Passport #" << passCounter << " is INVALID\n";
                // }

                // reset the vector, we are looking again.
                if(debug) cout << "clearing the vector, valids = " << validPassports << ".\n";
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
                if(debug) cout << "end of line, adding '" << buffer << "'.\n";
                data.push_back(buffer);
                buffer.clear();
            }
            
            if(debug) cout << "\n";
        }

        cout << "Total valid passports: " << validPassports << ".\n";

        file.close();
    } else {
        cout << "Could not read file.\n";
    }



    return 0;
}