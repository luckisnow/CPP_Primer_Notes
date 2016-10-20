#pragma region Notes

//Associated-Container Types

//1. Is Map or Set
//2. Is Ordered or Unordered
//3. Is Multi-key or Unique-key 

#pragma endregion

#include<string>
#include<iostream>
#include <map> //map,multimap
#include <set>  //set,multiset
#include <unordered_map>//unordered_map,unordered_multimap
#include <unordered_set> //unordered_set,unordered_multiset

#pragma  region using declaration
using std::map; using std::multimap; using std::unordered_map; using std::unordered_multimap;
using std::set; using std::multiset; using std::unordered_set; using std::unordered_multiset;
using std::string; using std::cout; using std::cin; using std::endl;
#pragma  endregion

void CountWordNumber_P375()
{
	map<string, std::size_t>words;
	string word;
	while (cin>>word)
	{
		++words[word];//if add new key-value pair and add the value.
	}
	for (const auto&pair:words)
	{
		cout << pair.first << " occurs " << words[pair.first] << " " << (words[pair.first] > 1 ? "times.":"time.") << endl;
	}
}

int main()
{

	//CountWordNumber_P375();



	system("pause");
	return 0;
}