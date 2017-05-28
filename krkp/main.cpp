#include <iostream>
#include <vector>
#include <string>
#include <QtWidgets>
#include <QVector>
#include <stack>
#include <unistd.h>

class Modifier : public QObject {
	Q_OBJECT
public:
	/* Constructor wih user defined function */
	Modifier(void(*_userFunc)(double&)) : userFunc(_userFunc) { }
	Modifier(std::string _name, void(*_userFunc)(double&)) : name(_name), userFunc(_userFunc) { }

	/* Constructor with empty lambda function */
	Modifier() : userFunc([](double&){}) { }
	Modifier(std::string _name) : name(_name), userFunc([](double&){}) { }

	std::string name;
	void (*userFunc)(double&);

public slots:
	void modifierSlot(double val) {
		userFunc(val);
		emit modSignal(val);
	}

signals:
	void modSignal(double val);
};

class Prop : public QObject{
	Q_OBJECT
public:
	std::string name;
	Prop(std::string _name, double _val) : name(_name), propVal(_val) { }
	Prop(double _val) : propVal(_val) { }

	double propVal;
public slots:
	void propSlotChangeVal(double changeVal) {
		propVal += changeVal;
	}
	void propSlotOverwriteVal(double val) {
		propVal = val;
	}
};

class Object {
public:
	Object() { }
	Object(std::string _name) : name(_name) { }
	std::string name;

	QVector<Prop*> objProp;
	void addProp(double val) {
		objProp.push_back(new Prop(val));
	}
	void addProp(std::string _name, double val) {
		objProp.push_back(new Prop(_name, val));
	}

	std::string whoami() {
		std::string res = "";
		res += "Object: " + name + '\n';
		res += "Has Properties: ";
		if(objProp.size() != 0) {
			res += '\n';
			QVector<Prop*>::iterator it = objProp.begin();
			while(it != objProp.end()) {
				res += (*it)->name + '\n';
				it++;
			}
		} else res += "NO\n";

		return res;
	}


	~Object() {
		for(size_t i = 0; i < objProp.size(); ++i) {
			delete objProp[i];
		}
	}
};

class Container : public QObject {
	Q_OBJECT

public:
	Container() {
		next = NULL;
		obj = NULL;
		contProp = NULL;
   	}

	Container(const std::string& _name) : name(_name) {
		next = NULL;
		obj = NULL;
		contProp = NULL;
   	}

	std::string name;

	Container* next;
	Object* obj;
	Prop* contProp;
	QVector<Modifier*> contMods;

	void addProp(std::string _name,double _val)
	{
		 contProp = new Prop(_name, _val);
	}

	void addModifier(void(*_userFunc)(double&)) {
		contMods.push_back(new Modifier(_userFunc));
	}
	void addModifier() {
		contMods.push_back(new Modifier());
	}

	void addModifier(std::string _name, void(*_userFunc)(double&)) {
		contMods.push_back(new Modifier(_name, _userFunc));
	}
	void addModifier(std::string _name) {
		contMods.push_back(new Modifier(_name));
	}

	Container* searchContainer(const std::string& _name) {
		Container* nx = this;
		while(nx->name != _name) {
			nx=nx->next;
			if(nx == NULL) break;
		}

		return nx;
	}

	Object* searchObject(const std::string& _name) {
		Container* nx = this;
		bool found = false;

		while(!found) {
			if(nx->obj != NULL) {
				if((nx->obj->name) == _name) {
					found = true;
					continue;
				}
			}
			nx=nx->next;

			if(nx == NULL) {
				break;
			}
		}

		if(!found) {
			return NULL;
		}

		return nx->obj;

	}

	Modifier* searchModifier(const std::string& _name)
	{
		if(!contMods.isEmpty())
		{
			for(int i=0;i<contMods.size();++i)
			{
				if(contMods[i]->name == _name)							
				{						
					return contMods[i];

				}
			}
		}
		return NULL;
	}
		
		


	void mkNestedContainers(QVector<std::string> cnts) {
		if(this->next != NULL) {
			//exception here
			return;
		}
		QVector<std::string>::iterator it = cnts.begin();
		Container* currentContainer = this;
		while(it != cnts.end()) {
			currentContainer->next = new Container(*it);
			currentContainer = currentContainer->next;
			it++;
		}
	}

	std::string whoami() {
		std::string res = "";
		res += "Container name: " + name + '\n';
		res += "Has next container: ";

		if(next == NULL) res += "NO\n";
		else res += next->name + '\n';

		res += "Has object: ";
		if(obj == NULL) res += "NO\n";
		else res += obj->name + '\n';

		res += "Container Modifiers: ";
		if(contMods.size() != 0) {
			res += '\n';
			QVector<Modifier*>::iterator it = contMods.begin();
			while(it != contMods.end()) {
				res += (*it)->name + '\n';
				it++;
			}
		} else res += "NO\n";

		res += "Has Properties: ";
		if(contProp == NULL) res += "NO\n";
		else res += contProp->name + '\n';

		return res;

	}

	void addObject() {
		if(obj != NULL) {
			delete obj;
		}
		obj = new Object();
	}
	void addObject(std::string _name) {
		if(obj != NULL) {
			delete obj;
		}
		obj = new Object(_name);
	}

	~Container() {
		for(size_t i = 0; i < contMods.size(); ++i) {
			delete contMods[i];
		}

		if(obj != NULL) {
			delete obj;
		}
		if(next != NULL) {
			delete next;
		}
		if(contProp != NULL){
		 delete contProp;
		 }
	}


};

/*
void PlusTwo(double& val) {
	//std::cout << "PlusTwo work " << val << std::endl;
	val += 2;
}
void Outt(double& value) {
	std::cout << value;
}
*/

void heat(double& h) {
	h += 5;
}

void closed(double& h) {
	h -= 0.2*h;
}


int main() {


	Container room("room");
	room.addModifier("heat", heat);
	room.addProp("temperature",25);
	room.next = new Container("table"); //Table
	room.next->next = new Container("bottle"); //Bottle
	room.next->next->addModifier("closed", closed); //The bottle is closed now
	room.next->next->addObject("milk"); //Milk is in the bottle
	room.next->next->obj->addProp("temperature", 10); //Initial temperature of milk is 10


	std::cout << "Connecting..." << std::endl;
	//Connect room to bottle
	QObject::connect(room.searchModifier("heat"), SIGNAL(modSignal(double)), room.searchContainer("bottle")->searchModifier("closed"), SLOT(modifierSlot(double)));
	//Connect bottle to the milk
	QObject::connect(room.searchContainer("bottle")->searchModifier("closed"), SIGNAL(modSignal(double)), room.searchObject("milk")->objProp[0], SLOT(propSlotChangeVal(double)));

//	std::cout << "Passing signal..." << std::endl;

//	std::cout << "Reading signal..." << std::endl;
	std::cout<<"room temperature: "<<room.contProp->propVal<<std::endl;
	std::cout<<"milk initial temperature: " << room.searchObject("milk")->objProp[0]->propVal<<std::endl;

	std::cout << room.whoami();
	while(room.contProp->propVal > room.searchObject("milk")->objProp[0]->propVal)
	{
		room.searchModifier("heat")->modifierSlot(0);
		std::cout<<"milk temperature: "<< room.searchObject("milk")->objProp[0]->propVal<<std::endl;
		sleep(1);
	}


	return 0;
}
#include "mmm.moc"
