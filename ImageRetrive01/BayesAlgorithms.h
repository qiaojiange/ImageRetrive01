#pragma once
#include <vector>
#include <string>
#include "opencv2/opencv.hpp"

class BayesAlgorithms
{
public:
	BayesAlgorithms(void);
	~BayesAlgorithms(void);
	virtual void putPositiveFile(std::string& filePath) = 0;
	// ���븺�����ļ�·��
	virtual void putNegativeFile(std::string& filePath);
	// ʶ��ͼƬ
	virtual float predict(std::string& filePath);
	// ��շ�������
	void cleanFeedBackData(void);
	std::vector<std::string> m_negativeFilePath;
	std::vector<std::string> m_positiveFilePath;
	// ѵ��
	virtual void train(void);
};

