//program to test the conversions in the src.ino
#include <iostream>

using namespace std;

//time coversion, only takes numbers. Returns -1 if it fails
long int timeConv(char* input){
	for(int i = 0; i < 6; i++){
		if((input[i] < 48 ) | (input[i] > 57)) return -1;
	}
	//s + s*10 + m*60 + m*600 + h*3600 + h*36000
	return (input[5]-48) + (input[4]-48)*10 + (input[3]-48)*60 + (input[2]-48)*600 + (input[1]-48)*3600 + (input[0]-48)*36000;
}




//degree conversion
double degConv(char* input){
	for(int i = 0; i < 9; i++){
		if(input[i] == '.') continue;
		if((input[i] < 48 ) | (input[i] > 57)) return -1;
	}
	int degree = (input[0]-48)*10 + (input[1]-48);
	long int mins = (input[2]-48)*100000 + (input[3]-48)*10000 + (input[5]-48)*1000 + (input[6]-48)*100 + (input[7]-48)*10 + (input[8]-48);

	return (double)degree + mins/(60*(double)10000);
}


long int degConv2(char* input){
	int decimal = 0;
	int multiplier = 10;
	for(int i = 0; i < 9; i++){
		if(input[i] == '.'){
			decimal = i;
			continue;
		}
		if((input[i] < 48 ) | (input[i] > 57)) return -1;
	}
	if((input[decimal+1] < 48 ) | (input[decimal+1] > 57)) return -1;


	long int altitude = (input[decimal+4] - 48);
	
	for(int i = decimal+3; i > decimal; i--){
		altitude += (input[i]-48)*multiplier;
		multiplier *= 10;
	}

	for(int i = decimal-1; i > 0; i--){
		altitude += (input[i]-48)*multiplier;
		multiplier *= 10;
	}

	return altitude;
}

//altitude conversion to decimeters
long int altConv(char* input){
	int decimal = 0;
	int multiplier = 10;
	for(int i = 0; i < 9; i++){
		if(input[i] == '.'){
			decimal = i;
			break;
		}
		if((input[i] < 48 ) | (input[i] > 57)) return -1;
	}
	if((input[decimal+1] < 48 ) | (input[decimal+1] > 57)) return -1;


	long int altitude = (input[decimal+1] - 48);
	for(int i = decimal-1; i > 0; i--){
		altitude += (input[i]-48)*multiplier;
		multiplier *= 10;
	}

	return altitude;
}


int main(){
	char time[] = "225704.000";
	char lat[] = "4225.6455";
	char lon[] = "07809.3606";
	char alt1[] = "359.9";
	char alt2[] = "55689.4";

	cout << timeConv(time) << ',';
	cout << degConv2(lat) << ',';
	cout << degConv2(&lon[1]) << ',';
	cout << altConv(alt1) << ',';
	cout << altConv(alt2) << endl;

}
