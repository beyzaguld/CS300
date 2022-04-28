//Beyzagul Demir, 28313
//CS300 - HW1
//30.03.2022

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "randgen.h"
#include "strutils.h"
using namespace std;

struct cell {
	int x, y;
	int l, r, u, d;
	bool visited;
};

struct maze {
	vector<vector<cell>> m;
};

string choose_wall(int x, int y, int M, int N, vector<vector<cell>> mat) {
	vector<string> choice_list;
	for (int i = -1; i < 2; i = i + 2) {
		if ((x + i > -1) && (x + i < N ) && (mat[y][x + i].visited == false)) {
					if (i == -1)
						choice_list.push_back("left");
					if (i == 1)
						choice_list.push_back("right");
		}
	}
	for (int i = -1; i < 2; i = i + 2) {
		if ((y + i > -1) && (y + i < M) && (mat[y+i][x].visited == false)) {
			if (i == -1)
				choice_list.push_back("down");
			if (i == 1)
				choice_list.push_back("up");
		}
	}
	RandGen rand;
	int vec_size = choice_list.size();
	string direction = "no_direction";
	if (vec_size != 0) {
		int dir = rand.RandInt(0, vec_size-1);
		direction = choice_list[dir];
	}
	return direction;
}

string choose_direction(int x, int y, int M, int N, vector<vector<cell>> new_mat) {
	vector<string> directions;
	if (x-1 > -1) {
		if ((new_mat[y][x].l == 0) && (new_mat[y][x-1].visited == false)) 
			directions.push_back("left");
	}
	if (x+1 < N) {
		if ((new_mat[y][x].r == 0) && (new_mat[y][x+1].visited == false)) 
			directions.push_back("right");
	}
	if (y-1 > -1) {
		if ((new_mat[y][x].d == 0) && (new_mat[y-1][x].visited == false)) 
			directions.push_back("down");
	}
	if (y+1 < N) {
		if ((new_mat[y][x].u == 0) && (new_mat[y+1][x].visited == false)) 
			directions.push_back("up");
	}
	RandGen rand;
	int vec_size = directions.size();
	string direction = "no_direction";
	if (vec_size != 0) {
		int dir = rand.RandInt(0, vec_size-1);
		direction = directions[dir];
	}
	return direction;
}

bool unvisited_cells (vector<vector<cell>> mat, int M, int N) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (mat[i][j].visited == false)
				return true;
		}
	}
	return false;
}

template <class Object>
class Stack {

public:
	Stack();
	Stack(const Stack& rhs);
	~Stack();

	bool isEmpty() const;
	bool isFull() const;
	void makeEmpty();

	void pop();
	void push(const Object& x);
	Object topAndPop();
	Object& top() const;

	const Stack& operator=(const Stack& rhs);

private:
	struct ListNode {
		Object element;
		ListNode* next;

		ListNode(const Object& theElement, ListNode* n = NULL)
			: element(theElement), next(n) {}
	};

	ListNode* topOfStack;  // list itself is the stack
};

//Construct the stack
template <class Object>
Stack<Object>::Stack() { topOfStack = NULL; }

template <class Object>
bool Stack<Object>::isFull() const { return false; }

template <class Object>
bool Stack<Object>::isEmpty() const { return topOfStack == NULL; }

/*
* Get the most recently inserted item in the stack.
* Return the most recently inserted item in the stack
* or throw an exception if empty.
*/
template <class Object>
Object& Stack<Object>::top() const {

	if (!isEmpty()) { return topOfStack->element; }

}

template <class Object>
void Stack<Object>::pop() {

	if (!isEmpty()) {

		ListNode* oldTop = topOfStack;
		topOfStack = topOfStack->next;
		delete oldTop;
	}

}

template <class Object>
void Stack<Object>::push(const Object& x) {

	topOfStack = new ListNode(x, topOfStack);
}

/*
	* Return and remove the most recently
	* inserted item from the stack.
*/
template <class Object>
Object Stack<Object>::topAndPop() {

	Object topItem = top();
	pop();
	return topItem;
}

template <class Object>
void Stack<Object>::makeEmpty() {

	while (!isEmpty()) { pop(); }
}

//Deep copy constructor
template <class Object>
const Stack<Object>& Stack<Object>::
operator=(const Stack<Object>& rhs)
{
	if (this != &rhs) {

		makeEmpty();

		if (rhs.isEmpty()) { return *this; }

		ListNode* rptr = rhs.topOfStack;
		ListNode* ptr = new ListNode(rptr->element);
		topOfStack = ptr;

		for (rptr = rptr->next; rptr != NULL; rptr = rptr->next)
			ptr = ptr->next = new ListNode(rptr->element);
	}

	return *this;
}

//Copy constructor
template <class Object>
Stack<Object>::Stack(const Stack<Object>& rhs) {

	topOfStack = NULL;
	*this = rhs; //deep copy 
}

//Destructor
template <class Object>
Stack<Object>::~Stack() { makeEmpty(); }

int main() {
	int M, N, K, entryX, entryY, exitX, exitY, mazeID;
	cout << "Enter the number of mazes: ";
	cin >> K;
	cout << "Enter the number of rows and columns (M and N): ";
	cin >> M >> N;
	vector<vector<vector<cell>>> mazes;
	for (int k = 0; k < K; k++) {
		vector<vector<cell>> mat(M, vector<cell>(N));
		cell currCell;
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				currCell.y = i;
				currCell.x = j;
				currCell.l = 1;
				currCell.r = 1;
				currCell.u = 1;
				currCell.d = 1;
				currCell.visited = false;
				mat[i][j] = currCell;

			}
		}
		cell CurrCell = mat[0][0];
		Stack<cell> myStack;
		myStack.push(CurrCell);
		mat[CurrCell.y][CurrCell.x].visited = true;
		while (unvisited_cells(mat, M, N)) {
			string direct = choose_wall(CurrCell.x, CurrCell.y, M, N, mat);
			if (direct == "left") {
				mat[CurrCell.y][CurrCell.x].l = 0;
				mat[CurrCell.y][CurrCell.x-1].r = 0;
				CurrCell = mat[CurrCell.y][CurrCell.x - 1];
			}
			else if (direct == "right") {
				mat[CurrCell.y][CurrCell.x].r = 0;
				mat[CurrCell.y][CurrCell.x + 1].l = 0;
				CurrCell = mat[CurrCell.y][CurrCell.x + 1];
			}
			else if (direct == "up") {
				mat[CurrCell.y][CurrCell.x].u = 0;
				mat[CurrCell.y + 1][CurrCell.x].d = 0;
				CurrCell = mat[CurrCell.y + 1][CurrCell.x];
			}
			else if (direct == "down") {
				mat[CurrCell.y][CurrCell.x].d = 0;
				mat[CurrCell.y - 1][CurrCell.x].u = 0;
				CurrCell = mat[CurrCell.y - 1][CurrCell.x];
			}
			else {
				while (choose_wall(CurrCell.x, CurrCell.y, M, N, mat) == "no_direction") {
					if (unvisited_cells(mat, M, N)) {
						myStack.pop();
						CurrCell = myStack.top();
					}
					else 
						break;
				}
				string direct = choose_wall(CurrCell.x, CurrCell.y, M, N, mat);
			}
			myStack.push(CurrCell);
			mat[CurrCell.y][CurrCell.x].visited = true;
		}
		string ID = itoa(k+1);
		string filename = "maze_" + ID + ".txt";
		ofstream myFile;
		myFile.open(filename.c_str());
		myFile << M << " " << N << endl;
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				cell currCell = mat[i][j];
				myFile << "x=" << currCell.x << " y=" << currCell.y << " l=" << currCell.l << " r="
					<< currCell.r << " u=" << currCell.u << " d=" << currCell.d << endl;
			}
		}
		mazes.push_back(mat);
		myFile.close();
	}

	cout << "All mazes are created." << endl;

	cout << "Enter a maze ID between 1 to ";
	cout << K;
	cout << " inclusive to find a path: ";
	cin >> mazeID;


	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> entryX >> entryY;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> exitX >> exitY;

	vector<vector<cell>> new_mat(M, vector<cell>(N));
	new_mat = mazes[mazeID-1];

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			new_mat[i][j].visited = false;
		}
	}
	cell currentCell = new_mat[entryY][entryX];
	cell exitCell = new_mat[exitY][exitX];
	Stack<cell> coordinates;
	coordinates.push(currentCell);
	new_mat[currentCell.y][currentCell.x].visited = true;
	while (!((currentCell.x == exitCell.x) && (currentCell.y == exitCell.y))) {
		string way_to_go = choose_direction(currentCell.x, currentCell.y, M, N, new_mat);
		if (way_to_go == "left") {
			currentCell = new_mat[currentCell.y][currentCell.x-1];
			coordinates.push(currentCell);
		}
		else if (way_to_go == "right") {
			currentCell = new_mat[currentCell.y][currentCell.x+1];
			coordinates.push(currentCell);
		}
		else if (way_to_go == "up") {
			currentCell = new_mat[currentCell.y+1][currentCell.x];
			coordinates.push(currentCell);
		}
		else if (way_to_go == "down") {
			currentCell = new_mat[currentCell.y-1][currentCell.x];
			coordinates.push(currentCell);
		}
		else {
			while (choose_direction(currentCell.x, currentCell.y, M, N, new_mat) == "no_direction") {
					coordinates.pop();
					if (!coordinates.isEmpty())
						currentCell = coordinates.top();
			}
		}
		new_mat[currentCell.y][currentCell.x].visited = true;
		currentCell.visited = true;
	}

	string filename;
	filename = "maze_" + to_string(mazeID) + "_path_" + to_string(entryX) + "_" + to_string(entryY) + "_" + to_string(exitX) + "_" + to_string(exitY) + ".txt";
	ofstream pathFile;
	pathFile.open(filename.c_str());

	Stack<cell> coordinate_stack;
	cell temp;
	while (!coordinates.isEmpty()) {
		temp = coordinates.top();
		coordinate_stack.push(temp);
		coordinates.pop();
	}
	while (!coordinate_stack.isEmpty()) {
		temp = coordinate_stack.top();
		pathFile << temp.x << " " << temp.y << endl;
		coordinate_stack.pop();
	}
	pathFile.close();

	
	return 0;
}