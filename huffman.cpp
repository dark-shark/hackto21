#include<bits/stdc++.h>
using namespace std;

struct freq{
char x;
int f;
};


struct nodeTree
{
    int info;
    struct nodeTree *left,*right;

};


struct nodeTree *getnodeTree(int info)
{
  struct nodeTree *ptr=(struct nodeTree *)malloc(sizeof(struct nodeTree));
  ptr->info=info;
  ptr->left=NULL;
  ptr->right=NULL;
  return ptr;

}


struct nodeTree *insertTree(struct nodeTree *root,int info)
{
  struct nodeTree *NEW=getnodeTree(info);
  if(root==NULL)
  {
      root=NEW;
  }
  else
  {
      struct nodeTree *ptr=root;
      struct nodeTree *beforeptr=ptr;

      while(ptr!=NULL)
      {
          if(info<ptr->info)
          {
              beforeptr=ptr;
              ptr=ptr->left;
          }
          else
          {
              beforeptr=ptr;
              ptr=ptr->right;
          }
      }

      if(info<beforeptr->info)
      {
          beforeptr->left=NEW;
      }
      else
      {
          beforeptr->right=NEW;
      }


  }


  return root;
}


void heapify(int arr[],int beg,int end)
{

    while(end>0)
    {
    int ptr=end,par;

    while(ptr>0)
    {
        if(ptr%2==0)
            par=(ptr/2)-1;
        else
            par=ptr/2;

        if(arr[ptr]>=arr[par])
        {
            int temp=arr[par];
            arr[par]=arr[ptr];
            arr[ptr]=temp;
        }
        ptr=par;

    }
    end--;
    }


}


struct nodeTree *heapsort(int arr[],int beg,int end,nodeTree *start)
{
    int x=0,c=0,a[2];

    for(int i=end;i>=beg;i--)
    {

    heapify(arr,beg,i);

    int temp=arr[0];
    arr[0]=arr[i];
    arr[i]=temp;

    x+=temp;
    a[c]=temp;

    c++;


    if(c==2){
        start=insertTree(start,x);
        start=insertTree(start,a[0])
        cout<<"x"<<endl;
        x=0;
        c=0;
    }
    }

    return start;
}


void sorttable(freq t[],int arr[],int n)
{
    for(int i=0;i<n;i++)
       arr[i]= t[i].f;

    sort(arr,arr+n);

   /* for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(t[i].f>=t[j].f)
            {
                freq temp=t[j];
                t[j]=t[i];
                t[i]=temp;
            }
        }
    }*/

}

void inorderDispaly(nodeTree *start)
{
    if(start!=NULL)
    {
        inorderDispaly(start->left);
        cout<<start->info<<endl;
        inorderDispaly(start->right);
    }
}

int main()
{

    int n;
    cin>>n;
    nodeTree *start=NULL;

    freq t[n],*p;
    int arr[n];

    for(int i=0;i<n;i++)
        cin>>t[i].x>>t[i].f;



    for(int i=0;i<n;i++)
       arr[i]= t[i].f;

    sort(arr,arr+n);


   start=heapsort(arr,0,n-1,start);


    inorderDispaly(start);



}
