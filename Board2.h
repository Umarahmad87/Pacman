/*
 * Board2.h
 *
 *  Created on: Apr 30, 2016
 *      Author: umar
 */

#ifndef BOARD2_H_
#define BOARD2_H_
float Distance(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
class Board2 {
int index;
int Frightened;
int count;
int life;
bool pause;
public:
	Board **pac;

Board2() {
	index=0;
	pac=new Board *[6];
	Frightened=0;
	count=0;
	life=3;
}
void All_Reset(){
	life=3;
	this->pac[0]->Pebbles_Reset();
	this->pac[0]->Reset(13,9);
	this->pac[1]->Reset(13,18);
	this->pac[3]->Reset(13,21);
	this->pac[4]->Reset(15,18);
	this->pac[5]->Reset(11,18);
	Frightened=0;

}
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
}
int Frightn(){
	return Frightened;
}
int Count2(){
	//static int i=0;
	int M=300;
	if(Frightened==1){
	for(int j=0;j<M;j++){
		if(count%M<=M/2){ count++; return 1;}
		else if(count%M>M/2){
			Frightened=0;
			count++; return 0;
		}
	}
	count++;}
	return 0;}
void Collision(){
	cout<<"Distance 1="<<(Distance(pac[0]->getX(),pac[0]->getY(),pac[1]->getX(),pac[1]->getY()))<<endl;
	cout<<"Distance 2="<<(Distance(pac[0]->getX(),pac[0]->getY(),pac[3]->getX(),pac[3]->getY()))<<endl;
	cout<<"Distance 3="<<(Distance(pac[0]->getX(),pac[0]->getY(),pac[4]->getX(),pac[4]->getY()))<<endl;
	cout<<"Distance 4="<<(Distance(pac[0]->getX(),pac[0]->getY(),pac[5]->getX(),pac[5]->getY()))<<endl;

	if(Distance(pac[0]->getX(),pac[0]->getY(),pac[1]->getX(),pac[1]->getY()) <=39.0){
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
	if(Distance(pac[0]->getX(),pac[0]->getY(),pac[3]->getX(),pac[3]->getY()) <=39.0){
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
	if(Distance(pac[0]->getX(),pac[0]->getY(),pac[4]->getX(),pac[4]->getY()) <=39.0){
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
	if(Distance(pac[0]->getX(),pac[0]->getY(),pac[5]->getX(),pac[5]->getY()) <=39.0){
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


}
};



#endif /* BOARD2_H_ */
