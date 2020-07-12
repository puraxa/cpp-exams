#include <iostream>
#include <vector>
#include <thread>
using namespace std;
const char* crt = "\n-------------------------------------------\n";
enum OznakaKrvneGrupe { O, A, B, AB };
const char* OznakaKrvneGrupeString[] = { "O", "A", "B", "AB" };

char* Alociraj(const char* sadrzaj) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

bool ValidanFormat(string telefon) {
	return true;
}



class Datum {
	int _dan, _mjesec, _godina;
public:
	Datum(int dan, int mjesec, int godina) :
		_dan(dan), _mjesec(mjesec), _godina(godina) {}
	friend ostream& operator<<(ostream& COUT, const Datum& obj) {
		COUT << obj._dan << " " << obj._mjesec << "." << obj._godina << endl;
		return COUT;
	}
	string ToString() const {
		string str = "";
		str += _dan + ".";
		str += _mjesec + ".";
		str += _godina + "";
		return str;
	}
	int getDani() {
		return _dan + _mjesec * 30 + _godina * 365;
	}
};
template <class T1, class T2, int max>
class Kolekcija {
	T1 _elementi1[max];
	T2 _elementi2[max];
	int* _trenutnoElemenata;
	int _keyElement; // kljucni element, a podrazumijevano T1 predstavlja kljucni element i tada je vrijednost 1, a u slucaju da je T2 onda ce vrijednost biti 2
public:
	Kolekcija(int keyElement = 1) {
		_trenutnoElemenata = new int(0);
		_keyElement = keyElement;
	}
	Kolekcija(const Kolekcija& kolekcija) {
		_elementi1 = kolekcija._elementi1;
		_elementi2 = kolekcija._elementi2;
		_keyElement = kolekcija._keyElement;
		_trenutnoElemenata = new int(*kolekcija._trenutnoElemenata);
	}
	Kolekcija& operator=(const Kolekcija& kolekcija) {
		if (this != &kolekcija) {
			delete[]_trenutnoElemenata;
			_trenutnoElemenata = new int(*kolekcija._trenutnoElemenata);
			_elementi1 = kolekcija._elementi1;
			_elementi2 = kolekcija._elementi2;
			_keyElement = kolekcija._keyElement;
		}
		return *this;
	}
	~Kolekcija() {
		delete _trenutnoElemenata;
		_trenutnoElemenata = nullptr;
	}
	bool AddElement(T1 ele1, T2 ele2) {
		if (*_trenutnoElemenata == max)
			return false;
		_elementi1[*_trenutnoElemenata] = ele1;
		_elementi2[*_trenutnoElemenata] = ele2;
		(*_trenutnoElemenata)++;
		return true;
	}
	void SetElement2(int lokacija, T2 ele2) {
		_elementi2[lokacija] = ele2;
	}
	void SetKeyElement(int keyElement) {
		_keyElement = keyElement;
	}
	int GetTrenutno() const { return *_trenutnoElemenata; }
	int GetMax() const { return max; }

	T1 GetElement1(int lokacija) const {
		return _elementi1[lokacija];
	}
	T2 GetElement2(int lokacija) const {
		return _elementi2[lokacija];
	}
	friend ostream& operator<<(ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj.GetElement1(i) << " " << obj.GetElement2(i) << endl;
		return COUT;
	}
	void Sort(string smjer) {
		if (smjer == "ASC") {
			SortASC();
			return;
		}
		SortDESC();
	}
	void SortASC() {
		for (size_t i = 0; i < *_trenutnoElemenata - 1; i++)
		{
			for (size_t j = 0; j < *_trenutnoElemenata - i - 1; j++)
			{
				if (_keyElement == 1) {
					if (_elementi1[j] > _elementi1[j + 1]) {
						Swap(j, j + 1);
					}
				}
				else {
					if (_elementi2[j] > _elementi2[j + 1]) {
						Swap(j, j + 1);
					}
				}
			}
		}
	}
	void SortDESC() {
		for (size_t i = 0; i < *_trenutnoElemenata - 1; i++)
		{
			for (size_t j = 0; j < *_trenutnoElemenata - i - 1; j++)
			{
				if (_keyElement == 1) {
					if (_elementi1[j] < _elementi1[j + 1]) {
						Swap(j, j + 1);
					}
				}
				else {
					if (_elementi2[j] < _elementi2[j + 1]) {
						Swap(j, j + 1);
					}
				}
			}
		}
	}
	void Swap(int i, int j) {
		T1 temp1 = _elementi1[i];
		_elementi1[i] = _elementi1[j];
		_elementi1[j] = temp1;
		T2 temp2 = _elementi2[i];
		_elementi2[i] = _elementi2[j];
		_elementi2[j] = temp2;
	}
};

class KrvnaGrupa {
	/*postoje 4 krvne grupe koje su navedene u enumeracije OznakaKrvneGrupe, pri cemu svaka od navedenih moze imati pozitivan (+) i negativan (-) Rh faktor*/
	OznakaKrvneGrupe _oznaka;//npr: AB
	char _rhFaktor; // + ili -
	/*prethodno pomenuto je izuzetno bitno iz razloga sto postoje jasna pravila vezana za darivanje krvi tj. koji primalac moze primiti krv od kojeg donatora sto je prikazano u tabeli, a naredna dva vector-a su zaduzena da cuvaju informacije o tome, npr. za krvnu grupu A+ vector donori ce cuvati vrijednosti: A+ i AB+ */
	vector<KrvnaGrupa> _donori; //krvne grupe kojima odredjena krvna grupa moze donirati krv.
	vector<KrvnaGrupa> _primaoci; //krvne grupe od kojih odredjena krvna grupa moze primiti krv.
public:
	KrvnaGrupa(OznakaKrvneGrupe oznaka, char rhFaktor) :
		_oznaka(oznaka), _rhFaktor(rhFaktor) {}
	KrvnaGrupa(const KrvnaGrupa& grupa) {
		_oznaka = grupa._oznaka;
		_rhFaktor = grupa._rhFaktor;
		_donori = grupa._donori;
		_primaoci = grupa._primaoci;
	}
	KrvnaGrupa& operator=(const KrvnaGrupa& grupa) {
		if (this != &grupa) {
			_oznaka = grupa._oznaka;
			_rhFaktor = grupa._rhFaktor;
			_donori = grupa._donori;
			_primaoci = grupa._primaoci;
		}
		return *this;
	}
	friend bool operator==(const KrvnaGrupa& lijeva, const KrvnaGrupa& desna) {
		return lijeva._oznaka == desna._oznaka && lijeva._rhFaktor == desna._rhFaktor;
	}
	void SetDonori(vector<KrvnaGrupa> donori) { _donori = donori; }
	void SetPrimaoci(vector<KrvnaGrupa> primaoci) { _primaoci = primaoci; }
	OznakaKrvneGrupe& GetOznakaKrvneGrupe() { return _oznaka; }
	vector<KrvnaGrupa>& GetDonori() { return _donori; }
	vector<KrvnaGrupa>& GetPrimaoci() { return _primaoci; }
	string ToString() const {
		string str = "Krvna grupa -> ";
		str += string(OznakaKrvneGrupeString[_oznaka]) + _rhFaktor;
		str += "\n";
		str += "Donori -> ";
		for (size_t i = 0; i < _donori.size(); i++)
		{
			str += string(OznakaKrvneGrupeString[_donori[i]._oznaka]) + _donori[i]._rhFaktor + ",";
		}
		str += "\nPrimaoci -> ";
		for (size_t i = 0; i < _primaoci.size(); i++)
		{
			str += string(OznakaKrvneGrupeString[_primaoci[i]._oznaka]) + _primaoci[i]._rhFaktor + ",";
		}
		str += "\n";
		cout << str;
		return str;
	}
};

class Osoba {
protected:
	char* _imePrezime;
	KrvnaGrupa _krvnaGrupa;
public:
	Osoba(const char* imePrezime, KrvnaGrupa krvnaGrupa) : _krvnaGrupa(krvnaGrupa) {
		_imePrezime = Alociraj(imePrezime);
	}
	~Osoba() {
		delete[] _imePrezime;
		_imePrezime = nullptr;
	}
	char* GetImePrezime() { return _imePrezime; }
	KrvnaGrupa& GetKrvnaGrupa() { return _krvnaGrupa; }
	virtual void Info() = 0;
};

class Donor : public Osoba {
	//u slucaju da broj telefona nije u validnom formatu potrebno ga je postaviti na podrazumijevanu vrijednost: 000-000-000
	//ValidanFormat treba biti globalna funkcija, a ne �lanica
	string _telefon; //regex: 000/000-000 ili 000-000-000
	Datum _datumPosljednjegDoniranja;
	bool _podsjetiMe;
	bool _kontaktirajMe;//u slucaju potrebe za doniranjem krvi, donor se slaze da bude kontaktiran
public:
	Donor(const char* imePrezime, KrvnaGrupa krvnaGrupa, string telefon, Datum dpd, bool remind = true, bool contact = true) : Osoba(imePrezime,krvnaGrupa), _datumPosljednjegDoniranja(dpd){
		if (ValidanFormat(telefon))
			_telefon = telefon;
		else
			_telefon = "000-000-000";
		_kontaktirajMe = contact;
		_podsjetiMe = remind;
	}
	Datum& GetDatumPosljednjegDoniranja() { return _datumPosljednjegDoniranja; }
	string& GetTelefon() {
		return _telefon;
	}
	bool GetPodsjeti() {
		return _podsjetiMe;
	}
	void SetDatum(Datum datum) {
		_datumPosljednjegDoniranja = datum;
	}
	void Info()override {

	}
};
void PosaljiEmail(Donor* donor) {
	cout << "Molimo vas da donirate krv!\n";
}
class Zahtjev {
	string _ustanova;
	Datum _datumZahtjeva;
	KrvnaGrupa _krvnaGrupa;
	double _kolicina;
public:
	Zahtjev(string ustanova, Datum datum, KrvnaGrupa krvnaGrupa, double kolicina) :
		_ustanova(ustanova), _datumZahtjeva(datum), _krvnaGrupa(krvnaGrupa), _kolicina(kolicina) { }
	string GetUstanova() { return _ustanova; }
	Datum GetDatumZahtjeva() { return _datumZahtjeva; }
	KrvnaGrupa GetKrvnaGrupa() { return _krvnaGrupa; }
	double GetKolicina() { return _kolicina; }

	friend ostream& operator<<(ostream& COUT, const Zahtjev& obj) {
		COUT << "Ustanova: " << obj._ustanova << endl;
		COUT << "Datum: " << obj._datumZahtjeva.ToString() << endl;//kreirati metodu koja vra�a datum kao niz karaktera
		COUT << "Krvna grupa: " << obj._krvnaGrupa.ToString() << endl;
		COUT << "Kolicina: " << obj._kolicina << endl;
		return COUT;
	}
};

class TransfuzijskiCentar {
	//stanje zaliha za svaku pojedinu krvnu grupu
	Kolekcija<KrvnaGrupa*, double, 8> _zalihe;
	//evidentira svaku donaciju krvi
	Kolekcija<Osoba*, double, 100> _donacije;
	vector<Zahtjev> _zahtjevi;
public:
	Kolekcija<KrvnaGrupa*, double, 8>& GetZalihe() { return _zalihe; }
	Kolekcija<Osoba*, double, 100>& GetDonacije() { return _donacije; }
	vector<Zahtjev>& GetZahtjeve() { return _zahtjevi; }
	void AddDonaciju(Datum datum, Osoba* osoba, double kolicina) {
		bool pronadjen = false;
		int lok = -1;
		bool osobaNadjena = false;
		int lokOsoba = -1;
		for (size_t i = 0; i < _zalihe.GetTrenutno(); i++)
		{
			if (_zalihe.GetElement1(i)->GetOznakaKrvneGrupe() == osoba->GetKrvnaGrupa().GetOznakaKrvneGrupe()) {
				pronadjen = true;
				lok = i;
				break;
			}
		}
		for (size_t i = 0; i < _donacije.GetTrenutno(); i++)
		{
			if (osoba == _donacije.GetElement1(i)) {
				cout << "Osoba pronadjena\n";
				osobaNadjena = true;
				lokOsoba = i;
				break;
			}
		}
		if (pronadjen) {
			_zalihe.SetElement2(lok, kolicina + _zalihe.GetElement2(lok));
		}
		else {
			_zalihe.AddElement(&osoba->GetKrvnaGrupa(), kolicina);
		}
		if (osobaNadjena) {
			_donacije.SetElement2(lokOsoba, kolicina + _donacije.GetElement2(lokOsoba));
			Donor* temp = dynamic_cast<Donor*>(osoba);
			temp->SetDatum(datum);
			return;
		}
		else {
			_donacije.AddElement(osoba, kolicina);
		}
	}
	Datum* GetDatumPosljednjegDoniranja(string ime, string brojTelefona) {
		for (size_t i = 0; i < _donacije.GetTrenutno(); i++)
		{
			Donor* temp = dynamic_cast<Donor*>(_donacije.GetElement1(i));
			if (strcmp(temp->GetImePrezime(), ime.c_str()) == 0 && brojTelefona == temp->GetTelefon()) {
				cout << "Osoba pronadjena\n";
				return &temp->GetDatumPosljednjegDoniranja();
			}
		}
		return nullptr;
	}
	bool DodajZahtjev(Zahtjev zahtjev) {
		double kolicina = 0;
		for (size_t i = 0; i < _zalihe.GetTrenutno(); i++)
		{
			if (_zalihe.GetElement2(i) > zahtjev.GetKolicina()) {
				cout << "Zalihe " << _zalihe.GetElement2(i) << endl << "Zahtjev " << zahtjev.GetKolicina() << endl;
				_zalihe.SetElement2(i, _zalihe.GetElement2(i) - zahtjev.GetKolicina());
				_zahtjevi.push_back(zahtjev);
				return true;
			}
		}
		for (size_t i = 0; i < _donacije.GetTrenutno(); i++)
		{
			for (size_t j = 0; j < zahtjev.GetKrvnaGrupa().GetDonori().size(); j++)
			{
				if (_donacije.GetElement1(i)->GetKrvnaGrupa() == zahtjev.GetKrvnaGrupa().GetDonori()[j]) {
					cout << "A u kurac vise \n";
					Donor* temp = dynamic_cast<Donor*>(_donacije.GetElement1(i));
					cout << temp->GetImePrezime();
					cout << temp->GetPodsjeti() << endl;
					if (temp->GetPodsjeti() && temp->GetDatumPosljednjegDoniranja().getDani() < Datum(10,07,2020).getDani() - 90) {
						cout << "A u kurac vise 22222\n";
						thread jedan(&PosaljiEmail, temp);
						jedan.join();
					}
				}
			}
		}
		return false;
	}
	void PrintajZahvalnice(const int brojZahvalnica) {
		Kolekcija<Osoba*, double, 100> temp;
		for (size_t i = 0; i < _donacije.GetTrenutno(); i++)
		{	
			bool pronadjen = false;
			for (size_t j = 0; j < temp.GetTrenutno(); j++)
			{
				if (_donacije.GetElement1(i) == temp.GetElement1(j)) {
					temp.SetElement2(j, _donacije.GetElement2(i) + temp.GetElement2(j));
					pronadjen = true;
					break;
				}
			}
			if (!pronadjen) {
				temp.AddElement(_donacije.GetElement1(i), _donacije.GetElement2(i));
			}
		}
		temp.SetKeyElement(2);
		temp.Sort("DESC");
		for (size_t i = 0; i < brojZahvalnica; i++)
		{
			cout << temp.GetElement1(i)->GetImePrezime() << endl;
			cout << temp.GetElement2(i) << endl;
		}
	}
};


void main() {

	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
	3. SPA�AVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URA?ENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKO?ER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIENI ONIMA KOJI SU KORI�TENI U TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOANE FUNKCIJE MO�ETE IMENOVATI I DODAVATI PO �ELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.
	7. IMATE POTPUNU SLOBODU DA U MAIN FUNKCIJI, ZA POTREBE TESTIRANJA, DODAJETE VISE POZIVA ILI SALJETE DRUGE VRIJEDNOSTI PARAMETARA
	****************************************************************************/

	Datum dat_12_01_2019(12, 1, 2019), dat_01_02_2019(1, 2, 2019);

	Kolekcija<int, int, 10> kolekcija1;
	for (size_t i = 0; i < kolekcija1.GetMax(); i++)
		if (!kolekcija1.AddElement(i, 170000 + i))
			cout << "Elementi " << i << " i " << 170000 + i << " nisu dodati u kolekciju" << endl;

	cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;

	kolekcija1.Sort("ASC"); //kljucne rijeci za sortiranje su ASC i DESC, a sortiranje se vrsi prema kljucnom elementu
	cout << kolekcija1 << endl << endl << endl;
	kolekcija1.Sort("DESC");
	cout << kolekcija1 << endl;

	kolekcija1.SetKeyElement(2);//postavlja kljucni element na T2

	kolekcija1.Sort("DESC"); //sada se sortiranje vrsi po elementu T2
	cout << kolekcija1 << endl;

	KrvnaGrupa
		O_poz(O, '+'), O_neg(O, '-'),
		A_poz(A, '+'), A_neg(A, '-'),
		B_poz(B, '+'), B_neg(B, '-'),
		AB_poz(AB, '+'), AB_neg(AB, '-');

	vector<KrvnaGrupa> donori_O_poz{ O_poz, A_poz, B_poz, AB_poz };
	O_poz.SetDonori(donori_O_poz);
	//ili krace napisano
	O_poz.SetPrimaoci(vector<KrvnaGrupa>{O_poz, O_neg});
	A_poz.SetDonori(vector<KrvnaGrupa>{A_poz, AB_poz});
	A_poz.SetPrimaoci(vector<KrvnaGrupa>{O_poz, A_poz, O_neg, A_neg});

	B_poz.SetDonori(vector<KrvnaGrupa>{B_poz, AB_poz});
	B_poz.SetPrimaoci(vector<KrvnaGrupa>{O_poz, B_poz, O_neg, B_neg});

	/*Ispis podataka o krvnoj grupi treba biti u formatu:
	-------------------------------------------
	Krvna grupa -> 0+
	-------------------------------------------
	Donori  ->  0+, A+, B+, AB+
	Primaoci ->	0+, 0-
	-------------------------------------------
	*/
	cout << O_poz.ToString() << endl;

	Osoba* jasmin = new Donor("Jasmin Azemovic", B_poz, "061-111-222", Datum(12, 2, 2018), true, true);
	Osoba* adel = new Donor("Adel Handzic", A_neg, "061-222-333", Datum(9, 1, 2018), true, true);
	Osoba* goran = new Donor("Goran Skondric", B_neg, "061-333-444", Datum(9, 3, 2018), true, true);

	TransfuzijskiCentar tcMostar;
	/*
	prilikom svake donacije je potrebno povecati zalihe za tu krvnu grupu
	ukoliko krvna grupa vec postoji na zalihi onda se uvecava samo njena kolicina
	takodjer, donoru se postavlja nova vrijednost datuma posljednje donacije
	*/
	//datum donacije, donor, kolicina
	tcMostar.AddDonaciju(Datum(20, 5, 2018), jasmin, 2.5);
	tcMostar.AddDonaciju(Datum(20, 5, 2018), adel, 3);
	tcMostar.AddDonaciju(Datum(6, 5, 2018), goran, 1.2);

	tcMostar.AddDonaciju(Datum(10, 9, 2018), jasmin, 2);
	tcMostar.AddDonaciju(Datum(18, 10, 2018), adel, 1.8);
	tcMostar.AddDonaciju(Datum(15, 9, 2018), goran, 3.8);
	/*
	parametri: imePrezime, brojTelefona
	vraca pokazivac na datum posljednjeg darivanja krvi. u slucaju da ne postoje trazeni podaci, metoda vraca nullptr
	*/
	Datum* posljednjeDoniranje = tcMostar.GetDatumPosljednjegDoniranja("Jasmin Azemovic", "061-111-222");

	Zahtjev zahtjev_0_poz("Tranfuziologija KCUS", Datum(18, 2, 2019), O_poz, 15),
		zahtjev_0_neg("Tranfuziologija Bakir Nakas", Datum(20, 2, 2019), O_neg, 8);

	/*ukoliko transfuzijski centar posjeduje zahtijevane kolicine na stanju, odmah ce ih ustupiti prema zahtjevu,
	a u slucaju da ne posjeduje onda ce (koristeci multithreading) kontaktirati (poslati SMS poruku sa odgovarajucim sadrzajem)
	sve donore koji zadovoljavaju sljedece uslove:
	- mogu donirati krv zahtijevanoj krvnoj grupi
	- oznacili su da zele biti kontaktirani
	- nisu davali krv u posljednjih 90 dana ili 3 mjeseca
	*/
	if (tcMostar.DodajZahtjev(zahtjev_0_poz))
		cout << "Zahtijevane zalihe na stanju i bit ce vam ustupljene!" << endl;
	if (tcMostar.DodajZahtjev(zahtjev_0_neg))
		cout << "Zahtijevane zalihe na stanju i bit ce vam ustupljene!" << endl;

	//printa zahvalnice (zahvaljujemo se ime i prezime donoru na ukupno doniranih X doza krvi) za TOP 2 donatora krvi
	tcMostar.PrintajZahvalnice(2);

	delete adel;
	delete jasmin;
	delete goran;
	cin.get();
}
