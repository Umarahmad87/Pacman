/*
 * Board.h
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include <GL/glut.h>
#include <iostream>
#include "util.h"
using namespace std;




class Board {
protected:
	int pebbles_left;
	int xcellsize, ycellsize;
	int lwidth;
	float cwidth;
	//array for eating
	int tp_array[31][28];
	ColorNames pcolor, bcolor, gcolor;

	float x_axis;
		float y_axis;
		float x_cell;
		float y_cell;
		int Mov;
public:
	int movement;

	static const int BOARD_X;
	static const int BOARD_Y;
	Board(int xsize =20 , int ysize= 20 );

	virtual ~Board(void);
	virtual int Radius();
	//draw the board
	virtual void Draw(void);
	virtual string Score();
	virtual void Score(int);
	virtual void Reset();
	static int GetBoardX() {
		return BOARD_X;
	}
	static int GetBoardY() {
		return BOARD_Y;
	}
	int GetMidX() {
		return BOARD_Y * xcellsize / 2.0;
	}
	int GetMidY() {
		return BOARD_X * ycellsize / 2.0;
	}
	int GetCellSize() {
		return xcellsize;
	}
	void GetInitPacmanPosition(int &x, int &y) {
		x = 14 * xcellsize;
		y = 9 * ycellsize + ycellsize / 2;
	}
	void GetInitPinkyPosition(int &x, int &y) {
		x = 11 * xcellsize/* - xcellsize / 2.0*/;
		y = 18 * ycellsize - ycellsize / 2.0;
	}
	void GetInitTextPosition(int &x, int &y) {
		x = 13 * xcellsize;
		y = 14 * ycellsize;
	}
	void xyCell(){
		cout<<"xcell size="<<xcellsize<<endl;
		cout<<"ycell size="<<ycellsize<<endl;
	}
	void Xpp();
		void Xmm();
		void Ypp();
		void Ymm();
		virtual void RemovePebbles();
		void GetPixel(float &x, float &y){
				x=x_axis;
				y=y_axis;
				cout<<"x_cell="<<x_cell<<" y_cell="<<y_cell<<endl;

		}
		void GetCell(float &x, float &y){
					x=x_cell;
					y=y_cell;
					cout<<"x_cell="<<x_cell<<" y_cell="<<y_cell<<endl;
			}
		float getX(){
				return x_axis;
			}
		float getY(){
				return y_axis;
				}
		int	GetMove(){
				return Mov;
			}
		void Move(int n){
			Mov+=n;
		}
//	int GetMidx
};

class Pacman:public Board {
	int score;
	int radius;
public:
	//static int Move=0;
	Pacman(int x=13, int y=9);
	void RemovePebbles();
	void Draw();
	string Score();
	void Score(int);
	int Radius();
	void Reset();
	virtual ~Pacman(){

	}


};
#endif
