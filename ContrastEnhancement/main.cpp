/*@Author:Tom Liao*/
#include "opencv2/opencv.hpp"
using namespace cv;
/*functionㄩ
*enhance the contrast of an image
inputㄩ
*[in]const Mat grayImg 每 a gray image
*[in]int nContrastPara - a parameter which controls the contrast,
*a smaller value produces higher contrat, default value is 5000
*[in] int nKernelSize - filter kernel szie
outputㄩ
*[out]vMat &enhancedImg 每 a contrast-enhanced image
returnㄩ
*0 每 valid;  -1 每 invalid
referenceㄩ
"Multiscale Local Contrast Enhancement"
*/
int enhanceContrast(const Mat grayImg, int nContrastPara, int nKernelSize, Mat &enhancedImg)
{
	if (nKernelSize % 2 == 0)
	{
		return -1;
	}
	Mat imgBlur = grayImg.clone();
	enhancedImg = Mat::ones(grayImg.rows, grayImg.cols, CV_8UC1);
	int size = grayImg.cols * grayImg.rows;

	blur(grayImg, imgBlur, Size(nKernelSize, nKernelSize));
	for (int i = 0; i < size; i++)
	{
		if (grayImg.data[i] > imgBlur.data[i])
		{
			enhancedImg.data[i] = (255 + nContrastPara / (grayImg.data[i] - imgBlur.data[i]))
				* grayImg.data[i] / (nContrastPara / (grayImg.data[i] - imgBlur.data[i]) + grayImg.data[i]);
		}
		else if (grayImg.data[i] < imgBlur.data[i])
		{
			enhancedImg.data[i] = (nContrastPara / (imgBlur.data[i] - grayImg.data[i]))
				* grayImg.data[i] / (nContrastPara / (imgBlur.data[i] - grayImg.data[i]) + 255 - grayImg.data[i]);
		}
		else
		{
			enhancedImg.data[i] = (255 + nContrastPara) * grayImg.data[i] / (nContrastPara + grayImg.data[i]);
		}
	}
	return 0;
}



//test enhanceContrast
int main()
{
	Mat srcImage = imread("r2a.jpg");
	namedWindow("srcImage", 1);
	imshow("srcImage", srcImage);
	waitKey(0);
	if (srcImage.channels() == 3)
	{
		cvtColor(srcImage, srcImage, CV_BGR2GRAY);
	}
	Mat dstImage;
	int ret = enhanceContrast(srcImage, 2000, 13, dstImage);
	if (ret == -1)
	{
		return 0;
	}
	namedWindow("dstImage", 1);
	imshow("dstImage", dstImage);
	waitKey(0);
	destroyAllWindows();
	return 0;
}