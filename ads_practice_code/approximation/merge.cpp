#include<iostream>

void MSort(int A[],int TmpArr[],int Left, int Right){

    int center;
    if(Left < Right){
        center = (Left + Right)/2;
        MSort(A,TmpArr,Left,center);
        MSort(A,TmpArr,center+1,Right);
        Merge(A,TmpArr,Left,center,Right);
    }

}
void MergeSort(int A[],int N){
    int* TmpArr = new int[N];
    MSort(A,TmpArr,0,N-1);
    delete[] TmpArr;
}
void Merge(int A[],int TmpArr[],int Left, int center, int Right){
    int Lptr = Left,Lend = center;
    int Rptr = center+1,Rend = Right;
    int j = Left;
    while(Lptr <= Lend && Rptr <= Rend){
        if(A[Lptr] < A[Rptr])
            TmpArr[j++] = A[Lptr++];
        else TmpArr[j++] = A[Rptr++];
    }
    while(Lptr <= Lend)
        TmpArr[j++] = A[Lptr++];
    while(Rptr <= Rend)
        TmpArr[j++] = A[Rptr++];
    // Copy back
    for(int i = Left;i <= Right;i++){
        A[i] = TmpArr[i];
    }

}
int main(){
    
}