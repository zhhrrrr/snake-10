#include"BGM.h"
#include<Windows.h>

void BGMgamestart() {
	mciSendString("close BGMgamemenu ", NULL, 0, NULL);
	mciSendString("open gamestart.mp3 alias BGMgamestart", NULL, 0, NULL);
	mciSendString("play BGMgamestart repeat", NULL, 0, NULL);
}

void BGMgameover() {
	mciSendString("close BGMgamestart ", NULL, 0, NULL);
	mciSendString("open gameover.aiff alias BGMgameover", NULL, 0, NULL);
	mciSendString("play BGMgameover repeat", NULL, 0, NULL);
}

void BGMmenu() {
	mciSendString("close BGMgameover", NULL, 0, NULL);
	mciSendString("open gamemenu.mp3 alias BGMgamemenu", NULL, 0, NULL);
	mciSendString("play BGMgamemenu repeat", NULL, 0, NULL);
}

extern void BGMVictory() {
	mciSendString("close BGMgamestart ", NULL, 0, NULL);
	mciSendString("open gamevictory.mp3 alias BGMgamevictory", NULL, 0, NULL);
	mciSendString("play BGMgamevictory repeat", NULL, 0, NULL);
}