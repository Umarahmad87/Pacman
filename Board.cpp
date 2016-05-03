/*
 * Board.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */

#include "Board.h"
#include <cstdio>

const int Board::BOARD_Y = 28;
const int Board::BOARD_X = 36;
//here's pacman's crazy board

// Note that all these enum constants from NILL onwards
// have been given numbers in increasing order
// e.g. NILL=0, TLC=1, TRC=2, BLC=3, BRC=4, and so on
// and these numbers are represented in the board array...

bool Board::RemovePebbles(){
		cout<<"Board::Pebbles"<<endl;
	}
void Board::Start(){
	for(int i=0;i<36;i++){
			for(int j=0;j<28;j++){
					if(board_array[35-i][j]==0)
						board_array[35-i][j]=16;
					if(i==35-6 and j==1)
						board_array[35-i][j]=SB;
					if(i==35-6 and j==26)
							board_array[35-i][j]=SB;
					if(i==35-26 and j==1)
							board_array[35-i][j]=SB;
					if(i==35-26 and j==26)
							board_array[35-i][j]=SB;
			}}
}
bool Pacman::RemovePebbles(){
	//cout<<"Pacman::Pebbles"<<endl;
		int x,y;
		x=x_cell;
		y=y_cell;
	if(board_array[35-y][x]==PEBB){
		board_array[35-y][x]=0;
		Score(10);
		this->pebbles_left--;
		return 0;
	}
	if(board_array[35-y][x]==SB){
			board_array[35-y][x]=0;
			Score(100);
			this->pebbles_left--;
			return 1;
		}
	return 0;
	}
void Pacman::Draw(){
	//DrawPacMan(Px + 20 - 9, Py +20 - 8, 16, YELLOW);
}
void Board::Xpp(){

		//x_cell += 1;
	int x,y;
	x=floor(x_cell);
	y=y_cell;
	//cout<<" Board = "<<board_array[35-y][x+1]<<endl;
	if(board_array[35-y][x+1]==PEBB or board_array[35-y][x+1]==0 or board_array[35-y][x+1]==SB or board_array[35-y][x+1]==VE ){
		x_axis += increment;
		x_cell = x_axis/xcellsize;}
		//y_cell = y_axis/20.0;
}
void Board::Xmm(){
	//	x_cell -= 1;
	int x,y;
	x=ceil(x_cell);
	y=y_cell;
	//cout<<" Board = "<<board_array[35-y][x-1]<<endl;
	if(board_array[35-y][x-1]==PEBB or board_array[35-y][x-1]==0 or board_array[35-y][x-1]==SB or board_array[35-y][x-1]==VE ){
		x_axis -= increment;
		x_cell = x_axis / xcellsize;	}
		//y_cell = y_axis/20.0;
}
void Board::Ypp(){
	//	y_cell += 1;
	int x,y;
	x=x_cell;
	y=floor(y_cell);
	//cout<<" Board = "<<board_array[35-y-1][x]<<endl;
	if(board_array[35-y-1][x]==PEBB or board_array[35-y-1][x]==0 or board_array[35-y-1][x]==SB or board_array[35-y-1][x]==VE ){
		y_axis += increment;
		y_cell = y_axis/ycellsize;}
		}
void Board::Ymm(){
		int x,y;
		x=x_cell;
		y=ceil(y_cell);
		//cout<<" Board = "<<board_array[35-y+1][x]<<endl;
		if(board_array[35-y+1][x]==PEBB or board_array[35-y+1][x]==0 or board_array[35-y+1][x]==SB or board_array[35-y+1][x]==VE){
		y_axis -= increment;
		y_cell = y_axis/ycellsize;}
		}
string Board::Score(){ return NULL;}
string Pacman::Score(){
	int i=0,A[10],count=0;
	int n=score;
	while(n!=0)
			{A[i]=n%10;
			n=n/10;
			count=count+1;
			i++;}
		char C[count];
		int p=0;
		for(int u=count-1;u>=0;u--)
			{C[p]=char(A[u]+48);
			p=p+1;
			}
		for(int j=0;j<count;j++)
			cout<<C[j];
		string s1;
		s1=C;
		//cout<<endl<<s1;
		return s1;}
void Board::Score(int n){}
void Pacman::Score(int n){ score+=n;}
int Board::Radius(){ return 20;}
int Pacman::Radius(){ return radius;}
void Board::Reset(int x,int y){}
void Pacman::Reset(int x,int y){
	x_cell=13;
	y_cell=9;
	x_axis=x_cell*xcellsize;
	y_axis=y_cell*ycellsize;
	if(this->pebbles_left==246) score=0;
	movement=0;
}
bool Board::Block_left(){
	int x,y;
		x=ceil(x_cell);
		y=y_cell;
		if(board_array[35-y][x-1]==PEBB or board_array[35-y][x-1]==0 or board_array[35-y][x-1]==SB or board_array[35-y][x-1]==VE )
			return 0;
		return 1;
}
bool Board::Block_right(){
	int x,y;
	x=floor(x_cell);
	y=y_cell;
	if(board_array[35-y][x+1]==PEBB or board_array[35-y][x+1]==0 or board_array[35-y][x+1]==SB or board_array[35-y][x+1]==VE )
		return 0;
	return 1;
}
bool Board::Block_up(){
	int x,y;
	x=x_cell;
	y=floor(y_cell);
	if(board_array[35-y-1][x]==PEBB or board_array[35-y-1][x]==0 or board_array[35-y-1][x]==SB or board_array[35-y-1][x]==VE )
		return 0;
	return 1;
}
bool Board::Block_down(){
	int x,y;
	x=x_cell;
	y=ceil(y_cell);
	if(board_array[35-y+1][x]==PEBB or board_array[35-y+1][x]==0 or board_array[35-y+1][x]==SB or board_array[35-y+1][x]==VE)
		return 0;
	return 1;
}
void Board::Search(){

}
// Destructor
Board::~Board(void) {}

//Constructor
Board::Board(int x_i, int y_i) {
	xcellsize = 20;
	ycellsize = 20;
	lwidth = 3; // line width
	cwidth = 3; // curve widh
	pcolor = CHOCOLATE;
	bcolor =  DARK_BLUE;
	gcolor = PINK;
	Mov=0;
//set up board

	movement  =  1;
		x_cell=x_i;
		y_cell=y_i;
		x_axis=x_cell*xcellsize; /*280*/
		y_axis=y_cell*ycellsize;
		pebbles_left=246;
}
Pacman::Pacman(int x_pos, int y_pos):Board(x_pos,y_pos)
{		radius=16;
		/*192*/
		score=0;
		increment=20;
		//pebbles_left=242;

}
void Board::Movement(){

}
void Pacman::Movement(){

	if(movement==1){

			Xmm();
			if(this->x_cell==0){
						x_cell=27;
						x_axis=20*x_cell;
						movement=1;
					}
			//cout<<"Movement = Left "<<endl;
			}
			if(movement==2){
			Xpp();
			if(this->x_cell==27){
					x_cell=0;
					x_axis=20*0;
					movement=2;
				}
			//cout<<"Movement = Right "<<endl;
			}
			if(movement==3){
			Ypp();
			//cout<<"Movement = Up "<<endl;
			}
			if(movement==4){
			Ymm();
			//cout<<"Movement = Down "<<endl;
			}
}
void Board::Movement2(){ }
void Board::Draw(void) {
	glColor3f(0, 0, 1);
	glPushMatrix();

	int offset = xcellsize / 2.0, roffset = 2;

	for (int i = BOARD_X - 1, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_Y; j++, x += ycellsize) {
//			cout << " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
			case NILL:	//resets the pebble array
						// Prohibitive Empty space
				break;
			case TLC: // Left corner top
				Torus2d(x, y + xcellsize, 270, 90,
						(float) xcellsize / 2.0 - cwidth, cwidth, 390,
						colors[bcolor]);
				break;
			case TRC: //Right corner top
				Torus2d(x + xcellsize, y + ycellsize, 180, 90,
						(float) xcellsize / 2.0 - cwidth, cwidth, 390,
						colors[bcolor]);
				break;
			case BLC: // Left corner bottom
				Torus2d(x, y, 0, 90, (float) xcellsize / 2.0 - cwidth, cwidth,
						390, colors[bcolor]);
				break;
			case BRC: //Right corner bottom
				Torus2d(x + xcellsize, y, 90, 90,
						(float) xcellsize / 2.0 - cwidth, cwidth, 390,
						colors[bcolor]);
				break;
			case BT: // Border Drawing top
				DrawLine(x, y + xcellsize, x + xcellsize, y + ycellsize, lwidth,
						colors[bcolor]);
				DrawLine(x, y + xcellsize - offset, x + xcellsize,
						y + ycellsize - offset, lwidth, colors[bcolor]);
				break;
			case BB: // Border Drawing bottom
				DrawLine(x, y, x + xcellsize, y, lwidth, colors[bcolor]);
				DrawLine(x, y + offset, x + xcellsize, y + offset, lwidth,
						colors[bcolor]);
				break;
			case BL: // Border Drawing left
				DrawLine(x, y, x, y + ycellsize, lwidth, colors[bcolor]);
				DrawLine(x + offset, y, x + offset, y + ycellsize, lwidth,
						colors[bcolor]);
				break;
			case BR: // Border Drawing right
				DrawLine(x + xcellsize, y, x + xcellsize, y + ycellsize, lwidth,
						colors[bcolor]);
				DrawLine(x - offset + xcellsize, y, x - offset + xcellsize,
						y + ycellsize, lwidth, colors[bcolor]);
				break;
			case HL: // Horizontal line
				DrawLine(x, y + ycellsize / 2, x + xcellsize, y + ycellsize / 2,
						lwidth, colors[bcolor]);
				break;
			case VL: // Vertical line
				DrawLine(x + xcellsize / 2, y, x + xcellsize / 2, y + ycellsize,
						lwidth, colors[bcolor]);
				break;
			case GG: // Ghost Gate
				DrawLine(x, y + ycellsize / 2, x + xcellsize,
						y + ycellsize / 2);
				break;
			case BTLC: // Border Left corner top
				Torus2d(x, y + xcellsize, 270, 90, (float) xcellsize - cwidth,
						cwidth, 390, colors[bcolor]);
				Torus2d(x, y + xcellsize, 270, 90,
						(float) xcellsize / 2.0 - cwidth, cwidth, 390,
						colors[bcolor]);
				break;
			case BTRC: //Border Right corner top
				Torus2d(x + xcellsize, y + ycellsize, 180, 90,
						(float) xcellsize - cwidth, cwidth, 390,
						colors[bcolor]);
				Torus2d(x + xcellsize, y + ycellsize, 180, 90,
						(float) xcellsize / 2.0 - cwidth, cwidth, 390,
						colors[bcolor]);
				break;
			case BBLC: //Border Left corner bottom
				Torus2d(x, y, 0, 90, (float) xcellsize - cwidth, cwidth, 390,
						colors[bcolor]);
				Torus2d(x, y, 0, 90, (float) xcellsize / 2.0 - cwidth, cwidth,
						390, colors[bcolor]);
				break;
			case BBRC: //Border Right corner bottom
				Torus2d(x + xcellsize, y, 90, 90,
						(float) xcellsize / 2.0 - cwidth, cwidth, 390,
						colors[bcolor]);
				Torus2d(x + xcellsize, y, 90, 90, (float) xcellsize - cwidth,
						cwidth, 390, colors[bcolor]);
				break;
			case PEBB: // Pebbles
				DrawCircle(x + xcellsize / 2, y + ycellsize / 2, xcellsize / 4,
						colors[pcolor]);
				break;
			case VE: // Valid Empty
				break;
			case SB: // Solid Ball
				DrawCircle(x + xcellsize / 2, y + ycellsize / 2, xcellsize / 2,
						colors[pcolor]);
				break;
			case SBL: // Staright line with Left corner bottom
				DrawLine(x, y + xcellsize, x + xcellsize, y + ycellsize, lwidth,
						colors[bcolor]);
				Torus2d(x, y, 0, 90, (float) xcellsize / 2.0 - cwidth, cwidth,
						390, colors[bcolor]);
				break;
			case SBR: // StrRight corner bottom
				DrawLine(x, y + xcellsize, x + xcellsize, y + ycellsize, lwidth,
						colors[bcolor]);
				Torus2d(x + xcellsize, y, 90, 90,
						(float) xcellsize / 2.0 - cwidth, cwidth, 390,
						colors[bcolor]);
				break;
				break;
			case GH: // Ghoust House
				;
				break;
			case VTL: // Left corner top
				DrawLine(x + xcellsize, y, x + xcellsize, y + ycellsize, lwidth,
						colors[bcolor]);
				Torus2d(x, y + xcellsize, 270, 90,
						(float) xcellsize / 2.0 - cwidth, cwidth, 390,
						colors[bcolor]);
				break;
			case VTR: //Right corner top
				DrawLine(x, y, x, y + ycellsize, lwidth, colors[bcolor]);

				Torus2d(x + xcellsize, y + ycellsize, 180, 90,
						(float) xcellsize / 2.0 - cwidth, cwidth, 390,
						colors[bcolor]);
				break;
			case VBL: // Left corner bottom
				DrawLine(x + xcellsize, y, x + xcellsize, y + ycellsize, lwidth,
						colors[bcolor]);
				Torus2d(x, y, 0, 90, (float) xcellsize / 2.0 - cwidth, cwidth,
						390, colors[bcolor]);
				break;
			case VBR: //Right corner bottom
				DrawLine(x, y, x, y + ycellsize, lwidth, colors[bcolor]);

				Torus2d(x + xcellsize, y, 90, 90,
						(float) xcellsize / 2.0 - cwidth, cwidth, 390,
						colors[bcolor]);
				break;
			}
		}
	}
	glPopMatrix();
}


