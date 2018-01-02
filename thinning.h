#ifndef THINNING_H
#define THINNING_H

#include <opencv2/opencv.hpp>


namespace pgcv{
void thinning(const cv::Mat& src, cv::Mat& dst);
}

#endif