// Brian Foster
// Advent of Code Day 3

// the input repeats forever to the right.
// if I go right 3 and down 1, will I hit a tree? 
// start in the top left, end in the bottom right.

// this is a multidimensional array[0][0].
// when I get to the end of the array, use a modulus 
// to loop back to the beginning of the line.
// OR, is it just an array of strings? Each would be an array of characters.
// each "turn" is down one and over three.

// actually, just skip the array!

// 323 lines
// 31 chars per line.


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool debug = false;

int countTrees(int right, int down) {
    int index = 0;
    int trees = 0;

    fstream file("input.txt");
    if(file.is_open()) {
        string line;

        for(int i = 0; getline(file, line); i++) {
            if(i == 0) continue;
            index += right;
            if(i % down != 0) continue;
            if(line[index % line.size()] == '#') trees += 1;
        }

        cout << "For the slope [" << right << ", " << down << "] I will hit " << trees << " trees on my way to the airport.\n";
        file.close();
    }

    return trees;
}

int main() {
    cout << "Day 3!\n";

    unsigned long int totaltrees = 1;

    int slopes[5][2] =  {   {1, 1},
                            {3, 1},
                            {5, 1},
                            {7, 1},
                            {1, 2}
                        };
    
    for(int i = 0; i < 5; i++) {
        totaltrees *= countTrees(slopes[i][0], slopes[i][1]);
    }

    cout << "For all of the slopes I will hit " << totaltrees << " trees.\n";

    return 0;
}