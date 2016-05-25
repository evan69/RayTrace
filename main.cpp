#include "all.h"

using namespace cv;

Mat colorim(600,800,CV_8UC3);

int main()
{
	time_t start = clock();
	srand(time(NULL));
	HYF::Engine* tracer = new HYF::Engine();
	tracer->getScene()->init();
	tracer->setTarget();
	tracer->HYF_render(colorim);
	imshow("test",colorim);
	time_t end = clock();
	printf("time : %llf second\n",(double)(end - start) / CLOCKS_PER_SEC);
	waitKey(0);
	return 0;
}