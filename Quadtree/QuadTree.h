#pragma once
#include <vector>
#include <set>

namespace QTree {
	class QuadTree 
	
	{
	public:
		// dimは15以下を想定している。
		QuadTree(int dim, int x_min, int x_max,int y_min, int y_max) {
			_dim = dim;
			_x_min = x_min;
			_x_max = x_max;
			_y_min = y_min;
			_y_max = y_max;
			for (int i = 0; i < (1 << (2 * (dim + 1) - 1)) / 3; i++) {
				std::vector<Node> tmp;
				_points_in_cell.push_back(tmp);
			}
		};
		~QuadTree() {
		};

		// データを追加する関数
		void addData(int x, int y);

		class Node {

			public:
			Node(int _depth, uint32_t _morton_number, bool _isPoint, std::pair<int,int> _center) {
				depth = _depth;
				morton_number = _morton_number;
				isPoint = _isPoint;
				center = _center;
			}
			int depth;
			uint32_t morton_number;
			bool isPoint;
			std::pair<int, int> center;
		};




		// _x_minから_x_max,_y_minから_y_maxの範囲にあるデータを2^_dim分割した時の新しい座標を返す関数
		std::pair<uint16_t, uint16_t> convertPoint(int x, int y) {
			return std::make_pair(x, y);
		}

		uint32_t BitSeparate32(uint32_t n);
		// 座標からモートン番号を計算し、返す関数
		uint32_t GetMortonNumber32(uint16_t x, uint16_t y);

		// 指定されたモートン番号のセルのインデックスを求める関数。
		uint32_t getIndexFromMortonNumber(uint32_t morton_number);

		int _dim;
		int _x_min;
		int _x_max;
		int _y_min;
		int _y_max;

		std::vector<std::pair<int, int>> _points;
		std::set<std::pair<int,int>> _points_set;
		std::vector<std::vector<Node>> _points_in_cell;

	};

}