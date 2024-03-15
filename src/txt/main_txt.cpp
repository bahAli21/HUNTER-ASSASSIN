#include "winTxt.h"
#include "gameTxt.h"
int main(int argc, char **argv)
{
	termClear();
	Game game(5);
    txtRun(game);
	termClear();
	return 0;
}
