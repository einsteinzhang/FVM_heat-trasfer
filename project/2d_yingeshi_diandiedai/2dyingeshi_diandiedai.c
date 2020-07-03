
#include<stdio.h>
#include<math.h>
    double length,height;
    double tl,tr,tb,tu;
    double den,cv,k;
    double s;
    double dt;
    int n;//�ֳ�x���οռ�
    int m;//�ֳ�y���οռ�
    double dx,dy;
    //��0-10:һ����n�������壬3n+2��������
    double T0[303][303],T[303][303],Tn0[303][303];
    double ae1[303][303],aw1[303][303],ap0[303][303],ap1[303][303],bp[303][303],an1[303][303],as1[303][303];
    double resi[303][303];//�вÿ�����ƶ���һ����
    double resimax;//���в
int main()
{

    FILE *outputT;

    int i,j;
    int iter;

    length=3;height=2;
    tl=3;tr=5;
    tb=2;tu=4;
    den=100;cv=1000;k=10;
    s=10;

    //dt =100;
    //��dxԽ��ԽС��dtҪ����CFL��������˵apҪ�����������壡
    dt=100;
    n=5;m=5;

//****************************************�����ǵ���ʱ�䲽��*********************
    int reali;
    int tstep;
    int maxtstep;
    maxtstep=2000;


//ϵ��ֻ��1-3�������ã�
    dx=length/n;
    dy=height/m;

    for(i=2;i<n;i++)
    {
        for(j=2;j<m;j++)
        {
        ae1[i][j]=k*dy/dx;aw1[i][j]=k*dy/dx;
        an1[i][j]=k*dx/dy;as1[i][j]=k*dx/dy;
        ap0[i][j]=den*cv*dx*dy/dt;
        ap1[i][j]=ap0[i][j]+ae1[i][j]+aw1[i][j]+an1[i][j]+as1[i][j];
        bp[i][j]=s*dx*dy;
        }
    }


    for(j=2;j<m;j++)
    {
            i=1;
        ae1[i][j]=k*dy/dx;aw1[i][j]=k*dy/(dx/2);
        an1[i][j]=k*dx/dy;as1[i][j]=k*dx/dy;
        ap0[i][j]=den*cv*dx*dy/dt;
        ap1[i][j]=ap0[i][j]+ae1[i][j]+aw1[i][j]+an1[i][j]+as1[i][j];
        bp[i][j]=s*dx*dy;
    }


    for(j=2;j<m;j++)
    {
            i=n;
        ae1[i][j]=k*dy/(dx/2);aw1[i][j]=k*dy/dx;
        an1[i][j]=k*dx/dy;as1[i][j]=k*dx/dy;
        ap0[i][j]=den*cv*dx*dy/dt;
        ap1[i][j]=ap0[i][j]+ae1[i][j]+aw1[i][j]+an1[i][j]+as1[i][j];
        bp[i][j]=s*dx*dy;
    }

    for(i=2;i<n;i++)
    {
            j=1;
        ae1[i][j]=k*dy/dx;aw1[i][j]=k*dy/dx;
        an1[i][j]=k*dx/dy;as1[i][j]=k*dx/(dy/2);
        ap0[i][j]=den*cv*dx*dy/dt;
        ap1[i][j]=ap0[i][j]+ae1[i][j]+aw1[i][j]+an1[i][j]+as1[i][j];
        bp[i][j]=s*dx*dy;
    }


    for(i=2;i<n;i++)
    {
            j=m;

        ae1[i][j]=k*dy/dx;aw1[i][j]=k*dy/dx;
        an1[i][j]=k*dx/(dy/2);as1[i][j]=k*dx/dy;
        ap0[i][j]=den*cv*dx*dy/dt;
        ap1[i][j]=ap0[i][j]+ae1[i][j]+aw1[i][j]+an1[i][j]+as1[i][j];
        bp[i][j]=s*dx*dy;
    }
    //�ĸ���
    i=1;j=1;
        ae1[i][j]=k*dy/dx;aw1[i][j]=k*dy/(dx/2);
        an1[i][j]=k*dx/dy;as1[i][j]=k*dx/(dy/2);
        ap0[i][j]=den*cv*dx*dy/dt;
        ap1[i][j]=ap0[i][j]+ae1[i][j]+aw1[i][j]+an1[i][j]+as1[i][j];
        bp[i][j]=s*dx*dy;

    i=1;j=m;
        ae1[i][j]=k*dy/dx;aw1[i][j]=k*dy/(dx/2);
        an1[i][j]=k*dx/(dy/2);as1[i][j]=k*dx/dy;
        ap0[i][j]=den*cv*dx*dy/dt;
        ap1[i][j]=ap0[i][j]+ae1[i][j]+aw1[i][j]+an1[i][j]+as1[i][j];
        bp[i][j]=s*dx*dy;
    i=n;j=1;
        ae1[i][j]=k*dy/(dx/2);aw1[i][j]=k*dy/dx;
        an1[i][j]=k*dx/dy;as1[i][j]=k*dx/(dy/2);
        ap0[i][j]=den*cv*dx*dy/dt;
        ap1[i][j]=ap0[i][j]+ae1[i][j]+aw1[i][j]+an1[i][j]+as1[i][j];
        bp[i][j]=s*dx*dy;
    i=n;j=m;
        ae1[i][j]=k*dy/(dx/2);aw1[i][j]=k*dy/dx;
        an1[i][j]=k*dx/(dy/2);as1[i][j]=k*dx/dy;
        ap0[i][j]=den*cv*dx*dy/dt;
        ap1[i][j]=ap0[i][j]+ae1[i][j]+aw1[i][j]+an1[i][j]+as1[i][j];
        bp[i][j]=s*dx*dy;


//BC��IC
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
            Tn0[i][j]=tl;
    }

    i=n+1;
    for(j=1;j<=m;j++)
    {
        Tn0[i][j]=tr;
    }
    j=0;
    for(i=1;i<=n;i++)
    {
           Tn0[i][j]=tb;
    }

    j=m+1;
    for(i=1;i<=n;i++)
    {
        Tn0[i][j]=tu;
    }

    //ʱ�������

    outputT=fopen("D:\code_blocks\project\��˹.txt","w");
    fprintf(outputT,"a, time, T11, T12, T13, T14, T15, T21, T22, T23, T24, T25, T31, T32, T33, T34, T35, T41, T42, T43, T44, T45, T51, T52, T53, T54, T55\n");
    for(tstep=1;tstep<=maxtstep;tstep++)
    {
        fprintf(outputT,"%i, %e  ",tstep,tstep*dt);

        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
            {
                Tn0[i][j]=T0[i][j];//������ֵ��
            }
        }

        reali=1000;

        for(iter=1;iter<1000;iter++)
        {
            //�������̣�
             for(i=1;i<=n;i++)
                {
                    for(j=1;j<=m;j++)
                    {
                        //��˹����
                        T[i][j]=(ae1[i][j]*Tn0[i+1][j]+aw1[i][j]*T[i-1][j]+an1[i][j]*Tn0[i][j+1]+as1[i][j]*T[i][j-1]+ap0[i][j]*T0[i][j]+bp[i][j])/ap1[i][j];
                        //T[i][j]=(ae1[i][j]*Tn0[i+1][j]+aw1[i][j]*Tn0[i-1][j]+an1[i][j]*Tn0[i][j+1]+as1[i][j]*Tn0[i][j-1]+ap0[i][j]*T0[i][j]+bp[i][j])/ap1[i][j];
                        resi[i][j]=abs(T[i][j]-Tn0[i][j]);
                    }
                }
                resimax=0;
                //�����в�
            for(i=1;i<=n;i++)
            {
                for(j=1;j<=m;j++)
                {
                    if(resi[i][j]>resimax)
                    {
                        resimax=resi[i][j];
                    }
                }
            }
                if(resimax<1e-5)
                {
                    reali=iter;
break;
                }


                //����ֵ������ֵ��
             for(i=1;i<=n;i++)
                {
                    for(j=1;j<=m;j++)
                    {
                        Tn0[i][j]=T[i][j];
                    }
                }

        }
        for(i=1;i<=n;i++)
            {
                for(j=1;j<=m;j++)
                {
                    fprintf(outputT,"%e ",T[i][j]);
                }
            }

        fprintf(outputT,",%e, %i \n",resimax,reali);
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

