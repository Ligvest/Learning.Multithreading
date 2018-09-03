#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;

void printRectangle(char c) {
	mtx.lock();

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 10; ++j) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			std::cout << c;
		}
		std::cout << std::endl;
	}

	mtx.unlock();
}

int main() {
	std::thread tS(printRectangle, '#');
	std::cout << std::endl;
	std::thread tA(printRectangle, '*');

	tS.join();
	tA.join();
	system("pause");
	return 0;
}