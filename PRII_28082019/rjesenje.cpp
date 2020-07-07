#include<iostream>
#include<regex>
#include<memory>
#include<thread>
#include<exception>
#include<string>
#include<iterator>

using namespace std;

const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };
enum SortirajPo { T1, T2 };

char* Alociraj(const char* sadrzaj) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
	bool _omoguciDupliranje;
public:
	Kolekcija(bool omoguciDupliranje = true) {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_omoguciDupliranje = omoguciDupliranje;
		_trenutno = 0;
	}
	Kolekcija(const Kolekcija& kolekcija) {
		_trenutno = kolekcija._trenutno;
		_omoguciDupliranje = kolekcija._omoguciDupliranje;
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
		for (size_t i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = kolekcija._elementi1[i];
			_elementi2[i] = kolekcija._elementi2[i];
		}
	}
	Kolekcija& operator=(const Kolekcija& kolekcija) {
		if (this != &kolekcija) {
			_trenutno = kolekcija._trenutno;
			_omoguciDupliranje = kolekcija._omoguciDupliranje;
			delete[]_elementi1;
			delete[]_elementi2;
			_elementi1 = new T1[_trenutno];
			_elementi2 = new T2[_trenutno];
			for (size_t i = 0; i < _trenutno; i++)
			{
				_elementi1[i] = kolekcija._elementi1[i];
				_elementi2[i] = kolekcija._elementi2[i];
			}
		}
		return *this;
	}
	~Kolekcija() {
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
	}
	T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
	int getTrenutno() { return _trenutno; }
	friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}
	void AddElement(T1 a, T2 b) {
		T1* temp1;
		T2* temp2;
		temp1 = new T1[_trenutno + 1];
		temp2 = new T2[_trenutno + 1];
		for (size_t i = 0; i < _trenutno; i++)
		{
			if (!_omoguciDupliranje) {
				if (_elementi1[i] == a && _elementi2[i] == b) {
					delete[]temp1;
					delete[]temp2;
					temp1 = nullptr;
					temp2 = nullptr;
					throw exception("Nije dozvoljeno dupliranje elemenata!\n");
				}
			}
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		temp1[_trenutno] = a;
		temp2[_trenutno] = b;
		delete[]_elementi1;
		delete[]_elementi2;
		_elementi1 = new T1[_trenutno + 1];
		_elementi2 = new T2[_trenutno + 1];
		for (size_t i = 0; i < _trenutno+1; i++)
		{
			_elementi1[i] = temp1[i];
			_elementi2[i] = temp2[i];
		}
		delete[]temp1;
		delete[]temp2;
		temp1 = nullptr;
		temp2 = nullptr;
		_trenutno++;
	}
	void SortirajRastuci(SortirajPo element) {
		for (size_t i = 0; i < _trenutno -1; i++)
		{
			for (size_t j = 0; j < _trenutno - 1 - i; j++)
			{
				if (element == SortirajPo::T1) {
					if (_elementi1[j] > _elementi1[j + 1]) {
						T1 temp1 = _elementi1[j];
						_elementi1[j] = _elementi1[j + 1];
						_elementi1[j + 1] = temp1;
						T2 temp2 = _elementi2[j];
						_elementi2[j] = _elementi2[j + 1];
						_elementi2[j + 1] = temp2;
					}
				}
				if (element == SortirajPo::T2) {
					if (_elementi2[j] > _elementi2[j + 1]) {
						T1 temp1 = _elementi1[j];
						_elementi1[j] = _elementi1[j + 1];
						_elementi1[j + 1] = temp1;
						T2 temp2 = _elementi2[j];
						_elementi2[j] = _elementi2[j + 1];
						_elementi2[j + 1] = temp2;
					}
				}
			}
		}
	}
};

class DatumVrijeme {
	int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);
	}
	DatumVrijeme(const DatumVrijeme& datum) {
		_dan = new int(*datum._dan);
		_mjesec = new int(*datum._mjesec);
		_godina = new int(*datum._godina);
		_sati = new int(*datum._sati);
		_minuti = new int(*datum._minuti);
	}
	DatumVrijeme& operator=(const DatumVrijeme& datum) {
		if (this != &datum) {
			delete _dan;
			delete _mjesec;
			delete _godina;
			delete _sati;
			delete _minuti;
			_dan = new int(*datum._dan);
			_mjesec = new int(*datum._mjesec);
			_godina = new int(*datum._godina);
			_sati = new int(*datum._sati);
			_minuti = new int(*datum._minuti);
		}
		return *this;
	}
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
		return COUT;
	}
	int getMinuti() {
		return *_dan * 24 * 60 + *_mjesec * 30 * 24 * 60 + *_godina * 365 * 24 * 60 + *_sati * 60 + *_minuti;
	}
	friend bool operator==(const DatumVrijeme& lijevi,  const DatumVrijeme& desni) {
		return *lijevi._dan == *desni._dan && *lijevi._mjesec == *desni._mjesec && *lijevi._godina && *desni._godina && *lijevi._sati == *desni._sati && *lijevi._minuti == *desni._minuti;
	}
};

class Predmet {
	char* _naziv;
	int _ocjena;
	string _napomena;
public:
	Predmet(const char* naziv = "", int ocjena = 0, string napomena = "") {
		_naziv = Alociraj(naziv);
		_ocjena = ocjena;
		_napomena = napomena;
	}
	Predmet(const Predmet& predmet) {
		_naziv = Alociraj(predmet._naziv);
		_ocjena = predmet._ocjena;
		_napomena = predmet._napomena;
	}
	Predmet& operator=(const Predmet& predmet) {
		if (this != &predmet) {
			delete[]_naziv;
			_naziv = Alociraj(predmet._naziv);
			_ocjena = predmet._ocjena;
			_napomena = predmet._napomena;
		}
		return *this;
	}
	friend bool operator==(const Predmet& lijevi, const Predmet& desni) {
		return strcmp(lijevi._naziv, desni._naziv)==0;
	}
	~Predmet() {
		delete[] _naziv; _naziv = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Predmet& obj) {
		COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
		return COUT;
	}
	string GetNapomena() { return _napomena; }
	char* GetNaziv() { return _naziv; }
	int GetOcjena() { return _ocjena; }

	void DodajNapomenu(string napomena) {
		_napomena += " " + napomena;
	}
};

class Uspjeh {
	eRazred* _razred;
	//formalni argument DatumVrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
	Kolekcija<Predmet, DatumVrijeme> _predmeti;
public:
	Uspjeh(eRazred razred) {
		_razred = new eRazred(razred);
	}
	Uspjeh(const Uspjeh& uspjeh) {
		_razred = new eRazred(*uspjeh._razred);
		_predmeti = uspjeh._predmeti;
	}
	Uspjeh& operator=(const Uspjeh& uspjeh) {
		if (this != &uspjeh) {
			delete _razred;
			_razred = new eRazred(*uspjeh._razred);
			_predmeti = uspjeh._predmeti;
		}
		return *this;
	}
	~Uspjeh() { delete _razred; _razred = nullptr; }

	Kolekcija<Predmet, DatumVrijeme>* GetPredmeti() { return &_predmeti; }
	eRazred* GetERazred() { return _razred; }
	friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
		COUT << *obj._razred << " " << obj._predmeti << endl;
		return COUT;
	}
	double getProsjek() {
		double prosjek = 0.0;
		for (size_t i = 0; i < _predmeti.getTrenutno(); i++)
		{
			prosjek += _predmeti.getElement1(i).GetOcjena();
		}
		return prosjek / _predmeti.getTrenutno();
	}
};

class Kandidat {
	char* _imePrezime;
	string _emailAdresa;
	string _brojTelefona;
	vector<Uspjeh> _uspjeh;
public:
	Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) {
		_imePrezime = Alociraj(imePrezime);
		regex rule("([a-z]{3,}[@]((outlook.com)|(edu.fit.ba)))");
		if (!regex_match(emailAdresa, rule)) {
			emailAdresa = "notSet@edu.fit.ba";
			cout << "Not match\n";
		}
		_emailAdresa = emailAdresa;
		_brojTelefona = brojTelefona;
	}
	Kandidat(const Kandidat& kandidat) {
		_imePrezime = Alociraj(kandidat._imePrezime);
		_emailAdresa = kandidat._emailAdresa;
		_brojTelefona = kandidat._brojTelefona;
		_uspjeh = kandidat._uspjeh;
	}
	Kandidat& operator=(const Kandidat& kandidat) {
		if (this != &kandidat) {
			delete[]_imePrezime;
			_imePrezime = Alociraj(kandidat._imePrezime);
			_emailAdresa = kandidat._emailAdresa;
			_brojTelefona = kandidat._brojTelefona;
			_uspjeh = kandidat._uspjeh;
		}
		return *this;
	}
	~Kandidat() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
		COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
		for (size_t i = 0; i < obj._uspjeh.size(); i++)
		{
			COUT << obj._uspjeh[i];
		}
		return COUT;
	}
	vector<Uspjeh>* GetUspjeh() { return &_uspjeh; }
	string GetEmail() { return _emailAdresa; }
	string GetBrojTelefona() { return _brojTelefona; }
	char* GetImePrezime() { return _imePrezime; }
	void PosaljiEmail(Predmet predmet, eRazred razred) {
		cout << "FROM:info@edu.fit.ba\n";
		cout << "TO:" << _emailAdresa << endl;
		cout << "Postovani " << _imePrezime << ", evidentirali ste uspjeh " << predmet.GetOcjena() << " za " << razred << ".\n";
		cout << "Pozdrav\nFIT Team\n";
	}
	void PosaljiSMS(int lok, eRazred razred) {
		cout << "Svaka cast za uspjeh " << _uspjeh[lok].getProsjek() << " u " << razred << "razredu.\n";
	}
	bool AddPredmet(eRazred razred, Predmet predmet, DatumVrijeme datum) {
		int lok = -1;
		for (size_t i = 0; i < _uspjeh.size(); i++)
		{
			if (razred == *_uspjeh[i].GetERazred()) {
				for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
				{
					if (predmet == _uspjeh[i].GetPredmeti()->getElement1(j)) {
						return false;
					}
					if (datum.getMinuti() - _uspjeh[i].GetPredmeti()->getElement2(j).getMinuti() <= 5) {
						return false;
					}
				}
				lok = i;
			}
		}
		if (lok > -1) {
			_uspjeh[lok].GetPredmeti()->AddElement(predmet, datum);
			thread jedan(&Kandidat::PosaljiEmail, this, predmet, razred);
			jedan.join();
			if (_uspjeh[lok].getProsjek() > 4.5) {
				thread dva(&Kandidat::PosaljiSMS,this, lok, razred);
				dva.join();
			}
			return true;
		}
		_uspjeh.push_back(Uspjeh(razred));
		_uspjeh[_uspjeh.size() - 1].GetPredmeti()->AddElement(predmet, datum);
		thread jedan(&Kandidat::PosaljiEmail, this, predmet, razred);
		jedan.join();
		if (_uspjeh[_uspjeh.size() - 1].getProsjek() > 4.5) {
			thread dva(&Kandidat::PosaljiSMS, this, _uspjeh.size() - 1, razred);
			dva.join();
		}
		return true;
	}
	int BrojPonavljanjaRijeci(string nesto) {
		int brojac = 0;
		regex pravilo(nesto);
		for (size_t i = 0; i < _uspjeh.size(); i++)
		{
			for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
			{
				string napomena = _uspjeh[i].GetPredmeti()->getElement1(j).GetNapomena();
				sregex_iterator pocetak(napomena.begin(), napomena.end(),pravilo);
				sregex_iterator kraj;
				while (pocetak != kraj) {
					pocetak++;
					brojac++;
				}
			}
		}
		return brojac;
	}
	vector<Predmet> operator()(DatumVrijeme lijevi, DatumVrijeme desni) {
		vector<Predmet> temp;
		for (size_t i = 0; i < _uspjeh.size(); i++)
		{
			for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
			{
				if (_uspjeh[i].GetPredmeti()->getElement2(j).getMinuti() > lijevi.getMinuti() && _uspjeh[i].GetPredmeti()->getElement2(j).getMinuti() < desni.getMinuti()) {
					temp.push_back(_uspjeh[i].GetPredmeti()->getElement1(j));
				}
			}
		}
		return temp;
	}
	Uspjeh* operator[](eRazred razred) {
		for (size_t i = 0; i < _uspjeh.size(); i++)
		{
			if (*_uspjeh[i].GetERazred() == razred) {
				return &_uspjeh[i];
			}
		}
		return nullptr;
	}
};

void main() {
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR AE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEEILO GUBLJENJE URA?ENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKO?ER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIENI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUEAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOANE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAEENO.
	7. IMATE POTPUNU SLOBODU DA U MAIN FUNKCIJI, ZA POTREBE TESTIRANJA, DODAJETE VISE POZIVA ILI SALJETE DRUGE VRIJEDNOSTI PARAMETARA
	****************************************************************************/

	DatumVrijeme temp,
		datum19062019_1015(19, 6, 2019, 10, 15),
		datum20062019_1115(20, 6, 2019, 11, 15),
		datum30062019_1215(30, 6, 2019, 12, 15),
		datum05072019_1231(5, 7, 2019, 12, 31);

	const int kolekcijaTestSize = 9;
	Kolekcija<int, int> kolekcija1(false);
	for (size_t i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i + 1, 20 - i);

	try {
		//ukoliko nije dozvoljeno dupliranje elemenata, metoda AddElement baca izuzetak
		kolekcija1.AddElement(6, 15);
	}
	catch (exception& err) {
		cout << err.what() << endl;
	}
	cout << kolekcija1 << endl;

	//na osnovu vrijednosti parametra sortira clanove kolekcije u rastucem redoslijedu 
	kolekcija1.SortirajRastuci(SortirajPo::T2);
	cout << kolekcija1 << endl;


	Kolekcija<int, int> kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;

	Kolekcija<int, int> kolekcija3;
	kolekcija3 = kolekcija1;
	cout << kolekcija3 << crt;

	//napomena se moze dodati i prilikom kreiranja objekta
	Predmet Matematika("Matematika", 5, "Ucesce na takmicenju"),
		Fizika("Fizika", 5),
		Hemija("Hemija", 2),
		Engleski("Engleski", 5);
	Fizika.DodajNapomenu("Pohvala za ostvareni uspjeh");
	cout << Matematika << endl;

	/*
	email adresa mora biti u formatu: text@outlook.com ili text@edu.fit.ba
	u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@edu.fit.ba
	za provjeru koristiti regex
	*/
	Kandidat jasmin("Jasmin Azemovic", "jasmin@outlook.com", "033 281 172");
	Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");
	Kandidat emailNotValid("Ime Prezime", "korisnik@klix.ba", "033 281 170");

	/*
	uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
	tom prilikom onemoguciti:
	- dodavanje istoimenih predmeta na nivou jednog razreda,
	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje 5 minuta).
	razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
	Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	if (jasmin.AddPredmet(DRUGI, Fizika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(DRUGI, Hemija, datum30062019_1215))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Engleski, datum19062019_1015))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Matematika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati Matematiku jer je vec dodana u prvom razredu
	if (jasmin.AddPredmet(PRVI, Matematika, datum05072019_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati Fiziku jer nije proslo 5 minuta od dodavanja posljednjeg predmeta
	if (jasmin.AddPredmet(PRVI, Fizika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	/*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
	FROM:info@edu.fit.ba
	TO: emailKorisnika
	Postovani ime i prezime, evidentirali ste uspjeh za X razred.
	Pozdrav.
	FIT Team.

	//ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh X.X u X razredu".
	//slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
	*/
	cout << "USPJEH ISPISATI KORISTECI OSTREAM_ITERATOR" << endl;
	cout << jasmin << endl;
	//vraca broj ponavljanja odredjene rijeci u napomenama, koristiti sregex_iterator
	cout << "Rijec takmicenje se pojavljuje " << jasmin.BrojPonavljanjaRijeci("takmicenju") << " puta." << endl;

	//vraca niz predmeta koji su evidentiranih u periodu izmedju vrijednosti proslijedjenih parametara
	vector<Predmet> jasminUspjeh = jasmin(DatumVrijeme(18, 06, 2019, 10, 15), DatumVrijeme(21, 06, 2019, 10, 10));
	for (size_t i = 0; i < jasminUspjeh.size(); i++)
		cout << jasminUspjeh[i] << endl;

	Uspjeh* uspjeh_Irazred = jasmin[PRVI];//vraca uspjeh kandidata ostvaren u prvom razredu
	if (uspjeh_Irazred != nullptr)
		cout << *uspjeh_Irazred << endl;

	cin.get();
	system("pause>0");
}