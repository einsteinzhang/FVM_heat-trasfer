
#include<stdio.h>



//公共变量区
    double length;
    double tl,tr;
    double den,c,k;
    double s;
    double dt;
    int n;//分成几段空间

    double dx;
    //从0-10:一共有n个控制体，3n+2个索引。
    double T0[302],T[302];
    double ae1[302],aw1[302],ap0[302],ap1[302],b[302];
    int maxtstep;


    double a[303],b0[303],c0[303],d[303],x[303],p[303],q[303];

    //以下就是子程序tdma
void tdma()
    {
        int i;
        i=1;
        p[i]=-c0[i]/a[i];
        q[i]=d[i]/a[i];
        for(i=2;i<n;i++)
        {
            p[i]=-c0[i]/(a[i]+b0[i]*p[i-1]);
            q[i]=(d[i]-b0[i]*q[i-1])/(a[i]+b0[i]*p[i-1]);
        }
        i=n;
        x[n]=(d[i]-b0[i]*q[i-1])/(a[i]+b0[i]*p[i-1]);
        //回代过程：
        for(i=n-1;i>=1;i--)
        {
            x[i]=p[i]*x[i+1]+q[i];
        }
    }
int main()
{

    FILE *outputT;
    int i;
    int tstep;

    length=3;
    tl=3;tr=5;den=100;c=1000;k=10;
    s=10;
    dt=10;
    n=101;

//****************************************以上是单个时间步长*********************


    maxtstep=3000;

/*

这部分是显示需要用到。

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
        */



     dx=length/n;
    for(i=2;i<n;i++)
    {
        ae1[i]=k/dx;aw1[i]=k/dx;
        ap0[i]=den*c*dx/dt;
        ap1[i]=ap0[i]+ae1[i]+aw1[i];//显示隐士一样
        b[i]=s*dx;
    }
    i=1;
        ae1[i]=k/dx;aw1[i]=k/(dx/2);
        ap0[i]=den*c*dx/dt;
        ap1[i]=ap0[i]+ae1[i]+aw1[i];
        b[i]=s*dx;
    i=n;
        ae1[i]=k/(dx/2);aw1[i]=k/dx;
        ap0[i]=den*c*dx/dt;
        ap1[i]=ap0[i]+ae1[i]+aw1[i];
        b[i]=s*dx;
//BC和IC
    for(i=1;i<=n;i++)
    {
        T0[i]=3;
    }
    T[0]=tl;T[n+1]=tr;

    //时间迭代；

    outputT=fopen("D:\code_blocks\project\T312.txt","w");
    for(tstep=1;tstep<=maxtstep;tstep++)
    {
        fprintf(outputT,"%i  ",tstep);
        //printf("%i  ",tstep);

        /*显示：
        for(i=1;i<=n;i++)
        {
            T[i]=(ae0[i]*T0[i+1]+aw0[i]*T0[i-1]+ap0[i]*T0[i]+b[i])/ap1[i];//正确，因为i=1时候，e对应着T2
            fprintf(outputT,"%e  ",T[i]);
            //printf("%e  ",T[i]);
        }
        */

        tdma();
        for(i=1;i<=n;i++)
        {
            T[i]=x[i];
            fprintf(outputT,"%e  ",T[i]);
        }

        fprintf(outputT,"\n");
        //printf("\n");

        for(i=1;i<=n;i++)
        {
            T0[i]=T[i];
        }

    }


    fclose(outputT);
    return 0;
}
