#ifndef CV_SPATIALMETHODS_H
#define CV_SPATIALMETHODS_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"
//#include "opencv2/nonfree/nonfree.hpp"
//#include "opencv2/contrib/contrib.hpp"
#include "data_spatial.h"

class cv_spatialMethods
{
public:
    cv_spatialMethods();
    cv::Mat DS2Mat(data_spatial ds);
    data_spatial Mat2DS(cv::Mat mat);
};

#endif // CV_SPATIALMETHODS_H
