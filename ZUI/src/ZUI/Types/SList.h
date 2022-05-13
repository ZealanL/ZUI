#pragma once
#include "../Framework.h"

namespace ZUI {
	// A list with an unchanging size
	template <typename T>
	class SList {
	private:
		T* _data;
		int _size;
	public:

		const int& size = _size;

		SList() {
			_size = 0;
			_data = NULL;
		}

		SList(const T* begin, int size) {
			_size = size;
			_data = (T*)malloc(size * sizeof(T));
			memcpy(_data, begin, GetDataAllocSize());
		}

		SList(std::initializer_list<T> data) : SList(data.begin(), data.size()) {}
		SList(const SList& other) : SList(other._data, other._size) {}

		T& operator[](int index) {
			ZUI_ASSERT(index, _size);
			return _data[index];
		}

		const T& operator[](int index) const {
			ZUI_ASSERT(index, _size);
			return _data[index];
		}

		// size * sizeof(T)
		int GetDataAllocSize() const {
			return _size * sizeof(T);
		}

		bool IsEmpty() const {
			return _size == 0;
		}

		~SList() {
			if (_data)
				free(_data);
		}

		// For C++ iterator
		T* begin() const { return IsEmpty() ? NULL : _data; }
		T* end() const { return IsEmpty() ? NULL : _data + GetDataAllocSize(); }
	};
}