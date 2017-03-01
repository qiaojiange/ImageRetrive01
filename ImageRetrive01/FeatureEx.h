#pragma once
#include "Feature.h"
#include <string>

class FeatureEx
{
public:
	FeatureEx(void);
	FeatureEx(Feature* query,std::string filePath );
	~FeatureEx(void);
private:
	Feature* query;
public:
	std::string filePath;
	float score;
private:
	Feature* pOwner;
public:
	// �������ƶ�
	void calSimilarity(void);
	bool operator() (FeatureEx& f1,FeatureEx& f2){
		return f1.score>f2.score;
	}
};

