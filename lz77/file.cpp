#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	string filename;
	cin>>filename;
	ifstream filein;
	filein.open(filename.c_str());
	char ch,c,c1;
	string s1;
	filein.get(ch);
	s1.push_back(ch);
	filein.get(c);
	s1.push_back(c);
	filein.get(c1);
	s1.push_back(c1);
	filein.close();
	cout<<ch<<c<<c1<<"sdfS"<<s1.size()<<endl;
	return 0;
}
