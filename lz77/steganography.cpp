/*
 * This is a template file to be used for assignment.
 * General instructions:
 * 1.Do not remove any included library file/namespace declaration.You can add more you need.
 * 2.Use function void yourCode(CImg<unsigned char>& sourceImage,int option,string &text)
 *  as a starting point to add your code.You may add more functions/classes etc if you need.
 * 3.Do not change main function.
 * 4.Use following commands to install necessary libs:
 * 		sudo apt-get install xorg-dev
 * 		sudo apt-get install imagemagick
 * 5.While compiling the code add -lpthread and -lX11.So your target will look like
 * 		g++ steganography.cpp  -lX11 -lpthread
 * 6.Help Page : http://cimg.sourceforge.net/
 * 7.Do not save image as jpeg.
 */

#include <iostream>
//#include <fstream>
#include <string>
#include <bitset>
#include <typeinfo>
#include <cstdio>

using namespace std;

#include "CImg.h"
using namespace cimg_library;
bitset<8> give(bitset<8> x, int index){
	if (index==1){x>>=5 ;}
	else if(index==2) {x<<=3;   x>>=5;}
	else {x <<=5 ; x>>=5;}
	
	return x;
}



void enc_v2(CImg<unsigned char> &sourceImage , int i , int j, unsigned char temp){            //this is the second version which uses
 											//bitwise operators rather than simple bit by bit access and assignment
	
	bitset<8> c =temp ;
	//cout<< "char is " << c;
	sourceImage(i,j,0,0)>>=3; sourceImage(i,j,0,0)<<=3;
	sourceImage(i,j,0,1)>>=3; sourceImage(i,j,0,1)<<=3;
	sourceImage(i,j,0,2)>>=3; sourceImage(i,j,0,2)<<=3;
	
	sourceImage(i,j,0,0)|=give(c, 1).to_ulong();
	sourceImage(i,j,0,1)|=give(c, 2).to_ulong();
	sourceImage(i,j,0,2)|=give(c, 3).to_ulong();
}


unsigned char dec_v2(CImg<unsigned char> &sourceImage , int i , int j){
	bitset<8> bc ;
	sourceImage(i,j,0,0)<<=5;
	sourceImage(i,j,0,1)<<=5;sourceImage(i,j,0,1)>>=3;
	sourceImage(i,j,0,2)<<=6;sourceImage(i,j,0,2)>>=6;
	
	bc=sourceImage(i,j,0,0)|sourceImage(i,j,0,1)|sourceImage(i,j,0,2);
	
	unsigned long y = bc.to_ulong();

	//cout << "unicode no :\t"<< y<<endl;
	unsigned char c = static_cast<unsigned char>( y ) ;
	return c;
}


/*
 * Starting point for your code.
 * Source Image file is now loaded in variable sourceImage
*/


void yourCode(CImg<unsigned char>& sourceImage,char option,string& text){

	/*
	 ----------------------------------------------------------------------
	 This is sample code to show some of the operations you may need to do.
	 ----------------------------------------------------------------------
	 We get height, width and number of channels from the image.
	 What are channels?
	 check here : http://www.imagemagick.org/Usage/color_basics/
	*/
	int imageHeight = sourceImage.height();
	int imageWidth = sourceImage.width();
	int imageDepth = sourceImage.depth();
	int imageChannels = sourceImage.spectrum();


	//## debugging
	//unsigned char tt = 'w';
	//if (option=='e') {enc_v2(sourceImage, 100,100, tt);}
	//else { cout<<"decrepted character is : " <<dec_v2(sourceImage, 100,100)<<endl; }
	//##enddebugging
	
	
   	//starting the main code 	
    if(option=='e'){
		const char *cs = text.c_str ();
		FILE * fp=fopen(cs,"r");
		unsigned char c;
		
		//Now read the input text file char by char and encode into image .
		if (fp!=NULL){
 			for(int i=0; i< imageWidth ; i++)
     		{
     			for(int j=0; (j<imageHeight ) ; j++)
     			{	
     				c=fgetc(fp);
     				enc_v2(sourceImage , i,j, c);
     				//scount++; 
     				
     				if (feof(fp)) { 
     					c= (char)0; 
     					{enc_v2(sourceImage , i, j, c) ; break;}    //ONCE file ends,  encode character corresponding
     					   											// to ascii 0 into very next pixel
     					}
     			}
     			if (feof(fp)) break;
     		}
     		
     		fclose (fp);
     	}
     	else cout<<"cant open input file\n"; 
     } 
     		
     //decrypt pixel by pixel and write into output text file until find the character corresponding to ascii value 0;
     else if(option=='d') {
     	cout<<"in decrepting part\n";
     	//ofstream fileout;
     	FILE* fp;
     	const char *fname = text.c_str ();
     	fp=fopen(fname,"w");
     	
     	string msg; msg.clear();
     	
     	unsigned char ch; int flag=1; 
     	for(int i=0; i<imageWidth; i++){
     		for(int j=0; j<imageHeight ;j++)
     		{
     			ch=dec_v2(sourceImage,i,j) ;
     			if (ch==(char)0){flag=0; break ;}
     			else {
     				fputc(ch , fp);
     				//cout << ch;
     			}
     			
     		}
     		if (flag== 0) {break ;}
     	}
     	fclose(fp);
     }
}     	
     	
     	


/*
 * Reads user input from console.Do not edit.
 */
void getUserInput(string& imageSource, string& filename, char& option) {
	cout << "Enter e for encrypt, d for decrypt :" << endl;
	cin >> option;
	cout << "Enter Image File Name" << endl;
	cin >> imageSource;
	if(option == 'e'){
		cout << "Enter file name of the message to be encrypted:" << endl;
		
	}
	else
	  cout << "Enter  name of file into which decrypted message will be written:" << endl; 

	cin >> filename;
}



int main() {
	string imageSource;
	//char textFile1[100];
	string textFile;
	char option;
	
	// Read the source image 
	getUserInput(imageSource, textFile, option);

	
	CImg<unsigned char> sourceImage(imageSource.c_str());


	yourCode(sourceImage,option, textFile);
	
	//bitset<8> rComponent = sourceImage(100,100,0,0);
	//cout<< "Type is :" << typeid(rComponent).name() <<endl;
	
	if(option == 'e')
		{sourceImage.save(imageSource.append("_encrypted.png").c_str());
		cout<<"seee the new image\n"; 
		}
	else
	  cout << "Decryption" << endl;
	return 0;
}



