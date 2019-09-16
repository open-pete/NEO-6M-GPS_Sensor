
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <wiringSerial.h>
#include <iostream>
#include <vector>

using namespace std;

vector<string> CSV2StringVector(const string& commaSeparatedString_) {
	vector<string> strings;
        std::size_t pos1 = 0;
        std::size_t pos2 = string::npos;

                string temp=commaSeparatedString_;
                pos1=temp.find(",",pos1);

                while (pos1 != string::npos) {
                        //cout << "found , in " << temp << " at |" << pos1 << "|" << endl;
                        pos2=temp.find(",",pos1+1);
                        //cout << "found second , in " << temp << " at |" << pos2 << "|" << endl;
                        string substring="";
                        if (pos2 != string::npos) {
                                substring = temp.substr(pos1+1,(pos2-pos1-1));
                                //cout << "extract from " << pos1+1 << " to " << pos2-pos1-1 << "|" << substring << "|" << endl;
                                pos1=pos2;
                        } else {
                                substring = temp.substr(pos1+1);
                                //cout << "extract from " << pos1+1 << " to end " << "|" << substring << "|" << endl;
                                pos1=pos2;
                        }
                        strings.push_back(substring);
		}

	return strings;
}

string readLineFromSerial(int fileDescriptor_) {
	string c;
	c = serialGetchar (fileDescriptor_);
	string result="";
	while(c != "\n") {
		result += c;
		c = serialGetchar (fileDescriptor_);
	}
	return result;
}

double angularMinute2Degree(string angularMinutesValue, string format_ = "ddmm.mmmmm") {
	double result;

	if ( angularMinutesValue.length() == format_.length() ) {
	        std::size_t pos = 0;
		string degreeString;
		string angularMinutesString;
		pos = format_.find("m");
		cout << "pos " << pos << endl;
		if (pos != string::npos) {
			degreeString = angularMinutesValue.substr(0,pos);
			angularMinutesString = angularMinutesValue.substr(pos-1);
			cout << degreeString << " - " << angularMinutesString << endl;
			double degreeDouble = std::stod(degreeString);
			double angularMinutesDouble = std::stod(angularMinutesString);
			cout.precision(8);
			cout << degreeDouble << " xx " << angularMinutesDouble << endl;
			result = degreeDouble + (angularMinutesDouble / 60.0);

		}
	}
	return result;
}

int main () {
	cout << angularMinute2Degree("4934.59024");
	return 0;
	int fd ;

  	if ((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0) {
	    cout << "Unable to open serial device: %s\n" << endl ;
	} else {
	    cout << "Opened /dev/ttyAMA0" << endl;
	}

	// Loop, getting and printing characters

	string s="";
	vector<string> strings;

	for (;;) {
		s=readLineFromSerial(fd);
		if (s.find("GPGLL") != string::npos) {
			strings = CSV2StringVector(s);
			cout << "---------------------------------" << endl;
			for (int i=0; i< strings.size();i++) {
				cout << "result " << strings[i] << endl;
			}
			cout << "+++++++++++++++++++++++++++++++++" << endl;

		}

  	}
}

