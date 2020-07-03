#include<stdio.h>
    double length;
    double tl,tr;
    double den,c,k;
    double s;
    double dt;
    int n;//分成几段空间

    double dx;
    //从0-10:一共有n个控制体，3n+2个索引。
    double T0[11],T[11];
    double ae0[11],aw0[11],ap0[11],ap1[11],b[11];
int main()
{

    FILE *outputT;

    int i;

    length=3;
    tl=3;tr=5;den=100;c=1000;k=10;
    s=10;

    //dt =100;
    //当dx越来越小，dt要符合CFL条件或者说ap要符合物理意义！
    dt=50;
    n=3;

//****************************************以上是单个时间步长*********************

    int tstep;
    int maxtstep;
    maxtstep=1000;


//系数只在1-3索引有用！
    dx=length/n;
    for(i=2;i<n;i++)
    {
        ae0[i]=k/dx;aw0[i]=k/dx;
        ap0[i]=den*c*dx/dt-ae0[i]-aw0[i];
        ap1[i]=ap0[i]+ae0[i]+aw0[i];
        b[i]=s*dx;
    }
    i=1;
        ae0[i]=k/dx;aw0[i]=k/(dx/2);
        ap0[i]=den*c*dx/dt-ae0[i]-aw0[i];
        ap1[i]=ap0[i]+ae0[i]+aw0[i];
        b[i]=s*dx;
    i=n;
        ae0[i]=k/(dx/2);aw0[i]=k/dx;
        ap0[i]=den*c*dx/dt-ae0[i]-aw0[i];
        ap1[i]=ap0[i]+ae0[i]+aw0[i];
        b[i]=s*dx;
//BC和IC
    for(i=1;i<=n;i++)
    {
        T0[i]=3;
    }
    T0[0]=tl;T0[n+1]=tr;

    //时间迭代；

    outputT=fopen("D:\code_blocks\project\t100.txt","w");
    for(tstep=1;tstep<=maxtstep;tstep++)
    {
        fprintf(outputT,"%i  ",tstep);

        for(i=1;i<=n;i++)
        {
            T[i]=(ae0[i]*T0[i+1]+aw0[i]*T0[i-1]+ap0[i]*T0[i]+b[i])/ap1[i];//正确，因为i=1时候，e对应着T2
            fprintf(outputT,"%e  ",T[i]);
        }
        fprintf(outputT,"\n");
        for(i=1;i<=n;i++)
        {
            T0[i]=T[i];
        }

    }


    fclose(outputT);
    return 0;
}
