#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 37
#define NOTHING 126
/*
Zichen Li (Mark) 1000031360
Xiao Tang Wang (Trista) 999523029
Wei Wang (Jonathan)  998802005
Aravind Jeyapalan  999776513
WINDOWS
*/
void manual_input(int row, int column, char grid[MAX][MAX]);
void file_input(char filename);
//void computer_play(char grid[MAX][MAX],int *y, int *x);
void inGameInput(int *y,int *x);
void fileInput(int *y, int *x,char grid[MAX][MAX],char *name);
char getB(int y, int x, char grid[MAX][MAX]);
int surrounded(char grid[MAX][MAX], int *around, char choose, int yU, int xU);
int inside(int y, int x, char grid[MAX][MAX]);
void touch(int *y, int *x, int dir);
void Play(char grid[MAX][MAX],int type,int x, int y);
//row=y
//colum=x
//grid[y][x]

int main(void){
    char start,method,filename[20],grid[MAX][MAX];
    int prow,pcolumn,score;
    int *row=&prow,*column=&pcolumn;
    int buffer;
    int i=0;
    for(;i<MAX;i++){
        int j=0;
        for(;j<MAX;j++)
            grid[i][j]=NOTHING;
    }

    //Asking for user input of computer play or interactive play
    printf("Would you like to play or let the computer play?\nPress \"I\" for interactive or press \"C\" for computer:\n");
    scanf("%c", &start);
    scanf("%c",&buffer);

    while (start!='I'&&start!='i'&&start!='C'&&start!='c'){
            printf("Please enter only \"I\" for interactive or \"C\" for computer play:\n");
            scanf("%c",&start);
            scanf("%c",&buffer);
    }

    //Asking the user for method of grid generation
    printf("Would you like to specify size of grid or read a grid from a file?\nPress \"M\" for manual input or press \"F\" for file input:\n");
    scanf("%c", &method);
    scanf("%c",&buffer);

    while (method!='M'&&method!='m'&&method!='F'&&method!='f'){
            printf("Please enter only \"M\" for manual input or \"F\" for file input:\n");
            scanf("%c",&method);
            scanf("%c",&buffer);
    }
    //Asks for file name
    if(method=='F'||method=='f'){
                printf("Please enter a filename (xxxxxxxx.yyy): ");
                scanf("%s", filename);
                //printf("AAAAAA");
                fileInput(row,column,grid,filename);

    }

    else if(method=='M'||method=='m'){

        //Asking the user for the dimensions of the grid
        printf("Please enter the dimensions of the grid (no larger than 36x36)\n    ex: '2 3' would produce a 2x3 row by column grid:\n");




        scanf("%d %d", row,column);



        //Checking the input values of row and column to be within range
        while ((*row)>36 || (*row)<2 || (*column)<2 || (*column>36)){
            printf("Row and/or column value not within range!\nPlease enter again:");
            scanf("%d%d",row,column);
        }
    system ("cls");

     manual_input(*row,*column,grid);
    }

    //Calls for user input grid generator
    if(start=='i'||start=='I'){
        Play(grid,1,*column,*row);
    }
    //Calls for user fild input grid generator
    if(start=='c'||start=='C'){
        Play(grid,2,*column,*row);
    }


return 0;
}

//This function generates a randomly produced grid using the dimensions given by the user
void manual_input(int row, int column, char grid[MAX][MAX]){

    //Seeds the random number generator
    srand((unsigned)time(NULL));

    //Declaration of 2D array
    char coordinate [MAX];
    int i,j,score=0;

    //Generating the arry containing the coordinate system
    for (i=0;i<MAX;i++){

        if(i<10)
            coordinate[i]='0'+i;

        else
            coordinate[i]='A'+i-10;
    }

    //Generates grid
    for (i = row; i >0; i--) {

        //Printing the y-coordinate

        for (j = 0; j <=column-1; j++) {

            //The following will output random elements(colours)
            int colour;
            colour=rand()%4;
            switch(colour){

            case 0:
            grid[row-i][j] ='r';
            break;

            case 1:
            grid[row-i][j] ='g';
            break;

            case 2:
            grid[row-i][j] ='b';
            break;

            case 3:
            grid[row-i][j] ='y';
            break;
            }

        }
    }



}

//Reads file
void fileInput(int *y, int *x,char grid[MAX][MAX],char *name){
    FILE *file=fopen(name,"r");
    if (file==NULL){
        printf("Unable to open file");
    }
    //Reads the file
    fscanf(file,"%d %d",y,x);
    int i=(*y)-1;
    fgetc(file);
    for(;i>=0;i--){
        int j=0;
        for(;j<(*x);j++){
           grid[i][j]=fgetc(file);
        }
        fgetc(file);
    }
    fclose(file);

    return;
}

//Converts the larger numbers to letters for coordinates
char printc(int x){
    if(x<10){
        return '0'+x;
    }
    return 'A'-10+x;

}

//Converts the alphabetical coordinates to number coordinates
int getIt(int x){
    if(x<'0'+10){
        return x-'0';
    }
    return x-'A'+10;

}

//This function prints the grid with the coordinates(which are obtained from the printc function)
void printMaze(int y, int x, char grid[MAX][MAX]){
    system ("cls");

    int i=y-1;

//Calls for the printc function which prints the y-axis of coordinates
    for(;i>=0;i--){
        printf("% c ",printc(i));
        int j=0;

        //Calls for the grid function to print the grid
        for(;j<x;j++){
           printf(" %c",grid[i][j]);
        }
        printf("\n");
    }

    printf("   ");
    i=0;

    //Calls for the printc function to print the x-axis of coordinates
    for(;i<x;i++){
        printf("%c ",printc(i));
    }
    printf("\n");

    return;
}

//This function asks the user to input the coordinates
void inGameInput(int *y,int *x){
    //ask for user input
    printf("Select the cell coordinates(row column):");
    char xc[10],yc[10];
    scanf("%s %s",&yc,&xc);

    //Sends the user input to the getIT function
    *y=getIt(*yc);
    *x=getIt(*xc);

    return;
}

//Keeps coordinates during elimination within bounds
int inside(int y, int x, char grid[MAX][MAX]){
    if (getB(y,x,grid)==NOTHING) return 0;
    return 1;
}

//Checks if input is within grid
char getB(int y, int x, char grid[MAX][MAX]){
    if (x>=0&&y>=0){
        return grid[y][x];
    }
    return NOTHING;
}

//Changes the coordinate being checked
void touch(int *y, int *x, int dir){
    if(dir==0){
        (*y)++;
    }
    if(dir==1){
        (*x)++;
    }
    if(dir==2){
        (*y)--;
    }
    if(dir==3){
        (*x)--;
    }

}

//Checks if selected coordiate is surrounded by blocks of the same color
int surrounded(char grid[MAX][MAX], int *around, char choose, int yU, int xU){
    int result=0;
    int i=0;
    for(;i<4;i++){
        int yT=yU,xT=xU;
        touch(&yT,&xT,i);
        if(getB(yT,xT,grid)==choose){
            result=1;
            around[i]=1;
        }
    }
    return result;

}

//Propogates elimination
void elimination(char grid[MAX][MAX], char choose, int y, int x,int *score){
    if(!inside(y,x,grid))
        return;

    int i=0;
    for(;i<4;i++){
        int yT=y,xT=x;
        touch(&yT,&xT,i);
        if(getB(yT,xT,grid)==choose){

            grid[yT][xT]=32;
            (*score)++;
            elimination(grid, choose,  yT,  xT,score);
        }
    }
}

//Checks if a row is empty
int rowEmpty(char grid[MAX][MAX],int y){
    int result=0;
    int i=0;
    for(;grid[0][i]!=NOTHING;i++){
        if(grid[y][i]!=32)
            result=1;
    }
    return result;
}

//Checks if a column is empty
int columnEmpty(char grid[MAX][MAX],int x){
    int result=0;
    int i=0;
    for(;grid[i][0]!=NOTHING;i++){
        if(grid[i][x]!=32)

            result=1;
    }
    return result;
}

//Eliminates columns using "~" sign
void eliminateColumn(char grid[MAX][MAX]){
    int i=0;
    for(;grid[0][i]!=NOTHING;i++){
        if(!columnEmpty(grid,i)){
            int j=0;
            for(;grid[j][0]!=NOTHING;j++){
                grid[j][i]=NOTHING;
            }
        }

    }
    return;


}

//Eliminates rows using "~"
void eliminateRow(char grid[MAX][MAX]){
    int i=0;
    for(;grid[i][0]!=NOTHING;i++){
        if(!rowEmpty(grid,i)){
            int j=0;
            for(;grid[0][j]!=NOTHING;j++){
                grid[i][j]=NOTHING;
            }
        }

    }
    return;


}

//Shifts row
void rowShift(char grid[MAX][MAX]){

    //printf(")))))))))))))))))))\n");
    int w;
    //scanf("%d",&w);

    int i=1;


    for(;grid[i][0]!=NOTHING;i++){
        int j=0;
        //printf("??????????????????????????\n");

        for(;j<i;j++){


            int m=0;

            //printf("*****************\n");
            //scanf("%d",&w);

            for(;grid[0][m]!=NOTHING;m++){
                //printf("$$$$$$$$$$$$$$$$$$$$$$$$\n");

                if(grid[j][m]==32){
                   grid[j][m]=grid[j+1][m];
                   grid[j+1][m]=32;
                }
            }

        }
    }
    return;
}

//Drops the column
void columnSwap(char grid[MAX][MAX],int x){
    int m=0;
    for(;grid[m][0]!=NOTHING;m++){
        grid[m][x]=grid[m][x+1];
        grid[m][x+1]=32;
    }
    return;


}

//Shifts the columns
void columnShift(char grid[MAX][MAX]){
    int i=1;
    int a=0;
    for(;grid[0][i]!=NOTHING;i++){
        int j=0;
        for(;j<i;j++){
            if(!columnEmpty(grid,j)){




                columnSwap(grid,j);



            }
        }
    }
    return;

}

//Determines win status
int hasWon(char grid[MAX][MAX]){
    int result=1;
    int i=0;
    for(;i<MAX;i++){
        int j=0;
        for(;j<MAX;j++){
            if(!(grid[i][j]==NOTHING||grid[i][j]==32)){
                result=0;
            }
        }
    }
    return result;
}

//Changes blocks to "~" if win status is true
int hasWonChange(char grid[MAX][MAX]){
    int result=1;
    int i=0;
    for(;i<MAX;i++){
        int j=0;
        for(;j<MAX;j++){
            if(!(grid[i][j]==NOTHING||grid[i][j]==' ')){
                result=0;
            }
        }
    }
    if(!result)
        return result;
    i=0;
    for(;i<MAX;i++){
        int j=0;
        for(;j<MAX;j++){
            if(grid[i][j]==' '){
                grid[i][j]=NOTHING;
            }
        }
    }
    return result;
}

//Propogates one selection (referred to as one "round")
void fire(char grid[MAX][MAX],char choose,int y, int x,int *score){

    (*score);
    int a=0;
    elimination(grid,choose,y,x,score);

    grid[y][x]=32;



    if (hasWonChange(grid)){
        return;
    }
    //printf("\nOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
    rowShift(grid);
    //printf("\n###################################");

    rowShift(grid);
    rowShift(grid);
    rowShift(grid);
    rowShift(grid);

    eliminateRow(grid);


    columnShift(grid);
    columnShift(grid);
    columnShift(grid);
    columnShift(grid);
    eliminateColumn(grid);


    return;
}

//Initiates "fire" function and keeps score
void oneRound(char grid[MAX][MAX],int yU, int xU,int *score){
   // printf("\nEEEEEEEEEEEEEEE");
    char choose=grid[yU][xU];
    int around[4]={0,0,0,0};
    int scoreT=0;

    if (surrounded(grid,around,choose,yU,xU)){
        //printf("\nLLLLLLLLLLLLLLLL");
        fire(grid,choose,yU,xU,&scoreT);
        //printf("\nUUUUUUUUUUUUUUUU");
    }
    *score+=scoreT*scoreT;

    return;
}

//Checks for lose status (if no more moves are available)
int hasLost(char grid[MAX][MAX]){
    int result=1;
    int i=0;
    int a[4]={0,0,0,0};
    for(;i<MAX;i++){
        int j=0;
        for(;j<MAX;j++){
            if(!(grid[i][j]==NOTHING||grid[i][j]==32)){

                if(surrounded(grid,a,grid[i][j],i,j)){
                    result=0;
                }
            }
        }
    }
    return result;

}

//Checks for win/lost status at the end of each round
int oneRoundPlay(int y, int x,char grid[MAX][MAX],int yU,int xU,int *score){
    oneRound(grid,yU,xU,score);



    if(hasWon(grid)){
        printMaze(y,x,grid);
        printf("\n\nyour score %d",*score);
        printf("\n\nYou Won ");
        return 1;
    }

    if(hasLost(grid)){
        printMaze(y,x,grid);
        printf("\n\nyour score %d",*score);
        printf("\n\nGame Over ");
        return 1;
    }
    return 0;

}


/*void computer_play(char grid[MAX][MAX],int *y, int *x){
    int i=0;
    int a[4]={0,0,0,0};
    for(;i<MAX;i++){
        int j=0;
        for(;j<MAX;j++){
            if(!(grid[i][j]==NOTHING||grid[i][j]==32)){
                if(surrounded(grid,a,grid[i][j],i,j)){
                    *y=i;
                    *x=j;
                    printf("the computer plays row %d  colum %d\npress any key and enter to continue\n",*y,*x);
                    char w;
                    scanf("%c",&w);
                    return;
                }
            }
        }
    }


}*/

//Makes a copy of the grid played (for purposes of safe keeping)
void copyGrid(char grid[MAX][MAX],char grid2[MAX][MAX]){
    int i=0,j=0;
    for(;i<MAX;i++){

        for(j=0;j<MAX;j++)
            grid2[i][j]=grid[i][j];
    }
}

//Finds the round with the maximum score
int maxScore(char grid[MAX][MAX],int score, int *y, int *x,int SIZE){

    //printf("BBBBBBBB\n");
    //int w;
    //scanf("%d",&w);
    int lowScore=0;
    if(SIZE)
        lowScore=10000000;

    if(hasWon(grid)||hasLost(grid)){
        return score;
    }
    int i=0;
    int a[4]={0,0,0,0};

    int yM=0,xM=0,yT,xT,scoreT;

    //printf("YYYYYY\n");
    //scanf("%d",&w);

    for(;i<MAX;i++){
        int j=0;
        for(;j<MAX;j++){
            if(!(grid[i][j]==NOTHING||grid[i][j]==32)){

                if(surrounded(grid,a,grid[i][j],i,j)){

                    yT=i;
                    xT=j;
                    scoreT=score;

                    char grid2[MAX][MAX];
                    copyGrid(grid,grid2);



                    //printMaze(25,25,grid2);

                   // printf("MMMMMMMMMMMM\n");
                   // scanf("%d",&w);

                    oneRound(grid2,yT,xT,&scoreT);

                    //0printf("NN %d  NN\n",scoreT);




                    if(scoreT<lowScore&&SIZE){
                        //printf("VVVVVVVV\n");
                        //scanf("%d",&w);
                        lowScore=scoreT;
                        yM=yT;
                        xM=xT;
                    }

                    if(scoreT>lowScore&&!SIZE){
                        //printf("VVVVVVVV\n");
                        //scanf("%d",&w);
                        lowScore=scoreT;
                        yM=yT;
                        xM=xT;
                    }
                }

            }
        }
    }


    //printf("TTTT %d TTTTT\n" ,lowScore);
    //scanf("%d",&w);

    *y=yM;
    *x=xM;
    return lowScore;

}

//Plays one round for computer play
void computer_play2(char grid[MAX][MAX],int *y, int *x, int SIZE){

    //printf("AAAAAAA");
    int w;
    //scanf("%d",&w);


    maxScore(grid,0,y,x,SIZE);


    printf("the computer plays row %d  colum %d\npress any key and enter to continue\n",*y,*x);
    char ww;
    scanf("%c",&ww);
    return;


}

//Initiates file
void stringInitiation(int x, int y, char grid[MAX][MAX]){
  FILE * pFILE;
  pFILE = fopen ("log.txt" , "w" );
  fprintf(pFILE,"TEAM INFO\nZichen Li (Mark) 1000031360\nXiao Tang Wang (Trista) 999523029\nWei Wang (Jonathan)  998802005\nAravind Jeyapalan  999776513\n");
  fprintf(pFILE,"%d %d\n\n",y,x);
  int i=0,j=0;
  for(;i<y;i++){
    for(j=0;j<x;j++){
        fputc(grid[i][j],pFILE);
    }
    fprintf(pFILE,"\n");
  }
  fprintf(pFILE,"\n\nSTART\nEND");
  fclose ( pFILE );

}

//Writes steps (coordinates and score)
void putInFile(int y , int x, int score){
  FILE * pFile;
  pFile = fopen ( "log.txt" , "r+" );
  fseek ( pFile , -3 , SEEK_END );
  fprintf(pFile,"%d %d %d\nEND",y,x,score);
  fclose ( pFile );
}

//Propogates game
void Play(char grid[MAX][MAX],int type,int x, int y){
    int pxU,pyU;
    int *xU=&pxU,*yU=&pyU;
    int finish=0, score=0,w;
    int SIZE;

    stringInitiation(x,y,grid);

    if (x*y>400)
        SIZE=1;

    else SIZE=0;

    while(!finish){
        printMaze(y,x,grid);
        printf("\n\nyour score %d\n",score);
        if (type==1)
            inGameInput(yU,xU);
        if(type==2)
            computer_play2(grid,yU,xU,SIZE);
        putInFile(*yU,*xU,score);
        finish=oneRoundPlay(y,x,grid,*yU,*xU,&score);

    }
    scanf("%d",&w);
}
