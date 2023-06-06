#include "ddini.h"
#include "ResFile.h"
#include "FastDraw.h"
#include "mgraph.h"
#include "mouse.h"
#include "menu.h"
#include "MapDiscr.h"
#include "multipl.h"
#include "fog.h"
#include "walls.h"
#include "Nature.h"
#include <assert.h>
#include <crtdbg.h>
//#define CHECKMODE
struct AskMove{
	word ReqID;//������ �������������
	word PreID;//������ ��������� ��������� � ��� ������
	byte x;
	byte y;
	char dx;
	char dy;
};
extern int NAsk;//���������� ��������
extern AskMove Ask[8192];//������ ��������

class CSum{
	int* lpInt;
	int NInt;
	int	Summa;
public:
	void GetSum(void* lp,int n);
	void GetSum();
	bool ChkSum();
};

void CSum::GetSum(void* lp,int n){
	lpInt=(int*)lp;
	NInt=n>>2;
	GetSum();
};
void CSum::GetSum(){
#ifdef CHECKMODE
	int SM=0;
	for(int j=0;j<NInt;j++)SM+=lpInt[j];
	Summa=SM;
#endif;
};
bool CSum::ChkSum(){
	int SM=0;
	for(int j=0;j<NInt;j++)SM+=lpInt[j];
	return Summa==SM;
};
//-------------------USING THIS CLASS----------------//
static int NSum=0;
CSum SMS[64];
BigSum();
void ADDSUMM(void* lp,int n);
void GETALL();
void CHKALL();
void ADDSUMM(void* lp,int n){
	SMS[NSum].GetSum(lp,n);
	NSum++;
};
void GETALL(){
#ifdef CHECKMODE
	for(int i=0;i<NSum;i++)	SMS[i].GetSum();
#endif
};
//Asks array integrity checking
void CheckAsks(){
	for(int i=0;i<NAsk;i++){
		word ID=Ask[i].ReqID;
		OneObject* OB=Group[ID];
		assert(OB&&OB->x==Ask[i].x&&Ask[i].y==OB->y);
	};
};
static dd=0;
void CHKALL(){
	return;
//#ifdef CHECKMODE
	for(int i=0;i<MAXOBJECT;i++){
		OneObject* OB=Group[i];
		assert(!(OB&&OB->LocalOrder&&OB->LocalOrder->OrderType==3&&OB->EnemyID==0xFFFF));
	};
	for(i=0;i<MAXOBJECT;i++){
		OneObject* OB=Group[i];
		if(OB&&OB->NIndex<15){
			assert(!OB->capBuilding);
		};
	};
//	for(int i=0;i<NSum;i++) assert(SMS[i].ChkSum());
//	if(!_CrtCheckMemory())
//		assert(0);
//	CheckAsks();
	/*for(int i=1;i<msx;i++)
		for(int j=1;j<msy;j++){
			word MID=Mops[j][i];
			if(MID!=0xFFFF){
				OneObject* OB=Group[MID];
				if(!OB->capBuilding)assert(OB->x==i&&OB->y==j);//
			};
		};*/
	/*for(int i=0;i<8192;i++){
		OneObject* OBJ=Group[i];
		if(int(OBJ))
			if(OBJ->Lx!=OBJ->Ly||((!OBJ->Sdoxlo)&&Mops[OBJ->y][OBJ->x]!=OBJ->Index))assert(0);
	};*/
//#endif
};
void SetSumms(){
	NSum=0;
};