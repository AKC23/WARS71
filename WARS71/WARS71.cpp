/*
	Project Name  : WARS71
	Developed By  : Ahmed Al Wasi, Ahmadul Karim Chowdhury, Aurunave Mollik Ruddro, Md. Shirajus Salekin Shafi
	Course Code   : CSE 1200
	Course Name   : Software Development - I
	YouTube Link  : https://www.youtube.com/watch?v=HUmatUBH9N8&t=13s&ab_channel=AhmadulKarimChowdhury
	Last Updated  : Sunday,September 26,2020
*/

#include "iGraphics.h"
#include <stdio.h>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <cstring>
using namespace std;

int bdtank_x, bdtank_y;
int gamestate=0;

int f1=0;
int f1_x,f1_y;
char story[11][100]={"0.bmp","1.bmp","2.bmp","3.bmp","4.bmp","5.bmp","6.bmp","7.bmp","8.bmp","9.bmp","10.bmp"};
int explosion = 0;
int a=0;
bool musicOn = true;
#define ScreenHeight 540
#define ScreenWidth 1080
bool BDtankshow = 1;																			//BDtankshow
char cars[3][100] = {"pakt.bmp","pakt.bmp","pakt.bmp"};
#define CarNumber 3
int i = 0;																						//i is used for enemy tank

int roadIndex = 0;
char burst[3][100]={"e1.bmp","e2.bmp","e3.bmp"};
int b=0;
int b1 = 0;

#define fireNumber 3																			//fireNumber = 3
char fire[fireNumber][100] = {"bdbomb.bmp","bdbomb.bmp","bdbomb.bmp"};
char pakfire[fireNumber][100] = {"bomb1.bmp","bomb1.bmp","bomb1.bmp"};

//char fire[10][100] = {"bomb1.bmp","bomb1.bmp","bomb1.bmp","bomb1.bmp","bomb1.bmp",
//	"bomb1.bmp","bomb1.bmp","bomb1.bmp","bomb1.bmp","bomb1.bmp"};
int firecon[fireNumber]= {0};
int fireIndex = 0;


char life[14][100]={"healthbar1.bmp","healthbar1.bmp","healthbar2.bmp","healthbar2.bmp","healthbar3.bmp","healthbar3.bmp","healthbar4.bmp",
	"healthbar4.bmp","healthbar5.bmp","healthbar5.bmp","healthbar6.bmp","healthbar6.bmp","healthbar7.bmp","healthbar7.bmp"};


//high score file

FILE *fp;
char name[20] = {}, point[10] = {};

//high score name input
char nameStr[20] = {}, nameStr2[20] = {};
int nameLength = 0, nameMode = 0, thanks = 0;

int myScore = 0;
char myScoreText[10];

void score()
{
	sprintf_s(myScoreText, 10, "%d", myScore);
	iSetColor(255, 255, 0);
	iFilledRectangle(15,570, 150, 25);
	iSetColor(255,0, 0);
	iText(15, 400, "Score:", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(105, 398, myScoreText, GLUT_BITMAP_TIMES_ROMAN_24);
	//iText(15,500,"BD Tank Life:  " );
//	myScoreCopy = myScore;
}

// new Road
int gamebg;
int gamebgY1 = 0;
int gamebgY2 = 600;
int dd = 5;

void gamebackground()
{
	iShowImage(200,gamebgY1,720,600, gamebg);
	gamebgY1 -= dd;
	if(gamebgY1 == -540)
	{
		gamebgY1 = 540;
	}
	iShowImage(200,gamebgY2,720,600,gamebg);
	gamebgY2 -= dd;
	if(gamebgY2 == -540)
	{
		gamebgY2 = 540;
	}
}


void storyf()
{
	if(a<10)
	{
		a++;
	}
}


void burstf()																						//burst image shown
{
	b++;
	if (b>2)
	{
		b=0;

    }
}

void burst2f()
{
	bdtank_x = 300 + 1.5 * (rand() % 100) + rand() % 130,  bdtank_y=0;								//tank's position will be initialized after explosion
	//BDtankshow = 1;
	explosion = 0;

}


int l=0;

void lifef()																				//bdtank life
{
	if(l < 12)
	{
		l++;
	}
	else if(l == 12)
	{
		gamestate = 5;
	}
}



struct shoot{
	int shoot_x;																			//for BD Tank - x axis
	int shoot_y;																			//for BD Tank - y axis
	int fire_x;																				//for Pak Tank - x axis
	int fire_y;																				//for Pak Tank - y axis
};

struct shoot bomb[fireNumber];

int c=0;
void Fireshow()
{
	for(int i=0;i<fireNumber;i++)
	{
		if (firecon[i]==i+1)
		{
			iShowBMP2( bomb[i].shoot_x,bomb[i].shoot_y, fire[i],0);							//BD fire show
			iShowBMP2( bomb[i].fire_x,bomb[i].fire_y, pakfire[i],0);						//Pak fire show
			//bomb[i].shoot_y = bomb[i].shoot_y + 10;
		}

		bomb[i].shoot_y += 13;																//BD shoot
		bomb[i].fire_y -= 13;																//Pak shoot

		//bomb[i].bombShow = true;
	}
}
void Fire()																					//fire function
{
	if(firecon[c]==c)
	{
		bomb[c].shoot_x=bdtank_x+25;
		bomb[c].shoot_y=bdtank_y+50;

		firecon[c]=c+1;
		if(c ==  fireNumber - 1)
		{
			firecon[0]=0;
			c=0;

		}
		else
		{
			firecon[c+1]=c+1;
			c++;

		}
	}
}


struct car
{
	int car_x;
	int car_y;
	int carIndex;
	int carShow;
};

car enemy[CarNumber];


void EnemyMovement()
{
	if(gamestate == 1 && a==10)																	  // if gamestate = 1 and a = 10 then tank will be shown
	{
		for(int i=0; i< CarNumber;i++)
		{
			if(enemy[i].carShow)
			{
				iShowBMP2(enemy[i].car_x, enemy[i].car_y,cars[enemy[i].carIndex],0);				//enemy car is shown here

				if( ( (bdtank_x+72 >= enemy[i].car_x) && (bdtank_x <= enemy[i].car_x+72) &&			//if collision is done
					(enemy[i].car_y+100 >= bdtank_y) && (enemy[i].car_y <= bdtank_y+100) ) )
				{
					explosion = 1;
					lifef();
					//BDtankshow = 0;
					iShowBMP2(enemy[i].car_x ,enemy[i].car_y,burst[b],0);
					enemy[i].car_x = 300 + 1.5 * (rand() % 100) + rand() % 130;
					enemy[i].car_y = enemy[i].car_y + 1000 + ScreenHeight + rand() % rand();
				}

					if( ( (bomb[i].shoot_x+10 >= enemy[i].car_x)  && (bomb[i].shoot_x <= enemy[i].car_x+72) &&
					(bomb[i].shoot_y+10 >= enemy[i].car_y) && (bomb[i].shoot_y <= enemy[i].car_y+70) )   ||
					    ( (bomb[i+1].shoot_x+10 >= enemy[i].car_x)  && (bomb[i+1].shoot_x <= enemy[i].car_x+72) &&
					(bomb[i+1].shoot_y+10 >= enemy[i].car_y) && (bomb[i+1].shoot_y <= enemy[i].car_y+70) )   ||
					    ( (bomb[i+2].shoot_x+10 >= enemy[i].car_x)  && (bomb[i+2].shoot_x <= enemy[i].car_x+72) &&
					(bomb[i+2].shoot_y+10 >= enemy[i].car_y) && (bomb[i+2].shoot_y <= enemy[i].car_y+70) )    )
					{
						explosion = 2;													//explosion 2 is for collision between Pak tank and BD bomb
						iShowBMP2(enemy[i].car_x ,enemy[i].car_y,burst[b],0);
						//bomb[i].bombShow = false;
						if( bomb[i].shoot_y >= ScreenWidth )							//bomb's value will initilize after explosion
						{
							bomb[i].shoot_x = bdtank_x + 25;
							bomb[i].shoot_y = bdtank_y + 50;
						}
						enemy[i].car_y = ScreenHeight + rand() % 300  + rand() % 300;
					}

					if( ( (bomb[i].fire_x+10 >= bdtank_x)  && (bomb[i].fire_x <= bdtank_x+72) &&
					(bomb[i].fire_y+10 >= bdtank_y) && (bomb[i].fire_y <= bdtank_y+70) )   ||
					    ( (bomb[i+1].fire_x+10 >= bdtank_x)  && (bomb[i+1].fire_x <= bdtank_x+72) &&
					(bomb[i+1].fire_y+10 >= bdtank_y) && (bomb[i+1].fire_y <= bdtank_y+70) )   ||
					    ( (bomb[i+2].fire_x+10 >= bdtank_x)  && (bomb[i+2].fire_x <= bdtank_x+72) &&
					(bomb[i+2].fire_y+10 >= bdtank_y) && (bomb[i+2].fire_y <= bdtank_y+70) )    )
					{
						explosion = 3;													//explosion 3 is for collision between BD tank and Pak's bomb
						iShowBMP2(bdtank_x ,bdtank_y,burst[b],0);
						lifef();														//life will decrease

						if( bomb[i].fire_y >= ScreenHeight )							//bomb's value will initialize after explosion/screen height
						{
							bomb[i].fire_x = enemy[i].car_x + 18;
							bomb[i].fire_y = enemy[i].car_y -10;
						}
																	//line 1 nd 2
						bdtank_y = ScreenHeight + rand() % 300  + rand() % 300;
																	//+ sign for sending the enemy backward and come again
					}




				}
			}
	}
}


void Fire2()													//pak fire function
{
	if(firecon[c]==c)
	{
		for(int i=0; i<fireNumber;i++)
		{
			bomb[c].fire_x=enemy[i].car_x+18;
			bomb[c].fire_y=enemy[i].car_y-10;

			firecon[c]=c+1;
			if(c == fireNumber - 1)
			{
				firecon[0]=0;
				c=0;
			}
			else
			{
				firecon[c+1]=c+1;
				c++;
			}
		}
	}
}

void setEnemyVariables()																		//road limit - 250 to 770
{
	if(i==0)																					//1st lane enemy tank
	{
		for(i=0; i<1;i++)
		{
			enemy[i].car_x = 80 + 3.5 * (rand() % 103) + rand() % 103 + (rand() % 103) ;
			//enemy[i].car_y = 1.5 * ScreenHeight + rand() % rand() * 1.5 ;
			enemy[i].car_y = ScreenHeight + rand() % 300  + rand() % 300;

			if(enemy[i].car_x > 300 && enemy[i].car_x < 550)
			{
				enemy[i].carShow = true;
			}
			enemy[i].carIndex = rand() % 10;
		}
	}
	if(i==1)
	{
		for( i=1; i<2;i++)																		//2nd lane enemy tank
		{
		enemy[i].car_x = 330 + 2.5 * (rand() % 133) + rand() % 133 + (rand() % 123) ;
		//enemy[i].car_y = 1.5 * ScreenHeight + rand() % rand() * 1.5 ;
		enemy[i].car_y = ScreenHeight + rand() % 300  + rand() % 300;

		if(enemy[i].car_x > 360 && enemy[i].car_x < 650)
		{
			enemy[i].carShow = true;
		}
		enemy[i].carIndex = rand() % 10;
		}
	}
	if(i==2)																					//3rd lane enemy tank
	{
		for( i=2; i<3;i++)
		{
			enemy[i].car_x = 520 + 2.3 * (rand() % 133) + rand() % 113 + (rand() % 123);
			//enemy[i].car_y = 1.5 * ScreenHeight + rand() % rand() * 1.5 ;
			enemy[i].car_y = ScreenHeight + rand() % 300  + rand() % 300;

			if(enemy[i].car_x > 500 && enemy[i].car_x < 770)
			{
				enemy[i].carShow = true;
			}
			//enemy[i].carShow = false;
			enemy[i].carIndex = rand() % 10;
		}
	}
}


void move(){

	if(gamestate == 1)
	{
		for(int i=0;i<CarNumber;i++)
		{
			enemy[i].car_y -= 10;																//car speed
			if(enemy[i].car_y <= 0)
			{
				enemy[i].car_y = ScreenHeight + rand() % 300  + rand() % 300;
			}
			enemy[i].carIndex++;
			if(enemy[i].carIndex >= 3)
			{
				enemy[i].carIndex = 0;
			}
		}
	}
}

int myTimer = 0, myTimerCopy;
char myTimerText[10];

void Time()
{
	sprintf_s(myTimerText, 10, "%d", myTimer);
	iSetColor(255, 255, 0);
	iFilledRectangle(15,570, 150, 25);
	iSetColor(255, 255, 255);
	iText(941,502, "Timer: ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1015, 502, myTimerText, GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(255, 0, 0);
	iText(941,472, "Time Limit: 5000");
	myTimerCopy = myTimer;
	myTimer++;
	if(myTimer == 5000)
	{
		myTimer = 0;
		gamestate = 5;
	}
}

void iDraw()
{
	iClear();

	if(gamestate==0)
	{
		iShowBMP(0,0, "menu.bmp" );
	}
	else if(gamestate == 1)
	{
		iShowBMP(200,0,story[a]);
		if(a<9)
		{
			iText(0,525,"Press's' to skip full story,'d' to view next picture and 'a' to view previous picture");
		}
		if(a==10)
		{
			Time();
			score();
			gamebackground();
			iShowBMP2( bdtank_x, bdtank_y, "bdt.bmp",0);

			EnemyMovement();
			Fireshow();
			iSetColor(255, 255, 255);
			iText(15, 502, "BD Tank Life  ", GLUT_BITMAP_TIMES_ROMAN_24);
			iShowBMP(0,450,life[l]);

			if(f1==1)
			{
				//iShowBMP2(f1_x, f1_y,"bomb1.bmp",0);
				Fire();
			}
			if(explosion == 1)													//explosion 1 is for collision between BD tank and pak tank
			{
				iShowBMP2(bdtank_x,bdtank_y,burst[b],0);						//explosion code here
				burstf();
				burst2f();
				explosion = 0;
			}
			if(explosion == 2)													//explosion 2 is for collision between a Pak tank and bomb
			{
				burstf();
				//myScore++;
				myScore = (myScore + 1);
				if(myScore>50)													//if score is greater than 40
				{
					gamestate = 6;
				}
				explosion = 0;
			}
			if(explosion == 3)													//explosion 2 is for collision between pak tank and bomb
			{
				burst2f();
				explosion = 0;
			}
		}
	}
	else if(gamestate == 2)
	{
		iShowBMP(0, 0,"highscorePage.bmp");

		iSetColor(255, 255, 255);

		int namePosition = 400;
		fp = fopen("Highscore file.txt","r");
/*
		for(int i=0; i<7; i++)
		{
			namePosition -= 40;
			fscanf(fp, "%s %s", name, point);
			iText(400, namePosition, name, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(650, namePosition, point, GLUT_BITMAP_TIMES_ROMAN_24);
		}
*/
		while(fscanf(fp, "%s\t%s", point, name)!=EOF)
		{
			int pointInt=toNumber(point);
			v.push_back(make_pair(pointInt,name));
		}
		sort(v.begin(),v.end());
		reverse(v.begin(),v.end());
		fclose(fp);
		int k;
		if(v.size()<5) k=v.size();
		else k=5;
		int nameposition = 350;
		for(int i=0;i<k;i++)
		{
			std::string s1=v[i].second;
			std::string s2=toString(v[i].first);
			char nameCopy[20];
			char pointCopy[10];
			strcpy(nameCopy,s1.c_str());
			strcpy(pointCopy,s2.c_str());
			iText(200, nameposition, nameCopy, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(500, nameposition, pointCopy, GLUT_BITMAP_TIMES_ROMAN_24);
			nameposition-=40;
		}
		v.clear();
		fclose(fp);

	}
	else if(gamestate == 3)
	{
		iShowBMP(0,0, "controls.bmp");
	}
	else if(gamestate == 4)
	{
		iShowBMP(0,0, "credits.bmp");
	}
	// gameover
	else if(gamestate == 5)																	//game over page
	{
		iShowBMP(0,0,"gameover.bmp");
		iSetColor(255, 255, 255);
		iText(5, 10, "Press 'z' to give input of your name and then press enter ");
		//scoreShow();																		//calling scoreShow()

		iSetColor(255, 0, 0);
		iFilledRectangle(440, 150, 200, 40);
		iSetColor(255, 255, 0);
		iFilledCircle(534,85, 60, 1000);
		iSetColor(150, 150, 150);
		iText(450, 165, " Enter Your Name ", GLUT_BITMAP_TIMES_ROMAN_24);

		if(nameMode == 1)
		{
			iSetColor(255, 0, 0);
			iFilledRectangle(440, 150, 200, 40);
			iSetColor(0, 0, 0);
			iText(454, 170, nameStr, GLUT_BITMAP_TIMES_ROMAN_24);
		}

		if(thanks == 1)
		{
			iShowBMP(440, 150,  "greenButton.bmp");
			iSetColor(0, 0, 0);
			//iText(460,170, "THANK YOU", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(480,162, "Thank You", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		iSetColor(0, 0, 0);
		iText(506, 109, "Score", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(518,73, myScoreText, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if(gamestate == 6)							//Mission Successful
	{
		iShowBMP(0,0,"success.bmp");

		iSetColor(255, 255, 255);
		iText(5, 10, "Press 'q' to give input of your name and then press enter ");
		//scoreShow();								//calling scoreShow()
		iSetColor(255, 0, 0);
		iFilledRectangle(440, 150, 200, 40);
		iSetColor(255, 255, 0);
		iFilledCircle(534,85, 60, 1000);
		iSetColor(150, 150, 150);
		iText(450, 165, "Enter Your Name", GLUT_BITMAP_TIMES_ROMAN_24);

		if(nameMode == 1)
		{
			iSetColor(255, 0, 0);
			iFilledRectangle(440, 150, 200, 40);
			iSetColor(0, 0, 0);
			iText(454, 170, nameStr, GLUT_BITMAP_TIMES_ROMAN_24);
		}

		if(thanks == 1)
		{
			iShowBMP(440, 150,  "greenButton.bmp");
			iSetColor(0, 0, 0);
			//iText(460,170, "THANK YOU", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(480,162, "Thank You", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		iSetColor(0, 0, 0);
		iText(506, 109, "Score", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(518,70, myScoreText, GLUT_BITMAP_TIMES_ROMAN_24);
	}

}

void iMouseMove(int mx, int my)
{
	//place your codes here
}
void iPassiveMouse(int mx, int my)
{
	//place your codes here
}

void iMouse(int button, int state, int mx, int my)
{
	//printf( "%d %d\n", mx, my);
	if( gamestate==0)
	{
		if(mx >=38 && mx <=185 && my >=340 && my <= 385)
		{
			gamestate = 1;
		}
		else if(mx >=38&& mx <= 172 && my>=283 && my <=323)
		{
			gamestate = 2;
		}
		else if(mx >=37 && mx <= 188 && my>=231 && my <=271)
		{
			gamestate = 3;
		}
		else if(mx>=38 && mx<= 183 && my >= 173 && my <= 213)
		{
			gamestate = 4;
		}
		else if(mx >= 441 && mx <=638 && my >= 152 && my <= 192 || nameMode == 0)
		{
			nameMode = 1;																				//name input on
		}
		else if(mx>=47   && mx<=172   && my >= 120   && my <= 140 )
		{
			exit(0);
		}
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}


void iKeyboard(unsigned char key)
{

	if(key == 'x')
	{
		gamestate = 0;
	}
	if(key == 'p')
	{
		iPauseTimer(0);
	}
	if(key == 'r')
	{
		iResumeTimer(0);
	}
	if(key == 'f')
	{
		Fire();
	}
	if(key == 'm')
	{
		if(musicOn)
		{
			musicOn = false;
			PlaySound(0,0,0);
		}
		else
		{
			musicOn = true;
			PlaySound("Music\\Chol chol chol.wav",NULL, SND_LOOP | SND_ASYNC);
		}
	}
	if(key == 's')
	{
		a=10;
	}
	if(key == 'd')
	{
		if(a<10)
		{
			a++;
		}
	}
	if(key == 'a')
	{
		if(a>0 && a<10)
		{
			a--;
		}
	}
	if(nameMode == 1 && gamestate == 5 )
	{
		if( key == '\r' && gamestate == 5)
		{
			//file
			fp = fopen("Highscore file.txt","a");
			fprintf(fp,"%s\t%s\n", myScoreText, nameStr);
			fclose(fp);

			for(int i=0; i<nameLength; i++)
			{
				nameStr[i] = 0;
			}
			nameLength = 0;
			nameMode = 0;
			thanks = 1;																	//thanks = 1
		}
		else if( key=='\b' && gamestate==5)
		{
			nameLength--;
			nameStr[nameLength] = key;
			if( nameLength < 0)
			{
				nameLength = 0;
			}
		}
		else
		{
			nameStr[nameLength] = key;
			nameLength++;
		}

	}
	if(nameMode == 1 && gamestate == 6)
	{
		if( key == '\r' && gamestate == 6)
		{
			//file
			fp = fopen("Highscore file.txt","a");
			fprintf(fp,"%s\t%s\n", myScoreText, nameStr);
			fclose(fp);

			for(int i=0; i<nameLength; i++)
			{
				nameStr[i] = 0;
			}
			nameLength = 0;
			nameMode = 0;
			thanks = 1;															//thanks = 1
		}
		else if( key=='\b' && gamestate==6)
		{
			nameLength--;
			nameStr[nameLength] = key;
			if( nameLength < 0)
			{
				nameLength = 0;
			}
		}
		else
		{
			nameStr[nameLength] = key;
			nameLength++;
		}
	}

	if(key == 'z')
	{
		gamestate = 5;															//gameover manually to check the error
		nameMode = 1;
	}
	if(key == 'q')
	{
		gamestate = 6;															//mission succesful manually to check the error
		nameMode = 1;
	}
}


void iSpecialKeyboard(unsigned char key)
{
	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	if(key == GLUT_KEY_LEFT)
	{
		if(bdtank_x >= 250)
		{
			bdtank_x -= 15;
		}
	}
	if(key == GLUT_KEY_RIGHT)
	{
		if( bdtank_x <=770)
		{
			bdtank_x +=15;
		}
	}
	if(key == GLUT_KEY_UP)
	{
		if(bdtank_y <= 440)
		{
			bdtank_y += 15;
		}
	}
	if(key == GLUT_KEY_DOWN)
	{
		if(bdtank_y >= 10)
		{
			bdtank_y -= 15;

		}
	}
}

void Image()
{
	gamebg = iLoadImage("newroad.jpg");											// road image inserted
}

void musics()
{
	//PlaySound("Music//Chol chol chol.wav",NULL, SND_LOOP | SND_ASYNC);
}

int main()
{
    bdtank_x = 400;
    bdtank_y = 0;

	setEnemyVariables();
	iSetTimer(1000,Image);														//Road is calling
	iSetTimer(1700,Fire2);														//Fire is calling
	iSetTimer(120,move);
	iSetTimer(200000, Time);

	if(musicOn)
	{
		musics();
	}
	iInitialize(ScreenWidth, ScreenHeight, "WARS71");
	iStart();
	return 0;
}


/*
//highscore sort
vector < pair<int,string> > v;
string toString(int n)
{
	ostringstream ost;
	ost << n;
	ost.flush();
	return ost.str();
}

int toNumber(string s)
{
	stringstream numStr(s);
	int numInt;
	numStr>>numInt;
	return numInt;
}
*/

/*
		iShowBMP(0, 0,"highscorePage.bmp");
		iSetColor(0, 0, 0);


*/
