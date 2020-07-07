#include<iostream>
#include<memory>
#include<regex>
#include<thread>
#include<exception>
#include<fstream>
using namespace std;

/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
****************************************************************************/

const char* nedozvoljena_operacija = "Nedozvoljena operacija";
const char* not_set = "NOT_SET";

enum Sortiranje { ASC, DESC };
enum Predmet { MATEMATIKA, FIZIKA, HEMIJA, GEOGRAFIJA, NOT_SET };
const char* charPredmet[] = { "MATEMATIKA", "FIZIKA", "HEMIJA", "GEOGRAFIJA", "NOT_SET"};
enum Razred { I = 1, II, III, IV };
const char* charRazred[] = { "I", "II", "III", "IV" };

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
template <class T1, class T2, int max>
class Kolekcija {
	T1* _elementi1[max] = { nullptr };
	T2* _elementi2[max] = { nullptr };
	int _trenutnoElemenata;
	bool _dozvoliDupliranje;
	Sortiranje _sortiranje;
public:
	Kolekcija(Sortiranje sortiranje = ASC, bool dozvoliDupliranje = true) {
		_trenutnoElemenata = 0;
		_sortiranje = sortiranje;
		_dozvoliDupliranje = dozvoliDupliranje;
	}
	Kolekcija(const Kolekcija& kolekcija) {
		_trenutnoElemenata = kolekcija._trenutnoElemenata;
		_sortiranje = kolekcija._sortiranje;
		_dozvoliDupliranje = kolekcija._dozvoliDupliranje;
		for (size_t i = 0; i < _trenutnoElemenata; i++)
		{
			_elementi1[i] = new T1(*kolekcija._elementi1[i]);
			_elementi2[i] = new T2(*kolekcija._elementi2[i]);
		}
	}
	Kolekcija& operator=(const Kolekcija& kolekcija) {
		if (this != &kolekcija) {
			for (size_t i = 0; i < _trenutnoElemenata; i++) {
				delete _elementi1[i]; _elementi1[i] = nullptr;
				delete _elementi2[i]; _elementi2[i] = nullptr;
			};
			_trenutnoElemenata = kolekcija._trenutnoElemenata;
			_dozvoliDupliranje = kolekcija._dozvoliDupliranje;
			_sortiranje = kolekcija._sortiranje;
			for (size_t i = 0; i < _trenutnoElemenata; i++)
			{
				_elementi1[i] = new T1(*kolekcija._elementi1[i]);
				_elementi2[i] = new T2(*kolekcija._elementi2[i]);
			}
		}
		return *this;
	}
	~Kolekcija() {
		for (size_t i = 0; i < _trenutnoElemenata; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
	}
	int GetTrenutno() const { return _trenutnoElemenata; }
	int GetMax() const { return max; }

	T1& GetElement1(int lokacija) const {
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw exception(nedozvoljena_operacija);
		return *_elementi1[lokacija];
	}
	T2& GetElement2(int lokacija) const {
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw exception(nedozvoljena_operacija);
		return *_elementi2[lokacija];
	}
	void SetElement2(int lokacija, T2 ele2) {
		_elementi2[lokacija] = ele2;
	}
	friend ostream& operator<<(ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj.GetElement1(i) << " " << obj.GetElement2(i) << endl;
		return COUT;
	}
	void AddElement(T1 a, T2 b) {
		if (_trenutnoElemenata == max) {
			throw exception("Dosegli ste maksimalan broj elemenata!\n");
		}
		if (!_dozvoliDupliranje) {
			for (size_t i = 0; i < _trenutnoElemenata; i++)
			{
				if (*_elementi1[i] == a && *_elementi2[i] == b) {
					throw exception("Dupliranje elemenata nije dozvoljeno!\n");
				}
			}
		}
		_elementi1[_trenutnoElemenata] = new T1(a);
		_elementi2[_trenutnoElemenata] = new T2(b);
		_trenutnoElemenata++;
		if (_sortiranje == ASC) {
			SortASC();
			return;
		}
		SortDESC();
		
	}
	void SortASC() {
		for (size_t i = 0; i < _trenutnoElemenata - 1; i++)
		{
			for (size_t j = 0; j < _trenutnoElemenata - i - 1; j++)
			{
				if (*_elementi1[j] > * _elementi1[j + 1]) {
					Swap(j, j + 1);
				}
			}
		}
	}
	void SortDESC() {
		for (size_t i = 0; i < _trenutnoElemenata - 1; i++)
		{
			for (size_t j = 0; j < _trenutnoElemenata - i - 1; j++)
			{
				if (*_elementi1[j] < * _elementi1[j + 1]) {
					Swap(j, j + 1);
				}
			}
		}
	}
	void Swap(int i, int j) {
		T1 temp1 = *_elementi1[i];
		*_elementi1[i] = *_elementi1[j];
		*_elementi1[j] = temp1;
		T2 temp2 = *_elementi2[i];
		*_elementi2[i] = *_elementi2[j];
		*_elementi2[j] = temp2;
	}
};

class Aktivnost {
	shared_ptr<Razred> _razred;
	string _opis;
	int _ocjena;//1-5
public:
	Aktivnost(Razred razred = I, int ocjena = 0, string opis = not_set) {
		_ocjena = ocjena;
		_opis = opis;
		_razred = make_shared<Razred>(razred);
	}
	Aktivnost(const Aktivnost& aktivnost) {
		_razred = make_shared<Razred>(*aktivnost._razred);
		_opis = aktivnost._opis;
		_ocjena = aktivnost._ocjena;
	}
	Aktivnost& operator=(const Aktivnost& aktivnost) {
		if (this != &aktivnost) {
			*_razred = *aktivnost._razred;
			_opis = aktivnost._opis;
			_ocjena = aktivnost._ocjena;
		}
		return *this;
	}
	friend bool operator==(const Aktivnost& lijeva, const Aktivnost& desna) {
		return *lijeva._razred == *desna._razred && lijeva._opis == desna._opis && lijeva._ocjena == desna._ocjena;
	}
	int  GetOcjenu() const { return _ocjena; }
	string GetOpis() const { return _opis; }
	Razred GetRazred() const { return *_razred; }

	friend ostream& operator<<(ostream& COUT, const Aktivnost& obj) {
		COUT << charRazred[*obj._razred-1] << " " << obj._ocjena << " " << obj._opis << endl;
		return COUT;
	}
};

class Polaznik {
protected:
	char* _imePrezime;
	string _brojTelefona;
public:
	Polaznik(string imePrezime, string brojTelefona) : _imePrezime(AlocirajNizKaraktera(imePrezime.c_str())) {
		_brojTelefona = brojTelefona;
	}
	~Polaznik() { delete[] _imePrezime; }
	char* GetImePrezime() { return _imePrezime; }
	string GetTelefon() { return _brojTelefona; }
	virtual void PredstaviSe() = 0;
};

class Ucenik : public Polaznik{
	Kolekcija<Predmet, Aktivnost, 16>* _aktivnosti;
public:
	Ucenik(string ime, string telefon) : Polaznik(ime,telefon){
		_aktivnosti = new Kolekcija<Predmet, Aktivnost, 16>();
	}
	Ucenik(const Ucenik& ucenik) : Polaznik(ucenik._imePrezime, ucenik._brojTelefona) {
		_aktivnosti = new Kolekcija<Predmet, Aktivnost, 16>(*ucenik._aktivnosti);
	}
	~Ucenik() { delete _aktivnosti; _aktivnosti = nullptr; }
	Kolekcija<Predmet, Aktivnost, 16>& GetAktivnosti() { return *_aktivnosti; };
	friend ostream& operator<<(ostream& COUT, Ucenik& n)
	{
		COUT << "Ime ->\t" << n._imePrezime << endl;
		COUT << "Broj telefona->\t" << n._brojTelefona << endl;
		COUT << "Aktivnosti \n";
		COUT << *n._aktivnosti << endl;
		return COUT;
	}
	void PredstaviSe() override {

	}
	float GetProsjekRazred(Razred razred) {
		float prosjek = 0;
		int brojac = 0;
		for (size_t i = 0; i < _aktivnosti->GetTrenutno(); i++)
		{
			if (_aktivnosti->GetElement2(i).GetRazred() == razred) {
				prosjek += _aktivnosti->GetElement2(i).GetOcjenu();
				brojac++;
			}
		}
		return prosjek / brojac;
	}
	float GetProsjekSve() {
		float prosjek = 0;
		int brojac = 0;
		for (size_t i = 0; i < _aktivnosti->GetTrenutno(); i++)
		{
			prosjek += _aktivnosti->GetElement2(i).GetOcjenu();
			brojac++;
		}
		return prosjek / brojac;
	}
};
class Skola {
	char* _naziv;
	vector<Ucenik> _ucenici;
public:
	Skola(const char* naziv = nullptr) {
		_naziv = AlocirajNizKaraktera(naziv);
	}
	Skola(const Skola& skola) {
		_naziv = AlocirajNizKaraktera(skola._naziv);
		_ucenici = skola._ucenici;
	}
	~Skola() {
		delete[] _naziv; _naziv = nullptr;
	}
	void operator()(string ime, string brojTelefona) {
		for (size_t i = 0; i < _ucenici.size(); i++)
		{
			if (_ucenici[i].GetImePrezime() == ime || _ucenici[i].GetTelefon() == brojTelefona) {
				throw exception("Nije moguce dodavanja ucenika sa istim imenom ili broj telefona!\n");
			}
		}
		regex rule("(\\+\\d{3}(([(]61[)])|([ ]61[ ]))\\d{3}[-]\\d{3})");
		if (!regex_match(brojTelefona, rule)) {
			brojTelefona = "not_set";
		}
		_ucenici.push_back(Ucenik(ime, brojTelefona));
	}
	char* GetNaziv()const { return _naziv; }
	vector<Ucenik>& GetUcenici() { return _ucenici; };

	friend ostream& operator<<(ostream& COUT, Skola& obj) {
		COUT << "Skola: " << obj._naziv << endl;
		COUT << "Ucenici: " << endl;
		for (size_t i = 0; i < obj._ucenici.size(); i++)
			COUT << obj._ucenici[i] << endl;
		return COUT;
	}
	void PosaljiSMS(Razred razred, double prosjek) {
		cout << "Uspjesno ste okoncali aktivnosti u okviru " << razred << " razreda sa prosjecnom ocjenom " << prosjek << endl;
	}
	bool DodajAktivnost(string ime, Predmet predmet, Aktivnost aktivnost) {
		int maxPredmetaRazred = 4;
		int brojacPredmetaRazred = 0;
		int lokUcenika = -1;
		for (size_t i = 0; i < _ucenici.size(); i++)
		{
			if (_ucenici[i].GetImePrezime() == ime) {
				for (size_t j = 0; j < _ucenici[i].GetAktivnosti().GetTrenutno(); j++)
				{
					if (predmet == _ucenici[i].GetAktivnosti().GetElement1(j) && aktivnost.GetRazred() == _ucenici[i].GetAktivnosti().GetElement2(j).GetRazred()) {
						return false;
					}
					if (aktivnost.GetRazred() == _ucenici[i].GetAktivnosti().GetElement2(j).GetRazred()) {
						brojacPredmetaRazred++;
					}
				}
				if (brojacPredmetaRazred >= 4) {
					return false;
				}
				lokUcenika = i;
				break;
			}
		}
		if (lokUcenika > -1) {
			_ucenici[lokUcenika].GetAktivnosti().AddElement(predmet, aktivnost);
			if (_ucenici[lokUcenika].GetProsjekRazred(aktivnost.GetRazred()) > 1  && _ucenici[lokUcenika].GetTelefon() != "not_set") {
				cout << "Prosjek je veci od 1!\n";
				cout << _ucenici[lokUcenika].GetTelefon()<<endl << _ucenici[lokUcenika].GetImePrezime() << endl;
				thread jedan(&Skola::PosaljiSMS, this, aktivnost.GetRazred(), _ucenici[lokUcenika].GetProsjekRazred(aktivnost.GetRazred()));
				jedan.join();
			}
			return true;
		}
		return false;
	}
	pair<Polaznik*, float> GetNajboljegUcenika() {
		Polaznik* pol;
		float max = -1;
		for (size_t i = 0; i < _ucenici.size(); i++)
		{
			if (_ucenici[i].GetProsjekSve() > max) {
				max = _ucenici[i].GetProsjekSve();
				pol = &_ucenici[i];
			}
		}
		return make_pair(pol, max);
	}
	bool SpasiUFajl(string nazivFajla, bool obrisi = false) {
		fstream upis;
		if (obrisi) {
			upis.open(nazivFajla,ios::out | ios::trunc);
		}
		else {
			upis.open(nazivFajla, ios::out | ios::app);
		}
		if (upis.fail()) {
			return false;
		}
		upis << *this;

		upis.close();
		return true;
	}
};

int main() {
	Kolekcija<int, int, 10> kolekcija1(DESC, false);
	try {
		kolekcija1.AddElement(1, 2);
		//dupliranje elemenata nije dozvoljeno
		kolekcija1.AddElement(1, 2);
	}
	catch (exception& ex) {
		cout << ex.what();
	}

	/*nakon svakog dodavanja, elemente sortirati prema T1 i vrijednosti atributa _sortiranje*/
	for (size_t i = 1; i < kolekcija1.GetMax() - 1; i++)
		kolekcija1.AddElement(rand(), rand());

	cout << kolekcija1 << endl;

	try {
		//prekoracen maksimalan broj elemenata
		kolekcija1.AddElement(rand(), rand());
	}
	catch (exception& ex) {
		cout << ex.what();
	}
	cout << kolekcija1 << endl;

	Kolekcija<int, int, 10> kolekcija2(kolekcija1);
	cout << kolekcija2 << endl;

	Skola gimnazijaMostar("GIMNAZIJA MOSTAR");
	//dodaje novog ucenika u skolu
	gimnazijaMostar("Jasmin Azemovic", "+387(61)111-222");
	gimnazijaMostar("Adel Handzic", "+387(61)333-444");

	/*
	koristeci regex, osigurati sljedeci format za broj telefona: +387(6X)XXX-XXX ili +387 6X XXX-XXX
	onemoguciti pojavljivanje samo jedne zagrade, a ukoliko format nije adekvatna koristiti vrijednost not_set
	*/
	gimnazijaMostar("Telefon NotValidFormat", "387 61)333-444");

	try
	{
		/*onemoguciti dodavanje ucenika sa istim imenom i prezimenom ili brojem telefona*/
		gimnazijaMostar("Adel Handzic", "+387(61)333-444");
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}

	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", MATEMATIKA, Aktivnost(I, 4, "Priprema za takmicenje iz Matematije koje se odrzava u Konjicu 07.02.2019")))
		cout << "Aktivnost uspjesno dodana" << endl;
	/*na nivou svakog razreda se mogu evidentirati maksimalno 4 aktivnosti, a takodjer, na nivou razreda se ne smiju ponavljati aktivnosti iz istog predmeta*/
	if (!gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", MATEMATIKA, Aktivnost(I, 4, "Aktivnosti iz matematike")))
		cout << "Aktivnost nije uspjesno dodana" << endl;
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", HEMIJA, Aktivnost(I, 5, "Priprema otopina za vjezbe iz predmeta Hemija")))
		cout << "Aktivnost uspjesno dodana" << endl;
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", FIZIKA, Aktivnost(I, 4, "Analiza stepena apsorpcije materijala ")))
		cout << "Aktivnost uspjesno dodana" << endl;
	/*u slucaju da je ucenik uspjesno (ocjenom vecom od 1) realizovao aktivnosti na nivou odredjenog razreda, te posjeduje validan broj telefona,
	u okviru zasebnog thread-a se salje SMS sa sadrzajem "Uspjesno ste okoncali aktivnosti u okviru X razreda sa prosjecnom ocjenom X.X"*/
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", GEOGRAFIJA, Aktivnost(I, 4, "Izrada 5 reljefa Mostara")))
		cout << "Aktivnost uspjesno dodana" << endl;
	if (gimnazijaMostar.DodajAktivnost("Adel Handzic", MATEMATIKA, Aktivnost(I, 5, "Izrada skripte na temu integralni racun")))
		cout << "Aktivnost uspjesno dodana" << endl;

	//ispisuje sve ucenike i njihove aktivnosti
	cout << gimnazijaMostar << endl;


	pair<Polaznik*, float> par = gimnazijaMostar.GetNajboljegUcenika();
	cout << "Najbolji ucenik je " << par.first->GetImePrezime() << " sa prosjekom " << par.second << endl;

	/*U fajl (npr. Gimnazija.txt) upisati podatke (podatke upisati kao obicni tekst) o skoli i svim ucenicima.
	Nakon upisa, potrebno je ispisati sadrzaj fajla. Parametar tipa bool oznacava da li ce ranije dodani sadrzaj fajla prethodno biti pobrisan*/

	if (gimnazijaMostar.SpasiUFajl("Gimnazija.txt"))
		cout << "Podaci o ucenicima uspjesno pohranjeni u fajl" << endl;
	//if (gimnazijaMostar.SpasiUFajl("Gimnazija.txt", true))
	//	cout << "Podaci o ucenicima uspjesno pohranjeni u fajl" << endl;

	cin.get();
	system("pause>0");
	return 0;
}


