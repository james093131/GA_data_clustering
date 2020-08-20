#include "function.h"
int main(int argc, char const *argv[])
{
    
    srand((unsigned int)time(NULL));
    double START,END;
    int pop = atoi(argv[1]);
    int iteration = atoi(argv[2]);
    int run = atoi(argv[3]);
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
    /////----花的資訊初始化完成
    int r=0;
    Vector_copy(clean_data,data.inf,ind ,item-1);
    START=clock();
    while(r<run)
    {
        create(data.P,pop,category.size(),ind);//隨機產生染色體
        for(int i=0;i<pop;i++)
        {
            vector<vector<double> >  sum(category.size(),vector<double>(item-1,0));
            SSE_Category_Data_Sum(data.inf, sum,data.P[i],ind,item,category.size());
            SSE_Formula(data.inf,sum,correct_category,data.fitness,i,ind,item);
        }//SSE完成    
        Find_best(data.fitness,data.P,data.Best_P,ind,item,pop,data.best_fitness);
        
        data.P=tournament(data.fitness,data.P,pop,ind,data.Best_P);
    
        crossover(data.P,pop,ind,category.size());
    
        //-----初始化完成
        int iter=0;
        while(iter<iteration)
        {
            for(int i=0;i<pop;i++)//SSE計算
            {
                vector<vector<double> > sum(category.size(),vector<double>(item-1,0));
                SSE_Category_Data_Sum(data.inf, sum,data.P[i],ind,item,category.size());
                SSE_Formula(data.inf,sum,data.P[i],data.fitness,i,ind,item);
                // cout<<data.fitness[i]<<endl;
            }//SSE完成
            Find_best(data.fitness,data.P,data.Best_P,ind,item,pop,data.best_fitness);
            data.P=tournament(data.fitness,data.P,pop,ind,data.Best_P);
            crossover(data.P,pop,ind,category.size());
            cout<<"Run"<<r+1<<'_'<<"Iteration"<<iter+1<<':'<<data.best_fitness<<endl;
            // cout<<iter+1<<": "<<data.accuracy<<endl;
            convergence[iter]+=data.best_fitness;
            iter++;
        }
        
        SSE_RUN.SSE_result[r]=data.best_fitness;
        if(SSE_RUN.SSE_result[r]<SSE_RUN.Best_SSE)
        {
            SSE_RUN.Best_SSE=SSE_RUN.SSE_result[r];
            for(int i=0;i<ind;i++)
            {
                SSE_RUN.Best_SSE_Category[i]=data.Best_P[i];
            }
        }
        r++;
    }
    END=clock();
    for(int i=0;i<run;i++)
    {
        SSE_RUN.AVG_SSE+=SSE_RUN.SSE_result[i];
    }
    SSE_RUN.AVG_SSE=SSE_RUN.AVG_SSE/run;
    double correct=Accuracy(correct_category,SSE_RUN.Best_SSE_Category,ind);
    finaloutput(iteration,pop,run,SSE_RUN.AVG_SSE,SSE_RUN.Best_SSE,SSE_RUN.Best_SSE_Category,correct,START,END);
    
    fstream file1;
    file1.open("GA_Clustering_Convergence.txt",ios::out);
   for(int i=0;i<iteration;i++)
   {
       convergence[i]=convergence[i]/run;
       file1<<(i+1)*pop<<' '<<convergence[i]<<endl;
   }
}