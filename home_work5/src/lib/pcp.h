#include <iostream>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

#include <vector>


class pcp {
public:

	void produce() {
        while(1){
		    {
			    std::lock_guard<std::mutex> lck(m_);
                if(!queue.empty() && !update){
		            update = true;
                    cv_.notify_one();
                }
		    }
        }
	}

	void consume() {
        while (1)
        {
    		std::unique_lock<std::mutex> lck(m_);
	    	cv_.wait(lck, [this] { return update;});
	    	if (update) {
		    	if(!queue.empty()){

                    std::cout << "update: new message from producer" << queue.front() << std::endl;
                    queue.pop();
                }
                else{
                    update = false;
                }
		    }
        }
	}

    void start(){
        std::thread thread_consumer(&pcp::consume, this);
        std::thread thread_producer(&pcp::produce, this);
        thread_consumer.detach();
        thread_producer.detach();

    }

    void add_task(int data){
        queue.push(data);
    }

private:
	std::mutex m_;
	std::condition_variable cv_;

    std::queue<int> queue;

	bool update{false};
};

