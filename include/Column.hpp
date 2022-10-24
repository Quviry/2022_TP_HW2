namespace nvec{

	template <typename T>
	class Column{
	public:
		Column();
		Column(const T* src, size_t size){
			this->size = size;
			this->data = new T[size];
			for(int i = 0; i < size; ++i){
				this->data[i] = src[i];
			}
		}

		template <size_t size>
		Column(const T (&src)[size]){
			this->size = size;
			this->data = new T[size];
			for(int i = 0; i < size; ++i){
				this->data[i] = src[i];
			}
		}

		T operator[](int pos){
			return this->data[pos];
		}
		~Column(){
			delete this->data;
		};
		std::string to_string(){
			std::string result = "";
			for(size_t i = 0; i < size; ++i){
				result +=  std::to_string(data[i]) + " ";
			}
			return result;
		}
		const size_t get_size(){
			return size;
		}
		
	private:
		T* data;
		size_t size;
	};
}