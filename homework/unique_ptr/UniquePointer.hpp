#pragma once

template <typename Type>
class UniquePointer {
private:
    Type* pointer_{nullptr};

public:
    UniquePointer() = default;
    UniquePointer(Type* pointer)
        : pointer_(pointer){};

    ~UniquePointer() noexcept {
        delete pointer_;
        pointer_ = nullptr;
    }
};