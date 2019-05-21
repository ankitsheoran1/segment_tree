#include<bits/stdc++.h>

using namespace std;
int a[100000][2][2];
	int r,n,q;
int tree[4*100000+1][2][2];
void multiply(int a1[2][2],int b[2][2],int r1[2][2])
{
    r1[0][0]=(a1[0][0]*b[0][0]+a1[0][1]*b[1][0])%r;
    r1[0][1]=(a1[0][0]*b[0][1]+a1[0][1]*b[1][1])%r;
    r1[1][0]=(a1[1][0]*b[0][0]+a1[1][1]*b[1][0])%r;
    r1[1][1]=(a1[1][0]*b[0][1]+a1[1][1]*b[1][1])%r;
}
void build(int ss,int se,int ind)
{
    if(ss==se)
    {
        for(int i=0;i<2;i++)
        {
            for(int j=0;j<2;j++)
            {
                tree[ind][i][j]=a[ss][i][j];
            }
        }
        return;
    }
    int mid=(ss+se)/2;
    build(ss,mid,2*ind);
    build(mid+1,se,2*ind+1);
    multiply(tree[2*ind],tree[2*ind+1],tree[ind]);
}

void query(int ss,int se,int qs,int qe,int res[2][2],int ind)
{
    if(qe<ss||qs>se)
    return;
     if(ss>=qs&&se<=qe)
    {
        for(int i=0;i<2;i++)
        {
            for(int j=0;j<2;j++)
            {
                res[i][j]=tree[ind][i][j];
            }
        }
        return;
    }
    int mid=(ss+se)/2;
     int x[2][2]={{1,0},{0,1}},y[2][2]={{1,0},{0,1}};
     query(ss,mid,qs,qe,x,2*ind);
     query(mid+1,se,qs,qe,y,2*ind+1);
     multiply(x,y,res);
}

int main() {

	cin>>r>>n>>q;
	for(int i=0;i<n;i++)
	{
	    for(int j=0;j<2;j++)
	    {
	        for(int k=0;k<2;k++)
	        {
	            cin>>a[i][j][k];
	        }
	    }
	}
	build(0,n-1,1);
	
	while(q--)
	{
	    int l,r;
	    int res[2][2]={{1,0},{0,1}};
	    cin>>l>>r;
	    l--;r--;
	    query(0,n-1,l,r,res,1);
	    for(int i=0;i<2;i++)
	    {
	        for(int j=0;j<2;j++)
	        cout<<res[i][j]<<" ";
	        cout<<"\n";
	    }
	}
	
	
	return 0;
	
	
}

