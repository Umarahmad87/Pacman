/*
 * Board2.h
 *
 *  Created on: Apr 30, 2016
 *      Author: umar
 */

#ifndef BOARD2_H_
#define BOARD2_H_
#include <fstream>
#include <cstring>
float Distance(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
class Board2 {
int index;
int Frightened;
int count;
int life;
bool pause;
int Highscore;
public:
	Board **pac;
	int level;
Board2() {
	index=0;
	pac=new Board *[6];
	Frightened=0;
	count=0;
	pause=0;
	life=3;
	level=0;
	ifstream in;
	in.open("HighScore.txt");
	in>>Highscore;
	if(Highscore==NULL){
		Highscore=10;
		ofstream enter;
		enter.open("HighScore.txt");
		enter<<Highscore;
	}
	cout<<"High Score="<<Highscore<<endl<<endl;



}
void Load_Level(int lev){
	this->pac[0]->Load_Level(lev);
	this->pac[1]->Load_Level(lev);
	this->pac[2]->Load_Level(lev);
	this->pac[3]->Load_Level(lev);
	this->pac[4]->Load_Level(lev);
	this->pac[5]->Load_Level(lev);
}
void Life_Reset(){
	life=3;
}
void All_Reset(){
	this->pac[0]->Pebbles_Reset();
	this->pac[0]->Reset(13,9);
	this->pac[1]->Reset(13,18);
	this->pac[3]->Reset(13,21);
	this->pac[4]->Reset(15,18);
	this->pac[5]->Reset(11,18);
	this->pac[2]->SetColor(level);
	this->Frightn(0);

}

void HighScore(string n){
	ofstream out;
	int u=this->pac[0]->score2();
	out.open("HighScore.txt");
	if(Highscore<u){
		out<<u;
		Highscore=u;}
	else out<<Highscore;

}
string HighScore(){
	int i=0,A[10],count=0;
		int n=Highscore;
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
			string s1;
			s1=C;
			return s1;}
int GetLife(){
	return life;
}
void Pause(int){
	pause=not(pause);
}
bool Pause(){
	return pause;
}
void insert(Board &B){
	if(index<7){
	pac[index++]=&B;
	cout<<"index="<<index<<endl;}
	else cout<<"Out of Range";
}
void Frightn(int n){
	count=0;
	Frightened = n;
	pac[1]->Frightn(n);
	pac[3]->Frightn(n);
	pac[4]->Frightn(n);
	pac[5]->Frightn(n);
}
int Frightn(){
	return Frightened;
}
int Count2(){
	int M=160;
	if(Frightened==1){
	for(int j=0;j<M;j++){
		if(count%M<=M/2){ count++; return 1;}
		else if(count%M>M/2){
			Frightened=0;
			pac[1]->Frightn(0);
			pac[3]->Frightn(0);
			pac[4]->Frightn(0);
			pac[5]->Frightn(0);
			count++; return 0;
		}
	}
	count++;}
	return 0;}
int Collision(){

	if((pac[0]->getX()/20==pac[1]->getX()/20 and pac[0]->getY()/20==pac[1]->getY()/20) or ((pac[0]->getX()/20)+1==pac[1]->getX()/20 and pac[0]->getY()/20==pac[1]->getY()/20 ) or ((pac[0]->getX()/20)-1==pac[1]->getX()/20 and pac[0]->getY()/20==pac[1]->getY()/20) or(pac[0]->getX()/20==pac[1]->getX()/20 and (pac[0]->getY()/20)+1==pac[1]->getY()/20) or (pac[0]->getX()/20==pac[1]->getX()/20 and (pac[0]->getY()/20)-1==pac[1]->getY()/20) ){


		if(pac[1]->Frightn()==0){
					pac[0]->Reset(13,9);
					life--;
					for(int i=0;i<70000000;i++);
					return 2;
				}
				else if(pac[1]->Frightn()==1){
					pac[1]->Reset(13,20);
					pac[1]->Frightn(0);
					for(int i=0;i<70000000;i++);
					//pac[1]->Start(0);
					pac[0]->Score(200);
					return 1;
				}
	}
	if((pac[0]->getX()/20==pac[3]->getX()/20 and pac[0]->getY()/20==pac[3]->getY()/20) or ((pac[0]->getX()/20)+1==pac[3]->getX()/20 and pac[0]->getY()/20==pac[3]->getY()/20 ) or ((pac[0]->getX()/20)-1==pac[3]->getX()/20 and pac[0]->getY()/20==pac[3]->getY()/20 ) or(pac[0]->getX()/20==pac[3]->getX()/20 and (pac[0]->getY()/20)+1==pac[3]->getY()/20) or (pac[0]->getX()/20==pac[3]->getX()/20 and (pac[0]->getY()/20)-1==pac[3]->getY()/20)){
		if(pac[3]->Frightn()==0){
					pac[0]->Reset(13,9);
					life--;
					for(int i=0;i<70000000;i++);
					return 2;
				}
				else if(pac[3]->Frightn()==1){
					pac[3]->Reset(13,20);
					pac[3]->Frightn(0);
					for(int i=0;i<70000000;i++);
					//pac[3]->Start(0);
					pac[0]->Score(200);
					return 1;
				}
		}
	if((pac[0]->getX()/20==pac[4]->getX()/20 and pac[0]->getY()/20==pac[4]->getY()/20) or ((pac[0]->getX()/20)+1==pac[4]->getX()/20 and pac[0]->getY()/20==pac[4]->getY()/20 ) or ((pac[0]->getX()/20)-1==pac[4]->getX()/20 and pac[0]->getY()/20==pac[4]->getY()/20 ) or(pac[0]->getX()/20==pac[4]->getX()/20 and (pac[0]->getY()/20)+1==pac[4]->getY()/20) or (pac[0]->getX()/20==pac[4]->getX()/20 and (pac[0]->getY()/20)-1==pac[4]->getY()/20)){
		if(pac[4]->Frightn()==0){
					pac[0]->Reset(13,9);
					life--;
					for(int i=0;i<70000000;i++);
					return 2;
				}
				else if(pac[4]->Frightn()==1){
					pac[4]->Reset(13,20);
					pac[4]->Frightn(0);
					for(int i=0;i<70000000;i++);
					//pac[4]->Start(0);
					pac[0]->Score(200);
					return 1;
				}
		}
	if((pac[0]->getX()/20==pac[5]->getX()/20 and pac[0]->getY()/20==pac[5]->getY()/20) or ((pac[0]->getX()/20)+1==pac[5]->getX()/20 and pac[0]->getY()/20==pac[5]->getY()/20 ) or ((pac[0]->getX()/20)-1==pac[5]->getX()/20 and pac[0]->getY()/20==pac[5]->getY()/20 ) or(pac[0]->getX()/20==pac[5]->getX()/20 and (pac[0]->getY()/20)+1==pac[5]->getY()/20) or (pac[0]->getX()/20==pac[5]->getX()/20 and (pac[0]->getY()/20)-1==pac[5]->getY()/20)){
		if(pac[5]->Frightn()==0){
					pac[0]->Reset(13,9);
					life--;
					for(int i=0;i<70000000;i++);
					return 2;
				}
				else if(pac[5]->Frightn()==1){
					pac[5]->Reset(13,20);
					pac[5]->Frightn(0);
					for(int i=0;i<70000000;i++);
					//pac[5]->Start(0);
					pac[0]->Score(200);
					return 1;
				}
		}


	return 0;


	/*cout<<"Distance 1="<<(Distance(pac[0]->getX(),pac[0]->getY(),pac[1]->getX(),pac[1]->getY()))<<endl;
	cout<<"Distance 2="<<(Distance(pac[0]->getX(),pac[0]->getY(),pac[3]->getX(),pac[3]->getY()))<<endl;
	cout<<"Distance 3="<<(Distance(pac[0]->getX(),pac[0]->getY(),pac[4]->getX(),pac[4]->getY()))<<endl;
	cout<<"Distance 4="<<(Distance(pac[0]->getX(),pac[0]->getY(),pac[5]->getX(),pac[5]->getY()))<<endl;*/
	/*double kk=10.0;
	if(Distance(pac[0]->getX(),pac[0]->getY(),pac[1]->getX(),pac[1]->getY()) <=kk){
		if(this->Frightn()==0){
			pac[0]->Reset(13,9);
			life--;
			for(int i=0;i<200000000;i++);
		}
		else if(Frightn()==1){
			pac[1]->Reset(13,9);
			for(int i=0;i<200000000;i++);
			pac[1]->Start();
			pac[0]->Score(200);
		}
	}
	if(Distance(pac[0]->getX(),pac[0]->getY(),pac[3]->getX(),pac[3]->getY()) <=kk){
			if(this->Frightn()==0){
				pac[0]->Reset(13,9);
				life--;
				for(int i=0;i<200000000;i++);
			}
			else if(Frightn()==1){
				pac[3]->Reset(13,9);
				for(int i=0;i<200000000;i++);
				pac[3]->Start();
				pac[0]->Score(200);
			}
		}
	if(Distance(pac[0]->getX(),pac[0]->getY(),pac[4]->getX(),pac[4]->getY()) <=kk){
				if(this->Frightn()==0){
					pac[0]->Reset(13,9);
					life--;
					for(int i=0;i<200000000;i++);
				}
				else if(Frightn()==1){
					pac[4]->Reset(13,9);
					for(int i=0;i<200000000;i++);
					pac[4]->Start();
					pac[0]->Score(200);
				}
			}
	if(Distance(pac[0]->getX(),pac[0]->getY(),pac[5]->getX(),pac[5]->getY()) <=kk){
				if(this->Frightn()==0){
					pac[0]->Reset(13,9);
					life--;
					for(int i=0;i<200000000;i++);
				}
				else if(Frightn()==1){
					pac[5]->Reset(13,9);
					for(int i=0;i<200000000;i++);
					pac[5]->Start();
					pac[0]->Score(200);
				}
			}

*/
}
};



#endif /* BOARD2_H_ */
