#include <string>
#include <iostream>

using namespace std;

class Investment {
public:
	Investment(string name, int price) {
		m_name = name;
		m_price = price;
	}
	virtual ~Investment() {};
	string name() const {
		return m_name;
	}
	int purchasePrice() const {
		return m_price;
	}
	virtual bool fungible() const = 0;
	virtual string description() const = 0;
private:
	string m_name;
	int m_price;
};

class Painting: public Investment {
public:
	Painting(string name, int price)
		:Investment(name, price)
	{}
	virtual ~Painting() {
		cout << "Destroying " + name() + ", a painting" << endl;
	}
	virtual bool fungible() const {
		return false;
	}
	virtual string description() const {
		return "painting";
	}
};

class Stock: public Investment {
public:
	Stock(string name, int price, string ticker) 
		:Investment(name, price)
	{
		m_ticker = ticker;
	}
	virtual ~Stock() {
		cout << "Destroying " + name() + ", a stock holding" << endl;
	}
	virtual bool fungible() const {
		return true;
	}
	virtual string description() const {
		return "stock trading as " + m_ticker;
	}
private:
	string m_ticker;
};

class House : public Investment {
public:
	House(string name, int price)
		:Investment(name, price)
	{}
	virtual ~House() {
		cout << "Destroying the house " + name() << endl;
	}
	virtual bool fungible() const {
		return false;
	}
	virtual string description() const {
		return "house";
	}
};

void display(const Investment* inv)
{
	cout << inv->name();
	if (inv->fungible())
		cout << " (fungible)";
	cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
}

int foo()
{
	Investment* portfolio[4];
	portfolio[0] = new Painting("Salvator Mundi", 450300000);
	// Stock holdings have a name, value, and ticker symbol
	portfolio[1] = new Stock("Lyft", 50000, "LYFT");
	portfolio[2] = new Stock("GameStop", 10000, "GME");
	portfolio[3] = new House("4 Privet Drive", 660000);

	for (int k = 0; k < 4; k++)
		display(portfolio[k]);

	// Clean up the investments before exiting
	cout << "Cleaning up" << endl;
	for (int k = 0; k < 4; k++)
		delete portfolio[k];

	return 1;
}