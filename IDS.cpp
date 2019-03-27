#include <bits/stdc++.h>

#define N 3

using namespace std;

struct ND{
	int tile [N][N];
	int level;
};
bool Unique(int tile[N][N]){
	int hist[9]={0};

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			hist[tile[i][j]]++;
		}
	}

	for(int i=0; i<9; i++){
		if(hist[i]==0 || hist[i]>1){
			return false;
		}
	}

	return true;
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



ND* makeND(ND* curr_head, int currX, int currY, int newX, int newY){
	int i,j,temp;

	ND* new_ND=(ND*)malloc(sizeof(ND));
	
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			new_ND->tile[i][j]=curr_head->tile[i][j];
		}
	}
	
	temp=new_ND->tile[currX][currY];
	new_ND->tile[currX][currY]=new_ND->tile[newX][newY];
	new_ND->tile[newX][newY]=temp;
	
	new_ND->level=curr_head->level+1;

	return new_ND;
}



int main(){
	ND* head=(ND*)malloc(sizeof(ND));

	cout<<"Enter intial state and 0 for blank.\n";

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			int temp;
			cin>>temp;
			head->tile[i][j]=temp;
		}
	}

	if(!Unique(head->tile)){
		cout<<"All values must be unique." <<endl;
		exit(0);
	}
	if(!Solvable(head->tile))
	{
		cout<<" Solvable!.\n";
		exit(0);
	}

	head->level=0;

	int steps=0, currX,currY;
	int limits;
	for(limits=0;; limits++){
		stack<ND *> tree;

		tree.push(head);

		while(!tree.empty()){
			ND* curr_head=tree.top();
			tree.pop();

			if(Final(curr_head->tile)){
				cout<<" The solution is found.\n";
				cout<<"The total number of steps required are "<<steps<<"."<<endl;
				exit(0);
			}
			else{
				if(curr_head->level < limits){
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
						tree.push(new_ND);
					}
					if(currY-1>=0){
						steps++;
						ND* new_ND=makeND(curr_head,currX,currY,currX,currY-1);
						tree.push(new_ND);
					}
					if(currX+1<=2){
						steps++;
						ND* new_ND=makeND(curr_head,currX,currY,currX+1,currY);
						tree.push(new_ND);
					}
					if(currY+1<=2){
						steps++;
						ND* new_ND=makeND(curr_head,currX,currY,currX,currY+1);
						tree.push(new_ND);
					}
				}
			}
		}
	}

}