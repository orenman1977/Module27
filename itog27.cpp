// itog27.cpp: исходный файл для целевого объекта.
//

#include "itog27.h"
#include <thread>
#include <sstream>
#include <vector>

void threadFunc(Logger& logger);

int main()
{
	std::vector<std::thread> threads;
	const size_t quantity_threads = 10;
	size_t counter = quantity_threads;
	Logger logger;
	do {
		threads.push_back(std::move(std::thread(threadFunc, std::ref(logger))));
	} while (--counter);

	for (auto& thread : threads) {
		if (thread.joinable()) thread.join();
	}
	return 0;
}

// поточная функция использующая логгер
void threadFunc(Logger& logger) {
	size_t quantity_log_messages = 10;
	std::stringstream ss;
	while (quantity_log_messages--) {
		ss << "Log message write from thread " << std::this_thread::get_id();
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));		// имитация бурной деятельности

		logger.logMessageWrite(ss.str());
		ss.ignore(std::numeric_limits<std::streamsize>::max());

		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));		// имитация бурной деятельности
		logger.logMessageRead(rand() % 10);
	}
}
