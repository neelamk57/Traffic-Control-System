#include<windows.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<iostream>

using namespace std;


GLint windowWidth = 800, windowHeight = 600;

float x_cor=800,y_cor=450;//coordinate reference for cars

float x_road,x_veh=-0.8,x_car=0,x_human=0, y_human=0; //component (x,y) references

float x_background = 0.0; // background x coordinate

int value = 0;//start status flag

const double TWO_PI = 6.2831853;

GLint traff_color;//traffic status flag

GLint acc_status=0;// accident status flag




//components display call function
void display();

//text display function
void drawstring(int, int, char*);

//main menu implementation functions
void menu(int);
void create_menu();
void text();

//menu options
void start();
void about();
void instruction();

//input functions
void keyboard (unsigned char, int, int);
void moveFcn(GLint, GLint, GLint );

//functions translating background on input command
void stop();
void move_car_backward();
void move_car_forward();


//viewframe background create functions

void market(int);
void residence(int);
void forest(int);
void highway(int);
void road(int);

//components of viewframe functions
void home(float);
void streetlight(float);
void tree(float,float);
void truck(float);
void carA( float);
void car(float);
void wheel(float , float ,float);
void trafficLights(float, long );
void human(float , float , GLint);

//status check functions
void status();
void check_accident( float);
void regHex(GLint, GLint);









void initialize()
{
    glClearColor(0.1,0.5,0.7,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,800.0,0.0,600.0);
    glClear(GL_COLOR_BUFFER_BIT);
 //   text();
}

class point
{
    GLint x,y;
public:
    point(){x=0;y=0;}

    void setCoord(GLint xCoord, GLint yCoord)
    {
        x = xCoord; y= yCoord;
    }
    GLint getx() const{return x;}
    GLint gety() const{return y;}

    void increment_x(){x++;}
    void decrement_y(){y--;}
};


void regHex(GLint x_cent, GLint y_cent)
{

    point hexVertex, circCenter;
    circCenter.setCoord(x_cent,y_cent);
     glBegin(GL_POLYGON);
            for(int k = 0;k<6;k++)
            {
                GLdouble theta = TWO_PI * k/6.0;//theta = (n-2)*pi/n interior angle
                hexVertex.setCoord(circCenter.getx()+ 15 * cos(theta),
                                            circCenter.gety() + 15 *sin(theta));
                glVertex2i(hexVertex.getx(),hexVertex.gety());
            }
        glEnd();
}

void check_accident( float x_street)
{
    if((int)x_street%4000==0)
    {
        if((traff_color==3)&&(x_street==-(x_background)))
        {
            cout<<"accident"<<endl<<x_street<<endl<<x_background<<endl;
            acc_status=-1;
        }
        else if(traff_color==1)
            {
            acc_status=1;
            }
    }
}
void status()
{
    if (acc_status==-1)
        {
            drawstring(300,550,"ACCIDENT!!");
            drawstring(300,500,"GAME OVER");
            drawstring(300,450,"PRESS E TO EXIT");
        _sleep(2000);
        }
    else if(acc_status==1)
        drawstring(300,500,"WELL DONE!");
    else
        drawstring(300,500,"");

}
void human(float xb, float h, GLint flag){

if(flag==3)
    {y_human+=-0.03;h=y_human;}
else
    {y_human=0;h=y_human;    }
glTranslatef(xb,h,0);

//legs
glColor3f(0.9,0.7,.3);
glRectf(410,110,418,100);
glRectf(432,110,440,100);
//body
glBegin(GL_TRIANGLES);
glColor3f(0.9,.7,.1);
glVertex2f(425,180);
glColor3f(0.9,0.5,.0);
glVertex2f(400,110);
glVertex2f(450,110);

glEnd();
//head
float x=425,y=185,th,r=24;
glColor3f(0.9,0.7,.0);
glBegin(GL_POLYGON);
for(int i=0;i<360;i++){
    th=i*3.14/180;
    glVertex2f(x+r*cos(th),y+r*sin(th));
}
glEnd();
glTranslatef(-xb,-h,0);


}
void trafficLights(float x_backgrnd, long _begin)
{
    GLint i = 0;
    float zebra_x=50, zebra_y=90.0;
    GLint zebx= 5, zeby = 1;
    float redlight[] = {0.1,0.1,0.1},yellowlight[] = {0.1,0.1,0.1},greenlight[] = {0.1,0.1,0.1};
        GLint timer = _begin/1000 ;
    GLint time = timer;
      if(time>11)
      {time = timer%10;}

     if((time>=7)&&(time<=11))
        {greenlight[1] = 1;traff_color=1;}
    else if((time>=5)&&(time<7))
        {yellowlight[1] = 1;yellowlight[0] = 1;traff_color=2;}
    else if((time>=0)&&(time<5))
        {redlight[0] = 1.0;traff_color=3;}
    while(i!=10)
     {

    glColor3f(0.5,0.2,0);

    GLint pole_left_x = 40, pole_left_y = 400, pole_right_x = 50, pole_right_y = 100;

    glRectf(x_backgrnd + pole_left_x, pole_left_y, x_backgrnd + pole_right_x, pole_right_y);

    glColor3f(0.0,0.0,0.0);
    glRectf(x_backgrnd + pole_left_x - 19,pole_left_y+10, x_backgrnd+pole_right_x + 19,300);

    glColor3fv(greenlight);
    regHex(x_backgrnd + pole_left_x + 5, pole_left_y - 75);

    glColor3fv(yellowlight);
    regHex(x_backgrnd + pole_left_x + 5, pole_left_y - 45);

    glColor3fv(redlight);
    regHex(x_backgrnd + pole_left_x + 5, pole_left_y - 15);



                //zebracrossing

    for(GLint l=0;l<6;l++)
    {
        glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2f(zebra_x-200-zebx+x_backgrnd,zebra_y+zeby-5);
    glVertex2f(zebra_x+zebx+x_backgrnd,zebra_y+zeby-5);

    glVertex2f(zebra_x+zebx+2.5+x_backgrnd,zebra_y+zeby-10);
    glVertex2f(zebra_x-200-(zebx+2.5)+x_backgrnd,zebra_y+zeby-10);
    glEnd();

    zebx+=2.5;zeby-=10;

    }
    zebx= 5, zeby = 1;


           //human
    human(x_backgrnd-500,y_human,traff_color);
    human(x_backgrnd-430,y_human,traff_color);

    check_accident(x_backgrnd);
    x_backgrnd = 4000 + x_backgrnd;
    i++;

    }


}

void road(int x_bckg)
{

    float zebra_x = x_bckg+40000,zebra_y = 90;
    glColor3f(0.5,0.7,0.1);
    glRectf(0,0,zebra_x,2*zebra_y);
     glColor3f(0.5,0.5,0.5);
    glRectf(0,20,zebra_x,zebra_y);
    glColor3f(0.8,0,0);
    glRectf(x_bckg+40,20,x_bckg+45,90);

}
void wheel(float x, float y,float speed){
float th;
int r=20;
glBegin(GL_POLYGON);
glColor3f(0.0,0.0,0);
for(int i=0;i<=360;i++){
    th=i*3.142/180;
    glVertex2f(x+r*cos(th),y+r*sin(th));
}
glEnd();
glColor3f(0.9,1,1);
glRectf(x-2,y-2,x+2,y+2);

}
void car(float xc){
glTranslatef(x_cor,y_cor,0);

//bottom
glBegin(GL_POLYGON);
glColor3f(0.8,0,0.0);
glVertex2f(-750,-340);
glVertex2f(-750,-400);
glColor3f(0.5,0,0);
glVertex2f(-540,-400);
glVertex2f(-540,-340);
glEnd();
glColor3f(1,1,.5);
glRectf(-560,-360,-540,-380);//flashlight

//car-top
glBegin(GL_POLYGON);
glColor3f(0.8,0,0.0);
glVertex2f(-700,-290);
glVertex2f(-750,-340);
glColor3f(0.5,0,0);
glVertex2f(-580,-340);
glVertex2f(-600,-290);
glEnd();
//window
glBegin(GL_POLYGON);
glColor3f(0.9,1,1);
glVertex2f(-700,-300);
glVertex2f(-740,-340);
glColor3f(0.6,0.8,1);
glVertex2f(-670,-340);
glVertex2f(-670,-300);
glEnd();

glBegin(GL_POLYGON);
glColor3f(0.9,1,1);
glVertex2f(-665,-300);
glVertex2f(-665,-340);
glColor3f(0.6,0.8,1);
glVertex2f(-590,-340);
glVertex2f(-605,-300);
glEnd();

wheel(-700,-400,x_car);

wheel(-600,-400,x_car);
glTranslatef(-x_cor,-y_cor,0);
}

void carA( float xa){

glTranslatef(xa,0,0);
//car bottom
glColor3f(.9,1,.4);

glRectf(x_cor-2800,y_cor-330,x_cor-2600,y_cor-405);
//car top
glBegin(GL_POLYGON);
glVertex2f(x_cor-2750,y_cor-280);
glVertex2f(x_cor-2780,y_cor-330);
glVertex2f(x_cor-2650,y_cor-330);
glVertex2f(x_cor-2680,y_cor-280);
glEnd();
//window
glBegin(GL_POLYGON);
glColor3f(0.6,0.4,0.6);
glVertex2f(x_cor-2750,y_cor-290);
glVertex2f(x_cor-2770,y_cor-330);
glColor3f(0.6,0.8,1);
glVertex2f(x_cor-2660,y_cor-330);
glVertex2f(x_cor-2680,y_cor-290);
glEnd();
glColor3f(1,.6,0);
glRectf(x_cor-2620,y_cor-350,x_cor-2600,y_cor-370);//flashlight
//wheel of carA

wheel(x_cor-2750,y_cor-405,x_veh+1);

wheel(x_cor-2650,y_cor-405,x_veh+1);
glTranslatef(-xa,0,0);
}

void truck(float xt){

glTranslatef(xt,0,0);
glColor3f(0.1,0,.0);
glRectf(x_cor-1300,y_cor-250,x_cor-1150,y_cor-380);
glColor3f(.7,.5,.2);
glRectf(x_cor-1150,y_cor-300,x_cor-1080,y_cor-380);
glColor3f(0.9,1,1);
glRectf(x_cor-1120,y_cor-310,x_cor-1085,y_cor-350);
wheel(x_cor-1260,y_cor-380,x_veh);
wheel(x_cor-1110,y_cor-380,x_veh);

glTranslatef(-xt,0,0);

}

void tree(float x_background,float y_parm)
{
float tree_x=680.0, tree_y=150.0+y_parm;
//tree
glColor3f(0.3,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(tree_x+x_background,tree_y+150);
glVertex2f(tree_x+30+x_background,tree_y+150);

glVertex2f(tree_x+30+x_background,tree_y);
glColor3f(0,0,0);
glVertex2f(tree_x+x_background,tree_y);
glEnd();

glColor3f(0.5,0.7,0.1);
glBegin(GL_TRIANGLES);
glVertex2f(tree_x+15+x_background,tree_y+200);
glColor3f(0,0.5,0.3);
glVertex2f(tree_x-40+x_background,tree_y+100);
glVertex2f(tree_x+70+x_background,tree_y+100);
glEnd();

glColor3f(0.5,0.7,0.1);
glBegin(GL_TRIANGLES);
glVertex2f(tree_x+15+x_background,tree_y+200);
glColor3f(0,0.5,0.3);
glVertex2f(tree_x-25+x_background,tree_y+90);
glVertex2f(tree_x+60+x_background,tree_y+90);
glEnd();

glColor3f(0.5,0.7,0.1);
glBegin(GL_TRIANGLES);
glVertex2f(tree_x+15+x_background,tree_y+200);
glColor3f(0,0.5,0.3);
glVertex2f(tree_x-20+x_background,tree_y+80);
glVertex2f(tree_x+50+x_background,tree_y+80);
glEnd();
}
void streetlight(float x_background)
{

   //glClear(GL_COLOR_BUFFER_BIT);

    GLfloat polefoot_left_x =40.0,polefoot_left_y = 90.0, poleHead_right_x =50, poleHead_right_y=380.0;
    glColor3f(0.3,0,0);
    glRectf(polefoot_left_x+x_background,polefoot_left_y,poleHead_right_x+x_background,poleHead_right_y);

    glColor3f(0.5,0,0);

  glBegin(GL_POLYGON);

    glVertex2f(poleHead_right_x+x_background,poleHead_right_y);
    glVertex2f(poleHead_right_x+15+x_background,poleHead_right_y+15);
    glVertex2f(poleHead_right_x+15+x_background,poleHead_right_y+20);
    glVertex2f(poleHead_right_x-5+x_background,poleHead_right_y);
    glEnd();
    glRectf(poleHead_right_x+15+x_background, poleHead_right_y+15, poleHead_right_x+30+x_background, poleHead_right_y+20);

      glBegin(GL_POLYGON);
    glVertex2f(poleHead_right_x+30+x_background, poleHead_right_y+15);
    glVertex2f(poleHead_right_x+35+x_background, poleHead_right_y+10);
    glVertex2f(poleHead_right_x+40+x_background, poleHead_right_y+10);
    glVertex2f(poleHead_right_x+30+x_background, poleHead_right_y+20);
    glEnd();

    glRectf(poleHead_right_x+20+x_background, poleHead_right_y+10, poleHead_right_x+55+x_background, poleHead_right_y);

    glBegin(GL_POLYGON);
 //   glColor3f(0.1,0.5,0.7);
   glColor3f(0.5,0.7,0.1);
    //glColor3f(0.5,0.8,0.4);
    glVertex2f(polefoot_left_x-200+x_background, polefoot_left_y);
    glVertex2f(poleHead_right_x+300+x_background, polefoot_left_y);
    glColor3f(1,1,1);

    glVertex2f(poleHead_right_x+55+x_background,poleHead_right_y);
    glVertex2f(poleHead_right_x+20+x_background,poleHead_right_y);
    glEnd();

    glColor3f(0.3,0,0);
    glRectf(polefoot_left_x+x_background,polefoot_left_y,poleHead_right_x+x_background,poleHead_right_y);

}
void home(float x_background)
{
//left roof
float house_left_x=50.0, roof_topleft_x=75.0, house_right_x= 100.0, roof_topright_x=100.0;
//glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.5,0.2,0);
glBegin(GL_TRIANGLES);
glVertex2f(house_left_x+x_background,house_left_x+250);
glColor3f(0,0,0);
glVertex2f(house_right_x+x_background,house_right_x+200);

glVertex2f(roof_topleft_x+x_background,roof_topleft_x+325);
glEnd();
//side wall
glColor3f(1,0.9,0.5);

glBegin(GL_POLYGON);
glVertex2f(house_left_x+x_background,house_left_x+250);

glVertex2f(house_right_x+x_background,house_right_x+200);
glVertex2f(house_right_x+x_background,house_right_x+50);
glColor3f(0.6,0.3,0);
glVertex2f(house_left_x+x_background,house_left_x+100);
glEnd();
//right roof
glColor3f(0.5,0.2,0);
glBegin(GL_QUADS);
glVertex2f(roof_topleft_x+x_background,roof_topleft_x+325);
glVertex2f(roof_topright_x+110+x_background,roof_topright_x+300);
glColor3f(0,0,0);
glVertex2f(house_right_x+150+x_background,house_right_x+200);
glVertex2f(house_left_x+50+x_background,house_left_x+250);
glEnd();
//front wall
glColor3f(1,1,0.7);
glBegin(GL_POLYGON);
glVertex2f(house_left_x+50+x_background,house_left_x+250);
glVertex2f(house_right_x+150+x_background,house_right_x+200);
glVertex2f(house_right_x+150+x_background,house_right_x+50);
glVertex2f(house_left_x+50+x_background,house_left_x+100);
glEnd();
//window 1
glColor3f(0.5,0.1,0.0);
glBegin(GL_POLYGON);
glVertex2f(house_left_x+60+x_background,house_left_x+230);
glVertex2f(house_left_x+90+x_background,house_left_x+230);
glVertex2f(house_left_x+90+x_background,house_left_x+200);
glVertex2f(house_left_x+60+x_background,house_left_x+200);
glEnd();
//window 1 door
glColor3f(0.9, 0.8, 0.5);
glPointSize(20);
glBegin(GL_POINTS);
glVertex2f(house_left_x+75+x_background,house_left_x+215);
glEnd();
//window 2
glColor3f(0.5,0.1,0.0);
glBegin(GL_POLYGON);
glVertex2f(house_right_x+110+x_background,house_right_x+180);
glVertex2f(house_right_x+140+x_background,house_right_x+180);
glVertex2f(house_right_x+140+x_background,house_right_x+150);
glVertex2f(house_right_x+110+x_background,house_right_x+150);
glEnd();
//window 2 door
glColor3f(0.9, 0.8, 0.5);
glPointSize(20);
glBegin(GL_POINTS);
glVertex2f(house_right_x+125+x_background,house_right_x+165);
glEnd();
//door
glColor3f(0.5,0.1,0.0);
glBegin(GL_POLYGON);
glVertex2f(house_left_x+105+x_background,house_left_x+215);
glVertex2f(house_right_x+95+x_background,house_right_x+165);
glVertex2f(house_right_x+95+x_background,house_right_x+50);
glVertex2f(house_left_x+105+x_background,house_left_x+100);
glEnd();
//door knob
glColor3f(0.7, 0.4, 0.2);
glPointSize(7);
glBegin(GL_POINTS);
glVertex2f(house_right_x+90+x_background,house_right_x+107);
glEnd();
}
void highway(int x_bckg)
{
    GLint i=0;

    while(i!=5)
   {

       streetlight(x_bckg);
          x_bckg += 600;

    i++;
   }
   truck(x_bckg+500);

}
void forest(int x_bckg)
{
    GLint i = 0,x=0;
    while(i!=15)
    {
        tree(x_bckg+x,0);
        tree(x_bckg+x+50,-30);
        x+=150;
        i++;
    }

}
void residence(int x_bckg)
{
    GLint i = 0;
    carA(x_bckg - (x_veh)/4);
    while(i!=5)
  {
     tree(x_bckg,0);
     home(x_bckg+300);
     tree(x_bckg+500,0);
     tree(x_bckg+900,0);
     i++;
     x_bckg+=1000;
  }
}
void market(int x_bckg)
{
    GLint i = 0;
     carA(x_bckg - (x_veh)/2);
    while(i!=5)
    {
        streetlight(x_bckg+1800);
        home(x_bckg+1000);
        tree(x_bckg,-10);
        i++;
        x_bckg+=2000;
    }
      glColor3f(0.8,0,0);
    glRectf(x_bckg-1650,20,x_bckg-1640,90);

}

void move_car_forward()
{
    x_background-=4.;
    x_veh+=6.;
    glutPostRedisplay();
}
void move_car_backward()
{
    x_background+=4.;
    glutPostRedisplay();
}
void stop()
{glutPostRedisplay();}
void moveFcn(GLint movKey, GLint xMouse, GLint yMouse )
{
    switch(movKey)
    {
    case GLUT_KEY_RIGHT:  glutIdleFunc(move_car_forward);break;
    case GLUT_KEY_LEFT:     glutIdleFunc(move_car_backward);break;
    default:glutIdleFunc(stop);break;
    }
}
void drawstring(int x,int y,char* str)
{
    glColor3f(1.0,1.0,1.0);
    int len,i;
    glRasterPos2f(x,y);
    len= strlen(str);
    for(i=0;i<len;i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
}
void text()
{
glClear(GL_COLOR_BUFFER_BIT);
drawstring(80.0,350.0,"* * * * * * * * TRAFFIC SIGNAL CONTROL * * * * * * * * ");
drawstring(110.0,250.0,"PRESS S -> FOR START");
drawstring(110.0,200.0,"PRESS I FOR INSTRUCTIONS");
drawstring(110.0,150.0,"PRESS A FOR ABOUT");
drawstring(110.0,100.0,"PRESS E TO EXIT");
glFlush();
}

void instruction()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawstring(100,350,"FOLLOW THE TRAFFIC RULES !!!");
    drawstring(20,300,"1. Press the arrow keys to move the car.");
    drawstring(20,250,"2. Stop the car when the red light glows in the traffic signal.");
    drawstring(20,200,"3. Move when you see the green light glowing.");
    drawstring(20,150,"4. Look out for vehicles when you see the yellow light glowing.");
    drawstring(180,100,"Press any key to return back to the menu.");
    glFlush();
}
void about()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawstring(20,300,"This program is a mini project named 'Traffic Signal Control' submitted by Nabin Paneru[THA075BEI025], ");
    drawstring(20,250,"Namrata Das[THA075BEI026], Neelam Karki[THA075BEI027] and Rakshya Panta[THA075BEI029] as  ");
    drawstring(20,200,"a final project of Computer Graphics[EX554] in year 2020 AD. This program is written is c++ and has used ");
    drawstring(20,150,"OpenGL utility toolkit (GLUT) for graphic implementations.");
    drawstring(180,100,"Press any key to return back to the menu.");
    glFlush();
}
void start()
{
    //changes the status of the display to begin game
   value=1;
}
void keyboard (unsigned char key, int x, int y)
{
   switch(key) {

      case 'S' :
      case 's' :
         	start();
         	break;


      case 'i':
      case 'I':
               instruction();
               break;
      case 'a':
      case 'A':
               about();
               break;

      case 'e':
      case 'E':
                exit(0);

      default: text();
    }
}
void menu(int id){
    if(id==1)
        start();
    else if(id==2)
        instruction();
    else if(id==3)
        about();
    else
        exit(0);
    glutPostRedisplay();
}
void display()
{


    glClear(GL_COLOR_BUFFER_BIT);
    if(value==0)
        text();
    if(value==1)
    {
    glClear(GL_COLOR_BUFFER_BIT);
    clock_t begin_time = clock();
    status();
    road(x_background);
    forest(x_background+50);
    trafficLights(x_background+4000,begin_time);
    highway(x_background+4500);
    residence(x_background+8000);
    market(x_background+12500);
    truck(x_veh);

    car(0);

    carA(x_veh+1);
    }
       glFlush();
}
void create_menu()
{
    glutCreateMenu(menu);
        glutAddMenuEntry("Start",1);
        glutAddMenuEntry("Instructions",2);
        glutAddMenuEntry("About",3);
        glutAddMenuEntry("Quit",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc,char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Travel&Traffic");

    initialize();
    glutDisplayFunc(display);
    create_menu();
    glutSpecialFunc(moveFcn);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
