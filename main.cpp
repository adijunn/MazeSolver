#include <opencv2\opencv.hpp> //image processing
#include <iostream>
#include <vector>
#include "thinning.h"
#include "endpoints.h"
#include "DijkstraShortPath.h"

void main() {
	cv::Mat im0 = cv::imread("C:\\Users\\Peyman\\Desktop\\maze.PNG", 0); //read image
	cv::resize(im0, im0, cv::Size(640, 480), 0, 0, CV_INTER_LINEAR); //Resize the image to 640x480
	cv::Mat bw;
	cv::threshold(im0, bw, 127, 255, CV_THRESH_BINARY); //binarize
	pgcv::thinning(bw, bw); //skeleton

	//clear the borders
	for (int r = 0; r < bw.rows; r++) {
		cv::Point P;
		P.x = 0;
		P.y = r;
		bw.at<uchar>(P) = 0;
		P.x = bw.cols-1;
		P.y = r;
		bw.at<uchar>(P) = 0;
	}
	for (int c = 0; c < bw.cols; c++) {
		cv::Point P;
		P.x = c;
		P.y = 0;
		bw.at<uchar>(P) = 0;
		P.x = c;
		P.y = bw.rows-1;
		bw.at<uchar>(P) = 0;
	}

	//find endpoints
	std::vector<cv::Point> endP;
	pgcv::endpoints(bw, endP);

	//find two main endpoints (two nearest endpoints to the borders of the image)
	cv::Point startPxl;
	cv::Point endPxl;

	int I_find_first_one = 0; //do you find it?
	for (int i = 0; i < endP.size(); i++) { 
		cv::Point P = endP[i];
		/*std::cout << P << std::endl;*/
		if (P.x == 1 || P.y == 1 || P.x==bw.cols-2 || P.y==bw.rows-2) { //if one of the endpoints is in the border of the image
			if (!I_find_first_one) {
				startPxl = P;
				I_find_first_one = 1; //yes I find it
			}
			else
				endPxl = P;
		}
	}


	std::vector<cv::Point> Result;
	pgcv::DijkstraShortPath(bw , startPxl , endPxl , Result); //Dijkstra algorithm for skeleton image


	//visualize in video
	std::cout << "HI" << std::endl << "Let's Solve the Maze!" << std::endl << "By: Peyman Ghasemi   P.Ghasemi94 [AT] Gmail [DOT] com" << std::endl;
	cv::Mat im;
	std::vector<cv::Mat> im2(3);
	im2[0] = im0;
	im2[1] = im0;
	im2[2] = im0;
	cv::merge(im2, im);

	for (int n = 0; n < Result.size(); n++) {
		im.at<cv::Vec3b>(Result[n])[0] = 0;
		im.at<cv::Vec3b>(Result[n])[1] = 0;

		cv::namedWindow("MazeSolver");
		cv::imshow("MazeSolver", im);
		cv::waitKey(1);
	}
	cv::waitKey(0);
}// BY: PEYMAN GHASEMI _ DECEMBER 2017 - TEHRAN_IRAN
// P.GHASEMI94 [AT] Gmail [DOT] com