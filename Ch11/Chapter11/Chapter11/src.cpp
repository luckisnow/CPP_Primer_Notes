#pragma region Include files
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<cctype>
#include<utility>
#include <map> //map,multimap
#include <set>  //set,multiset
#include <unordered_map>//unordered_map,unordered_multimap
#include <unordered_set> //unordered_set,unordered_multiset
#include<initializer_list>
#pragma  endregion

#pragma  region using declaration
using std::map; using std::multimap; using std::unordered_map; using std::unordered_multimap;
using std::set; using std::multiset; using std::unordered_set; using std::unordered_multiset;
using std::string; using std::cout; using std::cin; using std::endl; using std::vector;
using std::ostream_iterator;
#pragma  endregion

#pragma region Notes

//Associated-Container Types

//1. Is Map or Set
//2. Is Ordered or Unordered
//3. Is Multi-key or Unique-key 




void AssocaitedContainerDefinition_Note_N377()
{
	//definition types
	//1. default define
	set<string> d_set;
	//2. with value define
	set<string> v1 = {
		"The","But","And","Or","An","A",
		"the","but","and","or","an","a"
	};
	set<string> v2{
		"The","But","And","Or","An","A",
		"the","but","and","or","an","a"
	};
	//3 copy define
	set<string> c1 = v2;
	set<string> c2(v2);
	set<string> c3{ v2 };
	//4 iterator range
	std::vector<string> strVec;
	set<string> c4(strVec.begin(), strVec.end());
}


//**有序**关联容器的关键字必须定义了<运算符，因为默认使用这个运算符来安排顺序的
// 并且遵循严格弱序 1.单向性 不能a<b同时b>a 2.可传递 a<b c<a则c<b 3.a>=b&&b>=a则a==b

//如果一个关键字类型没有定义<运算符,可以传入一个函数指针,该指针指向的函数能代替<运算符
//注意该函数指针在类模板参数时要填写,为了让编译器能创建出该类型
//在定义容器类型的时候要函数,为了初始化模板中的函数指针
//例如:
//1.如我们定义一个类,这个类没有定义<运算符
class key
{
public:
	std::string name;
};
//2.自定义代替默认<运算的函数
bool CustomOrderOperator(const key& v1, const key& v2)
{
	return v1.name.compare(v2.name);
}

//3.定义有序关联容器
std::multiset<key, bool(*)(const key&, const key&) > ms(CustomOrderOperator);

//Pair类型相当于C#中的KeyValuePair
//有两个public成员first和second相当于key成员和value成员
//用make_pair(v1,v2)能得到一个pair
std::pair<string, string> p{ "a","B" };

//key_type 对于map来说是key的类型 对于set来说也是key的类型
//mapped_type 对于map来说是value的类型 对于set来说没有
//value_type 对于map来说是pair<cosnt key,value>的类型 注意pair里的first元素是const的  对于set来说是key类型
set<string> strSet;
map<string, int> strIntMap;
set<string>::key_type v = "asdf";//std::string
set<string>::value_type v = "asdf";//std::string
map<string, int>::key_type v = "asdf";//std::string
map<string, int>::value_type v;//std::pair<const string,int>
map<string, int>::mapped_type v=1 ;//int

//set的iterator解引用之后得到的const类型的值,只能读,不能写.
#pragma endregion

#pragma  region Exercises

void E114()
{
	set<string> exclude = {
		"The","But","And","Or","An","A",
		"the","but","and","or","an","a"
	};
	map<string, std::size_t>words;
	string word;
	while (cin >> word)
	{
		std::for_each(word.begin(), word.end(), [](char& c) {if (std::isupper(c))c = std::tolower(c); });
		string tmpWord;
		std::copy_if(word.begin(), word.end(), std::back_inserter(tmpWord), [](const char&c) {return std::isalpha(c); });
		if (exclude.find(tmpWord) == exclude.end())//filter exclude word
		{
			++words[tmpWord];//if add new key-value pair and add the value.
		}
	}

	for (const auto&pair : words)
	{
		cout << pair.first << " occurs " << words[pair.first] << " " << (words[pair.first] > 1 ? "times." : "time.") << endl;
	}
}

void E118(std::initializer_list<string> il)
{
	vector<string> resultVec;
	std::unique_copy(il.begin(), il.end(), std::back_inserter(resultVec));
	ostream_iterator<string> oi(cout, "\n");
	std::copy(resultVec.begin(), resultVec.end(), oi);
}

void CountWordNumber_E_P375()
{
	set<string> exclude = {
		"The","But","And","Or","An","A",
		"the","but","and","or","an","a"
	};
	map<string, std::size_t>words;
	string word;
	while (cin>>word)
	{
		if (exclude.find(word)==exclude.end())//filter exclude word
		{
			++words[word];//if add new key-value pair and add the value.
		}
	}

	for (const auto&pair:words)
	{
		cout << pair.first << " occurs " << words[pair.first] << " " << (words[pair.first] > 1 ? "times.":"time.") << endl;
	}
}

void E117_P378()
{
	map<string, vector<string>> Families;
	Families["Fruits"].push_back("Apple");
	Families["Fruits"].push_back("Orange");
	Families["Food"].push_back("Chocolate");
	Families["Food"].push_back("meat");
	Families["Food"].push_back("tomato");
	Families["Food"].push_back("rice");

	for (const auto& family : Families)
	{
		cout << family.first << " Family members: " << endl;
		std::copy(family.second.begin(), family.second.end(), ostream_iterator<string> (cout, "\n"));
	}
}

void E1112_P381(std::initializer_list<string> strings, std::initializer_list<int> ints)
{
	auto strB = strings.begin();
	auto intB = ints.begin();
	vector<std::pair<string, int>> vec;
	for (;strB!=strings.end()&&intB!=ints.end();++strB,++intB)
	{
		vec.push_back(std::make_pair(*strB, *intB));
		vec.push_back({ *strB,*intB });
		vec.push_back(std::pair<string,int>(*strB, *intB));
	}
	for (const auto& onePair:vec)
	{
		cout << onePair.first << "  " << onePair.second << endl;
	}
}

void E1114_P381()
{
	map<string, vector<std::pair<string,string>>> Families;
	Families["Fruits"].push_back({ "Apple" ,"1991.1.1"});
	Families["Fruits"].push_back({ "Orange", "1991.1.1" });
	Families["Food"].push_back({ "Chocolate", "1991.1.1" });
	Families["Food"].push_back({ "meat", "1991.1.1" });
	Families["Food"].push_back({ "tomato", "1991.1.1" });
	Families["Food"].push_back({ "rice", "1991.1.1"});

	for (const auto& family : Families)
	{
		cout << family.first << " Family members: " << endl;
		std::for_each(family.second.begin(), family.second.end(), [](const std::pair<string, string> p) 
		{
			cout << "Name: " << p.first << " BirthDay: " << p.second << endl;
		});
	}
}
//p11.10
//1.能定义vector<int>::iterator作为关联容器的关键字么
//能 因为vector的iterator是随机iterator支持<运算
//2. 能定义list的iterator为关联容器的关键字么
//不能 因为list的iterator是前向iterator 不支持<运算
#pragma endregion
int main()
{

//	CountWordNumber_E_P375();
//	E114();
//	E117_P378();
//	E118({ "example","example","another" });
//	E1112_P381({ "hello","world","CPP" }, { 1,2,3,4 });
	E1114_P381();
	system("pause");
	return 0;
}