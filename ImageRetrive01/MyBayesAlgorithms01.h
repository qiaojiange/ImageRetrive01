#pragma once
//#include "CvvImage.h"

#include "Feature.h"
#include <vector>
#include <string>
#include "BayesAlgorithms.h"
#include "opencv2/opencv.hpp"
//#include "Util.h"

class MyBayesAlgorithms01:public BayesAlgorithms
{
public:
	MyBayesAlgorithms01(void);
	~MyBayesAlgorithms01(void);
	// 初始化系统--计算用户选择图片的特征
//	int initSystem(void);
	// 特征规格化
//	int featureNormalization(std::vector<float>& colHisVector, const char* filePath);
//	void featureNormalization(std::vector<float>& featureVector);
	// 根据用户反馈进行处理
//	void process(void);
	// 更新参数
//	void updataParameter(int nk, int q, CvMat& sigma, CvMat& Q, std::vector<float> Pwi);
private:
//	std::vector<float> m_colHisVector;
//	CvMat* m_pSigma;
//	CvMat* m_pQ;
public:
	//std::vector<std::string> m_negativeFilePath;
	//std::vector<std::string> m_positiveFilePath;
	std::string m_userChooseFilePath;
	// 计算距离
	//static float calcDistance(CvMat& Q,CvMat& QTransposition, CvMat& meanVector, std::vector<float>& P, float detQ)
//	static float MyBayesAlgorithms01::calcDistance(CvMat& Q,CvMat& QTransposition, CvMat& meanVector, float& Pi, float detQ);
	void putPositiveFile(std::string& filePath);
	// 负反馈文件
	void putNegativeFile(std::string& filePath);
	// 抽取特征
	void train(void);


private:
	CvNormalBayesClassifier* pModel;
public:
	// 开始训练
//	void startTrain(void);
	// 识别图片
	float predict(std::string& filePath);
	// 清空反馈数据
	void cleanFeedBackData(void);
private:
	// 是否是第一次训练
	bool isFirstTrain;
};

