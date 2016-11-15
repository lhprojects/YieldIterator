#ifndef YIELD_ITERATOR_H
#define YIELD_ITERATOR_H

template<class T, class IT>
struct YieldInterator {
	bool step() {

		((IT*)this)->interate();

		__everRun = true;
		return __empty;
	}
	T value() { return __value; }
	bool __empty = false;
	bool __everRun = false;
	T __value;
};
#define YIELD_ITERATOR_BEGIN() if(__everRun) { goto YIELD; }
#define YIELD_ITERATOR_END() (__empty = true)
#define YIELD_ITERATOR_YIELD(x) do { __value = (x); return; YIELD: int __xx = 1; __xx /=__xx;} while(0)


#endif
