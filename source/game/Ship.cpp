#include "Ship.h"

Ship::Ship()
{
    pts = new float[30]{
        //top
         0.0f, 1.0f,0.25f,  //0 front
         1.0f,-0.5f,0.25f,  //1 right
         1.0f,-1.0f,0.25f,  //2 rear right
        -1.0f,-1.0f,0.25f,  //3 rear left
        -1.0f,-0.5f,0.25f,  //4 left
        //bottom
         0.0f, 1.0f,-0.25f, //5 front
         1.0f,-0.5f,-0.25f, //6 right
         1.0f,-1.0f,-0.25f, //7 rear right
        -1.0f,-1.0f,-0.25f, //8 rear left
        -1.0f,-0.5f,-0.25f};//9 left

    ind = new int[48]{
         0,1,2,0,2,3,0,3,4, //top
         5,7,6,5,8,7,5,9,8, //bottom
         3,2,8,2,7,8,       //back
         4,3,8,4,8,9,       //left
         2,1,6,2,6,7,       //right
         0,4,9,0,9,5,       //frontleft
         1,0,6,0,5,6//right
         };

    deltaX = 0.0f;
    deltaY = 0.0f;
    fieldDepth = -60.0f;
    yRotate = 0.0f;
    zRotate = 0.0f;
    loc = new float[2]{0,0};
    roll = 0;
    bearing = 90;
    weaponSound.load("data/audio/dwang.ogg");
}

Ship::Ship(float pFieldDepth)
{
    pts = new float[30]{
        //top
         0.0f, 1.0f,0.25f,  //0 front
         1.0f,-0.5f,0.25f,  //1 right
         1.0f,-1.0f,0.25f,  //2 rear right
        -1.0f,-1.0f,0.25f,  //3 rear left
        -1.0f,-0.5f,0.25f,  //4 left
        //bottom
         0.0f, 1.0f,-0.25f, //5 front
         1.0f,-0.5f,-0.25f, //6 right
         1.0f,-1.0f,-0.25f, //7 rear right
        -1.0f,-1.0f,-0.25f, //8 rear left
        -1.0f,-0.5f,-0.25f};//9 left

    ind = new int[48]{
         0,1,2,0,2,3,0,3,4, //top
         5,7,6,5,8,7,5,9,8, //bottom
         3,2,8,2,7,8,       //back
         4,3,8,4,8,9,       //left
         2,1,6,2,6,7,       //right
         0,4,9,0,9,5,       //frontleft
         1,0,6,0,5,6//right
         };

    forwardForce = 0.05f;
    reverseForce = -0.03f;
    sideForce = 0.03f;
    rotateForce = 1.0f;
    deltaX = 0.0f;
    deltaY = 0.0f;
    deltaRoll = 2;
    fieldDepth = pFieldDepth;
    yRotate = 0.0f;
    zRotate = 0.0f;
    loc = new float[2]{0,0};
    roll = 0;
    bearing = 90;
    scale = 1;
}

Ship::~Ship()
{
    delete pts;
    delete ind;
    delete loc;

    pts = NULL;
    ind = NULL;
    loc = NULL;
}

void Ship::render()
{
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(loc[0],loc[1],fieldDepth);
	glTranslatef(0,0,0); //ctr
	glRotatef(bearing-90,0,0,1);
	glRotatef(roll,0,1,0);
	glScalef(1,1,1);
	glTranslatef(0,0,0);//-ctr

    glBegin(GL_TRIANGLES);
        for (int i = 0; i < 48; i++)
        {
            if (i == 0)
                glColor3f(1.0f,0.0f,0.0f);
            else if (i == 18)
                glColor3f(0.7f,0.7f,1.0f);
            else if (i == 24)
                glColor3f(0.0f,0.0f,1.0f);

            glVertex3f(pts[ind[i]*3],pts[ind[i]*3+1],pts[ind[i]*3+2]);
        }
    glEnd();
    glPopMatrix();
}

void Ship::fire()
{
    //Ima firin mah Lazer!!!!!
    weaponSound.play();
}
//todo: incorperate accel and decel && switch roll and bering back to floats
void Ship::forwardThrust()
{
    yMove(forwardForce);
}

void Ship::reverseThrust()
{
    yMove(reverseForce);
}

void Ship::strafeRight()
{
    xMove(sideForce);
}

void Ship::strafeLeft()
{
    xMove(-sideForce);
}

void Ship::turnRight()
{
    bearing -= 1;
}

void Ship::turnLeft()
{
    bearing += 1;
}

void Ship::rollRight()
{
    if (roll < 90)
        roll += deltaRoll;
}

void Ship::rollLeft()
{
    if (roll > -90)
        roll -= deltaRoll;
}

void Ship::xMove(float thrust)
{
    loc[0] += thrust * sin(bearing * 3.14159/180);
    loc[1] += thrust * cos(bearing * 3.14159/180);
}

void Ship::yMove(float thrust)
{
    loc[0] += thrust * cos(bearing * 3.14159/180);
    loc[1] += thrust * sin(bearing * 3.14159/180);
}

void Ship::rollReset()
{
    if (roll > 0)
        roll -=deltaRoll;
    if (roll < 0)
        roll +=deltaRoll;
}
