#include <bits/stdc++.h>

using namespace std;
int lazy[2000]={0};
//
void build(int a[],int tree[],int ss,int se,int ind)                         // build segment tree
{                                                         
    if(ss==se)
    {
        tree[ind]=a[ss];
        return;
    }
    int mid=(ss+se)/2;
    build(a,tree,ss,mid,2*ind);
    build(a,tree,mid+1,se,2*ind+1);
    tree[ind]=min(tree[2*ind],tree[2*ind+1]);
}
//
int query(int tree[],int ss,int se,int qs,int qe,int ind)                 // return ans of query
{
    if(qe<ss||qs>se)
    return INT_MAX;
    if(ss>=qs&&se<=qe)
    return tree[ind];
    int mid=(ss+se)/2;
    int l=query(tree,ss,mid,qs,qe,2*ind);
    int r=query(tree,mid+1,se,qs,qe,2*ind+1);
    return min(l,r);
}
//

void update(int tree[],int ss,int se,int i,int inc,int ind)              // update node
{
    if(i>se||i<ss)
    return;
    if(ss==se)
    {
    tree[ind]+=inc;
    return;
    }
    int mid=(ss+se)/2;
    update(tree,ss,mid,i,inc,2*ind);
    update(tree,mid+1,se,i,inc,2*ind+1);
    tree[ind]=min(tree[2*ind],tree[2*ind+1]);
    
}
//
void updaterange(int tree[],int ss,int se,int qs,int qe,int inc,int ind)     // update range
{
    if(qe<ss||qs>se)
    return;
    if(ss==se)
    {
        tree[ind]+=inc;
        return;
    }
    int mid=(ss+se)/2;
    updaterange(tree,ss,mid,qs,qe,inc,2*ind);
    updaterange(tree,mid+1,se,qs,qe,inc,2*ind+1);
    tree[ind]=min(tree[2*ind],tree[2*ind+1]);
    
    
}
//
void updatelazy(int tree[],int ss,int se,int qs,int qe,int inc,int ind)
{
     if(qe<ss||qs>se)
       return;
       if(lazy[ind]!=0)
       {
           tree[ind]+=lazy[ind];
           if(ss!=se)
           {
               lazy[2*ind]+=lazy[ind];
               lazy[2*ind+1]+=lazy[ind];
               
           }
           lazy[ind]=0;
           
       }
       if(ss>=qs && se<=qe){
        tree[ind] += inc;
        
        // Pass the lazy value to children 
        if(ss!=se){
            lazy[2*ind] +=  inc;
            lazy[2*ind+1] += inc;
        }
    return;
    }
    int mid=(ss+se)/2;
    updatelazy(tree,ss,mid,qs,qe,inc,2*ind);
    updatelazy(tree,mid+1,se,qs,qe,inc,2*ind+1);
    tree[ind] = min(tree[2*ind],tree[2*ind+1]);
    
    return;
    
}
//
int querlazy(int tree[],int ss,int se,int qs,int qe,int ind)
{
    if(lazy[ind]!=0)
    {
        tree[ind]+=lazy[ind];
        if(ss!=se)
        {
            lazy[2*ind]+=lazy[ind];
            lazy[2*ind+1]+=lazy[ind];
            lazy[ind]=0;
        }
        
    }
    if(ss>qe||se<qs)
    return INT_MAX;
    if(ss>=qs&&se<=qe)
    return tree[ind];
    int mid=(ss+se)/2;
    int l=querlazy(tree,ss,mid,qs,qe, 2*ind);
    int r=querlazy(tree,mid+1,se,qs,qe, 2*ind+1);
    return min(l,r);
}

int main() {
int n;
cin>>n;
int a[n];
for(int i=0;i<n;i++)
cin>>a[i];
int tree[4*n+1];
build(a,tree,0,n-1,1);
int l,r;
cin>>l>>r;
cout<<query(tree,0,n-1,l,r,1)<<"\n";
int ind,inc;
cin>>ind>>inc;
 update(tree,0,n-1,ind,inc,1);
 cout<<query(tree,0,n-1,l,r,1);
return 0;
}

