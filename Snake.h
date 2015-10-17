#pragma once
#pragma execution_character_set("utf-8")
enum direct{ Up = 72, Right = 77, Down = 80, Left = 75 };
#include <iostream>
#include <fstream>
class Node{
public:
	Node();
	Node(int x,int y,char*sharp,Node *next);
	virtual void set(int x, int y, char* sharp, Node*ptr);

	int x, y;
	char* sharp;
	Node* next;
};

class Head :public Node{
public:
	Head();
	Head(int x, int y, char*sharp, int direction);
	int direction;
};

class Board;
class Snake{
public:
	//构建一个长度为n的蛇
	Snake(int n,Board*ptr);
	//从文件中读取蛇数据 TODO
	Snake(std::ifstream &file);
	//转方向
	void turn(int direction);
	//按照当前的方向运行
	void run();
	//数据写入文件 TODO
	void writeToFile();
	//返回分数
	int getScore();
	Head *getHead()const;

	~Snake();
private:
	//移动整个蛇身 依次把当前节点赋值给下一个节点
	void move(Node *head);
	//遇到食物则把食物当头节点添加到蛇身上去
	void addNode(int x, int y);
	//工厂函数，检测下一个节点是否是边界还是自身还是食物
	void checkThenGo(int x, int y);
	//保存头节点
	Head * head;
	//保存尾部节点 TODO
	Node * tail;
	//分数
	int score;
	//棋盘的引用
	Board *board;
};

class Board{
private:
	//各自表示边界，食物，空的地方 的字符
	char border,food,space;
	//一个棋盘
	char *board;
	//棋盘的长宽，食物的位置
	int row, column,food_x,food_y;
	//画出食物
	void drawFood();
	//创建一个食物
	void generateFood();
public:
	//构建一个row*column 的棋盘
	Board(int row, int column);
	~Board();
	void drawSnake(Node * head);
	void display();
	int getRow()const;
	int getCloum()const;
	int isBlock(int x,int y);
};