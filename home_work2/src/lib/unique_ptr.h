#ifndef MY_UNIQUE_PTR
#define MY_UNIQUE_PTR


namespace hmwrk2{

template <class T>
class unique_ptr{
    
    private:
        T *raw_ptr = nullptr;
        
    public:
        unique_ptr(T* raw_ptr):raw_ptr(raw_ptr)
        {}

        ~unique_ptr(){ 
            delete raw_ptr;
            raw_ptr = nullptr;
            }

        T* operator -> () const { return raw_ptr; }

        T& operator * () const { return *raw_ptr; }

        T* get() const noexcept { return raw_ptr; }

        T& operator = ( const unique_ptr& r ) = delete;

        explicit operator bool() const noexcept{
            return raw_ptr != nullptr;
        }
};


}


#endif