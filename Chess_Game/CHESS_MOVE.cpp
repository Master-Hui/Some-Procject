#include "CHESS_MOVE.h"
#include "mainwindow.h"
int red_win=0,blue_win=0,yellow_win=0,magenta_win=0,cyan_win=0,gray_win=0;

 void CHESS_MOVE::Gameover(int a,int Game_Area[33][25])
{
     if(a==1)//双人模式
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

    }
     if(a==2)//三人模式
    {
        for(int i=24;i>=18;i=i-2)
        {
            for(int j=0;j<4-(24-i)/2;j++)
            {
                if(Game_Area[i][2*j+(24-i)/2]==5)
                    yellow_win=1;
                else
                {
                    yellow_win=0;
                    break;
                }


            }
            for(int i=24;i>=18;i=i-2)
            {
                for(int j=0;j<4-(24-i)/2;j++)
                {
                    if(Game_Area[i][2*j+(24-i)/2+18]==2)
                        blue_win=1;
                    else
                    {   blue_win=0;
                        break;
                    }

                }
            }
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


        }

    }

     if(a==3)//四人模式
    {

        for(int i=0;i<=3;i++)
        {
            for(int j=9+3-i;j<=15-(3-i);j=j+2)//黄方胜利
            {
                if(Game_Area[2*i][j]==3)
                {
                    yellow_win=1;
                }
                else
                {
                    yellow_win=0;
                    break;
                }
            }
        }
        for(int i=0;i<=3;i++)
        {
            for(int j=9+i;j<=15-i;j=j+2)//红方胜利
            {
                if(Game_Area[26+2*i][j]==2)
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
        for(int i=24;i>=18;i=i-2)//蓝方胜利
        {
            for(int j=0;j<4-(24-i)/2;j++)
            {

                if(Game_Area[i][2*j+(24-i)/2+18]==2)
                    blue_win=1;
                else
                {

                    blue_win=0;
                    break;
                }
            }
        }
        for(int i=8;i<=14;i=i+2)//紫方胜利
        {
            for(int j=0;j<4-((i-8)/2);j++)
            {
                if(Game_Area[i][(i-8)/2+2*j]==2)
                {
                    magenta_win=1;
                }
                else
                {
                    magenta_win=0;
                    break;
                }

            }
        }



    }
     if(a==4)//六人模式
    {
        for(int i=0;i<=3;i++)
        {
            for(int j=9+3-i;j<=15-(3-i);j=j+2)//黄方胜利
            {
                if(Game_Area[2*i][j]==3)
                {
                    yellow_win=1;
                }
                else
                {
                    yellow_win=0;
                    break;
                }
            }
        }
        for(int i=0;i<=3;i++)
        {
            for(int j=9+i;j<=15-i;j=j+2)//红方胜利
            {
                if(Game_Area[26+2*i][j]==2)
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
        for(int i=24;i>=18;i=i-2)//蓝方胜利
        {
            for(int j=0;j<4-(24-i)/2;j++)
            {

                if(Game_Area[i][2*j+(24-i)/2+18]==2)
                    blue_win=1;
                else
                {

                    blue_win=0;
                    break;
                }
            }
        }
        for(int i=8;i<=14;i=i+2)//紫方胜利
        {
            for(int j=0;j<4-((i-8)/2);j++)
            {
                if(Game_Area[i][(i-8)/2+2*j]==2)
                {
                    magenta_win=1;
                }
                else
                {
                    magenta_win=0;
                    break;
                }

            }
        }
        for(int i=24;i>=18;i=i-2)//灰棋胜利
        {
            for(int j=0;j<4-(24-i)/2;j++)
            {
                if(Game_Area[i][2*j+(24-i)/2]==8)
                {
                    gray_win=1;
                }
                else
                {
                    gray_win=0;
                    break;
                }


            }
        }
        for(int i=8;i<=14;i=i+2)//天蓝棋胜利
        {
            for(int j=0;j<4-((i-8)/2);j++)
            {
                if(Game_Area[i][(i-8)/2+2*j+18]==7)
                    cyan_win=1;
                else
                {
                    cyan_win=0;
                    break;
                }
            }
        }
    }
}
