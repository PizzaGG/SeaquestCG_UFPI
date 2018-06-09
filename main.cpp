#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

int width = 800, height = 600; //Largura e altura da janela

void init(void);
void keyboard (unsigned char key, int x, int y);
void keyboard_special(int key, int x, int y);;
void display(void);
void reshape (int w, int h);
void mouse(int button, int state, int x, int y);
void ler_arquivo();






//------------------------------------------------------------------------------

/* Coordenadas dos vértices do objeto: */
#define N_VERTICES 4
const GLfloat vertices[N_VERTICES][3] = {
    { -0.5, -0.272,  0.289 },
    {  0.5, -0.272,  0.289 },
    {  0.0, -0.272, -0.577 },
    {  0.0,  0.544,  0.000 }
};

/* Triângulos do objeto (vértices que os constituem) */
#define N_FACES 4
const GLuint faces[N_FACES][3] = {
    {3, 0, 1},
    {3, 1, 2},
    {3, 2, 0},

    /* ATENÇÃO:                                                           *
     * De acordo com a vista superior, os vértices do triângulo da base   *
     * da pirâmide estão definidos no sentido horário, ao contrário do    *
     * que temos feito até aqui. Isso é porque, segundo a vista superior, *
     * esse triângulo está na realidade sendo visto "de costas".          */
    {0, 2, 1}
};

/* Vetores normais aos vértices do objeto: */
GLfloat vertex_normals[N_VERTICES][3];

/* Vetores normais aos triângulos do objeto: */
GLfloat face_normals[N_FACES][3];

//Estrutura criada para facilitar o entendimento
struct ponto{
    float x;
    float y;
    float z;
};
  
void normalizar(ponto * n){
	GLfloat length;
	
	length = (GLfloat) sqrt((n->x * n->x) + (n->y * n->y) + (n->z * n->z));
		
	if (length == 0.0f)
		length =  1.0f;

	n->x = n->x / length;
	n->y = n->y / length;
	n->z = n->z / length;
}
    
void calcularNormaisFaces(){
    float x[3], y[3], z[3];
    ponto a, b, n;
        
    for(int i = 0; i < N_FACES; i++){
        x[0] = vertices[faces[i][0]][0];
        y[0] = vertices[faces[i][0]][1];
        z[0] = vertices[faces[i][0]][2];
    
        x[1] = vertices[faces[i][1]][0];
        y[1] = vertices[faces[i][1]][1];
        z[1] = vertices[faces[i][1]][2];
    
        x[2] = vertices[faces[i][2]][0];
        y[2] = vertices[faces[i][2]][1];
        z[2] = vertices[faces[i][2]][2];
        
        a.x = x[2]- x[0];
        a.y = y[2]- y[0];
        a.z = z[2]- z[0];
        
        b.x = x[2]- x[1];
        b.y = y[2]- y[1];
        b.z = z[2]- z[1];
        
        n.x = a.y * b.z - a.z * b.y;
        n.y = a.z * b.x - a.x * b.z;
        n.z = a.x * b.y - a.y * b.x;
       
        normalizar(&n);
        
        face_normals[i][0] = n.x;
        face_normals[i][1] = n.y;
        face_normals[i][2] = n.z;
    }
}

void calcularNormaisVertices(){
    ponto n;
    for(unsigned int i = 0; i < N_VERTICES; i++){
        n.x = 0.0;
        n.y = 0.0;
        n.z = 0.0;
        for(int j = 0; j < N_FACES; j++){
            if(faces[j][0] == i || faces[j][1] == i || faces[j][2] == i){
                n.x += face_normals[j][0];
                n.y += face_normals[j][1];
                n.z += face_normals[j][2];
            }
        }
        
        n.x /= 3.0;
        n.y /= 3.0;
        n.z /= 3.0;        
        
        normalizar(&n);
        
        vertex_normals[i][0] = n.x;
        vertex_normals[i][1] = n.y;
        vertex_normals[i][2] = n.z;        

    }
    
}        

//------------------------------------------------------------------------------










int main(int argc, char** argv)
{
	
	calcularNormaisFaces();
    calcularNormaisVertices();
	
	//glutInit(&argc, argv); // Passagens de parametro C para o glut
	//glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); // Selecao do Modo do Display e do Sistema de cor utilizado
	//glutInitWindowSize (width, height);  // Tamanho da janela do OpenGL
	//glutInitWindowPosition (100, 100); //Posicao inicial da janela do OpenGL
	//glutCreateWindow ("Seaquest"); // Da nome para uma janela OpenGL
	init(); // Chama funcao init();
//	glutReshapeFunc(reshape); //funcao callback para redesenhar a tela
//	glutKeyboardFunc(keyboard); //funcao callback do teclado
//	glutMouseFunc(mouse); //funcao callback do mouse
//	glutDisplayFunc(display); //funcao callback de desenho
//	ler_arquivo();
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
