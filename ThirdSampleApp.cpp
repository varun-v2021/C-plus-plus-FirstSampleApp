//============================================================================
// Name        : ThirdSampleApp.cpp
// Author      : VV
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

int learnFunction();

void readerApi() {
	for (int i = 0; i < 10; i++) {
		usleep(400);
		std::cout << "readerApi: " << i << std::endl;
	}
}

void writerApi() {
	for (int i = 0; i < 10; i++) {
		std::cout << "writerApi: " << i << std::endl;
		usleep(400);
	}
}

void WorkerFunc(){
	boost::posix_time::seconds worktime(3);
	std::cout << "Worker: running..." << std::endl;
	boost::this_thread::sleep(worktime);
	std::cout << "Worker: finished..." << std::endl;
}

int main(void) {
	puts("Hello World!!!");

	boost::thread readerThread(readerApi);
	boost::thread writerThread(writerApi);

	readerThread.join();
	writerThread.join();

	boost::thread worker_thread(WorkerFunc);
	std::cout << "main .. waiting for worker thread to finish ..." << std::endl;
	worker_thread.join();
	std::cout << "main: done with all thread execution ..." << std::endl;

	learnFunction();

	return EXIT_SUCCESS;
}
