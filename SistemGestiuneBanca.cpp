#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>

using namespace std;

class ContBancarSimplu { // base class
protected:
	static int idContIncrementor;

	float sold;
	string titular;
	int idCont; // id unic

public:
	ContBancarSimplu() {
		this->idCont = ContBancarSimplu::idContIncrementor;
		this->sold = 0.0f;
		this->titular = "Default";
		ContBancarSimplu::idContIncrementor++;

	}
	ContBancarSimplu(string titular, float sold) {
		this->titular = titular;
		this->sold = sold;
		this->idCont = ContBancarSimplu::idContIncrementor;
		ContBancarSimplu::idContIncrementor++;

	}
	ContBancarSimplu(ContBancarSimplu &cbs) {
		this->idCont = cbs.idCont;
		this->sold = cbs.sold;
		this->titular = cbs.titular;
		this->idCont = ContBancarSimplu::idContIncrementor;
		ContBancarSimplu::idContIncrementor++;

	}

	string getTitular() {
		return this->titular;
	}
	
	float getSold() {
		return this->sold;
	}

	int getIdCont() {
		return this->idCont;
	}
	static int getIdContIncrementor() {
		return ContBancarSimplu::idContIncrementor;
	}

	void setTitular(string titular) {
		this->titular = titular;
	}
	void setIdCont(int idCont) {
		if (this->idCont < 0) {
			cerr << "idCont nu poate fi negativ" << endl;
			cerr << "idCont nu a fost modifcat. Incercati din nou..." << endl;
		}
		else {
			this->idCont = idCont;
		}
	}

	void setSold(float sold) {
		if (this->sold < 0) {
			cerr << "Soldul nu poate fi negativ" << endl;
			cout << "Soldul nu a fost modificat. Incercati din nou..." << endl;
		}
		else {
			this->sold = sold;
		}
	}

	ContBancarSimplu& operator = (ContBancarSimplu &cbs) {
		this->sold = cbs.sold;
		return *this;
	}
	

	friend ostream& operator << (ostream& os, ContBancarSimplu& cbs) {
		os << "idCont:" << cbs.idCont << endl;
		os << "Titular:" << cbs.titular << endl;
		os << "Sold:" << cbs.sold << endl;
		return os;
	}

	friend ostream& operator << (ostream& os, ContBancarSimplu* cbs) { // supraincarcare pt obiecte dinamice
		if (cbs != nullptr) {
			os << "idCont:" << cbs->idCont << endl;
			os << "Titular:" << cbs->titular << endl;
			os << "Sold:" << cbs->sold << endl;
		}
		else {
			os << "Pointerul nu este alocat" << endl;
		}
		return os;
	}

	friend istream& operator >> (istream& is, ContBancarSimplu& cbs) {
		cout << "Titular:";
		getline(is, cbs.titular);
		cout << "Sold:";
		is >> cbs.sold;

		return is;
	}

	friend istream& operator >> (istream& is, ContBancarSimplu* cbs) { // supraincarcare pt obiecte dinamice

		if (cbs != nullptr) {
			cout << "Titular:";
			getline(is, cbs->titular);
			cout << "Sold:";
			is >> cbs->sold;
		}
		else {
			cout << "Pointerul nu a fost alocat" << endl;
		}
		return is;
	}

	friend ofstream& operator<<(ofstream& ofs, ContBancarSimplu* cbs) {
		ofs << cbs->idCont << endl;
		ofs << cbs->titular << endl;
		ofs << cbs->sold << endl;
		return ofs;
	}

	friend ifstream& operator>>(ifstream& ifs, ContBancarSimplu* cbs) {
		if (cbs != nullptr) {
			string temp;
			getline(ifs, temp);
			cbs->idCont = stoi(temp);

			getline(ifs, cbs->titular);
			
			getline(ifs, temp);
			cbs->sold = stof(temp); // string to float
		
		}
		else {
			cout << "Pointerul nu a fost alocat" << endl;
		}
		return ifs;
	}



	virtual void afisare() {
		cout << "idCont:" << this->idCont << endl;
		cout<< "Titular:" << this->titular << endl;
		cout << "Sold:" << this->sold;
	}


	~ContBancarSimplu() {
		ContBancarSimplu::idContIncrementor--;
	}
};

class ContBancarCredit : public ContBancarSimplu {
private:
	float limitaCredit;

public:
	ContBancarCredit() : ContBancarSimplu(){
		this->limitaCredit = 0.0f;

	}
	ContBancarCredit(string titular,float sold,float limitaCredit) : ContBancarSimplu(titular,sold) {
		this->limitaCredit = limitaCredit;
	}

	ContBancarCredit(ContBancarCredit& cbc) {
		this->idCont = cbc.idCont;
		this->sold = cbc.sold;
		this->titular = cbc.titular;
		this->limitaCredit = cbc.limitaCredit;
		this->idCont = ContBancarSimplu::idContIncrementor;

	}


	float getLimitaCredit() {
		return limitaCredit;
	}

	void setLimitaCredit(float limitaCredit) {
		if (limitaCredit < 0) {
			cerr << "limitaCredit nu poate fi negativ" << endl;
			cout << "limitaCredit nu a fost modificat. Incercati din nou..." << endl;
		}
		else {
			this->limitaCredit = limitaCredit;
		}
	}

	ContBancarCredit& operator = (ContBancarCredit &cbc) {
		this->limitaCredit = cbc.limitaCredit;
	}
	friend ostream& operator << (ostream& os, ContBancarCredit& cbc) {

		ContBancarSimplu temp = cbc; //upcasting
		temp.setIdCont(temp.getIdCont() - 1); // Explicatie: la creearea lui temp, atributul idCont asociat acestuia se incrementeaza si se afiseaza,de aceea noi il vom decrementa inainte de afisare
		os << temp;

		os << "LimitaCredit:" << cbc.limitaCredit<< endl;
		return os;
	}
	friend ostream& operator << (ostream& os, ContBancarCredit* cbc) { // supraincarcare pt obiecte dinamice

		ContBancarSimplu* temp = cbc; //upcasting
		os << temp;

		os << "LimitaCredit:" << cbc->limitaCredit << endl;
		return os;
	}


	 
	friend istream& operator >> (istream& is, ContBancarCredit& cbc) {

		cout << "Titular:";
		getline(is, cbc.titular);
		cout << "Sold:";
		is >> cbc.sold;
		cout << "LimitaCredit:";
		is >> cbc.limitaCredit;

		return is;
	}
	friend istream& operator >> (istream& is, ContBancarCredit* cbc) { // supraincarcare pt obiecte dinamice

		cout << "Titular:";
		getline(is, cbc->titular);
		cout << "Sold:";
		is >> cbc->sold;
		cout << "LimitaCredit:";
		is >> cbc->limitaCredit;

		return is;
	}

	friend ofstream& operator<<(ofstream& ofs, ContBancarCredit& cbc) {
		ofs << "idCont:" << cbc.idCont<< endl;
		ofs << "Titular:" << cbc.titular << endl;
		ofs << "Sold:" << cbc.sold << endl;
		ofs << "LimitaCredit:" << cbc.limitaCredit << endl;
		return ofs;
	}

	friend ifstream& operator>>(ifstream& ifs, ContBancarCredit* cbc) {
		if (cbc != nullptr) {
			cout << "Titular:";
			getline(ifs, cbc->titular);
			cout << "Sold:";
			ifs >> cbc->sold;
			cout << "LimitaCredit:";
			ifs >> cbc->limitaCredit;
		}
		else {
			cout << "Pointerul nu a fost alocat" << endl;
		}
		return ifs;
	}


	 void afisare() override {
		 ContBancarSimplu::afisare();
		 cout << endl;
		 cout << "LimitaCredit:" << this->limitaCredit << endl;
	}



	~ContBancarCredit() {
		ContBancarSimplu::idContIncrementor--;
	}

};

class ContBancarEconomii : public ContBancarSimplu{
private:
	float rataDobanzii;
public:

	ContBancarEconomii() : ContBancarSimplu() {
		this->rataDobanzii = 0.0f;

	}
	ContBancarEconomii(string titular, float sold, float rataDobanzii) : ContBancarSimplu(titular, sold) {
		this->rataDobanzii = rataDobanzii;
	}

	ContBancarEconomii(ContBancarEconomii& cbe) {
		this->idCont = cbe.idCont;
		this->sold = cbe.sold;
		this->titular = cbe.titular;
		this->rataDobanzii = cbe.rataDobanzii;
		this->idCont = ContBancarSimplu::idContIncrementor;
	}

	float getRataDobanzii() {
		return this->rataDobanzii;
	}

	void setRataDobanzii(float rataDobanzii) {
		if (rataDobanzii < 0) {
			cerr << "rataDonabzii nu poate fi negativ" << endl;
			cout << "rataDobanzii nu a fost modificat. Incercati din nou..." << endl;
		}
		else {
			this->rataDobanzii = rataDobanzii;
		}
	}

	ContBancarEconomii& operator = (ContBancarEconomii& cbe) {
		this->rataDobanzii = cbe.rataDobanzii;
	}


	friend ostream& operator << (ostream& os, ContBancarEconomii& cbe) {

		ContBancarSimplu temp = cbe; //upcasting
		temp.setIdCont(temp.getIdCont() - 1); // Explicatie: vezi la ContBancarCredit - acelasi rationament
		os << temp;
		
		os << "RataDobanzii:" << cbe.rataDobanzii<< endl;
		return os;
	}
	friend ostream& operator << (ostream& os, ContBancarEconomii* cbe) { // supraincarcare pt obiecte dinamice

		ContBancarSimplu* temp = cbe; //upcasting
		os << temp;

		os << "RataDobanzii:" << cbe->rataDobanzii << endl;
		return os;
	}



	friend istream& operator >> (istream& is, ContBancarEconomii& cbe) {

		cout << "Titular:";
		getline(is, cbe.titular);
		cout << "Sold:";
		is >> cbe.sold;
		cout << "RataDobanzii:";
		is >> cbe.rataDobanzii;

		return is;
	}
	friend istream& operator >> (istream& is, ContBancarEconomii* cbe) { // supraincarcare pt obiecte dinamice

		cout << "Titular:";
		getline(is, cbe->titular);
		cout << "Sold:";
		is >> cbe->sold;
		cout << "RataDobanzii:";
		is >> cbe->rataDobanzii;

		return is;
	}

	friend ofstream& operator<<(ofstream& ofs, ContBancarEconomii& cbe) {
		ofs << "idCont:" << cbe.idCont << endl;
		ofs << "Titular:" << cbe.titular << endl;
		ofs << "Sold:" << cbe.sold << endl;
		ofs << "rataDobanzii:" << cbe.rataDobanzii << endl;
		return ofs;
	}

	friend ifstream& operator>>(ifstream& ifs, ContBancarEconomii* cbe) {
		if (cbe != nullptr) {
			cout << "Titular:";
			getline(ifs, cbe->titular);
			cout << "Sold:";
			ifs >> cbe->sold;
			cout << "RataDobanzii:";
			ifs >> cbe->rataDobanzii;
		}
		else {
			cout << "Pointerul nu a fost alocat" << endl;
		}
		return ifs;
	}


	

	 void afisare() override {
		 ContBancarSimplu::afisare();
		 cout << endl;
		cout << "RataDobanzii:" << this->rataDobanzii << endl;
	}

	 ~ContBancarEconomii() {
		 ContBancarSimplu::idContIncrementor--;
	 }

};

class Client {

private:
	ContBancarSimplu** conturi;
	int length;

public:
	Client() {
		this->length = 0;
		this->conturi = new ContBancarSimplu * [0];
	}

	void operator += (ContBancarSimplu* cbs) {

		ContBancarSimplu** temp = new ContBancarSimplu * [this->length + 1];
		for (int i = 0; i < this->length; i++) {
			temp[i] = this->conturi[i];
		}
		temp[this->length] = cbs;
		delete[] this->conturi;
		this->conturi = temp;
		this->length++;

	}
	void operator -= (ContBancarSimplu* cbs) {
		int indexToRemove = -1;
		for (int i = 0; i < this->length; i++) {
			if (this->conturi[i] == cbs) {
				indexToRemove = i;
				break;
			}
		}

		if (indexToRemove != -1) {
			ContBancarSimplu** temp = new ContBancarSimplu * [this->length - 1];

			// copiem elementele pana la index
			for (int i = 0; i < indexToRemove; i++) {
				temp[i] = this->conturi[i];
			}

			// copiem elementele dupa index(fara el)
			for (int i = indexToRemove + 1; i < this->length; i++) {
				temp[i - 1] = this->conturi[i];
			}

			delete[] this->conturi;
			this->conturi = temp;
			this->length--;
		}
		else {
			throw out_of_range("Index out of bounds1");
		}
	}

	ContBancarSimplu* operator[](int index)
	{
		if (index >= this->length || index < 0)
			throw out_of_range("Index out of bounds2");
		return this->conturi[index];
	}

	friend ostream& operator << (ostream& os, Client& client)
	{
		for (int i = 0; i < client.length; i++)
		{
			os << client.conturi[i] << endl << endl;
		}

		return os;
	}

	friend ofstream& operator<<(ofstream& ofs, Client& client) { // scriere in fisier
		ofs << client.length << endl;
		for (int i = 0; i < client.length; i++) {
			ofs << client.conturi[i];
		}
		return ofs;
	}


	friend ifstream& operator>>(ifstream& ifs, Client& client) { //citire din fisier
		string temp2;
		getline(ifs, temp2);
		int temp = stoi(temp2); //string to int

		delete[] client.conturi;
		client.conturi = new ContBancarSimplu * [temp];


		for (int i = 0; i < temp; i++) {
			ContBancarSimplu* cbs = new ContBancarSimplu();
			ifs >> cbs;
			client += cbs;
		}

		return ifs;

	}


	~Client() {
		delete conturi;
	}
	
};

int ContBancarSimplu::idContIncrementor = 1;

void main() {
	//////////////////////  Test cases:  ///////////////////////////
	try {

		ContBancarSimplu cont1("Magureanu Stefan", 2100.98);
		cout << cont1 << endl;

		ContBancarSimplu* cont2 = new ContBancarSimplu("Margelatu Andrei", 1999.99);
		cout << cont2 << endl;

		ContBancarCredit* cont3 = new ContBancarCredit("Miclea Mario", 4559.41, 8000);
		cout << cont3;

		cout << ContBancarSimplu::getIdContIncrementor() << endl;

		ContBancarSimplu* cont4 = new ContBancarSimplu("Firtat Alexandru", 1999.99);
		cout << cont4 << endl;

		ContBancarEconomii* cont5 = new ContBancarEconomii("Vasile Andrei", 2333, 0.01);
		cout << cont5;

		ContBancarEconomii cont6("Marinescu Stefania", 542.9, 0.2);
		cout << cont6;


		ContBancarCredit cont7;
		cout << cont7;
		cont7.afisare();
		ContBancarEconomii* cont8 = new ContBancarEconomii();
		cout << cont8;
		cont8->afisare();


		cout << endl << endl << endl;

		Client client1;

		client1 += cont2;
		client1 += cont3;

		client1 += cont5;
		client1 -= cont5;

		
		cout << client1;
	//	cout << client1[100];

		ContBancarSimplu* cont9 = new ContBancarSimplu(*cont4);
		cout << cont9;

		cout << "----------------------------------------"<<endl;

		ofstream ofs;
		ofs.open("client1.txt");
		ofs << client1;
		ofs.close();

		Client client1Afisare;
		ifstream ifs;
		ifs.open("client1.txt");
		ifs >> client1Afisare;
		ifs.close();

		cout << "Client1Afisare(din fisier):" << endl;
		cout << client1Afisare;
		cout << "DONE--------------" << endl;



		delete cont2;
		delete cont3;
		delete cont4;
		delete cont5;
		delete cont8;
		delete cont9;


	}
	catch(out_of_range ex){
		cout << ex.what() << endl;
		cout << "Aici 1" << endl;
	}
	catch (runtime_error ex) {
		cout << ex.what() << endl;
		cout << "Aici 2" << endl;
	}
	
	
}