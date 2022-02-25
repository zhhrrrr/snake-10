
//自带库
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<mmsystem.h>
#include<conio.h>
#include<time.h>
//定义库
#include"BGM.h"
#include"Home.h"

#pragma comment(lib,"winmm.lib")

#define SIZE 10
#define NUM 100000
enum { up = 72, down = 80, left = 75, right = 77 };
struct Coord {
	int x;
	int y;
};

struct Snake {
	int stanzas;
	int ch;
	Coord szb[NUM];
	bool deathflag;
	bool tie;
};

Snake snake[6];

struct Food
{
	int x;
	int y;
	bool iseat;
};

Food food[10];

int speed;
int singlemodechange=-1;
int rankingchange;
int score;
char num[7] = {0};
char Score[1536][7]={"000000"};
DWORD t1=0,t2=0;
int nt=1;
int ntt = 0;

//分数系统
void DrawScore() {
	score = snake[0].stanzas * 100;
	for(int i = 5; i>=0; i--) {
		num[i]= '0'+score % 10;
		score = score / 10;
	}
	for (int i = 0; i < 6; i++) {
		switch (num[i]) {
		case '0': {
			IMAGE num0;
			loadimage(&num0, "0.png", 40, 40);
			putimage(240 + i * 40, 325, &num0);
			break;
		}
		case '1': {
			IMAGE num1;
			loadimage(&num1, "1.png", 40, 40);
			putimage(240 + i * 40, 325, &num1);
			break;
		}
		case '2': {
			IMAGE num2;
			loadimage(&num2, "2.png", 40, 40);
			putimage(240 + i * 40, 325, &num2);
			break;
		}
		case '3': {

			IMAGE num3;
			loadimage(&num3, "3.png", 40, 40);
			putimage(240 + i * 40, 325, &num3);
			break;
		}
		case '4': {
			IMAGE num4;
			loadimage(&num4, "4.png", 40, 40);
			putimage(240 + i * 40, 325, &num4);
			break;
		}
		case '5': {
			IMAGE num5;
			loadimage(&num5, "5.png", 40, 40);
			putimage(240 + i * 40, 325, &num5);
			break;
		}
		case '6': {
			IMAGE num6;
			loadimage(&num6, "6.png", 40, 40);
			putimage(240 + i * 40, 325, &num6);
			break;
		}
		case '7': {
			IMAGE num7;
			loadimage(&num7, "7.png", 40, 40);
			putimage(240 + i * 40, 325, &num7);
			break;
		}
		case '8': {
			IMAGE num8;
			loadimage(&num8, "8.png", 40, 40);
			putimage(240 + i * 40, 325, &num8);
			break;
		}
		case '9': {
			IMAGE num9;
			loadimage(&num9, "9.png", 40, 40);
			putimage(240 + i * 40, 325, &num9);
			break;
		}
		}
	}
	num[6] = '\0';//不为'\'XXX
}

void MemorizeScore() {
	FILE* fp = NULL;
	char numcompare[7];
	int repeat = 1;
	if (singlemodechange == 0) {
		fp = fopen("D:\\vs2022\\贪吃蛇\\贪吃蛇\\easyscorememory.txt", "a+");//读取追加都可以实现
		while (fgets(numcompare,7,fp) != NULL) {
			repeat = strcmp(numcompare,num);
			if (repeat==0) break;
		}
		if (repeat == -1 || repeat == 1) {
			fprintf(fp, "%s", num);
		}
		fclose(fp);
	}
	

	else if (singlemodechange == 1) {
		fp = fopen("D:\\vs2022\\贪吃蛇\\贪吃蛇\\normalscorememory.txt", "a+");//读取追加都可以实现
		while (fgets(numcompare, 7, fp) != NULL) {
			repeat = strcmp(numcompare, num);
			if (repeat == 0) break;
		}
		if (repeat == -1 || repeat == 1) {
			fprintf(fp, "%s", num);
		}
		fclose(fp);
	}

	else if (singlemodechange == 2) {
		fp = fopen("D:\\vs2022\\贪吃蛇\\贪吃蛇\\difficultscorememory.txt", "a+");//读取追加都可以实现
		while (fgets(numcompare, 7, fp) != NULL) {
			repeat = strcmp(numcompare, num);
			if (repeat == 0) break;
		}
		if (repeat == -1 || repeat == 1) {
			fprintf(fp, "%s", num);
		}
		fclose(fp);
	}
	
}
void BMemorizeScore() {
	FILE* fp = NULL;
	char numcompare[7];
	int repeat = 1;
	if(rankingchange == 3) {
	fp = fopen("D:\\vs2022\\贪吃蛇\\贪吃蛇\\brawlmemory.txt", "a+");//读取追加都可以实现
	while (fgets(numcompare, 7, fp) != NULL) {
		repeat = strcmp(numcompare, num);
		if (repeat == 0) break;
	}
	if (repeat == -1 || repeat == 1) {
		fprintf(fp, "%s", num);
	}
	fclose(fp);
	}
}
void sorte() {
	
	FILE* fp;
	int i = 0;
	char temp[7];
	for (int j = 0; j < 7; j++) {
		for (int k = 0; k < 6; k++) {
			Score[j][k] = '0';
		}
	}
	fp = fopen("D:\\vs2022\\贪吃蛇\\贪吃蛇\\easyscorememory.txt", "r");
	while (fgets(Score[i], 7, fp) != NULL) {
		i++;
	}
	fclose(fp);
	for (int j = 0; j < i - 1; j++) {
		for (int k = 0; k < i - j - 1; k++)
		{
			if (strcmp(Score[k], Score[k+1]) == -1)
			{
				strcpy(temp, Score[k]);
				strcpy(Score[k], Score[k + 1]);
				strcpy(Score[k+ 1], temp);
			}
		}
	}
}


void sortn() {
	FILE* fp;
	int i = 0;
	char temp[7];
	for (int j = 0; j < 7; j++) {
		for (int k = 0; k < 6; k++) {
			Score[j][k] = '0';
		}
	}
	fp = fopen("D:\\vs2022\\贪吃蛇\\贪吃蛇\\normalscorememory.txt", "r");
	while (fgets(Score[i], 7, fp) != NULL) {
		i++;
	}
	fclose(fp);
	for (int j = 0; j < i - 1; j++) {
		for (int k = 0; k < i - j - 1; k++)
		{
			if (strcmp(Score[k], Score[k + 1]) == -1)
			{
				strcpy(temp, Score[k]);
				strcpy(Score[k], Score[k + 1]);
				strcpy(Score[k + 1], temp);
			}
		}
	}
}

void sortd() {

	FILE* fp;
	int i = 0;
	char temp[7];
	for (int j = 0; j < 7; j++) {
		for (int k = 0; k < 6; k++) {
			Score[j][k] = '0';
		}
	}
	fp = fopen("D:\\vs2022\\贪吃蛇\\贪吃蛇\\difficultscorememory.txt", "r");
	while (fgets(Score[i], 7, fp) != NULL) {
		i++;
	}
	fclose(fp);
	for (int j = 0; j < i - 1; j++) {
		for (int k = 0; k < i - j - 1; k++)
		{
			if (strcmp(Score[k], Score[k + 1]) == -1)
			{
				strcpy(temp, Score[k]);
				strcpy(Score[k], Score[k + 1]);
				strcpy(Score[k + 1], temp);
			}
		}
	}
}

void sortb() {
	FILE* fp;
	int i = 0;
	char temp[7];
	for (int j = 0; j < 7; j++) {
		for (int k = 0; k < 6; k++) {
			Score[j][k] = '0';
		}
	}
	fp = fopen("D:\\vs2022\\贪吃蛇\\贪吃蛇\\brawlmemory.txt", "r");
	while (fgets(Score[i], 7, fp) != NULL) {
		i++;
	}
	fclose(fp);
	for (int j = 0; j < i - 1; j++) {
		for (int k = 0; k < i - j - 1; k++)
		{
			if (strcmp(Score[k], Score[k + 1]) == -1)
			{
				strcpy(temp, Score[k]);
				strcpy(Score[k], Score[k + 1]);
				strcpy(Score[k + 1], temp);
			}
		}
	}
}

void putnumber() {
	for (int j = 0; j < 7; j++) {
		for (int k = 0; k < 6; k++) {
			switch (Score[j][k]) {
			case '0': {
				IMAGE num0;
				loadimage(&num0, "0.png", 30, 30);
				putimage(100 + k * 30, 100 + j * 30, &num0);
				break;
			}
			case '1': {
				IMAGE num1;
				loadimage(&num1, "1.png", 30, 30);
				putimage(100 + k * 30, 100 + j * 30, &num1);
				break;
			}
			case '2': {
				IMAGE num2;
				loadimage(&num2, "2.png", 30, 30);
				putimage(100 + k * 30, 100 + j * 30, &num2);
				break;
			}
			case '3': {

				IMAGE num3;
				loadimage(&num3, "3.png", 30, 30);
				putimage(100 + k * 30, 100 + j * 30, &num3);
				break;
			}
			case '4': {
				IMAGE num4;
				loadimage(&num4, "4.png", 30, 30);
				putimage(100 + k * 30, 100 + j * 30, &num4);
				break;
			}
			case '5': {
				IMAGE num5;
				loadimage(&num5, "5.png", 30, 30);
				putimage(100 + k * 30, 100 + j * 30, &num5);
				break;
			}
			case '6': {
				IMAGE num6;
				loadimage(&num6, "6.png", 30, 30);
				putimage(100 + k * 30, 100 + j * 30, &num6);
				break;
			}
			case '7': {
				IMAGE num7;
				loadimage(&num7, "7.png", 30, 30);
				putimage(100 + k * 30, 100 + j * 30, &num7);
				break;
			}
			case '8': {
				IMAGE num8;
				loadimage(&num8, "8.png", 30, 30);
				putimage(100 + k * 30, 100 + j * 30, &num8);
				break;
			}
			case '9': {
				IMAGE num9;
				loadimage(&num9, "9.png", 30, 30);
				putimage(100 + k * 30, 100 + j * 30, &num9);
				break;
			}
			}
		}
	}
}

void rankinge() {

	IMAGE rankinge;
	loadimage(&rankinge,"rankinge.png", 480, 360);
	putimage(0, 0, &rankinge);
}

void rankingn() {
	
	IMAGE rankingn;
	loadimage(&rankingn, "rankingn.png", 480, 360);
	putimage(0, 0, &rankingn);
}

void rankingd() {
	
	IMAGE rankingd;
	loadimage(&rankingd, "rankingd.png", 480, 360);
	putimage(0, 0, &rankingd);
}

void rankingb() {
	IMAGE rankb;
	loadimage(&rankb, "rankingb.png", 480, 360);
	putimage(0, 0, &rankb);
	
}

//单人模式
void GameInit() {
	initgraph(480, 360);
	setbkcolor(RGB(250, 155, 204));
	setbkmode(TRANSPARENT);
	cleardevice();

	snake[0].stanzas = 3;
	snake[0].ch = right;
	snake[0].szb[0].x = 100;
	snake[0].szb[0].y = 100;
	snake[0].szb[1].x = 90;
	snake[0].szb[1].y = 100;
	snake[0].szb[2].x = 80;
	snake[0].szb[2].y = 100;
	snake[0].deathflag = false;

	food[0].iseat = false;
}

void Draw() {
	cleardevice();
	BeginBatchDraw();
	setfillcolor(RGB(236, 19, 69));
	setlinecolor(RGB(236, 19, 69));
	fillrectangle(food[0].x, food[0].y, food[0].x + SIZE, food[0].y + SIZE);
	
	setfillcolor(RGB(214, 223, 235));
	setlinecolor(RGB(0, 108, 190));
	for (int i = 1; i < snake[0].stanzas; i++) {
		fillrectangle(snake[0].szb[i].x, snake[0].szb[i].y, snake[0].szb[i].x + SIZE, snake[0] .szb[i].y + SIZE);
	}

	setfillcolor(RGB(0, 47, 167));
	setlinecolor(RGB(0, 47, 167));
	fillrectangle(snake[0].szb[0].x, snake[0].szb[0].y, snake[0].szb[0].x + SIZE, snake[0].szb[0].y + SIZE);
	for (int i = 0; i < 480; i += 10) {
		fillrectangle(i, 0, i + SIZE, 10);
		fillrectangle(i, 310, i + SIZE, 320);
		}
	for (int i = 0; i < 320; i += 10) {
		fillrectangle(0, i,10, i+SIZE);
		fillrectangle(470,i,480, i+SIZE);
	}
	IMAGE score;
	loadimage(&score, "score.png", 80, 40);
	putimage(0, 325, &score);
	if (singlemodechange == 0) {
		IMAGE easy;
		loadimage(&score, "easy.png", 80, 40);
		putimage(160, 325, &score);
		}
	if (singlemodechange == 1) {
			IMAGE normal;
			loadimage(&normal, "normal.png", 80, 40);
			putimage(160, 325, &normal);
		}
	if (singlemodechange == 2) {
		IMAGE difficult;
		loadimage(&difficult, "difficult.png", 80, 40);
		putimage(160, 325, &difficult);
	}
	DrawScore();
	EndBatchDraw();
}


void SnakeMove() {
	//先将蛇的前一节给后一节
	for (int i = snake[0].stanzas - 1; i > 0; i--) {
		snake[0].szb[i].x = snake[0].szb[i - 1].x;
		snake[0] .szb[i].y = snake[0].szb[i - 1].y;
	}
	switch (snake[0].ch)
	{
	case up:
		snake[0].szb[0].y -= SIZE;
		break;
	case down:
		snake[0].szb[0].y += SIZE;
		break;
	case left:
		snake[0].szb[0].x -= SIZE;
		break;
	case right:
		snake[0].szb[0].x += SIZE;
		break;
	}
}

void ChangeCh() {
	if (_kbhit()) {
		char key = _getch();
		switch (key) {
		case up:
			if (snake[0].ch != down) snake[0].ch = up;
			break;
		case down:
			if (snake[0].ch != up) snake[0].ch = down;
			break;
		case left:
			if (snake[0].ch != right) snake[0].ch = left;
		case right:
			if (snake[0].ch != left) snake[0].ch = right;
			break;
		case 'w':
		case 'W':
			if (snake[1].ch != down) snake[1].ch = up;
			break;
		case 's':
		case 'S':
			if (snake[1].ch != up) snake[1].ch = down;
			break;
		case 'a':
		case 'A':
			if (snake[1].ch != right) snake[1].ch = left;
		case 'd':
		case 'D':
			if (snake[1].ch != left) snake[1].ch = right;
			break;
		}
	}
}

void FoodCreate() {
	food[0].x = rand() % 46 * 10 + 10;
	food[0].y = rand() % 30 * 10 + 10;
	food[0].iseat = false;
}


void Blood(){
	setlinecolor(RED);
	setfillcolor(RED);
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 16; j++) {
			fillrectangle(i * 20, j * 20, i * 20 + 20, j * 20 + 20);
			Sleep(2);
		}
	}
}




//双人模式
void GameInit2() {
	initgraph(480, 320);
	setbkcolor(RGB(250, 155, 204));
	setbkmode(TRANSPARENT);
	cleardevice();

	snake[0].stanzas = 3;
	snake[0].ch = right;
	snake[0].szb[0].x = 100;
	snake[0].szb[0].y = 100;
	snake[0].szb[1].x = 90;
	snake[0].szb[1].y = 100;
	snake[0].szb[2].x = 80;
	snake[0].szb[2].y = 100;
	snake[0].deathflag = false;
	snake[0].tie = false;
	
	snake[1].stanzas = 3;
	snake[1].ch =left;
	snake[1].szb[0].x = 380;
	snake[1].szb[0].y = 220;
	snake[1].szb[1].x = 390;
	snake[1].szb[1].y =220;
	snake[1].szb[2].x = 400;
	snake[1].szb[2].y = 220;
	snake[1].deathflag = false;
	snake[1].tie = false;

	food[0].iseat = false; 
	food[1].iseat = false;

}

void Draw2() {
	cleardevice();
	BeginBatchDraw();
	setfillcolor(RGB(255, 128, 0));
	setlinecolor(RGB(255, 128, 0));
	fillrectangle(food[0].x, food[0].y, food[0].x + SIZE, food[0].y + SIZE);

	setfillcolor(RGB(255, 128, 0));
	setlinecolor(RGB(255, 128, 0));
	fillrectangle(food[1].x, food[1].y, food[1].x + SIZE, food[1].y + SIZE);

	setfillcolor(RGB(214, 223, 235));
	setlinecolor(RGB(0, 108, 190));
	for (int i = 1; i < snake[0].stanzas; i++) {
		fillrectangle(snake[0].szb[i].x, snake[0].szb[i].y, snake[0].szb[i].x + SIZE, snake[0].szb[i].y + SIZE);
	}

	setfillcolor(RGB(255, 132, 25));
	setlinecolor(RGB(255, 43, 103));
	for (int i = 1; i < snake[1].stanzas; i++) {
		fillrectangle(snake[1].szb[i].x, snake[1].szb[i].y, snake[1].szb[i].x + SIZE, snake[1].szb[i].y + SIZE);
	}

	//第一半墙
	setfillcolor(RGB(0, 47, 167));
	setlinecolor(RGB(0, 47, 167));
	fillrectangle(snake[0].szb[0].x, snake[0].szb[0].y, snake[0].szb[0].x + SIZE, snake[0].szb[0].y + SIZE);//第一条蛇头
	for (int i = 0; i < 240; i += 10) {
		fillrectangle(i, 0, i + SIZE, 10);
		fillrectangle(i, 310, i + SIZE, 320);
	}
	for (int i = 0; i < 320; i += 10) {
		fillrectangle(0, i, 10, i + SIZE);
	}
	//第二半墙
	setfillcolor(RGB(232, 16, 16));
	setlinecolor(RGB(232, 16, 16));
	fillrectangle(snake[1].szb[0].x, snake[1].szb[0].y, snake[1].szb[0].x + SIZE, snake[1].szb[0].y + SIZE);//第二条蛇头
	for (int i = 240; i < 480; i += 10) {
		fillrectangle(i, 0, i + SIZE, 10);
		fillrectangle(i, 310, i + SIZE, 320);
	}
	for (int i = 0; i < 320; i += 10) {
		fillrectangle(470, i, 480, i + SIZE);
	}
	EndBatchDraw();
}


void FoodCreate2() {
	food[1].x = rand() % 46 * 10 + 10;
	food[1].y = rand() % 30 * 10 + 10;
	food[1].iseat = false;
}

void SnakeMove2() {
	//先将蛇的前一节给后一节
	for (int i = snake[1].stanzas - 1; i > 0; i--) {
		snake[1].szb[i].x = snake[1].szb[i - 1].x;
		snake[1].szb[i].y = snake[1].szb[i - 1].y;
	}
	switch (snake[1].ch)
	{
	case up:
		snake[1].szb[0].y -= SIZE;
		break;
	case down:
		snake[1].szb[0].y += SIZE;
		break;
	case left:
		snake[1].szb[0].x -= SIZE;
		break;
	case right:
		snake[1].szb[0].x += SIZE;
		break;
	}
}

//Brawl Mode
void GameInit3() {
	initgraph(480, 360);
	setbkcolor(RGB(250, 155, 204));
	setbkmode(TRANSPARENT);
	cleardevice();

	snake[0].stanzas = 3;
	snake[0].ch = right;
	snake[0].szb[0].x = 100;
	snake[0].szb[0].y = 100;
	snake[0].szb[1].x = 90;
	snake[0].szb[1].y = 100;
	snake[0].szb[2].x = 80;
	snake[0].szb[2].y = 100;
	snake[0].deathflag = false;

	snake[1].stanzas = 3;
	snake[1].ch = left;
	snake[1].szb[0].x = 380;
	snake[1].szb[0].y = 220;
	snake[1].szb[1].x = 390;
	snake[1].szb[1].y = 220;
	snake[1].szb[2].x = 400;
	snake[1].szb[2].y = 220;

	snake[2].stanzas = 3;
	snake[2].ch = down;
	snake[2].szb[0].x = 400;
	snake[2].szb[0].y = 120;
	snake[2].szb[1].x = 400;
	snake[2].szb[1].y = 110;
	snake[2].szb[2].x = 400;
	snake[2].szb[2].y = 100;

	snake[3].stanzas = 3;
	snake[3].ch = up;
	snake[3].szb[0].x = 80;
	snake[3].szb[0].y = 220;
	snake[3].szb[1].x = 80;
	snake[3].szb[1].y = 210;
	snake[3].szb[2].x = 80;
	snake[3].szb[2].y = 200;


	food[0].iseat = false;
	food[1].iseat = false;
}

void Draw3() {
	cleardevice();
	BeginBatchDraw();
	setfillcolor(RGB(16, 186, 115));
	setlinecolor(RGB(16, 186, 115));
	fillrectangle(food[0].x, food[0].y, food[0].x + SIZE, food[0].y + SIZE);

	setfillcolor(RGB(16, 186, 115));
	setlinecolor(RGB(16, 186, 115));
	fillrectangle(food[1].x, food[1].y, food[1].x + SIZE, food[1].y + SIZE);

	setfillcolor(RGB(214, 223, 235));
	setlinecolor(RGB(0, 108, 190));
	for (int i = 1; i < snake[0].stanzas; i++) {
		fillrectangle(snake[0].szb[i].x, snake[0].szb[i].y, snake[0].szb[i].x + SIZE, snake[0].szb[i].y + SIZE);
	}

	setfillcolor(RGB(0, 47, 167));
	setlinecolor(RGB(0, 47, 167));
	fillrectangle(snake[0].szb[0].x, snake[0].szb[0].y, snake[0].szb[0].x + SIZE, snake[0].szb[0].y + SIZE);//第一条蛇头
	 
	setfillcolor(RGB(0, 0, 0));
	setlinecolor(RGB(0, 0, 0));
	for (int i = 0; i < 480; i += 10) {
		fillrectangle(i, 0, i + SIZE, 10);
		fillrectangle(i, 310, i + SIZE, 320);
	}
	for (int i = 0; i < 320; i += 10) {
		fillrectangle(0, i, 10, i + SIZE);
		fillrectangle(470, i, 480, i + SIZE);
	}

	setfillcolor(RGB(134, 95, 197));
	setlinecolor(RGB(204, 150, 249));
	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < snake[i].stanzas; j++) {
			fillrectangle(snake[i].szb[j].x, snake[i].szb[j].y, snake[i].szb[j].x + SIZE, snake[i].szb[j].y + SIZE);
		}
	}
	IMAGE score;
	loadimage(&score, "score.png", 80, 40);
	putimage(0, 325, &score);
	IMAGE brawl;
	loadimage(&brawl, "brawl.png", 80, 40);
	putimage(160, 325, &brawl);
	DrawScore();
	EndBatchDraw();
}

void SnakeMove3() {
	//先将蛇的前一节给后一节
	for (int i = snake[2].stanzas - 1; i > 0; i--) {
		snake[2].szb[i].x = snake[2].szb[i - 1].x;
		snake[2].szb[i].y = snake[2].szb[i - 1].y;
	}
	switch (snake[2].ch)
	{
	case up:
		snake[2].szb[0].y -= SIZE;
		break;
	case down:
		snake[2].szb[0].y += SIZE;
		break;
	case left:
		snake[2].szb[0].x -= SIZE;
		break;
	case right:
		snake[2].szb[0].x += SIZE;
		break;
	}
	//避障
}
void SnakeMove4() {
	//先将蛇的前一节给后一节
	for (int i = snake[3].stanzas - 1; i > 0; i--) {
		snake[3].szb[i].x = snake[3].szb[i - 1].x;
		snake[3].szb[i].y = snake[3].szb[i - 1].y;
	}
	switch (snake[3].ch)
	{
	case up:
		snake[3].szb[0].y -= SIZE;
		break;
	case down:
		snake[3].szb[0].y += SIZE;
		break;
	case left:
		snake[3].szb[0].x -= SIZE;
		break;
	case right:
		snake[3].szb[0].x += SIZE;
		break;
	}

}

void avoid() {
	int i = 0;
	i = rand() % 2+ 1;
	for (int j = 1; j < 4; j++) {
		if (snake[j].szb[0].y == 10 && snake[j].ch == up) {
			if (i == 1)snake[j].ch = left;
			if (i == 2)snake[j].ch = right;
		}
		if (snake[j].szb[0].y == 300 && snake[j].ch == down) {
			if (i == 1)snake[j].ch = left;
			if (i == 2)snake[j].ch = right;
		}
		if (snake[j].szb[0].x == 10 && snake[j].ch == left) {
			if (i == 1)snake[j].ch = up;
			if (i == 2)snake[j].ch = down;
		}
		if (snake[j].szb[0].x == 460 && snake[j].ch == right) {
			if (i == 1)snake[j].ch = up;
			if (i == 2)snake[j].ch = down;
		}
		if (snake[j].szb[0].x == 10 && snake[j].szb[0].y == 10 && snake[j].ch == up) snake[j].ch = right;
		if (snake[j].szb[0].x == 10 && snake[j].szb[0].y == 10 && snake[j].ch == left) snake[j].ch = down;
		if (snake[j].szb[0].x == 460 && snake[j].szb[0].y == 10 && snake[j].ch == up) snake[j].ch = left;
		if (snake[j].szb[0].x == 460 && snake[j].szb[0].y == 10 && snake[j].ch == right) snake[j].ch = down;
		if (snake[j].szb[0].x == 10 && snake[j].szb[0].y == 300 && snake[j].ch == down) snake[j].ch = right;
		if (snake[j].szb[0].x == 10 && snake[j].szb[0].y == 300 && snake[j].ch == left) snake[j].ch = up;
		if (snake[j].szb[0].x == 460 && snake[j].szb[0].y == 300 && snake[j].ch == down) snake[j].ch = left;
		if (snake[j].szb[0].x == 460 && snake[j].szb[0].y == 300 && snake[j].ch == right) snake[j].ch = up;
	}
}

void turn() {
	for (int j = 1; j < 4; j++) {
		if (snake[j].szb[0].y == 10 && snake[j].ch != up)
			snake[j].ch = down;
		if (snake[j].szb[0].y == 300 && snake[j].ch != down)
			snake[j].ch = up;
		if (snake[j].szb[0].x == 10 && snake[j].ch != left)
			snake[j].ch = left;
		if (snake[j].szb[0].y == 460 && snake[j].ch != right)
			snake[j].ch = right;
	}

}

void randommove() {
	int i = 0;
	for (int j = 1; j < 4; j++) {
		i = rand() % 4 + 1;
		if (i == 1)snake[j].ch = left;
		if (i == 2)snake[j].ch = right;
		if (i == 3)snake[j].ch = up;
		if (i == 4)snake[j].ch = down;
	}
}
//Others
void IsEat() {
	int index = 0;
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 2; j++) {
			if (snake[i].szb[0].x == food[j].x && snake[i].szb[0].y == food[j].y) index = 1;
			if (index) goto SnakeGrow;
		}
	}
SnakeGrow:
	if (index) {
		snake[i].stanzas++;
		food[j].iseat = true;
	}
	for (i = 0; i < 4; i++) {
		j = snake[i].stanzas;
		switch (snake[i].ch) {
		case left:
			snake[i].szb[j].x = snake[i].szb[j-1].x ;
			snake[i].szb[j].y = snake[i].szb[j-1].y;
			break;
		case right:
			snake[i].szb[j].x = snake[i].szb[j-1].x ;
			snake[i].szb[j].y = snake[i].szb[j-1].y;
			break;
		case up:
			snake[i].szb[j].x = snake[i].szb[j-1].x;
			snake[i].szb[j].y = snake[i].szb[j-1].y;
			break;
		case down:
			snake[i].szb[j].x = snake[i].szb[j-1].x;
			snake[i].szb[j].y = snake[i].szb[j-1].y;
			break;
		}
	}
}

void Die() {
	//撞墙
	for (int i = 0; i < 4; i++) {
		if (snake[i].szb[0].x == 0 || snake[i].szb[0].x == 470 || snake[i].szb[0].y == 310 || snake[i].szb[0].y == 0) {
			snake[i].deathflag = true;
		}
	}
	for (int i = 0; i < 2; i++) {//head
		for (int j = 0; j < 2; j++) {//body
			for (int k = 1; k < snake[j].stanzas; k++) {//stanzas
				if (snake[i].szb[0].x == snake[j].szb[k].x && snake[i].szb[0].y == snake[j].szb[k].y) {
					snake[i].deathflag = true;
				}
			}
		}
	}
}

void Tie() {
	if(snake[0].szb[0].x == snake[1].szb[0].x && snake[0].szb[0].y == snake[1].szb[0].y){
		snake[0].tie = true;
		snake[1].tie = true;
	}
}

void corrode() {
	//撞墙
	for (int i = 0; i < 4; i++) {
		if (snake[i].szb[0].x == 0 || snake[i].szb[0].x == 470 || snake[i].szb[0].y == 310 || snake[i].szb[0].y == 0) {
			snake[i].deathflag = true;
		}
		//head
		for (int j = 0; j < 4; j++) {//body
			for (int k = 1; k < snake[j].stanzas; k++) {//stanzas
				if (snake[0].szb[0].x == snake[j].szb[k].x && snake[0].szb[0].y == snake[j].szb[k].y) {
					snake[0].deathflag = true;
				}
			}
		}
	}
}

void BrawlScore() {//顺序不能错
	sortb();
	BeginBatchDraw();
	rankingb();
	setfillcolor(RGB(250, 155, 204));
	setlinecolor(RGB(250, 155, 204));
	fillrectangle(440, 0, 480, 40);
	IMAGE n1;
	loadimage(&n1, "n1.png", 30, 30);
	putimage(10, 100, &n1);
	IMAGE n2;
	loadimage(&n2, "n2.png", 30, 30);
	putimage(10, 130, &n2);
	IMAGE n3;
	loadimage(&n3, "n3.png", 30, 30);
	putimage(10, 160, &n3);
	IMAGE n4;
	loadimage(&n4, "n4.png", 30, 30);
	putimage(10, 190, &n4);
	IMAGE n5;
	loadimage(&n5, "n5.png", 30, 30);
	putimage(10, 220, &n5);
	IMAGE n6;
	loadimage(&n6, "n6.png", 30, 30);
	putimage(10, 250, &n6);
	IMAGE n7;
	loadimage(&n7, "n7.png", 30, 30);
	putimage(10, 280, &n7);
	putnumber();
	EndBatchDraw();
	Sleep(3000);

	setlinecolor(RGB(112, 48, 160));
	setfillcolor(RGB(112, 48, 160));
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 18; j++) {
			fillrectangle(i * 20, j * 20, i * 20 + 20, j * 20 + 20);
			Sleep(2);
		}
	}
}

int main() {
Home:
	Home();
Mode:
	//变量归零
	rankingchange = 0;
	//mode menu
	BGMmenu();
	Sleep(100);//利用延时解决卡屏问题
	while (1) {
		IMAGE mode0;
		loadimage(&mode0, "mode0.png", 480, 360);
		putimage(0, 0, &mode0);//分支
		ExMessage msg;
		peekmessage(&msg, EM_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x >= 0 && msg.x <= 40 && msg.y >= 0 && msg.y <= 40) goto Home;
			else if (msg.x >= 140 && msg.x <= 340 && msg.y >= 20 && msg.y <= 90) {
				IMAGE mode1;
				loadimage(&mode1, "mode1.png", 480, 360);
				putimage(0, 0, &mode1);
				Sleep(100);
				goto SingleMenu;
			}
			else if (msg.x >= 140 && msg.x <= 340 && msg.y >= 110 && msg.y <= 180) {
				IMAGE mode2;
				loadimage(&mode2, "mode2.png", 480, 360);
				putimage(0, 0, &mode2);
				Sleep(100);
				goto TwoplayersBegin;
			}
			else if (msg.x >= 140 && msg.x <= 340 && msg.y >= 200 && msg.y <= 290) {
				IMAGE mode3;
				loadimage(&mode3, "mode3.png", 480, 360);
				putimage(0, 0, &mode3);
				Sleep(100);
				rankingchange = 3;
				goto BrawlBegin;
			}
		}
	}


	//single menu
SingleMenu:
	Sleep(100);
	while (1) {
		IMAGE single0;
		loadimage(&single0, "single0.png", 480, 360);
		putimage(0, 0, &single0);//分支
		ExMessage msg;
		peekmessage(&msg, EM_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x >= 440 && msg.x <= 480 && msg.y >= 0 && msg.y <= 40) goto Mode;
			else if (msg.x >= 0 && msg.x <= 40 && msg.y >= 320 && msg.y <= 360) goto Ranking;
			else if (msg.x >= 140 && msg.x <= 340 && msg.y >= 20 && msg.y <= 90) {
				IMAGE single1;
				loadimage(&single1, "single1.png", 480, 360);
				putimage(0, 0, &single1);
				Sleep(100);
				speed = 100;
				singlemodechange = 0;
				goto SingleBegin;
			}
			else if (msg.x >= 140 && msg.x <= 340 && msg.y >= 110 && msg.y <= 180) {
				IMAGE single2;
				loadimage(&single2, "single2.png", 480, 360);
				putimage(0, 0, &single2);
				Sleep(100);
				speed = 50;
				singlemodechange = 1;
				goto SingleBegin;
			}
			else if (msg.x >= 140 && msg.x <= 340 && msg.y >= 200 && msg.y <= 290) {
				IMAGE single3;
				loadimage(&single3, "single3.png", 480, 360);
				putimage(0, 0, &single3);
				Sleep(100);
				speed = 30;
				singlemodechange = 2;
				goto SingleBegin;
			}
		}
	}

Ranking:
	Sleep(100);
	while (1) {
		IMAGE ranking;
		loadimage(&ranking, "ranking.png", 480, 360);
		putimage(0, 0, &ranking);//分支
		ExMessage msg;
		peekmessage(&msg, EM_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x >= 440 && msg.x <= 480 && msg.y >= 0 && msg.y <= 40) goto SingleMenu;
			else if (msg.x >= 140 && msg.x <= 340 && msg.y >= 20 && msg.y <= 90) {
				IMAGE ranking1;
				loadimage(&ranking1, "ranking1.png", 480, 360);
				putimage(0, 0, &ranking1);
				Sleep(100);
				speed = 100;
				rankingchange = 0;
				goto RankingShow;
			}
			else if (msg.x >= 140 && msg.x <= 340 && msg.y >= 110 && msg.y <= 180) {
				IMAGE ranking2;
				loadimage(&ranking2, "ranking2.png", 480, 360);
				putimage(0, 0, &ranking2);
				Sleep(100);
				speed = 50;
				rankingchange = 1;
				goto RankingShow;
			}
			else if (msg.x >= 140 && msg.x <= 340 && msg.y >= 200 && msg.y <= 290) {
				IMAGE ranking3;
				loadimage(&ranking3, "ranking3.png", 480, 360);
				putimage(0, 0, &ranking3);
				Sleep(100);
				speed = 30;
				rankingchange = 2;
				goto RankingShow;
			}
		}

	}

RankingShow:
	if (rankingchange == 0) sorte();
	else if (rankingchange == 1) sortn();
	else if (rankingchange == 2) sortd();
	while (1) {
		BeginBatchDraw();
		if (rankingchange == 0) {
			IMAGE ranke;
			loadimage(&ranke, "rankinge.png", 480, 360);
			putimage(0, 0, &ranke);
		}
		else if (rankingchange == 1) {
			IMAGE rankn;
			loadimage(&rankn, "rankingn.png", 480, 360);
			putimage(0, 0, &rankn);
		}
		else if (rankingchange == 2) {
			IMAGE rankd;
			loadimage(&rankd, "rankingd.png", 480, 360);
			putimage(0, 0, &rankd);
		}
		setfillcolor(RGB(250, 155, 204));
		setlinecolor(RGB(250, 155, 204));
		fillrectangle(440, 0, 480, 40);
		IMAGE n1;
		loadimage(&n1, "n1.png", 30, 30);
		putimage(10, 100, &n1);
		IMAGE n2;
		loadimage(&n2, "n2.png", 30, 30);
		putimage(10, 130, &n2);
		IMAGE n3;
		loadimage(&n3, "n3.png", 30, 30);
		putimage(10, 160, &n3);
		IMAGE n4;
		loadimage(&n4, "n4.png", 30, 30);
		putimage(10, 190, &n4);
		IMAGE n5;
		loadimage(&n5, "n5.png", 30, 30);
		putimage(10, 220, &n5);
		IMAGE n6;
		loadimage(&n6, "n6.png", 30, 30);
		putimage(10, 250, &n6);
		IMAGE n7;
		loadimage(&n7, "n7.png", 30, 30);
		putimage(10, 280, &n7);
		putnumber();

		EndBatchDraw();
		Sleep(5000);
		setlinecolor(RGB(255, 192, 0));
		setfillcolor(RGB(255, 192, 0));
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 18; j++) {
				fillrectangle(i * 20, j * 20, i * 20 + 20, j * 20 + 20);
				Sleep(2);
			}
		}
		goto Ranking;

	}

	//Single Mode
SingleBegin:
	GameInit();
	BGMgamestart();//循环播放support mp3 aiff wav不行
	FoodCreate();
	while (1){
		while (!_kbhit()) {
			Draw();
			DrawScore();
			SnakeMove();
			IsEat();
			if (food[0].iseat == true) {//待优化闪屏
				FoodCreate();
			}
			Sleep(speed);
			Die();
			if (snake[0].deathflag) goto Gameover;//goto语句要不能跳过实例化（局部变量定义），把实例化移到函数开头就可以了
		}
		ChangeCh();
	}


	//Twoplayers Mode
TwoplayersBegin:
	GameInit2();
	BGMgamestart();//循环播放support mp3 aiff
	FoodCreate();
	FoodCreate2();
	while (1) {
		while (!_kbhit()) {
			Draw2();
			SnakeMove();
			SnakeMove2();
			IsEat();
			if (food[0].iseat == true) {
				FoodCreate();
			}
			if (food[1].iseat == true) {
				FoodCreate2();
			}
			Sleep(100);
			if (snake[0].tie && snake[1].tie) goto Tie;
			Die();
			Tie();
			if (snake[1].deathflag) goto Winner1;
			else if (snake[0].deathflag) goto Winner2;

		}
		ChangeCh();
		ChangeCh();
	}


	//获胜方
Winner1:
	BGMVictory();
	while (1) {
		IMAGE win1;
		loadimage(&win1, "win1.png", 480, 320);
		putimage(0, 0, &win1);//分支
		ExMessage msg;
		peekmessage(&msg, EM_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x >= 440 && msg.x <= 480 && msg.y >= 0 && msg.y <= 40) goto Mode;
		}
	}
Winner2:
	BGMVictory();
	while (1) {
		IMAGE win2;
		loadimage(&win2, "win2.png", 480, 320);
		putimage(0, 0, &win2);//分支
		ExMessage msg;
		peekmessage(&msg, EM_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x >= 440 && msg.x <= 480 && msg.y >= 0 && msg.y <= 40) goto Mode;
		}
	}

Tie:
	BGMVictory();
	while (1) {
		IMAGE tie;
		loadimage(&tie, "tie.png", 480, 320);
		putimage(0, 0, &tie);//分支
		ExMessage msg;
		peekmessage(&msg, EM_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x >= 440 && msg.x <= 480 && msg.y >= 0 && msg.y <= 40) goto Mode;
		}
	}
	//Brawl Mode
BrawlBegin:

	BrawlScore();
	GameInit3();
	BGMgamestart();//循环播放support mp3 aiff
	FoodCreate();
	FoodCreate2();
	while (1) {
		while (!_kbhit()) {
		
			Draw3();
			if (ntt % 4 == 0) {
				randommove();
			}
			ntt++;
			turn();
			avoid();
			SnakeMove();
			SnakeMove2();
			SnakeMove3();
			SnakeMove4();
			IsEat();
			if (food[0].iseat == true) {
				FoodCreate();
			}
			if (food[1].iseat == true) {
				FoodCreate2();
			}
			Sleep(100);
			corrode();
			if (snake[0].deathflag) goto Gameover;
			t2 = clock();
			if (t2-t1>(5000*nt)) {
				for (int i = 1; i < 4; i++) {
					snake[i].stanzas++;
				}
				nt++;
			}
		}
			ChangeCh();
	}

//Gameover
	Gameover:
	Blood();
	BGMgameover();
	MemorizeScore();
	BMemorizeScore();
	while (1) {
		IMAGE gameover;
		loadimage(&gameover, "gameover.png", 480, 360);
		putimage(0, 0, &gameover);//分支
		ExMessage msg;
		peekmessage(&msg, EM_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x >= 340 && msg.x <= 460 && msg.y >= 40 && msg.y <= 110) {
				IMAGE gameover1;
				loadimage(&gameover1, "gameover1.png", 480, 360);
			    putimage(0, 0, &gameover1);
				Sleep(100);
				goto Mode;
			}
			else if (msg.x >= 340 && msg.x <= 460 && msg.y >= 160 && msg.y <= 230) {
				IMAGE gameover2;
				loadimage(&gameover2, "gameover2.png", 480, 360);
				putimage(0, 0, &gameover2);
				Sleep(100);
				exit(0);
			}
		}
		singlemodechange = 0;
	}
	getchar();
	return 0;
}
