#ifndef MY_UNIQUE_PTR
#define MY_UNIQUE_PTR

#include <algorithm>
#include <iostream>



namespace hmwrk3{

    template <class T>
    class shared_ptr{
    
        private:
            T *raw_ptr = nullptr;
            long *used_count = nullptr;
        
        public:


        shared_ptr() noexcept = default;
        
        //Constructor
            explicit shared_ptr (T* raw_ptr):raw_ptr(raw_ptr){
                if(raw_ptr){
                    used_count = new long(1);
                }
            }
        //Copy constructor 
            shared_ptr(const shared_ptr &other)
                                : raw_ptr(other.raw_ptr)
                                , used_count(other.used_count){
                if(used_count){
                    ++*used_count;
                }
            }

        //Move constructor
            shared_ptr(shared_ptr&& other){
                std::swap(raw_ptr, other.raw_ptr);
                std::swap(used_count, other.used_count);
                other.delete_();

            }

        //Assignment operator
        shared_ptr& operator = ( const shared_ptr& other ) {
                if(this != &other){
                    shared_ptr tmp(other);
                    std::swap(raw_ptr, tmp.raw_ptr);
                    std::swap(used_count, tmp.used_count);
                }
                return *this;            
            }

        //Move assignment operator
        shared_ptr& operator = (shared_ptr&& other ) {
                std::swap(raw_ptr, other.raw_ptr);
                std::swap(used_count, other.used_count);
                other.delete_();
                return *this;            
            }

            ~shared_ptr(){
                delete_();
            }

            void delete_(){
                if(used_count){
                    if(--*used_count){
                        return;
                    }
                    else{
                        delete used_count;
                    }
                }
                if(raw_ptr){
                    delete raw_ptr;
                }
                used_count = nullptr;
                raw_ptr = nullptr;
            }


           /* shared_ptr& operator=(shared_ptr&& sp) noexcept {
                return *this;
            }*/


            T& operator * () const { return *raw_ptr; }

            T* operator -> () const { return raw_ptr; }

            long use_count() const noexcept { return *used_count; }

            T* get() const noexcept { return raw_ptr; }

            explicit operator bool() const noexcept{
                return raw_ptr != nullptr;
            }
    };
}

#endif