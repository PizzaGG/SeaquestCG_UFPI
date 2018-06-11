//****************************************************************************//
//                                                                            //
//  UNIVERSIDADE FEDERAL DO PIAU�  - UFPI                                     //
//  CURSO: BACHARELADO EM CI�NCIA DA COMPUTA��O                               //
//  DISCIPLINA: Computa��o Gr�fica     PER�ODO: 2017.1                        //
//  PROFESSOR: Laurindo de Sousa Brito Neto                                   //
//  ALUNOS: Messias Henrique da Silva Santos                                  //
//			Paulo Renato de Souza Filho                                       //
//  C�DIGO: Seaquest 3D                                                       //
//                                                                            //
//****************************************************************************//


//****************************************************************************//
//  Comandos:                                                                 //
//                                                                            //
//   W -> Cima;                                                               //
//   S -> BAIXO;                                                              //
//   A -> ESQUERDA;                                                           //
//   D -> DIREITA;                                                            //
//   ESC -> Sair;                                                             //                   
//                                                                            //
//****************************************************************************//

//Bibliotecas
#include <GL/gl.h> // Biblioteca Padr�o do OpenGL;
#include <GL/glut.h> //Biblioteca Padr�o do GLUT;
#include <stdio.h> // Biblioteca C padr�o para controle de entrade e saida.
#include <stdlib.h> //Para o uso de "rand()";
#include <time.h> //Para o uso de "time()";
#include <math.h> //Para o uso de "sqrt()";

//Vari�veis globais
int posicao_esfera_X = 0, posicao_esfera_Y = 0; //Posi��o inicial da primeira esfera;
int posicao_esfera_2_X = -20, posicao_esfera_2_Y = -20; //Posi��o inicial da segunda esfera;
bool colisao_esferas = false; //Verificar de colis�o;
int pontos = 0; //Contador de pontos;

//Chamadas das fun��es
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
/******************************************************************************/
/*                          Fun��o principal (main)                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
int main(int argc, char **argv)  // Fun��o principal
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(450, 350);
	glutCreateWindow("Seaquest");
	init_glut();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	/* fun��o de controle do GLUT */
	glutMainLoop();

	return 0;
}
/*----------------------------------------------------------------------------*/
/******************************************************************************/
/*                         Fun��es padr�es do OpenGL                          */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
void init_glut()
{

	GLfloat luzEspecular[] = {0.00, 1.00, 1.00, 1.00}; // "Brilho"
	GLfloat posicaoLuz[] = {0.00, 50.00, 5.00, 1.00};

	// Capacidade de brilho do material
	GLfloat materialEspecular[] = {10.00, 0.50, 1.00, 1.00}; //Brilho do Material
	GLint especMaterial = 20;

	// Habilita o modelo de tonaliza��o de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a reflet�ncia do material
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialEspecular);

	// Define a concentra��o do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a defini��o da cor do material
	// a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);
	// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)  //Fun��o chamada toda vez que a janela � redimensionada
{
	glViewport(0, 0, w, h); // Ajustando o visualizador;
	glMatrixMode(GL_PROJECTION); // Trabalhando com a matriz de proje��o;
	glLoadIdentity(); // Iniciando a matriz de proje��o;
	gluPerspective(30, (GLfloat)w / (GLfloat)h, 0.1, 1000.0); //Corrigindo a perspectiva
	glMatrixMode(GL_MODELVIEW);// Voltando a trabalhar com a matriz de modelo
}

void display(void)  //Fun��o chamada a cada quadro
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
	if (key == 27) 	/* Esc: sai do programa */
	{
		exit(0);
	}
	
	switch(key)
	{

	case 'W':
		if(posicao_esfera_Y == 30) //Teste de limite de tela superior;
		{
			break;
		}
		else
		{
			posicao_esfera_Y += 10;
		}
		break;
	case 'w':
		if(posicao_esfera_Y == 30) //Teste de limite de tela superior;
		{
			break;
		}
		else
		{
			posicao_esfera_Y += 10;
		}
		break;
	case 'S':
		if(posicao_esfera_Y == -30) //Teste de limite de tela inferior;
		{
			break;
		}
		else
		{
			posicao_esfera_Y -= 10;
		}
		break;
	case 's':
		if(posicao_esfera_Y == -30) //Teste de limite de tela inferior;
		{
			break;
		}
		else
		{
			posicao_esfera_Y -= 10;
		}
		break;
	case 'A':
		if(posicao_esfera_X == -50) //Teste de limite de tela a esquerda;
		{
			break;
		}
		else
		{
			posicao_esfera_X -= 10;
		}
		break;
	case 'a':
		if(posicao_esfera_X == -50) //Teste de limite de tela a esquerda;
		{
			break;
		}
		else
		{
			posicao_esfera_X -= 10;
		}
		break;
	case 'D':
		if(posicao_esfera_X == 50) //Teste de limite de tela a direita;
		{
			break;
		}
		else
		{
			posicao_esfera_X += 10;
		}
		break;
	case 'd':
		if(posicao_esfera_X == 50) //Teste de limite de tela a direita;
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
/*----------------------------------------------------------------------------*/
/******************************************************************************/
/*                           Fun��es de desenho                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/

void desenha_esfera()  //Desenha a primeira esfera;
{
	glPushMatrix();
	glTranslatef (posicao_esfera_X, posicao_esfera_Y, -105);
	glColor3f(0.1, 0.1, 0.1);
	//glRotatef (30.0, 0.0, 0.0, 1.0);
	glutSolidSphere(5, 200, 200);
	glPopMatrix();
}

void desenha_esfera_2()  //Desenha a segunda esfera;
{
	glPushMatrix();
	if(colisao_esferas == false)
	{
		glTranslatef(posicao_esfera_2_X, posicao_esfera_2_Y, -105);
		glColor3f(0.5, 0.5, 0.5);
	}
	else //colisao_esferas == true
	{
		posicao_esfera_2_X = (rand() % 51) - 40; //Se colidiu, calcula valores aleatorios para X e Y da segunda esfera;
		posicao_esfera_2_Y = (rand() % 31) - 20;
		glTranslatef(posicao_esfera_2_X, posicao_esfera_2_Y, -105);
		colisao_esferas = false;
		glColor3f(0.5, 0.5, 0.5); //Cor cinza;
	}
	glutSolidSphere(3.5, 200, 200);
	glPopMatrix();
}

/*----------------------------------------------------------------------------*/
/******************************************************************************/
/*                               Outras fun��es                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
void testa_colisao_esferas()
{
	float distancia;
	distancia = sqrt(((posicao_esfera_2_X - posicao_esfera_X) * (posicao_esfera_2_X - posicao_esfera_X)) + ((posicao_esfera_2_Y - posicao_esfera_Y) * (posicao_esfera_2_Y - posicao_esfera_Y)));
	if(distancia <= 8.5) //Maior ou igual a soma dos raios;
	{
		colisao_esferas = true;
		pontos++; //Aumenta a quantidade de pontos;
	}
}

void desenha_texto(char *string, int x, int y, void *fonte)
{
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0); //Cor preta para o texto;
	glRasterPos2f(x, y); //Rasteriza texto
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
}
/*----------------------------------------------------------------------------*/