#pragma once
#pragma execution_character_set("utf-8")
#include <iostream>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<string>
using namespace std;

#include "Snake.h"

int main(){
	int gamespeed = 100;
	int timeover,start;
	char direction = Left;
	//60*15�İ���
	Board board(60, 15);
	Snake snake(4, &board);
	while (true){
		
		timeover = 0.1;
		start = clock();
		//����м����»�ʱ�䳬���Զ�ǰ��ʱ��������ֹѭ��
		while ((timeover = (clock() - start <= gamespeed)) && !_kbhit());
		if (timeover){
			_getch(); direction = _getch();
		}

		
		snake.turn(direction);
		try{
			snake.run();
		}
		catch (string* e){
			cout << *e<<"\nscore:"<<snake.getScore()<<"\n";
			system("pause");
		}
		
		
		board.drawSnake(snake.getHead());
		system("cls");
		board.display();
		
	}

	
}