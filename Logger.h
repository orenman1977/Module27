#pragma once
#include <shared_mutex>
#include <fstream>
#include <iostream>
#include <string>		// для std::getline


class Logger
{
private:
	std::string file_name;			// файл лога
	std::ofstream fs_out;
	std::ifstream fs_in;
	std::string log_message;		// буфер
	size_t log_message_quantity;	// количество сообщений в логе и номер последнего сообщения

public:
	Logger();

	Logger(Logger& other_logger) noexcept;
	Logger(Logger&& logger) noexcept;

	~Logger();

	std::shared_mutex sh_m_out;
	std::shared_mutex sh_m_in;

	void logMessageWrite(const std::string& message);	// запись одной строчки

	void logMessageRead(size_t log_message_num);		// чтение одной строчки

	void logFileRead();									// чтение всего файла
};