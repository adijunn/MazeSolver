# MazeSolver
Solve the maze problem with the image input using OpenCV image processing library and Djikstra graph short path algorithm


In this project, we have an image from a maze problem as the input. After binarization of the image, the skeleton of the image is found by "thinning.cpp". It means that we remove the true pixels until the paths remain with just one pixel thickness.
Then we should find the "Enter" and "Exit" points of the maze problem. For this reason, it is just necessary to find the Endpoints of the paths in the borders of the image. So the outer pixels in the border of the image is filled with True values so that the "Enter" and "Exit" point can be findable as the endpoint. Then "endpoints.cpp" is used to find them. Two points in the borders of the image are acceptable as "Enter" and "Exit".
After that, we use "DjikstraShortPath.cpp" to find the shortest path between "Enter" and "Exit" points. in this function, we model the skeleton binary image as a graph. True pixels are the nodes of the graph and there is an edge between that pixel and true pixels in its 8-connected neighborhood. It is obvious that in this project, the weights of the edges should be equal (I assumed them 1), but you can change them to make some heuristic and difficult Maze Solvers (yeah, Fork this repository to do that!).
The best path between "Enter" and "Exit" Points of the maze problem is saved in a vector of cv::Point (OpenCV object for pixel point of the image). I visualized it in the OpenCV image viewer that a red line starts from the "Enter" point toward the "Exit".

To run this project, first, you should install and include OpenCV library (Download from here: https://opencv.org/)
Feel free to ask your questions about this project (and everything else about the world, if I know about it!): P.ghasemi94 AT gmail DOT com

Peyman Ghasemi - January 2018 - Tehran, Iran
