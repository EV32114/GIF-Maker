#include <stdio.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>

int main()
{

	cvNamedWindow("Display window", CV_WINDOW_AUTOSIZE); //create a window
	IplImage* image = cvLoadImage("C:\\Users\\משתמש\\Pictures\\day.png", 1); //create an image. ***change to your image path***
	if (!image)//The image is empty. 
	{
		printf("could not open image\n");
	}
	else
	{
		cvShowImage("Display window", image);
		cvWaitKey(0); system("pause");
		cvReleaseImage(&image);
	}
	return 0;
}

