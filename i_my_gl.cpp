// Submitter: tryond(Tryon, Daniel) - 20621204
// Partner: boliande(Oliande, Bryan) - 13179240

#ifdef WIN32
#include <windows.h>
#endif

#include <GLUT/GLUT.h>
#include <iostream>
#include <math.h>

#include "i_my_gl.h"
// Defines maximum stack capacity.
#define STACK_CAP 16

// Defines pi for converting angles.
#define PI 3.14159265359
//GIT
// Structure for the matrix stack, top specifies current top position on the stack, initially zero (which means one matrix in the stack)
struct matrix_stack
{
    GLdouble m[STACK_CAP][16];
    int top;
};

// Define a macro for retrieving current matrix from top of current stack.
#define current_matrix (current_stack->m[current_stack->top])

// Identity matrix constant.
const GLdouble identity[16] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

// the model view matrix stack.
struct matrix_stack model_view = {{{0}}, 0};
// the projection matrix stack.
struct matrix_stack projection = {{{0}}, 0};
// The current stack pointer that specifies the matrix mode.
struct matrix_stack *current_stack = &model_view;

// Multiplies current matrix with matrix b, put the result in current matrix.
// current = current * b
void matrix_multiply(const GLdouble *b)
{
    // copy so as not to overwrite intermediary values
    GLdouble c[16] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };
    
    // each value to be computed -> 16
    for (int i = 0; i < 16; ++i)
    {
        int col = i % 4;
        int row = i - col;  // starting row index
        
        GLdouble total = 0;
        
        for (int j = 0; j < 16; j += 4)
            total += current_matrix[col+j] * b[row++];
        
        c[i] = total;
    } // end current
    
    for (int i = 0; i < 16; ++i)
    {
        current_matrix[i] = c[i];
    }
}

// Calculates cross product of b and c, put the result in a
// a = b x c
void cross_product(GLdouble *ax, GLdouble *ay, GLdouble *az,
                   GLdouble bx, GLdouble by, GLdouble bz,
                   GLdouble cx, GLdouble cy, GLdouble cz)
{
    *ax = (by * cz - bz * cy);
    *ay = (bz * cx - bx * cz);
    *az = (bx * cy - by * cx);
}

// Normalizes vector (x, y, z). Assuming x, y, and z are the vector's x, y, z components.
void normalize(GLdouble *x, GLdouble *y, GLdouble *z)
{
    GLdouble mag = (GLdouble)sqrt((*x * *x) + (*y * *y) + (*z * *z));
    *x /= mag;
    *y /= mag;
    *z /= mag;
}

//`

// Switches matrix mode by changing the current stack pointer.
/* from the red book:
 Specifies whether the modelview, projection, or texture matrix will be modified, using the argument GL_MODELVIEW, GL_PROJECTION, or GL_TEXTURE for mode. Subsequent transformation commands affect the specified matrix. Note that only one matrix can be modified at a time. By default, the modelview matrix is the one that's modifiable, and all three matrices contain the identity matrix.
 */
void I_my_glMatrixMode(GLenum mode)
{
    if(mode == GL_MODELVIEW)
    {
        current_stack = &model_view;
    }
    else
    {
        current_stack = &projection;
    }
}

// Overwrites current matrix with identity matrix.
void I_my_glLoadIdentity(void)
{
    for(int i = 0; i < 16; i++)
        current_matrix[i] = identity[i];
}

// Pushes current matrix onto current stack, report error if the stack is already full.
//from red book:
//glPushMatrix pushes the current matrix stack down by one, duplicating the current matrix. That is, after a glPushMatrix
//call, the matrix on the top of the stack is identical to the one below it.
void I_my_glPushMatrix(void)
{
    if(current_stack == &projection)
    {
        if(projection.top < STACK_CAP)// 0 => one matrix in stack STACK_CAP -1?
        {
            for(int i = 0; i < 16; i++)
            {
                current_stack->m[current_stack->top + 1][i] = current_matrix[i];
            }
            ++current_stack->top;
        }
        else
        {
            std::cout << "ERROR: projection stack full" << std::endl;
        }
    }
    
    if(current_stack == &model_view)
    {
        if(model_view.top < STACK_CAP)// 0 => one matrix in stack STACK_CAP -1?
        {
            for(int i = 0; i < 16; i++)
            {
                current_stack->m[current_stack->top + 1][i] = current_matrix[i];
            }
            ++current_stack->top;
        }
        else
        {
            std::cout << "ERROR: model_view stack full" << std::endl;
        }
        
    }
}

// Pops current matrix from current stack, report error if the stack has only one matrix left.
void I_my_glPopMatrix(void)
{
    if(current_stack == &projection)
    {
        if(projection.top < 0)// 0 => one matrix in stack
        {
            std::cout << "ERROR: projection stack already empty" << std::endl;
        }
        else
        {
            --projection.top;
        }
    }
    
    if(current_stack == &model_view)
    {
        if(model_view.top < 0)// 0 => one matrix in stack
        {
            std::cout << "ERROR: model_view stack already empty" << std::endl;
        }
        else
        {
            --model_view.top;
        }
        
    }
}

// Overwrites currentmatrix with m.
void I_my_glLoadMatrixf(const GLfloat *m)
{
    for(int i = 0; i < 16; i++)
    {
        current_matrix[i] = (GLdouble) m[i];
    }
}

void I_my_glLoadMatrixd(const GLdouble *m)
{
    for(int i = 0; i < 16; i++)
    {
        current_matrix[i] = m[i];
    }
}


void I_my_glTranslated(GLdouble x, GLdouble y, GLdouble z)
{
    // translate matrix constant.
    const GLdouble t_mat[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1
    };
    matrix_multiply(t_mat);
}

void I_my_glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
    I_my_glTranslated((GLdouble)x, (GLdouble)y, (GLdouble)z);
}

// Remember to normalize vector (x, y, z), and to convert angle from degree to radius before calling sin and cos.
void I_my_glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
{
    normalize(&x, &y, &z);
    
    GLdouble x2 = x * x;
    GLdouble y2 = y * y;
    GLdouble z2 = z * z;
    GLdouble xy = x * y;
    GLdouble yz = y * z;
    GLdouble zx = z * x;
    
    GLdouble radA = (GLdouble)(angle * PI / (GLdouble)180.0);
    
    GLdouble sinA = sin(radA);
    GLdouble cosA = cos(radA);
    
    GLdouble xSinA = x * sinA;
    GLdouble ySinA = y * sinA;
    GLdouble zSinA = z * sinA;
    
    GLdouble oCosA = 1.0 - cosA;
    
    GLdouble r_mat[16] = {
        (x2 * oCosA) + cosA, (xy * oCosA) + zSinA, (zx * oCosA) - ySinA, (GLdouble)0.0,
        (xy * oCosA) - zSinA, (y2 * oCosA) + cosA, (yz * oCosA) + xSinA, (GLdouble)0.0,
        (zx * oCosA) + ySinA, (yz * oCosA) - xSinA, (z2 * oCosA) + cosA, (GLdouble)0.0,
        (GLdouble)0.0, (GLdouble)0.0, (GLdouble)0.0, (GLdouble)1.0,
    };
    
    matrix_multiply(r_mat);
}

void I_my_glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    I_my_glRotated((GLdouble)angle, (GLdouble)x, (GLdouble)y, (GLdouble)z);
}

void I_my_glScaled(GLdouble x, GLdouble y, GLdouble z)
{
    // scaling matrix constant.
    const GLdouble s_mat[16] = {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    };
    matrix_multiply(s_mat);
}

void I_my_glScalef(GLfloat x, GLfloat y, GLfloat z)
{
    I_my_glScaled((GLdouble)x, (GLdouble)y, (GLdouble)z);
}

// Copes current matrix to m.
void I_my_glGetMatrixf(GLfloat *m)
{
    for(int i = 0; i < 16; i++)
    {
        current_matrix[i] = (GLdouble)m[i];
    }
}

void I_my_glGetMatrixd(GLdouble *m)
{
    for(int i = 0; i < 16; i++)
    {
        m[i] = current_matrix[i];
    }
}

// Remember to normalize vectors.
void I_my_gluLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
                    GLdouble centerX, GLdouble centerY, GLdouble centerZ,
                    GLdouble upX, GLdouble upY, GLdouble upZ)
{
    GLdouble vx, vy, vz;    // normalized look
    GLdouble sx, sy, sz;    // normalized x-vector
    GLdouble ux, uy, uz;    // normalized up
    
    vx = centerX - eyeX;
    vy = centerY - eyeY;
    vz = centerZ - eyeZ;
    
    normalize(&vx, &vy, &vz);
    normalize(&upX, &upY, &upZ);
    
    cross_product(&sx, &sy, &sz, vx, vy, vz, upX, upY, upZ);
    cross_product(&ux, &uy, &uz, sx, sy, sz, vx, vy, vz);
    
    //redundant test - fixes size issue but shouldn't be necessary - investigate further
    normalize(&sx, &sy, &sz);
    normalize(&ux, &uy, &uz);
    
    GLdouble r_mat[16] ={
        sx, ux, -vx, 0,
        sy, uy, -vy, 0,
        sz, uz, -vz, 0,
        0, 0, 0, 1
    };
    
    // rotate to match x,y,z
    matrix_multiply(r_mat);
    
    I_my_glTranslated(-eyeX, -eyeY, -eyeZ);
}

void I_my_glFrustum(GLdouble left, GLdouble right, GLdouble bottom,
                    GLdouble top, GLdouble zNear, GLdouble zFar)
{
    GLdouble a = (2 * zNear) / (right -left);
    GLdouble b = (2 * zNear) / (top - bottom);
    GLdouble c = (right + left) / (right - left);
    GLdouble d = (top + bottom) / (top - bottom);
    GLdouble e = -(zFar + zNear) / (zFar - zNear);
    GLdouble f = -(2 * zFar * zNear) / (zFar - zNear);
    
    GLdouble f_mat[16] = {
        a, 0, 0, 0,
        0, b, 0, 0,
        c, d, e, -1,
        0, 0, f, 0
    };
    
    matrix_multiply(f_mat);
}

// Based on the inputs, calculate left, right, bottom, top, and call I_my_glFrustum accordingly
// remember to convert fovy from degree to radius before calling tan
void I_my_gluPerspective(GLdouble fovy, GLdouble aspect,
                         GLdouble zNear, GLdouble zFar)
{
    GLdouble l, r, b, t;
    t = zNear * (GLdouble)tan((fovy * PI) / (GLdouble)360.0);
    b = -t;
    l = b * aspect;
    r = t * aspect;
    
    I_my_glFrustum(l, r, b, t, zNear, zFar);
}


//PrintMat should just print out the values of all 16 entries of the given matrix
void printMat(GLdouble m[])
{
    for (int i = 0; i < 16; ++i)
    {
        if (!(i & 4))
            std::cout << std::endl;
        std::cout << m[i] << ' ';
    }
}

// compareMat raises the flag if the matrices don't match.
// Returns TRUE if matrices dont match, false otherwise
bool compareMat(GLdouble m1[], GLdouble m2[])
{
    for(int i = 0; i < 16; ++i)
    {
        if(m1[i] != m2[i])
        {
            return true;
        }
    }
    return false;
}



