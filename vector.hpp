#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <iterator>
#include <stdexcept>
#include "utils.hpp"

namespace ft {
	template< class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		class iterator;
		class const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		//CONSTRUCTORS

		vector();

		explicit vector(const Allocator& alloc);

		explicit vector(size_type count,
						const T& value = T(),
						const Allocator& alloc = Allocator());

		template< class InputIt >
		vector(typename enable_if<!is_integral<InputIt>::value, InputIt>::type first,
				InputIt last,
				const Allocator& alloc = Allocator());

		vector(const vector& other);

		~vector();

		vector& operator=(const vector& other);

		void assign(size_type count, const T& value);

		template< class InputIt >
		void assign(typename enable_if<!is_integral<InputIt>::value, InputIt>::type first, InputIt last);

		allocator_type get_allocator() const { return alloc; }

		//ELEMENT ACCESS

		reference at(size_type pos) {
			if (pos >= size) {
				throw std::out_of_range();
			}
			return array[pos];
		}

		const_reference at(size_type pos) const {
			if (pos >= size) {
				throw std::out_of_range();
			}
			return array[pos];
		}

		reference operator[](size_type pos) { return array[pos]; }

		const_reference operator[](size_type pos) const { return array[pos]; }

		reference front() { return array[0]; }

		const_reference front() const { return array[0]; }

		reference front() { return array[size - 1]; }

		const_reference front() const { return array[size - 1]; }

		T* data() { return array; }

		const T* data() const { return array; }

		//ITERATORS

	private:
		size_type size;
		size_type capacity;
		T* array;
		Allocator alloc;

		void free_array() {
			for (size_type i = 0; i < size; ++i) {
				alloc.destoy(array + i);
			}
			alloc.deallocate(array, capacity);
			size = 0;
			capacity = 0;
			array = NULL;
		}
	};

	template< class T, class Allocator >
	vector<T, Allocator>::vector() : alloc(), size(0), capacity(0) {
		array = alloc.allocate(capacity);
	}

	template< class T, class Allocator >
	vector<T, Allocator>::vector(const Allocator& alloc) : alloc(alloc), size(0), capacity(0) {
		array = alloc.allocate(capacity);
	}

	template< class T, class Allocator >
	vector<T, Allocator>::vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : alloc(alloc), size(count), capacity(count) {
		array = alloc.allocate(capacity);
		size_type i = 0;
		try {
			while (i < size) {
				alloc.construct(array + i, value);
			}
		} catch (...) {
			i--;
			while (i >= 0) {
				alloc.destroy(array + i);
			}
			alloc.deallocate(array, size);
			throw ;
		}
	}

	template< class T, class Allocator >
	template< class InputIt >
	vector<T, Allocator>::vector(typename enable_if<!is_integral<InputIt>::value, InputIt>::type first, InputIt last, const Allocator& alloc = Allocator()) : alloc(alloc), size(0), capacity(0) {
		size_type count = std::distance(first, last);
		this->array = alloc(capacity);
		size_type i = 0;
		try {
			while (first != last) {
				alloc.construct(array + i, *first);
				++i;
				++first;
			}
			this->size = count;
			this->capacity = count;
		} catch (...) {
			--i;
			while (i >= 0) {
				alloc.destroy(array + i);
				--i;
			}
			alloc.deallocate(array, count);
			throw ;
		}
	}

	template< class T, class Allocator >
	vector<T, Allocator>::vector(const vector& other) : size(other.size), capacity(other.capacity), alloc(ohter.alloc) {
		array = alloc.allocate(capacity);
		size_type i = 0;
		try {
			while (i < size) {
				alloc.construct(array + i, other.array[i]);
				++i;
			}
		} catch(...) {
			--i;
			while (i >= 0) {
				alloc.destroy(array + i);
				--i;
			}
			alloc.deallocate(array, capacity);
			throw ;
		}
	}

	template< class T, class Allocator >
	vector<T, Allocator>::~vector() {
		this->free_array();
	}

	template< class T, class Allocator >
	vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other) {
		if (this != &other) {
			T* temp = alloc.allocate(other.capacity);
			size_type i = 0;
			try {
				for (; i < other.size; ++i) {
					alloc.construct(temp + i, other.array[i]);
				}
			} catch(...) {
				--i;
				while (i >= 0) {
					alloc.destroy(temp + i);
					--i;
				}
				alloc.deallocate(temp, other.capacity);
				throw ;
			}
			this->free_array();
			this->size = other.size;
			this->capacity = other.capacity;
			this->array = temp;
		}
		return *this;
	}

	template< class T, class Allocator >
	void vector<T, Allocator>::assign(size_type count, const T& value) {
		if (count <= capacity) {
			for (size_type i = 0; i < size; ++i) {
				alloc.destroy(array + i);
			}
			size_type i = 0;
			try {
				while (i < count) {
					alloc.construct(array + i, value);
					++i;
				}
			} catch (...) {
				--i;
				while (i >= 0) {
					alloc.destroy(array + i);
					--i;
				}
				size = 0;
				throw ;
			}
			this->size = count;
		} else {
			T* temp = alloc.allocate(count);
			size_type i = 0;
			try {
				for (; i < count; ++i) {
					alloc.construct(temp + i, value);
				}
			} catch (...) {
				--i;
				while (i >= 0) {
					alloc.destroy(temp + i);
				}
				alloc.deallocate(temp, count);
				throw ;
			}
			this->free_array();
			this->array = temp;
			this->size = count;
			this->capacity = count;
		}
	}

	template< class T, class Allocator>
	template< class InputIt >
	void vector<T, Allocator>::assign(typename enable_if<!is_integral<InputIt>::value, InputIt>::type first, InputIt last) {
		size_type count = std::distance(first, last);
		size_type i = 0;
		if (count <= capacity) {
			for (size_type i = 0; i < size; ++i) {
				alloc.destroy(array + i);
			}
			try {
				while (first != last) {
					alloc.construct(array + i, *first);
					++i;
					++first;
				}
			} catch (...) {
				--i;
				while (i >= 0) {
					alloc.destroy(array + i);
					--i;
				}
				size = 0;
				throw ;
			}
			this->size = count;
		} else {
			T* temp = alloc.allocate(count);
			try {
				while (first != last) {
					alloc.construct(temp + i, *first);
					++i;
					++first;
				}
			} catch (...) {
				--i;
				while (i >= 0) {
					alloc.destroy(temp + i);
				}
				alloc.deallocate(temp, count);
				throw ;
			}
			this->free_array();
			this->array = temp;
			this->size = count;
			this->capacity = count;
		}
	}
}



#endif