#ifndef _MY_ITERATOR_H
#define _MY_ITERATOR_H



template <	typename It,
			typename Pointer = It*,
			typename Reference = It&,
			typename DifferenceType = long long int
			>
	struct MyGenericIterator {

		using ValueType = It;
		using PointerType = Pointer;
		using ReferenceType = Reference;		

		MyGenericIterator() noexcept : _ptr(nullptr), _inc(0)  {} // default constructor
		
		// Constructable

        MyGenericIterator(PointerType ptr, bool bRev = false)  noexcept : _ptr(ptr), _inc(((bRev)?-1:1)){} // MyGenericIterator it = some_raw_ptr;
		
		// CopyConstructable

		MyGenericIterator(const MyGenericIterator& it) noexcept {	
			_ptr = it._ptr; 
			_inc = it._inc;
		}
		
		MyGenericIterator(MyGenericIterator&& it) noexcept {	
			_ptr = it._ptr; 
			it._ptr = nullptr;
			_inc = it._inc;
			it._inc = 0;
		}		
		
		// Destructable

		~MyGenericIterator() noexcept = default; // End of scope

		// CopyAssignable

		MyGenericIterator& operator=(const MyGenericIterator& it) noexcept {
			_ptr = it._ptr;
			_inc = it._inc;
			return *this;
		}

		MyGenericIterator& operator=(MyGenericIterator&& it) noexcept {
			_ptr = it._ptr; 
			it._ptr = nullptr;
			_inc = it._inc;
			it._inc = 0;
			return *this;
		}

		// Dereferenceable

		ReferenceType operator*() const noexcept {
			return *_ptr;
		}

		
		MyGenericIterator* operator->() const noexcept {return this;}

		// Comparable

		bool operator<(const MyGenericIterator& it) const noexcept {
			return _ptr < it._ptr;
		}

		bool operator>(const MyGenericIterator& it) const noexcept {
			return _ptr > it._ptr;
		}

		bool operator<=(const MyGenericIterator& it) const noexcept {
			return !(_ptr > it._ptr);
		}


		bool operator>=(const MyGenericIterator& it) const noexcept {
			return !(_ptr < it._ptr);
		}


		bool operator==(const MyGenericIterator& it) const noexcept {
			return _ptr == it._ptr;
		}

		bool operator!=(const MyGenericIterator& it) const noexcept {
			return !(_ptr == it._ptr);
		}

		
		// Incrementable

		MyGenericIterator& operator+=(DifferenceType scale) noexcept {
			_ptr += (scale*_inc);
			return *this;
		}

		MyGenericIterator& operator++()  noexcept {
			return *this+=1;
		}

		MyGenericIterator operator++(int) noexcept {
			MyGenericIterator ret = *this;
			++*this;
			return ret;
		}
		
		DifferenceType operator-(MyGenericIterator iter) {
			return _ptr - iter._ptr;
		}
		
		// Fields

		public:
			PointerType _ptr;
		private:
			DifferenceType _inc;

	};


#endif //_MY_ITERATOR_H