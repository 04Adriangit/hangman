/*
 * mainmenu.cpp
 *
 *  Created on: 21.04.2024
 *      Author: swt
 */

#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


	class mainmenu{

	private:
		int width = 0;
		int height = 0;
		Color color;
		Font font;
		Text play;

		mainmenu(int width, int height, Color color){
			if(!font.loadFromFile("ArialCE.ttf")){

			}
			this->width = width;
			this->height = height;
			this->color = color;
		}

	public:
		int drawScreen(RenderWindow &wd){
			return 0;
		}
	};



