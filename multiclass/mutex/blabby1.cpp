#include <iostream>
#include <thread>
#include <vector>
#include <cstdint>
#include <getopt.h>

using namespace std;

void Worker(uint64_t c, int tid) {
	for (uint64_t i = 0; i < c; i++)
		cout << "[" << tid << "] " << i << endl;
}

int main(int argc, char * argv[]) {
	uint64_t max = 1 << 10;
	int c;

	while ((c = getopt(argc, argv, "m:")) != -1) {
		switch (c) {
			case 'm':
				max = atoi(optarg);
				break;
		}
	}

	cout << "Thread count:   " << thread::hardware_concurrency() << endl;
	cout << "Max:            " << max << endl;

	vector<thread> t(thread::hardware_concurrency());

	for (size_t i = 0; i < t.size(); i++)
		t.at(i) = thread(Worker, max, i);

	for (auto & it : t)
		it.join();

	return 0;
}
