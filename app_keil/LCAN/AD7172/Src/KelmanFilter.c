#include "KelmanFilter.h"
#include "math.h"
//#define LastPointNum 5
//#define N 1e-3
//static int X = 4500;                      //????
//static float P = 1;                    //??????
//static float K_Gain;                   //K??

//static int Pos = 0; 
//static int Len = 0;                 
//static int Last_Points[LastPointNum]; 

////????
//void  Enqueue(int data)
//{
//    Last_Points[Pos] = data;                                   
//    Pos = (Pos+1)%5;
//    if(Len <5)
//        Len++;
//}
////????????5???
//int IsFull()
//{
//    if(Len == 5)
//        return 1;
//    else
//        return 0;
//}
////????????,??????????


// float Least_square_method2()
//{   
//    int16_t x[LastPointNum] = {0,1,2,3,4};
//    int y[LastPointNum];
//    for(int i = 0;i<LastPointNum;i++)
//    {
//        y[i] = Last_Points[(Pos+i)%LastPointNum];
//    }
//    float a,b,c,m1,m2,m3,z1,z2,z3;
//    
//    a=b=c=1;

//    float sumx=0,sumx2=0,sumx3=0,sumx4=0,sumy=0,sumxy=0,sumx2y=0;
//    for(int i=0;i<5;i++)
//    {
//        sumx+=x[i];sumy+=y[i];
//        sumx2+=pow (x[i],2); sumxy+=x[i]*y[i];
//        sumx3+=pow(x[i],3); sumx2y+=pow(x[i],2)*y[i];
//        sumx4+=pow(x[i],4);
//    }
//    do{
//        m1=a;
//        a=(sumx2y-sumx3*b-sumx2*c)/sumx4;
//        z1=(a-m1)*(a-m1);

//        m2=b; 
//        b=(sumxy-sumx*c-sumx3*a)/sumx2;
//        z2=(b-m2)*(b-m2);

//        m3=c; 
//        c=(sumy-sumx2*a-sumx*b)/5;
//        z3=(c-m3)*(c-m3);

//    }while((z1>N)||(z2>N)||(z3>N));
//    return 2*a*4+b;
//}

//float Least_square_method(int N) 
//{
//    int Points[N];
//    for(int i = 0;i<N;i++)
//    {
//        Points[i] = Last_Points[(Pos+i)%N];
//    }
//    int i=0;
//    float K=0,b=0,A=0,B=0,C=0,D=0;
//    for(i=0;i<N;i++)
//    {
//        A+=(i+1)*Points[i];
//        B+=(i+1);
//        C+=Points[i];
//        D+=(i+1)*(i+1);
//    }
//    K=(N*A-B*C)/(N*D-B*B);
//    b=C/N-K*B/N;
//    /*?????????????????????*/
//    return K;
//}


//int KelmanFilter(int AdData)
//{
//    float Q = 0.08;                             //???? 
//    float R = 2;                                //??????
//    float u = 0;                                //????,????????
//		float B = 0;
//    if(IsFull())
//        u = Least_square_method2();
//		if(u <5)
//		{
//			B = 0.6;
//		}
//	  else 
//			B=0.6;
//    int Ref = (AdData + X)/2;      
//    float X_offset = X - Ref;
//    float AdData_offset = AdData - Ref;
//    
//    float X_ = X_offset + u*B;                                  //????
//    float P_ =  P + Q;                                        //??X_?????

//    K_Gain = P_ / (P_ + R);                                   //????
//    P = (1 - K_Gain) * P_;                                    //??P
//    float result = X_ + K_Gain * (AdData_offset - X_offset);  //??X
//    X = result+Ref;

//    Enqueue(X);
//    return X;
//}

static int X = 4400;           //????
static float P = 1;         //??????
static float K_Gain;        //K??

int KalmanFilter(int AdData)
{
    float Q = 0.07;       /* ???? */
    float R = 5;          /* ?????? */

    int Ref = (AdData + X)/2;
    float X_offset = X - Ref;
    float AdData_offset = AdData - Ref;
    
    float X_ = X_offset;
    float P_ =  P + Q;

    K_Gain = P_ / (P_ + R);                                   //????
    P = (1 - K_Gain) * P_;                                    //??P
    float result = X_ + K_Gain * (AdData_offset - X_offset);  //??X
    X = result;  
	  X = X + Ref;                
    return X;
}
