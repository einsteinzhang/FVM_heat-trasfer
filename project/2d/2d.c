
#include<stdio.h>
    double length,height;
    double tl,tr,tb,tu;
    double den,cv,k;
    double s;
    double dt;
    int n;//分成x几段空间
    int m;//分成y几段空间
    double dx,dy;
    //从0-10:一共有n个控制体，3n+2个索引。
    double T0[303][303],T[303][303];
    double ae0[303][303],aw0[303][303],ap0[303][303],ap1[303][303],bp[303][303],an0[303][303],as0[303][303];
int main()
{

    FILE *outputT;

    int i,j;

    length=3;height=2;
    tl=3;tr=5;
    tb=2;tu=4;
    den=100;cv=1000;k=10;
    s=10;

    //dt =100;
    //当dx越来越小，dt要符合CFL条件或者说ap要符合物理意义！
    dt=100;
    n=5;m=5;

//****************************************以上是单个时间步长*********************

    int tstep;
    int maxtstep;
    maxtstep=1000;


//系数只在1-3索引有用！
    dx=length/n;
    dy=height/m;

    for(i=2;i<n;i++)
    {
        for(j=2;j<m;j++)
        {
        ae0[i][j]=k*dy/dx;aw0[i][j]=k*dy/dx;
        an0[i][j]=k*dx/dy;as0[i][j]=k*dx/dy;
        ap0[i][j]=den*cv*dx*dy/dt-ae0[i][j]-aw0[i][j]-an0[i][j]-as0[i][j];
        ap1[i][j]=ap0[i][j]+ae0[i][j]+aw0[i][j]+an0[i][j]+as0[i][j];
        bp[i][j]=s*dx*dy;
        }
    }


    for(j=2;j<m;j++)
    {
            i=1;
        ae0[i][j]=k*dy/dx;aw0[i][j]=k*dy/(dx/2);
        an0[i][j]=k*dx/dy;as0[i][j]=k*dx/dy;
        ap0[i][j]=den*cv*dx*dy/dt-ae0[i][j]-aw0[i][j]-an0[i][j]-as0[i][j];
        ap1[i][j]=ap0[i][j]+ae0[i][j]+aw0[i][j]+an0[i][j]+as0[i][j];
        bp[i][j]=s*dx*dy;
    }


    for(j=2;j<m;j++)
    {
            i=n;
        ae0[i][j]=k*dy/(dx/2);aw0[i][j]=k*dy/dx;
        an0[i][j]=k*dx/dy;as0[i][j]=k*dx/dy;
        ap0[i][j]=den*cv*dx*dy/dt-ae0[i][j]-aw0[i][j]-an0[i][j]-as0[i][j];
        ap1[i][j]=ap0[i][j]+ae0[i][j]+aw0[i][j]+an0[i][j]+as0[i][j];
        bp[i][j]=s*dx*dy;
    }

    for(i=2;i<n;i++)
    {
            j=1;
        ae0[i][j]=k*dy/dx;aw0[i][j]=k*dy/dx;
        an0[i][j]=k*dx/dy;as0[i][j]=k*dx/(dy/2);
        ap0[i][j]=den*cv*dx*dy/dt-ae0[i][j]-aw0[i][j]-an0[i][j]-as0[i][j];
        ap1[i][j]=ap0[i][j]+ae0[i][j]+aw0[i][j]+an0[i][j]+as0[i][j];
        bp[i][j]=s*dx*dy;
    }


    for(i=2;i<n;i++)
    {
            j=m;
        ae0[i][j]=k*dy/dx;aw0[i][j]=k*dy/dx;
        an0[i][j]=k*dx/(dy/2);as0[i][j]=k*dx/dy;
        ap0[i][j]=den*cv*dx*dy/dt-ae0[i][j]-aw0[i][j]-an0[i][j]-as0[i][j];
        ap1[i][j]=ap0[i][j]+ae0[i][j]+aw0[i][j]+an0[i][j]+as0[i][j];
        bp[i][j]=s*dx*dy;
    }
    //四个角
    i=1;j=1;
        ae0[i][j]=k*dy/dx;aw0[i][j]=k*dy/(dx/2);
        an0[i][j]=k*dx/dy;as0[i][j]=k*dx/(dy/2);
        ap0[i][j]=den*cv*dx*dy/dt-ae0[i][j]-aw0[i][j]-an0[i][j]-as0[i][j];
        ap1[i][j]=ap0[i][j]+ae0[i][j]+aw0[i][j]+an0[i][j]+as0[i][j];
        bp[i][j]=s*dx*dy;

    i=1;j=m;
        ae0[i][j]=k*dy/dx;aw0[i][j]=k*dy/(dx/2);
        an0[i][j]=k*dx/(dy/2);as0[i][j]=k*dx/dy;
        ap0[i][j]=den*cv*dx*dy/dt-ae0[i][j]-aw0[i][j]-an0[i][j]-as0[i][j];
        ap1[i][j]=ap0[i][j]+ae0[i][j]+aw0[i][j]+an0[i][j]+as0[i][j];
        bp[i][j]=s*dx*dy;
    i=n;j=1;
        ae0[i][j]=k*dy/(dx/2);aw0[i][j]=k*dy/dx;
        an0[i][j]=k*dx/dy;as0[i][j]=k*dx/(dy/2);
        ap0[i][j]=den*cv*dx*dy/dt-ae0[i][j]-aw0[i][j]-an0[i][j]-as0[i][j];
        ap1[i][j]=ap0[i][j]+ae0[i][j]+aw0[i][j]+an0[i][j]+as0[i][j];
        bp[i][j]=s*dx*dy;
    i=n;j=m;
        ae0[i][j]=k*dy/(dx/2);aw0[i][j]=k*dy/dx;
        an0[i][j]=k*dx/(dy/2);as0[i][j]=k*dx/dy;
        ap0[i][j]=den*cv*dx*dy/dt-ae0[i][j]-aw0[i][j]-an0[i][j]-as0[i][j];
        ap1[i][j]=ap0[i][j]+ae0[i][j]+aw0[i][j]+an0[i][j]+as0[i][j];
        bp[i][j]=s*dx*dy;


//BC和IC
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            T0[i][j]=3;
        }
    }

    i=0;
    for(j=1;j<=m;j++)
    {
            T0[i][j]=tl;
    }

    i=n+1;
    for(j=1;j<=m;j++)
    {
        T0[i][j]=tr;
    }
    j=0;
    for(i=1;i<=n;i++)
    {
           T0[i][j]=tb;
    }

    j=m+1;
    for(i=1;i<=n;i++)
    {
        T0[i][j]=tu;
    }

    //时间迭代；

    outputT=fopen("D:\code_blocks\project\分.txt","w");
    fprintf(outputT,"a, time, T11, T12, T13, T14, T15, T21, T22, T23, T24, T25, T31, T32, T33, T34, T35, T41, T42, T43, T44, T45, T51, T52, T53, T54, T55\n");
    for(tstep=1;tstep<=maxtstep;tstep++)
    {
        fprintf(outputT,"%i, %e  ",tstep,tstep*dt);

        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
            {
                T[i][j]=(ae0[i][j]*T0[i+1][j]+aw0[i][j]*T0[i-1][j]+an0[i][j]*T0[i][j+1]+as0[i][j]*T0[i][j-1]+ap0[i][j]*T0[i][j]+bp[i][j])/ap1[i][j];//正确，因为i=1时候，e对应着T2
                fprintf(outputT,"%e  ",T[i][j]);
            }
        }

        fprintf(outputT,"\n");
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
            {
                T0[i][j]=T[i][j];
            }
        }


    }


    fclose(outputT);
    return 0;
}
