#include <iostream>
#include <memory>

// smart pointers

// unique_ptr

// application of type erasure in shared_ptr

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    explicit UniquePtr(T* ptr): ptr(ptr){}
    ~UniquePtr() {
        delete ptr;
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& another) noexcept: ptr(another.ptr) {
        another.ptr = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& another) {
        delete ptr;
        ptr = another.ptr;
        another.ptr = nullptr;
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

};


// shared_ptr

template <typename T>
class SharedPtr {
private:
    T* ptr;
    size_t* counter;
    
    void* deleter = nullptr;

    struct DeleterBase {
        virtual void operator()(void*);
        virtual ~DeleterBase() {}
    };

    template <typename U>
    struct DeleterDerived : public DeleterBase {
        U deleter;
        DeleterDerived(const U& deleter): deleter(deleter) {}
        void operator()(void* ptr) override {
            deleter(ptr);
        }
    };

    template <typename U>
    struct ControlBlock {
        size_t shared_counter;
        size_t weak_counter;
        U object;
    };

    template <typename U>
    class WeakPtr;

    ControlBlock<T>* cptr = nullptr;

    template <typename U, typename... Args>
    friend SharedPtr<U> make_shared(Args&&... args);

    struct make_shared_t;

    template <typename... Args>
    SharedPtr(make_shared_t, ControlBlock<T>* storage_ptr): cptr(storage_ptr) {}

public:
    SharedPtr() {}

    explicit SharedPtr(T* ptr): 
        ptr(ptr), counter(new size_t(1)) {
        if constexpr (std::is_base_of_v<enable_shared_from_this<T>, T>) {
            //ptr->wptr = /* ... */;
        }
    }

    SharedPtr(const SharedPtr& other) noexcept: //копирование
        ptr(other.ptr), counter(other.counter) {
        ++*counter;
    }

    SharedPtr(SharedPtr&& other) noexcept : //перемещение
        ptr(other.ptr), counter(other.counter) {
        other.ptr = nullptr;
        other.counter = nullptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    size_t use_count() const {
        return *counter;
    }

    /*~SharedPtr() {
        --cptr->shared_counter;

        if (cptr->shared_counter > 0) {
            return;
        }

        if (cptr->weak_counter == 0) {
            delete cptr;
            return;
        }

        cptr->object.~T();
    }*/

    ~SharedPtr() {
        if (!counter) return;

        --* counter;
        if (*counter == 0) {
            delete ptr;
            delete counter;
        }

        delete counter;
    }

    template <typename T, typename... Args>
    friend SharedPtr<T> make_shared(Args&&... args);

};


// allocate_shared
template <typename T, typename Alloc, typename... Args>
SharedPtr<T> allocate_shared(Alloc& alloc, Args&&... args) {
    //
}

// make_shared (since c++11)

template <typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args) {
    void* ptr = ::operator new(sizeof(T) + sizeof(size_t));
    new(ptr) T(std::forward<Args>(args)...);
    \return SharedPtr<T>(ptr);
    //return allocate_shared(&&Args... args);
    /*auto ptr = new ControlBlock<T>{1, T{std::forward<Args>(args)...}};
    return SharedPtr<T>(SharedPtr::make_shared_t(), ptr);*/
    /*auto ptr = new T(std::forward<Args>(args)...);
    return SharedPtr<T>(ptr);*/
}

// make_unique

/*template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}


int f1(int x) {
    //...
    if (x == 1) {
        throw std::runtime_error("aaaa!");
    }
    return result;
}

void g(const UniquePtr<int>& ptr, int x) {
    //...
}*/

void f(int x) {
    int* p = new int(5);

    if (x == 0) {
        throw 1;
    }


}


// weak_ptr

template <typename T>
class WeakPtr {
    ControlBlock<U>* cptr = nullptr;
public:
    WeakPtr(const SharedPtr<T>& ptr):
            cptr(ptr.cptr) {}

    bool expired() const {
        return cptr->shared_counter > 0;
    }

    SharedPtr<T> lock() const {

    }

    ~WeakPtr() {
        --cptr->weak_count;
        if (cptr->shared_counter == 0 && cptr->weak_counter == 0) {
            // deallocate
        }
    }
};


// enable_shared_from_this
// Curiously Recursive Template Pattern

template <typename T>
class enable_shared_from_this {
private:
    WeakPtr<T> wptr;

    template <typename U>
    friend class SharedPtr;


public:
    SharedPtr<T> shared_from_this() const {
        return wptr.lock();
    }
};


struct S : public enable_shared_from_this<S> {
    int x = 0;
    std::string str;

    S(int x, const std::string& str): x(x), str(str) {}

    SharedPtr<S> get_ptr() const {
        return shared_from_this();
    }
};


// alloc_shared

template <typename T, typename Alloc, typename... Args>
SharedPtr<T> allocate_shared(Alloc alloc, Args&&... args) {

}

int main()
{
    std::cout << "Hello World!\n";

    //auto sp = make_shared<S>(5, "abc");
}