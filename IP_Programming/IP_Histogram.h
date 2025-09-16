#pragma once
class CIP_Histogram
{
public:
	UCHAR** m_pucHistEqualImgBuf; // 히스토그램 평활화 이미지 저장 버퍼
public:
	CIP_Histogram(void);
	~CIP_Histogram(void);

	// 이미지의 히스토그램 계산
	void Histogram_MakeHistogram(UCHAR** HistImgbuf, float HistArray[256], int width, int height);

	// 히스토그램 평활화
	void Histogram_MakeHistogramEqualization(UCHAR** imgbuf, int width, int height);
	
	// 2D 메모리 할당
	UCHAR** memory_alloc2D(int width, int height);
};

