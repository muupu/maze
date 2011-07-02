#include <stdio.h>
#include <stdlib.h>
#define Maxm 30
#define Maxn 30

struct m{  // 检索方向，按从东沿顺时针方向
	int dx; // 横向增量
	int dy;	// 纵向增量
} move[8] = { {0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1} }; 

typedef struct qnod{ // 队列的节点
	int x; // 记录到达点的行坐标
	int y; // 记录列坐标 
	int pre; //到达该点的出发点在队列中的下标
}qnode;

void creatmaze(int *maze,int m,int n) // 产生随机数0和1，建立迷宫，m是行，n是列
{
	int row = m+2;
	int pol = n+2;
	int r,p;

	for ( r=0; r < row ; r++){
		if( r == 0 || r == row -1){ // 在第一行和最后一行各添加一道墙(为1)
			for ( p = 0 ; p < pol ; p++ )
				maze[r*Maxm+p] = 1;
		}
		else {
			for ( p = 0 ; p < pol; p++){
				if ( p == 0 || p == pol -1) //在第一列和最后一列 添加一道墙
					maze[r*Maxm+p] = 1;
				else if ( r == 1 && p == 1 || r == row -2 && p == pol - 2) // (1,1)为入口，(m,n)为出口，各置为0
					maze[r*Maxm+p] = 0;
				else { // 在其他位置产生随机数0和1
					maze[r*Maxm+p] =rand()% 2 ;
				}
			}// for
		}// else
	} // for
}		

int findminpath( int *maze,qnode queue[],int m , int n)
{

	int front = 0; int rear = 0; // front指向实际的队首，rear指向队尾
	
	int i,j,i1,j1; // 坐标点(i,j)

	int dir; // 方向

	queue[0].x = 1; // 队列初始化，为入口点
	queue[0].y = 1;
	queue[0].pre = -1;
	maze [Maxm + 1] = -1;

	while( !(queue[front].x ==m && queue[front].y == n)) {// 不是出口点
		i = queue[front].x;
		j = queue[front].y;

		for(dir = 0; dir < 8; dir++){ // 将邻近通道放进栈
			i1 = i+move[dir].dx;
			j1 = j+move[dir].dy;			
			if( maze [i1 * Maxm + j1] == 0 ){
				rear++;         
				queue[rear].x = i1;
				queue[rear].y = j1;
				queue[rear].pre = front;
				maze [i1 * Maxm + j1] = -1; // 对已走过的位置将0改为-1
			}
		}
		if(front == rear){ // 栈空 , 失败
			printf("\nTHERE IS NO PATH.\n");
			return 0;
		}
		else { // front指向队列的下一个元素
			front ++;
		}
		
	}// while

	while(queue[front].pre != -1){
		printf("(%d , %d) --> ",queue[front].x,queue[front].y);
		front = queue[front].pre;
	}
	printf("(1 , 1)");

	return 1;
}

int main()
{
	int m,n;
	int i,j;
	char repeatflag;
	int maze[Maxm][Maxn];
	qnode queue[Maxm * Maxn];// 用于保存已到达的坐标点
	do{
		printf("建立迷宫，请输入长度 n = ");
		scanf("%d",&n);
		printf("请输入高度 m = ");
		scanf("%d",&m);
		printf("\n");

		creatmaze(maze[0],m,n);

		for (i = 0 ; i< m+2; i ++){
			for (j = 0 ; j < n+2 ;j++){
				printf("%d  ",maze[i][j]);
				
			}
			printf("\n");
			
		}
		findminpath ( maze[0],queue, m , n) ;
		getchar();

		printf("\n要再玩一次吗? (输入'n'或其他代表不要,'y'代表要)\n");
		scanf("%c",&repeatflag);
	}while(repeatflag == 'y');
}



	