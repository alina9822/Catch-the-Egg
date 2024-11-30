#include "iGraphics.h"
#include<stdlib.h>
#include<math.h>
#include<Windows.h>
#include<MMSystem.h>

int screen_width=1200;
int screen_height=768;

int basketX=0;
int basketY=20;

int hen_x[]= {0};
int hen_y[]= {565,430,295};

int d[]= {1,-1,-1};
int m=1;
int m_show=1;
int sec=30;
int f=0;
int music=1;
int index_number=1;

char t[]="TIME: 00.00";
char score[20]="SCORE: 0";
char nm[20]="";
char str1[20]="0";

int temp[10];
int showcrack[10]= {0};

int b=1,n=0,l=0,x=200;
int explode=0;

int blockX[5]= {200,500,900};
int blockY[5]= {768,768,768};
int eggX[]= {100,400,800,1000,600,200};
int eggY[]= {575,440,305,575,440,305};
int line_y[]= {570,435,300};

int crack_x[10];
int point =0;

int st[20]= {0};

typedef enum
{
    home,play,scores,settins,con_new,help,time_choice,enter_name
} page;


char block_file[][30]= {"game pic\\clock.bmp","game pic\\gift.bmp","game pic\\bomb.bmp" };
char crackedegg_file[][30]= {"game pic//ceg1.bmp","game pic//ceg2.bmp","game pic//ceg3.bmp","game pic//ceg4.bmp","game pic//cgegg.bmp","game pic//cpoop.bmp"};
char egg_file[][30]= {"game pic//eg1.bmp","game pic//eg2.bmp","game pic//eg3.bmp","game pic//eg4.bmp","game pic//gegg.bmp","game pic//poop.bmp"};
//char lhen_file[][40]= {"chicken\\lhen1.bmp","chicken\\lhen2.bmp","chicken\\lhen3.bmp","chicken\\lhen4.bmp""chicken\\lhen5.bmp","chicken\\lcool.bmp"};
char rhen_file[][40]= {"game pic\\hen1.bmp","game pic\\hen2.bmp","game pic\\hen3.bmp"};

void score_show(int *m);
void scoring(int sc);
void score_compare();
void timer();
/*
	function iDraw() is called again and again by the system.
*/
void re_initializing()
{
    int i;
    basketX=0;
    basketY=20;
    for(i=0; i<10; i++)
        hen_x[i]= 0;
    //hen_y[]= {565,430,295};

//d[]= {1,-1,-1};

    sec=30;
    index_number=1;
    strcpy(t,"TIME: 00.00");
    strcpy(score,"SCORE: 0");

    for(i=0; i<10; i++)
        showcrack[i]= 0;

//int eggX[]= {100,400,800,1000,600,200};
    /* eggX[0]=eggX[5]=100;
     eggX[1]=eggX[4]=400;
     eggX[2]=eggX[3]=800;*/

    eggY[0]=eggY[3]=575;
    eggY[1]=eggY[4]=440;
    eggY[2]=eggY[5]=700;
//int eggY[]= {575,440,305,575,440,305};
    b=1;
    n=0;
    l=0;
    x=200;

    line_y[0]= 570;
    line_y[1]=435;
    line_y[2]=300;
// crack_x[10];
    point =0;
    m=1;

}

void pause()
{
    iPauseTimer(0);
    iPauseTimer(1);
    iPauseTimer(2);
    iPauseTimer(3);
    iPauseTimer(4);
    iPauseTimer(5);
    iPauseTimer(6);
}

void resume()
{
    iResumeTimer(0);
    iResumeTimer(1);
    iResumeTimer(2);
    iResumeTimer(3);
    iResumeTimer(4);
    iResumeTimer(5);
    iResumeTimer(6);
}

void iDraw()
{
    //place your drawing codes here
    iClear();
    if(st[home])
    {
        iShowBMP(0,0,"game pic\\b6.bmp");
        if(music)
            iShowBMP2(5,660,"game pic\\sound on.bmp",0);
        else
            iShowBMP2(5,660,"game pic\\sound off.bmp",0);
    }
    else if(st[scores])
    {
        iShowBMP(0,0,"game pic\\score board3.bmp");

        FILE *fp1,*fp2;
        char name[10][20];
        char score[10][20];
        int i,H=655;

        if(m_show==1)
        {
            fp1=fopen("score.txt","r");
            fp2=fopen("name.txt","r");
        }
        else if(m_show==2)
        {
            fp1=fopen("score2.txt","r");
            fp2=fopen("name2.txt","r");
        }
        else if(m_show==3)
        {
            fp1=fopen("score3.txt","r");
            fp2=fopen("name3.txt","r");
        }

        for(i=0; i<10; i++)
            fgets(score[i],20,fp1);
        //fscanf(fp1,"%d",&score[i]);

        for(i=0; i<10; i++)
            fgets(name[i],20,fp2);

        iSetColor(253,236,166);

        for(i=0; i<10; i++)
        {
            iText(220,H,name[i],GLUT_BITMAP_TIMES_ROMAN_24);
            iText(680,H,score[i],GLUT_BITMAP_TIMES_ROMAN_24);
            H-=69;
        }

        fclose(fp1);
        fclose(fp2);
    }
    else if(st[help])
    {
        iShowBMP(0,0,"game pic\\help.bmp");
    }
    else if(st[con_new])
    {
        iShowBMP(0,0,"game pic\\con_new.bmp");
    }
    else if(st[time_choice])
    {
        iShowBMP(0,0,"game pic\\time choice.bmp");
    }
    else if(st[enter_name])
    {
        iShowBMP(0,0,"game pic\\enter name.bmp");
        iText(570,448,str1,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(460,304,nm,GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else if(st[play])
    {
        iShowBMP(0,0,"game pic\\bg1.bmp");

        for(int i=0; i<6; i++)
        {
            if(showcrack[i])
            {
                if(i==3)
                    iShowBMP2(crack_x[i],73,crackedegg_file[i],16777215);
                else
                    iShowBMP2(crack_x[i],73,crackedegg_file[i],0);
            }

        }
        if(l)
            iShowBMP2(basketX,basketY,"game pic\\bigbs.bmp",0);
        else
            iShowBMP2(basketX,basketY,"game pic\\brownbaskets.bmp",0);//16777215);

        iShowBMP2(blockX[n],blockY[n],block_file[n],0);
        for(int i=0; i<6; i++)
            if(eggY[i]<temp[i]&&eggY[i]>73)
            {
                if(i==3)
                    iShowBMP2(eggX[i],eggY[i],egg_file[i],16777215);
                else
                    iShowBMP2(eggX[i],eggY[i],egg_file[i],0);
            }

        for(int i=0; i<3; i++)
            iShowBMP2(0,line_y[i],"game pic\\line.bmp",0);

        for(int i=0; i<3; i++)
            iShowBMP2(hen_x[i],line_y[i]-5,rhen_file[i],0);

        /* if(explode)
         {
             pause();
             for(int i=0;i<8;i++)
                iShowBMP2(blastX,60,blast[i],0);
         }*/


        iSetColor(253,236,166);
        iText(35,736,t,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(940,734,score,GLUT_BITMAP_TIMES_ROMAN_24);
    }
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
    if((mx-100)>=0 && (mx+100)<=1200)
        basketX=mx-100;
    // basketY=my;
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(st[home])
        {
            if((mx>=141&&mx<=481) && (my>=504&&my<=555))
            {
                //Sleep(300);
                for(int i=0; i<20; i++)
                    st[i]=0;
                FILE *fp;
                fp=fopen("last read.txt","r");
                fscanf(fp,"%d%d",&sec,&point);
                fclose(fp);
                score_show(&point);
                if(sec>0)
                    st[con_new]=1;
                else
                    st[time_choice]=1;
                //resume();
            }
            else if((mx>=139&&mx<=481) && (my>=431&&my<=482))
            {
                //Sleep(300);
                for(int i=0; i<20; i++)
                    st[i]=0;
                m_show=1;
                st[scores]=1;
            }
            else if((mx>=136&&mx<=481) && (my>=360&&my<=417))
            {
                //Sleep(300);
                for(int i=0; i<20; i++)
                    st[i]=0;
                st[help]=1;
            }
            else if((mx>=5&&mx<=111) && (my>=660))
            {
                if(music)
                {
                    music=1-music;
                    PlaySound(0,0,0);
                }
                else
                {
                    music=1-music;
                    PlaySound("sound.WAV",NULL,SND_LOOP|SND_ASYNC);
                }

            }
            else if((mx>=140&&mx<=484) && (my>=291&&my<=343))
            {
                exit(0);
            }
        }
        else if(st[help])
        {
            if((mx>=1035&&mx<=1180) && (my<=88))
            {
                for(int i=0; i<20; i++)
                    st[i]=0;
                st[home]=1;
            }
        }
        else if(st[time_choice])
        {
            if((mx>=1035&&mx<=1180) && (my<=88))
            {
                for(int i=0; i<20; i++)
                    st[i]=0;
                st[home]=1;
            }
            if((mx>=417&&mx<=786) && (my>=557&&my<=668))
            {
                re_initializing();
                resume();
                for(int i=0; i<20; i++)
                    st[i]=0;
                st[play]=1;
                m=1;
                sec=1*60;
                timer();
            }
            if((mx>=417&&mx<=786) && (my>=401&&my<=509))
            {
                re_initializing();
                resume();
                for(int i=0; i<20; i++)
                    st[i]=0;
                st[play]=1;
                m=2;
                sec=2*60;
                timer();
            }
            if((mx>=417&&mx<=786) && (my>=236&&my<=352))
            {
                re_initializing();
                resume();
                for(int i=0; i<20; i++)
                    st[i]=0;
                st[play]=1;
                m=3;
                sec=3*60;
                timer();
            }
        }
        else if(st[con_new])
        {
            if((mx>=1020&&mx<=1180) && (my<=88))
            {
                for(int i=0; i<20; i++)
                    st[i]=0;
                st[home]=1;
            }
            if((mx>=267&&mx<=515) && (my>=291&&my<=475))
            {
                for(int i=0; i<20; i++)
                    st[i]=0;
                st[play]=1;
                resume();
                if(!f)
                    timer();
            }
            if((mx>=669&&mx<=922) && (my>=291&&my<=475))
            {
                for(int i=0; i<20; i++)
                    st[i]=0;
                st[time_choice]=1;
            }

        }
        else if (st[play])
        {
            if((mx>=1148&&mx<=1200) && (my>=721&&my<=768))
            {
                pause();
                for(int i=0; i<20; i++)
                    st[i]=0;
                st[con_new]=1;
                f=1;
            }
        }
        else if(st[enter_name])
        {
            if((mx>=1035&&mx<=1180) && (my<=88))
            {
                for(int i=0; i<20; i++)
                    st[i]=0;
                st[home]=1;
            }
        }
        else if(st[scores])
        {
            if((mx>=1035&&mx<=1180) && (my<=88))
            {
                for(int i=0; i<20; i++)
                    st[i]=0;
                st[home]=1;
            }
            if((mx>=907&&mx<=1157) && (my>=299&&my<=404))
            {
                m_show=3;
            }
            if((mx>=907&&mx<=1157) && (my>=443&&my<=551))
            {
                m_show=2;
            }
            if((mx>=907&&mx<=1157) && (my>=585&&my<=697))
            {
                m_show=1;
            }
        }

    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {

    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(st[enter_name])
    {
        if(key!='\b' && key!='\r')
        {
            nm[index_number]=key;
            index_number++;
            nm[index_number]='\0';
        }
        else if(key=='\r')
        {
            scoring(point);
            st[enter_name]=0;
            st[home]=1;
            nm[index_number]='\0';
        }
        else
        {
            if(index_number<=0)
                index_number=0;
            else
                index_number--;

            nm[index_number]='\0';
        }

    }
    else if(key=='m' || key=='M')
    {
        if(music)
        {
            music=1-music;
            PlaySound(0,0,0);
        }
        else
        {
            music=1-music;
            PlaySound("sound.WAV",NULL,SND_LOOP|SND_ASYNC);
        }

    }

    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
    int x=20;
    if(key==GLUT_KEY_RIGHT)
        if((basketX+x)<=1000)
            basketX+=x;
    if(key==GLUT_KEY_LEFT)
        if((basketX-x)>=0)
            basketX-=x;
    if(key == GLUT_KEY_END)
    {
        printf("%d",point);
        exit(0);
    }
    //place your codes for other keys here
}

void henMove()
{
    if(st[play])
    {
        //printf("1\n");
        hen_x[0]+=5;
        if(hen_x[0]>=1200)
            hen_x[0]=0;
        hen_x[1]+=6;
        if(hen_x[1]>=1200)
            hen_x[1]=0;
        hen_x[2]+=7;
        if(hen_x[2]>=1200)
            hen_x[2]=0;
    }
}
void up_down()
{
    if(st[play])
    {
        //printf("1\n");
        line_y[0]=line_y[0]-(d[0]*1);
        if(line_y[0]<300 || line_y[0]>570)
            d[0]*=-1;
        line_y[1]=line_y[1]-(d[1]*1);
        if(line_y[1]<300 || line_y[1]>570)
            d[1]*=-1;
        line_y[2]=line_y[2]-(d[2]*1);
        if(line_y[2]<300 || line_y[2]>570)
            d[2]*=-1;
    }
}
void eggMove()
{
    if(st[play])
    {
        //printf("1\n");
        for(int i=0; i<3; i++)
            if(eggX[i]>=(hen_x[i]+60)&&eggX[i]<=(hen_x[i]+80))
            {
                showcrack[i]=0;
                temp[i]=line_y[i]+10;
                eggY[i]=temp[i]-1;
            }
        for(int i=0; i<3; i++)
            if(eggY[i]<=73 && ((eggX[i]+13)>=basketX&&(eggX[i]+13)<=(basketX+x)) )
            {
                if(i==1 )
                    point+=5;///white egg
                else if( i==2)
                    point+=2;///brown egg
                else if(i==0)
                    point+=10;///blue egg

                score_show(&point);

                eggX[i]=abs(rand()%1030)+80;
                eggY[i]=700;
            }
        for(int i=0; i<3; i++)
            if(eggY[i]<=73)
            {
                crack_x[i]=eggX[i]-20;
                showcrack[i]=1;
                eggX[i]=abs(rand()%1030)+80;
                eggY[i]=650;
            }
        for(int i=0; i<3; i++)
            if(eggY[i]<=temp[i])
                eggY[i]-=6;
    }
}
void eggMove1()
{
    if(st[play])
    {
        //printf("1\n");
        for(int i=3; i<6; i++)
            if(eggX[i]>=(hen_x[i-3]+60)&&eggX[i]<=(hen_x[i-3]+80))
            {
                showcrack[i]=0;
                temp[i]=line_y[i-3]+10;
                eggY[i]=temp[i]-1;
            }
        for(int i=3; i<6; i++)
            if(eggY[i]<=73 && ((eggX[i]+13)>=basketX&&(eggX[i]+13)<=(basketX+x)) )
            {
                if(i==3 )
                    sec-=10;///black egg
                else if(i==4)
                    point+=20;///golden egg
                else if(i==5)
                    point-=10;///poop

                score_show(&point);

                eggX[i]=abs(rand()%1030)+80;
                eggY[i]=700;
            }
        for(int i=3; i<6; i++)
            if(eggY[i]<=73)
            {
                crack_x[i]=eggX[i]-20;
                showcrack[i]=1;
                eggX[i]=abs(rand()%1030)+80;
                eggY[i]=650;
            }
        for(int i=3; i<6; i++)
            if(eggY[i]<=temp[i])
                eggY[i]-=6;

    }
}
void timer()
{
    if(st[play])
    {
        //printf("1\n");
        int s=0;
        s=sec-((sec/60)*60);
        t[7]=(sec/60)+'0';
        t[9]=(s/10)+'0';
        t[10]=(s%10)+'0';
        t[11]='\0';
        sec--;
        FILE *fp;
        fp=fopen("last read.txt","w");
        fprintf(fp,"%d\n%d",sec,point);
        fclose(fp);

        if(sec<0)
        {
            score_compare();
            strcpy(score,"SCORE: 0");
            st[play]=0;
        }
    }
}
void score_show(int *m)
{
    int n, i = 0 ;
    char str[20]="0";
    n=*m;
    if (*m < 0)
        n *= -1;
    while (n)
    {
        str[i++] = (n % 10) + '0';
        n /= 10;
    }
    if (*m < 0)
        str[i++] = '-';
    //str[i]='\0';
    score[7]='\0';
    strrev(str);
    strcpy(str1,str);
    strcat(score,str);
}
void score_compare()
{
    int x;
    FILE *fp1;
    if(m==1)
        fp1 = fopen("score.txt","r");
    else if(m==2)
        fp1 = fopen("score2.txt","r");
    else if(m==3)
        fp1 = fopen("score3.txt","r");

    while(!feof(fp1))
        fscanf(fp1,"%d",&x);

    fclose(fp1);
    if(point>=x)
        st[enter_name]=1;
    else
        st[home]=1;

}
void scoring(int sc)
{
    int score[10];
    char name[10][20];
    int i,f=1;

    FILE *fp1,*fp2;

    if(m==1)
    {
        fp1 = fopen("score.txt","r");
        fp2 = fopen("name.txt", "r");
    }
    else if(m==2)
    {
        fp1 = fopen("score2.txt","r");
        fp2 = fopen("name2.txt", "r");
    }
    else if(m==3)
    {
        fp1 = fopen("score3.txt","r");
        fp2 = fopen("name3.txt", "r");
    }

    for(i=0; i<10; i++)
    {
        fscanf(fp1,"%d",&score[i]);
        if(sc>=score[i] && f)
        {
            f=0;
            score[i+1]=score[i];
            score[i]=sc;
            i++;
        }
    }
    f=1;
    for(i=0; i<10; i++)
    {
        fgets(name[i],20,fp2);//fscanf(fp2,"%s",name[i]);//
        if(sc==score[i] && f)
        {
            f=0;
            strcpy(name[i+1],name[i]);
            strcpy(name[i],nm);
            int n=strlen(name[i]);
            name[i][n]='\n';
            name[i][n+1]='\0';
            strupr(name[i]);
            i++;
        }
    }

    fclose(fp1);
    fclose(fp2);

    if(m==1)
    {
        fp1 = fopen("score.txt","w");
        fp2 = fopen("name.txt", "w");
    }
    else if(m==2)
    {
        fp1 = fopen("score2.txt","w");
        fp2 = fopen("name2.txt", "w");
    }
    else if(m==3)
    {
        fp1 = fopen("score3.txt","w");
        fp2 = fopen("name3.txt", "w");
    }


    for(i=0; i<10; i++)
        fprintf(fp1,"%d\n",score[i]);

    fclose(fp1);

    for(i=0; i<10; i++)
    {
        fputs(name[i],fp2);
        //fprintf(fp2,"\n");
    }

    fclose(fp2);

}
void random()
{
    if(b)
    {
        l=0;
        x=200;
        n=rand()%3;
        blockX[n]=(rand()%1030)+80;
        b=0;
    }
}
void random_move()
{
    if(!b)
    {
        blockY[n]-=6;
        if(blockY[n]<=0)
        {
            blockY[n]=768;
            b=1;
        }
        else if(blockY[n]<=60 && ((blockX[n]+60)>=basketX&&(blockX[n]+60)<=(basketX+x)))
        {
            blockY[n]=768;
            b=1;
            if(n==0)
                sec+=10;
            else if(n==1)
            {
                l=1;
                x=318;
            }
            else if(n==2)
            {
                sec=0;
            }
        }
    }
}
int main()
{
    //place your own initialization codes here.

    st[home]=1;
    iSetTimer(15,eggMove);
    iSetTimer(15,eggMove1);
    iSetTimer(20,henMove);
    iSetTimer(5,up_down);
    iSetTimer(1000,timer);
    iSetTimer(8000,random);
    iSetTimer(15,random_move);
    if(music)
        PlaySound("sound.WAV",NULL,SND_LOOP|SND_ASYNC);
    iInitialize(screen_width, screen_height, "egg catch");
    //printf("%d",point);
    return 0;
}
