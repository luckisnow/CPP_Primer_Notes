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


//**����**���������Ĺؼ��ֱ��붨����<���������ΪĬ��ʹ����������������˳���
// ������ѭ�ϸ����� 1.������ ����a<bͬʱb>a 2.�ɴ��� a<b c<a��c<b 3.a>=b&&b>=a��a==b

//���һ���ؼ�������û�ж���<�����,���Դ���һ������ָ��,��ָ��ָ��ĺ����ܴ���<�����
//ע��ú���ָ������ģ�����ʱҪ��д,Ϊ���ñ������ܴ�����������
//�ڶ����������͵�ʱ��Ҫ����,Ϊ�˳�ʼ��ģ���еĺ���ָ��
//����:
//1.�����Ƕ���һ����,�����û�ж���<�����
class key
{
public:
	std::string name;
};
//2.�Զ������Ĭ��<����ĺ���
bool CustomOrderOperator(const key& v1, const key& v2)
{
	return v1.name.compare(v2.name);
}

//3.���������������
std::multiset<key, bool(*)(const key&, const key&) > ms(CustomOrderOperator);

//Pair�����൱��C#�е�KeyValuePair
//������public��Աfirst��second�൱��key��Ա��value��Ա
//��make_pair(v1,v2)�ܵõ�һ��pair
std::pair<string, string> p{ "a","B" };

//key_type ����map��˵��key������ ����set��˵Ҳ��key������
//mapped_type ����map��˵��value������ ����set��˵û��
//value_type ����map��˵��pair<cosnt key,value>������ ע��pair���firstԪ����const��  ����set��˵��key����
set<string> strSet;
map<string, int> strIntMap;
set<string>::key_type v = "asdf";//std::string
set<string>::value_type v = "asdf";//std::string
map<string, int>::key_type v = "asdf";//std::string
map<string, int>::value_type v;//std::pair<const string,int>
map<string, int>::mapped_type v=1 ;//int

//set��iterator������֮��õ���const���͵�ֵ,ֻ�ܶ�,����д.
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
//1.�ܶ���vector<int>::iterator��Ϊ���������Ĺؼ���ô
//�� ��Ϊvector��iterator�����iterator֧��<����
//2. �ܶ���list��iteratorΪ���������Ĺؼ���ô
//���� ��Ϊlist��iterator��ǰ��iterator ��֧��<����
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