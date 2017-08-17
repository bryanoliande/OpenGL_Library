// Submitter: tryond(Tryon, Daniel) - 20621204
// Partner: boliande(Oliande, Bryan) - 13179240

/*
 * OpenGL demonstration program for UCI ICS Computer Graphics courses
 * sceneModule.cpp,v 2.1 2016/10/05 11:38 pm
 *
 */

#include "sceneModule.h"

#include "my_gl.h"

#include <math.h>
#define PI 3.14159265359

GLfloat angley = 20;    /* in degrees */
GLfloat anglex = 30;   /* in degrees */
GLfloat distanceX = 0.0;
GLfloat distanceY = 0.0;
GLfloat distanceZ = 5.0;

GLfloat rotate = 0.0;
GLfloat speed = 2.0;

static float cubeColors[6][4] =
{
    {0.8, 0.8, 0.8, 1.0},
    {0.8, 0.0, 0.0, 1.0},
    {0.0, 0.8, 0.0, 1.0},
    {0.0, 0.0, 0.8, 1.0},
    {0.0, 0.8, 0.8, 1.0},
    {0.8, 0.0, 0.8, 1.0},
};

static float cubeVertexes[6][4][4] =
{
    {
        {-1.0, -1.0, -1.0, 1.0},
        {-1.0, -1.0, 1.0, 1.0},
        {-1.0, 1.0, 1.0, 1.0},
        {-1.0, 1.0, -1.0, 1.0}},
    
    {
        {1.0, 1.0, 1.0, 1.0},
        {1.0, -1.0, 1.0, 1.0},
        {1.0, -1.0, -1.0, 1.0},
        {1.0, 1.0, -1.0, 1.0}},
    
    {
        {-1.0, -1.0, -1.0, 1.0},
        {1.0, -1.0, -1.0, 1.0},
        {1.0, -1.0, 1.0, 1.0},
        {-1.0, -1.0, 1.0, 1.0}},
    
    {
        {1.0, 1.0, 1.0, 1.0},
        {1.0, 1.0, -1.0, 1.0},
        {-1.0, 1.0, -1.0, 1.0},
        {-1.0, 1.0, 1.0, 1.0}},
    
    {
        {-1.0, -1.0, -1.0, 1.0},
        {-1.0, 1.0, -1.0, 1.0},
        {1.0, 1.0, -1.0, 1.0},
        {1.0, -1.0, -1.0, 1.0}},
    
    {
        {1.0, 1.0, 1.0, 1.0},
        {-1.0, 1.0, 1.0, 1.0},
        {-1.0, -1.0, 1.0, 1.0},
        {1.0, -1.0, 1.0, 1.0}}
};

void drawScene(){
    
    for (int i = 0; i < 6; i++) {
        glBegin(GL_POLYGON);
        glColor3fv(&cubeColors[i][0]);
        glVertex4fv(&cubeVertexes[i][0][0]);
        glVertex4fv(&cubeVertexes[i][1][0]);
        glVertex4fv(&cubeVertexes[i][2][0]);
        glVertex4fv(&cubeVertexes[i][3][0]);
        glEnd();
    }
}

void sceneTransformation(){
    glLoadIdentity( );
    
//    glTranslatef(-distanceX, distanceY, -distanceZ);
//    glRotatef( anglex, 1.0, 0.0, 0.0 );
//    glRotatef( angley, 0.0, 1.0, 0.0 );
    
    // *************************************************************************
    // TEST CASE 2
    // *************************************************************************

    // eye position is moving around the circle, always looking at the center of the cube
    GLdouble theta = (GLdouble)-(anglex * PI / (GLdouble)180.0);
    GLdouble phi = (GLdouble)(angley * PI / (GLdouble)180.0);
    
    GLdouble radius = (GLdouble)sqrt(distanceX * distanceX + distanceY * distanceY + distanceZ * distanceZ);
    
    GLdouble ex = radius * sin(theta) * sin(phi);
    GLdouble ey = radius * cos(theta);
    GLdouble ez = radius * sin(theta) * cos(phi);
    
    GLdouble ux = (radius * sin(theta - 1) * sin(phi)) - ex;
    GLdouble uy = (radius * cos(theta - 1)) - ey;
    GLdouble uz = (radius * sin(theta - 1) * cos(phi)) - ez;
    
    gluLookAt(ex, ey, ez, 0, 0, 0, ux, uy, uz);
}

void display(){
//    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//    
//    /* Set up transformation */
//    sceneTransformation();
//    /* Draw the scene into the back buffer */
//    drawScene();
//    
//    /* Swap the front buffer with the back buffer - assumes double buffering */
//    glutSwapBuffers();
    
    // *************************************************************************
    // TEST CASE 3
    // *************************************************************************

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    /* Set up transformation */
    sceneTransformation();
    
    my_glPushMatrix();
    
    // scale down whole scene
    my_glScaled(0.25, 0.25, 0.25);
    
    // draw "Spinner"
    my_glPushMatrix();
    my_glScaled(2.0, 2.0, 2.0);
    my_glRotated(rotate, 0, 1, 0);
    drawScene();
    my_glPopMatrix();
    
    // draw "Revolver"
    my_glPushMatrix();
    my_glRotated(rotate, 0, 1, 0);
    my_glTranslated(6, 0, 0);
    drawScene();
    my_glPopMatrix();
    
    my_glPopMatrix();
    
    // update rotate
    rotate += speed;
    if (rotate >= 360)
        rotate = 0;
    
    /* Swap the front buffer with the back buffer - assumes double buffering */
    glutSwapBuffers();
    
    glutPostRedisplay();
}
