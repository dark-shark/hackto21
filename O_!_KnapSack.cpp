#include <bits/stdc++.h>
using namespace std;

int Knapsack(int wt[], int va[], int n, int W){
    // Base Condition:-
    if(n==0 || W==0){
        return 0;
    }
    // Choice Diagram Code:-
    if(wt[n-1]<=W){
        return(max((va[n-1]+Knapsack(wt,va,n-1,W-wt[n-1])), Knapsack(wt,va,n-1,W)));
    }
    if(wt[n-1]>W){
        return(Knapsack(wt,va,n-1,W));
    }
    return 0;
}

int main(){
    int n,W;
    cin>>n>>W;

    int weight[n],value[n];
    for(int i=0; i<n; i++){
        cin >> weight[i];
    }
    for(int i=0; i<n; i++){
        cin >> value[i];
    }
    int maxProfit = Knapsack(weight,value,n,W);
    cout <<"MaxProfit:"<<maxProfit;
   
    return 0;
}
