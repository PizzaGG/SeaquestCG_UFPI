#include <sdtio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

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

void init_glut(const char *nome_janela, int argc, char** argv){
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {25.0};
    GLfloat light_position[] = {-1.0, 1.0, 1.0, 0.0};


    /* inicia o GLUT */
    glutInit(&argc,argv);

    /* inicia o display usando RGB e double-buffering */
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,100);
    glutCreateWindow(nome_janela);

    /* define as funcões de callback */
    glutKeyboardFunc(keyboard_callback);
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutSpecialFunc(keyboard_callback_special);

//    glutIdleFunc(animate_callback);
    glutTimerFunc(10, timer_callback,10);
    
    /* Inicia as características gerais dos materiais */
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    /* Inicia a iluminação */
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    /* Ativa o modelo de sombreagem de "Gouraud". */
    glShadeModel(GL_SMOOTH);

    /* Ativa o z-buffering, de modo a remover as superfícies escondidas */
    glEnable(GL_DEPTH_TEST);

    /* define a cor com a qual o ecrã será apagado */
    glClearColor(1.0, 1.0, 1.0, 1.0);

    /* define a cor de desenho inicial (azul) */
    glColor3f(0.0, 0.0, 1.0);
}

void draw_object_smooth(void){
    GLuint i;

    /* Desenha todos os triângulos do objeto */
    glBegin(GL_TRIANGLES);
        for (i=0; i<N_FACES; i++){
            glNormal3fv(vertex_normals[faces[i][0]]);
            glVertex3fv(vertices[faces[i][0]]);

            glNormal3fv(vertex_normals[faces[i][1]]);
            glVertex3fv(vertices[faces[i][1]]);

            glNormal3fv(vertex_normals[faces[i][2]]);
            glVertex3fv(vertices[faces[i][2]]);
        }
    glEnd();
}



