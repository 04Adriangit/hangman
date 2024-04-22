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
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// * Functions declaration *
string hint(string word, string words[][10]);
char corresponding(int code);
void fillEmpty(char array[], int length);
string draw(char array[], int length, char letter, string word);
int checkLives(char letter, string word, int lives);
bool gameEnd(char array[], int length, int lives, string word);

int main(){
	//* Variables *
	const unsigned int WIDTH = 800;
	const unsigned int HEIGHT = 600;
	unsigned int LIVES = 11;
	bool running = true;
	int key_code = 0;
	srand(time(0));
	int rnd1 = rand() % 5;
	int rnd2 = rand() % 10;
	string my_word = words[rnd1][rnd2];
	char output[my_word.length()];
	int length = sizeof(output)/sizeof(char);
	// * Objects *
	RenderWindow window(VideoMode(WIDTH,HEIGHT),"Hangman game");

	Font font;
	// * Check if font file found else return failure *
	if(!font.loadFromFile("ArialCE.ttf")){
		return EXIT_FAILURE;
	}
	// * Menu *
	Text play("PLAY", font, 50);
	FloatRect playbutton = play.getGlobalBounds();
	Vector2 mousepos = Mouse::getPosition(window);
	float mouseposx = mousepos.x;
	float mouseposy = mousepos.y;
	// * Game *
	Text displayed_hint(hint(my_word,words),font,20);
	Text displayed_lives("Remaining lives: " + to_string(11) + " ",font,30);
	FloatRect ltextrect = displayed_lives.getLocalBounds();
	// * End *

	// * Fill array with underscore *
	fillEmpty(output, length);
	// ***
	Text displayed_word(draw(output, length, '_', my_word), font, 50);
	Text displayed_letter("_", font, 50);
	FloatRect textRect = displayed_word.getLocalBounds();
	Color RED = Color::Red;
	Color WHITE = Color::White;
	Color BLACK = Color::Black;

  //	cout << " ******** Welcome to Hangman !!! ******** " << endl;


	// * edit text objects *
	play.setColor(WHITE);
	play.setOrigin(playbutton.left + playbutton.width/2, playbutton.top + playbutton.height/2);
	play.setPosition(WIDTH/2, HEIGHT/2);
	displayed_hint.setPosition(10,10);
	displayed_hint.setColor(RED);
	displayed_lives.setPosition(800 - ltextrect.width,10);
	displayed_word.setOrigin(textRect.left + textRect.width/2, textRect.top + textRect.height/2);
	displayed_word.setPosition(WIDTH/2, HEIGHT/2 -100 );
	displayed_word.setColor(WHITE);
	displayed_letter.setColor(WHITE);
	displayed_letter.setPosition(WIDTH/2, HEIGHT/2 + 100);

	// * main loop *
	while(window.isOpen()){
		/*if(playbutton.contains(mouseposx,mouseposy)){
			//cout << "da";
			play.setColor(RED);
		}*/
		Event event;
		while(window.pollEvent(event)){
			if (event.type == Event::Closed)
			   window.close();
			else if(event.type == Event::KeyPressed){
			   key_code = event.key.code;
			   displayed_letter.setString(corresponding(key_code));
			   displayed_word.setString(draw(output,length,corresponding(key_code),my_word));
			   LIVES = checkLives(corresponding(key_code),my_word,LIVES);
			   string newlives = "Remaining lives: " + to_string(LIVES);
			   displayed_lives.setString(newlives);
			   bool end = gameEnd(output, length, LIVES, my_word);
			   if(end == true){
				   running = false;
			   }
			}

		}

		window.clear(BLACK);
		//window.draw(play);
		window.draw(displayed_hint);
		window.draw(displayed_lives);
		window.draw(displayed_word);
		window.draw(displayed_letter);
		window.display();

	}

	return 0;
}

// * Functions *
string hint(string word, string words[][10]){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j <= 10; j++){
			if(word == words[0][j]){
				return "HINT: *** It's a brand! *** \n";
			}
			else if(word == words[1][j]){
				return "HINT: *** It's a food! *** \n";
			}
			else if(word == words[2][j]){
				return "HINT: *** It's a job! *** \n";
			}
			else if(word == words[3][j]){
				return "HINT: *** It's a sport! *** \n";
			}
			else if(word == words[4][j]){
				return "HINT: *** It's an action! *** \n";
			}
		}
	}
	return "";
}

char corresponding(int code){
	char letter = ' ';
	 char alphabet[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	 for(int i = 0; i < 26; i++){
		 if(code == i){
			letter = alphabet[i];
		 }
	}
	 return letter;
}

void fillEmpty(char array[], int length){
	for(int i = 0; i < length; i++){
		array[i] = '_';
	}
}

string draw(char array[], int length, char letter, string word){
	int i;
	for(i = 0; i < length; i++){
			if(word[i] == letter){
				if(array[i] != word[i]){
					array[i] = letter;
				}
			}
		//cout << array[i] << " ";
	}
	//cout << "\n\n";
	array[i] = '\0';
	string hidden = array;
	return hidden;
}

int checkLives(char letter, string word, int lives){
	int showup = 0;
	for(unsigned int i = 0; i < word.length(); i++){
		if(word[i] == letter){
			showup++;
		}
	}
	if(showup == 0){
		lives--;
	}
	if(lives < 0){
		lives = 0;
	}
	//cout << "Remaining lives: " << lives << "\n";
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
