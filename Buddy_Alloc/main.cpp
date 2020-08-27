// Physical-Virtual Memory Mapping Simulation 
// using buddy allocation
// created by Nils Lübben

#include <iostream>
#include <string>
#include <vector>




struct Memory
{

	using pa = std::pair<std::string, int>;

	// [ Name of Block, Order of Block division ]
	std::vector<pa> allocs;
	
	int total_size;
	int granularity;

	Memory()
		: allocs(), granularity(4), total_size(64)
	{
		allocs.push_back(std::make_pair("FREE", log2(float(total_size) / float(granularity))));
		std::cout << "Constr: " <<  (1 << allocs[0].second) * granularity << "kb" << std::endl;
	}

	void print() const
	{
		for (auto e : allocs)
			std::cout << "[ " << e.first << ", 2^" << e.second << " ] " << std::endl;
		std::cout << "------------------------------------" << std::endl;
	}

	bool allocate(std::string name, int size)
	{	
		bool done = false;
		for (auto it = allocs.begin(); it != allocs.end() && !done ; it++)
		{
			if (it->first == "FREE" && (1 << (it->second)) * granularity >= size)
			{
				int n = it->second;

				while (n >= 0)
				{
					// check if new block fits in if we devide the current block
					// if not we found the block
					// if n = 0, subsequent divide check fails, base case met
					if ((1 << n - 1) * granularity >= size)
					{

						//std::cout << ((1 << n - 1) * granularity) << ">" << size << std::endl;
						n--;
						it = allocs.insert(it, std::make_pair("FREE", n));
						(it + 1)->second = n;
					}
					else
					{
						//std::cout << name << ": " << (1<<n)*4 << std::endl;;
						it->first = name;
						return true;
					}
				}
			}
		}
		return false;
	}

	bool remove(std::string name)
	{
		for (auto it = allocs.begin(); it != allocs.end(); it++)
		{
			if (it->first == name)
			{
				it->first = "FREE";
				free();
				return true;
			}
		}
		return false;
	}

	//frees leaves
	void free()
	{
		//find adjacent free blocks
		for (auto it = allocs.begin(); (it + 1) != allocs.end();)
		{
			if (it->first == "FREE" && (it + 1)->first == "FREE"
				&& it->second == (it + 1)->second)
			{
				//merge blocks
				it = allocs.erase(it);
				it->second++;
			}
			else
			{
				it++;
			}
		}
	}

	void printAdress()
	{
		int sum = 0;
		for (auto b : allocs)
		{
			if (b.first != "FREE")
				std::cout << b.first << " at " << sum << std::endl; //TODO make hex
			sum += (1 << b.second) * granularity;
		}
	}
};


int main(void)
{

	//example allocations
	Memory mem;
	mem.print();
	mem.allocate("A", 32);
	mem.print();
	mem.allocate("B", 3);
	mem.print();
	mem.allocate("C", 15);
	mem.print();
	mem.remove("B");
	mem.print();
	mem.remove("C");
	mem.print();
	mem.remove("A");
	mem.print();


	return 0;
}