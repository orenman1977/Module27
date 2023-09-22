/* Класс логгер */
#include "Logger.h"

Logger::Logger(): file_name("loggerLog.txt"), log_message_quantity(0) {
	fs_out.open(file_name, std::fstream::app);			// open file to write/append
	if (!fs_out.is_open()) {
		throw std::runtime_error("Error opening file out: " + file_name);
	}

	fs_in.open(file_name);
	if (!fs_in.is_open()) {
		throw std::runtime_error("Error opening file in: " + file_name);
	}
	else {
	
		while (std::getline(fs_in, log_message)) {
			++log_message_quantity;
		}
		fs_in.clear();		// сброс ошибки std::fstream (fs висит т.к. getline догнал его до EOF и FAIL)
	}
}

Logger::~Logger() {
	fs_out.close();
	fs_in.close();
}

void Logger::logMessageWrite(const std::string& message) {
	if (fs_out.is_open()) {
		sh_m_out.lock();
		++log_message_quantity;
		fs_out.seekp(std::fstream::end);
		fs_out << log_message_quantity << ".\t" << message << std::endl;
		sh_m_out.unlock();
	}	
}

void Logger::logMessageRead(size_t log_message_num) {		
	if (fs_in.is_open()) {
		if (log_message_num > log_message_quantity) return;
		sh_m_in.lock();
		fs_in.seekg(std::fstream::beg);
		for (size_t i = 0; i < log_message_num - 1; ++i) {
			fs_in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// перемотка до нужной строки
		}
		std::getline(fs_in, log_message);
		std::cout << log_message << std::endl;
		sh_m_in.unlock();
	}
}

void Logger::logFileRead() {
	if (fs_in.is_open()) {
		sh_m_in.lock();
		fs_in.seekg(std::fstream::beg);
		while (std::getline(fs_in, log_message)) {
			std::cout << log_message;
		}
		sh_m_in.unlock();
	}
}