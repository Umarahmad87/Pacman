/*
 * Ghost.h
 *
 *  Created on: Apr 30, 2016
 *      Author: umar
 */

#ifndef GHOST_H_
#define GHOST_H_

#include <GL/glut.h>
#include <iostream>
#include <set>
#include "Board.h"
#include "util.h"
enum Movements { Left , Right , up , down  };
class Ghost:public Board{
	int move_r;
	int Frightened;
public:

	Ghost(int x=13,int y=21):Board(x,y){
		movement=1;
		move_r=down;
		Frightened=0;
			}
	void Start(int n=0){
		x_cell=13;
		y_cell=21;
		x_axis=x_cell*20.0;
		y_axis=y_cell*20.0;
	}
	void Frightn(int n){
		Frightened = n;
	}
	int Frightn(){
		return Frightened;
	}
	void Load_Level(int lev){
		if(lev==0 or lev==1){
					for(int i=0;i<36;i++){
								for(int j=0;j<28;j++){
									board_array[i][j]=board_array1[i][j];
								}}

				}
			else if(lev==2 or lev==3){
						for(int i=0;i<36;i++){
									for(int j=0;j<28;j++){
										board_array[i][j]=board_array2[i][j];
									}}

					}
	}
	bool Block_left(){
		int x,y;
			x=ceil(x_cell);
			y=y_cell;
			if(board_array[35-y][x-1]==PEBB or board_array[35-y][x-1]==0 or board_array[35-y][x-1]==SB or board_array[35-y][x-1]==VE or board_array[35-y][x-1]==GH )
				return 0;
			return 1;
	}
	bool Block_right(){
		int x,y;
		x=floor(x_cell);
		y=y_cell;
		if(board_array[35-y][x+1]==PEBB or board_array[35-y][x+1]==0 or board_array[35-y][x+1]==SB or board_array[35-y][x+1]==VE or board_array[35-y][x+1]==GH )
			return 0;
		return 1;
	}
	bool Block_up(){
		int x,y;
		x=x_cell;
		y=floor(y_cell);
		if(board_array[35-y-1][x]==PEBB or board_array[35-y-1][x]==0 or board_array[35-y-1][x]==SB or board_array[35-y-1][x]==VE  or board_array[35-y-1][x]==GH )
			return 0;
		return 1;
	}
	bool Block_down(){
		int x,y;
		x=x_cell;
		y=ceil(y_cell);
		if(board_array[35-y+1][x]==PEBB or board_array[35-y+1][x]==0 or board_array[35-y+1][x]==SB or board_array[35-y+1][x]==VE or board_array[35-y+1][x]==GH)
			return 0;
		return 1;
	}
	void Reset(int x,int y){
		x_cell=x;
		y_cell=y;
		x_axis=x_cell*xcellsize;
		y_axis=y_cell*ycellsize;
		move_r=up;
	}
	void Search(int px,int py){
		int x,y;
		x=x_cell;
		y=y_cell;
		static int hh=0;
		record=move_r;
		cout<<" hh= "<<hh<<endl;
		/*if(board_array[35-y][x]==GH){
			if((hh%4==0 or hh%4==1) and board_array[35-y-1][x]==GH and Block_up()==1)
			y_cell +=1;
			else if((hh%4==2 or hh%4==3) and board_array[35-y+1][x]==GH and Block_down()==1)
				y_cell -=1;
			y_axis=20*y_cell;
		}*/
		hh++;
		cout<<"Ghost x and y :"<<x<<" , "<<y<<endl;
		cout<<"Pacman x and y :"<<px<<" , "<<py<<endl;
		for(int xx=x,j=1;xx<=28;xx++,j++){
			if(x+j==px and y==py and this->Block_right()==0 and move_r!=Left){
						x_cell +=1;
						x_axis=20*x_cell;
						move_r=Right;
						return;
						break;
					}}
		for(int xx=x,j=1; xx>0 ;xx--,j++){
					if(x-j==px and y==py and this->Block_left()==0 and move_r!=Right){
								x_cell -=1;
								x_axis=20*x_cell;
								move_r=Left;
								return;
								break;
							}}
		for(int yy=y,j=1; yy>0 ;yy--,j++){
							if(x==px and y-j==py and this->Block_down()==0 and move_r!=up){
										y_cell -=1;
										y_axis=20*y_cell;
										move_r=down;
										return;
										break;
									}}
		for(int yy=y,j=1; yy<36 ;yy++,j++){
							if(x==px and y+j==py and this->Block_up()==0 and move_r!=down){
										y_cell +=1;
										y_axis=20*y_cell;
										move_r=up;
										return;
										break;
									}}

		Movement();

	}
	void Movement(){
		int x,y;
		x=x_cell;
		y=y_cell;
		if(this->x_cell==0){
			x_cell=27;
			x_axis=20*x_cell;
			x_cell -=1;
			x_axis=20*x_cell;
			move_r=Left;}
		else if(this->x_cell==27){
							x_cell=0;
							x_axis=20*0;
							x_cell +=1;
							x_axis=20*x_cell;
							move_r=Right;
						}

		// Simple End
		 if(this->Block_right()==1 and this->Block_down()==1){
				if(move_r==down){
					if(Block_left()==0){
						x_cell -= 1;
						x_axis = x_cell * 20.0;
						move_r = Left;

					}}
				else if(move_r==Right){
									if(Block_up()==0){
										y_cell += 1;
										y_axis = y_cell * 20.0;
										move_r = up;

									}}
		}
		else if(this->Block_left()==1 and this->Block_up()==1){
						if(move_r==Left){
							if(Block_down()==0){
								y_cell -= 1;
								y_axis = y_cell * 20.0;
								move_r = down;

							}}
						else if(move_r==up){
											if(Block_right()==0){
												x_cell += 1;
												x_axis = x_cell * 20.0;
												move_r = Right;

											}}
				}
		else if(this->Block_left()==1 and this->Block_down()==1){
						if(move_r==down){
							if(Block_right()==0){
								x_cell += 1;
								x_axis = x_cell * 20.0;
								move_r = Right;

							}}
						else if(move_r==Left){
											if(Block_up()==0){
												y_cell += 1;
												y_axis = y_cell * 20.0;
												move_r = up;

											}}
				}

		else if(this->Block_right()==1 and this->Block_up()==1){
						if(move_r==up){
							if(Block_left()==0){
								x_cell -= 1;
								x_axis = x_cell * 20.0;
								move_r = Left;

							}}
						else if(move_r==Right){
											if(Block_down()==0){
												y_cell -= 1;
												y_axis = y_cell * 20.0;
												move_r = down;

											}}
				}
		// Special Condition 1
		else if(this->Block_left()==0 and this->Block_right()==0){
			if(move_r==up ){
						int ran=rand()%3;
					if(ran==0){
						move_r=Left;
						x_cell -= 1;
						x_axis = x_cell * 20.0;
					}
					else if (ran==1){
						move_r=Right;
						x_cell += 1;
						x_axis = x_cell * 20.0;

					}
					else if(ran==2 and Block_up()==0){
						move_r=up;
						y_cell += 1;
						y_axis=y_cell * 20.0;}
					}
			else if(move_r==down){
								int ran=rand()%3;
							if(ran==0){
								move_r=Left;
								x_cell -= 1;
								x_axis = x_cell * 20.0;
							}
							else if (ran==1){
								move_r=Right;
								x_cell += 1;
								x_axis = x_cell * 20.0;

							}
							else if(ran==2 and Block_down()==0){
								move_r=down;
								y_cell -= 1;
								y_axis=y_cell * 20.0;}}
			else if(Block_up()==1 and Block_down()==1){
				if(move_r==Left) {
					move_r=Left;
					x_cell -= 1;
					x_axis = x_cell * 20.0;
				}
				else if(move_r==Right){
					move_r=Right;
					x_cell += 1;
					x_axis = x_cell * 20.0;
				}
			}
			else if(move_r==Left){
				if(Block_up()==0){
					int ran2=rand()%2;
					if(ran2==0){
						move_r=Left;
						x_cell -= 1;
						x_axis = x_cell * 20.0;}
					else if (ran2==1){
						move_r=up;
						y_cell += 1;
						y_axis = y_cell * 20.0;}
				}
				else if(Block_down()==0){
								int ran2=rand()%2;
								if(ran2==0){
								move_r=Left;
								x_cell -= 1;
								x_axis = x_cell * 20.0;}
								else if (ran2==1){
									move_r=down;
									y_cell -= 1;
									y_axis = y_cell * 20.0;}
								}

			}
			else if(move_r==Right){
				if(Block_up()==0){
					int ran2=rand()%2;
					if(ran2==0){
						move_r=Right;
						x_cell += 1;
						x_axis = x_cell * 20.0;}
					else if (ran2==1){
						move_r=up;
						y_cell += 1;
						y_axis = y_cell * 20.0;}
				}
				else if(Block_down()==0){
								int ran2=rand()%2;
								if(ran2==0){
								move_r=Right;
								x_cell += 1;
								x_axis = x_cell * 20.0;}
								else if (ran2==1){
									move_r=down;
									y_cell -= 1;
									y_axis = y_cell * 20.0;}
								}

			}
		}

		 // Special Condition End 1

		 // Up Down Condition starts
		else if(this->Block_up()==0 and this->Block_down()==0){
			if(move_r == up or move_r==Right) {
			if(Block_right()==0 and Block_left()==0){
				int ran3=rand()%3;
				if(ran3==0){
					move_r=up;
					y_cell += 1;
					y_axis = y_cell * 20.0;
				}
				else if(ran3==1){
					move_r=Right;
					x_cell += 1;
					x_axis=x_cell * 20.0;
				}
				else if(ran3==2){
					move_r=Left;
					x_cell -= 1;
					x_axis=x_cell * 20.0;
				}
			}
			else if(Block_right()==1 and Block_left()==1){
				move_r=up;
				y_cell += 1;
				y_axis = y_cell * 20.0;}
			else if(Block_right()==1 or Block_left()==1){
							move_r=up;
							y_cell += 1;
							y_axis = y_cell * 20.0;}

			}
			else if(move_r == down or move_r==Left) {
						if(Block_right()==0 and Block_left()==0){
							int ran3=rand()%3;
							if(ran3==0){
								move_r=down;
								y_cell -= 1;
								y_axis = y_cell * 20.0;
							}
							else if(ran3==1){
								move_r=Right;
								x_cell += 1;
								x_axis=x_cell * 20.0;
							}
							else if(ran3==2){
								move_r=Left;
								x_cell -= 1;
								x_axis=x_cell * 20.0;
							}
						}
						else if(Block_right()==1 and Block_left()==1){
										move_r=down;
										y_cell -= 1;
										y_axis = y_cell * 20.0;}
						else if(Block_right()==1 or Block_left()==1){
										move_r=down;
										y_cell -= 1;
										y_axis = y_cell * 20.0;}}
			/*	int ran=rand()%2;
							if(ran==0){
								move_r=up;
								y_cell += 1;
								y_axis = y_cell * 20.0;
							}
							else if (ran==1){
								move_r=down;
								y_cell -= 1;
								y_axis = y_cell * 20.0;

							}*/
				}
		 // Up Down Condition Ends
		// Extra
		else if(this->Block_left()==1 and this->Block_right()==1){
			if(move_r==up){
				if(Block_up()==0){
				y_cell += 1;
				y_axis=y_cell*20;
				move_r=up;}
			}
			else if(move_r == down){
				if(Block_down()==0){
				y_cell -= 1;
				y_axis=y_cell*20;
				move_r=down;}
			}
		}
		else if(this->Block_up()==1 and this->Block_down()==1){
					if(move_r== Left ){
						if(Block_left()==0){
						x_cell -= 1;
						x_axis=x_cell*20;
						move_r= Left;}
					}
					else if(move_r == Right){
						if(Block_right()==0){
						y_cell += 1;
						x_axis=x_cell*20;
						move_r=Right;}
					}
				}
	}
	void Movement2(){
		if(move_r==Left and Block_left()==0){
					if(Block_left()==0){
						x_cell -= 1;
						x_axis = x_cell * 20.0;
						move_r= Left;
					}}
				else if(move_r==Right and Block_right()==0){
					x_cell += 1;
					x_axis = x_cell * 20.0;

					move_r= Right;
				}
				else if(move_r==up and Block_up()==0){
							y_cell += 1;
							y_axis = y_cell * 20.0;
							move_r= up;
						}
				else if(move_r==down and Block_down()==0){
							y_cell -= 1;
							y_axis = y_cell * 20.0;
							move_r= down;
						}
				else
					Movement();
	}

};

#endif /* GHOST_H_ */
