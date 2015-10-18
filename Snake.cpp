#include "Snake.h"
#include <time.h>
Node::Node(){
	x = y = 0;
	*sharp = '*';
	next = NULL;
}
//Node
Node::Node(int x, int y, char*sharp,Node *ptr){
	this->set(x, y, sharp, ptr);
}
void Node::set(int x,int y,char*sharp,Node *ptr){
	this->x = x;
	this->y = y;
	this->sharp = sharp;
	this->next = next;
}


//Head

Head::Head(int x, int y, char*sharp, int direction) : Node(x, y, sharp, NULL){
	this->direction = direction;
}

//Snake

Snake::Snake(int n,Board*ptr){
	this->head = new Head(3, 0, "#", Right);
	Node * temp = head;
	while (--n){
		temp->next = new Node(temp->x - 1, temp->y, "*", NULL);
		temp = temp->next;
	}
	tail = temp;
	score = 0;
	this->board = ptr;//TODO
}
Snake::Snake(std::ifstream &file){
	/*int s; file >> s;
	this->score = s; 
	head = new Head()
	int direct; file >> direct;
	int x, y;
	while (file >> x >> y){
	}*/
}

void Snake::turn(int direction){
	int currDirect = this->head->direction;
	if ((currDirect == Up && direction == Down)||
		(currDirect == Down && direction == Up)||
		(currDirect == Left &&direction == Right)||
		(currDirect == Right &&direction==Left))
		return;

	this->head->direction = direction;
}
void Snake::run(){
	switch (head->direction){
	case Up:
		checkThenGo(head->x, head->y - 1);
		break;
	case Right:
		checkThenGo(head->x+1, head->y);
		break;
	case Down:
		checkThenGo(head->x, head->y + 1);
		break;
	case Left:
		checkThenGo(head->x - 1, head->y);
		break;
	default:
		break;
	}
	 
}

Head * Snake::getHead()const{
	return head;
}

int Snake::getScore(){
	return score;
}
Snake::~Snake(){
	Node *temp = head;
	while (temp){
		Node * t = temp->next;
		delete temp;
		temp = t;
	}
	if (board){
		delete[] board;
	}
}

//Snake private
void Snake::addNode(int x,int y){
	Head *temp = new Head(x, y, "#", head->direction);
	head->set(head->x, head->y, "*", head->next);
	temp->next = head;
	head = temp;
}
void Snake::move(Node *head){
	int t_x = head->x,
		t_y = head->y;
	while (head->next){
		//移动到蛇头的下一个节点
		head = head->next;
		int t_t_x = head->x,
			t_t_y = head->y;
		head->x = t_x;
		head->y = t_y;
		t_x = t_t_x;
		t_y = t_t_y;
	}
}
void Snake::checkThenGo(int x, int y){
	int	flag = board->isBlock(x, y);
	//-1 碰到边界或者碰到自己
	if (flag == -1)throw new std::string("Game Over");
	//1 遇到食物
	else if (flag == 1){
		score++;
		addNode(x, y);
	}
	// 0 正常行进
	else {
		move(head);
		head->x = x;
		head->y = y;
	}
}




//Board
Board::Board(int x, int y){
	border = '+';
	food = '$';
	space = ' ';

	board = new char[x*y];
	memset(board,space, sizeof(char)*x*y);
 	this->row = y;
	this->column = x;
	generateFood();
	drawFood();
}

void Board::display(){
	for (int i = -1; i < row+1; i++){
		for (int j = -1; j < column+1; j++){
			if (i == -1 || i == row || j == -1 || j == column)
				std::cout << border;
			else
				std::cout << board[i*column + j];
		}
		std::cout << std::endl;
	}
}

int Board::isBlock(int x, int y){
	//-1 游戏结束 1 获取食物，0 正常前进
	if (x >= column || x < 0 || y >= row || y < 0)
		return -1;
	if (board[y*column + x] == food){
		generateFood();
		return 1;
	}
	if (board[y *column + x] != space)
		return -1;
	return 0;
}

int Board::getRow()const{
	return row;
}

int Board::getCloum() const
{
	return column;
}

void Board::drawSnake(Node*head){
	memset(board, space, sizeof(char)*row*column);
	while (head){
		board[head->y *column + head->x ] = *(head->sharp);
		head = head->next;
	}
	drawFood();
}
//Board private
void Board::generateFood(){
	srand(time(0));
	int x, y;
	do{
		x = rand() % column;
		y = rand() % row;
	} while (isBlock(x,y)==-1);
	food_x = x;
	food_y = y;
}

void Board::drawFood(){
	board[food_y*column + food_x] = food;
}

Board::~Board(){
	if (board){
		delete[] board;
	}
}