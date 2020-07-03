#ifndef CARRAY_H_
#define CARRAY_H_

#include <initializer_list>
#include <algorithm>
#include <iostream>


template <typename TData>
class CArray
{
public:
	CArray();

	CArray(
		const CArray& _arr
	);

	CArray(
		const std::initializer_list<TData>& _init_list
	);

	~CArray();

	void push_back(
		const TData& _value
	);

	void insert(
		unsigned int _index,
		const TData& _value
	);

	void erase(
		unsigned int _index
	);

	void print();

	void clear();

	bool is_empty() const;

	size_t size() const;

	TData& operator[] (
		unsigned int _index
		)
	{
		return _data[_index];
	}


	CArray& operator=(
		const CArray<TData>& _other
		);


	bool operator== (CArray<TData>& rhs);


	void swap(
		CArray& _first,
		CArray& _second
	) noexcept;


protected:
	TData* _data;
	size_t _size;

	TData* allocate(
		int _count
	)
	{
		TData* new_array = nullptr;

		new_array = new (std::nothrow) TData[_count];
		return new_array;
	}
};


template<class T>
CArray<T>::CArray()
	: _size(0),
	_data(nullptr)
{
}


template<class T>
CArray<T>::CArray(
	const CArray& _arr
)
{
	_data = new T[_arr._size];
	_size = _arr._size;

	for (int i = 0; i < _size; i++)
		_data[i] = _arr._data[i];
}


template<class T>
CArray<T>::CArray(
	const std::initializer_list<T>& _init_list
) : _size(_init_list.size()),
_data(new (std::nothrow) T[_init_list.size()])
{
	size_t count = 0;
	for (auto& element : _init_list)
	{
		_data[count] = element;
		++count;
	}
}


template<class T>
CArray<T>::~CArray()
{
	if (_size > 0)
		delete[] _data;
}


template<class T>
void CArray<T>::push_back(
	const T& _value
)
{
	T* new_array;

	new_array = new T[_size + 1];

	_size++;

	for (int i = 0; i < _size - 1; i++)
		new_array[i] = _data[i];

	new_array[_size - 1] = _value;

	if ((_size - 1) > 0)
		delete[] _data;

	_data = new_array;
}


template<class T>
void CArray<T>::insert(
	unsigned int _index,
	const T& _value
)
{
	T* new_array;
	new_array = allocate(_size + 1);
	if (new_array == nullptr)
	{
		return;
	}

	for (int i = 0; i < _index; i++)
		new_array[i] = _data[i];

	new_array[_index] = _value;

	for (int i = _index + 1; i < _size + 1; i++)
		new_array[i] = _data[i - 1];

	if (_size > 1)
		delete[] _data;

	_size++;

	_data = new_array;
}


template<class T>
void CArray<T>::erase(
	unsigned int _index
)
{
	for (int i = _index; i < _size - 1; i++)
		_data[i] = _data[i + 1];

	_size--;

	T* new_array = allocate(_size);

	for (int i = 0; i < _size; i++)
		new_array[i] = _data[i];

	if (_size > 0)
		delete[] _data;

	_data = new_array;
}


template<class T>
void CArray<T>::clear()
{
	_size = 0;
	_data = nullptr;
	delete[] _data;
}


template<class T>
size_t CArray<T>::size() const
{
	return _size;
}


template <class T>
bool CArray<T>::is_empty() const
{
	return _size == 0;
}


template <class T>
void CArray<T>::swap(
	CArray& _first,
	CArray& _second
) noexcept
{
	using std::swap;

	swap(_first.mSize, _second.mSize);
	swap(_first.mArray, _second.mArray);
}


template <class T>
void CArray<T>::print()
{
	using namespace std;

	for (int i = 0; i < _size; i++)
		cout << _data[i] << " ";
	cout << endl;
}


template <class T>
CArray<T>& CArray<T>::operator=(
	const CArray<T>& _other
	)
{
	if (_size > 0)
		delete[] _data;

	try {
		_data = new T[_other._size];
		_size = _other._size;

		for (int i = 0; i < _size; i++)
			_data[i] = _other._data[i];
	}
	catch (std::bad_alloc e)
	{
		_size = 0;
	}
	return *this;
}

template <class T>
bool CArray<T>::operator==(CArray<T>& rhs)
{
	return _size == rhs._size
		&&
		_data == rhs._data;
}


#endif