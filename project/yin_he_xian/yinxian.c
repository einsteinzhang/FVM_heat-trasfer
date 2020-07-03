

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
    double ae0[302],aw0[302];
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
    dt=50;
    n=100;


//****************************************�����ǵ���ʱ�䲽��*********************


    maxtstep=4000;


    dx=length/n;
//�ⲿ����ʱ����ʾ��Ҫ�õ���

//ϵ��ֻ��1-3�������ã�


        for(i=2;i<n;i++)
        {
            ae0[i]=k/(2*dx);aw0[i]=k/(2*dx);
            ae1[i]=k/(2*dx);aw1[i]=k/(2*dx);
            ap0[i]=den*c*dx/dt-k/(2*dx)-k/(2*dx);
            ap1[i]=ap0[i]+ae0[i]+aw0[i]+ae1[i]+aw1[i];
            b[i]=s*dx;
        }
        i=1;
            ae0[i]=k/(2*dx);aw0[i]=k/(2*dx/2);
            ae1[i]=k/(2*dx);aw1[i]=k/(2*dx/2);
            ap0[i]=den*c*dx/dt-k/(2*dx)-k/(2*dx/2);
            ap1[i]=ap0[i]+ae0[i]+aw0[i]+ae1[i]+aw1[i];
            b[i]=s*dx;
        i=n;
            ae0[i]=k/(2*dx/2);aw0[i]=k/(2*dx);
            ae1[i]=k/(2*dx/2);aw1[i]=k/(2*dx);
            ap0[i]=den*c*dx/dt-k/(2*dx)-k/(2*dx/2);
            ap1[i]=ap0[i]+ae0[i]+aw0[i]+ae1[i]+aw1[i];
            b[i]=s*dx;



//BC��IC

    for(i=1;i<=n;i++)
    {
        T0[i]=3;
    }

    T[0]=tl;T[n+1]=tr;
    T0[0]=tl;T0[n+1]=tr;


    //ʱ�������

    outputT=fopen("D:\code_blocks\project\T2444.txt","w");
    for(tstep=1;tstep<=maxtstep;tstep++)
    {
        fprintf(outputT,"%i  ",tstep);

              //��abcd�ֱ�ֵ
        i=1;
        a[i]=ap1[i];
        b0[i]=-aw1[i];
        c0[i]=-ae1[i];
        d[i]=aw1[i]*T[i-1]+ap0[i]*T0[i]+b[i]+ae0[i]*T0[i+1]+aw0[i]*T0[i-1];//������ʽ��

        for(i=2;i<n;i++)
        {
            a[i]=ap1[i];
            b0[i]=-aw1[i];
            c0[i]=-ae1[i];
            d[i]=ap0[i]*T0[i]+b[i]+ae0[i]*T0[i+1]+aw0[i]*T0[i-1];
        }
        i=n;
        a[i]=ap1[i];
        b0[i]=-aw1[i];
        c0[i]=-ae1[i];
        d[i]=ae1[i]*T[i+1]+ap0[i]*T0[i]+b[i]+ae0[i]*T0[i+1]+aw0[i]*T0[i-1];
        //���ú�����֮ǰ������ϵ����ֵ֮��
        tdma();
        for(i=1;i<=n;i++)
        {
            T[i]=x[i];
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
