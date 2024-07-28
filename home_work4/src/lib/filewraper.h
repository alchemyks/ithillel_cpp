#include <string>
#include <functional>
#include <memory>
#include <fstream>





class FileWrapper
{
public:

	FileWrapper(const std::string& filename){
		file_ptr = std::unique_ptr<std::fstream, std::function<void(std::fstream *)>>(new std::fstream(filename, std::ios::app), 
																						[](std::fstream *fs){
																							if(fs->is_open()){
																								fs->close();
																							}
																						});
	}

	void write(const std::string& data){
		*file_ptr << data;
	}

	FileWrapper(const FileWrapper& other) = delete;


	explicit operator bool() const noexcept{ return file_ptr != nullptr;} // повертає False якщо файл не змогли створити.

	~FileWrapper(){
		if(file_ptr){
			if(file_ptr->is_open()){
				file_ptr->close();
			}
			file_ptr.reset(nullptr);
		}
		file_ptr = nullptr;
	}

private:

        std::unique_ptr<std::fstream, std::function<void(std::fstream *)>> file_ptr; 

};