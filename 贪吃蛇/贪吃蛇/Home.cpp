#include<graphics.h>
#include<time.h>
#include"BGM.h"

void Home(){
	Sleep(100);
	BGMmenu();
	initgraph(480, 360);
	ExMessage msg;
	peekmessage(&msg, EM_MOUSE);
	while (msg.message != WM_LBUTTONDOWN) {
		IMAGE gamebegin;
		loadimage(&gamebegin, "gamebegin.png", 480, 360);
		putimage(0, 0, &gamebegin);
		peekmessage(&msg, EM_MOUSE);
	}
	srand(time(NULL));
}



	