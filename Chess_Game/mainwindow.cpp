#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <time.h>
#include <QtDebug>
#include <QKeyEvent>
#include <QPainter>
#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include "Gamemode.h"
#include "CHESS_MOVE.h"
int Game_Area[33][25]={0};//规划游戏区域
int pos_x,pos_y,chose_pos_x,chose_pos_y,Player_Chess,Convert=0,a=0;
 bool flag=false;
/*void Game_Over(int a)//游戏结束判定
{
    for(int i=0;i<=3;i++)
    {
        for(int j=9+3-i;j<=15-(3-i);j=j+2)
        {
            if(Game_Area[2*i][j]==3)
            {
                red_win=1;
            }
            else
            {
                red_win=0;
                break;
            }
        }
    }
    for(int i=0;i<=3;i++)
    {
        for(int j=9+i;j<=15-i;j=j+2)
        {
            if(Game_Area[26+2*i][j]==2)
            {
                blue_win=1;
            }
            else
            {
                blue_win=0;
                break;
            }
        }
    }
    if(red_win ==1)
    {
        qDebug("red win!!");
    }
    if(blue_win ==1)
    {
        qDebug("bule win!!");
    }
}*/
void MainWindow::Chess_area_init()//棋盘初始化
{

    int i=0,j=0;
    Game_Area[0][12]=1;

   for(i=1;i<=3;i++)
    {
        for(j=8;j<16;j++)
        {


            Game_Area[2*i][j]=Game_Area[2*i-2][j-1];
            if(Game_Area[2*i][j])
                continue;
            else
                Game_Area[2*i][j]=Game_Area[2*i-2][j+1];
        }


    }
    for(i=0;i<5;i++)
    {
        for(j=i;j<=24-i;j=j+2)
        {
            Game_Area[8+2*i][j]=1;
        }
    }
    for(i=3;i>=0;i--)
    {
        for(j=i;j<=24-i;j=j+2)
        {
            Game_Area[18+2*(3-i)][j]=1;
        }
    }
    for(j=0;j<=6;j=j+2)
    {
        for(i=9;i<=15;i++)
        {
            Game_Area[32-j][i]=Game_Area[j][i];
        }
    }

}
void MainWindow::Chess_Lay_init(int a)//放置初始棋子，其中的形参 a 代表不同的游戏模式以放置不同的棋子。
{
    int i,j;
    if(a==1)//双人PVP
    {
        Game_Area[0][12]=2;
        /*Game_Area[8][12]=2;*/
        for(i=1;i<=3;i++)//顶部蓝色棋子
        {
            for(j=8;j<16;j++)
            {


                Game_Area[2*i][j]=Game_Area[2*i-2][j-1];
                if(Game_Area[2*i][j])
                    continue;
                else
                    Game_Area[2*i][j]=Game_Area[2*i-2][j+1];
            }


        }
        /*Game_Area[24][12]=3;*/
        for(i=26;i<=32;i=i+2)
        {
            for(j=9;j<=16;j++)
            {
                if(Game_Area[i][j])
                    Game_Area[i][j]=3;
            }
        }

    }
}
void MainWindow::paintEvent(QPaintEvent *event)//绘制函数
{
    QPainter painter(this);//画游戏边框
    painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    painter.drawRect(MARGIN,MARGIN,COL*BLOCK_SIZE,ROW*BLOCK_SIZE);
    painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    for(int i=0;i<ROW;i++)
    {
        for(int j=0;j<COL;j++)
        {
            if(Game_Area[i][j])
            {
                painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
                painter.drawRoundedRect(MARGIN+j*BLOCK_SIZE,MARGIN+i*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE,10,10);
                switch (Game_Area[i][j])//"1"代表黑色棋盘；“2”代表蓝色棋子，“3”代表红色棋子“
                {
                case 2:
                    painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
                    painter.drawRoundedRect(MARGIN+j*BLOCK_SIZE,MARGIN+i*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE,10,10);
                    /*painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));*/
                    break;
                case 3:
                    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                    painter.drawRoundedRect(MARGIN+j*BLOCK_SIZE,MARGIN+i*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE,10,10);
                   /* painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));*/
                    break;
                case 4:
                    painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
                    painter.drawRoundedRect(MARGIN+j*BLOCK_SIZE,MARGIN+i*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE,10,10);
                    /*painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));*/
                    break;
                case 5:
                    painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
                    painter.drawRoundedRect(MARGIN+j*BLOCK_SIZE,MARGIN+i*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE,10,10);
                    break;
                   /* painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));*/
                case 6:
                    painter.setBrush(QBrush(Qt::magenta,Qt::SolidPattern));
                    painter.drawRoundedRect(MARGIN+j*BLOCK_SIZE,MARGIN+i*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE,10,10);
                    break;
                case 7:
                    painter.setBrush(QBrush(Qt::cyan,Qt::SolidPattern));
                    painter.drawRoundedRect(MARGIN+j*BLOCK_SIZE,MARGIN+i*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE,10,10);
                    break;
                case 8:
                    painter.setBrush(QBrush(Qt::gray,Qt::SolidPattern));
                    painter.drawRoundedRect(MARGIN+j*BLOCK_SIZE,MARGIN+i*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE,10,10);
                    break;
                default:
                    break;
                }

            }
        }
    }
    /*if(blue_win==1||red_win==1)
    {
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial",14));
        if(blue_win==1)
        {
            painter.drawText(QRect(2*MARGIN+COL*BLOCK_SIZE,MARGIN+ROW*BLOCK_SIZE,BLOCK_SIZE*2,BLOCK_SIZE*2),Qt::AlignCenter,"BLUE WIN!!");
        }
        if(red_win==1)
        {
            painter.drawText(QRect(2*MARGIN+COL*BLOCK_SIZE,MARGIN+ROW*BLOCK_SIZE,BLOCK_SIZE*2,BLOCK_SIZE*2),Qt::AlignCenter,"RED WIN!!");
        }

    }
    else
    {
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial",14));
        painter.drawText(QRect(2*MARGIN+COL*BLOCK_SIZE,MARGIN+ROW*BLOCK_SIZE,BLOCK_SIZE*2,BLOCK_SIZE*2),Qt::AlignCenter,"MOVING!!");
    }*/

}

void Chess_Move(int a)
{
    if(a==2&&Convert==3)
        Convert=0;
    if(a==1&&Convert==2)
        Convert=0;
    if(a==3&&Convert==4)
        Convert=0;
    if(a==4&&Convert==6)
        Convert=0;
    if(Convert==0)
    {
        Player_Chess=2;
    }
    if(Convert==1)
    {
        Player_Chess=3;
    }
    if(Convert==2)
    {
        Player_Chess=5;
    }
    if(Convert==3)
    {
        Player_Chess=6;
    }
    if(Convert==4)
    {
        Player_Chess=7;
    }
    if(Convert==5)
    {
        Player_Chess=8;
    }
    if(Game_Area[pos_y][pos_x]==Player_Chess)
    {
        if(!flag)//点击一颗棋子，如果之前未选中棋子，则选中该棋子。
        {
            flag=true;
            Game_Area[pos_y][pos_x]=4;
            chose_pos_x=pos_x;
            chose_pos_y=pos_y;
        }
    }

    if((chose_pos_x!=pos_x)||(chose_pos_y!=pos_y))
    {
        int jump_x=0,jump_y=0;
        for(int i=-2;i<=2;i++)
        {
            for(int j=-2;j<=2;j++)
            {
                if((pos_x+i==chose_pos_x)&&(pos_y+j==chose_pos_y)&&(pos_x>=0)&&(pos_y>=0)&&(pos_x<COL)&&(pos_y<ROW))
                {
                    if(Game_Area[pos_y][pos_x]==1)//棋子走一格，不借助其他棋子跳跃
                    {   Game_Area[pos_y][pos_x]=Player_Chess;
                        Game_Area[chose_pos_y][chose_pos_x]=1;
                        flag=false;
                        Convert++;
                        break;
                    }
                    if(Game_Area[pos_y][pos_x]==Player_Chess)//所选中棋子借助相邻棋子跳跃
                    {
                        jump_x=pos_x-chose_pos_x;
                        jump_y=pos_y-chose_pos_y;
                        if((pos_x+jump_x>=0)&&(pos_y+jump_y>=0)&&(pos_x+jump_x<COL)&&(pos_y+jump_y<ROW)&&(Game_Area[pos_y+jump_y][pos_x+jump_x]==1))
                        {
                            Game_Area[pos_y+jump_y][pos_x+jump_x]=Player_Chess;
                            Game_Area[chose_pos_y][chose_pos_x]=1;
                            flag=false;
                            Convert++;
                            break;
                        }
                    }
                }

            }

        }

    }
}
void MainWindow::mousePressEvent(QMouseEvent *ev )
{
    int i,j;

    if(ev->button()==Qt::LeftButton)
    {
        for(i=1;i<=COL;i++)//求棋子在Game_Area中对应的 x 坐标
        {
            if(ev->pos().x()-MARGIN-i*BLOCK_SIZE<=0)
            {
                pos_x=i-1;
                break;
            }
        }
        for(j=1;j<=ROW;j++)//求棋子在Game_Area中对应的 y 坐标
        {
            if(ev->pos().y()-MARGIN-j*BLOCK_SIZE<=0)
            {
                pos_y=j-1;
                break;
            }
        }
    }
    /*CHESS_MOVE::Chess_Move(flag,2,Game_Area,pos_y,pos_x,chose_pos_x,chose_pos_y,Player_Chess,Convert);*/
    if(a!=0)
        Chess_Move(a);
    if(ev->button()==Qt::RightButton&&flag==true)//取消选中棋子
    {
        flag=false;
        Game_Area[chose_pos_y][chose_pos_x]=Player_Chess;
    }

    if(a!=0)
        CHESS_MOVE::Gameover(a,Game_Area);
}
void MainWindow::timerEvent(QTimerEvent *event)//定时器，这里用作界面刷新
{

    if(event->timerId()==refresh_ms)//refresh_ms 代表一个200ms的定时器，每200ms刷新一次页面
        update();
}
void MainWindow::on_pushButton_2_clicked()//双人模式
{
    a=1;
    Convert=0;
    MainWindow::Chess_area_init();
    MODE::Gamemodefun(a,Game_Area);
}


void MainWindow::on_pushButton_3_clicked()//三人模式
{
    a=2;
    Convert=0;
    MainWindow::Chess_area_init();
    MODE::Gamemodefun(a,Game_Area);
}
void MainWindow::on_pushButton_clicked()//四人模式
{
    a=3;
    Convert=0;
    MainWindow::Chess_area_init();
    MODE::Gamemodefun(a,Game_Area);
}
void MainWindow::on_pushButton_4_clicked()
{
    a=4;
    Convert=0;
    MainWindow::Chess_area_init();
    MODE::Gamemodefun(a,Game_Area);
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("Chess_shin--Impact");
    Chess_area_init();//棋盘初始化
    /*Chess_Lay_init(1);*///游戏模式选择
    this->setMouseTracking(true);
    refresh_ms = startTimer(200);//启动定时器
    MODE::Gamemodefun(a,Game_Area);
}

MainWindow::~MainWindow()
{
    delete ui;
}









