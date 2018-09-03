#include <iostream>
#include <thread>
#include <chrono>


class MyClass {
public:
	int Sum(int a, int b) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "******* sum STARTED\tCurrent thread ID = " << std::this_thread::get_id() << std::endl;
		std::cout << "******* sum STOPPED\tCurrent thread ID = " << std::this_thread::get_id() << std::endl;
		return a + b;
	}

	void doWork(int a) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "******* doWork STARTED\tCurrent thread ID = " << std::this_thread::get_id() << std::endl;
		std::cout << "Value of the number is " << a << std::endl;
		std::cout << "******* doWork STOPPED\tCurrent thread ID = " << std::this_thread::get_id() << std::endl;
	}
};


int Sum(int a, int b) {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "******* sum STARTED\tCurrent thread ID = " << std::this_thread::get_id() << std::endl;	
	std::cout << "******* sum STOPPED\tCurrent thread ID = " << std::this_thread::get_id() << std::endl;
	return a+b;
}

void doWork(int a, int b, int& c) {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "******* doWork STARTED\tCurrent thread ID = " << std::this_thread::get_id() << std::endl;		
	c = a + b;
	std::cout << "******* doWork STOPPED\tCurrent thread ID = " << std::this_thread::get_id() << std::endl;
}


int main() {
	int res;
	int sum;
	int mSum;	
	MyClass m;
	std::thread mThSum([&m, &mSum]() {mSum = m.Sum(2, 9); });
	std::thread mTh(&MyClass::doWork, m, 15);
	std::thread th(doWork, 2, 3, std::ref(res));
	std::thread thSum([&sum]() { sum = Sum(2, 10); });

	for (int i = 0; i<10; ++i ) {
		std::cout << "main\tCurrent thread ID = " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	
	mThSum.join();
	std::cout << "sum of mThSum.Sum(2, 9) = " << mSum << std::endl;
	
	mTh.join();
	std::cout << "mTh has finished"<< std::endl;

	th.join();
	std::cout << "res of doWork(2, 3) = " << res << std::endl;

	thSum.join();
	std::cout << "sum of Sum(2, 10) = " << sum << std::endl;
	system("pause");
	return 0;
}