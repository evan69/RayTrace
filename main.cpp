#include "all.h"

using namespace cv;

Mat colorim(600,800,CV_8UC3);

int main()
{
	HYF::Engine* tracer = new HYF::Engine();
	tracer->getScene()->init();
	tracer->setTarget();
	tracer->HYF_render(colorim);
	imshow("test",colorim);
	waitKey(0);
	return 0;
}