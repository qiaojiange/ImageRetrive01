#include "StdAfx.h"
#include "FeatureEx.h"


FeatureEx::FeatureEx(void)
{
	this->query = NULL;
	score = 0.0f;
}
FeatureEx::FeatureEx(Feature* query,std::string filePath ){
	if (NULL == query )
	{
		MessageBox(NULL,_T("请选择目标图片！！！"),_T("提醒"),MB_OK | MB_ICONWARNING);
	}
	if ( filePath.empty())
	{
		MessageBox(NULL,_T("文件路径无效！！！"),_T("提醒"),MB_OK | MB_ICONWARNING);
	}
	this->query = query;
	this->filePath = filePath;

	this->pOwner = new Feature();
	pOwner->img = cvLoadImage(this->filePath.c_str(),1);
	memset(pOwner->col_hist,0,sizeof(pOwner->col_hist));
	memset(pOwner->col_moment,0,sizeof(pOwner->col_moment));
	pOwner = pOwner->get_colMoment(pOwner);
	pOwner = pOwner->get_colHis(pOwner);
	pOwner = pOwner->get_directionality(pOwner);
	pOwner = pOwner->get_contrast(pOwner);

	calSimilarity();

	//delete(pOwner);
}


FeatureEx::~FeatureEx(void)
{
	delete(this->pOwner);
}


// 计算相似度
void FeatureEx::calSimilarity(void)
{
	float score_hist=0.0, score_moment=0.0, score_texture=0.0;
   float score_color;
  // float score;
   float sum1_hist=0.0, sum1_moment=0.0;
   float sum2_hist=0.0, sum2_moment=0.0;
   float sum_texture1=0.0, sum_texture2=0.0;
   int i,j;
   int i1, j1;


   for(i=0;i<300;i++){
	   sum1_hist=sum1_hist+pow(this->query->col_hist[i]*1.0,2);
	   sum2_hist=sum2_hist+pow(pOwner->col_hist[i]*1.0,2);
   }

   sum1_hist=sqrt(sum1_hist);
   sum2_hist=sqrt(sum2_hist);

   for(i1=0;i1<300;i1++){
	   score_hist=score_hist+((this->query->col_hist[i1])*1.0/sum1_hist)*((pOwner->col_hist[i1])*1.0/sum2_hist);
   }

   for(j=0;j<9;j++){
	   sum1_moment=sum1_moment+pow((this->query->col_moment[j])*1.0,2);
	   sum2_moment=sum2_moment+pow((pOwner->col_moment[j])*1.0,2);
   }

   sum1_moment=sqrt(sum1_moment);
   sum2_moment=sqrt(sum2_moment);

   for(j1=0;j1<9;j1++){
	   score_moment=score_moment+((this->query->col_moment[j1])*1.0/sum1_moment)*((pOwner->col_moment[j1])*1.0/sum2_moment);
   }

   sum_texture1=sqrt(pow((this->query->f_con)*1.0,2)+pow((this->query->f_dir)*1.0,2));
   sum_texture2=sqrt(pow((pOwner->f_con)*1.0,2)+pow((pOwner->f_dir)*1.0,2));

   score_texture=((this->query->f_con)*1.0/sum_texture1)*((pOwner->f_con*1.0)/sum_texture2)+((this->query->f_dir)*1.0/sum_texture1)*((pOwner->f_dir)*1.0/sum_texture2);


   score_color=0.6*score_hist+0.4*score_moment;
   this->score=0.6*score_texture+0.4*score_color;
 /*  printf("color:%g\n",score_color);
   printf("texture:%g\n",score_texture);*/
  
}
