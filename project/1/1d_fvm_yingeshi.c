
#include<stdio.h>



//����������
    double length;
    double tl,tr;
    double den,c,k;
    double s;
    double dt;
    int n;//�ֳɼ��οռ�

    double dx;
    //��0-10:һ����n�������壬3n+2��������
    double T0[302],T[302];
    double ae1[302],aw1[302],ap0[302],ap1[302],b[302];
    int maxtstep;


    double a[303],b0[303],c0[303],d[303],x[303],p[303],q[303];

    //���¾����ӳ���tdma
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
        //�ش����̣�
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

//****************************************�����ǵ���ʱ�䲽��*********************


    maxtstep=3000;

/*

�ⲿ������ʾ��Ҫ�õ���

//ϵ��ֻ��1-3�������ã�
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
        ap1[i]=ap0[i]+ae1[i]+aw1[i];//��ʾ��ʿһ��
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
//BC��IC
    for(i=1;i<=n;i++)
    {
        T0[i]=3;
    }
    T[0]=tl;T[n+1]=tr;

    //ʱ�������

    outputT=fopen("D:\code_blocks\project\T312.txt","w");
    for(tstep=1;tstep<=maxtstep;tstep++)
    {
        fprintf(outputT,"%i  ",tstep);
        //printf("%i  ",tstep);

        /*��ʾ��
        for(i=1;i<=n;i++)
        {
            T[i]=(ae0[i]*T0[i+1]+aw0[i]*T0[i-1]+ap0[i]*T0[i]+b[i])/ap1[i];//��ȷ����Ϊi=1ʱ��e��Ӧ��T2
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
