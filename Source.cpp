#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>
#include <time.h>
#include <stdlib.h>

struct Mob
{
	int x;
	int y;

};
struct Hero
{
	int x;
	int y;
	int isJumping;
	int Velocity;
};
struct World
{
	char gameMap[45][60];
	struct Hero gameHero;
	struct Mob gameMobs[10];
};
World gameWorld;

void init(void)
{

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 600.0, 450.0, 0.0, -1.0, 1.0);
}


void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	for (int y = 0; y < 45; y++)
	{
		for (int x = 0; x < 60; x++)
		{
			if (gameWorld.gameMap[y][x] == '0')
			{

			}
			else
			{
				if (gameWorld.gameMap[y][x] == '1')
					glColor3f(1.0, 1.0, 0.0);
				else if (gameWorld.gameMap[y][x] == 'm')
					glColor3f(1.0, 0.0, 0.0);
				else if (gameWorld.gameMap[y][x] == 'P')
					glColor3f(1.0, 0.0, 1.0);
				glBegin(GL_POLYGON);
				glVertex3f(0.0 + x * 10, 0.0 + y * 10, 0.0);
				glVertex3f(10.0 + x * 10, 0.0 + y * 10, 0.0);
				glVertex3f(10.0 + x * 10, 10.0 + y * 10, 0.0);
				glVertex3f(0.0 + x * 10, 10.0 + y * 10, 0.0);
				glEnd();
			}
		}
	}
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0 + gameWorld.gameHero.x, 0.0 + gameWorld.gameHero.y, 0.0);
	glVertex3f(10.0 + gameWorld.gameHero.x, 0.0 + gameWorld.gameHero.y, 0.0);
	glVertex3f(10.0 + gameWorld.gameHero.x, 10.0 + gameWorld.gameHero.y, 0.0);
	glVertex3f(0.0 + gameWorld.gameHero.x, 10.0 + gameWorld.gameHero.y, 0.0);
	glEnd();

	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		gameWorld.gameHero.Velocity = 1;
		break;
	case 's':
		gameWorld.gameHero.Velocity = 0;
		break;
	case 'd':
		gameWorld.gameHero.Velocity = 2;
		break;
	case 'w':
		if (gameWorld.gameHero.isJumping == 0)
			gameWorld.gameHero.isJumping = 50;
		break;
	default:
		break;
	}

}

void calculate()
{
	Sleep(25);
	if (gameWorld.gameHero.isJumping > 0)
	{
			if ((gameWorld.gameMap[gameWorld.gameHero.y / 10][gameWorld.gameHero.x / 10 + 1] != '1') && (gameWorld.gameMap[gameWorld.gameHero.y / 10][gameWorld.gameHero.x / 10] != '1'))
			{
				gameWorld.gameHero.y -= 1;
				gameWorld.gameHero.isJumping -= 1;
			}
			else
				gameWorld.gameHero.isJumping = 0;
	}
	else if ((gameWorld.gameMap[gameWorld.gameHero.y / 10 + 1][gameWorld.gameHero.x / 10] != '1') && (gameWorld.gameMap[gameWorld.gameHero.y / 10 + 1][gameWorld.gameHero.x / 10+1] != '1'))
	{
		gameWorld.gameHero.y += 1;
	}
	if (gameWorld.gameHero.Velocity == 1)
	{
		if (gameWorld.gameMap[gameWorld.gameHero.y / 10][(gameWorld.gameHero.x) / 10] != '1')
			gameWorld.gameHero.x -= 2;
	}
	if (gameWorld.gameHero.Velocity == 2)
	{
		if (gameWorld.gameMap[gameWorld.gameHero.y / 10][gameWorld.gameHero.x / 10 + 1] != '1')
			gameWorld.gameHero.x += 2;
	}
	if ((gameWorld.gameMap[gameWorld.gameHero.y / 10][gameWorld.gameHero.x / 10] == 'm') || (gameWorld.gameMap[gameWorld.gameHero.y / 10 + 1][gameWorld.gameHero.x / 10] == 'm') || (gameWorld.gameMap[gameWorld.gameHero.y / 10][gameWorld.gameHero.x / 10 + 1] == 'm'))
	{
		glutDestroyWindow(1);
	}
	glutPostRedisplay();
}
int main(int argc, char **argv)
{
	srand(time(NULL));

	FILE * FILENAME = fopen("1_level.txt", "r");
	for (int y = 0; y < 45; y++)
	{
		for (int x = 0; x < 60; x++)
		{
			fscanf(FILENAME, "%c", &((gameWorld.gameMap)[y][x]));
			if (gameWorld.gameMap[y][x] == '\n')
				fscanf(FILENAME, "%c", &((gameWorld.gameMap)[y][x]));
			if (gameWorld.gameMap[y][x] == 'G')
			{
				gameWorld.gameMap[y][x] = '0';
				gameWorld.gameHero.x = x * 10;
				gameWorld.gameHero.y = y * 10;
				gameWorld.gameHero.isJumping = 0;
				gameWorld.gameHero.Velocity = 0;
			}
		}
	}
	fclose(FILENAME);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("RUNNER");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(calculate);
	glutMainLoop();
	return 0;
}
