#include "function.h"
void PR_Check(vector<int> &lock,vector<vector<int> > P ,vector<vector<int> > &check,vector<vector<double> > inf,vector<vector<double> > &sum,int ind,int pop,int item,int PR_ignore,int &Accumulation,vector<int>Category_Sum)
{
    if(Accumulation >  (ind*PR_coefficient) )
    {
        ;
    }
    else{
        for(int i=0;i<ind;i++){check[0][i]=0;}
        for(int i=0;i<pop;i+=2)
        {
            for(int j=0;j<ind;j++)
            {
                if(P[i][j]==P[i+1][j])
                    check[0][j]++;
            }
        }
        for(int i=0;i<ind;i++)
        {
            if(check[0][i] == (pop/2) )
            {
                check[1][i]++;
                    if(check[1][i] >= (PR_ignore/pop))//因為pop數量不同會導致不同有不同的evaluation所以除上pop在達到iter後才鎖住
                    {
                        if(lock[i]==0 )
                        {
                            Accumulation++;
                            lock[i]=P[0][i]+1;
                            Category_Sum[lock[i]-1]++;
                            int category=P[0][i];
                            for(int k=0;k<item-1;k++)
                            {
                                sum[category][k]+=inf[i][k];
                            }
                        
                        }
                        
                    
                    }
                
            }
            else{
                check[1][i]=0;
            }
        }
    }
    
}
int main(int argc, char const *argv[])
{
    
    srand((unsigned int)time(NULL));
    double START,END;
    int pop = atoi(argv[1]);
    int iteration = atoi(argv[2]);
    int run = atoi(argv[3]);
    int PR_ignore = atoi(argv[4]);//多少eva相同後忽略
    int ind;
    vector<int> convergence(iteration,0); 
    vector<string> temp;
    ind= readfile(temp);
    // cout<<ind<<endl;
    //-------讀檔結束
    int item=getinf(temp);
    // cout<<item<<endl;
    vector<vector<string> > aftsplit(ind,vector<string>(item));
    arrangereadfile(aftsplit,temp,ind,item);
    vector<string> category=make_category(aftsplit, ind, item);
    vector<vector<double> > clean_data(ind,vector<double>(item));
    make_clean_data(clean_data,aftsplit,category,ind,item);
   //--------------資料整理完成
    Run_Best SSE_RUN;
    SSE_RUN.SSE_result.resize(run);
    SSE_RUN.Best_SSE_Category.resize(ind);
    SSE_RUN.AVG_SSE=0;
    SSE_RUN.Best_SSE=100000;
    SSE_RUN.AVG_PR_Lock=0;
//---run資料初始化完成
    Iris_Data data;
    data.P.resize(pop,vector<int>(ind));
    data.inf.resize(ind,vector<double>(item-1));//花的資訊
    data.fitness.resize(pop);
    data.Best_P.resize(ind);
    vector<int> correct_category(ind);//正解
    
    for(int i=0;i<ind;i++)
    {
        correct_category[i]=clean_data[i][item-1];
    }
     vector<vector<int> > correct_2d;
     correct_2d.resize(pop);
     for(int i=0;i<pop;i++)
     {
         correct_2d[i].assign(correct_category.begin(),correct_category.end());
     }
    /////----花的資訊初始化完成
    int r=0;
    Vector_copy(clean_data,data.inf,ind ,item-1);
    double clc=0;
    START=clock();
    while(r<run)
    {
        PR PR_record;
        PR_record.index.resize(2,vector<int>(ind));//第一列儲存當個iter的pop是否一樣，第二列儲存該點已經幾輪沒變了
        PR_record.lock.resize(ind);
        PR_record.PR_Accumulation=0;
        PR_record.Sum.resize(category.size(),vector<double>(item-1));
        PR_record.Category_Sum.resize(category.size());
        //-----PR設定完成
        create(data.P,pop,category.size(),ind);//隨機產生染色體

            vector<vector<double> > sum(pop,vector<double>(category.size()*(item-1),0));
            SSE_Category_Data_Sum(data.inf, sum,PR_record.Sum,data.P,PR_record.lock,ind,pop,item,category.size(),PR_record.Category_Sum);
            SSE_Formula(data.inf,sum,correct_2d,data.fitness,pop,ind,item,PR_record.lock,PR_record.Sum,PR_record.Category_Sum,category.size());
        //SSE完成    
        Find_best(data.fitness,data.P,data.Best_P,ind,item,pop,data.best_fitness);
        
        data.P=tournament(data.fitness,data.P,pop,ind,data.Best_P);
    
        crossover(data.P,pop,ind,category.size(),PR_record.lock);
    
        //-----初始化完成
        int iter=0;
        while(iter<iteration)
        {
            double start1=clock();
            vector<vector<double> > sum(pop,vector<double>(category.size()*(item-1),0));
            SSE_Category_Data_Sum(data.inf, sum,PR_record.Sum,data.P,PR_record.lock,ind,pop,item,category.size(),PR_record.Category_Sum);
            SSE_Formula(data.inf,sum,correct_2d,data.fitness,pop,ind,item,PR_record.lock,PR_record.Sum,PR_record.Category_Sum,category.size());
                
                // cout<<data.fitness[i]<<endl;
        //SSE完成
            double end1=clock();   
            clc+=(end1 - start1) / CLOCKS_PER_SEC;
            Find_best(data.fitness,data.P,data.Best_P,ind,item,pop,data.best_fitness);
            data.P=tournament(data.fitness,data.P,pop,ind,data.Best_P);
            crossover(data.P,pop,ind,category.size(),PR_record.lock);
            cout<<"Run"<<r+1<<'_'<<"Iteration"<<iter+1<<':'<<data.best_fitness<<endl;
            // cout<<iter+1<<": "<<data.accuracy<<endl;
            convergence[iter]+=data.best_fitness;//畫收斂圖用的
            PR_Check(PR_record.lock,data.P ,PR_record.index,data.inf,PR_record.Sum,ind,pop,item,PR_ignore,PR_record.PR_Accumulation,PR_record.Category_Sum);
            iter++;
        }
        vector<vector<double> >  SSE_sum(category.size(),vector<double>(item-1,0));
        Recovery_SSE_Category_Data_Sum(data.inf, SSE_sum,data.Best_P,ind,item,category.size());
        double T=Recovery_SSE_Formula(data.inf,SSE_sum,data.Best_P,ind,item);
        cout<<"Recovery SSE : "<<T<<endl;
        SSE_RUN.SSE_result[r]=data.best_fitness;
        if(SSE_RUN.SSE_result[r]<SSE_RUN.Best_SSE)
        {
            SSE_RUN.Best_SSE=SSE_RUN.SSE_result[r];
            for(int i=0;i<ind;i++)
            {
                SSE_RUN.Best_SSE_Category[i]=data.Best_P[i];
            }
        }
        SSE_RUN.AVG_PR_Lock += PR_record.PR_Accumulation;
        r++;
    }
    END=clock();
    for(int i=0;i<run;i++)
    {
        SSE_RUN.AVG_SSE+=SSE_RUN.SSE_result[i];
    }
    SSE_RUN.AVG_SSE=SSE_RUN.AVG_SSE/run;
    SSE_RUN.AVG_PR_Lock=SSE_RUN.AVG_PR_Lock/run;
    double correct=Accuracy(correct_category,SSE_RUN.Best_SSE_Category,ind);
    finaloutput(iteration,pop,run,SSE_RUN.AVG_SSE,SSE_RUN.Best_SSE,SSE_RUN.Best_SSE_Category,SSE_RUN.AVG_PR_Lock,correct,START,END,clc);
    
    fstream file1;
    file1.open("GA_Clustering_Convergence.txt",ios::out);
   for(int i=0;i<iteration;i++)
   {
       convergence[i]=convergence[i]/run;
       file1<<(i+1)*pop<<' '<<convergence[i]<<endl;
   }
   
}