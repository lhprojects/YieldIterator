#ifndef YIELD_ITERATOR_H
#define YIELD_ITERATOR_H

template<class T, class IT>
struct YieldInterator {
	void step() {

		((IT*)this)->interate();

		if (__firstRun) {
			__firstRun = false;
		}

	}
	T value() { return __value; }
	bool empty() { if (__firstRun) step(); return __empty; }
	bool __firstRun = true;
	bool __empty = false;
	T __value;
};
#define YIELD_ITERATOR_BEGIN() if(!__firstRun) { goto YIELD; }
#define YIELD_ITERATOR_END() (__empty = true)
#define YIELD_ITERATOR_YIELD(x) do { __value = x; return; YIELD: int __xx = 1; __xx /=__xx;} while(0)


#endif
