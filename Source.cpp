#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <fstream> // for if/ofstream
#include <time.h> // for srand
#include <vector> // for vector
#include <stdio.h> // for printf
#include <stdlib.h> // for rand, srand
#include <sstream>
#include <utility>

using namespace std;

//function that check type error or "border crossing"
int initializeInteger(string path, int lowerBound, int upperBound) {
	bool isCorrect = false;
	int temporaryVariable;
	while (!isCorrect) {
		string temporaryVariableString;
		cin >> temporaryVariableString;
		isCorrect = true;
		for (size_t i = 0; i < 128; i++) {
			if ((i < (int)'0' || i >(int)'9') && i != (int)'-') {
				if (temporaryVariableString.find((char)i) != string::npos) {
					isCorrect = false;
				}
			}
		}
		if (isCorrect) {
			temporaryVariable = stoi(temporaryVariableString);
			if (lowerBound != 0 || upperBound != 0) {
				if (temporaryVariable < lowerBound
					|| temporaryVariable > upperBound) {
					cout << "Initialization error.\nEnter correct value:\n";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					isCorrect = false;
					// operator >> will no longer fetch data from the stream 
					// as it is in the wrong format
				}
			}
			else if (path == "allExceptZero" && temporaryVariable == 0 ||
				path == "negative" && temporaryVariable >= 0 ||
				path == "notpositive" && temporaryVariable > 0 ||
				path == "notnegative" && temporaryVariable < 0 ||
				path == "positive" && temporaryVariable <= 0) {
				cout << "Initialization error.\nEnter correct value:\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				isCorrect = false;
			}
		}
		else {
			cout << "Initialization error.\nEnter correct value:\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	return temporaryVariable;
}

// function that check type error or "border crossing"
double initializeDouble(string path, double lowerBound, double upperBound) {
	bool isCorrect = false;
	double temporaryVariable;
	while (!isCorrect) {
		string temporaryVariableString;
		cin >> temporaryVariableString;
		isCorrect = true;
		for (size_t i = 0; i < 128; i++) {
			if ((i < (int)'0' || i >(int)'9') &&
				i != (int)'-' && i != (int)'.') {
				if (temporaryVariableString.find((char)i) != string::npos) {
					isCorrect = false;
				}
			}
		}
		if (isCorrect) {
			// turns a string into a stream:
			istringstream stringStream(temporaryVariableString);
			stringStream >> temporaryVariable; // reads data from the stream
			if (lowerBound != 0.0 || upperBound != 0.0) {
				if (temporaryVariable < lowerBound ||
					temporaryVariable > upperBound) {
					cout << "Initialization error.\nEnter correct value:\n";
					cin.clear();
					// operator >> will no longer fetch data from the stream:
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					isCorrect = false;
				}
			}
			else if (path == "allExceptZero" && temporaryVariable == 0.0 ||
				path == "negative" && temporaryVariable >= 0.0 ||
				path == "notpositive" && temporaryVariable > 0.0 ||
				path == "notnegative" && temporaryVariable < 0.0 ||
				path == "positive" && temporaryVariable <= 0.0) {
				cout << "Initialization error.\nEnter correct value:\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				isCorrect = false;
			}
		}
		else {
			cout << "Initialization error.\nEnter correct value:\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	return temporaryVariable;
}

void sorting() {
	cout << "\nEnter the number of elements in array:\n";
	// minimal number of elements is 2:
	double arrayLength = 
		initializeDouble("all", 2.0, numeric_limits<double>::max());
	// pointer to dynamic array of type double and size 2:
	double* array = new double[2];
	cout << "\nEnter the elements:\n";
	// two first elements:
	array[0] = initializeDouble("all", 0, 0);
	array[1] = initializeDouble("all", 0, 0);
	// if needful size of array > 2, than extend it:
	for (size_t i = 2; i < arrayLength; i++) {
		double* arrayExtended = new double[sizeof(*array) + 1];
		// copying elements to the new length array:
		for (unsigned int j = 0; j < sizeof(*array); j++) {
			arrayExtended[j] = array[j];
		}
		delete[] array; // deleting old length array
		// assign the pointer with the old name 
		// to the value of the pointer to the new array:
		array = arrayExtended;
		// new element in extended array:
		array[i] = initializeDouble("all", 2.0, numeric_limits<double>::max());
	}
	cout << "\nThe sorted array is:\n";
	// sorting:
	for (size_t i = 0; i < arrayLength; i++) { 	// general iteration
		// beggining with maximal possible value:
		double minimalElement = numeric_limits<double>::max();
		size_t minimalElementIndex = 0; 
		for (size_t j = i; j < arrayLength; j++) { // inserted iteration
			if (array[j] < minimalElement) {
				minimalElement = array[j];
				minimalElementIndex = j;
			}
		}
		// swap current and minimal element:
		swap(array[i], array[minimalElementIndex]);
		cout << array[i] << endl;
	}
}

int main() {
	int chooseTask;
	setlocale(LC_ALL, "Russian");
	cout << "Hello!\nEnter 1 to run sorting.\n"
		"Enter 0 to end the programm.\nEnter the task number:\n";
	chooseTask = initializeInteger("notnegative", 0, 0);
	while (chooseTask > 0) {
		switch (chooseTask) {
		case 1:
			sorting();
			break;
		default:
			cout << "\nEntered number is incorrect, try again.\n"
				"Enter 1 to run sorting.\n"
				"Enter 0 to end the programm.\n";
			break;
		}
		cout << "\nEnter the next number:\n";
		chooseTask = initializeInteger("notnegative", 0, 0);
	}
}
