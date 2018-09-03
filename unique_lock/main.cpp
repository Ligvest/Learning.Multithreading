#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void printRect(char c) {	
	std::unique_lock<std::mutex> ul(mtx, std::defer_lock);

	ul.lock();
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 5; ++j) {
			std::cout << c;
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
		std::cout << std::endl;
	} 
	std::cout << std::endl;	
}


int main() {
	std::thread tS(printRect, '#');

	std::thread tA(printRect, '*');

	for (int i = 0; i < 10; ++i) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//	std::cout << "From main" << std::endl;
	}


	tS.join();
	tA.join();	
	system("pause");
	return 0;
}