#include <iostream>
#include <ostream>
#include <istream>
#include <vector>
using namespace std;
class Plata
{   protected:
        int zi,luna,an;
        float suma;
        char tip;
    public:
        virtual void display()=0;
        Plata() {
		suma=0;
		zi=0;luna=0;an=0;
        }
        Plata(int z,int l,int a, float s) {
		this->zi=z;
		this->luna=l;
		this->an=a;
		this->suma=s;
	}

};
class card : public Plata
{   private:
        long long nr_card;
        string nume;
    public:
        card():Plata(){}
        ~card(){}
        card(int z,int l,int a, float s,string n,long long nr):Plata(z,l,a,s)
        {   this->nume=n;
            this->nr_card=nr;
        }
        void display()
        {   cout<<"Data in care a fost efectuata plata in valoare de:"<<this->suma<<"RON este "
            <<this->zi<<"."<<this->luna<<"."<<this->an<<". Numarul cardului este "<<this->nr_card<<". Numele este "<<this->nume<<endl;};
        friend istream & operator>>(istream  & in, card &p);
};
class cec : public Plata
{   private:
        string nume;
    public:
        cec():Plata(){}
        ~cec(){}
        cec(int z,int l,int a, float s,string n):Plata(z,l,a,s){this->nume=n;}
        void display()
        {   cout<<"Data in care a fost efectuata plata in valoare de:"<<this->suma<<"RON este "
            <<this->zi<<"."<<this->luna<<"."<<this->an<<". Numele este "<<this->nume<<endl;
        };
        friend istream & operator>>(istream  & in, cec &p);
};
class cash : public Plata
{   public:
        void display(){
            cout<<"Data in care a fost efectuata plata in valoare de:"<<this->suma<<"RON este "
            <<this->zi<<"."<<this->luna<<"."<<this->an<<endl;
            };
         cash(void) :Plata() {}
         ~cash(){}
         cash(int z,int l,int a, float s):Plata(z,l,a,s){}
         friend istream & operator>>(istream  & in, cash &p);
};
istream& operator >>(istream &in, card &p)
{
	cout << "Introduceti suma zi luna an numar card nume: ";
	in >>p.suma>> p.zi>>p.luna>>p.an>>p.nr_card;
	getline(in, p.nume);
	return in;
}
istream& operator >>(istream &in,  cash &p)
{
	cout << "Introduceti suma zi luna an: ";
	in >>p.suma>> p.zi>>p.luna>>p.an;
	return in;
}
istream& operator >>(istream &in, cec &p)
{
	cout << "Introduceti suma zi luna an nume: ";
	in >>p.suma>> p.zi>>p.luna>>p.an;
	getline(in, p.nume);
	return in;
}
class numaratoare
{
protected:
    static long nr;
};

long numaratoare::nr = 0;
template <class T>
class Gestiune: private numaratoare
 {  private:
        vector<T*> chitanta;
    public:
        Gestiune() {}
        ~Gestiune() {}
	Gestiune(T *p) {
		chitanta.push_back(&p);
		nr++;
	}
	Gestiune(Gestiune<T> &p) {
		this->chitanta = p.chitanta;
		this->nr = p.nr;
	}


	Gestiune<T>& operator+= (T &x) {
		chitanta.push_back(&x);
		nr++;
		return *this;
	}

	void display() {

		card *A;
		cec *B;
		cash *C;

		for (int i = 0; i < chitanta.size(); i++)
		{
			try{
			A = dynamic_cast<card*>(chitanta[i]);
			B = dynamic_cast<cec*>(chitanta[i]);
			C = dynamic_cast<cash*>(chitanta[i]);

			if (A)
				A->display();

			if (B)
				B->display();

			if (C)
				C->display();

			}
			catch (const std::exception& bc)
			{
				cerr <<"exception caught"<< bc.what() << '\n';
			}
		}
	}
	void display_numar(){cout<<"Numar chitante actual:"<<nr<<endl;};

};
int main()
{
    card p1;
    cec p3;
    cash p2;
    int i,n,tip;
    Gestiune<Plata> P;
	cout<<"Introduceti numar clienti:\n";
	cin>>n;
	for (i=0;i<n;i++)
    {cout<<"Introduceti tipul platii 1.Card 2.Cash 3.Cec:";
     cin>>tip;
     if (tip==1) {cin>>p1;P+=p1;P.display_numar();}
     if (tip==2) {cin>>p2;P+=p2;P.display_numar();}
     if (tip==3) {cin>>p3;P+=p3;P.display_numar();}
    }
    P.display();



    return 0;
}
