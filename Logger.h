#pragma once
#include <shared_mutex>
#include <fstream>
#include <iostream>
#include <string>		// ��� std::getline


class Logger
{
private:
	std::string file_name;			// ���� ����
	std::ofstream fs_out;
	std::ifstream fs_in;
	std::string log_message;		// �����
	size_t log_message_quantity;	// ���������� ��������� � ���� � ����� ���������� ���������

public:
	Logger();

	Logger(Logger& other_logger) noexcept;
	Logger(Logger&& logger) noexcept;

	~Logger();

	std::shared_mutex sh_m_out;
	std::shared_mutex sh_m_in;

	void logMessageWrite(const std::string& message);	// ������ ����� �������

	void logMessageRead(size_t log_message_num);		// ������ ����� �������

	void logFileRead();									// ������ ����� �����
};