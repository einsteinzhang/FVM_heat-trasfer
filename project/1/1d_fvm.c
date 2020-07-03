#include<stdio.h>
    double length;
    double tl,tr;
    double den,c,k;
    double s;
    double dt;
    int n;//�ֳɼ��οռ�

    double dx;
    //��0-10:һ����n�������壬3n+2��������
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
    //��dxԽ��ԽС��dtҪ����CFL��������˵apҪ�����������壡
    dt=50;
    n=3;

//****************************************�����ǵ���ʱ�䲽��*********************

    int tstep;
    int maxtstep;
    maxtstep=1000;


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
//BC��IC
    for(i=1;i<=n;i++)
    {
        T0[i]=3;
    }
    T0[0]=tl;T0[n+1]=tr;

    //ʱ�������

    outputT=fopen("D:\code_blocks\project\t100.txt","w");
    for(tstep=1;tstep<=maxtstep;tstep++)
    {
        fprintf(outputT,"%i  ",tstep);

        for(i=1;i<=n;i++)
        {
            T[i]=(ae0[i]*T0[i+1]+aw0[i]*T0[i-1]+ap0[i]*T0[i]+b[i])/ap1[i];//��ȷ����Ϊi=1ʱ��e��Ӧ��T2
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
