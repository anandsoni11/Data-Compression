#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct code_ds {
	int offset;
	int length;
	char symbol;
};

vector<string> get_all_strings(char a, string s, vector<string> v) {
	int i,j,k=0;
	string s1;
	//cout<<"here I enter.."<<endl;
	while(k<s.size()) {
		//cout<<"here is k"<<" "<<k<<endl;
		if(s[k]!=a) k++;
		else {
			//cout<<"hey....!!"<<endl;
			for(i=0; i<s.size()-k; i++) {
				for(j=k; j<=k+i; j++) {
					s1.push_back(s[j]);
				}
				v.push_back(s1);
				s1.clear();
			}
			k++;
		}
		//cout<<"hiii..!!"<<endl;
	}
	//cout<<"here I terminate.."<<endl;
	return v;
}

vector<string> get_strings(char a, string s, vector<string> v) {
	int i=0; string s1;
	while(i<s.size()) {
		if(s[i]==a) {
			s1.push_back(s[i]);
			i++;
			while(s[i]!=a and i<s.size()) {
				s1.push_back(s[i]);
				i++;
			}
			v.push_back(s1);
			s1.clear();
			/*string s1;
			int k;
			for(k=i; k<s.size(); k++) {
				s1.push_back(s[k]);
			}
			get_strings(a,s1,v);*/
		}
		else {
			i++;
			/*if(i==s.size()) {
				vector<string> v2;
				v2.clear();
				return v2;
			}*/
		}
	}
	
	return v;
}
	/*int i=0;
	while(s[i]!=a) {
		i++;
		if(i==s.size()) {
			vector<string> v1;
			v1.clear();
			return v1;
		}
	}
	cout<<"while ends"<<endl;
	string str;
	str.push_back(s[i]);
	i++;
	//int l=i;
	cout<<"while2 begins"<<endl;
	while(s[i]!=a and i!=s.size()) {
		str.push_back(s[i]);
		i++;
	}
	cout<<"while2 ends"<<endl;
	v.push_back(str);
	str.clear();
	int k;
	string str1;
	if(i<s.size()) {
		for(k=i; k<s.size(); k++) {
			str1.push_back(s[k]);
		}
		get_strings(a, str1,v);
	}
	else return v;
}*/


string longest_match(string s1, string s2) {
	vector<string> v,v1;
	string s3;
	vector<string> vec = get_all_strings(s2[0], s1, v);
	if(vec.size()==0) {
		string s="";
		return s;
	}
	
	else {
		int i;
		for(i=0; i<vec.size(); i++) {
			int l1=(vec[i]).size();
			int l2= s2.size();
			int j=1;
			s3.push_back(s2[0]);
			if(l1>l2) {
				while(j!=l2 and s2[j]==(vec[i])[j]) {
					s3.push_back(s2[j]);
					j++;
				}
				v1.push_back(s3);
				s3.clear();
			}
					
			else {
				while(j!=l1 and s2[j]==(vec[i])[j]) {
					s3.push_back(s2[j]);
					j++;
				}
			}
			v1.push_back(s3);
			s3.clear();
		}
		int max=v1[0].size();
		int max_index=0;
		for(i=1; i<v1.size(); i++) {
			if(v1[i].size()>=max) {
				max=v1[i].size();
				max_index=i;
			}
		}
		
		return v1[max_index];
	}
}
			
					
int find_index(string m, string s) {
	int i=0;
	int len= m.size();
	while(i<s.size()) {
		if(m==s.substr(i,len)) {
			return i+1;
		}
		else i++;
	}
}					 
	
	
//vector<code_ds> encode(string& filename, vector<code_ds> v) {
void encode(string& filename, vector<code_ds> &v) {
	string search_buffer;
	code_ds encrypt;
	string look_ahead_buffer;
//	vector<string> vec;
	ifstream filein;
	filein.open(filename.c_str());
	//cout<<"here 1"<<endl;
	if(filein.is_open()) {
		//cout<<"here 2"<<endl;
		while(filein.good() or look_ahead_buffer.size()!=0) {
			char ch;
			//int ctr=look_ahead_buffer.size();
			while(look_ahead_buffer.size()<15 and filein.good()) {
				filein.get(ch);
				look_ahead_buffer.push_back(ch);
			}
			cout<<look_ahead_buffer.size()<<"adads"<<endl;
			cout<<look_ahead_buffer<<":"<<"can u see the problem?"<<endl;
			//if(look_ahead_buffer.size()!=0) {
				string s=longest_match(search_buffer, look_ahead_buffer);
				if(s=="") {
					encrypt.offset=0;
					encrypt.length=1;
					encrypt.symbol=look_ahead_buffer[0];
					v.push_back(encrypt);
					 
					search_buffer.push_back(look_ahead_buffer[0]);
					if(search_buffer.size()>=400) {
						search_buffer= search_buffer.substr(100, search_buffer.size()-100);
					}
					look_ahead_buffer= look_ahead_buffer.substr(1,look_ahead_buffer.size()-1);
				}
			
				else {
					int index1= find_index(s, search_buffer);
					int len= s.size();
					encrypt.offset=index1;
					encrypt.length=len;
					if(len==15) {
						filein.get(ch);
						encrypt.symbol=ch;
					}
					else encrypt.symbol=look_ahead_buffer[len];
					v.push_back(encrypt);
					search_buffer.append(look_ahead_buffer.substr(0, len));
					if(search_buffer.size()>=400) {
						search_buffer= search_buffer.substr(100, search_buffer.size()-100);
					}
					if(len==15) {
						string lk;
						lk.push_back(ch);
						look_ahead_buffer= lk;
					}
					else {
						look_ahead_buffer= look_ahead_buffer.substr(len, look_ahead_buffer.size()-len);
					}
					//look_ahead_buffer= look_ahead_buffer.substr(len, 5-len);
				}
			
		}
		cout<<look_ahead_buffer<<" "<<look_ahead_buffer.size()<<":"<<"here is the problem"<<endl;
	}
	else;
	//cout<<"Size of v "<<v.size()<<endl;
	
	//return v;
} 

int return_int(char c) {
	if(c=='0') return 0;
	else if(c=='1') return 1;
	else if(c=='2') return 2;
	else if(c=='3') return 3;
	else if(c=='4') return 4;
	else if(c=='5') return 5;
	else if(c=='6') return 6;
	else if(c=='7') return 7;
	else if(c=='8') return 8;
	else if(c=='9') return 9;
	else return -1;
}
			
void decode(string& filename, vector<char> &v) {
	ifstream filein;
	filein.open(filename.c_str());
	if(filein.is_open()) {
		while(filein.good()) {
			char ch;
			filein.get(ch);
			if((int)ch<48 or (int)ch>57) {
				if((int)ch==46 or (int)ch==58);
				else v.push_back(ch);
			}
			
			else {
				char ch1;
				vector<int> ind;
				ind.push_back(return_int(ch));
				//filein.get(ch1);
				//ind.push_back(return_int(ch));
				while(ch1!=':') {
					filein.get(ch1);
					ind.push_back(return_int(ch1));
				}
				int index1;
				if(ind.size()==2) {
					index1=ind[0];
					ind.clear();
				}
				else if(ind.size()==3) {
					index1=ind[0]*10 + ind[1];
					ind.clear();
				}
				
				else if(ind.size()==4) {
					index1=ind[0]*100 + ind[1]*10 + ind[2];
					ind.clear();
				}
				else;
				
				cout<<index1<<"here is index1"<<endl;
				 
				int leng;//= return_int(ch1);
				int i;
				vector<int> l;
				char ch2;
				while(ch2!='.') {
					filein.get(ch2);
					l.push_back(return_int(ch2));
				}
				if(l.size()==2) {
					leng=l[0];
					l.clear();
				}
				else if(l.size()==3) {
					leng=l[0]*10 + l[1];
					l.clear();
				}
				
				else if(l.size()==4) {
					leng=l[0]*100 + l[1]*10 + l[2];
					l.clear();
				}
				else;
				
				cout<<leng<<"here is leng"<<endl;
				
				for(i=index1-1; i<=index1+leng-2; i++) {
					v.push_back(v[i]);
				}
			}
		}
	}
	ofstream fileout;
	fileout.open("decompressed.txt");
	int j;
	for(j=0; j<v.size(); j++) {
		fileout<<v[j];
	}
	fileout.close();
}

					


int main() {
	/*string s1,s2;
	cin>>s1>>s2;
	cout<<longest_match(s1,s2,0)<<endl;
	cout<<longest_match(s1,s2,5)<<endl;*/
	//string s,s1; char c;
	vector<code_ds> v;
	vector<char> vec;
	string filename;
	cin>>filename;
	
	encode(filename, v);
	//decode(filename,vec);
	ofstream fileout;
	fileout.open("compressed.aa");
	int i;
	for(i=0; i<v.size(); i++) {
		if(v[i].offset==0) fileout<<v[i].symbol;
		else {
			//string s = myprint(v[i].offset,v[i].length);
			fileout<<v[i].offset<<':'<<v[i].length<<'.';
		}
	}
	fileout<<"@";
	fileout.close();
	/*code_ds enc,enc1,enc2,enc3,enc4,enc5,enc6,enc7,enc8,enc9,enc10,enc11;
	cout<<"Size of v "<<v.size()<<endl;
	enc = v[0];
	enc1= v[1];
	enc2 = v[2];
	enc3= v[3];
	enc4 = v[4];
	enc5= v[5];
	enc6 = v[6];
	enc7= v[7];
	enc8=v[8];
	enc9=v[9];
	enc10=v[10];
	enc11=v[11];
	cout<<enc.offset<<" "<<enc.length<<" "<<enc.symbol<<endl;
	cout<<enc1.offset<<" "<<enc1.length<<" "<<enc1.symbol<<endl;
	cout<<enc2.offset<<" "<<enc2.length<<" "<<enc2.symbol<<endl;
	cout<<enc3.offset<<" "<<enc3.length<<" "<<enc3.symbol<<endl;
	cout<<enc4.offset<<" "<<enc4.length<<" "<<enc4.symbol<<endl;
	cout<<enc5.offset<<" "<<enc5.length<<" "<<enc5.symbol<<endl;
	cout<<enc6.offset<<" "<<enc6.length<<" "<<enc6.symbol<<endl;
	cout<<enc7.offset<<" "<<enc7.length<<" "<<enc7.symbol<<endl;
	cout<<enc8.offset<<" "<<enc8.length<<" "<<enc8.symbol<<endl;
	cout<<enc9.offset<<" "<<enc9.length<<" "<<enc9.symbol<<endl;
	cout<<enc10.offset<<" "<<enc10.length<<" "<<enc10.symbol<<endl;
	cout<<enc11.offset<<" "<<enc11.length<<" "<<enc11.symbol<<endl;*/
	//vector<string> v1= get_all_strings(c,s,v);
	//string st= longest_match(s, s1);
	//cout<<st<<endl;
	//int index= find_index(st, s);
	//cout<<index<<endl;
	/*string s0=v1[0];
	string s2=v1[1];
	string s3=v1[2];
	string s4=v1[3];
	string s5=v1[4];
	string s6=v1[5];
	string s7=v1[6];
	string s8=v1[7];
	string s9=v1[8];
	string s10=v1[9];
	string s11=v1[10];
	string s12=v1[11];
	string s13=v1[12];
	string s14=v1[13];
	string s15=v1[14];
	string s16=v1[15];
	string s17=v1[16];
	string s18=v1[17];
	//string s2=v1[2];
	//string s3=v1[3];
	cout<<s0<<" "<<s2<<" "<<s3<<" "<<s4<<" "<<s5<<" "<<s6<<" "<<s7<<" "<<s8<<" "<<
	s9<<" "<<s10<<" "<<s11<<" "<<s12<<" "<<s13<<" "<<s14<<" "<<s15<<" "<<s16<<" "<<s17<<endl;//" "<<s2<<" "<<s3<<endl;	*/
	cout<<"done"<<endl;
	return 0;
}
		
		
		
