#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 36
#define NOTHING 126
void manual_input(int row, int column, char grid[MAX][MAX]);
void file_input(char filename);
void interactive_play(char grid[MAX][MAX]);
void computer_play(char grid[MAX][MAX],int *y, int *x);
void log_file(char grid[MAX][MAX]);
void log_file2(int row, int column, int score);
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
char start,method,filename[20],grid[MAX][MAX],buffer;
int prow,pcolumn,score;
int *row=&prow,*column=&pcolumn;
int i=0;
for(;i<MAX;i++){
int j=0;
for(;j<MAX;j++)
grid[i][j]=NOTHING;
}
//Asking for user input of computer play or interactive play
printf("Would you like to play or let the computer play?\nPress \"I\" for interactive or press \"C\" for computer:\n");
scanf("%c", &start);scanf("%c", &buffer);
while (start!='I'&&start!='i'&&start!='C'&&start!='c'){
printf("Please enter only \"I\" for interactive or \"C\" for computer play:\n");
scanf("%c",&start);scanf("%c", &buffer);
}
//Asking the user for method of grid generation
printf("Would you like to specify size of grid or read a grid from a file?\nPress \"M\" for manual input or press \"F\" for file input:\n");
scanf("%c", &method);scanf("%c", &buffer);

while (method!='M'&&method!='m'&&method!='F'&&method!='f'){
printf("Please enter only \"M\" for manual input or \"F\" for file input:\n");
scanf("%c",&method);scanf("%c", &buffer);
}
//Asks for filename
if(method=='F'||method=='f'){
printf("Please enter a filename (xxxxxxxx.yyy): ");
scanf("%s", filename);
printf("AAAAAA");
fileInput(row,column,grid,filename);
}
else if(method=='M'||method=='m'){
//Asking the user for the dimensions of the grid
printf("Please enter the dimensions of the grid (no larger than 36x36)\n ex: '2 3' would produce a 2x3 row by column grid:\n");
scanf("%d %d", row,column);
//Checking the input values of row and column to be within range
while ((*row)>36 || (*row)<2 || (*column)<2 || (*column>36)){
printf("Row and/or column value not within range!\nPlease enter again:");
scanf("%d%d",row,column);
}
system ("cls");
manual_input(*row,*column,grid);
}
//Calls for user input grid generation
if(start=='i'||start=='I'){
Play(grid,1,*column,*row);
}
//Calls for file input grid generation
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
//Calls small, medium, large grids
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
//Print coordinate
char printc(int x){
if(x<10){
return 48+x;
}
return 65-10+x;
}
//Converts the alphabetical coordinates to numbers for simplicity
int getIt(int x){
if(x<58){
return x-48;
}
return x-65+10;
}
//This function prints the grid with the coordinates(which are obtained from the printc function)
void printMaze(int y, int x, char grid[MAX][MAX]){
system ("cls");
//Calls for the printc function which prints the y-axis of coordinates
int i=y-1;
for(;i>=0;i--){
printf("%c",printc(i));
int j=0;
//Calls for the grid function to print the grid
for(;j<x;j++){
printf(" %c",grid[i][j]);
}
printf("\n");
}
printf("  ");
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
printf("Select the cell coordinates(row column):");
char xc[10],yc[10];
scanf("%s %s",&yc,&xc);
//Sends the user input to the getIT function
*y=getIt(*yc);
*x=getIt(*xc);
return;
}

int inside(int y, int x, char grid[MAX][MAX]){
if (getB(y,x,grid)==NOTHING) return 0;
return 1;
}
char getB(int y, int x, char grid[MAX][MAX]){
if (x>=0&&y>=0){
return grid[y][x];
}
return NOTHING;
}
//The following functions deals with eliminating the neighbouring blocks
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
elimination(grid, choose, yT, xT,score);
}
}
}
int rowEmpty(char grid[MAX][MAX],int y){
int result=0;
int i=0;
for(;grid[0][i]!=NOTHING;i++){
if(grid[y][i]!=32)
result=1;
}
return result;
}
int columnEmpty(char grid[MAX][MAX],int x){
int result=0;
int i=0;
for(;grid[i][0]!=NOTHING;i++){
if(grid[i][x]!=32)
result=1;
}
return result;
}
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
void rowShift(char grid[MAX][MAX]){
int i=1;
for(;grid[i][0]!=NOTHING;i++){
int j=0;
for(;j<i;j++){
int m=0;
for(;grid[0][m]!=NOTHING;m++){
if(grid[j][m]==32){
grid[j][m]=grid[j+1][m];
grid[j+1][m]=32;
}
}
}
}
return;
}
void columnSwap(char grid[MAX][MAX],int x){
int m=0;
for(;grid[m][0]!=NOTHING;m++){
grid[m][x]=grid[m][x+1];
grid[m][x+1]=32;
}
return;
}
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
int hasWonChange(char grid[MAX][MAX]){
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
if(!result)
return result;
i=0;
for(;i<MAX;i++){
int j=0;
for(;j<MAX;j++){
if(grid[i][j]==32){
grid[i][j]=NOTHING;
}
}
}
return result;
}
void fire(char grid[MAX][MAX],char choose,int y, int x,int *score){
(*score)++;
int a=0;
elimination(grid,choose,y,x,score);
grid[y][x]=32;
if (hasWonChange(grid)){
return;
}
rowShift(grid);
rowShift(grid);
eliminateRow(grid);
columnShift(grid);
columnShift(grid);
eliminateColumn(grid);
}
void oneRound(char grid[MAX][MAX],int yU, int xU,int *score){
char choose=grid[yU][xU];
int around[4]={0,0,0,0};
if (surrounded(grid,around,choose,yU,xU)){
fire(grid,choose,yU,xU,score);
}
}
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
printf("\n");
}
}
}
return result;
}
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
printf("\n\nYou Lost ");
return 1;
}
return 0;
}
void computer_play(char grid[MAX][MAX],int *y, int *x){
int i=0;
int a[4]={0,0,0,0};
for(;i<MAX;i++){
int j=0;
for(;j<MAX;j++){
if(!(grid[i][j]==NOTHING||grid[i][j]==32)){
if(surrounded(grid,a,grid[i][j],i,j)){
*y=i;
*x=j;
printf("the computer plays row %d colum %d\npress any key and enter to continue\n",*y,*x);
char w;
scanf("%c",&w);
return;
}
}
}
}
}
void copyGrid(char grid[MAX][MAX],char grid2[MAX][MAX]){
int i=0,j=0;
for(;i<MAX;i++){
for(j=0;j<MAX;j++)
grid2[MAX][MAX]=grid[MAX][MAX];
}
}
int maxScore(char grid[MAX][MAX],int score, int *y, int *x){
if(hasWon(grid)||hasLost(grid)){
return score;
}
int i=0,lowScore=0;
int a[4]={0,0,0,0};
int yM=0,xM=0,yT,xT,scoreT;
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
oneRound(grid2,yT,xT,&scoreT);
if(scoreT>lowScore){
lowScore=scoreT;
yM=yT;
xM=xT;
}
}
}
}
}
*y=yM;
*x=xM;
return lowScore;
}
void computer_play2(char grid[MAX][MAX],int *y, int *x){
printf("AAAAAAA");
int w;
scanf("%d",w);
maxScore(grid,0,y,x);
printf("the computer plays row %d colum %d\npress any key and enter to continue\n",*y,*x);
char u;
scanf("%c",&u);
return;
}
void Play(char grid[MAX][MAX],int type,int x, int y){
int pxU,pyU;
int *xU=&pxU,*yU=&pyU;
int finish=0, score=0,w;
while(!finish){
printMaze(y,x,grid);
printf("\n\nyour score %d\n",score);
if (type==1)
inGameInput(yU,xU);
if(type==2)
computer_play(grid,yU,xU);
finish=oneRoundPlay(y,x,grid,*yU,*xU,&score);
}
scanf("%d",&w);
}
