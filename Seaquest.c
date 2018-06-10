#include <GL/gl.h> // Biblioteca Padrão do OpenGL
#include <GL/glut.h> //Biblioteca Padrão do GLUT, em alguns sistemas ela chama o freeglut sem precisar declarar freeglut.h
#include <stdio.h> // Biblioteca C padrão para controle de entrade e saida.

//Globais

float pos_X = 0, pos_Y = 0, pos_Z = -105;

GLuint car; //inteiro especial do OpenGL, os "objetos" gravados no OpenGL são chamados por numero, gravado no próprio OpenGL e não no programa
float carrot; //float para controle de movimentação.

void init_glut();
void desenha_principal();
void desenha_2();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

/**********************************************************************/
/*                                                                    */
/*                       Função principal (main)                      */
/*                                                                    */
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

//void init_glut(const char *nome_janela, int argc, char** argv)
void init_glut()
{

	GLfloat luzAmbiente[] = {0.00, 0.00, 0.00, 1.00};
	GLfloat luzDifusa[] = {1.00, 1.00, 1.00, 1.00};		 // "cor"
	GLfloat luzEspecular[] = {0.00, 1.00, 1.00, 1.00}; // "brilho"
	//GLfloat posicaoLuz[4] = {0.0, 50.0, 50.0, 1.0};
	GLfloat posicaoLuz[] = {0.00, 50.00, 5.00, 1.00};

	// Capacidade de brilho do material
	GLfloat materialAmbiente[] = {0.00, 0.00, 0.00, 1.00};
	GLfloat materialDifusa[] = {1.00, 0.50, 0.50, 1.00};
	GLfloat materialEspecular[] = {1.00, 0.50, 1.00, 1.00}; //Ks
	GLfloat materialEmissiva[] = {0.00, 0.00, 0.00, 0.00};
	GLint especMaterial = 128;

	// Especifica que a cor de fundo da janela será preta
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Habilita o modelo de tonalização de Gouraud
	//glShadeModel(GL_SMOOTH);
	glShadeModel(GL_FLAT);

	// Define a refletância do material
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDifusa);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialEspecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, materialEmissiva);
	// Define a concentração do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
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

	/*
	glutInit(&argc, argv); //Incializando o GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Definindo o modo, memoria, em RGB, Com profundidade
	glutInitWindowSize(800, 800); // Tamanho da Janela
	glutInitWindowPosition(20, 20); //Posição inicial da janela
	glutCreateWindow("Seaquest"); //Nome da Janela
	carregaObjeto(); //Carrega o arquivo .obj
	glutReshapeFunc(reshape); //Chama a função quando a tela for redimensionada
	glutDisplayFunc(display); //Chama a função a cada frame da tela
	glutIdleFunc(display); //Chama esta função quando não estiver fazendo nada.
	glutKeyboardFunc(keyboard);
	glutMainLoop(); // Cria um loop que volta para as funções anteriores */
}

void reshape(int w, int h)  //Função chamada toda vez que a janela é redimensionada
{
	glViewport(0, 0, w, h); // Ajustando o visualizador
	glMatrixMode(GL_PROJECTION); // Trabalhando com a matriz de projeção
	glLoadIdentity(); // Iniciando a Matriz de cima
	gluPerspective(30, (GLfloat)w / (GLfloat)h, 0.1, 1000.0); //Corrigindo a perspectiva
	//glortho(-25,25,-2,2,0.1,100); //Método alternativo de fazer o mesmo
	glMatrixMode(GL_MODELVIEW);// Voltando a trabalhar com a matriz de modelo
}



void desenha_principal()  //Função de movimentação
{
	/*
	glPushMatrix(); //Abrindo as matrizes do modelo
	glTranslatef(pos_X, pos_Y, pos_Z); // Função para movimentar, X, Y, Z
	glColor3f(0.5, 0.5, 0.5);
	glScalef(0.2, 0.0, 0.0); // Função da escalonar
	glRotatef(carrot, 0, 1, 0); //Função para rodar grau, e ( x, y, z = sob os eixos que ocorrerá a movimentação)
	glCallList(car); //Chamando o nosso objeto incializado por numero
	glPopMatrix(); // Fechando a matriz
	carrot = carrot + 0.6; //Aumentando em mais 0.6 o valor do carrot
	if(carrot > 360)carrot = carrot - 360; //Se o carrot passar de 360º volte a 0 */

	glPushMatrix();
	glTranslatef (pos_X, pos_Y, pos_Z);
	glColor3f(0.5, 0.5, 0.5);
	//glScalef(0.2, 0.0, 0.0);
//	glRotatef (90.0, 0.0, 0.0, 1.0);

	glutSolidCube (10);
	glPopMatrix();
}


void desenha_2()  //Função de movimentação
{
	/*
	glPushMatrix(); //Abrindo as matrizes do modelo
	glTranslatef(pos_X, pos_Y, pos_Z); // Função para movimentar, X, Y, Z
	glColor3f(0.5, 0.5, 0.5);
	glScalef(0.2, 0.0, 0.0); // Função da escalonar
	glRotatef(carrot, 0, 1, 0); //Função para rodar grau, e ( x, y, z = sob os eixos que ocorrerá a movimentação)
	glCallList(car); //Chamando o nosso objeto incializado por numero
	glPopMatrix(); // Fechando a matriz
	carrot = carrot + 0.6; //Aumentando em mais 0.6 o valor do carrot
	if(carrot > 360)carrot = carrot - 360; //Se o carrot passar de 360º volte a 0 */

	glPushMatrix();
	glTranslatef (pos_X+10, pos_Y+10, pos_Z);
	glColor3f(0.5, 0.5, 0.5);
	//glScalef(0.2, 0.0, 0.0);
//	glRotatef (90.0, 0.0, 0.0, 1.0);

	glutSolidCube (10);
	glPopMatrix();


}

void display(void)  //Função chamada a cada quadro
{
	glClearColor(0.0, 0.0, 1.0, 1.0); //Cor de fundo
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpar tela
	glLoadIdentity(); //Carregar as entidades
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//chamada da função acima.
	desenha_principal();
	glutSwapBuffers(); //auxiliar na troca dos buffers(trabalha com a memoria)
}

void keyboard(unsigned char key, int x, int y)
{
	//if (key == 27) exit(0); /* Esc: sai do programa */
	switch(key)
	{

	case 'W':
		if(pos_Y == 30)
		{
			break;
		}
		else
		{
			pos_Y += 10;
		}
		break;
	case 'w':
		if(pos_Y == 30)
		{
			break;
		}
		else
		{
			pos_Y += 10;
		}
		break;
	case 'S':
		if(pos_Y == -30)
		{
			break;
		}
		else
		{
			pos_Y -= 10;
		}
		break;
	case 's':
		if(pos_Y == -30)
		{
			break;
		}
		else
		{
			pos_Y -= 10;
		}
		break;
	case 'A':
		if(pos_X == -60)
		{
			break;
		}
		else
		{
			pos_X -= 10;
		}
		break;
	case 'a':
		if(pos_X == -50)
		{
			break;
		}
		else
		{
			pos_X -= 10;
		}
		break;
	case 'D':
		if(pos_X == 50)
		{
			break;
		}
		else
		{
			pos_X += 10;
		}
		break;
	case 'd':
		if(pos_X == 50)
		{
			break;
		}
		else
		{
			pos_X += 10;
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
