
#include <iostream>
#include <fstream>
using namespace std;
	/*ofstream fileout;
	fileout.open("anand.txt");
	ofstream fileout1;
	fileout1.open("anan1.txt");
	for(int i = 0;i<10;i++){
		for(int j =0;j<10;j++){
			fileout<< char(i+47);
			fileout1 <<char(100);
		}
	}*/
	
	
string convertToChar(int a){
	string b ;

	while(a != 0){
		int i = a%10;
		b=b+ char(i+48);
		a=a/10;
	}
	
	string c;
	int len = b.length() - 1;
	while(len>=0){
		c=c+b[len];
		len--;
	}
		return c;
}
int main(){
	cout<<convertToChar(45);
	return 1;
}
