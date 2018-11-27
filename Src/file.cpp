#include "file.h"


std::string File::obtn(std::string path){
	std::string value;
	std::ifstream shader;
	try
	{
		shader.open(path);
		std::stringstream stream;
		// Read file's buffer contents into streams
		stream << shader.rdbuf();
		shader.close();
		// Convert stream into string
		value = stream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	for (char c : value){
		std::cout << c;
	}
	return value;

}

