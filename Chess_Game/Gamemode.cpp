#include "Gamemode.h"
#include <QDebug>




void MODE::Gamemodefun(int x,int Game_Area[33][25])
{
    int i,j;
    if(x==1)//双人模式
    {
            Game_Area[0][12]=2;

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
            for(i=26;i<=32;i=i+2)
            {
                for(j=9;j<=16;j++)
                {
                    if(Game_Area[i][j])
                        Game_Area[i][j]=3;
                }
            }

    }
   if(x==2)//三人模式
    {
            for(i=8;i<=14;i=i+2)
            {
                for(j=0;j<4-((i-8)/2);j++)
                {
                    Game_Area[i][(i-8)/2+2*j]=2;
                    Game_Area[i][(i-8)/2+2*j+18]=5;

                }
            }
            for(i=26;i<=32;i=i+2)
            {
                for(j=9;j<=16;j++)
                {
                    if(Game_Area[i][j])
                        Game_Area[i][j]=3;
                }
            }
    }
  if(x==3)//四人模式
    {
            for(i=8;i<=14;i=i+2)//蓝棋放置
            {
                for(j=0;j<4-((i-8)/2);j++)
                {
                    Game_Area[i][(i-8)/2+2*j]=2;
                }
            }



            Game_Area[0][12]=3;//红棋放置

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
            for(i=26;i<=32;i=i+2)//黄棋放置
            {
                for(j=9;j<=16;j++)
                {
                    if(Game_Area[i][j])
                        Game_Area[i][j]=5;
                }
            }


            for(int i=24;i>=18;i=i-2)//紫棋放置
            {
                for(int j=0;j<4-(24-i)/2;j++)
                {
                    Game_Area[i][2*j+(24-i)/2+18]=6;


                }
             }


    }
  if(x==4)//六人模式
    {
             for(i=8;i<=14;i=i+2)//蓝棋放置
             {
                for(j=0;j<4-((i-8)/2);j++)
                {
                    Game_Area[i][(i-8)/2+2*j]=2;
                }
             }



             Game_Area[0][12]=3;//红棋放置

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
             for(i=26;i<=32;i=i+2)//黄棋放置
             {
                for(j=9;j<=16;j++)
                {
                    if(Game_Area[i][j])
                        Game_Area[i][j]=5;
                }
             }


             for(int i=24;i>=18;i=i-2)//紫棋放置
             {
                for(int j=0;j<4-(24-i)/2;j++)
                {
                    Game_Area[i][2*j+(24-i)/2+18]=6;


                }
             }
             for(int i=24;i>=18;i=i-2)//天蓝棋放置
             {
                for(int j=0;j<4-(24-i)/2;j++)
                {
                    Game_Area[i][2*j+(24-i)/2]=7;


                }
             }
             for(i=8;i<=14;i=i+2)//灰棋放置
             {
                for(j=0;j<4-((i-8)/2);j++)
                {
                    Game_Area[i][(i-8)/2+2*j+18]=8;
                }
             }

    }
}


