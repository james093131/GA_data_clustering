double Accuracy(vector<int> correct_category,vector<int> test_category,int ind)
{
    double r=0;
    int a=0;int b=0;int c=0;
    for(int i=0;i<ind/3;i++)
    {
        if(test_category[i]==0)
            a++;
        else if(test_category[i]==1)
            b++;
        else if(test_category[i]==2)
            c++;
    }
    if(a>b)
    {
        if(c>a)
            r+=c;
        else
        {
            r+=a;
        }
    
    }
    else if(b>=a)
    {
            if(c>b)
                r+=c;
            else 
                r+=b;
    }
     a=0; b=0; c=0;
    for(int i=ind/3;i<ind*2/3;i++)
    {
        if(test_category[i]==0)
            a++;
        else if(test_category[i]==1)
            b++;
        else if(test_category[i]==2)
            c++;
    }
    if(a>b)
    {
        if(c>a)
            r+=c;
        else
        {
            r+=a;
        }
    
    }
    else if(b>=a)
    {
            if(c>b)
                r+=c;
            else 
                r+=b;
    }
     a=0; b=0; c=0;
    for(int i=ind*2/3;i<ind;i++)
    {
        if(test_category[i]==0)
            a++;
        else if(test_category[i]==1)
            b++;
        else if(test_category[i]==2)
            c++;
    }
    if(a>b)
    {
        if(c>a)
            r+=c;
        else
        {
            r+=a;
        }
    
    }
    else if(b>=a)
    {
            if(c>b)
                r+=c;
            else 
                r+=b;
    }
    r=r/ind;
    return r;
}