#include "read.h"
void create(vector<vector<int> > &P,int pop,int category,int ind);//隨機起始種類
void Vector_copy(vector<vector<double> > clean_data,vector<vector<double> > &inf,int ind ,int item);
void SSE_Category_Data_Sum(vector<vector<double> > inf,vector<vector<double> > &sum,vector<int> P,int ind,int item,int category);
void SSE_Formula(vector<vector<double> > inf,vector<vector<double> > sum,vector<int> P,vector<double>&fit,int i,int ind,int item);
vector<vector<int> >  tournament(vector<double> fit,vector<vector<int> > P,int pop,int ind,vector<int> Best_P);
void mutation(vector<int>P,int ind,int category);//隨機選取一點做調換
void crossover(vector<vector<int> > &P,int pop,int ind,int category);
void Find_best(vector<double> fit,vector<vector<int> > P,vector<int> &Best_P,int ind,int item,int pop,double &best_fit);
void finaloutput(int iteration,int pop,int run,int avgbestvalue,int best,vector<int>result,double START,double END);