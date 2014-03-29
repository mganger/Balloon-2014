//This program is for testing the wildcard function

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>

int wildcard(char *path){

	std::string strPath = path;				//make a string for simplicity

	for(unsigned int i = 0; i<strPath.size();i++){
		if(strPath.at(i) == '!'){			//to avoid conflicts with bash
			for(int j = 0; j<=9; j++){
				strPath.erase(strPath.size() - 1);
				std::ostringstream oss;
				oss << j;
				strPath += oss.str();
				std::ifstream file(strPath.c_str());
				if(file){
					strPath.copy(path,100,0);
					return 1;		//exit method on success
				}
			}
		}
	}
	return 0;				//return 0 if failed.		
}


int main(int argc,char* argv[]){
	if (argc == 2){
		char * buffer = argv[1];
		if(wildcard(buffer)){
			std::cout << "Path is " << buffer << std::endl;
		}
	}else {
		std::cerr << "Only takes 1 argument, not " << (argc - 1) << std::endl;
	}
}
