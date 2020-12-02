// Brian Foster
// Advent of Code 2020 | Day 2


// false answers on 2nd task: 384. that answer is too high. Oh! I added a number to "zero-index" but I should have subtracted.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool debug = false;

bool validate(int min, int max, char letter, string password) {
	if(debug) {
		cout << "min(" << min << "), max(" << max << "), letter(" << letter << ").\n";
		cout << "password(" << password << ").\n";
	}
	int counter = 0;
	for(int i = 0; i < password.size(); i++) {
		if(password[i] == letter) {
			counter += 1;
		}
	}
	if(counter >= min && counter <= max) {
		return true;
	} else {
		return false;
	}
}

bool validateTwo(int firstPosition, int secondPosition, char letter, string password) {
	if(debug) {
		cout << "firstPosition(" << firstPosition << "), secondPosition(" << secondPosition << "), letter(" << letter << ").\n";
		cout << "password(" << password << ").\n";
	}

	// adjusting zero-index.
	firstPosition -= 1;
	secondPosition -= 1;

	if(password[firstPosition] == letter && password[secondPosition] == letter) {
		return false;
	}
	else if(password[firstPosition] == letter || password[secondPosition] == letter) {
		return true;
	}
	else {
		return false;
	}
}


// parse password, send to validate(), and count the valid passwords.
int main() {
	int validPasswords = 0;
	int validPasswords2 = 0;

	int counter = 0;

	fstream file("input.txt");

	if(file.is_open()) {
		if(debug) cout << "The file is open.\n";

		string line;
		while(getline(file, line)) {
			
			if(debug) {
				counter++;
				if(counter > 10) break;
			}

			int min, max;
			int first, second;
			char letter;
			string pass;
			string buffer;

			for(int i = 0; i < line.size(); i++) {
				if(line[i] == '-') {
					min = stoi(buffer);
					first = stoi(buffer);
					buffer = "";
				}
				else if(line[i] == ' ' && line[i - 1] != ':') {
					max = stoi(buffer);
					second = stoi(buffer);
					buffer = "";
				}else if(line[i] == ':') {
					letter = line[i - 1];
					buffer = "";
				} else if(line[i] == ' ') {
					continue;
				} 
				else {
					buffer += line[i];
				}
				
			}
			pass = buffer; 

			bool passwordIsValid = validate(min, max, letter, pass);
			bool passwordIsValid2 = validateTwo(first, second, letter, pass);

			if(passwordIsValid) validPasswords += 1;
			if(passwordIsValid2) validPasswords2 += 1;
		}
	} else {
		cout << " I could not read the file.\n";
	}

	cout << "There are " << validPasswords << " valid passwords, according to the first task.\n";
	cout << "There are " << validPasswords2 << " valid passwords, according to the second task.\n";

	return 0;
}