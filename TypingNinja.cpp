#include<iostream>
#include<conio.h>
#include <windows.h>
#include <time.h>
#include<dos.h>
#define ROWS 90
#define COLUMN 26
#define WIN_WIDTH 70 

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

COORD CursorPosition;

char letter[10];	
int position[10][2];	
int count = 0; 

void gotoxy(int a, int b){
	CursorPosition.X = a;
	CursorPosition.Y = b;
	SetConsoleCursorPosition(console, CursorPosition);
}
void fix(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void create(){  
	for(int i=0; i<ROWS; i++){ 
		gotoxy(i,COLUMN); cout<<"±";
	}
	
	for(int i=0; i<COLUMN; i++){
		gotoxy(0,i); cout<<"±";
		gotoxy(ROWS,i); cout<<"±";
	}
	for(int i=0; i<COLUMN; i++){
		gotoxy(WIN_WIDTH,i); cout<<"±";
	}
}

void generate(int ind){
	letter[ind] = 65+rand()%25;
	position[ind][0] = 2 + rand()%(WIN_WIDTH-2);
	position[ind][1] = 1;
}
void drawing(int ind){
	if( position[ind][0] != 0 ){
		gotoxy(position[ind][0], position[ind][1]);   cout<<letter[ind];  
	} 
}
void eraseALPH(int ind){
	if( position[ind][0] != 0 ){
		gotoxy(position[ind][0], position[ind][1]);   cout<<" ";  
	}
}
void reset(int ind){
eraseALPH(ind);
	generate(ind);
}
void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<count<<endl;
}
int end(){
	system("cls");
	system("color 21");
	cout<<endl;
	cout<<"\t\t**********"<<endl;
	cout<<"\t\t-------- GAME OVER -------"<<endl;
	 gotoxy(18,5);
	cout<<"Score: "<<count<<endl;
	cout<<"\t\t**********"<<endl<<endl;
	cout<<"\t\tClick on any key to continue.";
	getch();
	
}


void instructions(){
	system("cls");
	system("color 67");
	cout<<"INSTRUCTIONS";
	cout<<"\n----------------";
	cout<<"\n 1. Characters are going to be shooted from top ";
	cout<<"\n 2. You have to keep them away from touching floor";
	cout<<"\n 3. In order to keep them away from ground you need to press on respective letter from keyboard";
	cout<<"\n\n 4. Press 'escape' to exit";
	cout<<"\n\n5. Click on any key to continue.";
	getch();
}

void play(){
	count = 0;
	for(int i=0; i<10; i++){
		position[i][0] = position[i][1] = 1;	
	}
	 
	system("cls"); 
    system("color 07");
	create(); 
	updateScore();
	
	for(int i=0; i<10; i++)
		generate(i); 
	
	gotoxy(WIN_WIDTH + 5, 2);cout<<"****";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"TYPING NINJA";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"****";
	
	gotoxy(18, 5);cout<<"Click on any key to continue";
	getch();
	gotoxy(18, 5);cout<<"                              ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			for(int i=0; i<10; i++){
				if( ch == letter[i] || ch-32 == letter[i] ){
					reset(i);
					count++;
					updateScore();
				}
			}
			if(ch==27){
				break;
			}
		} 
		
		for(int i=0; i<10; i++)
			drawing(i);  
			
		Sleep(300); 
		
		for(int i=0; i<10; i++){
		eraseALPH(i);  
			position[i][1] += 1;
			if( position[i][1] > COLUMN ){
				end();
				return;
			}
		}
	}
}

int main()
{
	fix(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("cls");
		system("color 90");
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |     TYPING  NINJA      | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. START GAME";
		gotoxy(10,10); cout<<"2. INSTRUCTIONS";	 
		gotoxy(10,11); cout<<"3. QUIT";
		gotoxy(10,13); cout<<"Select option: ";
		char op = getche();
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	}while(1);
	system("color d4");
	return 0;
}