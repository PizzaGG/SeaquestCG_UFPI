#include <GL/gl.h> // Biblioteca Padr�o do OpenGL
#include <GL/glut.h> //Biblioteca Padr�o do GLUT, em alguns sistemas ela chama o freeglut sem precisar declarar freeglut.h
#include <stdio.h> // Biblioteca C padr�o para controle de entrade e saida.

//Globais

float pos_X = 0, pos_Y = 0, pos_Z = -105;

GLuint car; //inteiro especial do OpenGL, os "objetos" gravados no OpenGL s�o chamados por numero, gravado no pr�prio OpenGL e n�o no programa
float carrot; //float para controle de movimenta��o.


void init_glut(const char *window_name, int argc, char** argv);
void desenha_objeto();
//void desenha_objetoMOVIMENTO(float x, float y, float z);
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

/**********************************************************************/
/*                                                                    */
/*                       Fun��o principal (main)                      */
/*                                                                    */
/**********************************************************************/
int main(int argc, char **argv)  // Fun��o principal
{
	init_glut("Seaquest", argc, argv);

	/* fun��o de controlo do GLUT */
	glutMainLoop();

	return 0;
}


/**********************************************************************/
/*                                                                    */
/*                         Carrega objeto                             */
/*                                                                    */
/**********************************************************************/
void carregaObjeto()  //*fname � nome do arquivo, como � ponteiro � chamado como uma string.
{
	FILE *fp; //Ponteiro que representa o arquivo dentro desta fun��o
	int read; //inteiro que pegar� o numero de par�metros recebidos da linha
	GLfloat x, y, z; // Float que armazenara os valores de cada linha de x, y, z
	char ch; //primeiro caratere lido de cada linha
	car = glGenLists(1); //Vari�vel global recebendo o numero que representar� o objeto no OpenGL.
	fp = fopen("submarine.obj"/*fname*/, "r"); //instanciando o arquivo em modo somente de leitura
	if(!fp)  //se o fp retornar falso, ou seja n�o funcionou como deveria
	{
		//printf("can�t open file %s\n"); //Reposta dado ao usu�rio
		exit(1); //chamando a sa�da do programa.
	}
	glPointSize(100.0); //Especifica o di�metro dos pontos.
	glNewList(car, GL_COMPILE); //Especificando que o objeto ficar� em uma lista do OpenGL, referenciado pelo numero car.
	{
		glPushMatrix(); //Coloca a matriz posterior como a atual, ou seja aquela que ser� trabalhada.
		glBegin(GL_POINTS); //Defini que a matriz ser� representado com pontos.
		while(!(feof(fp)))  //Enquanto n�o chegar o final do arquivo
		{
			read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z); //numero de par�metros recebidos, al�m disso coloca valores na variavel ch,x,y,z
			if(read == 4 && ch == 'v') // se o numero de parametros recebidos for 4 e o primeiro carater for v ent�o
			{
				glVertex3f(x, y, z); //Fun��o que manda a linha das matrizes para o OpenGL
			}
		}
		glEnd(); //Fim da composi��o da Matriz
	}
	glPopMatrix(); //A Matrix anterior n�o est� sendo trabalhada
	glEndList(); //A Lista est� pronta.
	fclose(fp); //O arquivo ent�o ser� fechado
}
//fim do obj loader

void init_glut(const char *nome_janela, int argc, char** argv)
{
	glutInit(&argc, argv); //Incializando o GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Definindo o modo, memoria, em RGB, Com profundidade
	glutInitWindowSize(800, 800); // Tamanho da Janela
	glutInitWindowPosition(20, 20); //Posi��o inicial da janela
	glutCreateWindow("Seaquest"); //Nome da Janela
	carregaObjeto(); //Carrega o arquivo .obj
	glutReshapeFunc(reshape); //Chama a fun��o quando a tela for redimensionada
	glutDisplayFunc(display); //Chama a fun��o a cada frame da tela
	glutIdleFunc(display); //Chama esta fun��o quando n�o estiver fazendo nada.
	glutKeyboardFunc(keyboard);
	glutMainLoop(); // Cria um loop que volta para as fun��es anteriores
}

void reshape(int w, int h)  //Fun��o chamada toda vez que a janela � redimensionada
{
	glViewport(0, 0, w, h); // Ajustando o visualizador
	glMatrixMode(GL_PROJECTION); // Trabalhando com a matriz de proje��o
	glLoadIdentity(); // Iniciando a Matriz de cima
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0); //Corrigindo a perspectiva
	//glortho(-25,25,-2,2,0.1,100); //M�todo alternativo de fazer o mesmo
	glMatrixMode(GL_MODELVIEW);// Voltando a trabalhar com a matriz de modelo
}

void desenha_objeto()  //Fun��o de movimenta��o
{
	glPushMatrix(); //Abrindo as matrizes do modelo
	glTranslatef(pos_X, pos_Y, pos_Z); // Fun��o para movimentar, X, Y, Z
	glColor3f(0.5, 0.5, 0.5);
	glScalef(0.2, 0.0, 0.0); // Fun��o da escalonar
	glRotatef(carrot, 0, 1, 0); //Fun��o para rodar grau, e ( x, y, z = sob os eixos que ocorrer� a movimenta��o)
	glCallList(car); //Chamando o nosso objeto incializado por numero
	glPopMatrix(); // Fechando a matriz
	carrot = carrot + 0.6; //Aumentando em mais 0.6 o valor do carrot
	if(carrot > 360)carrot = carrot - 360; //Se o carrot passar de 360� volte a 0
}

void display(void)  //Fun��o chamada a cada quadro
{
	glClearColor(0.0, 0.0, 1.0, 1.0); //Cor de fundo
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpar tela
	glLoadIdentity(); //Carregar as entidades
	//chamada da fun��o acima.
	desenha_objeto();
	glutSwapBuffers(); //auxiliar na troca dos buffers(trabalha com a memoria)
}

void keyboard(unsigned char key, int x, int y)
{
	//if (key == 27) exit(0); /* Esc: sai do programa */
	switch(key)
	{

	case 'W':
		if(pos_Y == 60)
		{
			break;
		}
		else
		{
			pos_Y += 10;
		}
		break;
	case 'w':
		if(pos_Y == 60)
		{
			break;
		}
		else
		{
			pos_Y += 10;
		}
		break;
	case 'S':
		if(pos_Y == -60)
		{
			break;
		}
		else
		{
			pos_Y -= 10;
		}
		break;
	case 's':
		if(pos_Y == -60)
		{
			break;
		}
		else
		{
			pos_Y -= 10;
		}
		break;
	case 'A':
		if(pos_X == -110)
		{
			break;
		}
		else
		{
			pos_X -= 10;
		}
		break;
	case 'a':
		if(pos_X == -110)
		{
			break;
		}
		else
		{
			pos_X -= 10;
		}
		break;
	case 'D':
		if(pos_X == 110)
		{
			break;
		}
		else
		{
			pos_X += 10;
		}
		break;
	case 'd':
		if(pos_X == 110)
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