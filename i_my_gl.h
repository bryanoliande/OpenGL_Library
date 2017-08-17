// Submitter: tryond(Tryon, Daniel) - 20621204
// Partner: boliande(Oliande, Bryan) - 13179240

void I_my_glMatrixMode(GLenum mode);
void I_my_glLoadIdentity(void);
void I_my_glPushMatrix(void);
void I_my_glPopMatrix(void);
void I_my_glLoadMatrixf(const GLfloat *m);
void I_my_glLoadMatrixd(const GLdouble *m);
void I_my_glTranslated(GLdouble x, GLdouble y, GLdouble z);
void I_my_glTranslatef(GLfloat x, GLfloat y, GLfloat z);
void I_my_glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
void I_my_glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
void I_my_glScaled(GLdouble x, GLdouble y, GLdouble z);
void I_my_glScalef(GLfloat x, GLfloat y, GLfloat z);
void I_my_glGetMatrixf(GLfloat *m);
void I_my_glGetMatrixd(GLdouble *m);
void I_my_gluLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, 
    GLdouble centerX, GLdouble centerY, GLdouble centerZ, 
    GLdouble upX, GLdouble upY, GLdouble upZ);
void I_my_glFrustum(GLdouble left, GLdouble right, GLdouble bottom,
    GLdouble top, GLdouble zNear, GLdouble zFar);
void I_my_gluPerspective(GLdouble fovy, GLdouble aspect, 
    GLdouble zNear, GLdouble zFar);
    


//Implementing printMat and compareMat in i_my_gl
//PrintMat should just print out the values of all 16 entries of the given matrix, and compareMat should compare two matrices element by element.

void printMat(GLdouble m[]);
bool compareMat(GLdouble m1[], GLdouble m2[]);
void matrix_multiply(const GLdouble *b);

#define debug true

