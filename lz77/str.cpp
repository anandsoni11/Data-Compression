#include <iostream>
#include <string>

using namespace std;

string ret_s(string& s) {
	s.append(" ksdf");
	return s;
}

int main() {
	string s;
	//cin>>s;
	//r/et_s(s);
	//cout<<s<<endl;
	cout<<"adla"<<endl;
	string s1,s2;
	s1.push_back('T');
	s1.push_back(' ');
	s1.push_back('h');
	s2=s1.substr(1,2);
	cout<<s2<<"sadasd"<<endl;
	return 0;
}
	
