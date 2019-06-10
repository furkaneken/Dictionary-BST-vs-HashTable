#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
using namespace std;



template <class x>
class node
{
public:
	x english;
	x turkish;
	node *left = NULL;
	node *right = NULL;

};
template <class x>
class BT               // binary tree
{
public:
	void insert(x newword, x newtrans);
	node<x>* search(x key);
	void newtrans(x word, x newtrans);
	void newword();
	node<x> * root = NULL;




};
template <class x>
void BT<x>::insert(x newword, x newtrans)
{

	node<string> *temp = new node<string>;

	temp->english = newword;
	temp->turkish = newtrans;

	if (root == NULL)
	{
		root = temp;

	}
	else if (root != NULL)
	{
		node<string>* temproot = new node<string>;
		temproot = root;
		while (temproot != NULL)
		{
			if (newword < temproot->english)
			{
				if (temproot->left == NULL)
				{
					temproot->left = temp;
					break;
				}
				temproot = temproot->left;
			}
			else if (newword > temproot->english)
			{
				if (temproot->right == NULL)
				{
					temproot->right = temp;
					break;
				}
				temproot = temproot->right;
			}
			else if (newword == temproot->english)
			{
				/*cout << "this word already exist" << endl;*/
				break;
			}
		}


	}
}
template <class x>
node<x>* BT<x>::search(x key)
{
	bool a = false;
	node<string> * current = new node<string>;
	current = root;
	/*cout << "visiting nodes : " << endl;*/
	while (current != NULL && current->english != key)
	{
		if (current != NULL)
		{
			/*cout << current->english << endl;*/
			if (key <= current->english)
			{
				current = current->left;
			}
			else if (key >= current->english)
			{
				current = current->right;
			}
		}


	}
	if (current == NULL)
	{
		a = true;
		/*cout << "no element in tree" << endl;*/
		return 0;

	}
	if (!a)
	{
		return current;
	}


}
template <class x>
void BT<x>::newword()
{
	cout << "enter new word :";
	string newword;
	cin >> newword;
	cout << endl;
	node * temp = new node;
	temp = this->search(newword);
	if (temp->english == newword);
	{
		cout << "world already exist, if you want to add new translation please use command 2" << endl;
	}
	if (temp->english != newword)
	{
		cout << "Enter new translation :";
		string trans;
		cin >> trans;
		cout << endl;
	}
}
template <class x>
void BT<x>::newtrans(x trans, x newtrans)
{
	node<string> * temp = new node<string>;
	temp = search(trans);
	temp->turkish = newtrans;
	cout << endl;
	cout << "**UPDATED**";
	cout << endl;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




bool IsPrime(int number)
{

	if (number == 2 || number == 3)
		return true;

	if (number % 2 == 0 || number % 3 == 0)
		return false;

	int divisor = 6;
	while (divisor * divisor - 2 * divisor + 1 <= number)
	{

		if (number % (divisor - 1) == 0)
			return false;

		if (number % (divisor + 1) == 0)
			return false;

		divisor += 6;

	}

	return true;

}

int NextPrime(int a)
{

	while (!IsPrime(++a))
	{
	}
	return a;

}




template <class x>
struct Node1
{
	x eng;
	x tr;
	Node1 *next = NULL;

};
template <class x>
class hashtable
{
public:
	vector<Node1<x>> elementvector;
	hashtable();
	int elementin = 0;
	void rehash();
	long hashfunc(x eng, int size);
	void insert(x eng, x tr);
	x search(x eng);
	/*void deleteelement(string eng);*/

private:

};
template <class x>
hashtable<x>::hashtable()
{
	elementvector.resize(53);
}
template <class x>
void hashtable<x>::rehash()
{
	cout << "rehashed..." << endl;
	elementin = 0;
	int oldsize = this->elementvector.size();
	int newsize = NextPrime(oldsize * 2);
	vector<Node1<x>> newvector(newsize);
	for (int i = 0; i < oldsize; i++)
	{
		if (this->elementvector[i].eng != "")
		{
			int newkey = hashfunc(this->elementvector[i].eng, newsize);
			while (newvector[newkey].eng != "")
			{
				newkey = newkey + 1;
			}
			newvector[newkey].eng = this->elementvector[i].eng;
			newvector[newkey].tr = this->elementvector[i].tr;
			elementin++;
			while (this->elementvector[i].next != NULL)
			{
				newkey++;
				while (newvector[newkey].eng != "")
				{
					newkey = newkey + 1;
				}
				newvector[newkey].eng = this->elementvector[i].next->eng;
				newvector[newkey].tr = this->elementvector[i].next->tr;
				elementin++;
				this->elementvector[i].next = this->elementvector[i].next->next;
			}
			
		}
		

	}
	this->elementvector = newvector;

	cout << "previous table size: " << oldsize << ", new table size: " << newsize << " , current unique word count: " << elementin << " current load factor:" << (double(elementin) / double(newsize)) << endl;






}
template <class x>
long hashtable<x>::hashfunc(x eng, int size)
{
	int len = eng.length();
	long hash = 5381;
	int i = 0;

	for (i = 0; i < len; i++)
	{
		hash = (((hash << 5) + hash) + (eng[i]));
	}
	/*unsigned int fornow = hash % size;	*/
	/*if (fornow < 0)
	{
		fornow = fornow + size;
	}*/

	hash = hash % size;
	if (hash < 0)
	{
		hash = hash + size;
	}
	return hash;
}
template <class x>
void hashtable<x>::insert(x eng, x tr)
{
	int size = this->elementvector.size();           // vectorumuzun size ýný alýyoruz
	int index = hashfunc(eng, size);                   // yeni kelime için pozisyon buluyoruz

	if (this->elementvector[index].eng == "")           // o pozisyonun bos olduðunu kontrol ediyoruz
	{
		this->elementvector[index].eng = eng;          // koyuyoruz
		this->elementvector[index].tr = tr;
	}
	else if (this->elementvector[index].eng != "")          // bos degilse diyoruz
	{
		Node1<x> *temp = new Node1<x>;
		temp = &(this->elementvector[index]);           // bir tempe esitliyoruz simdilik o bos olmayan yeri
		while (temp->next != NULL)                   // bos yer arýyoruz
		{
			temp = temp->next;
		}
		Node1<x> *temp2 = new Node1<x>;
		temp2->eng = eng;
		temp2->tr = tr;
		temp->next = temp2;             // kelimeyi oraya koyuyoruz
	}

	elementin++;
	double of = (double)elementin / (double)this->elementvector.size();
	if (of >= 0.5)
	{
		this->rehash();
	}

}
template <class x>
x hashtable<x>::search(x eng)
{
	int pos = hashfunc(eng, this->elementvector.size());
	if (this->elementvector[pos].eng == eng)
	{
		return this->elementvector[pos].tr;
	}
	else if (this->elementvector[pos].next != NULL)
	{
		Node1<x> *temp = new Node1<x>;
		temp = elementvector[pos].next;
		while (temp != NULL)
		{
			if (temp->eng == eng)
			{
				return temp->tr;
				break;
			}
			temp = temp->next;
		}
	}
	else 
	{
		while (this->elementvector[pos].eng != "")
		{
			if (this->elementvector[pos].eng == eng)
			{
				return this->elementvector[pos].tr;
				break;
			}
			pos++;
			
		}
		{
			cout << "this element not in the dict." << endl;
		}
	}
	
	
	
}

int main()
{

	hashtable<string> ht;
	ifstream file;
	file.open("dict.txt");
	cout << "building binary tree for dict.txt..." << endl;
	cout << "building binary tree for dict.txt..." << endl;
	string line;
	while (getline(file, line))
	{

		string final;
		istringstream read(line);
		string eng;
		string tr;
		read >> eng;
		std::transform(eng.begin(), eng.end(), eng.begin(), ::tolower);
		while (read >> tr)
		{
			if (tr != "")
			{
				final = final + tr + " ";
			}
		}
		if (eng != "")
		{
			ht.insert(eng, final);
		}

	}
	file.close();
	BT<string> binarytree;
	ifstream file1;
	file1.open("dict.txt");
	/*cout << "building binary tree for dict.txt..." << endl;*/
	string line1;
	while (getline(file1, line1))
	{

		string final;
		istringstream ikra(line1);
		string eng;
		string tr;
		ikra >> eng;
		std::transform(eng.begin(), eng.end(), eng.begin(), ::tolower);
		while (ikra >> tr)
		{
			if (tr != "")
			{
				final = final + tr + " ";
			}
		}
		if (eng != "")
		{
			binarytree.insert(eng, final);
		}

	}
	file.close();
	cout << "Running queries in query.txt..." << endl;
	cout << "***********************************************" << endl;
	cout << "Benchmark results for Binary Search Tree (BST):" << endl;
	cout << "***********************************************" << endl;



	
	


	ifstream file2;
	file2.open("query.txt");
	string line2;
	int count = 0;
	auto start = std::chrono::high_resolution_clock::now();
	while (getline(file2, line2))
	{

		string final2;
		istringstream read(line2);
		string eng2;
		/*string tr;*/
		read >> eng2;
		std::transform(eng2.begin(), eng2.end(), eng2.begin(), ::tolower);
		if (eng2 != "")
		{
			count++;
			binarytree.search(eng2);
		}

	}
	auto time = (std::chrono::high_resolution_clock::now() - start).count();

	cout << "+ Elapsed time: " << time <<" ns" << endl;
	cout << "+ Avarage query time: " << (double)time / count << " ns" <<endl;



	
	cout << "***********************************************" << endl;
	cout << "Benchmark results for Hash Table:" << endl;
	cout << "***********************************************" << endl;

	ifstream file3;
	file3.open("query.txt");
	string line3;
	int count2 = 0;
	auto start1 = std::chrono::high_resolution_clock::now();
	while (getline(file3, line3))
	{

		string final3;
		istringstream read(line3);
		string eng3;
		/*string tr;*/
		read >> eng3;
		std::transform(eng3.begin(), eng3.end(), eng3.begin(), ::tolower);
		if (eng3 != "")
		{
			count2++;
			ht.search(eng3);
		}

	}
	auto time1 = (std::chrono::high_resolution_clock::now() - start1).count();
	double  ortalama = (double)time1 / (double)count2;
	cout << "+ Elapsed time: " << time1 << " ns" << endl;
	cout << "+ Avarage query time: " << ortalama << " ns" << endl;
	cout << "+ Speed Up:" << (double)time / time1 << "x" << endl;



	cout << "Time measurements in ns (N, 4096N):" << endl;
	cout << "*****************************" << endl;
	cout << "bst" << endl;
	cout << "N         time" << endl;
	int n = 1;
	while (n <= 4096)
	{
		auto start5 = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n; i++)
		{

			ifstream file2;
			file2.open("query.txt");
			string line2;
			int count = 0;
			while (getline(file2, line2))
			{

				string final2;
				istringstream read(line2);
				string eng2;
				/*string tr;*/
				read >> eng2;
				std::transform(eng2.begin(), eng2.end(), eng2.begin(), ::tolower);
				if (eng2 != "")
				{
					count++;
					binarytree.search(eng2);
				}

			}

		}
		auto time5 = (std::chrono::high_resolution_clock::now() - start5).count();
		cout << n << "         " << time5 << endl;
		n = n * 2;
	}
	cout << endl;
	cout << "ht" << endl;
	cout << "N         time" << endl;
	int n1 = 1;
	while (n1 <= 4096)
	{
		auto start6 = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n1; i++)
		{

			ifstream file2;
			file2.open("query.txt");
			string line2;
			int count = 0;
			while (getline(file2, line2))
			{

				string final2;
				istringstream read(line2);
				string eng2;
				/*string tr;*/
				read >> eng2;
				std::transform(eng2.begin(), eng2.end(), eng2.begin(), ::tolower);
				if (eng2 != "")
				{
					count++;
					ht.search(eng2);
				}

			}

		}
		auto time6 = (std::chrono::high_resolution_clock::now() - start6).count();
		cout << n1 << "         " << time6 << endl;
		n1 = n1 * 2;
	}







	
	/*ifstream file2;
	file2.open("query.txt");
	string line2;
	while (getline(file2, line2))
	{

		string final2;
		istringstream read(line2);
		string eng2;
		string tr;
		read >> eng2;
		std::transform(eng2.begin(), eng2.end(), eng2.begin(), ::tolower);
		if (eng2 != "")
		{
			cout << ht.search(eng2) << endl;
		}

	}*/
	cin.get();
	cin.ignore();
	return 0;



}
