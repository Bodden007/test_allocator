#include <iostream>
#include <map>
#include <memory>
#include <memory_resource>

// Создание аллокатора
template <typename T>
struct MyAllocator {
	using value_type = T;
	const size_t pre_size = 10;

	MyAllocator()
	{
		m_memory = static_cast<T*>(::operator new(pre_size * sizeof(T)));
	}
	
	~MyAllocator() 
	{
		::operator delete(m_memory);
	};

	template <typename U>
	MyAllocator(const MyAllocator<U>&) {}

	T* allocate(const size_t n) {
		
		if (n > 10)
			throw std::bad_alloc();

		return static_cast<T*>(::operator new(pre_size * sizeof(T)));
		
	}

	void deallocate(T* p, std::size_t) {
		
	}

private:
	T* m_memory{nullptr};

};

template<typename Allocator>
void factorial(std::map<int, int, std::less<int>, Allocator> & factor);

int main()
{	
	std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>>> myMap;

	factorial(myMap);

	for (const auto f : myMap)
	{
		std::cout << f.first << " " << f.second << std::endl;
	}
}


template<typename Allocator>
void factorial(std::map<int, int, std::less<int>, Allocator>& factor)
{
	for (int i = 0; i < 9; i++)
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
