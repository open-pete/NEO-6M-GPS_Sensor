
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
                        cout << "found , in " << temp << " at |" << pos1 << "|" << endl;
                        pos2=temp.find(",",pos1+1);
                        cout << "found second , in " << temp << " at |" << pos2 << "|" << endl;
                        string substring="";
                        if (pos2 != string::npos) {
                                substring = temp.substr(pos1+1,(pos2-pos1-1));
                                cout << "extract from " << pos1+1 << " to " << pos2-pos1-1 << "|" << substring << "|" << endl;
                                pos1=pos2;
                        } else {
                                substring = temp.substr(pos1+1);
                                cout << "extract from " << pos1+1 << " to end " << "|" << substring << "|" << endl;
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

int main () {
	int fd ;

  	if ((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0) {
	    cout << "Unable to open serial device: %s\n" << endl ;
	} else {
	    cout << "Opened /dev/ttyAMA0" << endl;
	}

// Loop, getting and printing characters

  string s="";
  string c="";

  for (;;) {
	cout << readLineFromSerial(fd) << endl;
}/*
    c = serialGetchar (fd);
    cout << "|" << c;
    if (c=="\n") {
	vector<string> strings;
        std::size_t pos1 = 0;
        std::size_t pos2 = string::npos;

	if (s.find("GPGLL") != string::npos) {
		strings = CSV2StringVector(s);
		cout << "---------------------------------" << endl;
		for (int i=0; i< strings.size();i++) {
			cout << "result " << strings[i] << endl;
		}
		cout << "+++++++++++++++++++++++++++++++++" << endl;
	
	}

	s="";

    } else {

	s+=c;

    }
  }*/
}

