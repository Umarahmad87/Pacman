//============================================================================
// Name        : Pacman.cpp
// Copyright   : (c) Reserved
// Description : Basic 2D game of Pacman...
//============================================================================

#ifndef PACMAN_CPP_
#define PACMAN_CPP_
#include "Board.h"
#include "Board2.h"
#include "Ghost.h"
#include "util.h"
#include <iostream>
#include<string>
#include"opal.h"
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void Hello_World(){
	ALuint helloBuffer, helloSource=0;
	    //alutInit (&argc, argv);
	    helloBuffer = alutCreateBufferHelloWorld ();
	    alGenSources (1, &helloSource);
	    cout<<endl<<"Hello Source="<<helloSource<<endl<<endl;
	    alSourcei (helloSource, AL_BUFFER, helloBuffer);
	    alSourcePlay (helloSource);
	  //  alutSleep (1);
	    //alutExit ();
	//    return EXIT_SUCCESS;
}

void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
}
void DrawGhost(int x/*starting x*/, int y/*starting y*/,
		ColorNames color/*color*/,float gw = 6/*Ghost Width in Units*/,
		float gh = 7/*Ghost Height in Units*/,int record=1) {
	int ogw = 6, ogh = 7;

	glPushMatrix();
	float sx = (float) gw / ogw, sy = (float) gh / ogh;
	glTranslatef(x, y, 1);
	glScalef(sx, sy, 1);

	// Draw ghost
	DrawRoundRect(0, 1, 6, 3, colors[color]);
	DrawCircle(3, 4, 3.01, colors[color]);
	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	//  legs
	DrawCircle(0.75, 1, 0.75, colors[color]);
	DrawCircle(3.25, 1, 0.75, colors[color]);
	DrawCircle(5.85, 1, 0.75, colors[color]);

	glPopMatrix();
//	glPopMatrix();

	// eyes

	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	DrawCircle(1.85, 3.95, 0.75, colors[WHITE]);
	DrawCircle(4.95, 3.95, 0.75, colors[WHITE]);
	glPopMatrix();

	// eyes
	if(record==0){
	DrawCircle(1.45, 4.25, 0.45, colors[BLUE]);
	DrawCircle(4.25, 4.25, 0.45, colors[BLUE]);}
	else if(record==1){
		DrawCircle(1.85, 4.25, 0.45, colors[BLUE]);
		DrawCircle(4.65, 4.25, 0.45, colors[BLUE]);}
	else if(record==2){
			DrawCircle(1.65, 4.45, 0.45, colors[BLUE]);
			DrawCircle(4.45, 4.45, 0.45, colors[BLUE]);}
	else if(record==3){
				DrawCircle(1.65, 4.05, 0.45, colors[BLUE]);
				DrawCircle(4.45, 4.05, 0.45, colors[BLUE]);}
	else {
		DrawCircle(1.65, 4.25, 0.45, colors[BLUE]);
		DrawCircle(4.45, 4.25, 0.45, colors[BLUE]);}
	glPopMatrix();
}

//Number of Vertices used to draw Pacman Circle...
// x= r cos (theta), y= r sin(theta)
const int npmvertices = 1220;
GLfloat pmvertices[npmvertices][2];
void InitPMVertices(float radius,float angle2) {

	float hdegree = (M_PI - M_PI / 2.0) / 360.0;
	float angle = M_PI + M_PI / angle2;
	for (int i = 0; i < npmvertices; ++i) {
		pmvertices[i][0] = radius * cos(angle);
		pmvertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}
}

void DrawPacMan(float sx/*center x*/, float sy/*center y*/,
		float radius/*Radius*/, const ColorNames &colorname/*Pacman Colour*/,float angle) {

	glColor3fv(colors[colorname]); // set the circle color
	InitPMVertices(radius,angle);
	glBegin(GL_TRIANGLE_FAN);
	glVertex4f(sx, sy, 0, 1);
	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(sx + pmvertices[i][0], sy + pmvertices[i][1], 0, 1);
	glEnd();
	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
			radius / 10, colors[BLACK]);
}
void DrawPacMan2(float sx/*center x*/, float sy/*center y*/,
		float radius/*Radius*/, const ColorNames &colorname/*Pacman Colour*/,float angle) {

	DrawCircle(sx, sy ,radius, colors[YELLOW]);
	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
			radius / 10, colors[BLACK]);
}

enum Characters { pacman, pinky , board , blinky , inky , clyde};

/*
 * Main Canvas drawing function.
 * */

Board2 *B;
void Display()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0.0/*Red Component*/, 0.0/*Green Component*/,
			0.0/*Blue Component*/, 0.0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	//alSourcePlay(Source);
	if(B->GetLife()<=0){
			DrawString(230, 300, "Game Over", colors[5]);
			DrawString(170, 425, "Press R to play again...", colors[RED]);}
	if(B->pac[0]->Pebbles()<=0){
				if(B->level<=2){
				DrawString(180, 300, " Level Completed !", colors[5]);
				DrawString(170, 425, "Press R for Next Level", colors[RED]);}
				else {
				DrawString(230, 300, " You Won ! ", colors[GREEN_YELLOW]);
				DrawString(170, 425, "Press R to play again", colors[GREEN_YELLOW]);}}
	//cout<<"Pebbles Left :"<<B->pac[0]->Pebbles()<<endl;
	// Life
	for(int life=0,x=40;life <(B->GetLife());life++){
	DrawPacMan(x , 20, B->pac[0]->Radius() , YELLOW,6.0);
	x+=40;}

	static int jj=0;
	B->pac[board]->Draw(jj);
	if(jj==1)
	DrawString(230, 300,"Get Ready !", colors[GOLD]);
	jj++;
	int x, y;
	float Px,Py,x1,y1,Gx,Gy,Gcx,Gcy;
	float blinkyx,blinkyy,inkyx,inkyy,cx,cy;
	B->pac[board]->GetInitPinkyPosition(x, y);
	B->pac[pinky]->GetPixel(Gx,Gy);
	B->pac[blinky]->GetPixel(blinkyx,blinkyy);
	B->pac[inky]->GetPixel(inkyx,inkyy);
	B->pac[clyde]->GetPixel(cx,cy);

		if(B->pac[pinky]->Frightn()==1){
			DrawGhost(Gx - 6, Gy-6, BLUE, 1.8 * B->pac[pinky]->GetCellSize(), 1.8 * B->pac[pinky]->GetCellSize(),B->pac[pinky]->record);}
		if(B->pac[blinky]->Frightn()==1){
			DrawGhost(blinkyx - 6, blinkyy-6, BLUE, 1.8 * B->pac[blinky]->GetCellSize(), 1.8 * B->pac[blinky]->GetCellSize(),B->pac[blinky]->record);}
		if(B->pac[inky]->Frightn()==1){
			DrawGhost(inkyx - 6, inkyy-6,BLUE, 1.8 * B->pac[inky]->GetCellSize(), 1.8 * B->pac[inky]->GetCellSize(),B->pac[inky]->record);}
		if(B->pac[clyde]->Frightn()==1){
			DrawGhost(cx - 6, cy-6, BLUE, 1.8 * B->pac[clyde]->GetCellSize(), 1.8 * B->pac[clyde]->GetCellSize(),B->pac[clyde]->record);}


		if(B->pac[pinky]->Frightn()==0){
			DrawGhost(Gx - 6, Gy-6, PINK, 1.8 * B->pac[pinky]->GetCellSize(), 1.8 * B->pac[pinky]->GetCellSize(),B->pac[pinky]->record);}
		if(B->pac[blinky]->Frightn()==0){
			DrawGhost(blinkyx - 6, blinkyy-6, RED, 1.8 * B->pac[blinky]->GetCellSize(), 1.8 * B->pac[blinky]->GetCellSize(),B->pac[blinky]->record);}
		if(B->pac[inky]->Frightn()==0){
			DrawGhost(inkyx - 6, inkyy-6,SKY_BLUE, 1.8 * B->pac[inky]->GetCellSize(), 1.8 * B->pac[inky]->GetCellSize(),B->pac[inky]->record);}
		if(B->pac[clyde]->Frightn()==0){
			DrawGhost(cx - 6, cy-6, ORANGE, 1.8 * B->pac[clyde]->GetCellSize(), 1.8 * B->pac[clyde]->GetCellSize(),B->pac[clyde]->record);}

/*
	else if(B->Frightn()==0){
	DrawGhost(Gx - 6, Gy-6, PINK, 1.8 * B->pac[pinky]->GetCellSize(), 1.8 * B->pac[pinky]->GetCellSize(),B->pac[pinky]->record);
	DrawGhost(blinkyx - 6, blinkyy-6, RED, 1.8 * B->pac[blinky]->GetCellSize(), 1.8 * B->pac[blinky]->GetCellSize(),B->pac[blinky]->record);
	DrawGhost(inkyx - 6, inkyy-6,SKY_BLUE, 1.8 * B->pac[inky]->GetCellSize(), 1.8 * B->pac[inky]->GetCellSize(),B->pac[inky]->record);
	DrawGhost(cx - 6, cy-6, ORANGE, 1.8 * B->pac[clyde]->GetCellSize(), 1.8 * B->pac[clyde]->GetCellSize(),B->pac[clyde]->record);}*/
	B->pac[pacman]->GetPixel(Px,Py);
	B->pac[pacman]->GetCell(x1,y1);
	B->pac[pinky]->GetCell(Gcx,Gcy);

	if(B->pac[pacman]->movement==0 or B->pac[pacman]->record==0){
		DrawPacMan(Px + 20 - 9, Py + 20 - 8, B->pac[0]->Radius(), YELLOW,6.0);
	}
	if(B->pac[pacman]->record==1){
		if(B->pac[0]->GetMove()%2==0)
		DrawPacMan(Px + 20 - 9, Py + 20 - 8, B->pac[0]->Radius(), YELLOW,6.0);
		else if(B->pac[0]->GetMove()%2==1)
			DrawPacMan2(Px + 20 - 9, Py + 20 - 8, B->pac[0]->Radius(), YELLOW,6.0);
	}
	if(B->pac[pacman]->record==2){
		if(B->pac[0]->GetMove()%2==0)
			DrawPacMan(Px + 20 - 9, Py +20 - 8, B->pac[0]->Radius(), YELLOW,-1.2);
		else if(B->pac[0]->GetMove()%2==1 )
			DrawPacMan2(Px + 20 - 9, Py + 20 - 8, B->pac[0]->Radius(), YELLOW,-1.2);
	}
	if(B->pac[pacman]->record==3){
		if(B->pac[0]->GetMove()%2==0  )
		DrawPacMan(Px + 20 - 9, Py +20 - 8, B->pac[0]->Radius(), YELLOW,-3.0);
		else if(B->pac[0]->GetMove()%2==1)
					DrawPacMan2(Px + 20 - 9, Py + 20 - 8, B->pac[0]->Radius() , YELLOW,-3.0);

	}
	if(B->pac[pacman]->record==4){
	if(B->pac[0]->GetMove()%2==0)
		DrawPacMan(Px + 20 - 9, Py +20 - 8, B->pac[0]->Radius() , YELLOW,1.5);
	else if(B->pac[0]->GetMove()%2==1)
						DrawPacMan2(Px + 20 - 9, Py + 20 - 8, B->pac[0]->Radius(), YELLOW,1.5);}

	// Pacman Movement
	cout<<"____PACMAN____"<<endl;
	string score="Score = ",hscore="HighScore = ";
	DrawString(280/14, 680, score += B->pac[pacman]->Score(), colors[WHITE]);
	DrawString(20, 720, hscore += B->HighScore(), colors[ANTIQUE_WHITE]);
	if(B->level==0) DrawString(450, 680, "Level 1", colors[WHITE]);
	if(B->level==1) DrawString(450, 680, "Level 2", colors[WHITE]);
	if(B->level==2) DrawString(450, 680, "Level 3", colors[WHITE]);
	if(B->level==3) DrawString(450, 680, "Level 4", colors[WHITE]);
	int decision;
	decision=B->pac[pacman]->RemovePebbles();
	if(decision==2){
			alSourcePlay(Source2);
	}
	if(decision==1){

		alSourcePlay(Source2);
		B->Frightn(1);
	}
//	glPopMatrix();
	glutSwapBuffers(); // do not modify this line..
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y){
	if(B->GetLife()>0 and B->pac[0]->Pebbles()>0){
	if(B->Pause()==0){
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		B->pac[pacman]->movement = 1;

	} else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		B->pac[pacman]->movement = 2;

	}
	else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		B->pac[pacman]->movement = 3;

	}

	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		B->pac[pacman]->movement = 4;
	}
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	// glutPostRedisplay();
	}}
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == KEY_ESC/* Escape key ASCII*/) {
		B->HighScore(B->pac[pacman]->Score());
		exit(1); // exit the program when escape key is pressed.
		//pac[0]->Reset();
	}
	if(key==80 or key==80 + 32){  // P
		B->Pause(0);
	}
	if(key==82 or key==82 + 32){  // R
			//B->pac[0]->Reset();
		if(B->GetLife()<=0){
			B->All_Reset();
			B->Life_Reset();
			B->HighScore(B->pac[pacman]->Score());
			B->pac[0]->Score_Reset();
			B->level=0;
			B->pac[2]->SetColor(0);
			B->pac[board]->Start(B->level);
			B->Load_Level(B->level);
		}
		if(B->pac[0]->Pebbles()<=0){
					B->All_Reset();

					if(B->level==3){
						B->level=0;
						B->Life_Reset();
						B->HighScore(B->pac[pacman]->Score());
						B->pac[0]->Score_Reset();
						B->pac[2]->SetColor(0);
					}
					else{
						B->level++;
						B->pac[2]->SetColor(B->level);
					}
					B->pac[board]->Start(B->level);
					B->Load_Level(B->level);
				}
			//B->Frightn(0);
	}
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

// implement your functionality here
	if(B->GetLife()>0 and B->pac[0]->Pebbles()>0){
	if(B->Pause()==0){
	B->pac[pacman]->Movement();


	//B->pac[blinky]->Movement();
		if(B->pac[blinky]->Frightn()==0){
			B->pac[blinky]->Search((B->pac[pacman]->getX()/20.0),B->pac[pacman]->getY()/20.0);}
		else if(B->pac[blinky]->Frightn()==1){

			static int ll1=0;
					if(ll1%2==0){
					B->pac[blinky]->Movement2();}
			ll1++;
		}

	if(B->pac[pinky]->Frightn()==0){
		B->pac[pinky]->Search(B->pac[pacman]->getX()/20.0,B->pac[pacman]->getY()/20.0);}
	else if(B->pac[pinky]->Frightn()==1){
		static int ll2=0;
							if(ll2%2==0){
							B->pac[pinky]->Movement2();}
					ll2++;
	}

	if(B->pac[inky]->Frightn()==0){
		B->pac[inky]->Search((B->pac[pacman]->getX()/20.0),(B->pac[pacman]->getY()/20.0));}
	else if(B->pac[inky]->Frightn()==1){

		static int ll3=0;
							if(ll3%2==0){
							B->pac[inky]->Movement2();}
					ll3++;
	}

	if(B->pac[clyde]->Frightn()==0){
		B->pac[clyde]->Search(B->pac[pacman]->getX()/20.0,B->pac[pacman]->getY()/20.0);}
	else if(B->pac[clyde]->Frightn()==1){

		static int ll4=0;
							if(ll4%2==0){
							B->pac[clyde]->Movement2();}
					ll4++;
	}
//	B->pac[pinky]->Movement();
//	B->pac[inky]->Movement();
//	B->pac[clyde]->Movement();

	/*else if(B->Frightn()==1){
		static int ll=0;
		if(ll%2==0){
		B->pac[blinky]->Movement2();
		B->pac[pinky]->Movement2();
		B->pac[inky]->Movement2();
		B->pac[clyde]->Movement2();}
		ll++;

	}*/
	B->pac[0]->Move(1);}}
	if(B->pac[pacman]->Pebbles()==242){
		B->pac[pinky]->Start(0);
	}
	if(B->pac[pacman]->Pebbles()==170){
			B->pac[inky]->Start(0);
		}
	if(B->pac[pacman]->Pebbles()==72){
			B->pac[clyde]->Start(0);
		}
	if(B->Frightn()==1)
		B->Count2();
	int collision=B->Collision();
	if(collision==1){
		alSourcePlay(Source);
	}
	if(collision==2){
			alSourcePlay(Source);
		}
// once again we tell the library to call our Timer function after next 1000/FPS
	if(B->level%2==0)
		glutTimerFunc(100.0, Timer, 0);
	if(B->level%2==1)
		glutTimerFunc(80.0, Timer, 0);
	glutPostRedisplay();
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
	//b=new Board; // create a new board object to use in the Display Function ...
	static Board **pacman=new Board *[5];
	pacman[2]=new Board;
	pacman[0]=new Pacman(13,9); /* 13,9*/
	pacman[pinky]=new Ghost(13,18); /* 13,18*/
	pacman[blinky]=new Ghost(13,21);/* 13,21*/
	pacman[inky]=new Ghost(15,18);/* 15,18*/
	pacman[clyde]=new Ghost(11,18);/* 11,18*/
	B = new Board2;
	B->insert(*pacman[0]);
	B->insert(*pacman[1]);
	B->insert(*pacman[2]);
	B->insert(*pacman[blinky]);
	B->insert(*pacman[inky]);
	B->insert(*pacman[clyde]);
	int width = 560, height = 760; // i have set my window size to be 560 x 720
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
    alutInit(NULL, 0);
    alGetError();
    if(LoadALData() == AL_FALSE) //method 1: LoadALData()
    {
                   cout<<"Error loading data.";
                           return 0;
    }
    LoadALData2();
    SetListenerValues();
    //alSourcePlay(Source);
             /*   cin>>c;
                while(c != 'q')
                {

                            switch(c)
                            {
                                        // Pressing 'p' will begin playing the sample.
                                        case 'p': alSourcePlay(Source); break;

                                        // Pressing 's' will stop the sample from playing.
                                        case 's': alSourceStop(Source); break;

                                        // Pressing 'h' will pause the sample.
                                        case 'h': alSourcePause(Source); break;
                            };
                            cin>>c;
                }*/
	alutInit(&argc, argv) ;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition( 500 , 0); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("PACMAN"); // set the title of our game window
	SetCanvasSize(width, height);// set the number of pixels...

// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
// now handle the control to library and it will call our registered functions when
// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* PACMAN_CPP_ */
