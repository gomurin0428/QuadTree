#pragma once
#include <vector>
#include <set>

namespace QTree {
	class QuadTree 
	
	{
	public:
		// dim��15�ȉ���z�肵�Ă���B
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

		// �f�[�^��ǉ�����֐�
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




		// _x_min����_x_max,_y_min����_y_max�͈̔͂ɂ���f�[�^��2^_dim�����������̐V�������W��Ԃ��֐�
		std::pair<uint16_t, uint16_t> convertPoint(int x, int y) {
			return std::make_pair(x, y);
		}

		uint32_t BitSeparate32(uint32_t n);
		// ���W���烂�[�g���ԍ����v�Z���A�Ԃ��֐�
		uint32_t GetMortonNumber32(uint16_t x, uint16_t y);

		// �w�肳�ꂽ���[�g���ԍ��̃Z���̃C���f�b�N�X�����߂�֐��B
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