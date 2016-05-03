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
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
}
void DrawGhost(int x/*starting x*/, int y/*starting y*/,
		ColorNames color/*color*/, float gw = 6/*Ghost Width in Units*/,
		float gh = 7/*Ghost Height in Units*/) {
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
	DrawCircle(1.65, 4.25, 0.45, colors[BLUE]);
	DrawCircle(4.45, 4.25, 0.45, colors[BLUE]);
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
//Board *b;

Board2 *B;
void Display()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0.0/*Red Component*/, 0.0/*Green Component*/,
			0.0/*Blue Component*/, 0.0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	//glutPostRedisplay();
	 //
	//b->Draw();
	//DrawString(300, 300, "READY !", colors[5]);
	if(B->GetLife()<=0 or B->pac[0]->Pebbles()<=0){
			DrawString(230, 300, "Game Over", colors[5]);
			DrawString(170, 425, "Press R to play again...", colors[RED]);}
	cout<<"Pebbles Left :"<<B->pac[0]->Pebbles()<<endl;
	// Life
	for(int life=0,x=40;life <(B->GetLife());life++){
	DrawPacMan(x , 20, B->pac[0]->Radius() , YELLOW,6.0);
	x+=40;}


	B->pac[board]->Draw();
	int x, y;
	float Px,Py,x1,y1,Gx,Gy,Gcx,Gcy;
	float blinkyx,blinkyy,inkyx,inkyy,cx,cy;
	B->pac[board]->GetInitPinkyPosition(x, y);
	B->pac[pinky]->GetPixel(Gx,Gy);
	B->pac[blinky]->GetPixel(blinkyx,blinkyy);
	B->pac[inky]->GetPixel(inkyx,inkyy);
	B->pac[clyde]->GetPixel(cx,cy);
	if(B->Frightn()==1){
	DrawGhost(Gx - 6, Gy-6, BLUE, 1.8 * B->pac[pinky]->GetCellSize(), 1.8 * B->pac[pinky]->GetCellSize());
		DrawGhost(blinkyx - 6, blinkyy-6, BLUE, 1.8 * B->pac[blinky]->GetCellSize(), 1.8 * B->pac[blinky]->GetCellSize());
		DrawGhost(inkyx - 6, inkyy-6,BLUE, 1.8 * B->pac[inky]->GetCellSize(), 1.8 * B->pac[inky]->GetCellSize());
		DrawGhost(cx - 6, cy-6, BLUE, 1.8 * B->pac[clyde]->GetCellSize(), 1.8 * B->pac[clyde]->GetCellSize());}

	else if(B->Frightn()==0){
	DrawGhost(Gx - 6, Gy-6, PINK, 1.8 * B->pac[pinky]->GetCellSize(), 1.8 * B->pac[pinky]->GetCellSize());
	DrawGhost(blinkyx - 6, blinkyy-6, RED, 1.8 * B->pac[blinky]->GetCellSize(), 1.8 * B->pac[blinky]->GetCellSize());
	DrawGhost(inkyx - 6, inkyy-6,SKY_BLUE, 1.8 * B->pac[inky]->GetCellSize(), 1.8 * B->pac[inky]->GetCellSize());
	DrawGhost(cx - 6, cy-6, ORANGE, 1.8 * B->pac[clyde]->GetCellSize(), 1.8 * B->pac[clyde]->GetCellSize());}
	B->pac[pacman]->GetPixel(Px,Py);
	B->pac[pacman]->GetCell(x1,y1);
	B->pac[pinky]->GetCell(Gcx,Gcy);
	//cout<<"Ghost x cell="<<Gcx<<" y cell="<<Gcy<<endl;
	B->pac[pacman]->Draw();
	// Pacman Movement
	//DrawGhost(Px - 5, Py, PINK, 1.8 * pac[0]->GetCellSize(), 1.8 * pac[0]->GetCellSize());
	if(B->pac[pacman]->movement==0){
		DrawPacMan(Px + 20 - 9, Py + 20 - 8, B->pac[0]->Radius(), YELLOW,6.0);
	}
	if(B->pac[pacman]->movement==1){
		if(B->pac[0]->GetMove()%2==0)
		DrawPacMan(Px + 20 - 9, Py + 20 - 8, B->pac[0]->Radius(), YELLOW,6.0);
		else if(B->pac[0]->GetMove()%2==1)
			DrawPacMan2(Px + 20 - 9, Py + 20 - 8, B->pac[0]->Radius(), YELLOW,6.0);
	}
	if(B->pac[pacman]->movement==2){
		if(B->pac[0]->GetMove()%2==0)
			DrawPacMan(Px + 20 - 9, Py +20 - 8, B->pac[0]->Radius(), YELLOW,-1.2);
		else if(B->pac[0]->GetMove()%2==1 )
			DrawPacMan2(Px + 20 - 9, Py + 20 - 8, B->pac[0]->Radius(), YELLOW,-1.2);
	}
	if(B->pac[pacman]->movement==3){
		if(B->pac[0]->GetMove()%2==0  )
		DrawPacMan(Px + 20 - 9, Py +20 - 8, B->pac[0]->Radius(), YELLOW,-3.0);
		else if(B->pac[0]->GetMove()%2==1)
					DrawPacMan2(Px + 20 - 9, Py + 20 - 8, B->pac[0]->Radius() , YELLOW,-3.0);

	}
	if(B->pac[pacman]->movement==4){
	if(B->pac[0]->GetMove()%2==0)
		DrawPacMan(Px + 20 - 9, Py +20 - 8, B->pac[0]->Radius() , YELLOW,1.5);
	else if(B->pac[0]->GetMove()%2==1)
						DrawPacMan2(Px + 20 - 9, Py + 20 - 8, B->pac[0]->Radius(), YELLOW,1.5);}

	// Pacman Movement
	//cout<<"x_pixel = "<<B->pac[pacman]->getX()<<" y_pixel= "<<B->pac[pacman]->getY()<<endl;
	cout<<"Pacman: x_cell = "<<Px/20<<" y_cell= "<<Py/20<<endl;
	//x = pac[pacman]->GetMidX();
	string score="Score = ";
	DrawString(280/14, 680, score += B->pac[pacman]->Score(), colors[WHITE]);

	//B->pac[pacman]->RemovePebbles();
	if(B->pac[pacman]->RemovePebbles()==1){
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
		exit(1); // exit the program when escape key is pressed.
		//pac[0]->Reset();
	}
	if(key==80 or key==80 + 32){  // P
		//B->pac[0]->movement=0;
		B->Pause(0);
		//B->Frightn(1);
	}
	if(key==82 or key==82 + 32){  // R
			//B->pac[0]->Reset();
		if(B->GetLife()==0 or B->pac[0]->Pebbles()==0){
			B->All_Reset();
			B->pac[board]->Start();
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
	//for(int i=0;i<20000000;i++);
	if(B->GetLife()>0 and B->pac[0]->Pebbles()>0){
	if(B->Pause()==0){
	B->pac[pacman]->Movement();
	B->pac[pinky]->Search();

	if(B->Frightn()==0){
	B->pac[blinky]->Movement();
	B->pac[pinky]->Movement();
	B->pac[inky]->Movement();
	B->pac[clyde]->Movement();}
	else if(B->Frightn()==1){
		B->pac[blinky]->Movement2();
		B->pac[pinky]->Movement2();
		B->pac[inky]->Movement2();
		B->pac[clyde]->Movement2();

	}
	B->pac[0]->Move(1);}}
	if(B->pac[pacman]->Pebbles()==241){
		B->pac[pinky]->Start();
	}
	if(B->pac[pacman]->Pebbles()==170){
			B->pac[inky]->Start();
		}
	if(B->pac[pacman]->Pebbles()==72){
			B->pac[clyde]->Start();
		}
	if(B->Frightn()==1)
		B->Count2();
	B->Collision();
// once again we tell the library to call our Timer function after next 1000/FPS
	glutPostRedisplay();
	glutTimerFunc(100.0, Timer, 0);

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
	int width = 560, height = 720; // i have set my window size to be 560 x 720
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 500); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("CP's Pacman"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

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
