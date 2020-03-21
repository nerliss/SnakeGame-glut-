#include <glut.h>
#include <time.h>
#include <stdlib.h>

int N = 30, M = 20;
int Scale = 25;//Scaling ratio

int w = Scale * N;//Width
int h = Scale * M;//Height

int direction,//Direction takes a value from 0 to 4
	num = 4;//Original size of the snake

struct 
{
	int x;
	int y;
}
s[100];//Max size of the snake

//Fruits
class Fruits
{
public:
	int x, y;
	void Spawn()
	{
		x = rand() % N;
		y = rand() % M;
	}
	void DrawApple()
	{
		glColor3f(0.3, 0.2, 0.6);
		glRectf(x * Scale, y * Scale, (x + 1) * Scale, (y + 1) * Scale);
	}
}
arr[10];//Array of ten Apples

//Drawing the field of the game
void DrawField()
{
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);

	for (int i = 0; i < w; i += Scale)
	{
		glVertex2f(i, 0);
		glVertex2f(i, h);
	}
	for (int j = 0; j < h; j += Scale)
	{
		glVertex2f(0, j);
		glVertex2f(w, j);
	}
	glEnd();
}

//Drawing the snake
void DrawSnake()
{
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < num; i++)
	{
		glRectf(s[i].x * Scale, s[i].y * Scale, (s[i].x + 1) * Scale, (s[i].y + 1) * Scale);//Drawing the rectangular form of the snake
	}
}


//Snake moving
void Tick()
{
	//Moving to the next position
	for (int i = num; i>0; --i)
	{
		s[i].x = s[i - 1].x;		
		s[i].y = s[i - 1].y;
	}

	//Direction of moving
	if (direction == 0) s[0].y += 1;//Up
	if (direction == 1) s[0].y -= 1;//Down
	if (direction == 2) s[0].x += 1;//Right
	if (direction == 3) s[0].x -= 1;//Left

	//Eating an Apple
	for (int i = 0; i < 10; i++)
	{
		if ((s[0].x==arr[i].x)&&(s[0].y==arr[i].y))
		{
			num++;
			arr[i].Spawn();
		}
	}

	//!!!DOESNT WORK PROPERLY MIGHT CHANGE LATER. Turning the snake on hit with a border of the field 
	if (s[0].x > N) direction = 1;
	if (s[0].x < 0) direction = 2;
	if (s[0].y > M) direction = 3;
	if (s[0].y < 0) direction = 0;

	//Resizing the snake on hit with itself
	for (int i = 1; i < num; i++)
		if (s[0].x == s[i].x && s[0].y == s[i].y) num = i;
}

//Controls
void Keyboard(int key, int a, int b)
{
	switch (key)
	{
	case 101: direction = 0;//ArrowUp
		break;
	case 103: direction = 1;//ArrowDown
		break;
	case 102: direction = 2;//ArrowRight
		break;
	case 100: direction = 3;//ArrowLeft
		break;
	}
}

//Displays on screen things I draw 
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//Screen clean
	DrawField();
	DrawSnake();

	for (int i = 0; i < 10; i++)
		arr[i].DrawApple();

	glFlush();
}

//Changing subjects every time. 50ms in my case
void timer(int = 0)
{
	display();

	Tick();

	glutTimerFunc(100, timer, 0);
}


int main(int argc, char **argv)
{
	for (int i = 0; i < 10; i++)
		arr[i].Spawn();

	s[0].x = 10;
	s[0].y = 10;



	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h); //Resolution
	glutCreateWindow("Snake"); //Name of the window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);

	glutDisplayFunc(display); //Displaying of a function. void display in my case
	glutTimerFunc(100, timer, 0); //Declaring Timer function. void timer in my case
	glutSpecialFunc(Keyboard);
	
	glutMainLoop();
}