#include <iostream>
#include <map>
#include <memory>
#include <memory_resource>

//// Создание аллокатора
template<typename T, size_t pre_size>
struct MyAllocator
{
	T* m_memory;
	
	size_t m_position{ 0 };

	MyAllocator()
	{
		m_memory = ::operator new(pre_size);
	}

	T* allocate(const size_t n)
	{
		if (m_position + n > pre_size)
		{
			throw std::bad_alloc{"no more memory!"};
		}

		const auto result = m_memory + m_position;
		m_position += n;
		return result;
	}

};

template<typename Allocator>
void factorial(std::map<int, int, std::less<int>, Allocator> & factor);

int main()
{	
	std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>, 10>> myMap;

	std::map<int, int> myMap;

	/*factorial(myMap);*/

	for (const auto f : myMap)
	{
		std::cout << f.first << " " << f.second << std::endl;
	}
}


template<typename Allocator>
void factorial(std::map<int, int, std::less<int>, Allocator>& factor)
{
	for (int i = 0; i < 10; i++)
	{
		factor[i] = 1;

		if (i == 0)
		{
			factor[i] = 1;
		}
		else
		{
			for (auto p = 1; p <= i; p++)
			{
				factor[i] = factor[i] * p;
			}
		}
	}
}
