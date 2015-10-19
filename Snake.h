#pragma once
#pragma execution_character_set("utf-8")
enum direct{ Up = 72, Right = 77, Down = 80, Left = 75 };
#include <iostream>
#include <fstream>
struct Coordinate{
	Coordinate();
	Coordinate(int x, int y);
	int x,
		y;
};
class Node{
public:
	Node();
	Node(const Coordinate&pos,char*sharp,Node *next);
	virtual void set(const Coordinate&pos, char* sharp, Node*ptr);

	Coordinate pos;
	char* sharp;
	Node* next;
};

class Head :public Node{
public:
	Head();
	Head(const Coordinate&pos, char*sharp, int direction);
	int direction;
};

class Board;
class Snake{
public:
	//����һ������Ϊn����
	Snake(int n,Board*ptr);
	//���ļ��ж�ȡ������ TODO
	Snake(std::ifstream &file);
	//ת����
	void turn(int direction);
	//���յ�ǰ�ķ�������
	void run();
	//����д���ļ� TODO
	void writeToFile();
	//���ط���
	int getScore();
	Head *getHead()const;

	~Snake();
private:
	//�ƶ��������� ���ΰѵ�ǰ�ڵ㸳ֵ����һ���ڵ�
	void move(Node *head);
	//����ʳ�����ʳ�ﵱͷ�ڵ���ӵ�������ȥ
	void addNode(const Coordinate&pos);
	//���������������һ���ڵ��Ƿ��Ǳ߽绹��������ʳ��
	void checkThenGo(const Coordinate&pos);
	//����ͷ�ڵ�
	Head * head;
	//����β���ڵ� TODO
	Node * tail;
	//����
	int score;
	//���̵�����
	Board *board;
};

class Board{
private:
	//���Ա�ʾ�߽磬ʳ��յĵط� ���ַ�
	char border,food,space;
	//һ������
	char *board;
	//���̵ĳ���
	int row, column;
	//ʳ������
	Coordinate foodPos;
	//����ʳ��
	void drawFood();
	//����һ��ʳ��
	void generateFood();
	//����ָ�������ֵ
	char getPos(const Coordinate&pos);
	//����ָ�������ֵ
	void setPos(const Coordinate&pos,const char ch);
public:
	//����һ��row*column ������
	Board(int row, int column);
	~Board();
	void drawSnake(Node * head);
	void display();
	int getRow()const;
	int getCloum()const;
	int isBlock(const Coordinate&pos);
};