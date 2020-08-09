#include <iostream>

using ElemType = char;
class Vektor
{
private:
	ElemType *m_data{nullptr};
	int m_capacity{0};
	int m_size{0};
	bool add_capacity();

public:
	Vektor(const int _cap = 5) : m_capacity(_cap), m_data(new ElemType[_cap])
	{
	}
	virtual ~Vektor();
	bool insert(const int _i, const ElemType &_e);
	bool erase(const int _i);
	bool push_back(const ElemType &_e);
	bool pop_back();
	bool push_front(const ElemType &_e);
	bool pop_front();

	bool get(const int _i, ElemType &_e) const;
	bool set(const int _i, const ElemType &_e);
	int size() const { return m_size; }
	friend std::ostream &operator<<(std::ostream &_os, const Vektor &_v);
};

int main()
{
	using std::cout;
	using std::endl;
	char a;
	Vektor v1;
	v1.push_back('a');
	v1.push_back('b');
	v1.push_back('c');
	cout << v1 << endl;
	v1.insert(1, 't');
	v1.pop_back();
	v1.push_front('y');
	v1.push_front('h');
	v1.push_back('r');
	cout << v1 << endl;
	v1.pop_back();
	v1.pop_front();
	cout << v1 << endl;
	v1.get(0, a);
	cout << a << endl;
	v1.set(2, a);
	cout << v1 << endl;

	return 0;
}

bool Vektor::add_capacity()
{
	ElemType *tmp = new ElemType[2 * m_capacity];
	if (!tmp)
	{
		return false;
	}
	for (auto i = 0; i < m_size; ++i)
	{
		tmp[i] = m_data[i];
	}
	delete m_data;
	m_data = tmp;
	m_capacity *= 2;
	return true;
}

Vektor::~Vektor()
{
	delete m_data;
}

bool Vektor::insert(const int _i, const ElemType &_e)
{
	if (_i < 0 || _i > m_size)
	{
		return false;
	}
	if (m_size == m_capacity && !add_capacity())
	{
		return false;
	}
	for (auto j = m_size; j > _i; --j)
	{
		m_data[j] = m_data[j - 1];
	}
	m_data[_i] = _e;
	++m_size;
	return true;
}

bool Vektor::erase(const int _i)
{
	if (_i >= 0 && _i < m_size)
	{
		for (auto j = _i; j < m_size - 1; ++j)
		{
			m_data[j] = m_data[j + 1];
		}
		--m_size;
		return true;
	}
	return false;
}

bool Vektor::push_back(const ElemType &_e)
{
	if (m_size == m_capacity && !add_capacity())
	{
		return false;
	}
	m_data[m_size] = _e;
	++m_size;
	return true;
}

bool Vektor::pop_back()
{
	if (0 != m_size)
	{
		--m_size;
		return true;
	}
	return false;
}

bool Vektor::push_front(const ElemType &_e)
{
	if (m_size == m_capacity && !add_capacity())
	{
		return false;
	}
	for (auto i = m_size; i > 0; --i)
	{
		m_data[i] = m_data[i - 1];
	}
	m_data[0] = _e;
	++m_size;
	return true;
}

bool Vektor::pop_front()
{
	if (0 == m_size)
	{
		return false;
	}
	if (1 == m_size)
	{
		--m_size;
		return true;
	}
	for (auto i = 0; i < m_size - 1; i++)
	{
		m_data[i] = m_data[i + 1];
	}
	--m_size;
	return true;
}

bool Vektor::get(const int _i, ElemType &_e) const
{
	if (_i >= 0 && _i < m_size)
	{
		_e = m_data[_i];
		return true;
	}
	return false;
}

bool Vektor::set(const int _i, const ElemType &_e)
{
	if (_i > 0 && _i < m_size)
	{
		m_data[_i] = _e;
		return true;
	}
	return false;
}

std::ostream &operator<<(std::ostream &_os, const Vektor &_v)
{
	for (auto i = 0; i < _v.m_size; i++)
	{
		_os << _v.m_data[i] << "\t";
	}
	return _os;
}
