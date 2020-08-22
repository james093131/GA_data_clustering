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
#define MR 0.15
#define PR_coeffient 0.8
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
    vector<int> SSE_result;
    vector<int> Best_SSE_Category;
    int AVG_SSE;
    int Best_SSE;
};
class PR{
public:
    vector<vector<int> > index;
    vector<int> lock;
    int PR_Accumulation;
    vector<vector<double> > Sum;
    vector<int> Category_Sum;

};

int  readfile(vector<string> &s);//讀檔 以讀一行一行的方式來讀取
int getinf(vector<string> s);//用,分割看有幾項
void arrangereadfile(vector<vector<string> > &aftsplit ,vector<string> temp,int ind,int item);//資料整理成 2D-vector型式
vector<string>  make_category(vector<vector<string> > &aftsplit,int ind,int item);//將種類進行分類儲存到vector中
void make_clean_data(vector<vector<double> > &clean,vector<vector<string> > aftsplit,vector<string> category,int ind,int item);//將所有資料以double方式儲存
