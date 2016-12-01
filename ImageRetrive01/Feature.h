#pragma once
#include <opencv2/core/core.hpp>
#include <cv.h>
#include <highgui.h>
#include <string.h>
#define pi 3.1415926


#define ColorMonmentLength 9
#define ColorHistLength 300


//粗糙度
typedef struct img_coaresness{
	float avg[1000][1000][10];
	float eh[1000][1000][10];
	float ev[1000][1000][10];
	int s_best[1000][1000];
}coareness;

//方向性
typedef struct img_directionality{
	float MH[1000][1000];
	float MV[1000][1000];
	float MG[1000][1000];
	float sita[1000][1000];
	int Nsita[16];
	float HD[16];
}directionality;

class Feature
{
public:
	Feature(void);
	~Feature(void);
	static int quantization_H(float h);
	 static int quantization_S(float s);
	 static int quantization_V(float v);
	 Feature* get_colHis(Feature* img);
	 Feature* get_colMoment(Feature* img);
	 int get_kmax(IplImage* img1);
	 Feature* get_coarsness(Feature* img);
	 Feature* get_contrast(Feature* img);
	 Feature* get_directionality(Feature* img);
	 CvMat getFeartureVector(Feature* img);

public:
	IplImage* img;//原图像
	int col_hist[300];//直方图
	float col_moment[9];//颜色距
	float f_con;//对比度
	float f_crs;//粗糙度
	float f_dir;//方向度
	float score;
	static std::vector<float> get_colHis(const char* filePath);
};

