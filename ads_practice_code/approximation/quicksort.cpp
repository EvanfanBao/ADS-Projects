#include<iostream>
#include<vector>

using namespace std;
// Naive quick sort
void quickSort(int A[],int L, int R){
    int pivot = A[R];
    if(L >= R)return;
    int i = L, j = R-1;
    while(1){
        while(A[i] < pivot && i!=R){i++;}
        while(A[j] > pivot && j!=1){j--;}
        if(i < j)
            swap(A[i],A[j]);
        else break;
    }
    cout << i;
    if(A[i] < A[R])
        swap(A[i],A[R]);
    quickSort(A,L,i-1);
    quickSort(A,i,R);
}


int main(){
    int n;
    cin >> n;
    int *A = new int[n];
    for(int i = 0;i < n;i++){
        cin >> A[i];
    }
    quickSort(A,0,n-1);
    for(int i = 0;i < n;i++)
        cout << A[i];
}