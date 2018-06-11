#include <GL/gl.h> // Biblioteca Padrão do OpenGL;
#include <GL/glut.h> //Biblioteca Padrão do GLUT;
#include <stdio.h> // Biblioteca C padrão para controle de entrade e saida.
#include <stdlib.h> //Para o uso de "rand()";
#include <time.h> //Para o uso de "time()";
#include <math.h> //Para o uso de "sqrt()";


//Variáveis globais
int posicao_esfera_X = 0, posicao_esfera_Y = 0;
int posicao_esfera_2_X = -10, posicao_esfera_2_Y = -10;
bool colisao_esferas = false;
int pontos = 0;

/*----------------------------------------------------------------------------*/
void init_glut();
void desenha_esfera();
void desenha_esfera_2();
void testa_colisao_esferas();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void desenha_texto(char *string, int x, int y, void *fonte);
void iniciar_aleatorio(void);
/*----------------------------------------------------------------------------*/

/**********************************************************************/
/*                       Função principal (main)                      */
/**********************************************************************/

int main(int argc, char **argv)  // Função principal
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(450, 350);
	glutCreateWindow("Seaquest");
	init_glut();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	/* função de controlo do GLUT */
	glutMainLoop();

	return 0;
}
/*----------------------------------------------------------------------------*/

//void init_glut(const char *nome_janela, int argc, char** argv)
void init_glut()
{

	//GLfloat luzAmbiente[] = {0.00, 0.00, 0.00, 1.00};
//	GLfloat luzDifusa[] = {1.00, 1.00, 1.00, 1.00};		 // "cor"
	GLfloat luzEspecular[] = {0.00, 1.00, 1.00, 1.00}; // "brilho"
	GLfloat posicaoLuz[] = {0.00, 50.00, 5.00, 1.00};

	// Capacidade de brilho do material
//	GLfloat materialAmbiente[] = {1.00, 1.00, 1.00, 1.00};
	//GLfloat materialDifusa[] = {1.00, 0.50, 0.50, 1.00};
	GLfloat materialEspecular[] = {1.00, 0.50, 1.00, 1.00}; //Ks
	//GLfloat materialEmissiva[] = {0.00, 0.00, 0.00, 0.00};
	GLint especMaterial = 20;

	// Especifica que a cor de fundo da janela será preta
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Habilita o modelo de tonalização de Gouraud
	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

	// Define a refletância do material
	//glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbiente);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDifusa);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialEspecular);
///	glMaterialfv(GL_FRONT, GL_EMISSION, materialEmissiva);
	// Define a concentração do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
//	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a definição da cor do material
	// a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)  //Função chamada toda vez que a janela é redimensionada
{
	glViewport(0, 0, w, h); // Ajustando o visualizador
	glMatrixMode(GL_PROJECTION); // Trabalhando com a matriz de projeção
	glLoadIdentity(); // Iniciando a Matriz de cima
	gluPerspective(30, (GLfloat)w / (GLfloat)h, 0.1, 1000.0); //Corrigindo a perspectiva
	glMatrixMode(GL_MODELVIEW);// Voltando a trabalhar com a matriz de modelo
}

void desenha_esfera()  //Função de movimentação
{
	glPushMatrix();
	glTranslatef (posicao_esfera_X, posicao_esfera_Y, -105);
	glColor3f(0.1, 0.1, 0.1);
	//glRotatef (30.0, 0.0, 0.0, 1.0);
	glutSolidSphere(5, 200, 200);
	glPopMatrix();
}

void desenha_esfera_2()  //Função de movimentação
{
	glPushMatrix();
	if(colisao_esferas == false)
	{
		glTranslatef(posicao_esfera_2_X, posicao_esfera_2_Y, -105);
		glColor3f(0.5, 0.5, 0.5);
	}
	else //colisao_esferas == true
	{
		posicao_esfera_2_X = (rand() % 51) - 40;
		posicao_esfera_2_Y = (rand() % 31) - 20;
		glTranslatef(posicao_esfera_2_X, posicao_esfera_2_Y, -105);
		colisao_esferas = false;
		glColor3f(0.5, 0.5, 0.5);
	}
	glutSolidSphere(3.5, 200, 200);
	glRotatef (100.0, 100.0, 0.0, 1.0);
	glPopMatrix();
}

void display(void)  //Função chamada a cada quadro
{
	glClearColor(0.0, 0.0, 1.0, 1.0); //Cor de fundo
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpar tela
	glLoadIdentity(); //Carregar as entidades
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	desenha_esfera();
	desenha_esfera_2();
	testa_colisao_esferas();

	//Texto
	char string[50];
	sprintf(string, "Pontos: %d", pontos); //Prencho a string
	desenha_texto(string, -2.6, 1, GLUT_BITMAP_9_BY_15);

	glutSwapBuffers(); //auxiliar na troca dos buffers(trabalha com a memoria)
}

void keyboard(unsigned char key, int x, int y)
{
	//if (key == 27) exit(0); /* Esc: sai do programa */
	switch(key)
	{

	case 'W':
		if(posicao_esfera_Y == 30)
		{
			break;
		}
		else
		{
			posicao_esfera_Y += 10;
		}
		break;
	case 'w':
		if(posicao_esfera_Y == 30)
		{
			break;
		}
		else
		{
			posicao_esfera_Y += 10;
		}
		break;
	case 'S':
		if(posicao_esfera_Y == -30)
		{
			break;
		}
		else
		{
			posicao_esfera_Y -= 10;
		}
		break;
	case 's':
		if(posicao_esfera_Y == -30)
		{
			break;
		}
		else
		{
			posicao_esfera_Y -= 10;
		}
		break;
	case 'A':
		if(posicao_esfera_X == -50)
		{
			break;
		}
		else
		{
			posicao_esfera_X -= 10;
		}
		break;
	case 'a':
		if(posicao_esfera_X == -50)
		{
			break;
		}
		else
		{
			posicao_esfera_X -= 10;
		}
		break;
	case 'D':
		if(posicao_esfera_X == 50)
		{
			break;
		}
		else
		{
			posicao_esfera_X += 10;
		}
		break;
	case 'd':
		if(posicao_esfera_X == 50)
		{
			break;
		}
		else
		{
			posicao_esfera_X += 10;
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void testa_colisao_esferas()
{
	float distancia;
	distancia = sqrt(((posicao_esfera_2_X - posicao_esfera_X) * (posicao_esfera_2_X - posicao_esfera_X)) + ((posicao_esfera_2_Y - posicao_esfera_Y) * (posicao_esfera_2_Y - posicao_esfera_Y)));
	if(distancia <= 8.5)
	{
		colisao_esferas = true;
		pontos++;
	}

	/*
	if((posicao_esfera_X - posicao_esfera_2_X)) && (posicao_esfera_Y == posicao_esfera_2_Y))
	{
		colisao_esferas = true;
	} */
}

void desenha_texto(char *string, int x, int y, void *fonte)
{
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(x, y);
	while (*string)
	{
		glutBitmapCharacter(fonte, *string++);
	}
	glPopMatrix();
}

void iniciar_aleatorio(void)
{
	srand((unsigned int)time(NULL));
	rand();
//	rand();
//	rand();
}