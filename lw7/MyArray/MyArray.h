#ifndef MYARRAY_H
#define MYARRAY_H

#include <iostream>
#include <iterator>
#include <limits>
#include <ostream>

template <typename T> class MyArray
{
public:
	MyArray();
	~MyArray();

	MyArray(const MyArray& other);
	MyArray(MyArray&& other) noexcept;

	void PushBack(T value);
	void Resize(size_t capacity);
	void Clear();
	void Swap(MyArray& other) noexcept;
	[[nodiscard]] size_t GetSize() const;
	[[nodiscard]] size_t GetCapacity() const;

	T* begin();
	const T* begin() const;
	T* end();
	const T* end() const;
	std::reverse_iterator<T*> rbegin();
	std::reverse_iterator<const T*> rbegin() const;
	std::reverse_iterator<T*> rend();
	std::reverse_iterator<const T*> rend() const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	MyArray& operator=(const MyArray& other);
	MyArray& operator=(MyArray&& other) noexcept;

	template <typename U> MyArray& operator=(const MyArray<U>& other);

private:
	T* m_values;
	size_t m_size;
	size_t m_capacity;
};

template <typename T>
MyArray<T>::MyArray()
	: m_values(nullptr)
	, m_size(0)
	, m_capacity(0)
{
}

template <typename T> MyArray<T>::~MyArray() { Clear(); }

template <typename T>
MyArray<T>::MyArray(const MyArray& other)
	: m_values(nullptr)
	, m_size(other.m_size)
	, m_capacity(other.m_capacity)
{
	T* tempValues = nullptr;
	if (other.m_values)
	{
		tempValues = new T[other.m_capacity];
		try
		{
			std::copy(other.m_values, other.m_values + other.m_size, tempValues);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	m_values = tempValues;
}

template <typename T>
MyArray<T>::MyArray(MyArray&& other) noexcept
	: m_values(other.m_values)
	, m_size(other.m_size)
	, m_capacity(other.m_capacity)
{
	other.m_values = nullptr;
	other.m_size = 0;
	other.m_capacity = 0;
}

template <typename T> void MyArray<T>::PushBack(T value)
{
	if (m_size >= m_capacity)
	{
		const size_t newCapacity = m_capacity == 0 ? 1 : m_capacity * 2;
		Resize(newCapacity);
	}
	m_values[m_size] = value;
	m_size++;
}

template <typename T> void MyArray<T>::Resize(const size_t capacity)
{
	if (capacity > std::numeric_limits<size_t>::max())
	{
		throw std::overflow_error("Array size is too large");
	}

	if (capacity == 0)
	{
		Clear();
		return;
	}

	T* tempValues = nullptr;
	tempValues = new T[capacity];
	try
	{
		std::copy(m_values, m_values + m_size, tempValues);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	delete[] m_values;
	m_values = tempValues;
	m_capacity = capacity;
	for (size_t i = m_size; i < capacity; ++i)
	{
		m_values[i] = T();
	}
}

template <typename T> void MyArray<T>::Clear()
{
	delete[] m_values;
	m_values = nullptr;
	m_size = 0;
	m_capacity = 0;
}

template <typename T> void MyArray<T>::Swap(MyArray& other) noexcept
{
	std::swap(m_values, other.m_values);
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
}

template <typename T> size_t MyArray<T>::GetSize() const { return m_size; }

template <typename T> size_t MyArray<T>::GetCapacity() const { return m_capacity; }

template <typename T> T* MyArray<T>::begin() { return m_values; }

template <typename T> const T* MyArray<T>::begin() const { return m_values; }

template <typename T> T* MyArray<T>::end() { return m_values + m_size; }

template <typename T> const T* MyArray<T>::end() const { return m_values + m_size; }

template <typename T> std::reverse_iterator<T*> MyArray<T>::rbegin()
{
	return std::reverse_iterator<T*>(end());
}

template <typename T> std::reverse_iterator<const T*> MyArray<T>::rbegin() const
{
	return std::reverse_iterator<const T*>(end());
}

template <typename T> std::reverse_iterator<T*> MyArray<T>::rend()
{
	return std::reverse_iterator<T*>(begin());
}

template <typename T> std::reverse_iterator<const T*> MyArray<T>::rend() const
{
	return std::reverse_iterator<const T*>(begin());
}

template <typename T> T& MyArray<T>::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Array index out of range");
	}
	return m_values[index];
}

template <typename T> const T& MyArray<T>::operator[](size_t index) const
{
	if (index >= m_size)
	{
		throw std::out_of_range("Array index out of range");
	}

	return m_values[index];
}

template <typename T> MyArray<T>& MyArray<T>::operator=(const MyArray& other)
{
	if (this != &other)
	{
		MyArray temp(other);
		Swap(temp);
	}

	return *this;
}

template <typename T> MyArray<T>& MyArray<T>::operator=(MyArray&& other) noexcept
{
	if (this != &other)
	{
		MyArray temp(std::move(other));
		Swap(temp);
	}

	return *this;
}

template <typename T>
template <typename U>
MyArray<T>& MyArray<T>::operator=(const MyArray<U>& other)
{
	try
	{
		MyArray temp;
		for (auto elem : other)
		{
			temp.PushBack(static_cast<T>(elem));
		}
		Swap(temp);
	}
	catch (...)
	{
		throw std::invalid_argument("Array assignment failed");
	}

	return *this;
}

#endif // MYARRAY_H
