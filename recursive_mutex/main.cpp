#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex rmtx;

void printToDown(int iCount) {
	rmtx.lock();

	std::cout << iCount << std::endl;

	if (iCount <= 1) {
		rmtx.unlock();
		return;
	}		

	printToDown(iCount - 1);	

	rmtx.unlock();
}


int main() {
	std::thread th1(printToDown, 10);
	std::thread th2(printToDown, 10);

	for (int i = 0; i < 10; ++i) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//	std::cout << "From main" << std::endl;
	}


	th1.join();
	th2.join();
	system("pause");
	return 0;
}