#ifndef sortedArray_H
#define sortedArray_H
#include <iostream>
#include <ostream> 
#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <cstddef>  

//Percorso: cd /Users/marco/Desktop/progetto/sortedArray.h

/**
@brief Logically ordered array

**/
enum {
	INCREASING,
	DECREASING
};
template<typename T>

class sortedArray {

private:

	T *_array; //Pointer to array
	unsigned int _size; //Actual size
	unsigned int current_elements; //Number of elements in the array at the moment

	int *utility_positions; //Utility array for logic sorting
							//See the function logic_sort() for further details
	int sortingOrder;
public:

	/**
	@brief Default constructor
	**/
	sortedArray() : _array(0), _size(0), current_elements(0) {}

	/**
	@brief Constructor to create an array, given its size
	@param size: the size wanted
	@throw Exception thrown for an invalid choice of size parameter (i.e. 0)
	**/
	explicit sortedArray(unsigned int size) : _array(0), _size(0), current_elements(0) {
		if (size == 0) {
			std::cout << "Invalid size!" << std::endl;
			throw;
		}

		try {
			_array = new T[size];
			utility_positions = new int[size];

			int utility_positions[5] = { 0, 1, 2, 3, 4 }; //default logical order

		}
		catch (...) {
			std::cout << "Fatal error!" << std::endl;
			throw;
		}

		_size = size;
		current_elements = 0;
	}

	/**
	@brief Costructor to create an array given its size and the elements to fill it with
	@param size: the size wanted
	@param value: the element to fill the array with
	@throw Exception thrown for an invalid choice of size parameter (i.e. 0)
	**/
	sortedArray(unsigned int size, const T &value) : _array(0), _size(0), current_elements(0) {
		if (size == 0) {
			std::cout << "Invalid size!" << std::endl;
			throw;
		}
		try {
			_array = new T[size];
			utility_positions = new int[size];
		}
		catch (...) {
			std::cout << "Fatal error!" << std::endl;
			throw;

		}
		_size = size;

		try {
			for (int i = 0; i < _size; i++) {
				_array[i] = value;
				current_elements++;
			}
			int utility_positions[5] = { 0, 1, 2, 3, 4 }; //default logical order
		}
		catch (...) { //In case of error, empty the array and initialize size and current_elements
			delete[] _array;
			_size = 0;
			_array = 0;
			current_elements = 0;
			throw;
		}
	}

	/**
	@brief Copy constructor
	@param other: Passed-by-reference array to copy
	@throw General exception
	**/
	sortedArray(const sortedArray &other) : _array(0), _size(0), current_elements(0) {

		try {
			_array = new T[other._size];
		}
		catch (...) {
			std::cout << "Invalid size!" << std::endl;
			throw;
		}
		_size = other._size;
		current_elements = other._size;

		try {
			for (int i = 0; i<_size; i++) {
				_array[i] = other._array[i];
			}
		}
		catch (...) {
			delete[] _array;
			_size = 0;
			_array = 0;
			current_elements = 0;
			throw;
		}

	}

	/**
	@brief Redefining the assignment operator
	@param other: Passed-by-reference array
	@return Self-referenced pointer
	**/
	sortedArray &operator=(const sortedArray &other) {

		if (this != &other) { //Auto assignment is not permitted
			sortedArray tmp(other);
			this->swap(tmp);
		}
		return *this;
	}

	/**
	@brief Swap the content of two arrays. Utility for the assignment operator overload
	@param other: Array to be swapped
	**/
	void swap(sortedArray &other) {
		std::swap(other._size, this->_size);
		std::swap(other._array, this->_array);
	}

	/**
	@brief Destructor. Used to free the heap.
	**/
	~sortedArray() {
		delete[] _array;
		delete[] utility_positions;
		_array = 0;
		_size = 0;
		current_elements = 0;
	}

	/**
	@brief Method called to get the size of the array
	@return The size of the array
	**/
	unsigned int size() const {
		return _size;
	}

	/**
	@brief Method called to get the number of elements currently in the array
	@return The number of elements currently in the array
	**/
	unsigned int occupied_size() const {
		return current_elements;
	}

	/**
	@brief Method to empty the data structure using a default value.
	@throw Memory error
	**/
	void clear(const T &init) {
		try {
			for (int i = 0; i<_size; i++) {
				_array[i] = static_cast<T>(init);
			}
			current_elements = 0;
		}
		catch (...) {
			delete[] _array;
			_size = 0;
			_array = 0;
			current_elements = 0;
			throw;
		}
	}

	/**
	@brief GETTER method. Elements are returned in the original insertion order. (No logical sorting)
	@pre Must have index < _size
	@param index: Index of the element to get
	@return The element at the given position
	**/
	const T &operator()(unsigned int index) const {
		assert(index < _size);
		return _array[index];
	}

	/**
	@brief SETTER method.
	@pre Must have index < _size
	@param index: Index of the position to be written
	@return The element inserted
	**/
	T &operator[](unsigned int index) {
		assert(index < _size);
		if (current_elements < _size) {
			current_elements++;
			return _array[index];
		}
		else {
			std::cout << "Array is full!" << std::endl;
			return _array[index];
		}
	}

	void print() {
		for (int i = 0; i<_size; i++) {
			std::cout << _array[utility_positions[i]] << "\t";
		}
	}

	/**
	@brief Logic sorting function. Selection sort is used.
	**/
	void logic_sort(int order) {
		int i = 0, j = 0, n = _size, min = 0, temp = 0;

		for (int z = 0; z < _size; z++)
			utility_positions[z] = z;

		for (i = 0; i<n - 1; i++) {
			min = i;
			for (j = i + 1; j<n; j++) {
				if (order == INCREASING) {
					if (_array[utility_positions[j]] < _array[utility_positions[min]]) {
						min = j;
					}
				}
				else if (order == DECREASING) {
					if (_array[utility_positions[j]] > _array[utility_positions[min]]) {
						min = j;
					}
				}
			}
			if (min != i) {
				temp = utility_positions[min];
				utility_positions[min] = utility_positions[i];
				utility_positions[i] = temp;
			}

		}

		for (int i = 0; i<_size; i++) {
			std::cout << _array[i] << "\t";
		}

		std::cout << std::endl;

		for (int i = 0; i<_size; i++) {

			std::cout << utility_positions[i] << "\t";
		}

	}

	/**
	@brief Iterators overloading
	**/
#pragma region Iterators

	class unsorted_const_iterator;

	class iterator {
		T *ptr;

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef T*                        pointer;
		typedef T&                        reference;

		iterator() : ptr(0) {
		}

		iterator(const iterator &other) : ptr(other.ptr) {
		}

		iterator& operator=(const iterator &other) {
			ptr = other.ptr;
			return *this;
		}

		~iterator() {}

		// Dereferentiation
		reference operator*() const {
			return *ptr;
		}

		pointer operator->() const {
			return ptr;
		}

		iterator operator++(int) {
			iterator tmp(*this);
			++ptr;
			return tmp;
		}

		iterator& operator++() {
			++ptr;
			return *this;
		}

		bool operator==(const iterator &other) const {
			return ptr == other.ptr;
		}

		bool operator!=(const iterator &other) const {
			return ptr != other.ptr;
		}

		friend class unsorted_const_iterator;

		bool operator==(const unsorted_const_iterator &other) const {
			return ptr == other.ptr;
		}

		bool operator!=(const unsorted_const_iterator &other) const {
			return ptr != other.ptr;
		}

	private:
		friend class sortedArray;

		iterator(T *p) : ptr(p) {
		}

	};

	iterator begin() {
		return iterator(_array);
	}

	iterator end() {
		return iterator(_array + (_size));
	}


	class unsorted_const_iterator {
		const T *ptr;
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;


		unsorted_const_iterator() : ptr(0) {
		}

		unsorted_const_iterator(const unsorted_const_iterator &other)
			: ptr(other.ptr) {

		}

		unsorted_const_iterator(const iterator &other)
			: ptr(other.ptr) {

		}

		unsorted_const_iterator& operator=(const unsorted_const_iterator &other) {
			ptr = other.ptr;
			return *this;
		}

		unsorted_const_iterator& operator=(const iterator &other) {
			ptr = other.ptr;
			return *this;
		}

		~unsorted_const_iterator() {

		}

		reference operator*() const {
			return *ptr;
		}

		pointer operator->() const {
			return ptr;
		}

		unsorted_const_iterator operator++(int) {
			unsorted_const_iterator tmp(*this);
			++ptr;
			return tmp;
		}

		unsorted_const_iterator& operator++() {
			++ptr;
			return *this;
		}

		bool operator==(const unsorted_const_iterator &other) const {
			return ptr == other.ptr;
		}

		bool operator!=(const unsorted_const_iterator &other) const {
			return ptr != other.ptr;
		}

		friend class iterator;

		bool operator==(const iterator &other) const {
			return ptr == other.ptr;
		}

		bool operator!=(const iterator &other) const {
			return ptr != other.ptr;
		}

	private:
		friend class sortedArray;

		unsorted_const_iterator(const T*p) : ptr(p) {

		}

	}; unsorted_const_iterator begin() const {
		return unsorted_const_iterator(_array);
	}

	unsorted_const_iterator end() const {
		return unsorted_const_iterator(_array + (_size));
	}

#pragma endregion

};

/**
@brief Print method. Overloading of the operator <<
**/

template <typename T>
std::ostream& operator<<(std::ostream &os, const sortedArray <T> &util) {
	for (unsigned int i = 0; i < util.size(); i++) {
		os << util(i) << "/t";
	}
	return os;
}

template <typename T, typename P>
void find_count(const sortedArray<T> &util, const T &target, const P &funct) {
	for (int i = 0; i<util.size(); i++) {
		if (funct(util[i], target)) {
			std::cout << "P(SA[i], target) = 1" << std::endl;
		}
		else {
			std::cout << "P(SA[i], target) = 0" << std::endl;
		}
	}
}



int main() {
	typedef void (sortedArray<int>::*LogicSort_fnc_ptr)(int );
	LogicSort_fnc_ptr fnc_ptr = &sortedArray<int>::logic_sort;

	sortedArray<int> sorted(10);
	for (register int i = 0; i < 10; i++)
	{
		sorted[i] = rand() % 100;
	}
	for (register int i = 0; i < 10; i++)
	{
		std::cout<<sorted(i)<<" ";
	}
	//sorted.logic_sort(INCREASING);
	(sorted.*fnc_ptr)(INCREASING);
	sorted.print();
	(sorted.*fnc_ptr)(DECREASING);
	sorted.print();
	return 0;
}
#endif