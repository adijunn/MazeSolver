#include "endpoints.h"

namespace pgcv {
	void endpoints(cv::Mat img, std::vector<cv::Point>& endP) {

		cv::Mat Filtered , endpImg;
		cv::Mat kernel = cv::Mat::zeros(cv::Size(3, 3), CV_8U);
		
		//kernel of filter for endpoints
		int kern_data[9] = { 1 , 1 , 1 , 1 , 10 , 1 , 1 , 1 , 1 };
		for (int i = 0; i < 9; i++) {
			kernel.data[i] = kern_data[i];
		}
		int src_depth = -1;
		cv::filter2D(img/255, Filtered, src_depth, kernel); //apply endpoints kernel to skeleton image

		endpImg = (Filtered == 11); //values of 11 are the endpoint pixels
		cv::findNonZero(endpImg, endP); //endpoint locations to a vector of points



	}


}
//BY: PEYMAN GHASEMI - DECEMBER 2017 - TEHRAN - IRAN