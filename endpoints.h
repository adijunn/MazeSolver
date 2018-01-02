#pragma once
#ifndef ENDPOINTS_H
#define ENDPOINTS_H

#include <opencv2\opencv.hpp>
#include <vector>
#include <iostream>

namespace pgcv {
	void endpoints(cv::Mat img, std::vector<cv::Point>& endP);
}

#endif