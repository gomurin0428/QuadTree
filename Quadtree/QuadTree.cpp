// Quadtree.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "QuadTree.h"

int main()
{
	QTree::QuadTree qtree(8,0,256,0,256);
	qtree.addData(0, 0);
	std::cout << qtree.getIndexFromMortonNumber(45) << std::endl;


}

namespace QTree {

	void QuadTree::addData(int x, int y) {
		// とりあえず最初は重複を許さないようにする。
		if (_points_set.count(std::make_pair(x, y)) == 0) {
			_points.push_back(std::make_pair(x, y));
			_points_set.insert(std::make_pair(x, y));
			std::pair<uint16_t,uint16_t> converted_point = convertPoint(x, y);
			uint32_t morton_number = GetMortonNumber32(converted_point.first, converted_point.second);
			uint32_t index = getIndexFromMortonNumber(morton_number);
			Node node(_dim, morton_number, true, std::make_pair(x,y));
			_points_in_cell[index].push_back(node);
		}
	}



	uint32_t QuadTree::getIndexFromMortonNumber(uint32_t morton_number) {
		int count = 0;
		uint32_t tmp = morton_number;
		while (tmp != 0) {
			tmp = tmp >> 2;
			count++;
		}
		int depth = count;

		if (depth == 0) {
			return 0;
		}

		uint32_t index = ((1 << (2 * depth)) - 1) / 3;
		return index+morton_number;
	}

	uint32_t QuadTree::BitSeparate32(uint32_t n) {
		n = (n | (n << 8)) & 0x00ff00ff;
		n = (n | (n << 4)) & 0x0f0f0f0f;
		n = (n | (n << 2)) & 0x33333333;
		return (n | (n << 1)) & 0x55555555;
	}

	uint32_t QuadTree::GetMortonNumber32(uint16_t x, uint16_t y) {
		return (BitSeparate32(x) | (BitSeparate32(y) << 1));
	}

 

}