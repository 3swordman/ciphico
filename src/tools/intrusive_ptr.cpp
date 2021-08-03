#include <type_traits>
#include <iostream>
#include <atomic>
#include <cassert>
#include <inttypes.h>
struct enable_intrusive {
	std::atomic<int32_t> counter{0};
};

template <typename T>
class intrusive_ptr {
	T *raw_ptr;
public:
	intrusive_ptr(T *ptr = nullptr) : raw_ptr(ptr) {
	    static_assert(std::is_base_of<enable_intrusive, T>::value,"??? should be subclass of enable_intrusive");
	    if (raw_ptr != nullptr)
            ++raw_ptr->counter;
	};
	~intrusive_ptr() {
		if (raw_ptr != nullptr) {
			if (--raw_ptr->counter == 0) {
				delete raw_ptr;
			}
		}
	};
	operator T *() const {
        return raw_ptr; 
    }
    T& operator*() const {
        return *raw_ptr;
    }
    T *operator->() const {
        return raw_ptr;
    }
};

struct A : public enable_intrusive {
	int data = 5;
};

template <typename T, typename ...Ts>
intrusive_ptr<T> make_intrusive(Ts ...args) {
    return intrusive_ptr<T>(new T(std::forward<Ts>(args)...));
}


