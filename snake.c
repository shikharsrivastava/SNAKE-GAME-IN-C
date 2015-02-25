#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<fcntl.h>


#define INPUT_LEN 20
int halt(int);
void display(char**);
void moveright(char**);
void moveleft(char**);
void moveup(char**);
void movedown(char**);

char curr_dir;
int curr_x,curr_y;
int pos;


char answer[INPUT_LEN];

int main()
{
int i;
curr_dir='r';

char** map;
curr_x=curr_y=1;

map=(char**)calloc(25,sizeof(char*));

for(i=0;i<25;i++)
map[i]=(char*)calloc(25,sizeof(char));

map[1][1]='1';

for(i=0;i<25;i++)
{
map[0][i]='_';
map[24][i]='_';
map[i][0]='|';
map[i][24]='|';

}
int k=1;
while(k<=92)
{
display(map);
switch(curr_dir)
{

case 'r':moveright(map);
	break;
case 'l':moveleft(map);
	break;
case 'u':moveup(map);
	break;
case 'd':movedown(map);
	 break;

}
halt(1);

switch(answer[0])
{
 case 'w': if(curr_dir=='r' || curr_dir=='l')
		curr_dir='u';
		break;
 case 's': if(curr_dir=='r' || curr_dir=='l')
                curr_dir='d';
                break;
 case 'a':if(curr_dir=='u' || curr_dir=='d')
                curr_dir='l';
                break;
 case 'd':if(curr_dir=='u' || curr_dir=='d')
                curr_dir='r';
                break;
 case 'x':exit(0);
}

k++;

}
return 0;
}


void moveright(char** map)
{
	if(curr_x==23 && curr_y==1)
	{
	curr_dir='d';
	movedown(map);
	}
	else
{
	map[curr_y][curr_x+1]='1';
	map[curr_y][curr_x]=0;
	curr_x++;
}
}


void moveleft(char** map)
{
	if(curr_y==23 && curr_x==1)
	{
	curr_dir='u';
	moveup(map);
	}
	else
{
	map[curr_y][curr_x-1]='1';
	map[curr_y][curr_x]=0;
	curr_x--;
}
}

void moveup(char** map)
{
	if(curr_x==1 && curr_y==1)
	{
	curr_dir='r';
	moveright(map);
	}
	else
{
	map[curr_y-1][curr_x]='1';
	map[curr_y][curr_x]=0;
	curr_y--;
}
}

void movedown(char** map)
{
	if(curr_x==23 && curr_y==23)
	{
	curr_dir='l';
	moveleft(map);
	}
	else
{
	map[curr_y+1][curr_x]='1';
	map[curr_y][curr_x]=0;
	curr_y++;
}}

void display(char** map)
{

int i,j;

for(i=0;i<25;i++)
{
for(j=0;j<25;j++)
{
if(map[i][j]==0)
printf(" ");
else if(map[i][j]=='1')
printf("O");
else
printf("%c",map[i][j]);
}
printf("\n");
}

}




int halt(int sec)
{
    printf ("Please enter choice\n : ");
    fflush(stdout);
    time_t end = time(0) + sec; //sec seconds time limit.

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);


     pos = 0;
    while(time(0) < end)
    {
        int c = getchar();

        /* 10 is new line */
        if (c != EOF && c != 10 && pos < INPUT_LEN - 1)
            answer[pos++] = c;

        /* if new line entered we are ready */
   }

    answer[pos] = '\0';

    if(pos > 0)
        printf("%s\n", answer);
    else
        puts("\nSorry, I got tired waiting for your input !");
}
