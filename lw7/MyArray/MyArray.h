#ifndef MYARRAY_H
#define MYARRAY_H
#include <iterator>

template <typename T> class MyArray
{
public:
	MyArray();
	~MyArray();

	MyArray(const MyArray& other);
	MyArray(MyArray&& other) noexcept;

	void PushBack(
		T value); // TODO: Массив должен динамически увеличивать свой размер при добавлении
				  // элементов. Вместимость буфера для хранения элементов должна удваиваться.
	void Resize(size_t capacity); // TODO: В случае, если новая длина массива больше прежней,
								  // вставляемые в конец массива элементы должны инициализироваться
								  // значением по умолчанию для типа T.
	void Clear();
	void Swap(MyArray& other) noexcept;
	[[nodiscard]] size_t GetSize() const;

	T* begin();
	const T* begin() const;
	T* end();
	const T* end() const;
	std::reverse_iterator<T*> rbegin();
	std::reverse_iterator<const T*> rbegin() const;
	std::reverse_iterator<T*> rend();
	const std::reverse_iterator<const T*> rend() const;

	T& operator[](size_t index); // TODO: В случае, если индекс элемента выходит за пределы массива,
								 // должно выбрасываться исключение std::out_of_range
	const T& operator[](size_t index) const;

	MyArray& operator=(const MyArray& other);
	MyArray& operator=(MyArray&& other) noexcept;

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
		tempValues = new T[other.m_size];
		try
		{
			std::copy(other.m_values, other.m_values + other.m_size, tempValues);
		}
		catch (...)
		{
			delete[] tempValues;
			throw;
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
}

template <typename T> void MyArray<T>::PushBack(T value)
{
	if (m_size == m_capacity)
	{
		Resize(m_capacity * 2);
	}
	m_values[m_size + 1] = value;
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

	if (capacity > m_capacity)
	{
		T* tempValues = nullptr;
		tempValues = new T[capacity];
		try
		{
			std::copy(m_values, m_values + m_size, tempValues);
			delete[] m_values;
		}
		catch (...)
		{
			delete[] tempValues;
			throw;
		}
		for (size_t i = m_size; i < capacity; ++i)
		{
			m_values[i] = T();
		}
		m_values = tempValues;
		m_capacity = capacity;
	}
}

template <typename T> void MyArray<T>::Clear()
{
	delete[] m_values;
	m_values = nullptr;
	m_size = 0;
	m_capacity = 0;
}
template <typename T> void MyArray<T>::Swap(MyArray& other)
{
	std::swap(m_values, other.m_values);
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
}

template <typename T> size_t MyArray<T>::GetSize() const { return m_size; }

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
	return std::reverse_iterator<T*>(end());
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
	if (index > m_size)
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

template <typename T> MyArray<T>& MyArray<T>::operator=(MyArray&& other)
{
	if (this != &other)
	{
		Clear();
		m_values = other.m_values;
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		other.m_values = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}

	return *this;
}

#endif // MYARRAY_H
