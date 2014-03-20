//This is just for Michael to test his morse code stuff with a real compiler.
//It is probably irrelevant to the balloon (but still interesting)

#include <iostream>
#include <string>

using namespace std;



string play(string code){

	string dotDash;

	for(unsigned int i = 0; i<code.size(); i++){
		switch(code.at(i)){
			case '.':
				dotDash.append("dot");
				break;
			case '-':
				dotDash.append("DASH");
				break;
			case '/':
				dotDash.append("       ");
				break;
			case ' ':
				dotDash.append("\n");
				break;
//For some reason this went ahead of time
//			default:
//				cout << "Nothing happening";
		}		
	}
	return dotDash;

}

int main(){

	string morseCode = "...---.../";

	//Ask the user for some morse code
	cout << "What is the morse code that you want to see? (use .-/):";
	std::getline(cin,morseCode);


	cout << play(morseCode) << endl;
	return 0;
}
