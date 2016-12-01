#include "StdAfx.h"
#include "Feature.h"


Feature::Feature(void)
{
}


Feature::~Feature(void)
{
}


//获取颜色直方图
Feature* Feature::get_colHis(Feature* img){
	int i,j,m,n,q;
	IplImage* img_hsv;
	int width, height;
	int count;
	int after_h,after_s,after_v;
	int Feature_Q;

	int count_s[4]={0}, count_v[4]={0}, count_h[16]={0};
	CvScalar s;

	img_hsv=cvCreateImage(cvGetSize(img->img),IPL_DEPTH_8U,3);
	s = cvGet2D(img_hsv,0,0);


	cvCvtColor(img->img,img_hsv,CV_BGR2HSV);
	after_h,after_s,after_v;
	width=img->img->width;
	height=img->img->height;


	for(i=0;i<height;i++){ 
		for(j=0;j<width;j++){
			s=cvGet2D(img_hsv,i,j);
			count=i*width+j;
			//色彩
			after_h=quantization_H(s.val[0]*2);
			//饱和度
			after_s=quantization_S(s.val[1]/255);
			//亮度
			after_v=quantization_V(s.val[2]/255);

			Feature_Q=25*after_h+5*after_s+after_v;

			img->col_hist[Feature_Q]=img->col_hist[Feature_Q]+1;

		}
	}

	return img;
}

//color moment---色矩
//颜色矩是一种简单有效的颜色特征表示方法，
//有一阶矩(均值,mean)、二阶矩(方差,viarance)
//	和三阶矩(斜度,skewness)等，由于颜色信息主要分布于低阶矩中，
//	所以用一阶矩，二阶矩和三阶矩足以表达图像的颜色分布

Feature* Feature::get_colMoment(Feature* img){
	int width, height;
	IplImage* img_hsv;
	float sum_h1=0,sum_s1=0,sum_v1=0; 
	float sum_h2=0,sum_s2=0,sum_v2=0;
	float sum_h3=0,sum_s3=0,sum_v3=0;
	int i,j,k,n;
	int m1,m2;
	float avg_h,avg_s,avg_v;
	CvScalar s;

	img_hsv=cvCreateImage(cvGetSize(img->img),IPL_DEPTH_8U,3);
	s = cvGet2D(img_hsv,0,0);

	cvCvtColor(img->img,img_hsv,CV_RGB2HSV);
	width=img->img->width;
	height=img->img->height;

	n=width*height;

	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			s=cvGet2D(img_hsv,i,j);
			sum_h1=sum_h1+s.val[0];
			sum_s1=sum_s1+s.val[1];
			sum_v1=sum_v1+s.val[2];
		}
	}

	avg_h=sum_h1/n;
	avg_s=sum_s1/n;
	avg_v=sum_v1/n;

	img->col_moment[0]=avg_h;
	img->col_moment[1]=avg_s;
	img->col_moment[2]=avg_v;

	printf("moment[0]=%g\n",img->col_moment[0]);
	printf("moment[1]=%g\n",img->col_moment[1]);
	printf("moment[2]=%g\n",img->col_moment[2]);

	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			s=cvGet2D(img_hsv,i,j);
			sum_h2=sum_h2+pow((s.val[0]-avg_h)*1.0,2);
			sum_s2=sum_s2+pow((s.val[1]-avg_s)*1.0,2);
			sum_v2=sum_v2+pow((s.val[2]-avg_v)*1.0,2);

			sum_h3=sum_h3+pow((s.val[0]-avg_h)*1.0,3);
			sum_s3=sum_s3+pow((s.val[1]-avg_s)*1.0,3);
			sum_v3=sum_v3+pow((s.val[2]-avg_v)*1.0,3);

		}
	}

	img->col_moment[3]=sqrt(sum_h2*1.0/n);
	img->col_moment[4]=sqrt(sum_s2*1.0/n);
	img->col_moment[5]=sqrt(sum_v2*1.0/n);

	printf("moment[3]=%g\n",img->col_moment[3]);
	printf("moment[4]=%g\n",img->col_moment[4]);
	printf("moment[5]=%g\n",img->col_moment[5]);

	img->col_moment[6]=pow(abs(sum_h3/n)*1.0,1.0/3);
	img->col_moment[7]=pow(abs(sum_s3/n)*1.0,1.0/3);
	img->col_moment[8]=pow(abs(sum_v3/n)*1.0,1.0/3);

	if(sum_h3<=0){
		img->col_moment[6]=img->col_moment[6]*(-1);
	}
	if(sum_s3<=0){
		img->col_moment[7]=img->col_moment[7]*(-1);
	}
	if(sum_v3<=0){
		img->col_moment[8]=img->col_moment[8]*(-1);
	}

	printf("moment[6]=%g\n",img->col_moment[6]);
	printf("moment[7]=%g\n",img->col_moment[7]);
	printf("moment[8]=%g\n",img->col_moment[8]);


	return img;
}


//coarsness --粗粒度

int Feature::get_kmax(IplImage* img1){
	int width, height;
	int kmax;
	float k;
	int k_int;

	width=img1->width;
	height=img1->height;

	if(width>=height){
		kmax=width;
	}else{
		kmax=height;
	}

	do{
		k=log(kmax*1.0)/log(2*1.0);
		k_int=(int)k;
		if(k-k_int!=0){
			kmax=kmax-1;
		}
	}while(k-k_int!=0);

	printf("kmax=%d",k_int);
	return k_int;
}

//获取图片的粗糙度
Feature* Feature::get_coarsness(Feature* img){
	int width,height;
	IplImage* img_gray;
	int kmax,e_max=0,k_best=0;
	int i,j,i1,j1,k,k1;
	int limit,sum=0,sum1=0;
	CvScalar s;

	coareness *c  = (coareness*)malloc(sizeof(coareness) + sizeof(int)*100);
	memset(c->avg,0,sizeof(c->avg));
	memset(c->eh,0,sizeof(c->eh));
	memset(c->ev,0,sizeof(c->ev));
	memset(c->s_best,0,sizeof(c->s_best));

	img_gray=cvCreateImage(cvGetSize(img->img),IPL_DEPTH_8U,1);
	s = cvGet2D(img_gray,0,0);

	cvCvtColor(img->img,img_gray,CV_RGB2GRAY);
	width=img->img->width;
	height=img->img->height;
	kmax=get_kmax(img->img);

	for(k=1;k<=kmax;k++){
		limit=pow(2*1.0,k-1);
		printf("limit=%d\n",limit);
		for(i=1+limit;i<=(height-limit);i++){
			for(j=1+limit;j<=(width-limit);j++){
				sum=0;

				for(i1=i-limit;i1<i+limit;i1++){
					for(j1=j-limit;j1<j+limit;j1++){
						s=cvGet2D(img_gray,i1,j1);
						sum=sum+s.val[0];
					}
				}

				c->avg[i][j][k]=sum/pow(2*1.0,2*k);
			}
		}
	}


	for(k=1;k<=kmax;k++){
		limit=pow(2*1.0,k-1);
		printf("limit=%d\n",limit);
		for(i=1+limit;i<=(height-limit);i++){
			for(j=1+limit;j<=(width-limit);j++){
				c->eh[i][j][k]=abs((c->avg[i+limit][j][k])-(c->avg[i-limit][j][k]));
				c->ev[i][j][k]=abs((c->avg[i][j+limit][k])-(c->avg[i][j-limit][k]));
			}
		}
	}



	for(i=0;i<height;i++){
		for(j=0;j<=width;j++){
			e_max=0;
			for(k=1;k<=kmax;k++){
				if((c->eh[i][j][k])>e_max){
					e_max=c->eh[i][j][k];
					k_best=k;
				}
				if((c->ev[i][j][k])>e_max){
					e_max=c->ev[i][j][k];
					k_best=k;
				}
			}	
			c->s_best[i][j]=pow(2*1.0,k_best);
			printf("s-best[%d][%d][%d]=%d\n",i,j,k_best,c->s_best[i][j]);
			sum1=sum1+c->s_best[i][j];
		}
	}

	img->f_crs=sum1*1.0/(width*height);
	printf("f_crs=%g\n",img->f_crs);
	return img;
}




//contrast，对比度
Feature* Feature::get_contrast(Feature* img){
	int width,height;
	IplImage* img_gray;
	int i,j,i1,j1;
	float sum=0.0,sum1=0.0,sum_var=0.0; 
	float avg,area,m4;
	float var,alfa4,std;
	CvScalar s;

	img_gray=cvCreateImage(cvGetSize(img->img),IPL_DEPTH_8U,1);
	//value = arr(idx0,idx1,...) 
	s = cvGet2D(img_gray,0,0);

	//Converts input array pixels from one color space to another
	cvCvtColor(img->img,img_gray,CV_RGB2GRAY);//变成灰度图
	width=img->img->width;
	height=img->img->height;
	area=height*width;

	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			s=cvGet2D(img_gray,i,j);//
			sum=sum+s.val[0];//单通道图像像素
		}
	}
	avg=sum/area;

	//printf("avg=%g\nkkkkk\n",avg);

	for(i1=0;i1<height;i1++){
		for(j1=0;j1<width;j1++){
			s=cvGet2D(img_gray,i1,j1);
			// printf("s=%d\n",s.val[0]);
			sum1=sum1+pow((s.val[0]-avg)*1.0,4);
			sum_var=sum_var+pow((s.val[0]-avg)*1.0,2);
			// printf("sum_1[%d][%d]=%g\n",i1,j1,sum1);
			// printf("sum_var[%d][%d]=%g\n",i1,j1,sum_var);
		}
	}
	//printf("sum_1=%g\n",sum1);
	//printf("sum_var=%g\n",sum_var);
	m4=sum1*1.0/area;
	std=sum_var*1.0/area;
	var=sqrt(std*1.0);
	alfa4=pow(m4*1.0,0.25)/(pow(var*1.0,4));
	img->f_con=var/(pow(alfa4*1.0,0.25));

	//printf("m4=%g\n",m4);
	//printf("std=%g\n",std);
	//printf("var=%g\n",var);
	//printf("alfa4=%g\n",alfa4);
	printf("f_con=%g\n",img->f_con);

	return img;
}



//directionaloty

//方向性
Feature* Feature::get_directionality(Feature* img){
	int width, height;
	int i,j,k;
	float max=-1;
	int sum=0;
	float f_dir=0;
	IplImage* dst1;
	IplImage* dst2;
	IplImage* img_gray;
	CvScalar s1;
	CvScalar s2;
	//垂直
	float gradientH[9]={-1,0,1,
		-1,0,1,
		-1,0,-1};
	//水平
	float gradientV[9]={1,1,1,
		0,0,0,
		-1,-1,-1};
	CvMat km1 = cvMat(3,3,CV_32F,gradientH);
	CvMat km2 = cvMat(3,3,CV_32F,gradientV);//卷积核

	directionality *d  = (directionality*)malloc(sizeof(directionality) + sizeof(int)*100);
	memset(d->MH,0,sizeof(d->MH));
	memset(d->MV,0,sizeof(d->MV));
	memset(d->MG,0,sizeof(d->MG));
	memset(d->sita,0,sizeof(d->sita));
	memset(d->Nsita,0,sizeof(d->Nsita));
	memset(d->HD,0,sizeof(d->HD));

	img_gray=cvCreateImage(cvGetSize(img->img),IPL_DEPTH_8U,1);

	cvCvtColor(img->img,img_gray,CV_RGB2GRAY);
	dst1= cvCreateImage( cvGetSize(img_gray), IPL_DEPTH_8U, 1 );
	dst2= cvCreateImage( cvGetSize(img_gray), IPL_DEPTH_8U, 1 );
	s1=cvGet2D(dst1,0,0);
	s2=cvGet2D(dst2,0,0);

	//计算卷积，将图像IplImage结构转换为图像数组，在核中心卷积
	cvFilter2D( img_gray, dst1, &km1, cvPoint( -1, -1 ) );
	cvFilter2D( img_gray, dst2, &km2, cvPoint( -1, -1 ) );

	width=img->img->width;
	height=img->img->height;




	for(i=2;i<height;i++){
		for(j=2;j<width;j++){
			s1=cvGet2D(dst1,i,j);
			s2=cvGet2D(dst2,i,j);
			d->MH[i-2][j-2]=s1.val[0];
			d->MV[i-2][j-2]=s2.val[0];
			d->MG[i-2][j-2]=(abs(d->MH[i-2][j-2])+abs(d->MV[i-2][j-2]))*1.0/2;

			if(d->MV[i-2][j-2]!=0){
				d->sita[i-2][j-2]=(atan((d->MH[i-2][j-2])/(d->MV[i-2][j-2]))*1.0)+(pi*1.0/2);
			}else{ d->sita[i-2][j-2]=0;}


			for(k=0;k<16;k++){
				if((d->sita[i-2][j-2]>=(2*(k-1)*pi/32)) && (d->sita[i-2][j-2]<((2*(k-1)+1)*pi/32)) && (d->MG[i-2][j-2]>=12)){
					d->Nsita[k]++;
				}

			}


		}
	}

	for(k=0;k<16;k++){
		sum=sum+(d->Nsita[k]);
	}
	//printf("sum=%d\n",sum);

	for(k=0;k<16;k++){
		d->HD[k]=(d->Nsita[k])*1.0/sum;
		//printf("N[%d]=%d\n",k,d->Nsita[k]);
		//printf("HD[%d]=%g\n",k,d->HD[k]);
		if((d->HD[k])>max){
			max=d->HD[k];
		}
	}
	//printf("max=%g\n",max);
	for(k=0;k<16;k++){
		f_dir=f_dir+pow((k-max)*1.0,2)*(d->HD[k]);
		//printf("f-dir=%g\n",f_dir);
	}

	img->f_dir=f_dir;
	printf("f_dir=%g\n",f_dir);

	return img;
}

//获取特征向量
CvMat Feature::getFeartureVector(Feature* img){
	int i =0;
	float sum_hist = 0;
	for (i = 0;i<300;++i)
	{
		sum_hist += pow(img->col_hist[i]*1.0,2);
	}
	sum_hist=sqrt(sum_hist);
	//printf("sum_hist= %f\n",sum_hist);

	float score_hist = 0.0f;
	for(i=0;i<300;++i){
		score_hist=score_hist+((img->col_hist[i])*1.0/sum_hist);
	}
	printf("score_hist= %f\n",score_hist);

	float sum_moment= 0;
	for (int i=0;i<9;i++)
	{
		sum_moment += pow(img->col_moment[i]*1.0,2);
	}
	sum_moment=sqrt(sum_moment);
	//printf("sum_moment = %f\n",sum_moment);

	float score_moment = 0.0f;
	for(i=0;i<9;i++){
		score_moment += img->col_moment[i]*1.0/sum_moment;
	}
	printf("score_moment = %f\n",score_moment);

	float sum_texture = sqrt( pow(img->f_con*1.0,2)+pow(img->f_dir*1.0,2));
	//printf("sum_texture = %f\n",sum_texture);
	float score_texture = ((img->f_con)*1.0/sum_texture)+((img->f_dir)*1.0/sum_texture);
	printf("score_texture = %f\n",score_texture);


	float vals[] = {score_hist*0.24,score_moment*0.16,score_texture*0.6};
	CvMat  mat ;
	cvInitMatHeader(&mat,1,3,CV_32FC1,vals);

	/*for ( i=0;i<mat.rows;i++)
	{
	float element = CV_MAT_ELEM(mat,float,0,i);
	printf("element = %f\n",element);
	}*/
	return mat;
}


//饱和度S表示颜色接近光谱色的程度
int Feature::quantization_S(float s){
	int after_s=0;
	if((s>=0.0&&s<=0.1)||(s>=0.85&&s<=1.0)){
		after_s=0;
	}else if(s>0.1&&s<=0.25){
		after_s=1;
	}else if(s>0.25&&s<=0.45){
		after_s=2;
	}else if(s>0.45&&s<=0.65){
		after_s=3;
	}else if(s>0.65&&s<=0.85){
		after_s=4;
	}
	return after_s;
}
//明度
//明度表示颜色明亮的程度，对于光源色，明度值与发光体的光亮度有关
int Feature::quantization_V(float v){
	int after_v=0;
	if(v>=0.0&&v<=0.15){
		after_v=0;
	}else if(v>0.15&&v<0.4){
		after_v=1;
	}else if(v>0.4&&v<=0.6){
		after_v=2;
	}else if(v>0.6&&v<=0.8){
		after_v=3;
	}else if(v>0.8&&v<=1.0){
		after_v=4;
	}
	return after_v;
}

//颜色直方图 色调
//角度度量，取值范围为0°～360°，从红色开始按逆时针方向计算，红色为0°，绿色为120°,蓝色为240°。它们的补色是：黄色为60°，青色为180°,品红为300°；
int Feature::quantization_H(float h){
	int after_h=0;
	if((h>270.0&&h<=360.0)||(h>=0.0&&h<=20.0)){
		after_h=0;
	}else if(h>20.0&&h<=45){
		after_h=1;
	}else if(h>45.0&&h<=55.0){
		after_h=2;
	}else if(h>55.0&&h<=80.0){
		after_h=3;
	}else if(h>80.0&&h<=100.0){
		after_h=4;
	}else if(h>100.0&&h<=120.0){
		after_h=5;
	}else if(h>120.0&&h<=140.0){
		after_h=6;
	}else if(h>140.0&&h<=165.0){
		after_h=7;
	}else if(h>165.0&&h<=190.0){
		after_h=8;
	}else if(h>190.0&&h<=220.0){
		after_h=9;
	}else if(h>220.0&&h<=255.0){
		after_h=10;
	}else if(h>255.0&&h<=270.0){
		after_h=11;
	}
	return after_h;
}

std::vector<float> Feature::get_colHis(const char* filePath)
{
	int i,j,m,n,q;
	IplImage* img_hsv;
	int width, height;
	int count;
	int after_h,after_s,after_v;
	int Feature_Q;

	int count_s[4]={0}, count_v[4]={0}, count_h[16]={0};
	CvScalar s;
	IplImage * img = cvLoadImage(filePath,1);

	img_hsv=cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,3);
	s = cvGet2D(img_hsv,0,0);


	cvCvtColor(img,img_hsv,CV_BGR2HSV);
	after_h,after_s,after_v;
	width=img->width;
	height=img->height;

	float col_hist[300];
	memset(col_hist,0,sizeof(col_hist));
	for(i=0;i<height;i++){ 
		for(j=0;j<width;j++){
			s=cvGet2D(img_hsv,i,j);
			count=i*width+j;
			//色彩
			after_h=quantization_H(s.val[0]*2);
			//饱和度
			after_s=quantization_S(s.val[1]/255);
			//亮度
			after_v=quantization_V(s.val[2]/255);

			Feature_Q=25*after_h+5*after_s+after_v;

			col_hist[Feature_Q]= col_hist[Feature_Q]+1;

		}
	}
	std::vector<float> col_hist_vector(col_hist,col_hist+300);
	return col_hist_vector;
}
