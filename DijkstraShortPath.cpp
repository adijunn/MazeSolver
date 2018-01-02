#include "DijkstraShortPath.h"



/*
This function (---- DijkstraShortPath ----) can find the shortest path in a binary image using Dijkstra Algorithm.
It Converts the binary image to a graph and then find the shortest path between two selected pixels.
Dijkstra Graph Short Path Algorithm From:
http://rosettacode.org/wiki/Dijkstra%27s_algorithm#C.2B.2B

Peyman Ghasemi - December 2017 - Tehran - Iran
*/
typedef int vertex_t;
typedef double weight_t;

const weight_t max_weight = std::numeric_limits<double>::infinity();

struct neighbor {
	vertex_t target;
	weight_t weight;
	neighbor(vertex_t arg_target, weight_t arg_weight)
		: target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;


void DijkstraComputePaths(vertex_t source,
	const adjacency_list_t &adjacency_list,
	std::vector<weight_t> &min_distance,
	std::vector<vertex_t> &previous)
{
	int n = adjacency_list.size();
	min_distance.clear();
	min_distance.resize(n, max_weight);
	min_distance[source] = 0;
	previous.clear();
	previous.resize(n, -1);
	std::set<std::pair<weight_t, vertex_t> > vertex_queue;
	vertex_queue.insert(std::make_pair(min_distance[source], source));

	while (!vertex_queue.empty())
	{
		weight_t dist = vertex_queue.begin()->first;
		vertex_t u = vertex_queue.begin()->second;
		vertex_queue.erase(vertex_queue.begin());

		// Visit each edge exiting u
		const std::vector<neighbor> &neighbors = adjacency_list[u];
		for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
		neighbor_iter != neighbors.end();
			neighbor_iter++)
		{
			vertex_t v = neighbor_iter->target;
			weight_t weight = neighbor_iter->weight;
			weight_t distance_through_u = dist + weight;
			if (distance_through_u < min_distance[v]) {
				vertex_queue.erase(std::make_pair(min_distance[v], v));

				min_distance[v] = distance_through_u;
				previous[v] = u;
				vertex_queue.insert(std::make_pair(min_distance[v], v));

			}

		}
	}
}


std::vector<vertex_t> DijkstraGetShortestPathTo(
	vertex_t vertex, const std::vector<vertex_t> &previous)
{
	std::vector<vertex_t> path;
	for (; vertex != -1; vertex = previous[vertex])
		path.push_back(vertex);
	std::reverse(path.begin(), path.end());
	return path;
}

namespace pgcv {
	void DijkstraShortPath(cv::Mat InputBWImage , cv::Point Start , cv::Point End , std::vector<cv::Point>& Result)
	{

		cv::Mat bw = InputBWImage;
		if (bw.at<uchar>(Start) != 255 || bw.at<uchar>(End) != 255) { //error if start or end point is not proper
			std::cerr << "ERROR: Start or End Point Is not Located on the Path..." << std::endl;
			std::getchar();
			std::exit(0);
		}

		// extract the white points as the graph nodes
		std::vector<cv::Point> nodes;
		cv::findNonZero(bw, nodes);

		// save index of each white point in the vector on the corresponding pixel in other Image
		cv::Mat Index_of_nodes = cv::Mat::zeros(bw.size(), CV_32S); //save index of each node in the corresponding pixel
		for (int pidx = 0; pidx < nodes.size(); pidx++) {
			Index_of_nodes.at<int>(nodes[pidx]) = pidx;
		}

		//now check the neighborhood of each node and save find the edges
		adjacency_list_t adjacency_list(nodes.size());

		for (int n = 0; n < nodes.size(); n++) {
			cv::Point node = nodes[n];

			for (int Nx = -1; Nx < 2; Nx++) {
				for (int Ny = -1; Ny < 2; Ny++) {
					if (Ny != 0 || Nx != 0) { //do not check the node itself

						//define the neighbor pixel
						cv::Point neighborP;
						neighborP.x = node.x + Nx;
						neighborP.y = node.y + Ny;

						cv::Rect rect(cv::Point(), bw.size());
						if (rect.contains(neighborP)) { //if the point is inside the image

							if (bw.at<uchar>(neighborP) == 255) { //if neighbor is TRUE
								int index = Index_of_nodes.at<int>(neighborP); //return the name of the node for this pixel
								adjacency_list[n].push_back(neighbor(index, 1)); //write the name of the node in the list
							}
						}
					}
				}
			}
		}


		// Define the Start and End Points of the Node
		int StartNode = Index_of_nodes.at<int>(Start);
		int EndNode = Index_of_nodes.at<int>(End);


		// Do Dijkstra Short Path Algorithm
		std::vector<weight_t> min_distance;
		std::vector<vertex_t> previous;
		DijkstraComputePaths(StartNode, adjacency_list, min_distance, previous);
		std::vector<vertex_t> path = DijkstraGetShortestPathTo(EndNode, previous);

		// Reconstruct the Image Pixels from the Path nodes
		for (int pn = 0; pn < path.size(); pn++) { //for each element of the path list
			int pnt = path[pn]; //node number in the path
			cv::Point pixel = nodes[pnt]; //corresponding pixel to the node
			Result.push_back(pixel);

		}
	}
}


//BY: PEYMAN GHASEMI - DECEMBER 2017 - TEHRAN - IRAN.