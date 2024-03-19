#include <iostream>

//#include <windows.h>
#include <unistd.h>

#include "winTxt.h"

#include "../core/Game.h"
#include "../core/Garde.h"

void Display(WinTXT &win, Game &g)
{

	const Map &map = g.getConstMap();
	const Player & player = g.getConstPlayer();
	const Garde *gardes = g.getAllGardes();

	win.clear();

	// Affichage des murs et des portes
	for (int x = 0; x < map.getDimX(); ++x)
		for (int y = 0; y < map.getDimY(); ++y)
			win.print(x, y, map.getObjectChar(x, y));

	// Affichage de l'assassin
	win.print(player.getPosition().x, player.getPosition().y, 'A');

	win.draw();
}

void txtRun(Game &g)
{
	//Je creer une fenetre en mode texte
	WinTXT win(g.getConstMap().getDimX(), g.getConstMap().getDimY());

	bool run = true;
	int chKey;

	do
	{
        sleep(3);
        termClear();
        Display(win, g);



        chKey = win.getCh();
		switch (chKey)
		{
		case 'z': //UP
			g.toucheClavier('z');
			break;
		case 'q': //LEFT
			g.toucheClavier('q');
			break;
		case 's': //DOWN
			g.toucheClavier('s');
			break;
		case 'd': //RIGHT
			g.toucheClavier('d');
			break;
		case 'k': //arreter k comme kill , ahhh les signaux en LIFSE
            run = false;
			break;
		}

	} while (run);
}
