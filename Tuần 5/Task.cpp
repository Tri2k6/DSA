#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#define fileName "input.txt"
#define outFile "output.txt"

typedef struct leader *lref;
typedef struct trailer *tref;

struct leader
{
	int value, count; // count in the number of elements in front of it
	lref next;
	tref trail;
};

struct trailer
{
	lref id;
	tref next;
};

void readFile(const char *name, std::vector<int> &arr, int &n)
{
	std::ifstream in(name);
	if (!in)
	{
		std::cout << "Invalid input file.";
		return;
	}

	n = 0;

	std::string line;
	std::getline(in, line);
	std::stringstream stream = std::stringstream(line);

	char buffer;
	int c;
	while (stream >> buffer)
	{
		stream >> c;
		arr.push_back(c);
		stream >> buffer;

		stream >> c;
		arr.push_back(c);
		stream >> buffer;

		n += 2;
	}

	in.close();
}

lref addList(lref head, lref &tail, int key, int &size)
{
	lref h = head;
	tail->value = key;

	while (h->value != key) // check if value is in the list
		h = h->next;

	if (h == tail) // value is not in the list
	{
		tail = new leader;
		size++;
		h->count = 0;
		h->trail = nullptr;
		h->next = tail;
	}
	return h;
}

void freeList(lref head, lref tail)
{
	lref p = head, q;
	tref u, v;

	while (p)
	{
		q = p->next;
		u = p->trail;

		while (u)
		{
			v = u->next;
			delete u;
			u = v;
		}

		delete p;
		p = q;
	}
}

int main()
{
	std::vector<int> arr;
	int n;

	readFile(fileName, arr, n);

	lref head = new leader;
	lref tail = head, p, q;
	tref t;
	int size = 0, i = 0;
	int x = arr[i++], y;
	while (i < n)
	{
		y = arr[i++];
		p = addList(head, tail, x, size);
		q = addList(head, tail, y, size);
		t = new trailer;
		t->id = q; // add y to x's trailer
		t->next = p->trail;
		p->trail = t;
		q->count++;
		x = arr[i++]; // read in the next x
	}

	p = head;
	head = nullptr;
	while (p != tail) // find nodes with count = 0 (starting nodes) and connect them to head
	{
		q = p;
		p = p->next;
		if (q->count == 0)
		{
			q->next = head;
			head = q;
		}
	}

	std::vector<int> output(size);
	int k = 0;

	q = head;
	while (q)
	{
		output[k++] = q->value; // print the value of the starting nodes
		size--;
		t = q->trail; // read the trailer of that starting nodes
		q = q->next;
		while (t)
		{
			p = t->id; // for each node in the trailer, reduce count by 1
			p->count--;
			if (p->count == 0) // new starting node found
			{
				p->next = q;
				q = p;
			}
			t = t->next;
		}
	}

	std::ofstream out(outFile);
	if (!out)
	{
		std::cout << "Invalid output file.";
		return -1;
	}

	if (size)
		out << "-1";
	else
	{
		for (int c = 0; c < k; c++)
		{
			out << output[c] << ' ';
		}
	}

	freeList(head, tail);
	out.close();
}