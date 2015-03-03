#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<time.h>
#include<unistd.h>
#include<fcntl.h>


#define MAP_SIZE 20
#define INPUT_LEN 20

char halt(time_t);
void generatefood();
void addsnakenode();
void display();
void movesamedir();
void movehead();
void movetail();
void gameover();


char answer[INPUT_LEN];
int food_x,food_y;
char temp_head_dir;
int pos;
struct Map
{
	int snake_node;
	char dir;

} ** map;

int curr_x,curr_y,curr_y_tail,curr_x_tail;
int snake_length;
char choice;

int main()
{

snake_length=1;
curr_x=3;curr_y=1;
curr_x_tail=1;curr_y_tail=1;

int i,j;

map=(struct Map**)calloc(MAP_SIZE,sizeof(struct Map*));
for(i=0;i<MAP_SIZE;i++)
map[i]=(struct Map*)calloc(MAP_SIZE,sizeof(struct Map));

for(i=0;i<MAP_SIZE;i++)
{
	map[0][i].snake_node='-';
	map[MAP_SIZE-1][i].snake_node='-';
	map[i][0].snake_node='|';
	map[i][MAP_SIZE-1].snake_node='|';
}

map[1][1].snake_node=1;
map[1][1].dir='r';
map[1][2].snake_node=1;
map[1][2].dir='r';
map[1][3].snake_node=1;
map[1][3].dir='r';
display();
char temp;
int eaten=1;
printf("controls\n");
printf("w-> up , s->down , d->right , a->left\n");
printf("press any key to continue\n");
pos=getchar();
pos=0;

while(1)
{	

	system("clear");
	display();
	choice=halt(1);
	if(eaten==1)	
	generatefood();
	eaten=0;
	map[food_y][food_x].snake_node=4;
	switch(choice)
	{
		case 'w':{if(map[curr_y][curr_x].dir=='d')
					choice='s';
		
				  movetail();
				  movehead();
				  	break;
				
		
		}  
		case 's':{ if(map[curr_y][curr_x].dir=='u')
					choice='w';
				 
				  movetail();
				  movehead();
				  	break;
				
		
		}  
				  
		case 'd':{ if(map[curr_y][curr_x].dir=='l')
					choice='a';
			
				  movetail();
				  movehead();
				  break;
				

			
		}  
				 
				 
		case 'a':{if(map[curr_y][curr_x].dir=='r')
					choice='d';
				  
				  movetail();
				  movehead();
				  break;
				
			
		}  
				 
		
		
					
		default : {
					switch(map[curr_y][curr_x].dir)
					{
						case 'u':choice='w';
								 break;
						case 'd':choice='s';
							     break;
						case 'l':choice='a';
							     break;
						case 'r':choice='d';
							break;
					}
				  movetail();
				  movehead();
			break;
		}
		case 'm':addsnakenode();
					break;
		case 'x' : exit(0);  		
	}
	
	map[curr_y][curr_x].dir=temp_head_dir;
	if(curr_y == 0 || curr_y ==MAP_SIZE-1 || curr_x==0 || curr_x ==MAP_SIZE-1)
	gameover();
	if(curr_y == food_y && curr_x ==food_x)
	{
	map[food_y][food_x].snake_node-=4;
	eaten=1;
	addsnakenode();
	}

	
	
	}
	return 0;
}


void movetail()
{	

	switch(map[curr_y_tail][curr_x_tail].dir)
	{
		case 'u' : {
				   map[curr_y_tail][curr_x_tail].snake_node-=1;
				   map[curr_y_tail][curr_x_tail].dir = 0;
				   curr_y_tail--;
				   map[curr_y_tail][curr_x_tail].snake_node+=1;
				   break;
			 }

		case 'd' : {
				   map[curr_y_tail][curr_x_tail].snake_node-=1;
				   map[curr_y_tail][curr_x_tail].dir = 0;
				   curr_y_tail++;
				   map[curr_y_tail][curr_x_tail].snake_node+=1;
				   break;
			}

		case 'l' : {
				   map[curr_y_tail][curr_x_tail].snake_node-=1;
				   map[curr_y_tail][curr_x_tail].dir = 0;
				   curr_x_tail--;
				   map[curr_y_tail][curr_x_tail].snake_node+=1;
				   break;
			}
		case 'r' :{
				   map[curr_y_tail][curr_x_tail].snake_node-=1;
				   map[curr_y_tail][curr_x_tail].dir = 0;
				   curr_x_tail++;
				   map[curr_y_tail][curr_x_tail].snake_node+=1;
				   break;
			}
				   
				   
		default:break;
	}
}



void movehead()
{
	
	switch(choice)
{
	case 'w' : {map[curr_y][curr_x].dir='u';
				temp_head_dir='u';
			   curr_y--;
			   if(map[curr_y][curr_x].snake_node>0 && map[curr_y][curr_x].snake_node<3)
			   gameover();
			   movesamedir();
			   break;
		}
	case 's' : { map[curr_y][curr_x].dir='d';
			   temp_head_dir='d';
			   curr_y++;
			   if(map[curr_y][curr_x].snake_node>0 && map[curr_y][curr_x].snake_node<3)
			   gameover();
			   movesamedir();
			   break;
		}
	case 'a' :  {map[curr_y][curr_x].dir='l';
			   temp_head_dir='l';
			   curr_x--;
			   if(map[curr_y][curr_x].snake_node>0 && map[curr_y][curr_x].snake_node<3 )
			   gameover();
			   movesamedir();
			   break;
		}
	case 'd' :  {map[curr_y][curr_x].dir='r';
				temp_head_dir='r';
			   curr_x++;
			   if(map[curr_y][curr_x].snake_node>0  && map[curr_y][curr_x].snake_node<3)
			   gameover();	  
			   movesamedir();
			   break;
		}
	default:break;
}

}


void movesamedir()
{
	

	int i,j;
	for(i=1;i<MAP_SIZE-1;i++)
	for(j=1;j<MAP_SIZE-1;j++)
	{
		if(map[i][j].snake_node>0 )
		{
			switch(map[i][j].dir)
			{
				case 'u':{ 
				          map[i][j].snake_node-=1;
						  map[i-1][j].snake_node+=1;
						  break;
						  
					}

				case 'd':{ 
						  map[i][j].snake_node-=1;
						  map[i+1][j].snake_node+=1;
						  break;
					}

				case 'l': {
						  map[i][j].snake_node-=1;
						  map[i][j-1].snake_node+=1;
						  break;
					}

				case 'r': {
						  map[i][j].snake_node-=1;
						  map[i][j+1].snake_node+=1;
  						  break;
					}
				default:break;

			}
		}

	}

}

void addsnakenode()
	
	{
		
		if(map[curr_y_tail+1][curr_x_tail].snake_node==0)
		{
			map[++curr_y_tail][curr_x_tail].snake_node=1;
			map[curr_y_tail][curr_x_tail].dir='u';
		}
		else if(map[curr_y_tail-1][curr_x_tail].snake_node==0)
		{
			map[--curr_y_tail][curr_x_tail].snake_node=1;
			map[curr_y_tail][curr_x_tail].dir='d';			
		}
		else if(map[curr_y_tail][curr_x_tail+1].snake_node==0)
		{
			map[curr_y_tail][++curr_x_tail].snake_node=1;
			map[curr_y_tail][curr_x_tail].dir='l';
		}
		else if(map[curr_y_tail][curr_x_tail-1].snake_node==0)
		{
			map[curr_y_tail][--curr_x_tail].snake_node=1;
			map[curr_y_tail][curr_x_tail].dir='r';
		}
	}
	
	
	

void display()
{
	int i,j;
	for(i=0;i<MAP_SIZE;i++)
	{
	for(j=0;j<MAP_SIZE;j++)
	{	
		if(map[i][j].snake_node == 1)
		{
		if(i==curr_y && j==curr_x)
		printf("0");
		else if(curr_y_tail==i && curr_x_tail==j)
		printf("O");
		else	
		printf("O");
		
		
		}
		else if(map[i][j].snake_node =='-' || map[i][j].snake_node=='|')
		printf("%c",map[i][j].snake_node);
		else if(map[i][j].snake_node==4)
		printf("*");
		else
		printf(" "); 

	}
	printf("\n");
	}

}

void gameover()
{	display();
	printf("##############   GAME OVER ###################");
	exit(0);
}

void generatefood()
{	food_x=rand()%MAP_SIZE;
	food_y=rand()%MAP_SIZE;
	while(map[food_x][food_y].snake_node !=0)
	{
		food_x=rand()%MAP_SIZE-1;
		food_y=rand()%MAP_SIZE-1;
	}
}

char halt(time_t sec)
{
    printf ("Please enter choice\n : ");
    fflush(stdout);
    time_t end = time(0) + sec; //sec seconds time limit.

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

	system ("/bin/stty raw");
     pos = 0;
	int c;
    while(time(0) < end)
    {
        c=getchar();

        /* 10 is new line */
        if (c != EOF && c != 10 && pos < INPUT_LEN - 1)
            answer[pos++] = c;


   }

    answer[pos] = '\0';

    if(pos > 0)
        printf("%s\n", answer);
    else
        puts("\nSorry, I got tired waiting for your input !");
	system ("/bin/stty cooked");
	return answer[0];

}

