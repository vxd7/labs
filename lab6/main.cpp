#include <iostream>
#include <cmath>
#include <string>

class ICalculator {
protected:
	double res;
public:
	virtual void operation() = 0;
	double outResult() {
		return res;
	}

	virtual ~ICalculator() {}
};

class SimpleCalculator : public ICalculator {
public:
	void operation() {
	}
};

class Decorator : public ICalculator {
protected:
	ICalculator *ical;
public:
	Decorator(ICalculator *ic) : ical(ic) { }
};

class SumDecorator : public Decorator {
private:
	double op1_, op2_;
public:
	SumDecorator(ICalculator *ic, double op1, double op2) : Decorator(ic), op1_(op1), op2_(op2) { }

	void operation() {
		res = op1_ + op2_;
		ical->operation();
	}
};

class MulDecorator : public Decorator {
private:
	double op1_, op2_;
public:
	MulDecorator(ICalculator *ic, double op1, double op2) : Decorator(ic), op1_(op1), op2_(op2) { }

	void operation() {
		res = op1_ * op2_;
		ical->operation();
	}
};

class SinDecorator : public Decorator {
private:
	double op_;
public:
	SinDecorator(ICalculator *ic, double op) : Decorator(ic), op_(op) { }

	void operation() {
		res = std::sin(op_);
		ical->operation();
	}

};

int main() {
	ICalculator *mycal = new SumDecorator(new SimpleCalculator(), 1, 2);
	mycal->operation();
	std::cout << mycal->outResult();

	ICalculator *mycal2 = new MulDecorator(new SimpleCalculator(), 2, 3);
	mycal2->operation();
	std::cout << mycal2->outResult();

	ICalculator *mycal3 = new SinDecorator(new SimpleCalculator(), 30);
	mycal3->operation();
	std::cout << mycal3->outResult();

	delete mycal;
	delete mycal2;
	delete mycal3;

	return 0;
}
