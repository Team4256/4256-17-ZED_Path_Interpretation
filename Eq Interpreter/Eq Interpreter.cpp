#include "stdafx.h"
#include "exprtk.hpp"

#include <iostream>
#include <fstream>
#include <string>

using std::clock;
using std::string;

typedef double T;//just use t rather than typing double each time
typedef exprtk::symbol_table<T> symbolTableT;
typedef exprtk::expression<T> expressionT;
typedef exprtk::parser<T> parserT;

std::ifstream inFile;
string currText;

parserT parser;

time_t start = clock();
time_t current = clock();
T difference = ((double)(current - start)) / ((double)CLOCKS_PER_SEC);

int main() {
	inFile.open("C:\\Users\\h_shively\\0eveloper\\workspace\\{git} Eq Interpreter\\Left Gear.txt");
	if (inFile.fail()) {
		std::cerr << "An error occurred while opening the file." << std::endl;
		system("pause");
		exit(1);
	}
	if (inFile.is_open()) {
		int untilCheck = -1;
		int xCheck = -1;
		int yCheck = -1;
		T until = -1;
		string strx = "empty";
		string stry = "empty";
		while (!inFile.eof()) {
			std::getline(inFile, currText);//get new line
			currText.erase(std::remove_if(currText.begin(), currText.end(), isspace), currText.end());//delete whitespace
			untilCheck = untilCheck != -1 ? -2 : currText.find("Until:");//-1 when absent, becomes >= 0 after this line if present, -2 when this line is reached again

			if (untilCheck >= 0) { until = std::stod(currText.substr(6, std::string::npos)); }//save line if good	atof(currText.substr(6, std::string::npos).c_str());

			if (untilCheck == -2) {//only bother looking for x if found until
				xCheck = xCheck != -1 ? -2 : currText.find("x:=");
				if (xCheck >= 0) { strx = currText; }//save line if good
			}

			if (untilCheck == -2 && xCheck == -2) {//only bother looking for y if found until and x
				yCheck = yCheck != -1 ? -2 : currText.find("y:=");
				if (yCheck >= 0) { stry = currText; }//save line if good
			}

			if (until != -1 && strx != "empty" && stry != "empty") {//have everything saved, ready to begin processing
				symbolTableT symbolX;
				expressionT eqX;
				symbolTableT symbolY;
				expressionT eqY;
				while (difference <= until) {
					current = clock();
					difference = ((double)(current - start)) / ((double)CLOCKS_PER_SEC);
					T numx = T(0);
					symbolX.add_variable("t", difference);
					symbolX.add_variable("x", numx);
					symbolX.add_constants();
					eqX.register_symbol_table(symbolX);
					parser.compile(strx, eqX);
					numx = eqX.value();

					printf("%19.5f", numx);

					T numy = T(0);
					symbolY.add_variable("x", numx);
					symbolY.add_variable("y", numy);
					symbolY.add_constants();
					eqY.register_symbol_table(symbolY);
					parser.compile(stry, eqY);
					numy = eqY.value();

					printf("%19.5f", numy);
				}
				//reset variables for next section of equations
				untilCheck = -1;
				xCheck = -1;
				yCheck = -1;
				until = -1;
				strx = "empty";
				stry = "empty";
			}
		}
	}

	system("pause");

	exit(0);
}