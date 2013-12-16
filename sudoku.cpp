#include<iostream>

#define R 9
#define C 9
using namespace std;

bool flag=false;//标志是否找出了一个解

void print_sudoku(int s[][C])
{
	cout<<endl;
	for(int i=0;i<R;i++)
	{
		if(i%3==0) cout<<endl;
		for(int j=0;j<C;j++)
		{
			if(j%3==0) cout<<"  ";
			cout<<s[i][j]<<" ";
		}
		cout<<"  "<<endl;
	}
	cout<<endl;
}
void input_sudoku(int s[][C])
{
	cout<<"please input the initial sudoku: ('_' denotes the place to be assigned a value)"<<endl;
	for(int i=0;i<R;i++)
	{
		for(int j=0;j<C;j++)
			cin>>s[i][j];
	}

}
bool judge_row(int s[][C], int r,int c)
{
    for(int j=0;j<C;j++)
	{
		if(j==c || s[r][j]==0) continue;
	//	if(j==c) continue;
        if(s[r][j]==s[r][c]) break;
	}
	if(j==C) return true;
	else return false;
//	return true;
}
bool judge_col(int s[][C],int r,int c) //judge whether duplicate or not. return false if it is, or true if it is not
{
    for(int i=0;i<R;i++)
	{
		if(i==r || s[i][c]==0) continue;
     //   if(i==r) continue;
		if(s[i][c]==s[r][c]) break;
	}
	if(i==R) return true;
	else  return false;
}
bool judge_cube(int s[][C],int r,int c)
{
	int cr,cc;
	int ir,jc;
	if(r<3) 
		cr=1;
	else if(r<6)
		cr=4;
	else
		cr=7;

	if(c<3)
		cc=1;
	else if(c<6)
		cc=4;
	else
		cc=7;

	for(int i=-1;i<=1;i++)
	{
        ir=i+cr;
		for(int j=-1;j<=1;j++)
		{
           jc=j+cc;
		   if((ir==r && jc==c)) continue;
		   if(s[ir][jc]==s[r][c]) return false;
		}
	}
	return true;
}
//judge判断是否可以填写，可以返回true，否则返回false
bool judge(int s[][C],int row,int col)
{
	if(judge_row(s,row,col) && judge_col(s,row,col) && judge_cube(s,row,col))
		return true;   //true 可以填
	else
		return false;
}
//依次填写每个方格的数字，index指示一个方格
void solution_one(int s[][C],int index)
{
	int row,col;
	bool nomodi=false;
	row=index/R;
	col=index%C;

	if(index==R*C) 
	{
		flag=true;
		return;
	}
     
	//如果当前方格已有初始数字，则不填写，填写下一个,并设nomodi为true，表示之前已有初始数字
	if(s[row][col]) 
	{
        nomodi=true;
		solution_one(s,index+1);
	}
	if(nomodi)
		return;

	for(int t=1;t<=R;t++)
	{	
		
		if(flag) return;
		s[row][col]=t;
		if(judge(s,row,col))  
		{

		//	print_sudoku(s);
			solution_one(s,index+1);
		}
	}
	if(t>R && !flag) 
       s[row][col]=0;
	
}

void solute_sudoku(int s[][C])
{
    int index=0;
	if(flag) flag=false;
   //solution_one(s,index);
    solution_one(s,index);
}

int main()
{
  //  input_sudoku(sudoku,R);
/*	char sudoku[R][C]={ {'_','_','_','_','_','_','_','_','7'},
					{'7','_','4','_','_','_','8','9','3'},
					{'_','_','6','8','_','2','_','_','_'},
					{'_','_','7','5','2','8','6','_','_'},
					{'_','8','_','_','_','6','7','_','1'},
					{'9','_','3','4','_','_','_','8','_'},
					{'_','_','_','7','_','4','9','_','_'},
					{'6','_','_','_','9','_','_','_','_'},
					{'4','5','9','_','_','_','1','_','8'}
				}; *///define the sudoku array
	int sudoku1[R][C]={{0,0,0,0,0,0,0,0,7},
		              {7,0,4,0,0,0,8,9,3},
					  {0,0,6,8,0,2,0,0,0},
					  {0,0,7,5,2,8,6,0,0},
					  {0,8,0,0,0,6,7,0,1},
					  {9,0,3,4,0,0,0,8,0},
					  {0,0,0,7,0,4,9,0,0},
					  {6,0,0,0,9,0,0,0,0},
					  {4,5,9,0,0,0,1,0,8},        
					};
	int sudoku2[R][C]={ {0,3,0,0,0,0,0,4,0},
						{0,1,0,0,9,7,0,5,0},
						{0,0,2,5,0,8,6,0,0},
						{0,0,3,0,0,0,8,0,0},
						{9,0,0,0,0,4,3,0,0},
						{0,0,7,6,0,0,0,0,4},
						{0,0,9,8,0,5,4,0,0},
						{0,7,0,0,0,0,0,2,0},
						{0,5,0,0,7,1,0,8,0},
					};
    cout<<"first sudoku:"<<endl;
	print_sudoku(sudoku1);
	solute_sudoku(sudoku1);
	cout<<"solution:"<<endl;
	print_sudoku(sudoku1);

	cout<<"second sudoku:"<<endl;
	print_sudoku(sudoku2);
	solute_sudoku(sudoku2);
	cout<<"solution:"<<endl;
	print_sudoku(sudoku2);
	return 0;
}
