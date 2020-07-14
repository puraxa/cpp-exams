#include<iostream>
#include<regex>
#include<thread>
#include<vector>
#include<string>

using namespace std;

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO RE\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U,\n"
"\tOSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE\n"
"\tPOMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE!\n"
"7. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };
bool ValidirajEmail(string email) {
    regex rule("((([a-z]{4,}[.][a-z]{4,})|([a-z]{4,}))[@]((edu.fit)|(fit))[.]((ba)|(com)|(org)))");
    return regex_match(email, rule) ? true : false;
}
char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    if (dealociraj)
        delete[]sadrzaj;
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
    Kolekcija(const Kolekcija& obj) {
        _omoguciDupliranje = obj._omoguciDupliranje;
        _trenutno = obj._trenutno;
        _elementi1 = new T1[_trenutno];
        _elementi2 = new T2[_trenutno];
        for (size_t i = 0; i < _trenutno; i++)
        {
            _elementi1[i] = obj._elementi1[i];
            _elementi2[i] = obj._elementi2[i];
        }
    }
    Kolekcija& operator=(const Kolekcija& obj) {
        if (this != &obj) {
            delete[]_elementi1;
            delete[]_elementi2;
            _omoguciDupliranje = obj._omoguciDupliranje;
            _trenutno = obj._trenutno;
            _elementi1 = new T1[_trenutno];
            _elementi2 = new T2[_trenutno];
            for (size_t i = 0; i < _trenutno; i++)
            {
                _elementi1[i] = obj._elementi1[i];
                _elementi2[i] = obj._elementi2[i];
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
                    delete[] temp1;
                    delete[] temp2;
                    temp1 = nullptr;
                    temp2 = nullptr;
                    throw exception("Dupliranje elemenata nije dozvoljeno!\n");
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
        _trenutno++;
        delete[] temp1;
        delete[] temp2;
        temp1 = nullptr;
        temp2 = nullptr;
    }
    Kolekcija operator()(int a, int b) {
        if (a < 0 || b >= _trenutno) {
            throw exception("Proslijedjeni parametri ne odgovaraju!\n");
        }
        Kolekcija<T1, T2>temp;
        for (size_t i = a; i <= b; i++)
        {
            temp.AddElement(_elementi1[i], _elementi2[i]);
        }
        return temp;
    }
    int size()const {
        return _trenutno;
    }
    int getDupliranje()const {
        return _omoguciDupliranje;
    }
    friend bool operator==(const Kolekcija& lijeva, const Kolekcija& desna) {
        if (lijeva.getDupliranje() != desna.getDupliranje()) {
            return false;
        }
        if (lijeva.size() != desna.size()) {
            return false;
        }
        int brojac = 0;
        for (size_t i = 0; i < lijeva.size(); i++)
        {
            if (lijeva.getElement1(i) == desna.getElement1(i) && lijeva.getElement2(i) == desna.getElement2(i)) {
                brojac++;
            }
        }
        if (brojac == lijeva.size()) {
            return true;
        }
        return false;
    }
};
class Datum {
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
    }
    Datum(const Datum& obj) {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
    Datum& operator=(const Datum& obj) {
        if (this != &obj) {
            delete _dan;
            delete _mjesec;
            delete _godina;
            _dan = new int(*obj._dan);
            _mjesec = new int(*obj._mjesec);
            _godina = new int(*obj._godina);
        }
        return *this;
    }
    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }
    friend bool operator==(const Datum& lijevi, const Datum& desni) {
        return *lijevi._dan == *desni._dan && *lijevi._mjesec == *desni._mjesec && *lijevi._godina == *desni._godina;
    }
    int GetDani() {
        return *_dan + *_mjesec * 30 + *_godina * 365;
    }
};

class Predmet {
    char* _naziv;
    //int se odnosi na ocjenu u opsegu od 1 – 5, a datum na momenat postizanja ocjene
    Kolekcija<int, Datum> _ocjene;
public:
    Predmet(const char* naziv = "", int ocjena = 0, Datum datum = Datum()) {
        _naziv = GetNizKaraktera(naziv);
        if (ocjena > 0)
            _ocjene.AddElement(ocjena, datum);
    }
    Predmet(const Predmet& obj) {
        _naziv = GetNizKaraktera(obj._naziv);
        _ocjene = obj._ocjene;
    }
    Predmet& operator=(const Predmet& obj) {
        if (this != &obj) {
            delete[]_naziv;
            _naziv = GetNizKaraktera(obj._naziv);
            _ocjene = obj._ocjene;
        }
        return *this;
    }
    ~Predmet() {
        delete[] _naziv; _naziv = nullptr;
    }
    void AddOcjena(int ocjena, Datum datum) {
        _ocjene.AddElement(ocjena, datum);
    }
    char* GetNaziv() { return _naziv; }
    Kolekcija<int, Datum>& GetOcjene() { return _ocjene; }
    friend ostream& operator<<(ostream& cout, Predmet& predmet) {
        cout << "Naziv -> " << predmet._naziv << endl;
        for (size_t i = 0; i < predmet._ocjene.getTrenutno(); i++)
        {
            cout << "Ocjena -> " << predmet._ocjene.getElement1(i) << "\t" << "Datum -> " << predmet._ocjene.getElement2(i) << endl;
        }
        cout << "Prosjecna ocjena -> " << predmet.getProsjecnaOcjena() << endl;
        return cout;
    }
    friend bool operator==(const Predmet& lijevi, const Predmet& desni) {
        return strcmp(lijevi._naziv, desni._naziv) == 0 && lijevi._ocjene == desni._ocjene;
    }
    float getProsjecnaOcjena() {
        float prosjek = 0;
        for (size_t i = 0; i < _ocjene.getTrenutno(); i++)
        {
            prosjek += _ocjene.getElement1(i);
        }
        return prosjek > 0 ? prosjek / _ocjene.getTrenutno() : 0;
    }
    float getProsjecanBrojDana() {
        float prosjek = 0;
        for (size_t i = 1; i < _ocjene.size(); i++)
        {
            prosjek += _ocjene.getElement2(i).GetDani() - _ocjene.getElement2(i - 1).GetDani();
        }
        return prosjek > 0 ? prosjek / (_ocjene.size() - 1) : 0;
    }
};
class Uspjeh {
    eRazred _razred;
    //string se odnosi na napomenu o polozenom predmetu
    Kolekcija<Predmet, string>* _polozeniPredmeti;
public:
    Uspjeh(eRazred razred = PRVI) {
        _razred = razred;
        _polozeniPredmeti = new Kolekcija<Predmet, string>();
    }
    Uspjeh(const Uspjeh& obj) {
        _razred = obj._razred;
        _polozeniPredmeti = new Kolekcija<Predmet, string>(*obj._polozeniPredmeti);
    }
    Uspjeh& operator=(const Uspjeh& obj) {
        if (this != &obj) {
            delete _polozeniPredmeti;
            _polozeniPredmeti = new Kolekcija<Predmet, string>(*obj._polozeniPredmeti);
            _razred = obj._razred;
        }
        return *this;
    }
    ~Uspjeh() { delete _polozeniPredmeti; _polozeniPredmeti = nullptr; }

    Kolekcija<Predmet, string>* GetPredmeti() { return _polozeniPredmeti; }
    eRazred GetERazred() { return _razred; }
    friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
        COUT << obj._razred << " " << *obj._polozeniPredmeti << endl;
        return COUT;
    }
    friend bool operator==(const Uspjeh& lijevi, const Uspjeh& desni) {
        return lijevi._razred == desni._razred && *lijevi._polozeniPredmeti == *desni._polozeniPredmeti;
    }
    bool provjeriPredmet(Predmet predmet) {
        for (size_t i = 0; i < _polozeniPredmeti->getTrenutno(); i++)
        {
            if (predmet == _polozeniPredmeti->getElement1(i)) {
                return true;
            }
        }
        return false;
    }
    float getProsjek() {
        float prosjek = 0;
        for (size_t i = 0; i < _polozeniPredmeti->getTrenutno(); i++)
        {
            prosjek += _polozeniPredmeti->getElement1(i).getProsjecnaOcjena();
        }
        return prosjek > 0 ? prosjek / _polozeniPredmeti->size() : 0;
    }
};

class Kandidat {
    char* _imePrezime;
    string _emailAdresa;
    string _brojTelefona;
    vector<Uspjeh> _uspjeh;
public:
    Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) {
        _imePrezime = GetNizKaraktera(imePrezime);
        if (ValidirajEmail(emailAdresa)) {
            _emailAdresa = emailAdresa;
        }
		else {
			_emailAdresa = "notSet@edu.fit.ba";

		}
        _brojTelefona = brojTelefona;
    }
    Kandidat(const Kandidat& obj) {
        _imePrezime = GetNizKaraktera(obj._imePrezime);
        _emailAdresa = obj._emailAdresa;
        _brojTelefona = obj._brojTelefona;
        _uspjeh = obj._uspjeh;
    }
    Kandidat& operator=(const Kandidat& obj) {
        if (this != &obj) {
            delete[]_imePrezime;
            _imePrezime = GetNizKaraktera(obj._imePrezime);
            _emailAdresa = obj._emailAdresa;
            _brojTelefona = obj._brojTelefona;
            _uspjeh = obj._uspjeh;
        }
        return *this;
    }
    ~Kandidat() {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
        for (size_t i = 0; i < obj._uspjeh.size(); i++)
            COUT << obj._uspjeh[i];
        return COUT;
    }
    vector<Uspjeh>& GetUspjeh() { return _uspjeh; }
    string GetEmail() { return _emailAdresa; }
    string GetBrojTelefona() { return _brojTelefona; }
    char* GetImePrezime() { return _imePrezime; }
    void PosaljiSMS(int lok){
        cout << "Svaka cast za uspjeh " << _uspjeh[lok].getProsjek() << " u " << _uspjeh[lok].GetERazred() << " razredu. \n";
    }
    void PosaljiEmail(int lok) {
        cout << "FROM:info@fit.ba\nTO:" << _emailAdresa << endl;
        cout << "Postovani " << _imePrezime << ", evidentirali ste uspjeh za " << _uspjeh[lok].GetERazred() << "razred. Dosadasnji uspjeh na nivou " << _uspjeh[lok].GetERazred() << " iznosi " << _uspjeh[lok].getProsjek() << " , a ukupni uspjeh u toku skolovanja iznosi "<< this->getProsjek() << endl;
        cout << "Pozdrav.\nFIT Team." << crt;
        if (_uspjeh[lok].getProsjek() > 4.5) {
            thread dva(&Kandidat::PosaljiSMS, this, lok);
            dva.join();
        }
    }
    bool AddPredmet(eRazred razred, Predmet predmet, string napomena) {
        if (predmet.getProsjecnaOcjena() < 2.5) {
            return false;
        }
        int lok = -1;
        for (size_t i = 0; i < _uspjeh.size(); i++)
        {
            if (_uspjeh[i].GetERazred() == razred && (_uspjeh[i].provjeriPredmet(predmet) || _uspjeh[i].GetPredmeti()->getTrenutno() == 5) ) {
                return false;
            }
            if (_uspjeh[i].GetERazred() == razred) {
                lok = i;
            }
        }
        if (lok > -1) {
            _uspjeh[lok].GetPredmeti()->AddElement(predmet, napomena);
            thread jedan(&Kandidat::PosaljiEmail, this, lok);
            jedan.join();
            return true;
        }
        _uspjeh.push_back(Uspjeh(razred));
        _uspjeh[_uspjeh.size() - 1].GetPredmeti()->AddElement(predmet, napomena);
        thread jedan(&Kandidat::PosaljiEmail, this, _uspjeh.size()-1);
        jedan.join();
        return true;
    }
    float getProsjek() {
        float prosjek = 0;
        for (size_t i = 0; i < _uspjeh.size(); i++)
        {
            prosjek += _uspjeh[i].getProsjek();
        }
        return prosjek > 0 ? prosjek / _uspjeh.size() : 0;
    }
    Kolekcija<Predmet, float> operator()(Datum lijevi, Datum desni) {
        Kolekcija<Predmet, float>temp;
        for (size_t i = 0; i < _uspjeh.size(); i++)
        {
            for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
            {
                for (size_t k = 0; k < _uspjeh[i].GetPredmeti()->getElement1(j).GetOcjene().getTrenutno(); k++)
                {
                    if (_uspjeh[i].GetPredmeti()->getElement1(j).GetOcjene().getElement2(k).GetDani() > lijevi.GetDani() && _uspjeh[i].GetPredmeti()->getElement1(j).GetOcjene().getElement2(k).GetDani() < desni.GetDani()) {
                        temp.AddElement(_uspjeh[i].GetPredmeti()->getElement1(j), _uspjeh[i].GetPredmeti()->getElement1(j).getProsjecanBrojDana());
                    }
                }
            }
        }
        return temp;
    }
    Uspjeh* operator[](eRazred razred) {
        for (size_t i = 0; i < _uspjeh.size(); i++)
        {
            if (_uspjeh[i].GetERazred() == razred) {
                return &_uspjeh[i];
            }
        }
        return nullptr;
    }
};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Na sta se odnosi pojam reprezentacije tipa?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Na koji nacin se moze izbjeci pojavljivanje vise podobjekata bazne klase u slucaju visestrukog nasljedjivanja?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}

void main() {

    cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();

    Datum temp,
        datum19062019(19, 6, 2019),
        datum20062019(20, 6, 2019),
        datum30062019(30, 6, 2019),
        datum05072019(5, 7, 2019);

    int kolekcijaTestSize = 9;
    Kolekcija<int, int> kolekcija1(false);
    for (int i = 0; i <= kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement baca izuzetak
        kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    /*objekat kolekcija2 ce biti inicijalizovan elementima koji se u objektu kolekcija1 nalaze na lokacijama 1 - 4
    ukljucujuci i te lokacije. u konkretnom primjeru to ce biti parovi sa vrijednostima: 1 1 2 2 3 3 4 4*/
    Kolekcija<int, int> kolekcija2 = kolekcija1(1, 4);
    cout << kolekcija2 << crt;
    try {
        //primjeri u kojima opseg nije validan, te bi funkcija trebala baciti izuzetak
        Kolekcija<int, int> temp1 = kolekcija1(1, 14);//imamo 10 elemenata
        Kolekcija<int, int> temp2 = kolekcija1(-1, 8);//lokacija -1 ne postoji
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }

    //parametri: nazivPredmeta, prva ocjena, datum
    Predmet Matematika("Matematika", 5, datum19062019),
        Fizika("Fizika", 5, datum20062019),
        Hemija("Hemija", 2, datum30062019),
        Engleski("Engleski", 5, datum05072019);

    Matematika.AddOcjena(3, datum05072019);
    Matematika.AddOcjena(5, datum05072019);

    // ispisuje: naziv predmeta, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu na predmetu
    // ukoliko predmet nema niti jednu ocjenu prosjecna treba biti 0
    cout << Matematika << endl;

    if (ValidirajEmail("text.text@edu.fit.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@edu.fit.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@fit.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@fit.com"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@edu.fit.org"))
        cout << "Email validan" << crt;

    ///*
    //email adresa mora biti u formatu text.text (sa ili bez tacke),
    //dok domena moze biti fit.ba ili edu.fit.ba
    //nakon institucije (fit ili edu.fit), osim drzavne (.ba), dozvoljene su domene .com i .org.

    //za provjeru validnosti email adrese koristiti globalnu funkciju ValidirajEmail, a unutar nje regex metode.
    //validacija email adrese ce se vrsiti unutar konstruktora klase Kandidat, a u slucaju da nije validna
    //postaviti je na defaultnu adresu: notSet@edu.fit.ba
    //*/

    Kandidat jasmin("Jasmin Azemovic", "jasmin@fit.ba", "033 281 172");
    Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");
    Kandidat emailNotValid("Ime Prezime", "korisnik@klix.ba", "033 281 170");

    /*
    uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih clanova) predmeta na nivou jednog razreda,
    - dodavanje predmeta kod kojih je prosjecna ocjena manja od 2.5
    - dodavanje vise od 5 predmeta na nivou jednog razreda
    razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
    Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */
    if (jasmin.AddPredmet(DRUGI, Fizika, "Napomena 1"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(DRUGI, Hemija, "Napomena 2"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Engleski, "Napomena 3"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 4"))
        cout << "Predmet uspjesno dodan!" << crt;
    //ne treba dodati Matematiku jer je vec dodana u prvom razredu
    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 5"))
        cout << "Predmet uspjesno dodan!" << crt;

    /*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
    FROM:info@fit.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirali ste uspjeh za X razred. Dosadasnji uspjeh (prosjek)
    na nivou X razreda iznosi Y, a ukupni uspjeh u toku skolovanja iznosi Z.
    Pozdrav.
    FIT Team.
    ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.X u X razredu".
    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */
    cout << jasmin << crt;

    ////vraca kolekciju predmeta koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    ////float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na predmetu
    Kolekcija<Predmet, float> jasminUspjeh = jasmin(Datum(18, 06, 2019), Datum(21, 06, 2019));
    cout << jasminUspjeh << crt;
    cout << "Uspjeh\n";
    Uspjeh* uspjeh_Irazred = jasmin[PRVI];//vraca uspjeh kandidata ostvaren u prvom razredu
    if (uspjeh_Irazred != nullptr)
        cout << *uspjeh_Irazred << crt;

    cin.get();
    system("pause>0");
}

