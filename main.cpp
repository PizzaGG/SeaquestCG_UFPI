#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <SDL/SDL.h>

int width = 800, height = 600; //Largura e altura da janela

void init(void);
void keyboard (unsigned char key, int x, int y);
void keyboard_special(int key, int x, int y);;
void display(void);
void reshape (int w, int h);
void mouse(int button, int state, int x, int y);
void ler_arquivo();

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Passagens de parametro C para o glut
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); // Selecao do Modo do Display e do Sistema de cor utilizado
	glutInitWindowSize (width, height);  // Tamanho da janela do OpenGL
	glutInitWindowPosition (100, 100); //Posicao inicial da janela do OpenGL
	glutCreateWindow ("Seaquest"); // Da nome para uma janela OpenGL
	init(); // Chama funcao init();
	glutReshapeFunc(reshape); //funcao callback para redesenhar a tela
	glutKeyboardFunc(keyboard); //funcao callback do teclado
	glutMouseFunc(mouse); //funcao callback do mouse
	glutDisplayFunc(display); //funcao callback de desenho
	ler_arquivo();
	glutMainLoop(); // executa o loop do OpenGL
	return 0; // retorna 0 para o tipo inteiro da funcao main();
}

// Funcao com alguns comandos para a inicializacao do OpenGL;
void init(void)
{
//	glClearColor(1.0, 1.0, 1.0, 1.0); //Limpa a tela com a cor branca;
	glClearColor(0.0, 0.0, 0.7, 0.0);

}

void reshape(int w, int h)
{
	// Definindo o Viewport para o tamanho da janela
	glViewport(0, 0, w, h);

	// Reinicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	width = w;
	height = h;
	glOrtho (0, w, 0, h, -1 , 1);

	// muda para o modo GL_MODELVIEW (não pretendemos alterar a projecção
	// quando estivermos a desenhar na tela)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Funcao usada na funcao callback para utilizacao das teclas normais do teclado
void keyboard(unsigned char key, int x, int y)
{
	switch (key)   // key - variavel que possui valor ASCII da tecla precionada
	{
	case 27: // codigo ASCII da tecla ESC
		exit(0); // comando pra finalizacao do programa
		break;
	}
}

//Funcao usada na funcao callback para a utilizacao do mouse
void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
		break;
		/*
		      case GLUT_MIDDLE_BUTTON:
		         if (state == GLUT_DOWN) {
		            glutPostRedisplay();
		         }
		         break;
		      case GLUT_RIGHT_BUTTON:
		         if (state == GLUT_DOWN) {
		            glutPostRedisplay();
		         }
		         break;
		*/
	default:
		break;
	}
}

// Funcao usada na funcao callback para desenhar na tela
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //Limpa o Buffer de Cores
	//glColor3f (0.0, 0.0, 0.0); // Seleciona a cor default como preto
	glutSwapBuffers(); // manda o OpenGl renderizar as primitivas

}

void ler_arquivo()
{
	FILE *fp;

	if((fp = fopen("Fun.bmp", "rw")) == NULL)
	{
		printf("Impossivel abrir o arquivo.\n");
		getchar();
		exit(1);
	}
}
