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
	// 放入负反馈文件路径
	virtual void putNegativeFile(std::string& filePath);
	// 识别图片
	virtual float predict(std::string& filePath);
	// 清空反馈数据
	void cleanFeedBackData(void);
	std::vector<std::string> m_negativeFilePath;
	std::vector<std::string> m_positiveFilePath;
	// 训练
	virtual void train(void);
};

