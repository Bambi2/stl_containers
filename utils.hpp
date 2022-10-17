#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef>

namespace ft {

	template< bool B, class T = void >
	struct enable_if { };

	template< class T >
	struct enable_if<true, T> { typedef T type; };

	template< class T >
	struct is_integral {
		typedef bool value_type;
		static const bool value = false;
	};

	template <>
	struct is_integral<bool> {
		static const bool value = true;
	};

	template <>
	struct is_integral<char> {
		static const bool value = true;
	};

	template <>
	struct is_integral<char16_t> {
		static const bool value = true;
	};

	template <>
	struct is_integral<char32_t> {
		static const bool value = true;
	};

	template <>
	struct is_integral<wchar_t> {
		static const bool value = true;
	};

	template <>
	struct is_integral<short> {
		static const bool value = true;
	};

	template <>
	struct is_integral<int> {
		static const bool value = true;
	};

	template <>
	struct is_integral<long> {
		static const bool value = true;
	};

	template <>
	struct is_integral<long long> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned char> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned short> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long long> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned int> {
		static const bool value = true;
	};

	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template<
		class Category,
		class T,
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T& > 
	struct iterator {
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	template< class Iter >
	struct iterator_traits {
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template< class T >
	struct iterator_traits<T*> {
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template< class T >
	struct iterator_traits<const T*> {
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template< class Iter >
	class reverse_iterator {
	public:
		typedef Iter iterator_type;
		typedef typename iterator_traits<Iter>::iterator_category iterator_category;
		typedef typename iterator_traits<Iter>::value_type value_type;
		typedef typename iterator_traits<Iter>::difference_type difference_type;
		typedef typename iterator_traits<Iter>::pointer pointer;
		typedef typename iterator_traits<Iter>::reference reference;

		reverse_iterator() : current() {};

		explicit reverse_iterator(iterator_type x) : current(x) {};

		template< class U >
		reverse_iterator(const reverse_iterator<U>& other) : current(other.iter) {};

		template< class U >
		reverse_iterator& operator=(const reverse_iterator<U>& other) {
			if (this != &other) {
				this->current = other;
			}

			return *this;
		}

		iterator_type base() const { return this->current; }

		reference operator*() const {
			iterator_type tmp = this->current;

			return *(--tmp);
		}

		pointer operator->() const { return &(operator*()); }

		reference operator[](difference_type n) { return base()[-n-1]; }

		reverse_iterator& operator++() {
			this->current--;
			return *this;
		}

		reverse_iterator& operator--() {
			this->current++;
			return *this;
		}

		reverse_iterator& operator++(int) {
			reverse_iterator temp = *this;
			++(*this);

			return temp;
		}

		reverse_iterator& operator--(int) {
			reverse_iterator temp = *this;
			--(*this);

			return temp;
		}

		reverse_iterator operator+(difference_type n) const { return reverse_iterator(base() - n); }

		reverse_iterator operator-(difference_type n) const { return reverse_iterator(base() + n); }

		reverse_iterator& operator+=(difference_type n) {
			*this = *this + n;
			return *this;
		}

		reverse_iterator& operator-=(difference_type n) {
			*this = *this - n;
			return *this;
		}
	protected:
		iterator_type current;
	};

	template< class Iterator1, class Iterator2 >
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() == rhs.base(); }

	template< class Iterator1, class Iterator2 >
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() != rhs.base(); }

	template< class Iterator1, class Iterator2 >
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() > rhs.base(); }

	template< class Iterator1, class Iterator2 >
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() >= rhs.base(); }

	template< class Iterator1, class Iterator2 >
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() < rhs.base(); }

	template< class Iterator1, class Iterator2 >
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() <= rhs.base(); }

	template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return rhs.base() - lhs.base(); }


}

#endif