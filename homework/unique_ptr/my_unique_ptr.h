#include <algorithm>

template<typename T>
class my_unique_ptr{
public:
    my_unique_ptr() noexcept = default;
    my_unique_ptr(std::nullptr_t) noexcept : my_unique_ptr() {}

    my_unique_ptr(const my_unique_ptr&) noexcept = delete;
    my_unique_ptr& operator=(const my_unique_ptr&) noexcept = delete;

    my_unique_ptr(my_unique_ptr&& other) noexcept {
        std::swap(ptr_, other.ptr_);
    }

    my_unique_ptr& operator=(my_unique_ptr&& other) noexcept {
        std::swap(ptr_, other.ptr_);
    }

    template<typename Type>
    explicit my_unique_ptr(Type* ptr) noexcept : ptr_{ptr} {}

    my_unique_ptr& operator=(T* ptr) {
        reset(ptr);
    }
    
    ~my_unique_ptr() {
        reset();
    }

    T* release () noexcept {
        T* result = ptr_;
        ptr_ = nullptr;
        return result;
    }

    void reset() noexcept {
        if(ptr_){
            delete ptr_;
            ptr_ = nullptr;
        }
    }
    void reset(std::nullptr_t) noexcept {
        reset();
    }
    void reset(T* ptr) noexcept {
        reset();
        ptr_ = ptr;
    }

    T* get() {
        return ptr_;
    }

    T& operator*() {
        return *ptr_;
    }

    T* operator->() {
        return ptr_;
    }

private:
    T* ptr_{nullptr};
};
