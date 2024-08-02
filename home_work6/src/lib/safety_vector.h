#include <iostream>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <memory>

#include <vector>

template<typename T>
class safety_vector{
    public:
        safety_vector(){
            vector_ = std::vector<T>();
        }

        void push_back(const T& value){
                std::lock_guard<std::mutex> lck(m_);
                vector_.push_back(value);
        }

        T get(size_t index){
            std::lock_guard<std::mutex> lc(m_);
            return vector_.at(index);
        }
        
        size_t size() const{
           // std::lock_guard<std::mutex> lc(m_);
            return vector_.size();
        }
        void erase(size_t index){
            std::lock_guard<std::mutex> lc(m_);
            vector_.erase(vector_.begin()+index);
        }

    private:
	    std::mutex m_;
        std::vector<T> vector_;
};

