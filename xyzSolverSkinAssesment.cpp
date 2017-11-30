#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"
//#include "opencv2/core/core.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <opencv2/features2d/features2d.hpp>
//#include <iostream>
//#include <string>
//#include <stdio.h>
//#include <math.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
//#include <sstream>
#include <iostream>
#include <fstream>


using namespace cv;
using namespace std;

//string file_read = "1907_1_L10c.xyz";
//string file_read = "lenganbawah_lutfi.xyz";
string file_read = "asli/lenganatas_lutfic.xyz";
ifstream incount(file_read.c_str());
ifstream in2(file_read.c_str());

float avg(float a[],int n);

        int ndatacount,ndataR;

typedef struct{
    float x;
    float y;
    float z;
    float v1,v2,v3;
}dataR;

typedef struct{
    float x;
    float y;
    float z;
}data;

int main(int, char**)
{
    float totaldiff=0;
    float Sa=0;
    float Err=0;

    //initiate high polynomial koef
    float a1=0;
    float a2=0;
    float a3=0;
    float a4=0;
    float a5=0;
    float a6=0;
    float a7=0;
    float a8=0;
    float a9=0;

    string line;
    int i=0;
    while(getline(incount,line)){
    //do something with the line
        i=i+1;
        //cout << i <<"\t"<< x[i-1]<<"\t"<<y[i-1]<<"\t"<<rough[i-1]<<"\n";
    }
    ndataR=i;
    cout<<"FILE Input : "<<file_read<<endl;
    cout<<"Jumlah data : "<<ndataR<<endl;
    dataR *datR= (dataR*)malloc(6*ndataR*sizeof(float));
    i=0;
    while(getline(in2,line)){
    //do something with the line
        //in2 >> x[i] >> y[i] >> z[i];
        in2 >> datR[i].x >> datR[i].z >> datR[i].y >> datR[i].v1 >> datR[i].v2 >> datR[i].v3 ;
        i=i+1;
        //cout << i <<"\t"<< x[i-1]<<"\t"<<y[i-1]<<"\t"<<z[i-1]<<"\n";
        //cout << i <<"\t"<< datR[i-1].x <<"\t"<< datR[i-1].y <<"\t"<< datR[i-1].z <<endl;
    }
    //cout<<x<<"\t"<<y<<"\t"<<z<<endl;
    cout<<"Read file succesfull\n";


    //Assignment Data
    ndatacount = ndataR;
    data *datcount = (data*)malloc(3*ndatacount*sizeof(float));
    for(i=0;i<ndatacount;i++){
        datcount[i].x=datR[i].x;
        datcount[i].y=datR[i].y;
        datcount[i].z=datR[i].z;
    }


    //format fungsi Ax+By=Z(x,y);

    //data yang akan diambil 80x80 =>
    /* Useless in here
    // x = > 15.205 & 25.384
    // y = > 9.547 & 19.731
    int i2=0;
    for(i=0;i<ndata;i++){
        if(dat[i].x>=19.205){
            if(dat[i].x<=21.384){
                if(dat[i].y>=13.547){
                    if(dat[i].y<=15.731){
                         //datcount[i2]=dat[i];
                        i2++;
                    }
                }
            }
        }
    }
    */
    /*
    int ndatacount=i2;
    data *datcount= (data*)malloc(3*ndatacount*sizeof(float));
    */
    float *z = (float*)malloc(ndatacount*sizeof(float));
    float *zt = (float*)malloc(ndatacount*sizeof(float));
    float *zdiff = (float*)malloc(ndatacount*sizeof(float));
    /*
    cout<<"ndata hitung :\t"<<i2<<endl;

    i2=0;
    for(i=0;i<ndata;i++){
        if(dat[i].x>=19.205){
            if(dat[i].x<=21.384){
                if(dat[i].y>=13.547){
                    if(dat[i].y<=15.731){
                        datcount[i2]=dat[i];
                        z[i2]=datcount[i2].z;
                        i2++;
                    }
                }
            }
        }
    }
    */

    // matrix [x,y][A B]=[Z]
    Mat A(ndatacount,9,CV_32FC1);
    //cout<<(pow(x[0],2))*(pow(y[0],2))<<endl;
    cout <<"initiate Matrix A\n";
    for(unsigned int a = 0; a < ndatacount; a++){
        A.at<float>(a,0)=(pow(datcount[a].x,2))*(pow(datcount[a].y,2));
        A.at<float>(a,1)=datcount[a].x*(pow(datcount[a].y,2));
        A.at<float>(a,2)=pow(datcount[a].y,2);
        A.at<float>(a,3)=(pow(datcount[a].x,2))*datcount[a].y;
        A.at<float>(a,4)=datcount[a].x*datcount[a].y;
        A.at<float>(a,5)=datcount[a].y;
        A.at<float>(a,6)=pow(datcount[a].x,2);
        A.at<float>(a,7)=datcount[a].x;
        A.at<float>(a,8)=1;
        z[a]=datcount[a].z;
    }
    cout<<"Assign Matrix Successfull:\n";
    //cout << "A: \n" << A << std::endl;
    Mat inverted(9,ndatacount,CV_32FC1);
    invert(A, inverted, cv::DECOMP_SVD);
    //cout<<"\nhasil invers:\n"<<inverted<<endl;
    cout<<"Processing matrix to solve A1 & A2 .... "<<endl;
    //cout<<inverted.at<float>(2,1)<<"\t"<<rough[1];
    for(unsigned int b=0; b<ndatacount ;b++){
        a1+=inverted.at<float>(0,b)*datcount[b].z;
        a2+=inverted.at<float>(1,b)*datcount[b].z;
        a3+=inverted.at<float>(2,b)*datcount[b].z;
        a4+=inverted.at<float>(3,b)*datcount[b].z;
        a5+=inverted.at<float>(4,b)*datcount[b].z;
        a6+=inverted.at<float>(5,b)*datcount[b].z;
        a7+=inverted.at<float>(6,b)*datcount[b].z;
        a8+=inverted.at<float>(7,b)*datcount[b].z;
        a9+=inverted.at<float>(8,b)*datcount[b].z;
    }
    cout<<"nilai koefisien fitting :"<<endl;
    cout<<"a1 \t\t a2 \t\t a3 \t\t a4 \t\t a5 "<<endl;
    cout<<a1<<" \t"<<a2<<" \t"<<a3<<" \t"<<a4<<" \t"<<a5<<endl;
    cout<<"a6 \t\t a7 \t\t a8 \t\t a9"<<endl;
    cout<<a6<<" \t"<<a7<<" \t"<<a8<<" \t"<<a9<<endl;

    //fungsi fitting high polynomial
    //a1(pow(x,2)*pow(y,2))+a2(x*pow(y,2))+a3(pow(y,2))+a4(pow(x,2)*y)+a5(x*y)+a6(y)+a7(pow(x,2))+a8(x)+a9(1)
    for(unsigned int c=0; c<ndatacount ; c++){
        zt[c]=(a1*(pow(datcount[c].x,2)*pow(datcount[c].y,2)))+(a2*(datcount[c].x*pow(datcount[c].y,2)))+(a3*(pow(datcount[c].y,2)))+(a4*(pow(datcount[c].x,2)*datcount[c].y))+(a5*(datcount[c].x*datcount[c].y))+(a6*(datcount[c].y))+(a7*(pow(datcount[c].x,2)))+(a8*(datcount[c].x))+(a9*(1));
        zdiff[c]=abs(z[c]-zt[c]);
        //cout<<c<<"\t"<<z[c]<<"\t"<<zt[c]<<"\t"<<zdiff[c]<<endl;
        totaldiff+=zdiff[c];
    }

     //Menghitung nilai Sa
     //cout<<"total diff:\t"<<totaldiff<<endl;
     Sa=(1.00/ndatacount)*totaldiff;
     cout<<"Nilai MAE :\t"<<Sa<<endl;

    /* Masih Salah
     //Menghitung Error
     //Err=abs(avg(zt,ndatacount)-avg(z,ndatacount));
     //cout<<"Error :\t"<<Err<<endl;

     //Menghitung akurasi
     //float akurasi=0;
     //akurasi=(1-(Err/avg(z,ndatacount)))*100;
     //cout<<"Akurasi : "<<akurasi<<"%"<<endl;
    */
    return 0;
}

float avg(float a[],int n){
    int i;
    float sum=0;

    for(i=0;i<n;i++){
        sum+=a[i];
    }
    return sum/n*1.00;
}
