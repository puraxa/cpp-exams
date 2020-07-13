#include <iostream>
#include <exception>
#include <thread>
#include <regex>
#include <vector>

using namespace std;
char* AlocirajNizKaraktera(const char* nesto) {
    char* temp = new char[strlen(nesto) + 1];
    strcpy_s(temp, strlen(nesto) + 1, nesto);
    return temp;
}

class Datum
{
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000)
    {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
    }
    Datum(const Datum& datum) {
        _dan = new int(*datum._dan);
        _mjesec = new int(*datum._mjesec);
        _godina = new int(*datum._godina);
    }
    ~Datum()
    {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    Datum& operator=(const Datum& datum) {
        if (this != &datum) {
            delete _dan;
            delete _mjesec;
            delete _godina;
            _dan = new int(*datum._dan);
            _mjesec = new int(*datum._mjesec);
            _godina = new int(*datum._godina);
        }
        return *this;
    }
    friend ostream& operator<< (ostream& COUT, Datum& obj)
    {
        COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina << endl;
        return COUT;
    }
    friend bool operator==(const Datum& lijevi, const Datum& desni) {
        return *lijevi._dan == *desni._dan && *lijevi._mjesec == *desni._mjesec && *lijevi._godina == *desni._godina;
    }
    int getDani() {
        return *_dan + *_mjesec * 30 + *_godina * 365;
    }
};

class Izuzetak :public exception
{
    Datum _datum;//KORISTITE DANASNJI DATUM
    string _funkcija;//FUNKCIJA U KOJOJ JE NASTAO IZUZETAK
    int _linija;//LINIJA CODE-A U KOJOJ JE NASTAO IZUZETAK
public:
    Izuzetak(Datum datum, string funkcija, int linija) {
        _datum = datum;
        _funkcija = funkcija;
        _linija = linija;
    }
    friend ostream& operator<<(ostream& cout, Izuzetak& izuzetak) {
        cout << izuzetak._datum;
        cout << "Funkcija -> " << izuzetak._funkcija << endl;
        cout << "Linija -> " << izuzetak._linija << endl;
        return cout;
    }
};
template<class T1, class T2, int max>
class Kolekcija
{
    T1 _elementi1[max];
    T2 _elementi2[max];
    int* _trenutno;
public:
    Kolekcija() {
        _trenutno = new int(0);
    }
    Kolekcija(const Kolekcija& kolekcija) {
        _trenutno = new int(*kolekcija._trenutno);
        for (size_t i = 0; i < *_trenutno; i++)
        {
            _elementi1[i] = kolekcija._elementi1[i];
            _elementi2[i] = kolekcija._elementi2[i];
        }
    }
    Kolekcija& operator=(const Kolekcija& kolekcija) {
        if (this != &kolekcija) {
            delete _trenutno;
            _trenutno = new int(*kolekcija._trenutno);
            for (size_t i = 0; i < *_trenutno; i++)
            {
                _elementi1[i] = kolekcija._elementi1[i];
                _elementi2[i] = kolekcija._elementi2[i];
            }
        }
        return *this;
    }
    ~Kolekcija() {
        delete _trenutno;
        _trenutno = nullptr;
    }
    int size() {
        return *_trenutno;
    }
    int GetMax() {
        return max;
    }
    int GetTrenutno() {
        return *_trenutno;
    }
    T1& operator[](int lok) {
        return _elementi1[lok];
    }
    T1& GetElement1(int lok) {
        if (lok > * _trenutno) {
            throw Izuzetak(Datum(12,7,2020), "GetElement1", 118);
        }
        return _elementi1[lok];
    }
    T2& GetElement2(int lok) {
        if (lok > * _trenutno) {
            throw Izuzetak(Datum(12, 7, 2020), "GetElement2", 124);
        }
        return _elementi2[lok];
    }
    void AddElement(T1 a, T2 b) {
        if (*_trenutno == max) {
            throw Izuzetak(Datum(12, 7, 2020), "AddElement", 130);
        }
        _elementi1[*_trenutno] = a;
        _elementi2[*_trenutno] = b;
        (*_trenutno)++;
    }
    friend ostream& operator<<(ostream& cout, Kolekcija& kolekcija) {
        cout << "Trenutno -> " << kolekcija.GetTrenutno() << endl;
        cout << "Max -> " << kolekcija.GetMax() << endl;
        for (size_t i = 0; i < kolekcija.GetTrenutno(); i++)
        {
            cout << kolekcija.GetElement1(i) << " " << kolekcija.GetElement2(i) << endl;
        }
        return cout;
    }
    friend bool operator==(Kolekcija& lijevi,Kolekcija& desni) {
        if (lijevi.GetTrenutno() != desni.GetTrenutno()) {
            return false;
        }
        for (size_t i = 0; i < lijevi.GetTrenutno(); i++)
        {
            if (lijevi.GetElement1(i) != desni.GetElement1(i) || lijevi.GetElement2(i) != desni.GetElement2(i)) {
                return false;
            }
        }
        return true;
    }
};



enum enumKursevi { HtmlCSSJavaScript, SoftwareEngeneeringFundamentals, MasteringSQL, WindowsSecurity };
class Kurs
{
    enumKursevi _kurs;
    Datum _pocetak;
    Datum _kraj;
    char* _imePredavaca;
public:
    Kurs() {
        _imePredavaca = nullptr;
    }
    Kurs(enumKursevi kurs, const char* imePredavaca, Datum pocetak, Datum kraj) {
        _kurs = kurs;
        _pocetak = pocetak;
        _kraj = kraj;
        _imePredavaca = AlocirajNizKaraktera(imePredavaca);
    }
    Kurs(const Kurs& kurs) {
        _kurs = kurs._kurs;
        _pocetak = kurs._pocetak;
        _kraj = kurs._kraj;
        _imePredavaca = AlocirajNizKaraktera(kurs._imePredavaca);
    }
    Kurs& operator=(const Kurs& kurs) {
        if (this != &kurs) {
            _pocetak = kurs._pocetak;
            _kraj = kurs._kraj;
            delete[]_imePredavaca;
            _imePredavaca = AlocirajNizKaraktera(kurs._imePredavaca);
            _kurs = kurs._kurs;
        }
        return *this;
    }
    char* getIme() {
        return _imePredavaca;
    }
    enumKursevi geteKurs() {
        return _kurs;
    }
    Datum& GetKraj() {
        return _kraj;
    }
    Datum& GetPocetak() {
        return _pocetak;
    }
    ~Kurs() {
        delete[]_imePredavaca;
        _imePredavaca = nullptr;
    }
    friend ostream& operator<<(ostream& cout, Kurs& kurs) {
        cout << "Ime predavaca -> " << kurs._imePredavaca << endl;
        cout << "Datum pocetka -> " << kurs._pocetak;
        cout << "Datum kraja -> " << kurs._kraj;
        cout << "Kurs -> " << kurs._kurs << endl;
        return cout;
    }
    friend bool operator==(const Kurs& lijevi, const Kurs& desni) {
        return strcmp(lijevi._imePredavaca, desni._imePredavaca) == 0 && lijevi._kurs == desni._kurs && lijevi._pocetak == desni._pocetak && lijevi._kraj == desni._kraj;
    }
};
class Polaznik
{
    static int ID;
    const int _polaznikID;
    //SVAKOM NOVOM POLAZNIKU AUTOMATSKI DODIJELITI NOVI ID (AUTOINCREMENT) POCEVSI OD BROJA 1
    char* _imePrezime;
    string _kontaktTelefon; //BROJ TELEFONA TREBA BITI U FORMATU (06X)XXX-XXX 
    Kolekcija<Kurs*, int, 10> _uspjesnoOkoncaniKursevi;
    //INT PREDSTAVLJA OSTVARENI PROCENAT NA ISPITU, A JEDAN POLAZNIK MOZE POLOZITI NAJVISE 10 KURSEVA
public:
    Polaznik(const char* imePrezime, string telefon) : _polaznikID(ID++)
    {
        cout << "Polaznikid " << _polaznikID << endl;
        int size = strlen(imePrezime) + 1;
        _imePrezime = new char[size];
        strcpy_s(_imePrezime, size, imePrezime);
        _kontaktTelefon = telefon;
    }
    Polaznik(const Polaznik& polaznik) : _polaznikID(polaznik._polaznikID){
        _imePrezime = AlocirajNizKaraktera(polaznik._imePrezime);
        _kontaktTelefon = polaznik._kontaktTelefon;
        _uspjesnoOkoncaniKursevi = polaznik._uspjesnoOkoncaniKursevi;
    }
    Polaznik& operator=(const Polaznik& polaznik) {
        if (this != &polaznik) {
            delete[]_imePrezime;
            _imePrezime = AlocirajNizKaraktera(polaznik._imePrezime);
            _kontaktTelefon = polaznik._kontaktTelefon;
            _uspjesnoOkoncaniKursevi = polaznik._uspjesnoOkoncaniKursevi;
        }
        return *this;
    }
    char* getIme() {
        return _imePrezime;
    }
    ~Polaznik()
    {
        delete[] _imePrezime; _imePrezime = nullptr;
      /*  for (size_t i = 0; i < _uspjesnoOkoncaniKursevi.size(); i++)
        {
            delete _uspjesnoOkoncaniKursevi[i];
            _uspjesnoOkoncaniKursevi[i] = nullptr;
        }*/
    }
    friend ostream& operator<<(ostream& cout, Polaznik& polaznik) {
        cout << "ID -> " << polaznik._polaznikID << endl;
        cout << "Ime -> " << polaznik._imePrezime<< endl;
        cout << "Kontakt telefon -> " << polaznik._kontaktTelefon << endl;
        cout << "Kursevi -> " << polaznik._uspjesnoOkoncaniKursevi << endl;
        return cout;
    }
    friend bool operator==(Polaznik& lijevi,Polaznik& desni) {
        if (lijevi._uspjesnoOkoncaniKursevi.GetTrenutno() != desni._uspjesnoOkoncaniKursevi.GetTrenutno()) {
            return false;
        }
        return strcmp(lijevi._imePrezime, desni._imePrezime) == 0 && lijevi._uspjesnoOkoncaniKursevi == desni._uspjesnoOkoncaniKursevi;
    }
    int getId() {
        return _polaznikID;
    }
    void addKurs(Kurs& kurs, int procenat) {
        _uspjesnoOkoncaniKursevi.AddElement(&kurs, procenat);
    }
};
int Polaznik::ID = 0;
class SkillsCentar
{
    string _nazivCentra;
    vector<Kurs> _kursevi;//KURSEVI KOJE NUDI ODREDJENI CENTAR
    Kolekcija<Kurs, Polaznik*, 150> _aplikanti;
public:
    SkillsCentar(string naziv) { _nazivCentra = naziv; }
    SkillsCentar(const SkillsCentar& obj) :_kursevi(obj._kursevi), _aplikanti(obj._aplikanti)
    {
        _nazivCentra = obj._nazivCentra;
    }
    SkillsCentar& operator=(const SkillsCentar& obj) {
        if (this != &obj) {
            _nazivCentra = obj._nazivCentra;
            _kursevi = obj._kursevi;
            _aplikanti = obj._aplikanti;
        }
        return *this;
    }
    ~SkillsCentar() {
        cout << "Destruktor pozvan skillscentar \n";
    }
    bool provjerikoliziju(Kurs kurs) {
        for (size_t i = 0; i < _kursevi.size(); i++)
        {
            if (_kursevi[i].GetKraj().getDani() > kurs.GetPocetak().getDani() && _kursevi[i].GetPocetak().getDani() < kurs.GetPocetak().getDani()) {
                return false;
            }
            if (kurs.GetPocetak().getDani() > _kursevi[i].GetPocetak().getDani() && kurs.GetPocetak().getDani() < _kursevi[i].GetKraj().getDani()) {
                return false;
            }
        }
        return true;
    }
    void addkurs(Kurs kurs) {
        for (size_t i = 0; i < _kursevi.size(); i++)
        {
            if (kurs == _kursevi[i]) {
                return;
            }
        }
        _kursevi.push_back(kurs);
    }
    void addaplikaciju(Kurs& kurs, Polaznik& polaznik) {
        bool pronadjen = false;
        for (size_t i = 0; i < _kursevi.size(); i++)
        {
            if (_kursevi[i] == kurs) {
                pronadjen = true;
            }
        }
        if (!pronadjen) {
            throw Izuzetak(Datum(20,7,2020), "addaplikaciju",297);
        }
        for (size_t i = 0; i < _aplikanti.size(); i++)
        {
            if (_aplikanti.GetElement1(i) == kurs && _aplikanti.GetElement2(i) == &polaznik) {
                throw Izuzetak(Datum(20,7,2020), "addaplikaciju",302);
            }
        }
        Polaznik* temp = new Polaznik(polaznik);
        cout << temp << "==" << &polaznik;
        _aplikanti.AddElement(kurs, &polaznik);
    }
    void dodajuspjesnookoncankurs(int id, Kurs& kurs, int procenat) {
        for (size_t i = 0; i < _aplikanti.size(); i++)
        {
            cout << _aplikanti.GetElement2(i)->getId() << endl;
            if (id == _aplikanti.GetElement2(i)->getId() && kurs == _aplikanti[i] && procenat> 55) {
                _aplikanti.GetElement2(i)->addKurs(kurs, procenat);
                cout << "Kurs dodan\n";
            }
        }
    }
    vector<Polaznik> getpolaznicibypredavac(const char* ime, enumKursevi ekurs) {
        vector<Polaznik>temp;
        for (size_t i = 0; i < _aplikanti.GetTrenutno(); i++)
        {
            if (strcmp(_aplikanti.GetElement1(i).getIme(), ime) == 0 && ekurs == _aplikanti.GetElement1(i).geteKurs()) {
                temp.push_back(Polaznik(*_aplikanti.GetElement2(i)));
            }
        }
        return temp;
    }
    friend ostream& operator<<(ostream& cout, SkillsCentar& obj) {
        cout << "Naziv centra -> " << obj._nazivCentra <<endl;
        for (size_t i = 0; i < obj._kursevi.size(); i++)
        {
            cout << obj._kursevi[i] << endl;
        }
        for (size_t i = 0; i < obj._aplikanti.size(); i++)
        {
            cout << obj._aplikanti.GetElement1(i);
            cout << *obj._aplikanti.GetElement2(i);
        }
        return cout;
    }
    bool removekurs(Kurs kurs) {
        for (size_t i = 0; i < _aplikanti.size(); i++)
        {
            if (_aplikanti.GetElement1(i) == kurs) {
                return false;
            }
        }
        for (size_t i = 0; i < _kursevi.size(); i++)
        {
            if (kurs == _kursevi[i]) {
                _kursevi.erase(_kursevi.begin() + i);
                return true;
            }
        }
    }
};
const char* crt = "\n---------------------------------------\n";
bool ProvjeriFormatTelefona(string telefon) {
    regex rule("([(]06[0-9][)][0-9]{3,}[-][0-9]{3,})");
    if (regex_match(telefon, rule)) {
        return true;
    }
    return false;
}
void main()
{
    /****************************************************************************
    // 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
    // 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU
    //    RUNTIME ERROR ÆE BITI OZNACENO KAO "RE"
    // 3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEÈILO GUBLJENJE URAÐENOG ZADATKA
    // 4. PROGRAMSKI CODE SE TAKOÐER NALAZI U FAJLU CODE.TXT
    // 5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U
    //    TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE,
    //    POMOÆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
    // 6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAÈENO.
    ****************************************************************************/

#pragma region TestiranjeDatuma
    Datum danas(26, 11, 2015);
    Datum sutra(danas);
    Datum prekosutra;
    prekosutra = danas;
    cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region TestiranjeKolekcije
    Kolekcija<int, int, 10> kolekcija1;
    try
    {
        for (size_t i = 0; i < kolekcija1.GetMax(); i++)
            kolekcija1.AddElement(i, i + 2);
        //FUNKCIJA TREBA BACITI IZUZETAK U SLUCAJ DA NEMA VISE PROSTORA ZA DODAVANJE NOVIH ELEMENATA
        cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
        //cout << kolekcija1.GetElement1(20) << " " << kolekcija1.GetElement2(20) << endl;
        //FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO ELEMENT NA ZAHTIJEVANOJ LOKACIJI NE POSTOJI
    }
    catch (Izuzetak& err)
    {
        cout << "Greska -> " << err << endl;
    }

    cout << kolekcija1 << endl;
    Kolekcija<int, int, 10> kolekcija2;
    kolekcija2 = kolekcija1;
    cout << kolekcija2 << crt;
    if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
        cout << "ISTI BROJ ELEMENATA" << endl;
    Kolekcija<int, int, 10> kolekcija3(kolekcija2);
    cout << kolekcija3 << crt;
#pragma endregion

#pragma region testiranjekursa
    Kurs sef(SoftwareEngeneeringFundamentals, "jasmin azemovic", Datum(28, 1, 2016), Datum(15, 2, 2016));
    cout << sef << endl;
    Kurs msql(MasteringSQL, "adel handzic", Datum(28, 2, 2016), Datum(15, 3, 2016));
    sef = msql;
    if (sef == msql)//kursevi su isti ako posjeduju identicne vrijednosti svih atributa
        cout << "isti su kursevi" << endl;
    Kurs msql2(msql);
    cout << msql2 << endl;
#pragma endregion

#pragma region TestiranjePolaznika
    string telefon1 = "(061)111-111";
    string telefon2 = "(061)111222";
    string telefon3 = "(061)111-333";

    if (!ProvjeriFormatTelefona(telefon1))
        cout << "Broj " << telefon1 << " nije validan" << endl;
    if (!ProvjeriFormatTelefona(telefon2))
        cout << "Broj " << telefon2 << " nije validan" << endl;
    if (!ProvjeriFormatTelefona(telefon3))
        cout << "Broj " << telefon3 << " nije validan" << endl;


    Polaznik denis("Denis Music", telefon1);
    Polaznik denis2("Denis2 Music2", telefon3);

#pragma endregion

#pragma region testiranjecentra
    try
    {
        SkillsCentar mostar("skills center mostar");
        if (mostar.provjerikoliziju(sef)) //jedan kurs ne smije poceti dok drugi traje tj. vrijeme odrzavanja i
            mostar.addkurs(sef);          //kursa se ne smije poklapat
        if (mostar.provjerikoliziju(msql))
            mostar.addkurs(msql);
        if (mostar.provjerikoliziju(msql2))
            mostar.addkurs(msql2);
        //onemoguciti dodavanje identicnih kurseva. funkcija treba da baci izuzetak ukoliko se pokusa dodati identican kurs
        mostar.addaplikaciju(sef, denis);
        //onemoguciti apliciranje za kurseve koji nisu registrovani u centru
        //mostar.addaplikaciju(msql, denis);
        //mostar.addaplikaciju(msql, denis);
        //onemoguciti apliciranje za isti kurs. funkcija baza izuzetak
        cout << denis2 << endl;
        denis2 = denis;
        if (denis == denis2) //polaznici su isti ako posjeduju isto ime i ako su pohadjali iste kurseve
            cout << "isti su" << endl;

        mostar.dodajuspjesnookoncankurs(0, sef, 60);
        // broj 1 oznacava id polaznika. funkcija je zaduzena da polazniku 
        // doda informaciju o uspjesno polozenom kursu koji je poslan kao parametar. preduslov za dodavanje je da je 
        // polaznik prethodno aplicirao za taj kurs, te da je na ispitu ostvario vise od 55%
        mostar.dodajuspjesnookoncankurs(1, msql, 83);
        vector<Polaznik> listapolaznika = mostar.getpolaznicibypredavac("jasmin azemovic", SoftwareEngeneeringFundamentals);
        //vraca informacije o polaznicima koji su kod odredjenog predavaca uspjesno okoncali odredjeni kurs

        if (mostar.removekurs(sef))//onemoguciti uklanjanje kursa koji su vec prijavili neki od polaznika
            cout << "kurs " << sef << " uspjesno uklonjen iz centra " << mostar << endl;

        SkillsCentar sarajevo = mostar;
        cout << sarajevo << endl;
    }
    catch (Izuzetak& err)
    {
        cout << err << endl;
    }
#pragma endregion
    system("pause");
}