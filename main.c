#include <stdio.h>
#include <stdlib.h>
#include <sl.h>

//#define scanf scanf_s
/*
nb:number of butterflies 
ng:number of graph`s vertexes
ps:place of spider
G[ng]:hraph
B[nb]:place of butterflies
*/

short G[100][100];
int nb ;
int ng; 
int B[100];
int BC[100] ; 
int ps;
short winning[100];
short Set[100][100][100];
int x[100] ; 
int y[100] ; 

void MoveSpider(int);
void paria() ;
void cut(int , int);
void SW();

//determines if the game has ended or not
short IsGameOver() ;
void madochistic_user();
void smart_user();
void File();
int BestMove() ;
void GetInformation();
void GGraphic( );
int IsThisButterfly (int ) ; 
void cloner();

//shows the distance between two vertexes
int Distance(int ,int) ;
void BestC(int* ,int* );
int maximum(int , int);
int minimum (int , int);

int main()
{


	//the user choses between entering adjancency matrix and entering graph or entering prepared file.
	int c;
	printf("choose ; if you want to input adjancency matrix enter 1 , if you want to input graph enter 2 , if you want to use prepared file enter 3:");
	choose :
	scanf("%d",&c);
	printf("\n");
	switch (c)
	{
	case 1:
		GetInformation();
		madochistic_user();
		cloner () ;
		break;
	case 2:
		GetInformation();
		smart_user();
		cloner () ;
		break;
	case 3:
		File();
		cloner () ;
		break;
	default:
		printf("I told you to choose between 1 , 2 and 3!! 	😤  😤 	😤 Choose again!\n");
		goto choose;
	}


//asks the user for the wanted game mode
	int node1,node2;
	int f , v;
	printf("If you want to play as spider please enter 1 , if you want to play as butterfly please enter 2, and if you want me to play as both please enter 3:");
	choose2 :
	scanf("%d",&f);
	switch (f)
	{
	case 1:
		while(IsGameOver()==0)
		{
			
			printf("Where do you want to go");
			scanf("%d",&v);
			MoveSpider(v);
			SW();
			if(IsGameOver())
        		break;
    		BestC(&node1,&node2);
			cut (node1 ,node2);
			

		}
		if(BC[ps])
    		printf("spider won!");
    	else
    		printf("Butterfly won!");
		
		break;
	case 2:
		while(IsGameOver()==0)
			{
			SW();
			MoveSpider(BestMove());
			printf("which edge do you want to cut");
			scanf("%d %d",&node1,&node2);
			cut (node1 ,node2);
			
			}
		if(BC[ps])
    		printf("spider won!");
    	else
    		printf("Butterfly won!");
			
		break;
	case 3:
	slWindow(1920,780,"GIVE ME THE FULL SCORE",0);
 		SW();
		while(IsGameOver()==0)
		{   
			GGraphic() ;
    		MoveSpider(BestMove());
			GGraphic() ;
   			SW();
   			if(IsGameOver())
        		break;
    		BestC(&node1,&node2);
    		printf("Butterfly cuts {%d-%d}\ng",node1+1,node2+1);
    		cut (node1 ,node2);
    
		}
    	if(BC[ps])
        	printf("spider won!\n");
    	else
        	printf("Butterfly won!\n");

		break;
	default:
		printf("I told you to choose between 1 , 2 and 3!! 	😤  😤 	😤 Choose again!\n");
		goto choose2 ;
		break;
	
		
	}

	GGraphic() ; 
	slClose() ; 
} 

//finds the shortest distance between graph vertexes
int Distance(int a,int b)
{
    
    int dis[ng];
    for(int i = 0; i < ng;i++)
        dis[i]=-1;
    dis[b]=0;
    for(int i = 0; i < ng - 1;i++)
        for(int j = 0;j < ng ;j++)
            if(dis[j]==i)
                for(int x = 0;x < ng ;x++)
                    if(G[j][x]&&dis[x]==-1)
                        dis[x]=i+1;
   return dis[a];
}

//cuts graph`s vertexes
void cut ( int a , int b)
{
	G[a][b] = 0;
	G[b][a] = 0;
}

//gets the adjancency matrix from user
void madochistic_user()
{

	printf("Please enter digits for adjacency matrix.\n ");

    for(int i = 0; i < ng ;i++)
		for(int j = 0;j < ng ;j++)
		{
			scanf("%d",&G[i][j]);
			if( !(G[i][j] == 1 || G[i][j] == 0))
			{
				printf("Heeey adjancency matrix only consists of 1 or 0 ,please study!!🙄 🙄 🙄\n");
				j--;
			}
			else if(G[i][j] != G[j][i] && i>=j)
			{
				printf("Heeeeyyy!! adjancency matrix is symmetric try again!😠 😠 😠\n");
				j--;
			}
			else if( G[i][i] == 1 )
			{
				printf("Are you using your brain 😫 😫 😫!!?? main diagonal of adjancency matrix only consists of 0 try again!\n");
				j--;
			}
			

		}

}

void BestC(int* cut1,int* cut2)
{
    int MS[ng][ng];
    for(int i=0;i<ng;i++)
        for(int j=0;j<ng;j++)
            MS[i][j]=0;
    for(int i=0;i<ng;i++)
        if(G[i][ps]&&winning[i]){
            MS[minimum(i,ps)][maximum(i,ps)]++;
            for(int j=0;j<ng;j++)
                for(int x=0;x<j;x++)
                    if(Set[i][x][j])
                        MS[x][j]++;}
    *cut1=0;
    *cut2=0;
    for(int i=0;i<ng;i++)
        for(int j=0;j<i;j++)
            if(MS[j][i]>MS[*cut1][*cut2])
            {
                *cut1=j;
                *cut2=i;
            }
    if(!*cut1&&!*cut2)
        for(int i=0;i<ng;i++)
            for(int j=0;j<ng;j++)
                if(G[i][j])
                {
                    *cut1=i;
                    *cut2=j;
                }

}


//gets the graph from user then generate the adjacency matrix
void smart_user()
{
	int f;
	int i , j;
	int s = ng * (ng-1) /2;
	get_edge:
	printf("How many edges do you want?");
	scanf("%d",&f);
	printf("\n");

	//checks the necessary conditions before generating the aadjancency matrix

	if(f>s)
	{
		printf("Hey you idiot , the number you entered is bigger than the graph`s capacity");
		goto get_edge;
	}
	else if(f<=0)
	{
		printf("You really expect me to generate a graph with non_possitive number of edges 😑 😶 \n");
		goto get_edge;	
	}

	for(int d = 0 ;d < f;d++)
	{
		printf("Please determine between which vertexes are gonna be edges\n");
		scanf("%d %d",&i,&j);
		if (i==j)
		{
			printf("Hey you little!!! 	😵 	😵 	😵\tIt is not a pseudograph,You can`t have graph loop.\n");
			d--;
			continue;
		}
		else if(i > ng || j > ng)
		{
			printf("You are messing with me right!? 😊 😊 😊  ,We can`t have more vertexes than the number you have given me\n");
			d--;
		}
		else if(i <= 0 || j <= 0)
		{
			printf("You high or something ?! 🥴 🥴 🥴  how am I suppose to generate that!!??\n");
			d--;
		}
		else if(G[i][j] == 1 || G[j][i] == 1)
		{
			printf("You definetly have a death wish 👿 👿 👿 You alredy made that edge!\n");
			d--;
		}

		else 
		{
			G[i][j] = 1;
			G[j][i] = 1;		
		}
	}
}

short IsGameOver()
{
    if(BC[ps])
       return 1;
    int i;
    for(i=0;i<ng;i++)
        if(G[ps][i])
           return 0;
   return 1;
}

//reads prepared file(.map)
//1st gets the number of graph vertexes then adjancency matrix then number of butterflies then place of butterflies then place of spider 
void File ()
{
	FILE *map ;
	char path[100];
	char line[200];
	for(int i = 0 ;i < 1 ;i++)
	{
		printf("Enter the path :");
		scanf("%s",path);
		map = fopen(path,"r") ;
		if(map == NULL)
		{
			printf("No such file found  🙁 🙁 🙁 Be more careful next time ");
			i--;
		}
		
	}
	fgets(line,100,map);
	ng = atoi(line);
	fgets(line,100,map);
		for( int x = 0; x < ng ; x++)
	{
		fgets(line,100,map) ;
		for(int i = 0; i < ng ; i++)
		{
			 G[x][i] = line[i] - 48 ;
		}
	}
	fgets(line,100,map);
	nb = atoi(line);
	for(int j = 0 ; j < nb;j++)
	{
		fgets(line,100,map);
		B[j]= atoi(line);
	}
	fgets(line,100,map);
	ps = atoi(line);
	fclose(map) ; 
}


int BestMove()
{
    int i,j;
    int dis[ng],next;
    for(i=0;i<ng;i++)
        dis[i]=0;
    for(i=0;i<ng;i++)
        if(G[ps][i]&&winning[i])
           return i;
    for(i=0;i<ng;i++)
        if(G[i][ps])
            for(j=0;j<ng;j++)
                if(winning[j])
                    dis[i]+=Distance(i,j);

    for(i=0;i<ng;i++)
        if(G[ps][i])
            {
            next=i;
            break;
            }
    for(i=0;i<ng;i++)
        if(G[i][ps]&&dis[i]<dis[next])
            next=i;
   return next;
}


//gets information about graph vertexes and number and place of butterflies and place of spider
void GetInformation()
{
	for(int x = 0;x < 1;x++)
	{  
		printf("Please enter the number of graph vertexes (lower than 100 if not you will face consequnes) : ");
		scanf("%d", &ng);

		if(ng > 100 )
		{
			printf("Hey I siad don`t enter a number bigger than 100 🤬 🤬 🤬\n");
			x--;
		}
		else if ( ng < 0)
		{
			printf("You really expect me to generate a graph with negative number of vertexes 😑 😶 \n");
			x--;
		}
		else if(ng ==0 )
		{
			printf("Seriusly !! a graph with 0 number of vertexes! 	😱 	😱 	😱\n ");
			x--;
		}		
		printf("\n");
	}

	for(int x = 0;x < 1;x++)
	{
		printf("Please enter the number of butterflies: ");
		scanf("%d", &nb);
		if ( nb < 0)
		{
			printf("What the hell dude ,seriously!!?? 😑 😶 negative number of butterflies!!???\n");
			x--;
		}
		printf("\n");


		if(nb > ng)
		{
			printf("You can`t have more butterflies than graph vertexes shoud I spell everything out for you!!??😶 😶 😶 (keep that in mind that you are gonna have a spider too) .\n");
			x--;
		}
		if(nb == (ng -1))
		{
			printf("Are you cosidering the spider?!🤨 🤨 🤨 consider a place for him\n");
			x--;
		}
	}
	
	for(int i = 0; i< nb ;i++)
	{	
		printf("Please enter the place of butterflies: ");
		scanf("%d",&B[i]);
		for(int j = 0;j < i;j++)
		{
			if (B [j] == B[i])
			{
				printf("You already have inputed that place 😼 😼 😼 use that grey matter and try again \n ");
				i--;
			}
		}
	}
	printf("\n");


	get_spider :
	printf("Please enter the place of spider: ");
	scanf("%d",&ps);
	for(int i = 0 ;i < nb;i++)
	{	
		if (ps == B[i])
		{ 
			printf("You seriusly are on the spider`s side ha!😏 😏 😏 at least let the game begin before finishing it !\n");
			goto get_spider;
		}
	}
	printf("\n");
}

//this function generate graphic
void GGraphic()
{
	if (x[0] == 0 && x[1] == 0 && y[0]==0 && y[1]==0)
		paria() ; 
	slSetForeColor(1,1,1,1) ; 
	// print normal nodes 
	for(int i = 0 ; i < ng ; i++)
	{
		if ( IsThisButterfly(i+1))
		{
			slSetForeColor(0,1,0,1) ;
		}
		if (i+1 == ps)
		{
	 
			slSetForeColor(1,53.0/255,1,1) ;
		}
		slCircleFill(x[i-1],y[i-1],12,900) ; 
		slSetForeColor(1,1,1,1) ;
	}
	for(int i = 0 ; i < ng ; i++)
	{
		for(int j = 0 ; j <= ng ; j++)
		{
			if(G[i][j] == 1)
			{
				slLine(x[i],y[i],x[j],y[j]) ; 
			}
		}
	}
	slRender() ;  
	system("sleep 5");

}

 int IsThisButterfly (int n)
 {
	return BC[n] ; 
 }

void cloner ()
{
	for (int i = 0 ; i < nb ; i++ )
	{
		if(B[i] != 0)
		{
			BC[B[i]] = 1 ; 
		}
	}
}

int maximum(int a,int b)
{
    return a > b ? a : b ; 
}


int minimum(int a,int b)
{
    return a > b ? b : a ;
}

void paria ()
{
	time_t timer ; 
    srand((unsigned) time(&timer)) ;
	for(int i = 0; i < ng ; i++)
    {
        x[i] = rand()%1366 ;    
    }
    
    for(int j = 0 ; j < ng ; j++)
    {
        y[j] = rand()%768 ; 
    }
}

void MoveSpider(int v)
{
	printf("spider went from %d to %d\n",ps + 1,v + 1);
	ps = v;
}

void SW()
{
	   
    for (int i = 0;i < ng; i++)
        winning[i]=BC[i];
    for(int i = 0;i < ng ; i++)
        for(int j = 0; j < ng ;j++)
            for(int x = 0 ; x < ng ; x++)
                Set[i][j][x]=0;
    short same,collumn;
    for (int i=0;i<ng;i++)
        if(winning[i]&&!BC[i])
        {
            same=1;
            for(int j = 0;j < ng;j++)
                for(int x = 0; x < j;x++)
                    if(winning[j]&&winning[x]&&G[i][j]&&G[i][x])
                        for(int k = 0;k < ng;k++)
                            for(int l = 0;l < k;l++)
                                if(!(Set[j][l][k]||Set[x][l][k])&&Set[i][l][k])
                                    same=Set[i][l][k]=0;
       	    if(!same)
                i--;
        }
        else if(i+1)
        {
            collumn=1;
            for(int j = 0 ; j < ng && collumn ; j++)
                for(int x = 0+1;x < j&&collumn;x++)
                {
                    if(G[i][j]&&G[i][x]&&winning[j]&&winning[x])
                    {
                        collumn=0;
                        for(int k = 0;k < ng &&!collumn;k++)
                            for(int l = 0; l < k &&!collumn;l++)
                                if(Set[j][l][k] && Set[x][l][k])
                                    collumn=1;
                        if(!collumn)
                        {
                            winning[i]=1;
                            for(int k = 0; k < ng;k++)
                                for(int l = 0; l < k ;l++)
                                    if(Set[j][l][k]||Set[x][l][k])
                                        Set[i][l][k]=1;
                            i--;
                        }
                    }
                }
        }
}