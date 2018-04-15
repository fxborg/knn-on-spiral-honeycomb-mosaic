#include "hexgrid.h"
#include <iostream>
#include <vector>

using namespace hex;

void test(double radius, Layout layout, vector<Point> pt)
{
	HexGrid hexgrid(radius, layout);

	std::cout << "point(x, y)\t center(q, r, s) \t hexagon(q, r, s)" << std::endl;
	for (int i = 0; i < int(pt.size()); i++)
	{
		Hexagon hex = hexgrid.pixel_to_hex(pt[i]);
		Hexagon grid = hexgrid.round_hex(hex.q(), hex.r(), hex.s());

		hexgrid.add_point(grid, pt[i]);
		std::cout << pt[i].x << ", " << pt[i].y << "\t\t" << grid.q() << ", " << grid.r() << ", " << grid.s() << "\t\t" << hex.q() << ", " << hex.r() << ", " << hex.s() << std::endl;
	}
}

void neigbor(double radius, Layout layout, std::vector<std::vector<double>> src, const Hexagon & target, double distnace) {
	HexGrid hexgrid(radius, layout);
	for (auto it = begin(src); it != end(src); ++it) {
		Hexagon hex(it->at(0), it->at(1));
		Point pt = hexgrid.hex_to_pixel(hex);
		hexgrid.add_point(hex, pt);
		//	std::cout << pt.x << ", " << pt.y << std::endl;
	}

	auto result = hexgrid.neighbors(target, distnace);
	for (auto it = begin(result); it != end(result); ++it) {
		if (it->second.size() > 0) {
			for (auto h = begin(it->second); h != end(it->second); ++h) {
				std::cout << it->first << ":" << h->q() << ", " << h->r() << ", " << h->s() << std::endl;
			}
		}

	}

}

int main() {

	Hexagon test_target(-2, 3);
	double distance = 2.5;
	std::vector<std::vector<double>> src{ { 0,0 },{ 0,-1 },{ -1,0 },{ -1,1 },{ 0,1 },{ 1,0 },{ 1,-1 },{ -2,-1 },{ -2,-2 },{ -3,-1 },{ -3,0 },{ -2,0 },
	{ -1,-1 },{ -1,-2 },{ -3,2 },{ -3,1 },{ -4,2 },{ -4,3 },{ -3,3 },{ -2,2 },{ -2,1 },{ -1,3 },{ -1,2 },{ -2,3 },
	{ -2,4 },{ -1,4 },{ 0,3 },{ 0,2 },{ 2,1 },{ 2,0 },{ 1,1 },{ 1,2 },{ 2,2 },{ 3,1 },{ 3,0 },{ 3,-2 },{ 3,-3 },
	{ 2,-2 },{ 2,-1 },{ 3,-1 },{ 4,-2 },{ 4,-3 },{ 1,-3 },{ 1,-4 },{ 0,-3 },{ 0,-2 },{ 1,-2 },{ 2,-3 },{ 2,-4 },
	{ -8,3 },{ -8,2 },{ -9,3 },{ -9,4 },{ -8,4 },{ -7,3 },{ -7,2 },{ -10,2 },{ -10,1 },{ -11,2 },{ -11,3 },
	{ -10,3 },{ -9,2 },{ -9,1 },{ -11,5 },{ -11,4 },{ -12,5 },{ -12,6 } };

	vector<Point> pt{ Point(1, 1), Point(1, 5), Point(5, 1),Point(5, 5),Point(3, 3) };
	std::cout << "Pointy Topped LAYOUT" << std::endl;
	std::cout << ">> Origin hex(" << test_target.q() << "," << test_target.r() << "," << test_target.s() << ")" << std::endl;
	std::cout << "Nearest Neighbors(" << distance << ") >>  " << std::endl;
	neigbor(1, Layout::VERTICAL, src, test_target, distance);
	std::cout << std::endl;

	std::cout << "FlatTopped LAYOUT" << std::endl;
	std::cout << ">> Origin hex(" << test_target.q() << "," << test_target.r() << "," << test_target.s() << ")" << std::endl;
	std::cout << "Nearest Neighbors(" << distance << ") >>  " << std::endl;

	neigbor(1, Layout::HORIZONTAL, src, test_target, distance);
	std::cout << std::endl;


	system("PAUSE");
	return 0;
}