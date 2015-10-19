#include "Snake.h"
#include <time.h>

//Coordinate
Coordinate::Coordinate(){
	x = 0;
	y = 0;
}
Coordinate::Coordinate(int x, int y){
	this->x = x;
	this->y = y;
}
//Node
Node::Node():pos(0,0){
	*sharp = '*';
	next = NULL;
}
Node::Node(const Coordinate&pos, char*sharp,Node *ptr){
	this->set(pos, sharp, ptr);
}
void Node::set(const Coordinate&pos, char*sharp, Node *ptr){
	this->pos = pos;
	this->sharp = sharp;
	this->next = next;
}


//Head

Head::Head(const Coordinate&pos, char*sharp, int direction) : Node(pos, sharp, NULL){
	this->direction = direction;
}

//Snake

Snake::Snake(int n,Board*ptr){
	this->head = new Head(Coordinate(3,0), "#", Right);
	Node * temp = head;
	while (--n){
		temp->next = new Node(Coordinate(temp->pos.x - 1, temp->pos.y), "*", NULL);
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
	//TODO

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
		checkThenGo(Coordinate(head->pos.x, head->pos.y - 1));
		break;
	case Right:
		checkThenGo(Coordinate(head->pos.x + 1, head->pos.y));
		break;
	case Down:
		checkThenGo(Coordinate(head->pos.x, head->pos.y + 1));
		break;
	case Left:
		checkThenGo(Coordinate(head->pos.x - 1, head->pos.y));
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
void Snake::addNode(const Coordinate&pos){
	Head *temp = new Head(pos, "#", head->direction);
	head->set(head->pos, "*", head->next);
	temp->next = head;
	head = temp;
}
void Snake::move(Node *head){
	int t_x = head->pos.x,
		t_y = head->pos.y;
	while (head->next){
		//移动到蛇头的下一个节点
		head = head->next;
		int t_t_x = head->pos.x,
			t_t_y = head->pos.y;
		head->pos.x = t_x;
		head->pos.y = t_y;
		t_x = t_t_x;
		t_y = t_t_y;
	}
}
void Snake::checkThenGo(const Coordinate&pos){
	int	flag = board->isBlock(pos);
	//-1 碰到边界或者碰到自己
	if (flag == -1)throw new std::string("Game Over");
	//1 遇到食物
	else if (flag == 1){
		score++;
		addNode(pos);
	}
	// 0 正常行进
	else {
		move(head);
		head->pos = pos;
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

int Board::isBlock(const Coordinate&pos){
	//-1 游戏结束 1 获取食物，0 正常前进
	if (pos.x >= column || pos.x < 0 || pos.y >= row || pos.y < 0)
		return -1;
	if (getPos(pos) == food){
		generateFood();
		return 1;
	}
	if (getPos(pos) != space)
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
		setPos(head->pos,*(head->sharp));
		head = head->next;
	}
	drawFood();
}
//Board private
char Board::getPos(const Coordinate&pos){
	return board[pos.y*column+pos.x];
}
void Board::setPos(const Coordinate&pos,const char ch){
	board[pos.y*column+pos.x] = ch;
}
void Board::generateFood(){
	srand(time(0));
	Coordinate temp(0,0);
	do{
		temp = Coordinate(rand() % column, rand() % row);
	} while (isBlock(temp) == -1);
	foodPos = temp;
}

void Board::drawFood(){
	setPos(foodPos,food);
}

Board::~Board(){
	if (board){
		delete[] board;
	}
}