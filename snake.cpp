#include<windows.h>
#include"snlv0.h"
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<time.h>
#include<math.h>
#define DEG2RAD (22/7)/180
using namespace std;

char mess[4];
int width=0,height=0;
GLfloat theta[3]={0.0,0.0,0.0};
int f=0;
int cnt;
int mt=1;
int flg=1;
int r,s;
int sel=0;
GLfloat vertices [][3] = {{1150.0,550.0,-50.0}, {1250.0,550.0,-50.0},
                          {1250.0,650.0,-50.0}, {1150.0,650.0,-50.0},
                          {1150.0,550.0,50.0}, {1250.0,550.0,50.0},
                          {1250.0,650.0,50.0}, {1150.0,650.0,50.0}};

pawns paw1(x0-40,y2+40,1,70);
pawns paw2(x0-40,y2+10,0.5,70);

struct ladder
{
	int xp,xq,yp,yq;			//ladder co-ordinates
};
struct snake
{
	int xp,xq,yp,yq;			//snake co-ordinates
};

struct snake sn[4];
struct ladder l[4];

void drawStringAtPos(double x, double y,double z,string msg)
{
	glRasterPos3f(x,y,z);	//Specifies Raster Position for Pixel operations
	for(int i=0;i<msg.size();i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg[i]);
}

void reshape(int w,int h)
{
        width=w;height=h;
    	glViewport(0,0,w,h);
    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
        glOrtho(0.0,1367.0,0.0,767.0, -180.0,180.0);
        glMatrixMode(GL_MODELVIEW);
        glClearColor(1.0,1.0,0.8,1.0);
}

void polygon(int a,int b,int c,int d,int e)
{
	glColor3f(0,0,1);
	glBegin(GL_POLYGON);			//dice face
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[b]);
		glVertex3fv(vertices[c]);
		glVertex3fv(vertices[d]);
 	glEnd();
	
 	glLineWidth(1.0);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);			//dice edges
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[b]);
		glVertex3fv(vertices[c]);
		glVertex3fv(vertices[d]);
 	glEnd();

 	glLineWidth(2.0);
	glColor3f(1.0,1.0,1.0);
   	glPointSize(3.0);			//dots on dice face
    	glBegin(GL_POINTS);
        switch(e)		//number on dice
        {
            case 1 :
                        glVertex3f(1200.0,600.0,-50.0);
                        break;
            case 2 :
                        glVertex3f(1175.0,651.0,25.0);
                        glVertex3f(1225.0,651.0,-25.0);
                        break;
            case 3 :    glVertex3f(1149.0,575.0,25.0);
                        glVertex3f(1149.0,600.0,0.0);
                        glVertex3f(1149.0,625.0,-25.0);
                        break;
            case 4 :    glVertex3f(1251.0,575.0,25.0);
                        glVertex3f(1251.0,575.0,-25.0);
                        glVertex3f(1251.0,625.0,25.0);
                        glVertex3f(1251.0,625.0,-25.0);
                        break;
            case 5 :    glVertex3f(1175.0,549.0,25.0);
                        glVertex3f(1175.0,549.0,-25.0);
                        glVertex3f(1200.0,549.0,0.0);
                        glVertex3f(1225.0,549.0,25.0);
                        glVertex3f(1225.0,549.0,-25.0);
                        break;
            case 6 :    glVertex3f(1175.0,575.0,51.0);
                        glVertex3f(1175.0,600.0,51.0);
                        glVertex3f(1175.0,625.0,51.0);
                        glVertex3f(1225.0,575.0,51.0);
                        glVertex3f(1225.0,600.0,51.0);
                        glVertex3f(1225.0,625.0,51.0);
                        break;
        }
	 glEnd();
}

void colorcube()
{
    polygon(0,3,2,1,1);
    polygon(2,3,7,6,2);
    polygon(0,4,7,3,3);
    polygon(1,2,6,5,4);
    polygon(4,5,6,7,5);
    polygon(0,1,5,4,6);
}

void rect()         //board
{
	int i,j;
	x[-1]=x0;
	y[-1]=y2;
	for( i=0;i<=maxx;i++)
		x[i]=x0+i*dx;
	for( j=0;j<=maxy;j++)
		y[j]=y2+j*dy;
	glColor3f(0.88,0.88,0.88);
	glBegin(GL_QUADS);			//outer-boundaries of board
        	glVertex3f(x0,y2,10);
        	glVertex3f(x[maxx],y2,10);
        	glVertex3f(x[maxx],y[maxy],10);
        	glVertex3f(x0,y[maxy],10);
	glEnd();
	int count=1;
	int temp=1;		//x index increment by 1 always
	i=0;
	for(j=0;j<maxy;j++)
	{
		while(1)
		{
			if(temp<0)
			{
				if(i<0)
					break;
			}
			else
			{
				if(i>maxx-1)
					break;
			}
			glColor3f(0.4,0.2,0.0);
			glBegin(GL_LINE_LOOP);			//draw squares one by one
                    glVertex3f(x[i],y[j],11);
                    glVertex3f(x[i],y[j+1],11);
                    glVertex3f(x[i+temp],y[j+1],11);
                    glVertex3f(x[i+temp],y[j],11);
			glEnd();

            if(count%2==0)
            {
                glColor3f(0.21,0.27,0.31);
            }

            else
            {
                glColor3f(0.255,0.41,0.882);
            }
			sprintf(mess,"%d",count);
			if(count==100)
				strcpy(mess,"END");
			drawStringAtPos(x[i]+10,y[j]+10,20,mess);
			count++;
			i+=temp;
		}
		if(temp>0)
		{
			temp=-1;
		}
		else
		{
			temp=1;
		}
		i+=temp;
	}
}

void snake_head(int xr,int yr)
{
	int i;
	glColor3f(0.50,0.0,0.502);
	glBegin(GL_LINE_LOOP);
    for(i=0;i<360;i++)
    {
        float rad = i*DEG2RAD;
        glVertex2f(cos(rad)*xr,sin(rad)*yr);
    }
    glEnd();
	glColor3f(0.45,0.309,0.588);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0,0);
	for (int i=0;i<=360;++i)
	{
		glVertex2f(xr*cos(i), yr*sin(i));
	}

	glEnd();
    glScaled(1,2,0.5);
	glFlush();
}

void snakes()
{
	GLfloat xsnake[]={380,995,782,784},
		zsnake[]={175,210,370,70},
		lcarr[]={0.3,-0.15,0.30,-0.20,0.45,-0.15,0.55,-0.2,0.70,-0.25,0.80,-0.35,0.9};
	GLfloat i;
	GLint j,lc=0,
		reploop[]={70,35,35,35,35,35,35,35,35,35,35,25,70},
		snakeLc[]={13,7,6,5};
	for(j=0;j<4;j++)
	{
		glColor3f(0.502,0.502,0.502);
		glPointSize(15.0);
		lc=0;
		glBegin(GL_TRIANGLES);			//tail of snake
			glVertex3f(xsnake[j]-10,zsnake[j]-10,12);
			glVertex3f(xsnake[j],zsnake[j]-36,12);
			glVertex3f(xsnake[j]+10,zsnake[j]-10,12);
		glEnd();

		while(lc<snakeLc[j])
		{

			for(i=0;i<reploop[lc];i++)
			{
				glBegin(GL_POINTS);
   					glVertex3i(xsnake[j],zsnake[j],12);
				glEnd();
				zsnake[j]++;
				if(j%2==0)			//if-else gives zig-zag effect to snake
                    xsnake[j]+=lcarr[lc];
				else
					xsnake[j]-=lcarr[lc];
			}
			lc++;
		}
		glPushMatrix();
        		glTranslatef(xsnake[j],zsnake[j],18);
        		glColor3f(255/255.0, 51/255.0, 0);
        		glPointSize(3.0);
       			glBegin(GL_POINTS);			//eyes of snake
        			glVertex3f(-12.5,7.5,20);
        			glVertex3f(12.5,7.5,20);
       	 		glEnd();
        		glBegin(GL_POLYGON);			//teeth of snake
            			glVertex3f(0,-1,20);
            			glVertex3f(-4,-13,20);
            			glVertex3f(-4,-1,20);
            			glVertex3f(4,-1,20);
            			glVertex3f(4,-13,20);
       			glEnd();
        		snake_head(25,15);
        	glPopMatrix();
	}
}
pawns::pawns(GLfloat p1,GLfloat q1,GLfloat col,GLint tmp)
{
	add=speed,up=0,flag=1;
	this->p1=p1;
	this->p2=p1-10;
	this->p3=p1;
	this->p4=p1+10;
	this->q1=q1;
	this->q2=q1+10;
	this->q3=q1+20;
	this->q4=q1+10;
	this->col1=col;
	oy=q1-y2;
	this->tmp=tmp;			//stop speed
}

void pawns::disp()
{
	glColor3f(col1,1.0,0.0);
	glBegin(GL_POLYGON);
        glVertex3f(p1,q1,28);
        glVertex3f(p2,q2,28);
        glVertex3f(p3,q3,28);
        glVertex3f(p4,q4,28);
	glEnd();
	glFlush();
}

void pawns::init(int r)
{
	this->t=r;
}

GLfloat kingf(GLfloat x,GLfloat m,GLfloat k)
{
	return (m*x+k);
}

void ltorladder(GLint a,GLint b,GLint c,GLint d)			//left to right ladder
{
	glBegin(GL_QUADS);			//Ladder construction
		glVertex3f(x[a]+40,y[b]+23,15);
		glVertex3f(x[a]+30,y[b]+18,15);
		glVertex3f(x[c]+50,y[d]+10,15);
		glVertex3f(x[c]+47,y[d]+15,15);
		glVertex3f(x[a]+3,y[b]+47,15);
		glVertex3f(x[a]+6,y[b]+42,15);
		glVertex3f(x[c]+26,y[d]+34,15);
		glVertex3f(x[c]+23,y[d]+39,15);
		GLfloat xi=x[a]+27;
		int d1=8,d2=13;
		GLfloat m=(y[b]+23.0-(y[d]+15.0)) / (x[a]+27.0-(x[c]+47.0));
		GLfloat k=y[b]+23.0-(m*(x[a]+27.0));
		while(((x[c]+47)-(xi+d1))>8)			//rungs of ladder
		{
			glVertex3f(xi+d1,kingf(xi+d1,m,k),16);
			glVertex3f(xi+d2,kingf(xi+d2,m,k),16);
			glVertex3f(xi-24+d2,kingf(xi+d2,m,k)+24,16);
			glVertex3f(xi-24+d1,kingf(xi+d1,m,k)+24,16);
			d1+=15;
			d2+=15;
		}
    glEnd();
}

void rtolladder(GLint a,GLint b,GLint c,GLint d)			//right to left ladder
{
	glBegin(GL_QUADS);
		glVertex3f(x[a]+6,y[b]+32,15);
		glVertex3f(x[a]+9,y[b]+37,15);
		glVertex3f(x[c]+29,y[d]+29,15);
		glVertex3f(x[c]+26,y[d]+24,15);
		glVertex3f(x[a]+6+24,y[b]+32+24,15);
		glVertex3f(x[a]+9+24,y[b]+37+24,15);
		glVertex3f(x[c]+29+24,y[d]+29+24,15);
		glVertex3f(x[c]+26+24,y[d]+24+24,15);
		GLfloat xi=x[c]+26;
		int d1=8,d2=13;
		GLfloat m=(y[b]+32.0-(y[d]+24.0)) / (x[a]+6.0-(x[c]+26.0));
		GLfloat k=y[b]+32.0-(m*(x[a]+6.0));
		while(((x[a]+6)-(xi+d1))>8)
		{
			glVertex3f(xi+d1,kingf(xi+d1,m,k),16);
			glVertex3f(xi+d2,kingf(xi+d2,m,k),16);
			glVertex3f(xi+d2+24,kingf(xi+d2,m,k)+24,16);
			glVertex3f(xi+d1+24,kingf(xi+d1,m,k)+24,16);
			d1+=15;
			d2+=15;
		}
	glEnd();
}

void ladders()
{
	GLfloat m;
	glPointSize(20.0);
	glColor3f(0.48,0.29,0);

	switch(sel)
	{
		case 0:
                ltorladder(1,0,4,2);
                l[0].xp=1,l[0].xq=4,l[0].yp=0,l[0].yq=2;
                ltorladder(2,6,3,8);
                l[1].xp=2,l[1].xq=3,l[1].yp=6,l[1].yq=8;
                rtolladder(8,4,6,6);
                l[2].xp=8,l[2].xq=6,l[2].yp=4,l[2].yq=6;
                rtolladder(5,4,3,5);
                l[3].xp=5,l[3].xq=3,l[3].yp=4,l[3].yq=5;
                break;
		case 1:
                ltorladder(1,1,4,4);
                l[0].xp=1,l[0].xq=4,l[0].yp=1,l[0].yq=4;
                ltorladder(7,7,9,8);
                l[1].xp=7,l[1].xq=9,l[1].yp=7,l[1].yq=8;
                rtolladder(8,0,7,2);
                l[2].xp=8,l[2].xq=7,l[2].yp=0,l[2].yq=2;
                rtolladder(3,6,2,8);
                l[3].xp=3,l[3].xq=2,l[3].yp=6,l[3].yq=8;
                break;
		case 2:
                ltorladder(1,1,4,4);
                l[0].xp=1,l[0].xq=4,l[0].yp=1,l[0].yq=4;
                ltorladder(2,6,3,8);
                l[1].xp=2,l[1].xq=3,l[1].yp=6,l[1].yq=8;
                rtolladder(8,4,6,6);
                l[2].xp=8,l[2].xq=6,l[2].yp=4,l[2].yq=6;
                rtolladder(8,0,7,2);
                l[3].xp=8,l[3].xq=7,l[3].yp=0,l[3].yq=2;
                break;
	}
    // sn[0].xp=2,sn[0].yp=9,sn[0].xq=0,sn[0].yq=1;
	// sn[1].xp=5,sn[1].yp=3,sn[1].xq=6,sn[1].yq=0;
	// sn[2].xp=6,sn[2].yp=8,sn[2].xq=6,sn[2].yq=4;
	// sn[3].xp=8,sn[3].yp=6,sn[3].xq=9,sn[3].yq=2;
}

void display2()
{
    int i=0;
    paw1.disp();
	paw2.disp();
    glClearColor(0,0.50,0.50,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glTranslatef(1200,600,0.0);
		glRotatef(theta[0],1.0,1.0,0.0);
        glRotatef(theta[1],0.0,1.0,0.0);
   		glRotatef(theta[2],0.0,0.0,1.0);
        glTranslatef(-1200,-600,0.0);
        colorcube();
    glPopMatrix();
    glFlush();

    rect();         //board

    drawStringAtPos(50.0,600.0,20.0,"Player 1:");
    drawStringAtPos(50.0,550.0,20.0,"Player 2:");
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_QUADS);			//Player 1
        glVertex3f(200.0,600.0,20.0);
        glVertex3f(210.0,610.0,20.0);
        glVertex3f(200.0,620.0,20.0);
        glVertex3f(190.0,610.0,20.0);
    glEnd();
    glColor3f(0.5,1.0,0.0);
    glBegin(GL_QUADS);			//Player 2
        glVertex3f(200.0,550.0,20.0);
        glVertex3f(210.0,560.0,20.0);
        glVertex3f(200.0,570.0,20.0);
        glVertex3f(190.0,560.0,20.0);
    glEnd();

    glPushMatrix();
    glTranslatef(1200.0,300.0,0.0);
    glColor3f((51.0/255.0),(51.0/255.0),1.0);
    glBegin(GL_POLYGON);			//Button
        for(i=0;i<360;i++)
        {
            float rad = i*(float)DEG2RAD;
            glVertex3f(cos(rad)*60,sin(rad)*40,18.0);
        }
    glEnd();
    glPopMatrix();
    glColor3f(0,0,0);
    drawStringAtPos(1170,320,20,"ROLL");
    drawStringAtPos(1170,280,20,"DICE");

    glColor3f(0.4,0.2,0.0);         //board border horizontal
	glBegin(GL_QUADS);
        glVertex3f(x0+20,y[maxy]+20,0);
        glVertex3f(x0,y[maxy],10);
        glVertex3f(x[maxx],y[maxy],10);
        glVertex3f(x[maxx]+20,y[maxy]+20,0);
	glEnd();
    glBegin(GL_QUADS);          //board border vertical
        glVertex3f(x[maxx],y[maxy],10);
        glVertex3f(x[maxx]+20,y[maxy]+20,0);
        glVertex3f(x[maxx]+20,y2+20,0);
        glVertex3f(x[maxx],y2,10);
	glEnd();

    ladders();
    snakes();
    glFlush();
    glutSwapBuffers();
}

int spincube()
{
	theta[0]+=12;
    if(theta[0]>360.0)
	{
		cnt++;
        theta[0]-=360;
	}
    display2();
	if(cnt<2)
        spincube();
    else
    {
        if(flg)
		{
            srand(time(NULL));			//prevent repeat of same
            s=r=(rand()%6)+1;			//value of dice
            switch(s)
            {
                case 1 :    theta[1]+=90;
                            theta[2]-=45;
                            break;
                case 2 :    theta[2]+=45;
                            break;
                case 3 :    theta[2]-=45;
                            break;
                case 4 :    theta[2]+=135;
                            break;
                case 5 :    theta[2]+=225;
                            break;
                case 6 :    theta[1]-=90;
                            theta[2]-=45;
                            break;
			}
			flg=0;
			spincube();
		}
	}
	return 0;
}

void mymouse(int btn,int state,int x,int y)
{
    if(!f)
    {
            if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
            {
               glutDisplayFunc(display2);
               glutPostRedisplay();
                f=1;
            }
    }
    else
	{
		if(x>=((1140*width)/1367) && x<=((1260*width)/1367) && y<=(((767-260)*height)/767) && y>=(((767-340)*height)/767))
		{
			if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
			{
				cnt=0;
                flg=1;
                theta[1]=90;
                theta[2]=45;
				mt=0;
				int a=spincube();
			}
		}
	}
}

void display1()
{
	glClearColor(0,0.50,0.50,1);
    // glClearColor(255,165,0,1);
	// glClearColor(0.67,0.84,0.902,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(1,1,1);
    drawStringAtPos(500,680,10,"Department of Computer Science and Engineering");
    drawStringAtPos(520,600,10,"Computer Graphics Project Mini Project");
    drawStringAtPos(550,520,10,"Snake and Ladders");
    drawStringAtPos(550,440,10,"1RN20CS161 Swaroop K S");
    drawStringAtPos(550,360,10,"1RN20CS167 Tejas R");

    glColor3f(0,0,0);
    drawStringAtPos(565,275,10,"Click to Begin");

    glFlush();
    glutSwapBuffers();
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1367,768);
    glutCreateWindow("Snake and Ladders");
    srand(time(NULL));
	sel=rand()%3;
    glEnable(GL_POLYGON_SMOOTH);
    //init();
    glutDisplayFunc(display1);
    glEnable(GL_DEPTH_TEST);
    glutMouseFunc(mymouse);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}