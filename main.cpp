//Andrew Godfrey
//Final Maze Projects
//Classes Used: Maze (for game board), Stack ( for direction list ), Point ( for coordinate pairing )
//Date: 11/25/2016
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

template<class Type>
class Stack {
public:
	Stack()
	{
		head = NULL;
	}
	void push(Type data)
	{
		if (head)
		{
			Node * tmp = new Node;
			tmp->data = data;
			tmp->next = head;
			head = tmp;
		}
		else
		{
			head = new Node;
			head->data = data;
			head->next = NULL;
		}

	}
	void pop()
	{
		if (head)
		{
			Node * tmp = head;
			head = head->next;
			delete tmp;
		}
	}
	Type top()
	{
		return head->data;
	}
	bool isEmpty()
	{
		return (head) ? false : true;
	}
private:
	struct Node {
		Type data;
		Node * next;
	};
	Node * head;
};

class Point {
public:
	Point(int currX, int currY)
	{
		x = currX;
		y = currY;
	}
	bool operator==(const Point & rhs)
	{
		return (x == rhs.x && y == rhs.y)? true:false;
	}
	void print()
	{
		cout << "( " << x << ", " << y << " )\n";
	}
	Point right()
	{
		Point tmp(x, y+1);
		return tmp;
	}
	Point left()
	{
		Point tmp(x, y - 1);
		return tmp;
	}
	Point up()
	{
		Point tmp(x-1, y);
		return tmp;
	}
	Point down()
	{
		Point tmp(x+1, y);
		return tmp;
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
private:
	int x, y;
};

class Maze {
public:
	Maze(string file)
	{
		pathLen = 0;
		int row = 0, col = 0;
		ifstream infile(file);
		if (infile.is_open())
		{
			infile >> height >> width;
			grid = new char*[height];
			visited = new char*[height];
			for (int i = 0; i < height; i++)
			{
				grid[i] = new char[width];
				visited[i] = new char[width];
			}
			for (int row = 0; row < height; row++) 
			{
				for (int col = 0; col < width; col++)
				{
					infile >> grid[row][col];
					visited[row][col];
				}	
			}
			infile.close();
		}
		else
			cout << "File not found!\n";
	}
	~Maze()
	{
		for (int i = 0; i < height; i++)
		{
			delete[]grid[i];
			delete[]visited[i];
		}
		delete grid;
		delete visited;
	}
	void printMaze()
	{
		cout << "-Maze-\n";
		for(int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
				cout << grid[i][j];
			cout << endl;
		}
	}
	bool canGetOut(Point curr)
	{
		visited[curr.getX()][curr.getY()] = 'X';
		if (grid[curr.getX()][curr.getY()] == 'E')
			return true;
		if ((*this)[curr.down()] && canGetOut(curr.down()))//down
		{
			path.push("down\n");
			return true;
		}
		if ((*this)[curr.up()] && canGetOut(curr.up()))//up
		{
			path.push("up\n");
			return true;
		}
		if ((*this)[curr.right()] && canGetOut(curr.right()))//right
		{
			path.push("right\n");
			return true;
		}
		if ((*this)[curr.left()] && canGetOut(curr.left()))//left
		{
			path.push("left\n");
			return true;
		}
		if(!path.isEmpty())
			path.pop();
		return false;
	}
	void showPath()
	{
		while (!path.isEmpty())
		{
			cout << path.top();
			path.pop();
		}
		while (!path.isEmpty())
		{
			cout << path.top();
			path.pop();
		}
	}
	bool isVisited(Point curr)
	{
		return (visited[curr.getX()][curr.getY()] == 'X');
	}
	bool operator[](Point & point)const
	{
		int currX = point.getX();
		int currY = point.getY();
		if (!(currX < height && currX > -1 && currY > -1 && currY < width))
			return false;
		if (visited[currX][currY] == 'X' || grid[currX][currY] == 'X')
			return false;
		return true;
	}
private:
	int height, width;
	char ** grid;
	char ** visited;
	Stack<string>path;
	int pathLen;
};
int main()
{
	Maze test("C:\\Users\\Andrew\\Desktop/maze.txt");
	test.printMaze();
	Point testPoint(0, 1);
	string result = test.canGetOut(testPoint) ? "Yes\n" : "No\n";
	cout << result;
	test.showPath();
	return 0;
}
