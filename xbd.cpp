/*
Program 1, hexdump
CS 530 Fall 2020
Erik Morua
cssc3051 
filename: xbd.cpp
*/
#include "xbd.h"
using namespace std;

//prototype functions
unsigned char* readFile(const char*);
void binPrint(unsigned char*, long);
string convert(int);
void hexPrint(unsigned char*, long);
long length;

/*
IN: file location is given. If chosen, will be printed in binary. 
Else: it will be printed in Hex.
File is read. Error checking happens, if we are printing in hex, hexPrint will run. 
If we print in binary, the convert function goes in and converts to binary before printing.
*/
int main(int argc, char* argv[]) {
	int file;

	if (argc == 3) {
		file = 2;
		unsigned char* buffer = readFile(argv[file]);
		binPrint(buffer, length);
	}
	else {
		file = 1;
		unsigned char* buffer = readFile(argv[file]);
		hexPrint(buffer, length);
	}
	unsigned char* buffer = readFile(argv[file]);
	cout << endl;
	free(buffer);
	return 0;
}

/*
* opens file and checks for errors.
* uses the fseek and ftell function to find the length of the file. 
* creates a buffer and stores the contents of the file.
*/
unsigned char* readFile(const char* myFile) {
	FILE* fp;

	//error checking
	fp = fopen(myFile, "r");

	if (!fp) {
		cout << "Could not locate file." << endl;
		exit(1);
	}

	//checking the size of the file
	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	rewind(fp);

	//stores contents of the file into a buffer of size length
	unsigned char* buffer = (unsigned char*) new char[length];
	fread(buffer, 1, length, fp);
	fclose(fp);
	return buffer;
}

/*
IN: buffer with file contents, size
Prints the buffer in hex. If non readable character, print a period.
Loops through the buffer and formats using setfill and setw for readability.
Iterates through the addresses starting at the specified 0000000 location.
*/
void hexPrint(unsigned char* buffer, long length) {
	int row = 16;
	int addressStart = 0000000;

	//loop through buffer and print in hex. if it's a non readable character print a period.
	for (int i = 0; i < length; i++) {
		if (i % row == 0 && i != 0) {
			cout << " ";
			for (int j = row; j > 0; j--) {
				if (buffer[i - j] < ' ' || buffer[i - j] > '~') {
					cout << '.';
				}
				else {
					cout << buffer[i - j];
				}
			}
			cout << endl;
		}

		//formatting our info and printing
		if (i % row == 0) {
			cout << setfill('0') << setw(7) << hex << addressStart << ": ";
			addressStart += row;
		}
		cout << setfill('0') << setw(2) << hex << int(buffer[i]);

		//printing the last of ascii and finding last row.
		if (i == length - 1) {
			int final = length % row;
			int leftovers = row - final;
			int fillers = (leftovers / 2);
			int odd = (leftovers % 2);
			int spaces((leftovers * 2) + odd + fillers + 2);

			cout << setfill(' ') << setw(spaces);
			for (int k = final - 1; k >= 0; k--) {
				if (buffer[i - k] < ' ' || buffer[i - k] > '~') {
					cout << '.';
				}
				else {
					cout << buffer[i - k];
				}
			}
		}
		if ((i % 2) - 1 == 0){
			cout << " ";
		}
	}
}

/*IN: buffer, length
 takes our passed in buffer, converts from hex to binary and then prints what we have in the buffer
 Out: buffer in binary
*/

void binPrint(unsigned char* buffer, long length) {
	int rowBytes = 6;
	int addressStart = 0000000;

	for (int i = 0; i < length; i++) {

		//iterating to look for non readable characters
		if (i % rowBytes == 0 && i != 0) {
			cout << " ";
			for (int j = rowBytes; j > 0; j--) {
				if (buffer[i - j] < ' ' || buffer[i - j] > '~') {
					cout << '.';
				}
				else {
					cout << buffer[i - j];
				}
			}
			cout << endl;
		}
		//first hex then converting to binary
		if (i % rowBytes == 0) {
			cout << setfill('0') << setw(7) << hex << addressStart << ": ";
			addressStart += rowBytes;
		}

		//hex to binary and print
		cout << convert(int(buffer[i]));

		//same as hex print, printing the last row. Non readable characters as periods.
		if (i == length - 1) {
			int final = length % rowBytes;
			int leftovers = rowBytes - final;
			int spaces = (leftovers * 9) + 3;
			cout << setfill(' ') << setw(spaces);

			//replacing non readable characters with periods
			for (int k = final - 1; k >= 0; k--) {
				if (buffer[i - k] < ' ' || buffer[i - k] > '~') {
					cout << '.';
				}
				else {
					cout << buffer[i - k];
				}
			}
		}
		cout << " ";
	}

}

//since we only have 16 choices, we are taking each byte and comparing it to one of the cases. 
//simple binary print after the byte is found 
string convert(int num) {
	string result = "";

	//we will read in one bit at a time in the hex decimal passed in, take the case and then move on to the next bit.
	int k = num / 16;
	//converting to binary, put out a case for each hex byte
	for (int i = 0; i < 2; i++) {
		switch (k) {
		case (0):
			result.append("0000");
			break;
		case (1):
			result.append("0001");
			break;
		case (2):
			result.append("0010");
			break;
		case (3):
			result.append("0011");
			break;
		case (4):
			result.append("0100");
			break;
		case (5):
			result.append("0101");
			break;
		case (6):
			result.append("0110");
			break;
		case (7):
			result.append("0111");
			break;
		case (8):
			result.append("1000");
			break;
		case (9):
			result.append("1001");
			break;
		case (10):
		case ('A'):
		case ('a'):
			result.append("1010");
			break;
		case (11):
		case ('B'):
		case ('b'):
			result.append("1011");
			break;
		case (12):
		case ('C'):
		case ('c'):
			result.append("1100");
			break;
		case (13):
		case ('D'):
		case ('d'):
			result.append("1101");
			break;
		case (14):
		case ('E'):
		case ('e'):
			result.append("1110");
			break;
		case (15):
		case ('F'):
		case ('f'):
			result.append("1111");
			break;
		
		}
		k = num % 16;
	}
	return result;
}//end
