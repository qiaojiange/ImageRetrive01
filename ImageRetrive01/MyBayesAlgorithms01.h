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
	// ��ʼ��ϵͳ--�����û�ѡ��ͼƬ������
//	int initSystem(void);
	// �������
//	int featureNormalization(std::vector<float>& colHisVector, const char* filePath);
//	void featureNormalization(std::vector<float>& featureVector);
	// �����û��������д���
//	void process(void);
	// ���²���
//	void updataParameter(int nk, int q, CvMat& sigma, CvMat& Q, std::vector<float> Pwi);
private:
//	std::vector<float> m_colHisVector;
//	CvMat* m_pSigma;
//	CvMat* m_pQ;
public:
	//std::vector<std::string> m_negativeFilePath;
	//std::vector<std::string> m_positiveFilePath;
	std::string m_userChooseFilePath;
	// �������
	//static float calcDistance(CvMat& Q,CvMat& QTransposition, CvMat& meanVector, std::vector<float>& P, float detQ)
//	static float MyBayesAlgorithms01::calcDistance(CvMat& Q,CvMat& QTransposition, CvMat& meanVector, float& Pi, float detQ);
	void putPositiveFile(std::string& filePath);
	// �������ļ�
	void putNegativeFile(std::string& filePath);
	// ��ȡ����
	void train(void);


private:
	CvNormalBayesClassifier* pModel;
public:
	// ��ʼѵ��
//	void startTrain(void);
	// ʶ��ͼƬ
	float predict(std::string& filePath);
	// ��շ�������
	void cleanFeedBackData(void);
private:
	// �Ƿ��ǵ�һ��ѵ��
	bool isFirstTrain;
};

