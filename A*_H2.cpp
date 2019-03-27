#include <bits/stdc++.h>

using namespace std;

#define N 3
int steps=0;
struct ND{
	int tile [3][3];
	int fValue;
	int gValue;
	int hValue;
	ND * parent;
};


bool Unique(int tile[N][N]){
	int hist[9]={0};

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			hist[tile[i][j]]++;
		}
	}

	for(int i=0; i<9; i++){
		if(hist[i]!= 1){
			return false;
		}
	}

	return true;
}

int MDistance(int tile[3][3]){
	int sum=0;
	int x_val[9]={0,0,0,1,1,1,2,2,2};
	int y_val[9]={0,1,2,0,1,2,0,1,2};
	int k=1,i,j;
	
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(tile[i][j]!=k && tile[i][j]!=0){
				sum=sum+abs(x_val[(tile[i][j])-1]-i)+abs(y_val[(tile[i][j])-1]-j);
			}
			k++;
			if(k==9){
				k=0;
			}
		}	
	}
	
	return sum;
}

bool Final(int tile[N][N]){
	int value=1;

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if(tile[i][j]==value){
				value++;
				if(value==9)
					return true;
			}
			else{
				return false;
			}
		}
	}
	return true;
}


bool Solvable(int tile[N][N]){
	int array[9];
	int k=0;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			array[k++]=tile[i][j];
		}
	}

	int count=0;

	for(int i=0;i<8;i++){
		for(int j=i+1;j<9;j++){
			if(array[i]!=0 && array[j]!=0 && array[i]>array[j]){
				count++;
			}
		}
	}

	if(count%2==1){
		return false;
	}
	else{
		return true;
	}
}

struct CompareVals
{
    bool operator()(const ND* a, const ND* b){
		if(a->fValue > b->fValue){
			return 1;
		}
		else{
		    return 0;
	    }
    }
};


ND* makeND(ND* curr_head, int currX, int currY, int newX, int newY)
{
	int i,j,temp;

	ND* new_ND=(ND*)malloc(sizeof(ND));
	
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			new_ND->tile[i][j]=curr_head->tile[i][j];
		}
	}
	new_ND -> parent = curr_head ;
	temp=new_ND->tile[currX][currY];
	new_ND->tile[currX][currY]=new_ND->tile[newX][newY];
	new_ND->tile[newX][newY]=temp;
	
	new_ND->gValue=curr_head->gValue+1;
	new_ND->hValue=MDistance(new_ND->tile);
	new_ND->fValue=new_ND->gValue+new_ND->hValue;
	
	return new_ND;
}

void printmatrix(int tile[3][3], int fValue, int gValue, int hValue){
	for(int i=0; i<3; ++i){
		for(int j=0; j<3; ++j){
			cout<<tile[i][j]<<" \t  ";
		}

		cout<<endl;
	}
	printf("hValue = %d\n",hValue);
	printf("gValue = %d\n",gValue);
	printf("fValue = %d\n",fValue);
	//steps++;
}

void printPath (ND* head)
{
   if (head != NULL)
   {  printPath (head -> parent);}
	printmatrix(head->tile, head -> fValue, head -> gValue, head -> hValue);
	
    
}


int main(int argc, char const *argv[])
{
	ND* head=(ND*)malloc(sizeof(ND));

	cout<<"Enter intial state and 0 for blank.\n";

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			int temp;
			cin>>temp;
			head->tile[i][j]=temp;
		}
	}

	if(!Unique(head->tile))
	{   cout<<" All values must be unique.\n";
		exit(0);
	}

	if(!Solvable(head->tile)){
		cout<<" Cant be solved!.\n";
		exit(0);
	}

	head->gValue=0;
	head->hValue=MDistance(head->tile);
	head->fValue=head->gValue+head->hValue;

	printf("hValue = %d\n",head->hValue);
	printf("gValue = %d\n",head->gValue);
	printf("fValue = %d\n",head->fValue);

	priority_queue<ND *, vector<ND *>, CompareVals> tree;

	tree.push(head);
    head -> parent = NULL;
	int currX, currY;
	while(!tree.empty()){
		ND* curr_head=tree.top();
		tree.pop();

		if(Final(curr_head->tile)){
			cout<<"The solution is found!.\n";
			cout<<"The total number of steps: "<<steps<<"."<<endl;
			cout<<"Optimal step: " <<curr_head->gValue<<"."<<endl;
			printPath(curr_head);
			exit(0);
		}
		else{
			for(int i=0; i<N; i++){
				for(int j=0; j<N; j++){
					if(curr_head->tile[i][j]==0){
						currX=i, currY=j;
						break;
					}
				}
			}

			if(currX-1>=0){
				steps++;
				ND* new_ND=makeND(curr_head,currX,currY,currX-1,currY);
				printmatrix(new_ND -> tile, new_ND -> fValue, new_ND -> gValue, new_ND -> hValue);
				tree.push(new_ND);
			}
			if(currY-1>=0){
				steps++;
				ND* new_ND=makeND(curr_head,currX,currY,currX,currY-1);
				printmatrix(new_ND -> tile, new_ND -> fValue, new_ND -> gValue, new_ND -> hValue);
				tree.push(new_ND);
			}
			if(currX+1<=2){
				steps++;
				ND* new_ND=makeND(curr_head,currX,currY,currX+1,currY);
				printmatrix(new_ND -> tile, new_ND -> fValue, new_ND -> gValue, new_ND -> hValue);	
				tree.push(new_ND);
			}
			if(currY+1<=2){
				steps++;
				ND* new_ND=makeND(curr_head,currX,currY,currX,currY+1);
				printmatrix(new_ND -> tile, new_ND -> fValue, new_ND -> gValue, new_ND -> hValue);
				tree.push(new_ND);
			}
		}
	}
	return 0;
}