#include "function.h"
void create(vector<vector<int> > &P,int pop,int category,int ind)//隨機起始種類
{
    for(int i=0;i<pop;i++)
    {
        for(int j=0;j<ind;j++)
        {
            int a=rand()%category;
            P[i][j]=a;
        }
        
    }
}
void Vector_copy(vector<vector<double> > clean_data,vector<vector<double> > &inf,int ind ,int item)
{
    for(int i=0;i<ind;i++)
    {
        for(int j=0;j<item;j++)
        {
            inf[i][j]=clean_data[i][j];
        }
    }
}
void SSE_Category_Data_Sum(vector<vector<double> > inf,vector<vector<double> > &sum,vector<vector<double> > PR_sum,vector<vector<int> > P,vector<int> lock,int ind,int pop,int item,int category,vector<int> Category_Sum)
{
    vector<vector<int> > k;
    k.resize(pop);
    for(int z=0;z<pop;z++) {k[z].resize(category);}
    for(int i=0;i<ind;i++)
    {
        if(lock[i]==0)
        {
            for(int j=0;j<pop;j++)
            {
                k[j][P[j][i]]++;//k為pop個category長度的陣列,P為pop個長度為ind的陣列
                for(int y=0;y<item-1;y++)
                {
                    int clc=(item-1)*P[j][i];
                    sum[j][clc+y] += inf[i][y];
                }

            }
        }
    }
    for(int y=0;y<pop;y++)
    {
        for(int i=0;i<category;i++)
        {
            for(int j=0;j<item-1;j++)
            {
                int clc=(item-1)*i;
                if(Category_Sum[i]!=0)
                {
                    sum[y][clc+j]+=PR_sum[i][j]/Category_Sum[i];
                    sum[i][j]=sum[i][j]/(k[y][i]+1);
                }
                else{
                    sum[y][clc+j]=sum[y][clc+j]/k[y][i];
                }
                    
            }
        }
    }
}
void SSE_Formula(vector<vector<double> > inf,vector<vector<double> > sum,vector<vector<int> > P,vector<double>&fit,int pop,int ind,int item,vector<int> lock,vector<vector<double> > PR_sum,vector<int> Category_Sum,int category)
{
    
    for(int y=0;y<pop;y++)
    {
        fit[y]=0;
        for(int j=0;j<ind;j++)
        {
            if(lock[j]==0)
            {
                for(int k=0;k<item-1;k++)
                {
                    int clc=(item-1)*P[y][j];
                    fit[y]+=pow(inf[j][k]-sum[y][clc+k],2);//sum logic
                }
            }
        
        }
        for(int i=0;i<category;i++)
            for(int j=0;j<item-1;j++)
            {
                if(Category_Sum[i]!=0)
                    fit[y] += pow( (PR_sum[i][j]/Category_Sum[i])-sum[y][i*j+j],2);
            }
    }
    
}
vector<vector<int> >  tournament(vector<double> fit,vector<vector<int> > P,int pop,int ind,vector<int> Best_P)
{
    vector <int> choose(pop);
    vector<vector<int> > temp;
    temp.resize(pop);
    for(int k=0;k<pop;k++) temp[k].resize(ind);
    int i=0;
    for(int k=0;k<ind;k++)
        {
            temp[i][k] = Best_P[k];
        }
    i++;
    while(i<pop){
        int c1=rand()%(pop);
        int c2=rand()%(pop);
        int chc;
        if(fit[c1]>fit[c2]){
            chc=c2;
        }
        else{
             chc=c1;
        }
        for(int k=0;k<ind;k++)
        {
            temp[i][k] = P[chc][k];
        }
        
        i++;
    }
    return temp;
}
void mutation(vector<int>&P,int ind,int category,vector<int>lock)//隨機選取一點做調換
{
    int c=rand()%ind;
    if(lock[c]==0)
    {
        int a=rand()%category;
        P[c]=a;
    }
   
    
    
}
void crossover(vector<vector<int> > &P,int pop,int ind,int category,vector<int> lock)
{
    int i=0;
    while(i<pop){
        int c1=rand()%ind;
        int c2=rand()%ind;
        int c3=rand()%ind;
        int c4=rand()%ind;
        int c5=rand()%ind;
        int c6=rand()%ind;
        while(c2>c1)
        {
            c2=rand()%ind;
        }
        float t1 = (float) rand() / (RAND_MAX + 1.0);
        for(int k=0;k<ind;k++)
        {
            if(t1<CR){
                if(lock[k]!=0)
                {
                    P[i][k]=P[i][k];
                    P[i+1][k]=P[i+1][k];
                }
                else if(k>c1||k<c2||k==c3||k==c4||k==c5||k==c6)
                {
                    int temp=P[i][k];
                    P[i][k]=P[i+1][k];
                    P[i+1][k]=temp;
                } 
                else{
                    
                    P[i][k]=P[i][k];
                    P[i+1][k]=P[i+1][k];
                }
            }
           
        }
        float x = (float) rand() / (RAND_MAX + 1.0);
        float y = (float) rand() / (RAND_MAX + 1.0);
        if(x<MR)
        {
            mutation(P[i],ind,category,lock);
        }
        if(y<MR)
        {
             mutation(P[i+1],ind,category,lock);
        }
         i+=2;
    }
}
void Find_best(vector<double> fit,vector<vector<int> > P,vector<int> &Best_P,int ind,int item,int pop,double &best_fit)
{
    double best=100000;
    int best_index;
    for(int i=0;i<pop;i++)
    {
        if(best > fit[i])
        {
            best=fit[i];
            best_index=i;
        }
    }
    best_fit=best;
    for(int i=0;i<ind;i++)
    {
        Best_P[i]=P[best_index][i];
    }
}
double Accuracy(vector<int> correct_category,vector<int> test_category,int ind)
{
    double r=0;
    int a=0;int b=0;int c=0;
    for(int i=0;i<ind;i++)
    {
        if(test_category[i]==correct_category[i])
            r++;
    }
    r=r/ind;
    return r;
}
void Recovery_SSE_Category_Data_Sum(vector<vector<double> > inf,vector<vector<double> > &sum,vector<int> P,int ind,int item,int category)
{
   vector<int> k(category);
    for(int i=0;i<ind;i++)
    {
        k[P[i]]++;
    }
    for(int i=0;i<ind;i++)
    {
        for(int j=0;j<item-1;j++)
        {
            sum[P[i]][j] += inf[i][j];
        }
    }
    for(int i=0;i<category;i++)
    {
        for(int j=0;j<item-1;j++)
        {
            sum[i][j] = sum[i][j]/k[i];
        }
    }
}
double Recovery_SSE_Formula(vector<vector<double> > inf,vector<vector<double> > sum,vector<int> P,int ind,int item)
{
    double temp=0;
    for(int j=0;j<ind;j++)
    {
        for(int k=0;k<item-1;k++)
        {
            temp += pow(inf[j][k]-sum[P[j]][k],2);
        }
    }
    return temp;
}
void finaloutput(int iteration,int pop,int run,int avgbestvalue,int best,vector<int>result,int AVG_PR_Lock,double correct,double START,double END,double clc)
{
    fstream file;//寫檔
	file.open("GA_Clustering.txt",ios::app);
    cout<<endl;
    cout<<"Run : "<<run<<endl;
    cout<<"Population : "<<pop<<endl;
    cout<<"Iteration: "<<iteration<<endl;
    cout<<"AVG_SSE : "<<avgbestvalue<<endl;
    cout<<"AVG_PR_LOCK : "<<AVG_PR_Lock<<endl;
    cout<<"Execution Time :"<<(END - START) / CLOCKS_PER_SEC<<"(s)"<<endl;
    cout<<"SSE Execution Time : "<<clc<<endl;
    cout<<"Best_SSE : "<<best<<endl;
    cout<<"Accuracy : "<<correct*100<<'%'<<endl;
   
    file<<"Run : "<<run<<endl;
    file<<"Population : "<<pop<<endl;
    file<<"Iteration: "<<iteration<<endl;
    file<<"AVG_SSE : "<<avgbestvalue<<endl;
    file<<"AVG_PR_LOCK : "<<AVG_PR_Lock<<endl;
    file<<"SSE Execution Time : "<<clc<<"(s)"<<endl;
    file<<"Execution Time :"<<(END - START) / CLOCKS_PER_SEC<<"(s)"<<endl;
    
    file<<"Best_SSE : "<<best<<endl;
    file<<"Accuracy : "<<correct*100<<'%'<<endl;
    file<<"Category_Result : "<<endl; 
    file<<endl;

    for(int i=0;i<result.size();i++)
    {
        cout<<result[i]<<' ';
        file<<result[i]<<' ';
        if(i==49||i==99)
        {
            cout<<endl;
            file<<endl;
        }
            
    }
    file.close();
}
