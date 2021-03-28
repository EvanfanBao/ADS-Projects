#include <stdio.h>

#define MAXN 10
#define MAXS 1000

int need_time(const int time[], const int score[], int happy_score, int n);

int main() {
  int n, i, happy_score;
  int time[MAXN], score[MAXN];
  scanf("%d %d", &n, &happy_score);
  for (i = 0; i < n; ++i)
      scanf("%d", &time[i]);
  for (i = 0; i < n; ++i)
      scanf("%d", &score[i]);
  printf("%d\n", need_time(time, score, happy_score, n));
  return 0;
}


//所有题目都做完，如果都没达到happy score。那肯定不可能达到
//如果能达到happy score。那其实达到了就不会再做更多的题目了，这样时间会更长
//达到happy score后不会再去做题。那么我们只要把总分
//减去happy score。就是不做的那些题目的分数。
//不做的也就是不做的题目的分数和达到了那个值，
//再加上时间限制。也就是不做的题目，在最多的时间下。
//总的分数 小于等于 全部题目的分数减去happy_score
//于是，剩下的题目，分数一定大于等于happy score，且时间最少
int min(int a,int b){
    return a < b ? a : b;
}
int max(int a, int b){
    return a > b ? a : b;
}
int sum(const int arr[],int n){
    int sum = 0;
    for(int i = 0; i < n;i++)
        sum += arr[i];
    return sum;
}
int need_time(const int time[], const int score[], int happy_score, int n){
    int sum_score = 0, sum_time = 0; //记录完成所有题目的分数 时间---显然如果总的分数都比
    int min_score = 1000,capacity;               //happyscore 小的话，怎么都不可能成功
    sum_score = sum(score,n);
    sum_time = sum(time,n);
    capacity = sum_score - happy_score;
    int pack[capacity+1][n+1]; //背包容量是总分-happy分。最多n个题目都不做  总的value
    for(int i = 0;i < n; i++)               //最低的分数
        min_score = min(score[i],min_score);
    if(sum_score < happy_score)
        return -1;              //总分无法达到happy score-显然不行
    //printf("%d\t",sum_score);
    //初始化数组---初始i=0 一定为0，没有东西。 j=0 也一定为0，无法塞东西
    // for(int i = 0 ; i <= capacity;i++ )
    //     for(int j = 0; j <= n; j++)
    //         pack[i][j] = 0;

    for(int i = 0; i <= n; i++ )  //容量为0
        pack[0][i] = 0;
    for(int i = 0; i <= capacity;i++)       //0题
        pack[i][0] = 0; 

    for(int i = min_score;i <= capacity;i++)
    {//背包容量--从小到最大 dp算法
        for(int j = 1;j <= n;j++)
        {
                if(i >= score[j-1])
                pack[i][j] = max(pack[i][j-1],pack[i-score[j-1]][j-1]+time[j-1]);
                else pack[i][j] = pack[i][j-1];
        }
    }
    if(sum_time == pack[capacity][n])
        return -1;
    else 
        return sum_time - pack[capacity][n];

}



