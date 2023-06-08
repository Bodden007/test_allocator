#include <iostream>
#include <map>
#include <memory>
#include <memory_resource>

// Создание аллокатора
template<typename T, size_t pre_size >
struct MyAllocator
{
	using value_type = T;

	T* m_memory{nullptr};
	
	/*size_t pre_size = 10;*/
	size_t m_position{ 0 };

	//template <typename U, size_t pre_size>
	//MyAllocator(const MyAllocator<U>&, size_t pre_size) {}

	MyAllocator()
	{
		m_memory = ::operator new(pre_size);
	}

	T* allocate(size_t n)
	{
		if (m_position + n > pre_size)
		{
			throw std::bad_alloc();
		}

		const auto result = m_memory + m_position;
		m_position += n;
		return result;
	}

	void deallocate(T* p, std::size_t) {
		operator delete(p);
	}
};


template<typename Allocator>
void factorial(std::map<int, int, std::less<int>, Allocator> & factor);

int main()
{	
	std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>,10>> myMap;

	/*std::map<int, int> myMap;*/

	factorial(myMap);

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
