/*
 * hangman.cpp
 *
 *  Created on: 17.04.2024
 *      Author: swt
 */

#include <iostream>
#include <cstring>
#include "word.h"
#include <ctime>

using namespace std;

void hint(string word, string words[][10]);
char playerInput(char playerchoice);
void fillEmpty(char array[], int length);
void fillLetter(char playerchoice, string word, char array[]);
void draw(char array[], int length);
int checkLives(char playerchoice, string word, int lives);
bool gameEnd(char array[], int length, int lives, string word);

int main(int argc, const char* argv[]){

	cout << " ******** Welcome to Hangman !!! ******** " << endl;
	bool running = true;
	char playerchoice;
	int lives = 11;
	srand(time(0));
	int rnd1 = rand() % 5;
	int rnd2 = rand() % 10;
	string my_word = words[rnd1][rnd2];
	char output[my_word.length()];
	int length = sizeof(output)/sizeof(char);
	fillEmpty(output, length);
	draw(output, length);
	hint(my_word, words);

	while(running){
		playerchoice = toupper(playerInput(playerchoice));
		fillLetter(playerchoice, my_word, output);
		draw(output, length);
		lives = checkLives(playerchoice, my_word, lives);
		bool end = gameEnd(output, length, lives, my_word);
		if(end == true){
			running = false;
		}
	}
	return 0;
}

void hint(string word, string words[][10]){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j <= 10; j++){
			if(word == words[0][j]){
				cout << "HINT: *** It's a brand! *** \n";
				break;
			}
			else if(word == words[1][j]){
				cout << "HINT: *** It's a food! *** \n";
				break;
			}
			else if(word == words[2][j]){
				cout << "HINT: *** It's a job! *** \n";
				break;
			}
			else if(word == words[3][j]){
				cout << "HINT: *** It's a sport! *** \n";
				break;
			}
			else if(word == words[4][j]){
				cout << "HINT: *** It's an action! *** \n";
				break;
			}
		}
		break;
	}
}


char playerInput(char playerchoice){
	cout << "Your letter of choice: ";
	cin >> playerchoice;
	return playerchoice;
}

void fillEmpty(char array[], int length){
	for(int i = 0; i < length; i++){
		array[i] = '_';
	}
}

void fillLetter(char playerchoice, string word, char array[]){
	for(unsigned int i = 0; i < word.length(); i++){
		if(word[i] == playerchoice){
			if(array[i] != word[i]){
				array[i] = playerchoice;
			}
			else{
				continue;
			}
		}
	}
}

void draw(char array[], int length){
	for(int i = 0; i < length; i++){
		cout << array[i] << " ";
	}
	cout << "\n\n";
}

int checkLives(char playerchoice, string word, int lives){
	int showup = 0;
	for(unsigned int i = 0; i < word.length(); i++){
		if(word[i] == playerchoice){
			showup++;
		}
	}
	if(showup == 0){
		lives--;
	}
	cout << "Remaining lives: " << lives << "\n";
	return lives;
}

bool gameEnd(char array[], int length, int lives, string word){
	int countletters = 0;
	for(int i = 0; i < length; i++){
		if(array[i] != '_'){
			countletters++;
		}
	}
	if(countletters == length){
		cout << " ******** CONGRATULATIONS, ******** \n";
		cout << " ******** YOU WIN !        ******** ";
		return true;
	}
	else if(lives == 0){
		cout << " ******** GAME OVER,   ******** \n";
		cout << " ******** YOU LOSE !!! ******** \n";
		cout <<"The word was: " << word;
		return true;
	}
	return false;
}
