#pragma once
#ifndef DIJKSTRASHORTPATH_H
#define DIJKSTRASHORTPATH_H

#include <iostream>
#include <vector>
#include <string>
#include <list>

#include <limits> // for numeric_limits

#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

#include <opencv2\opencv.hpp> //image processing


namespace pgcv {
	void DijkstraShortPath(cv::Mat InputBWImage, cv::Point Start, cv::Point End, std::vector<cv::Point>& Result);
}


#endif
