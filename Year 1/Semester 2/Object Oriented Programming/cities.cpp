#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

class localitate {
protected:
	char* nume;
	int numar_loc;
public:
	localitate() : nume(nullptr), numar_loc(0) {}

	localitate(const char* n, int l) {

		this->nume = new char[strlen(n) + 1];
		strcpy(this->nume, n);

		this->numar_loc = l;
	}

	virtual void print() = 0;
	virtual void citire() = 0;

	virtual ~localitate() {
		if (this->nume != nullptr) delete[] this->nume;
		this->numar_loc = 0;
	}
};

class sat : public localitate {

public:
	sat() : localitate() {}
	sat(const char* n, int l) : localitate(n, l) {}

	void print() override{

		cout << " Sat. Nume: " << this->nume << " - Numar locuitori: " << this->numar_loc;

	}
	void citire() override {

		this->nume = new char[30];

		cout << "\nCitire sat:\n";
		cout << "Introduceti numele satului: "; cin >> this->nume;
		cout << "Introduceti numaru lde locuitori: "; cin >> this->numar_loc;
	}

};

class oras : public localitate {
protected:
	int blocuri;
public:
	oras() : localitate(), blocuri(0) {}
	oras(const char* n, int l, int b) : localitate(n, l), blocuri(b) {}
	
	void print() override {

		cout << " Oras. Nume: " << this->nume << " - Numar locuitori: " << this->numar_loc << " - Numarul de blocuri din oras: " << this->blocuri;

	}
	void citire() override {

		this->nume = new char[30];

		cout << "\nCitire oras:\n";
		cout << "Introduceti numele orasului: "; cin >> this->nume;
		cout << "Introduceti numarul lde locuitori: "; cin >> this->numar_loc;
		cout << "Introduceti nuamrul de blocuri din oras: "; cin >> this->blocuri;
	}
};

class Judet {
protected:
	localitate** locs;
	int numar_locs;
public:
	Judet() : locs(nullptr), numar_locs(0) {}

	Judet(localitate** l, int numar_l) {

		this->numar_locs = numar_l;

		this->locs = new localitate * [this->numar_locs];
		for (int i = 0; i < this->numar_locs; i++) {

			this->locs[i] = l[i];
		}
	}

	void citire() {
		cout << "\nCate localitati vreti sa introduceti in judet?: "; cin >> this->numar_locs;

		this->locs = new localitate*[this->numar_locs];

		int input;
		for (int i = 0; i < this->numar_locs; i++) {
			while (true) {
				cout << "\n1.Oras   ;    2. Sat: ";
				cin >> input;
				if (input < 1 || input > 2) cout << "Input invalid, mai incearca inca o data";
				else {

					if (input == 1) this->locs[i] = new oras, this->locs[i]->citire();
					else this->locs[i] = new sat, this->locs[i]->citire();

					break;
				}
			}
		}

	}

	void afisare() {
		cout << "\n\n Afisare judet: \n\n";

		if (this->numar_locs == 0) cout << "Judetul nu are localitati";
		else {

			for (int i = 0; i < this->numar_locs; i++) {
				cout << i + 1 << ". ";
				this->locs[i]->print();
				cout << "\n";
			}

		}
		cout << "\n\n\n";
	}

	~Judet() {
		if (this->locs != nullptr) {
			for (int i = 0; i < this->numar_locs; i++) {
				delete this->locs[i];
			}
			delete[] this->locs;
			this->numar_locs = 0;
		}
	}
};

int main() {

	Judet j;

	j.citire();
	j.afisare();

	return 0;
}
