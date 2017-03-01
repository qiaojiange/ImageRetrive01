#include "StdAfx.h"
#include "MyBayesAlgorithms01.h"
#include "Feature.h"

using namespace std;

MyBayesAlgorithms01::MyBayesAlgorithms01(void)
	: isFirstTrain(false)
{
	this->pModel = new CvNormalBayesClassifier();
	this->isFirstTrain = false;
}


MyBayesAlgorithms01::~MyBayesAlgorithms01(void)
{
	this->pModel->~CvNormalBayesClassifier();
}


// ��ʼ��ϵͳ--�����û�ѡ��ͼƬ������
//int MyBayesAlgorithms01::initSystem(void)
//{
//	return 0;
//}


// �����������ļ�


void MyBayesAlgorithms01::putPositiveFile(std::string& filePath)
{
	this->m_positiveFilePath.push_back(filePath);
	
}


// �������ļ�
void MyBayesAlgorithms01::putNegativeFile(std::string& filePath)
{
	this->m_negativeFilePath.push_back(filePath);
}


// ��ȡ����
void MyBayesAlgorithms01::train(void)
{
	vector<float> trainingData;
	vector<int> labels;
	for (int i = 0;i< this->m_positiveFilePath.size();i++)
	{
		vector<float> temp = Feature::get_colHis(this->m_positiveFilePath[i].c_str());
		for (int i = 0;i<temp.size();i++)
		{
			trainingData.push_back(temp[i]);
		}
		labels.push_back(1);
	}

	printf("--- trainingData end -------\n");
	for (int i = 0;i<this->m_negativeFilePath.size();i++)
	{
		vector<float> temp = Feature::get_colHis(this->m_negativeFilePath[i].c_str());
		for (int i = 0;i<temp.size();i++)
		{
			trainingData.push_back(temp[i]);
		}
		labels.push_back(-1);
	}

	printf("--- trainingData end -------\n");
	CvMat trainingDataMat;

	CvMat labelsCvMat;
	int length = this->m_positiveFilePath.size()+this->m_negativeFilePath.size();

	//CvMat trainingDataMat;
	cvInitMatHeader(&trainingDataMat,length,300,CV_32FC1,&trainingData[0]);
	//CvMat labelsCvMat;
	cvInitMatHeader(&labelsCvMat,length,1,CV_32SC1,&labels[0]);
	printf("--- length end -------\n");

	printf("---Train start -------\n");
	if (!isFirstTrain)
	{
		this->pModel->train(&trainingDataMat,&labelsCvMat,NULL,NULL,false);
		isFirstTrain = true;
	}else{
		//���Խ�������ʹ��
		this->pModel->train(&trainingDataMat,&labelsCvMat,NULL,NULL,true);
		//this->pModel->train(&trainingDataMat,&labelsCvMat,NULL,NULL,false);
	}

	//model.train(&this->trainingDataMat,&this->labelsCvMat,NULL,NULL,false);
	printf("--- train end -------\n");
	cleanFeedBackData();
	/*m_positiveFilePath.clear();
	m_negativeFilePath.clear();*/
}


// ��ʼѵ��
//void MyBayesAlgorithms01::startTrain(void)
//{
//	//printf("---Train start -------\n");
//	////this->model.train(&this->trainingDataMat,&this->labelsCvMat,NULL,NULL,false);
//	//this->pModel->train(&this->trainingDataMat,&this->labelsCvMat,NULL,NULL,false);
//	//printf("--- startTrain end -------\n");
//}



// ʶ��ͼƬ
float MyBayesAlgorithms01::predict(std::string& filePath)
{
	CvMat sampleMat;
	std::vector<float> sampleVec = Feature::get_colHis(filePath.c_str());
	cvInitMatHeader(&sampleMat,1,300,CV_32FC1,&sampleVec[0]);
	printf("---predict start -------\n");
	float response = this->pModel->predict(&sampleMat);
	printf("---predict end -------\n");
	return response;
}


// ��շ�������
void MyBayesAlgorithms01::cleanFeedBackData(void)
{
	this->m_negativeFilePath.clear();
	this->m_positiveFilePath.clear();
}
