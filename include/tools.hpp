#pragma once

namespace nvec{
	template <typename T>
	T min(const T& a, const T& b){
		if(a > b){return a;}
		else{return b;}
	}

	template <typename T, size_t size>
	auto subarray(T src[size], int begin = 0, int end = -1){
		size_t _begin, _end;
		if (begin < 0){
			_begin = size - begin; 
		}else{
			_begin = begin;
		}
		if(end < 0){
			_end = size - end;
		}else{
			_end = end;
		}
		if(_end < _begin){
			return {};
		}else{
			auto result = new T[_end - _begin + 1];
			for(size_t pose = _begin; pose < _end; ++pose){
				result[pose - _begin] = src[pose];
			}
			return result;
		}
	};
}