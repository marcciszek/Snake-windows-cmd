#include <iostream>
#include <Windows.h>
#include <random>
#include <string>

using namespace std;

void ustaw_weza(int szer, int wys);
void ustaw_cel(int szer, int wys,bool& ustawiony);
void sterowanie(int& kierunek,bool& koniec);
void ruch_weza(int kierunek);
void sprawdz_weza(int& dlugosc,bool& koniec,bool& ustawiony);
void rysuj(int szer, int wys);
void rysuj2(int szer, int wys);
void rysuj_weza(int dlugosc);
void plansza_1_ramka(int szer, int wys);
void plansza_2_ramka_linie(int szer, int wys);
void clearScreen();
//zmniejszyc ilosc globalnych
//zrobic menu i ustawic poziomy
//dodac punktacje
//jak trudniejszy tryb waz przyspiesza
//sprawdzic gdzie powinien byc sleep

const int szerokosc = 50;
const int wysokosc = 50;
const int predkosc = 40;

int plansza[wysokosc][szerokosc]{};
int waz[100][2]{};//0=x 1=y
int waz_poprzedni[100][2]{}; 

int main()
{
	int kierunek = 0; // 1-gora 2-dol 3-lewo 4-prawo
	bool koniec_gry = false;
	bool cel_stawiony = false;
	int dlugosc_weza = 1;
	

	//debug
	int licznik = 0;


	plansza_1_ramka(szerokosc, wysokosc);
	//plansza_2_ramka_linie(szerokosc, wysokosc);
	ustaw_weza(szerokosc, wysokosc);
	while (koniec_gry == false)
	{
		rysuj_weza(dlugosc_weza);
		if (cel_stawiony == false) ustaw_cel(szerokosc, wysokosc, cel_stawiony);
		rysuj2(szerokosc, wysokosc);
		sterowanie(kierunek,koniec_gry);
		ruch_weza(kierunek);
		sprawdz_weza(dlugosc_weza, koniec_gry,cel_stawiony);


		//debug
		licznik++;
		cout << licznik;
	}
}

void ustaw_weza(int szer, int wys)
{
	random_device ziarno;
	mt19937 losowa(ziarno());
	uniform_int_distribution<int> zakres_wys(0, wys - 1);
	uniform_int_distribution<int> zakres_szer(0, szer - 1);
	int x = 0;
	int y = 0;
	do
	{
		x = zakres_szer(losowa);
		y = zakres_wys(losowa);
	} while (plansza[y][x] != 0);

	waz[0][0] = x;
	waz[0][1] = y;
	waz_poprzedni[0][0] = x;
	waz_poprzedni[0][1] = y;
}

void ustaw_cel(int szer, int wys,bool& ustawiony)
{
	random_device ziarno;
	mt19937 losowa(ziarno());
	uniform_int_distribution<int> zakres_wys(1, wys - 2);
	uniform_int_distribution<int> zakres_szer(1, szer - 2);
	int x = 0;
	int y = 0;
	do
	{
		x = zakres_szer(losowa);
		y = zakres_wys(losowa);
	} while (plansza[y][x] != 0);
	plansza[y][x] = 3;
	ustawiony = true;
}

void sterowanie(int& kierunek, bool& koniec)
{
	if (GetAsyncKeyState('E') * 0x1) koniec = true;
	if (GetAsyncKeyState(VK_UP) * 0x1 and kierunek != 2) kierunek = 1;
	if (GetAsyncKeyState(VK_DOWN) * 0x1 and kierunek != 1) kierunek = 2;
	if (GetAsyncKeyState(VK_LEFT) * 0x1 and kierunek != 4) kierunek = 3;
	if (GetAsyncKeyState(VK_RIGHT) * 0x1 and kierunek != 3) kierunek = 4;
}

void ruch_weza(int kierunek) // 1-gora 2-dol 3-lewo 4-prawo
{
	if (kierunek == 1)
	{
		waz[0][1]--;
	}
	else if (kierunek == 2)
	{
		waz[0][1]++;
	}
	else if (kierunek == 3)
	{
		waz[0][0]--;
	}
	else if (kierunek == 4)
	{
		waz[0][0]++;
	}
}

void sprawdz_weza(int &dlugosc, bool& koniec,bool& ustawiony)
{
	if (plansza[waz[0][1]][waz[0][0]] == 1 or plansza[waz[0][1]][waz[0][0]] == 2) koniec = true;
	else if ((plansza[waz[0][1]][waz[0][0]] == 3))
	{
		dlugosc++;
		ustawiony = false;
	}
}

void rysuj(int szer, int wys)
{
	clearScreen();
	for (int i = 0;i < wys;i++)
	{
		for (int j = 0;j < szer;j++)
		{
			if (plansza[i][j] == 1) cout << (char)0xDB;
			else if (plansza[i][j] == 4) cout << (char)0x4F;
			else if (plansza[i][j] == 2) cout << (char)0xCF;
			else if (plansza[i][j] == 3) cout << (char)0x24;
			else if (plansza[i][j] == 0)cout << " ";
			else cout << plansza[i][j];
		}
		cout << '\n';
	}
	//Sleep(predkosc);
}

void rysuj2(int szer, int wys) //wykorzystanie string duzo przyspiesza wypisywnie
{
	string linia;
	clearScreen();
	for (int i = 0;i < wys;i++)
	{
		for (int j = 0;j < szer;j++)
		{
			if (plansza[i][j] == 1) linia+=(char)0xDB;
			else if (plansza[i][j] == 4) linia += (char)0x4F;
			else if (plansza[i][j] == 2) linia += (char)0xCF;
			else if (plansza[i][j] == 3) linia += (char)0x24;
			else if (plansza[i][j] == 0) linia += " ";
			else linia += plansza[i][j];
		}
		cout << linia << endl;
		linia.clear();
	}
	//Sleep(predkosc);
}

void rysuj_weza(int dlugosc)
{
	for (int i = 0;i < dlugosc;i++)//kasowanie poprzedniego weza
	{
		if (waz_poprzedni[i][0] != 0) plansza[waz_poprzedni[i][1]][waz_poprzedni[i][0]] = 0; 
	} 
	for (int i = 0;i < dlugosc;i++)//rysowanie aktualnego weza
	{
		plansza[waz[i][1]][waz[i][0]] = 2; //waz oznaczony 2
		waz[i + 1][1] = waz_poprzedni[i][1];
		waz[i + 1][0] = waz_poprzedni[i][0];
		waz_poprzedni[i][1] = waz[i][1];
		waz_poprzedni[i][0] = waz[i][0];
		plansza[waz[0][1]][waz[0][0]] = 4; //glowa oznaczona 4
	}
	Sleep(predkosc);
}

void plansza_1_ramka(int szer, int wys)
{
	for (int i = 0;i < wys;i++)
	{
		for (int j = 0;j < szer;j++)
		{
			if (i == 0) plansza[i][j] = 1;
			else if (i == (wys - 1)) plansza[i][j] = 1;
			else if (j == 0) plansza[i][j] = 1;
			else if (j == (szer - 1)) plansza[i][j] = 1;
		}
	}
}

void plansza_2_ramka_linie(int szer, int wys)
{
	for (int i = 0;i < wys;i++)
	{
		for (int j = 0;j < szer;j++)
		{
			if (i == 0) plansza[i][j] = 1;
			else if (i == (wys - 1)) plansza[i][j] = 1;
			else if (j == 0) plansza[i][j] = 1;
			else if (j == (szer - 1)) plansza[i][j] = 1;
			if (i == wys / 2 and (j < szer / 3 or j >= szer - (szer / 3))) plansza[i][j] = 1;
			else if (i == wys / 4 and (j < szer / 3 or j >= szer - (szer / 3))) plansza[i][j] = 1;
			else if (i == wys-(wys/4) and (j < szer / 3 or j >= szer - (szer / 3))) plansza[i][j] = 1;
		}
	}
}

void clearScreen()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}