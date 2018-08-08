#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 36
#define NAME_LENGTH 12

void manual_input(int row, int column);
void file_input(char filename);
void log_file(char grid[MAX][MAX]);
void log_file2(int row, int column, int score);

int main(void){
    char start, generation_method,filename[NAME_LENGTH];
    int row,column,ch;

    //Asking for user input of computer play or interactive play
    printf("Would you like to play or let the computer play?\nPress \"I\" for interactive or press \"C\" for computer:\n");
    scanf("%c", &start);
    //clear buffer
    ch = getchar();

    while (start!='I'&&start!='i'&&start!='C'&&start!='c'){
            printf("Please enter only \"I\" for interactive or \"C\" for computer play:\n");
            scanf("%c",&start);
            //clear buffer
            ch = getchar();
    }



    //Asking the user for method of grid generation
    printf("Would you like to specify size of grid or read a grid from a file?\nPress \"M\" for manual input or press \"F\" for file input:\n");
    scanf("%c", &generation_method);
    //clear buffer
    ch = getchar();


    while (generation_method!='M'&&generation_method!='m'&&generation_method!='F'&&generation_method!='f'){
            printf("Please enter only \"M\" for manual input or \"F\" for file input:\n");
            scanf("%c",&generation_method);
            //clear buffer
            ch = getchar();
            }

    if(generation_method=='F'||generation_method=='f'){
                printf("Please enter a filename (xxxxxxxx.yyy): ");
                gets(filename);
                file_input(filename);
    }

    else if(generation_method=='M'||generation_method=='m'){

        //Asking the user for the dimensions of the grid
        printf("Please enter the dimensions of the grid (no larger than 36x36)\n    ex: '2 3' would produce a 2x3 row by column grid:\n");
        scanf("%d %d", &row,&column);

        //Checking the input values of row and column to be within range
        while (row>36 || row<2 || column<2 || column>36){
                printf("Row and/or column value not within range!\nPlease enter again:");
                scanf("%d %d", &row,&column);
        }
    system ("cls");
    manual_input(row,column);
}

return 0;
}

//This function generates a randomly produced grid using the dimensions given by the user
void manual_input(int row, int column){

    //Seeds the random number generator
    srand((unsigned)time(NULL));

    //Declaration of 2D array
    char grid[MAX][MAX],coordinate [MAX];
    int i,j;

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
        printf("%c ",coordinate[i-1]);

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

            printf("%c ",grid[row-i][j] );
        }
        printf("\n");
    }

    printf ("  ");

    //Printing the x-coordinate
    for(i=0; i<=column-1; i++){
        printf("%c ",coordinate[i]);
    }
}

void file_input(char filename[NAME_LENGTH]){
    FILE *input;
    char color;
    puts(filename);
    if ((input = fopen(filename, "r")) == NULL) {
           printf("\nFilename invalid");
           puts(filename);
           return -1;
            }
   // fscanf(input,"%c",color);
    //while(fscanf!=EOF)
}








