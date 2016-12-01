#include "StdAfx.h"
#include "BayesAlgorithms.h"


BayesAlgorithms::BayesAlgorithms(void)
{
}


BayesAlgorithms::~BayesAlgorithms(void)
{
}


// 放入负反馈文件路径
void BayesAlgorithms::putNegativeFile(std::string& filePath)
{
}


// 识别图片
float BayesAlgorithms::predict(std::string& filePath)
{
	return 0;
}


// 清空反馈数据
void BayesAlgorithms::cleanFeedBackData(void)
{
	m_negativeFilePath.clear();
	m_positiveFilePath.clear();
}


// 训练
void BayesAlgorithms::train(void)
{
}
