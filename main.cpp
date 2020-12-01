// Brian Foster
// Advent of Code Day 1

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {

	bool debug = false;			// enable this for additional cout statements.
	vector<int> numbers;		// the list of numbers
	
	int answer1 = -1;
	int answer2 = -1;
	int totalCycles = 0;

	// open the input text file.
	ifstream input ("input.txt");
	if (input.is_open())
	{
		string line;
		// add numbers to the vector of ints.
		while ( getline (input,line) )
		{
			numbers.push_back(stoi(line));		// stoi converts strings to ints
		}
		// close the input text file.
		input.close();

		// display numbers to ensure they work.
		if(debug) {	
			cout << "numbers created, here they are:\n";
			for(int i = 0; i < numbers.size(); i++) {
				cout << numbers[i] << endl;
			}
		}

		// parse the numbers to find the correct pair that equal 2020
		// just a nested for loop to check each one against each other one?
		// we don't need to check the duplicates against each other more than once...
		// so I have set j = i instead of 0 every time, to save time.
		for(int i = 0; i < numbers.size(); i++) {
			if(debug) cout << "\n\n";
			for(int j = i; j < numbers.size(); j++, totalCycles++) {
				if(answer1 == -1) {
					if(debug) cout << "Does " << numbers[i] << " plus " << numbers[j] << " equal 2020?\n";

					if(numbers[i] + numbers[j] == 2020) {
						cout << "We've found a match!\n";
						cout << "\n\tThe correct numbers are " << numbers[i] << " + " << numbers[j] << " = 2020.\n\n"; 

						answer1 = numbers[i] * numbers[j];

						cout << numbers[i] << " x " << numbers[j] << " = " << answer1 << "!!!\n";
						cout << "It took " << totalCycles << " turns to find these numbers.\n";
					}
				}
				if(answer2 == -1) {
					for(int k = i; k < numbers.size(); k++, totalCycles++) {
						
						if(numbers[i] + numbers[j] + numbers[k] == 2020) {
							cout << "The Three numbers are\n";
							cout << numbers[i] << ", "<< numbers[j] << ", " << numbers[k] << "\n";

							int product = numbers[i] * numbers[j] * numbers[k];
							cout << "The product of those numbers is " << product << ".\n\n";
							
							answer2 = product;
							
						}
					}
				}
				if(answer1 != -1 && answer2 != -1) return 0;
				
			}
		}
	}
	else {
		cout << "Unable to open file"; 
	}

	return 0;

}