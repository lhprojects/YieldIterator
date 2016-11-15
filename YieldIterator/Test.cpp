#include <chrono>
#include <stdio.h>
#include <list>

#include "YieldIterator.h"

struct ListIter : YieldInterator<int, ListIter> { // note here

	void interate();

private:
	friend struct List;
	ListIter(List *);
	List *fList;
	std::list<int>::iterator it;
	std::list<int>::iterator end;

};

struct List {

	List() {
		for (int i = 0; i < 1000; ++i) {
			fList.push_back(i);
		}
	}
	ListIter Begin() { return ListIter(this); }
	std::list<int> fList;
};

inline ListIter::ListIter(List *list) {
	fList = list;
}

void ListIter::interate() { // note here
	YIELD_ITERATOR_BEGIN();

	end = fList->fList.end();
	for (it = fList->fList.begin(); it != end; ++it) {
		YIELD_ITERATOR_YIELD(*it);
	}

	YIELD_ITERATOR_END();
}


int main() {
	using namespace std::chrono;
	using clock = high_resolution_clock;

	List l;
	int c = 0;
	int cc = rand();
	int loop = 100000;

	auto t0 = clock::now();
	c = cc;
	for (int i = 0; i < loop; ++i) {
		for (auto i = l.Begin(); !i.empty(); i.step()) {
			c += c*i.value()*i.value() + (i.value() >> 1);
		}
	}
	auto t1 = clock::now();
	auto dur = duration_cast<microseconds>(t1 - t0);
	printf("Yield iterator time %dus\n", (int)dur.count());
	printf("result %d\n", c);

	t0 = clock::now();
	c = cc;
	auto *list = &l.fList;
	for (int i = 0; i < loop; ++i) {
		for (auto i = list->begin(); i != list->end(); ++i) {
			c += c * *i * *i + (*i >> 1);
		}
	}
	t1 = clock::now();
	dur = duration_cast<microseconds>(t1 - t0);
	printf("original iterator time %dus\n", (int)dur.count());
	printf("result %d\n", c);

}
