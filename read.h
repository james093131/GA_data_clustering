#include <stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include <string.h>
#include<time.h>
#include<math.h>
#include<vector>
#define CR 0.95
#define MR 0.05
#define PR_coefficient 0.8
using namespace std;
class Iris_Data { 
public: 
	vector<vector<int> > P ;//分類
    vector<int> Best_P;
    vector<vector<double> > inf;//花的資料
    vector<double> fitness;//ＳＳＥ計算出來的適應度
    double best_fitness;
    double accuracy;
};
class Run_Best{
public:
    vector<int> SSE_result;//陣列儲存每一ＲＵＮSSE的結果
    vector<int> Best_SSE_Category;//在全部Run中最好的那個的分類結果
    int AVG_PR_Lock;//ＰＲ鎖住幾個點
    double AVG_Accuracy;
    int AVG_SSE;//平均的ＳＳＥ
    int Best_SSE;//最佳解的ＳＳＥ
};
class Iter_Best{
    public:
        vector<int> Global_Best_P;//全部iteration下最優解的分類狀況
        double Global_Best_fitness;//全部Iteration下最佳的ＳＳＥ
        double Global_best_accuracy;//全部解中最佳的ＳＳＥ的準確度
};
class PR{
public:
    vector<vector<int> > index;//第一列儲存當個iter的pop是否一樣，第二列儲存該點已經幾輪沒變了
    vector<int> lock;//長度為ind，儲存被鎖住的位置
    int PR_Accumulation;//儲存ＰＲ總共鎖住幾個點
    vector<vector<double> > Sum;//長度category*item-1的2d vector把鎖住的點加總起來
    vector<int> Category_Sum;//長度為category的vector儲存哪一群有幾個鎖住的點

};
int  readfile(vector<string> &s);//讀檔 以讀一行一行的方式來讀取
int getinf(vector<string> s);//用,分割看有幾項
void arrangereadfile(vector<vector<string> > &aftsplit ,vector<string> temp,int ind,int item);//資料整理成 2D-vector型式
vector<string>  make_category(vector<vector<string> > &aftsplit,int ind,int item);//將種類進行分類儲存到vector中
void make_clean_data(vector<vector<double> > &clean,vector<vector<string> > aftsplit,vector<string> category,int ind,int item);//將所有資料以double方式儲存
