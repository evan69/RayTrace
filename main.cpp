#include "all.h"

using namespace cv;
using std::string;

Mat colorim(600,800,CV_8UC3);

//#define OUTPUT
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
#ifdef OUTPUT
	string name = "output_";
	char* htime = new char[100];
	gcvt((double)(end - start) / CLOCKS_PER_SEC,6,htime);
	name += string(htime);
	name += string("s.png");
	imwrite(name.c_str(),colorim);
#endif
	waitKey(0);
	return 0;
}