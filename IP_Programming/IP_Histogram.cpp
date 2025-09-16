#include "pch.h"
// #include "stdafx.h" // mfc 구버전에서 이렇게 사용합니다
#include "IP_Histogram.h"

CIP_Histogram::CIP_Histogram(void)
	: m_pucHistEqualImgBuf(NULL)
{
}

CIP_Histogram::~CIP_Histogram(void)
{
	if (m_pucHistEqualImgBuf) {
		free(m_pucHistEqualImgBuf[0]);
		free(m_pucHistEqualImgBuf);
		m_pucHistEqualImgBuf = NULL;
	}
}

// 이미지의 히스토그램 계산
void CIP_Histogram::Histogram_MakeHistogram(UCHAR** HistImgbuf, float HistArray[256], int width, int height)
{
	// 8bit depth 임시 배열 생성
	int Image_Histogram[256] = { 0 };
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Image_Histogram[HistImgbuf[i][j]]++;
		}
	}

	// 히스토그램 정규화
	float Image_Area = (float)(height * width);
	for (int i = 0; i < 256; i++)
	{
		HistArray[i] = Image_Histogram[i] / Image_Area;
	}
}

// 히스토그램 평활화
void CIP_Histogram::Histogram_MakeHistogramEqualization(UCHAR** imgbuf, int width, int height)
{
	// 원본 영상의 히스토그램 생성
	float Image_Histogram[256] = { 0 };
	Histogram_MakeHistogram(imgbuf, Image_Histogram, width, height);

	// 히스토그램 누적 합 계산
	double CDF[256] = { 0.0 };
	CDF[0] = Image_Histogram[0];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			m_pucHistEqualImgBuf[i][j] = (UCHAR)(CDF[imgbuf[i][j]] * 255);
		}
	}
}

// 2D 메모리 할당
UCHAR** CIP_Histogram::memory_alloc2D(int width, int height)
{
	UCHAR** ppMem2D = 0;
	
	// 2차원 배열 메모리 할당
	ppMem2D = (UCHAR**)calloc(sizeof(UCHAR*), height);
	if (ppMem2D == 0) {
		return 0;
	}

	*ppMem2D = (UCHAR*)calloc(sizeof(UCHAR), height*width);
	if ((*ppMem2D) == 0) {
		free(ppMem2D);
		return 0;
	}

	for (int i = 0; i < height; i++)
	{
		ppMem2D[i] = ppMem2D[i - 1] + width;
	}
	return ppMem2D;
}