#include<iostream>
#include<vector>
#include<algorithm>


using namespace std;
#define INFINITY 1000000;

//目标 -- 选择中心 -- 最小化 最小覆盖半径(以所有中心结点圆心，该半径画圆 能覆盖所有的点--半径更大当然更能覆盖)
//greedy1---用r*的上界找--其实我还不太懂的

// 也可以用graph---直接给出不同点之间的距离
// 因为我们最终近似选择的点一定是已知的site--所以没问题
// 但如果是求最优解--显然不行--当然最优解几乎无法求出来--因为平面空间是无限的
// 现在用point表示离远点的x y坐标--原点本身不重要---重要的是距离
struct point{
    double x;
    double y;
};

typedef vector<point> Centers;
typedef Centers Sites;


double dist(point p1,point p2){
    return (p1.x-p2.x) * (p1.x-p2.x) + p1.y-p2.y * (p1.x-p2.x);     //返回距离的平方
}

double dist(point p1,Centers C){
    Centers :: iterator it;
    double mind = INFINITY;
    for(it = C.begin();it != C.end();it++){
        if(dist(p1,*it) < mind)mind = dist(p1,*it);
    }
    return mind;
}
// shuffle 的方法从 一个数组中随机的取n个数---每一次都shuffle一次，然后比较
// shuffle的方式就是生成数组的随机全排列
// 由于阶乘比较大 所以重复概率几乎是0

random_device rd;
mt19937 gr(rd());
Centers Greedy_2r(const Sites& sites,int K,double r){
    Sites New_sites = sites;    //应该是有一个默认copy构造函数 --- remaining sites
    Centers C;  // 中心集
    point temp;
    
    Sites:: iterator ite;
    while(New_sites.size() != 0){
        shuffle(New_sites.begin(),New_sites.end(),gr);
        temp = New_sites[0];
        C.push_back(temp);
        for(ite = New_sites.begin();ite != New_sites.end();){
            if(dist(*ite,temp) <= 4*r*r ){
                ite = New_sites.erase(ite);
            }
            else ++ite;
        }
    }
    if(C.size() <= K)return C;
    // else error
    else return C;
}



// 不用猜半径的方法 -- 还没有完全理解---发现c++转伪代码太舒服了
Centers Greedy_Kcenter(const Sites& sites,int K){
    Centers C;
    point temp;
    Sites New_sites = sites;
    Sites:: iterator ite;
    Sites:: iterator maxit;
    double maxd;
    shuffle(New_sites.begin(),New_sites.end(),gr);
    temp = New_sites[0];
    while(C.size() < K){
        maxd = 0;maxit = New_sites.begin();
        for(ite = New_sites.begin();ite != New_sites.end();ite++){
            if(dist(*ite,C) > maxd){
                maxd = dist(*ite,C);
                maxit = ite;
            }
        }
        C.push_back(*maxit);
    }
    return C;
}

int main(){
    Sites sites;
    int n;
    int K;
    cin >> n >> K;
    
    point tp;
    for(int i=0; i < n;i++){
        cin >> tp.x >> tp.y;
        sites.push_back(tp);  
    }

}