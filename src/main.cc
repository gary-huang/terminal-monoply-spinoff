#include <string>
#include <iostream>
#include <fstream>
#include "controller.h"
using namespace std;

//const int ERR_TOOMANYARGS = 70;

//enum Errors {ERR_TOO_FEW_ARGS = 4, ERR_TOO_MANY_ARGS, ERR_INCORRECT_ARGS, ERR_FILE_FAIL};

int argumentCheck(int argc, char *argv[], string &fileName) {
	if (argc == 1) {
		cout << "Got no arguments." << endl;
		return NEW;
	}

	if (argc == 2) {
		string firstArg = argv[1];
		if (firstArg == "-testing") {
			cout << "Testing mode." << endl;
			return NEW_TEST;
		} else if (firstArg == "-load") {
			cerr << "Expecting file name after -load." << endl;
			return ERR_TOO_FEW_ARGS;
		} else {
			cerr << "Command not recognized." << endl;
			return ERR_INCORRECT_ARGS;
		}
	}

	if (argc == 3) {
		string firstArg = argv[1];
		if (firstArg == "-load") {
			//cout << "-load arugment got file " << argv[2] << endl;
			fileName = argv[2];
			ifstream ifs(fileName.c_str());
			if (ifs.fail()) {
				cerr << "Can't open " << fileName;
				cerr << ". Ensure that the file exists and is readable." << endl;
				return ERR_FILE_FAIL;
			}
			return LOAD;
		} else {
			cerr << "Given number of arguments, expecting the argument -load file." << endl;
			return ERR_INCORRECT_ARGS;
		}
	}

	if (argc == 4) {
		string firstArg = argv[1];
		string secondArg = argv[2];
		string thirdArg = argv[3];
		if ((firstArg == "-load") && (thirdArg == "-testing")) {
			fileName = secondArg;
			ifstream ifs(fileName.c_str());
			if (ifs.fail()) {
				cerr << "Can't open " << fileName;
				cerr << ". Ensure that the file exists and is readable." << endl;
				return ERR_FILE_FAIL;
			}
			return LOAD_TEST;			
		} else if ((firstArg == "-testing") && (secondArg == "-load")) {
			fileName = thirdArg;
			ifstream ifs(fileName.c_str());
			if (ifs.fail()) {
				cerr << "Can't open " << fileName;
				cerr << ". Ensure that the file exists and is readable." << endl;
				return ERR_FILE_FAIL;
			}
			return LOAD_TEST;
		} else {
			cerr << "Given number of arguments, expecting the argument -load file, and -testing." << endl;
			return ERR_INCORRECT_ARGS;
		}
	}

	cerr << "There are too many command line arguments." << endl;
	return ERR_TOO_MANY_ARGS;
}

int main(int argc, char *argv[]) {

	string loadFile = "";
	int argCheck = argumentCheck(argc, argv, loadFile);
	
	if (argCheck > LOAD_TEST) {
		return argCheck;
	} else {
		Controller c(loadFile);
		c.init(argCheck);
	}
}
