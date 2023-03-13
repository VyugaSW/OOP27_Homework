#pragma once


template <typename T>
class shared_ptr {
	T* ptr;
	static size_t* counter;
public:
	// Constructors
	shared_ptr(T* ptr = nullptr) this->ptr{ptr} {};
	shared_ptr(const shared_ptr& another) : ptr{ another.ptr } {*counter++;}
	shared_ptr(shared_ptr& another) : ptr{ another.ptr } { another.ptr == nullptr };


	// Operators
	operator=(shared_ptr&& another) {
		reset(another);
	}
	T* operator*() const { return *ptr; }
	T* operator->() const { return ptr };
	operator bool() { return ptr != nullptr; }


	//Functions
	size_t use_count() const {
		return *counter;
	}
	T& get() const {
		return ptr;
	}
	void reset(T* ptr = nullptr) {
		if (ptr != this->ptr) {
			delete this->ptr;
			this->ptr = ptr;
		}
	} // Reset :)
	bool unique() const {
		return *counter == 1;
	} // Object has one ptr

	// Destuctor
	~shared_ptr() {
		if (*counter > 1) {
			counter--;
			return;
		}
		delete ptr;
		delete counter;
	}
};
