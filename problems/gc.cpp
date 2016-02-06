/*-------------------------------------------------------------------------------------------
 *
 * Garbage collection : Mark and Sweep Algorithm
 *
 * ------------------------------------------------------------------------------------------*/
#include <iostream>
#include <list>
#include <typeinfo>
#include <cstdlib>

using namespace std;

class OutofRangeExec {


};

// Iterator class for cycling through arrays
// that are pointed to by GCPtrs
template <class T> class Iter {
	T *ptr;
	T *begin;
	T *end;
	unsigned length;

	public :
	
	Iter() {
		ptr = end = begin = NULL;
		length = 0;
	}

	Iter(T *p, T *first, T *last) {
		ptr = p;
		begin = first;
		last = end;
		length = last - first;
	}

	unsigned size() {
		return length;
	}

	T &operator*() {
		if((ptr >= end) || (ptr < begin)) 
			throw OutofRangeExec();
		return *ptr;
	}

	T *operator->() {
		if((ptr >= end) || (ptr < begin)) 
			throw OutofRangeExec();
		return ptr;
	}
	
	Iter operator++() {
		ptr++;
		return *this;
	}
	
	Iter operator--() {
		ptr--;
		return *this;
	}

        Iter operator++(int) {
		T *tmp = ptr;
		ptr++;
		return Iter<T>(tmp, begin, end);
	}	

	Iter operator--(int) {
		T *tmp = ptr;
		ptr--;
		return Iter<T>(tmp, begin, end);
	}

	T& operator[](int i) {
		if ((i < 0) || (i > (end - begin))) 
			throw OutofRangeExec();
		return *(ptr + i);
	}

	bool operator==(Iter op2) {
		return (ptr == op2.ptr);
	}

	bool operator!=(Iter op2) {
		return (ptr != op2.ptr);
	}

	bool operator<(Iter op2) {
		return ptr < op2.ptr;
	}	

	bool operator<=(Iter op2) {
		return ptr <= op2.ptr;
	}	

	bool operator>(Iter op2) {
		return ptr > op2.ptr;
	}	

	bool operator>=(Iter op2) {
		return ptr >= op2.ptr;
	}	

	Iter operator-(int n) {
		T *p = ptr - n;
		if (p < begin || p > end)	
			throw OutofRangeExec();
		ptr = p;
		return *this;
	}

	Iter operator+(int n) {
		T *p = ptr + n;
		if (p < begin || p > end)	
			throw OutofRangeExec();
		ptr = p;
		return *this;
	}
};


template <class T> class GCInfo {
	
	public :

		unsigned refcount;

		T *mptr;

		bool isArray;

		unsigned arraySize;

		GCInfo(T *memptr, unsigned size = 0) {
			refcount = 1;
			mptr = memptr;
			if (size != 0)
				isArray = true;
			else
			   	isArray = false;
		}	
				

		bool operator==(const GCInfo<T> &obj2) {
			return mptr == obj2.mptr;
		}

};		

// GCPtr implements a pointer type that uses garbage collection
// to release unused memory

template <class T, int size = 0> class GCPtr {

	static list<GCInfo<T> > gclist;
	T *addr;

	bool isArray;
	unsigned arraysize;
	static bool first;

	typename list<GCInfo<T> >::iterator findPtrInfo(T *ptr);
	
	public :

	typedef Iter<T> GCiterator; 

	GCPtr(T *t = NULL) {
		if (first)
			atexit(shutdown);

		first = false;
		
		typename list<GCInfo<T> >::iterator p = findPtrInfo(t);
		if (p != gclist.end()) {
			p->refcount++;
		} else {
			GCInfo<T> gcobj(t, size);
			gclist.push_front(gcobj);
		}
			
		addr = t;
		arraysize = size;
		
		if (size > 0)
			isArray = true;
		else
			isArray = false;	
	}

	GCPtr(const GCPtr &obj) {

		first = false;
		
		typename list<GCInfo<T> >::iterator p = findPtrInfo(obj.addr);
		p->refcount++;
		arraysize = obj.arraysize;
		isArray = obj.isArray;
	}

	~GCPtr();

	static bool collect();

	T *operator=(T* t);

	GCPtr &operator=(GCPtr &rv);

	T &operator*() {
		return *addr;
	}

	T *operator->() {
		return addr;	
	}

	T &operator[](int i) {
		return addr[i];
	}

	Iter<T> begin() {

		if (isArray) size = arraysize;
		else size = 1;

		return Iter<T> (addr, addr, addr + size);
	}

	Iter<T> end() {

		if (isArray) size = arraysize;
		else size = 1;

		return Iter<T> (addr + size, addr, addr + size);
	}

	static int gclistSize() { return gclist.size(); }
			
	static void showlist();

	static void shutdown();
};

template <class T, int size>
	list<GCInfo<T> > GCPtr<T, size>::gclist;
	
template <class T, int size>
	bool GCPtr<T, size>::first = true;

template<class T, int size>
GCPtr<T, size>::~GCPtr() {
	typename list<GCInfo<T> >::iterator p = findPtrInfo(addr);
	p->refcount--;
	collect();	
}
	
template<class T, int size>
bool GCPtr<T, size>::collect() {
	typename list<GCInfo<T> >::iterator p;
	bool memfreed = false;
	do {
		for (p = gclist.begin(); p!= gclist.end(); p++) {
			if (p->refcount)
				continue;
			gclist.remove(*p);
			memfreed = true;

			if (p->mptr) {
				if (p->isArray) 
					delete [] p->mptr;
				else	
					delete p->mptr;
			}
		}	
	} while (p!= gclist.end());

	return memfreed;
}

//overload assignment of pointer to GCPtr
template<class T, int size>
T *GCPtr<T, size>::operator=(T* t) {
	
	typename list<GCInfo<T> >::iterator p;
	p = findPtrInfo(addr);
	p->refcount--;
	p = findPtrInfo(t);
	if (p != gclist.end()) {
		p->refcount++;
	} else {
		GCInfo<T> gcobj(t, size);
		gclist.push_front(gcobj);
	}
	addr = t;
	return t;
}

//overload assignment of GCPtr to GCPtr
template<class T, int size>
GCPtr<T, size>& GCPtr<T, size>::operator=(GCPtr& obj) {
	
	typename list<GCInfo<T> >::iterator p;
	p = findPtrInfo(addr);
	p->refcount--;
	p = findPtrInfo(obj.addr);
	p->refcount++;
	addr = obj.addr;
	return obj;
}

template<class T, int size>
void GCPtr<T, size>::showlist() {
	
	typename list<GCInfo<T> >::iterator p;

	cout <<"gclist" << typeid(T).name() << ", " << size << ">:\n";
	cout <<"memPtr	refcount	value\n";

	if (gclist.begin() == gclist.end()) {
		cout << "-----Empty-----\n\n";
		return;
	}

	for(p = gclist.begin(); p != gclist.end(); p++) {
		cout << "[" << (void*)p->mptr << "]" << p->refcount << endl; 
	}
}

// Find a pointer in gclist
template<class T, int size>
typename list<GCInfo<T> >::iterator
GCPtr<T, size>::findPtrInfo(T *ptr) {
	typename list<GCInfo<T> > ::iterator p;
	
	for (p = gclist.begin(); p != gclist.end(); p++)
		if (p->mptr == ptr)
			return p;
	return p;
}

// Shutdown
template<class T, int size>
void GCPtr<T, size>::shutdown() {
	
	if (gclist.size() == 0)
		return;

	typename list<GCInfo<T> >::iterator p;
	
	for (p = gclist.begin(); p != gclist.end(); p++)
		p->refcount = 0;
	
	collect();
}

int main(void) {

	GCPtr<int> p;

	try {
		p = new int;
	
	} catch (exception &e) {
		cout << "Allocation Failure" << endl;
		return 1;
	}

	return 0;
}
