#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

class Polinom
{
public:

	static const int limit = 8; // Dökümanda belirtildiği üzere.

	Polinom()
	{
		for (int t = 0; t < limit; ++t)
		{
			katsayilar[t] = 0;
			kuvvetler[t] = 0;
		}
		terimSayisi = 0;
		polinomAdi = "";
	}

	Polinom(string ad, int terimSayi, int katsayi[], int kuvvet[]);

	Polinom operator + (const Polinom& pol)
	{
		Polinom sonuc;

		if (terimSayisi >= pol.terimSayisi)
		{
			int fark = terimSayisi - pol.terimSayisi;
			sonuc.terimSayisi = terimSayisi;

			for (int i = 0; i < fark; i++)
			{
				sonuc.katsayilar[i] = katsayilar[i];
			}

			for (int i = 0; i <= pol.terimSayisi; i++)
			{
				sonuc.katsayilar[i + fark] = katsayilar[i + fark] + pol.katsayilar[i];

			}

			for (int i = 0; i <= terimSayisi; i++)
			{
				sonuc.kuvvetler[i] = kuvvetler[i];
			}
		}
		else
		{
			int fark = pol.terimSayisi - terimSayisi;
			sonuc.terimSayisi = pol.terimSayisi;

			for (int i = 0; i < fark; i++)
			{
				sonuc.katsayilar[i] = pol.katsayilar[i];
			}

			for (int i = 0; i <= terimSayisi; i++)
			{
				sonuc.katsayilar[i + fark] = pol.katsayilar[i + fark] + katsayilar[i];

			}

			for (int i = 0; i <= pol.terimSayisi; i++)
			{
				sonuc.kuvvetler[i] = pol.kuvvetler[i];
			}
		}

		return sonuc;
	}

	Polinom operator - (const Polinom& pol)
	{
		Polinom sonuc;

		if (terimSayisi >= pol.terimSayisi)
		{
			int fark = terimSayisi - pol.terimSayisi;
			sonuc.terimSayisi = terimSayisi;

			for (int i = 0; i < fark; i++)
			{
				sonuc.katsayilar[i] = katsayilar[i];
			}

			for (int i = 0; i <= pol.terimSayisi; i++)
			{
				sonuc.katsayilar[i + fark] = katsayilar[i + fark] - pol.katsayilar[i];

			}

			for (int i = 0; i <= terimSayisi; i++)
			{
				sonuc.kuvvetler[i] = kuvvetler[i];
			}
		}
		else
		{
			int fark = pol.terimSayisi - terimSayisi;
			sonuc.terimSayisi = pol.terimSayisi;

			for (int i = 0; i < fark; i++)
			{
				sonuc.katsayilar[i] = pol.katsayilar[i];
			}

			for (int i = 0; i <= terimSayisi; i++)
			{
				sonuc.katsayilar[i + fark] = pol.katsayilar[i + fark] - katsayilar[i];

			}

			for (int i = 0; i <= pol.terimSayisi; i++)
			{
				sonuc.kuvvetler[i] = pol.kuvvetler[i];
			}
		}

		return sonuc;

	}

	int operator + (int sayi)
	{


		int toplam = 0;

		for (int i = 0; i < limit; i++)
		{
			toplam += katsayilar[i];
		}

		toplam += sayi;

		return toplam;
	}

	Polinom operator ++ (int)
	{
		Polinom sonuc;

		sonuc = *this;

		sonuc.katsayilar[terimSayisi] = katsayilar[terimSayisi] += 1;

		return sonuc;

	}

	Polinom& operator += (const Polinom& r)
	{
		*this = *this + r;
		return *this;
	}

	void operator == (const Polinom& pol)
	{
		if (terimSayisi == pol.terimSayisi)
			cout << "Dereceleri esit." << endl;
		else
			cout << "Dereceleri esit degildir." << endl;
	}

	void DosyaOku(Polinom dizi[])
	{

		string satir = "";
		ifstream dosya;
		dosya.open("polinom.txt");

		if (dosya.is_open())
		{
			for (int i = 0; i < 10; i++)
			{

				dosya >> satir;
				dosya.get();
				getline(dosya, satir);


				for (int j = 0; j < dizi[i].terimSayisi + 1; j++)
				{
					dizi[i].katsayilar[j] = stoi(satir.substr(0, satir.find(',')));
					satir = satir.substr(satir.find(',') + 1);

					dizi[i].kuvvetler[j] = dizi[i].terimSayisi - j;
				}
			}
		}
		dosya.close();
	}

	void terimSay(Polinom dizi[])
	{
		string satir = "";
		ifstream dosya;
		dosya.open("polinom.txt");

		if (dosya.is_open())
		{

			for (int i = 0; i < 10; i++)
			{
				dosya >> dizi[i].polinomAdi;
				dosya.get();
				getline(dosya, satir);

				int terimSayi = 0;

				for (int j = 0; j < satir.length(); j++)
				{
					if (satir[j] == ',')
						terimSayi++;
				}

				dizi[i].terimSayisi = terimSayi;

			}
		}
		dosya.close();
	}

	void print()
	{

		for (int i = 0; i < terimSayisi + 1; i++)
		{
			if (katsayilar[i] == 0)
				continue;

			cout << katsayilar[i];

			if (kuvvetler[i] > 1)
				cout << "x^" << kuvvetler[i] << " ";
			else if (kuvvetler[i] == 1)
				cout << "x ";
			else
			{

			}

			if (katsayilar[i + 1] > 0)
				cout << "+ ";
		}
		cout << endl;

		cout << "==============================================" << endl;
		cout << endl;
	}

	void printText(Polinom sonuc)
	{
		ofstream dosya;
		dosya.open("sonuc.txt");

		if (dosya.is_open())
		{
			for (int i = 0; i <= terimSayisi; i++)
			{
				dosya << katsayilar[i] << "x^" << terimSayisi - i << " ";
			}
		}
	}

	int derece()
	{
		int elemanSayisi = 0;

		for (int i = limit - 1; i >= 0; i--)
		{
			if (katsayilar[i] == 0)
			{

			}
			else
				return i;
		}
	}

	bool pol_Derece(Polinom veri1, Polinom veri2)
	{
		if (veri1.derece() == veri2.derece())
			return true;
		else
			return false;
	}


private:
	string polinomAdi = "";
	int terimSayisi;
	int katsayilar[limit];
	int kuvvetler[limit];

};

int main()
{
	Polinom pol[10];
	pol->terimSay(pol);
	pol->DosyaOku(pol);

	int scalarSonuc = 0;
	Polinom sonuc1, sonuc2, sonuc3, sonuc4;

	sonuc1 = pol[0] + pol[5];

	cout << "Sonuc1 : ";
	sonuc1.print();

	cout << "Sonuc2 : ";
	scalarSonuc = pol[9] + 18;

	cout << scalarSonuc << endl;
	cout << endl;

	pol[2]++;

	pol[3] += pol[7];

	sonuc3 = pol[6] - pol[3];

	cout << "Sonuc3 : ";
	sonuc3.print();

	pol[2] == pol[9];
	cout << endl;

	pol[6] == pol[7];
	cout << endl;

	sonuc4 = pol[3] - pol[9] + pol[5];

	sonuc4.printText(sonuc4);

	cout << "========= Tüm Polinomlar ========" << endl << endl;

	for (int i = 0; i < 10; i++)
	{
		pol[i].print();
	}

	return 0;
}
