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
	void Resize(
		int size); // TODO: В случае, если новая длина массива больше прежней, вставляемые в конец
				   // массива элементы должны инициализироваться значением по умолчанию для типа T.
	void Clear();
	int GetSize() const;

	T* begin();
	const T* begin() const;
	T* end();
	const T* end() const;
	std::reverse_iterator<T*> rbegin();
	const std::reverse_iterator<T*> rbegin() const;
	std::reverse_iterator<T*> rend();
	const std::reverse_iterator<T*> rend() const;

	T& operator[](int index); // TODO: В случае, если индекс элемента выходит за пределы массива,
							  // должно выбрасываться исключение std::out_of_range
	const T& operator[](int index) const;

	MyArray& operator=(const MyArray& other);
	MyArray& operator=(MyArray&& other);

private:
	T* m_values;
	size_t m_size;
};

template <typename T>
MyArray<T>::MyArray()
	: m_values(nullptr)
	, m_size(0)
{
}

template <typename T> MyArray<T>::~MyArray() { Clear(); }

template <typename T>
MyArray<T>::MyArray(const MyArray& other)
	: m_values(nullptr)
	, m_size(other.m_size)
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
{
	other.m_values = nullptr;
	other.m_size = 0;
}

#endif // MYARRAY_H
