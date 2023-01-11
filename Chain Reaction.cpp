//Header files used
#include<simplecpp>
#include<cmath>
#include<iostream>
#include<assert.h>

using namespace std;

//All the user defined functions are declared here
//.............
//.............
const int no_of_rows=8,no_of_columns=6;

bool win(int state[no_of_rows][no_of_columns]);          //Declaration of the win function to decide the wiiner

void drawGrid(int x1,int x2,int y1,int y2,int nrows,int ncols,int player_no)   //drawing the grids
{
    for(int i=x1,count=0;count<=ncols;i+= (x2-x1)/ncols , count++)
    {
        Line l1(i,y1,i,y2);
        if(player_no==1)
        {

            l1.setColor(COLOR(255,0,0));     //change of grids colour to red when it's player 1's turn
            l1.imprint();

        }
        else if(player_no==2)
        {

            l1.setColor(COLOR(0,255,0));     //change of grids colour to green when it's player 2's turn
            l1.imprint();
        }}

   {

    for(int i=y1,count=0;count<=nrows;i+= (y2-y1)/nrows , count++)
        {
            Line l1(x1,i,x2,i);
            if(player_no==1)
        {

            l1.setColor(COLOR(255,0,0));
            l1.imprint();

        }
        else if(player_no==2)
        {

            l1.setColor(COLOR(0,255,0));
            l1.imprint();
        }
        }
    }
}

void expand(int player_state[no_of_rows][no_of_columns],int x,int y,int player_no)  //expansion of orbs
{

    if(win(player_state))
       {
        assert(true);

       }

    if(x<0 || x>=no_of_columns || y < 0 || y >= no_of_rows)
        return;

    int max_val=3;
    if(x==0 || x == no_of_columns -1)
    {
        max_val--;
    }
    if(y==0 || y == no_of_rows - 1)        // checks maximum number of allowed orbs at corners and edges.
    {
        max_val--;
    }

    if(player_state[x][y]%10 <= max_val)
    {
                int no_of_circles= player_state[x][y]%10;

                Circle c(x*(822/no_of_columns) + (411/no_of_columns) , y *(488/no_of_rows) + (244/no_of_rows) , 20);
                c.setColor(COLOR(255,255,255));
                c.setFill();
                c.imprint();

                Circle c1(x*(822/no_of_columns) + (411/no_of_columns) - 9 , y *(488/no_of_rows) + (244/no_of_rows) - 9 , 7 );
                Circle c2(x*(822/no_of_columns) + (411/no_of_columns), y *(488/no_of_rows) + (244/no_of_rows) + 9, 7 );
                Circle c3(x*(822/no_of_columns) + (411/no_of_columns) + 9 , y *(488/no_of_rows) + (244/no_of_rows) - 9, 7);

                 if(player_no==1){
                    c1.setColor(COLOR(255,0,0));
                    c2.setColor(COLOR(255,0,0));
                    c3.setColor(COLOR(255,0,0));
                 }
                else{
                    c1.setColor(COLOR(0,255,0));
                    c2.setColor(COLOR(0,255,0));
                    c3.setColor(COLOR(0,255,0));
                }

                c1.setFill();
                c2.setFill();
                c3.setFill();

                if(no_of_circles>=1)
                    c1.imprint();

                if(no_of_circles>=2)
                    c2.imprint();

                if(no_of_circles>=3)
                    c3.imprint();


        return;
    }
    else if(player_state[x][y]%10 == max_val + 1)
    {

        Circle c(x*(822/no_of_columns) + (411/no_of_columns) , y *(488/no_of_rows) + (244/no_of_rows) , 20 );
        c.setColor(COLOR(255,255,255));
        c.setFill();
        c.imprint();

        player_state[x+1][y]=player_no*10+player_state[x+1][y]%10+1;
        expand(player_state,x+1,y,player_no);
        player_state[x-1][y]=player_no*10+player_state[x-1][y]%10+1;
        expand(player_state,x-1,y,player_no);
        player_state[x][y+1]=player_no*10+player_state[x][y+1]%10+1;
        expand(player_state,x,y+1,player_no);
        player_state[x][y-1]=player_no*10+player_state[x][y-1]%10+1;
        expand(player_state,x,y-1,player_no);

        player_state[x][y]=0;

    }

    else
        {
        return;
        }
}

bool win(int state[no_of_rows][no_of_columns])
{
    if(state[0][0]==0)
    {
        return false;
    }
    int winner=state[0][0]/10;
    for(int i=0;i<no_of_rows;i++)
        {
        for(int j=0;j<no_of_columns;i++)
            {
                if(state[i][j]==0)
                    {
                        return false;
                    }
                int temp_winner=state[i][j]/10;
                if(winner!=temp_winner)
                {
                    return false;
                }
            }
        }

    cout<<" CONGRATS .. PLAYER "<<winner<<" Wins!!! "<<endl;
    return true;
}

void playGame()
{

    int player_state[no_of_rows][no_of_columns];

    for(int i=0;i<no_of_rows;i++)
    {
        for(int j=0;j<no_of_columns;j++)
        {
            player_state[i][j]=0;
        }
    }


    int player_no=1;






        while(1)
       {
           drawGrid(0,822,0,488,no_of_rows,no_of_columns,player_no);

            int click=getClick();
            int xpos = click/65536;
            int ypos = click % 65536;

            int block_x=xpos/(822/no_of_columns);
            int block_y=ypos/(488/no_of_rows);

            if(block_x>no_of_columns || block_y > no_of_rows)
                continue;

            cout<<player_state[block_x][block_y]/10<<endl;
            if(player_state[block_x][block_y]/10 != player_no && player_state[block_x][block_y]!=0)
                continue;

            if(player_state[block_x][block_y]==0)
            {
                player_state[block_x][block_y]=player_no*10+1;

                Circle c(block_x*(822/no_of_columns) + (411/no_of_columns) , block_y *(488/no_of_rows) + (244/no_of_rows) , 15 );
                if(player_no==1)
                    c.setColor(COLOR(255,0,0));
                else
                    c.setColor(COLOR(0,255,0));
                c.setFill();
                c.imprint();
            }

            else
                {
                   player_state[block_x][block_y]++;

                   expand(player_state,block_x,block_y,player_no);
                }

            if(win(player_state))
                {
                    break;
                }

            if(player_no==1)
                player_no=2;
            else
                player_no=1;
        }
}
main_program
{

    initCanvas("CHAIN REACTION",822,488);
    Text game(411,50,"WELCOME TO THE GAME CHAIN REACTION");
    game.setColor(COLOR(255,0,0));
    Rectangle Startgame(411,150,100,24);
    Text Startga(411,150,"START GAME");
    Startga.setColor(COLOR(255,0,0));
    Rectangle Instru(411,250,125,24);
    Text inst(411,250,"INSTRUCTIONS");                    //
    inst.setColor(COLOR(0,0,255));
    Rectangle Qui(411,350,100,24);
    Text exit(411,350,"EXIT");
    exit.setColor(COLOR(0,0,255));
    Rectangle Hardness[4];
    Text Level[7];
    Text Hardness1[3];
do{

   int v=getClick();
   int m=v/65536;
   int n=v%65536;

   if(m>=361 && m<=461 && n>=338 && n<=362)
    {
        wait(0);
        return -1;
    }

   if(m>=361 && m<=461 && n>=126 && n <=174)
    {
        game.hide();
        Startgame.hide();     //Game has started
        Startga.hide();
        Instru.hide();
        inst.hide();
        Qui.hide();
        exit.hide();
        playGame();
        break;
   }

   if(348.5<= m && m<=473.5 && 226<=n && n <=274)
   {

    game.hide();
    Startgame.hide();
    Startga.hide();               //Instruction box is opened
    Instru.hide();
    inst.hide();
    Qui.hide();
    exit.hide();

    Text l1(411,97,"A 2 player game each player using orbs of different colour");
    Text l2(411,194,"Each player is allowed to place the orb in a empty cell");
    Text l3(411,291,"A cell explodes once the orbs have reached their critical mass");
    Text l4(411,388,"As soon as a player loses all his orbs he is out of the game");

    l1.setColor(CYAN);
    l2.setColor(CYAN);
    l3.setColor(CYAN);
    l4.setColor(CYAN);

    Rectangle strtgm(411,440,100,25);
    Text stgame(411,440,"START GAME");     //Game started after reading the instructions
    stgame.setColor(CYAN);

    int v=getClick();
    int m=v/65536;
    int n=v%65536;

        if(361<= m && m<=461 && 415<=n && n <=465)
            {
                l1.hide();
                l2.hide();
                l3.hide();
                l4.hide();
                strtgm.hide();
                stgame.hide();
                playGame();

            }


   }

   else
        {
        continue;
        }
   }
   while(true);

}
