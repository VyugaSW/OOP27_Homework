#pragma once

template <typename T>
class unique_ptr {
	T* ptr;
public:
	// Constructors
	unique_ptr(T*ptr = nullptr) : this->ptr{ptr} {}
	unique_ptr(unique_ptr&& another) : ptr{another.ptr} // Moving
	{ another.ptr = nullptr;  }

	template <typename U>
	unique_ptr(unique_ptr<U>&& another) : ptr{ another.ptr } {
		another.ptr = nullptr;
		static_assert(std::is_convertible<T*, U*>::value, "Convertation is impossible\n");
	}
	

	// Prohibits
	unique_ptr(const unique_ptr&) = delete; // Prohibit copying
	unique_ptr& operator=(const unique_ptr) = delete; // Prohibit assignment


	// Operators
	unique_ptr& operator=(unique_ptr&& another) { // Assigment another ptr
		reset(another.release());
		return *this;
	}
	T& operator*() const { // Operator *
		return *ptr;
	}
	T& operator->() const { // Operator ->
		return ptr;
	}
	operator bool() const {  // Bool operator
		return ptr != nullptr;
	}

	template<typename U>
	unique_ptr& opertator= (unique_ptr<U> && another){ // Operator= convertible
		static_assert(std::is_convertible<T*, U*>::value, "Convertation is impossible\n");
		reset(another.release);
		return *this;
	}


	// Main functions
	T* release() {
		T* temp_ptr = ptr;
		ptr = nullptr;
		return temp_ptr;
	}
	void reset(T* ptr = nullptr) {
		if (ptr != this->ptr) {
			delete this->ptr;
			this->ptr = ptr;
		}
	}
	void swap(unique_ptr&& another) {
		swap(ptr, another);
	}
	T* get() const { return ptr; }


	// Destructor
	~unique_ptr() {
		delete ptr;
	}
};