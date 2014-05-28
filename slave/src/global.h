//Ultilites we can use to do stuff
#ifndef _GLOBAL_H_
#define _GLOBAL_H_


#define CENTER_LAT	41.996243	//latitude of center point
#define CENTER_LONG	77.987309	//longitude of the center point
#define MAXDISTANCE	80000		//distance (in meters) to stay within


int getline(char* input, char* output, char delim){
	for(int i = 0; i < SIZE; i++){
		if(input[i] != delim){
			output[i] = input[i];
			continue;
		}
		return i+1;
	}
}

int getline(char* input, char delim){
	for(int i = 0; i < SIZE; i++){
		if(input[i] != delim){
			continue;
		}
		return i+1;
	}
}

int checksum(char * chk)
{
	char a(chk[1]);
	for(int i = 2;chk[i]!='*';i++)
	{
		a = a ^ chk[i];
	}

	return (int)a;
}

double resultant(double lat, double lon){

	double x = (lon - CENTER_LONG) * 111974.434;
	double y = (lat - CENTER_LAT) * 82226.69901;
	return sqrt(x*x + y*y);
}

unsigned int htoi(char * s)
{
	unsigned int val = 0;

	for(int x = 0; x < 2; x++)
	{
		if(val > 255) return 0;
		else if(s[x] >= '0' && s[x] <='9')
		{
		   val = val * 16 + s[x] - '0';
		}
		else if(s[x]>='A' && s[x] <='F')
		{
		   val = val * 16 + s[x] - 'A' + 10;
		}
		else return 0;
	}
	return val;
}
#endif
