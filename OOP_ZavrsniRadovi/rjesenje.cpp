#include<iostream>
#include<string>
#include<vector>
using namespace std;

/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR �E BITI OZNACENO KAO "RE"
3. SPA�AVAJTE PROJEKAT KAKO BI SE SPRIJE�ILO GUBLJENJE URA�ENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTI�NI ONIMA KOJI SU KORI�TENI U TESTNOM CODE-U, OSIM U SLU�AJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMO�NE FUNKCIJE MO�ETE IMENOVATI I DODAVATI PO �ELJI.
5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNA�ENO.
****************************************************************************/
const char* crt = "\n-------------------------------------------\n";
const char* nedozvoljena_operacija = "Nedozvoljena operacija";
const char* not_set = "NOT_SET";
const int min_polgavlja = 3;
const int min_karaktera_po_poglavlju = 30;

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
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
public:
	Kolekcija() :_trenutno(0), _elementi1(nullptr), _elementi2(nullptr) { }
	~Kolekcija() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi1 = nullptr;
	}
	T1* getElementi1Pok() { return _elementi1; }
	T2* getElementi2Pok() { return _elementi2; }
	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
	int getTrenutno() { return _trenutno; }

	friend ostream& operator<<(ostream& COUT, Kolekcija<T1, T2>& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}
	void AddElement(T1 a, T2 b) {
		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];
		for (size_t i = 0; i < _trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		temp1[_trenutno] = a;
		temp2[_trenutno] = b;
		delete[]_elementi1;
		delete[]_elementi2;
		_elementi1 = new T1[_trenutno + 1];
		_elementi2 = new T2[_trenutno + 1];
		for (size_t i = 0; i < _trenutno +1; i++)
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
};
class Poglavlje {
	char* _naslov;
	char* _sadrzaj;
	bool _prihvaceno;
	int _ocjena;//da bi se poglavlje smatralo prihvacenim ocjena mora biti u opsegu od 6 - 10
public:
	Poglavlje(const char* naslov = nullptr, const char* sadrzaj = nullptr)
		:_ocjena(0), _prihvaceno(false) {
		_naslov = AlocirajNizKaraktera(naslov);
		_sadrzaj = AlocirajNizKaraktera(sadrzaj);
	}
	Poglavlje(const Poglavlje& poglavlje) {
		_naslov = AlocirajNizKaraktera(poglavlje._naslov);
		_sadrzaj = AlocirajNizKaraktera(poglavlje._sadrzaj);
		_prihvaceno = poglavlje._prihvaceno;
		_ocjena = poglavlje._ocjena;
	}
	~Poglavlje() {
		delete[] _naslov; _naslov = nullptr;
		delete[] _sadrzaj; _sadrzaj = nullptr;
	}
	friend ostream& operator<<(ostream& COUT, Poglavlje& obj) {
		if (obj._naslov == nullptr || obj._sadrzaj == nullptr)
			return COUT;
		COUT << endl << obj._naslov << endl << obj._sadrzaj << endl;
		if (obj._prihvaceno)
			COUT << "Ocjena: " << obj._ocjena << endl;;
		return COUT;
	}
	char* GetNaslov() { return _naslov; }
	char* GetSadrzaj() { return _sadrzaj; }
	bool GetPrihvaceno() { return _prihvaceno; }
	int GetOcjena() { return _ocjena; }

	void OcijeniPoglavlje(int ocjena) {
		_ocjena = ocjena;
		if (_ocjena > 5 && ocjena <= 10)
			_prihvaceno = true;
	}
	void AddSadrzaj(string zaDodati) {
		string temp = string(_sadrzaj);
		temp += " " + zaDodati;
		delete[]_sadrzaj;
		_sadrzaj = AlocirajNizKaraktera(temp.c_str());
	}
	void SetOcjena(int ocjena){
		if (ocjena < 6) {
			throw exception("Ocjena nije validna");
		}
		_ocjena = ocjena;
		_prihvaceno = true;
	}
};

class ZavrsniRad {
	char* _tema;
	vector<Poglavlje> _poglavljaRada;
	string _datumOdbrane;
	float _konacnaOcjena; //prosjek ocjena svih poglavlja u zavrsnom radu koja se izracunava u momentu zakazivanja odbrane
public:
	ZavrsniRad(const char* nazivTeme = nullptr) : _konacnaOcjena(0), _datumOdbrane(not_set) {
		_tema = AlocirajNizKaraktera(nazivTeme);
	}

	ZavrsniRad(const ZavrsniRad& org) : _poglavljaRada(org._poglavljaRada), _konacnaOcjena(org._konacnaOcjena), _datumOdbrane(org._datumOdbrane) {
		_tema = AlocirajNizKaraktera(org._tema);
	}

	~ZavrsniRad() {
		delete[] _tema; _tema = nullptr;
	}
	char* GetNazivTeme()const { return _tema; }
	vector<Poglavlje>& GetPoglavlja() { return _poglavljaRada; };
	string GetDatumOdbrane()const { return _datumOdbrane; }
	float GetOcjena() { return _konacnaOcjena; }
	void SetDatumOdbrane(string datumOdbrane) { _datumOdbrane = datumOdbrane; }

	ZavrsniRad& operator=(const ZavrsniRad& org) {
		if (this != &org) {
			delete[] _tema;
			_tema = AlocirajNizKaraktera(org._tema);
			_datumOdbrane = org._datumOdbrane;
			_poglavljaRada = org._poglavljaRada;
			_konacnaOcjena = org._konacnaOcjena;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& COUT, ZavrsniRad& obj) {
		COUT << "Tema rada: " << obj._tema << endl;
		COUT << "Sadrzaj: " << endl;
		for (size_t i = 0; i < obj._poglavljaRada.size(); i++)
			COUT << obj._poglavljaRada[i] << endl;
		COUT << "Datum odbrane rada: " << obj._datumOdbrane << endl << " Ocjena: " << obj._konacnaOcjena << endl;
		return COUT;
	}
	void DodajPoglavlje(string naziv, string sadrzaj) {
		int lok = -1;
		for (size_t i = 0; i < _poglavljaRada.size(); i++)
		{
			if (strcmp(_poglavljaRada[i].GetNaslov(), naziv.c_str()) == 0) {
				lok = i;
				break;
			}
		}
		if (lok > -1) {
			_poglavljaRada[lok].AddSadrzaj(sadrzaj);
			return;
		}
		_poglavljaRada.push_back(Poglavlje(naziv.c_str(), sadrzaj.c_str()));
	}
	void OcijeniPoglavlje(string naziv, int ocjena) {
		for (size_t i = 0; i < _poglavljaRada.size(); i++)
		{
			if (strcmp(_poglavljaRada[i].GetNaslov(), naziv.c_str()) == 0) {
				_poglavljaRada[i].SetOcjena(ocjena);
				return;
			}
		}
		throw exception("Poglavlje ne postoji!\n");
	}
	friend bool operator==(const ZavrsniRad& lijevi, const ZavrsniRad& desni) {
		return strcmp(lijevi._tema, desni._tema) == 0;
	}
	bool Validan() {
		if (_poglavljaRada.size() <= min_polgavlja) {
			return false;
		}
		for (size_t i = 0; i < _poglavljaRada.size(); i++)
		{
			cout << "Prihvaceno -> " << _poglavljaRada[i].GetPrihvaceno() << endl;
			cout << "Strlen -> " << strlen(_poglavljaRada[i].GetSadrzaj()) << endl;
			if (!_poglavljaRada[i].GetPrihvaceno()) {
				return false;
			}
			if (strlen(_poglavljaRada[i].GetSadrzaj()) <= min_karaktera_po_poglavlju) {
				return false;
			}
		}
		return true;
	}
	void SetKonacnaOcjena() {
		_konacnaOcjena = 0;
		for (size_t i = 0; i < _poglavljaRada.size(); i++)
		{
			_konacnaOcjena += _poglavljaRada[i].GetOcjena();
		}
		_konacnaOcjena = _konacnaOcjena / _poglavljaRada.size();
	}
};

class Mentor {
	string _imePrezime;
	//Parametar string predstavlja broj indeksa studenta koji prijavljuje zavrsni rad kod odredjenog Mentora
	Kolekcija<string, ZavrsniRad> _teme;
public:
	Mentor(string imePrezime) :_imePrezime(imePrezime) {}
	Kolekcija<string, ZavrsniRad>& GetTeme() { return _teme; };
	string GetImePrezime() { return _imePrezime; }
	void Info() {
		cout << _imePrezime << endl << _teme << endl;
	}
	bool DodajZavrsniRad(string indeks, ZavrsniRad rad) {
		for (size_t i = 0; i < _teme.getTrenutno(); i++)
		{
			if (indeks == _teme.getElement1(i) || rad == _teme.getElement2(i)) {
				return false;
			}
		}
		_teme.AddElement(indeks, rad);
	}
	ZavrsniRad* ZakaziOdbranuRada(string indeks, string datum) {
		for (size_t i = 0; i < _teme.getTrenutno(); i++)
		{
			if (indeks == _teme.getElement1(i) && _teme.getElement2(i).Validan()) {
				_teme.getElement2(i).SetDatumOdbrane(datum);
				_teme.getElement2(i).SetKonacnaOcjena();
				return &_teme.getElement2(i);
			}
		}
		return nullptr;
	}
};

int main() {
	cout << crt << "UPLOAD RADA OBAVEZNO IZVRSITI U ODGOVARAJUCI FOLDER NA FTP SERVERU" << endl;
	cout << "U slucaju da je Upload folder prazan pritisnite tipku F5" << crt;

	const int max = 4;
	Mentor* mentori[max];

	mentori[0] = new Mentor("Armina Hubana");
	mentori[1] = new Mentor("Zanin Vejzovic");
	mentori[2] = new Mentor("Jasmin Azemovic");
	mentori[3] = new Mentor("Emina Junuz");
	//parametri: naziv zavrsnog rada
	ZavrsniRad multimedijalni("Multimedijalni informacijski sistem za visoko - obrazovnu ustanovu");
	ZavrsniRad podrsa_operaterima("Sistem za podr�ku rada kablovskog operatera");
	ZavrsniRad analiza_sigurnosti("Prakticna analiza sigurnosti be�i�nih ra�unarskih mre�a");
	ZavrsniRad kriptografija("Primjena teorije informacija u procesu generisanja kriptografskih klju�eva");

	/*u zavrsni rad dodaje novo poglavlje i njegov sadrzaj. ukoliko poglavlje vec postoji u zavrsnom radu, funkcija tom poglavlju treba dodati novi sadrzaj i pri tome zadrzi postojeci (izmedju postojeceg i novog sadrzaja se dodaje prazan prostor). u slucaju da poglavlje ne postoji, ono se dodaje zajedno sa sadrzaje*/
	//parametri: nazivPoglavlja, sadrzajPoglavlja
	multimedijalni.DodajPoglavlje("Uvod", "U ovom poglavlju ce biti rijeci");
	multimedijalni.DodajPoglavlje("Uvod", "o multimedijalnim sistemima koji se danas koriste");
	multimedijalni.DodajPoglavlje("Uvod", "u savremenom poslovanju");
	multimedijalni.DodajPoglavlje("Vrste multimedijalnih sistema", "Danas se moze govoriti o nekoliko vrsta multimedijalnih sistema, a neke od najznacajnijih su ...");
	multimedijalni.DodajPoglavlje("Teorija multimedije", "Sadrzaj koji bi trebao stajati na pocetku treceg poglavlja zavrsnog rada o multimediji studenta IB130011");
	multimedijalni.DodajPoglavlje("Zakljucak", "U ovom radu su predstavljeni osnovni koncepti i prakticna primjena...");

	try {
		/*funkcija OcijeniPoglavlje, na osnovu naziva poglavlja, dodjeljuje ocjenu poglavlju te ukoliko je ocjena pozitivna (6 - 10) onda poglavlje oznacava prihvacenim. U slucaju da ocjena nije validna ili poglavlje ne postoji, funkcija baca izuzetak sa odgovarajucom porukom*/
		//parametri:nazivPoglavlja, ocjena

		multimedijalni.OcijeniPoglavlje("Uvod", 8);
		multimedijalni.OcijeniPoglavlje("Vrste multimedijalnih sistema", 8);
		multimedijalni.OcijeniPoglavlje("Teorija multimedije", 9);
		multimedijalni.OcijeniPoglavlje("Zakljucak", 7);
		multimedijalni.OcijeniPoglavlje("Naziv poglavlja ne postoji", 8);
	}
	catch (exception& err) {
		cout << "Greska -> " << err.what() << endl;
	}

	/*funkcija DodajZavrsniRad ima zadatak da odredjenom Mentoru dodijeli mentorstvo na zavrsnom radu. zavrsni rad se dodaje studentu sa brojem indeksa proslijedjenim kao prvi parametar.
	sprijeciti dodavanje zavrsnih radova sa istom temom*/
	//parametri:brojIndeksa, zavrsniRad
	if (mentori[0]->DodajZavrsniRad("IB130011", multimedijalni))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (mentori[0]->DodajZavrsniRad("IB120051", podrsa_operaterima))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (!mentori[0]->DodajZavrsniRad("IB120056", podrsa_operaterima))//dupliranje rada
		cout << "Zavrsni rad nije dodat!" << endl;
	if (!mentori[0]->DodajZavrsniRad("IB120051", kriptografija)) //studentu vec dodijeljen rad
		cout << "Zavrsni rad nije dodat!" << endl;
	if (mentori[1]->DodajZavrsniRad("IB140102", analiza_sigurnosti))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (mentori[2]->DodajZavrsniRad("IB140002", kriptografija))
		cout << "Zavrsni rad uspjesno dodat!" << endl;

	/*funkcija ZakaziOdbranuRada ima zadatak da studentu sa proslijedjenim brojem indeksa zakaze odbranu zavrsnog rada sto podrazumijeva definisanje
	datuma odbrane. odbrana rada se moze zakazati samo studentu koji je rad prethodno prijavio i pri tom su zadovoljeni sljedeci uslovi:
		1. zavrsni rad ima broj poglavlja veci od minimalnog
		2. svako poglavlje ima broj karaktera veci od minimalnog
		3. svako poglavlje je prihvaceno/odobreno
	ukoliko su zadovoljeni prethodni kriteriji, izracunava se konacna ocjena rada (prosjek ocjena svih poglavlja), postavlja datum odbrane rada i vraca pokazivac na rad kome je zakazan odbrana.
	u slucaju da student sa primljenim brojem indeksa nije prijavio zavrsni rad ili neki od postavljenih kriterija nije zadovoljen, funkcija vraca nullptr.
*/

	//parametri:brojIndeksa, datumOdbrane
	ZavrsniRad* zr1 = mentori[0]->ZakaziOdbranuRada("IB130011", "25.09.2018");
	if (zr1 != nullptr)
		cout << *zr1 << endl;

	zr1 = mentori[0]->ZakaziOdbranuRada("IB130111", "25.09.2018");//student sa brojem indeksa IB130111 jos uvijek nije prijavio rad
	if (zr1 != nullptr)
		cout << *zr1 << endl;

//	ispisuje sve podatke o Mentoru i njegovim mentorstvima
	mentori[0]->Info();

	for (int i = 0; i < max; i++) {
		delete mentori[i];
		mentori[i] = nullptr;
	}
	system("pause>0");
	return 0;
}
