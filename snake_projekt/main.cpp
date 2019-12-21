#include <iostream>
#include <Windows.h>
#include <random>
#include <string>

using namespace std;

int menu_glowne();
void wybierz_predkosc(int &predkosc);
int wybierz_plansze();
void wybierz_rozmiar(int& szerokosc, int& wysokosc);

void ustawienia_okna();

void ustaw_weza(int szer, int wys,int **plansza);
void ustaw_cel(int szer, int wys,bool& ustawiony, int** plansza);
void sterowanie(int& kierunek,bool& koniec);
void ruch_weza(int kierunek);
void sprawdz_weza(int& dlugosc,bool& koniec,bool& ustawiony, int** plansza);
void rysuj2(int szer, int wys, int** plansza);
void rysuj_weza(int dlugosc, int** plansza);
void plansza_1_ramka(int szer, int wys, int** plansza);
void plansza_2_ramka_linie(int szer, int wys, int** plansza);
void clearScreen_nadpisz();
void clearScreen();
//dodac punktacje
//tryb z przyspieszaniem weza
//zapisywanie graczy i wynikow

int waz[1000][2]{};//0=x 1=y
int waz_poprzedni[1000][2]{}; 

int main()
{
	ustawienia_okna();
	
	int wysokosc = 30;//domyslne
	int szerokosc = 30;//domyslne
	int predkosc{ 50 };//domyslne
	int ksztalt_planszy = 1;//domyslne

	while (true)
	{
		int kierunek = 0; // 1-gora 2-dol 3-lewo 4-prawo
		bool koniec_gry = true;
		bool koniec_programu = false;
		bool cel_stawiony = false;
		int dlugosc_weza = 1;

		int wybor = menu_glowne();

		switch (wybor)
		{
		case 1: //graj
		{
			koniec_gry = false;
		}
		break;
		case 2: //zmien poziom trudnosci(predkosci)
		{
			wybierz_predkosc(predkosc);
		}
		break;
		case 3: //zmien rodzaj planszy
		{
			ksztalt_planszy=wybierz_plansze();
		}
		break;
		case 4: //zmien rozmiar planszy
		{
			wybierz_rozmiar(szerokosc, wysokosc);
		}
		break;
		case 9: //zmien rozmiar planszy
		{
			koniec_gry = true;
			koniec_programu = true;
		}
		break;
		default:
			break;
		}
				
		int** plansza = new int* [wysokosc];
		for (int i = 0;i < wysokosc;i++)
		{
			*(plansza + i) = new int[szerokosc] {};
		}
		if(ksztalt_planszy==1) plansza_1_ramka(szerokosc, wysokosc, plansza);
		else if(ksztalt_planszy==2) plansza_2_ramka_linie(szerokosc, wysokosc, plansza);

		//debug
		int licznik = 0;

		ustaw_weza(szerokosc, wysokosc, plansza);
		while (koniec_gry == false)
		{
			rysuj_weza(dlugosc_weza, plansza);
			Sleep(predkosc);
			if (cel_stawiony == false) ustaw_cel(szerokosc, wysokosc, cel_stawiony, plansza);
			rysuj2(szerokosc, wysokosc, plansza);
			sterowanie(kierunek, koniec_gry);
			ruch_weza(kierunek);
			sprawdz_weza(dlugosc_weza, koniec_gry, cel_stawiony, plansza);

			//debug
			licznik++;
			cout << licznik << endl;
		}

		for (int i = 0;i < 1000;i++)
		{
			waz[i][0] = 0;
			waz[i][1] = 0;
			waz_poprzedni[i][0] = 0;
			waz_poprzedni[i][1] = 0;
		}
		for (int i = 0;i < wysokosc;i++)
		{
			delete[] plansza[i];
		}
		delete[] plansza;
		if (koniec_programu==true)break;
	}
}

int menu_glowne()
{
	int menu;
	clearScreen();
	cout << "Snake" << endl;
	cout << "1. GRAJ!" << endl;
	cout << "2. zmien poziom trudnosci" << endl;
	cout << "3. zmien rodzaj planszy" << endl;
	cout << "4. zmien rozmiar planszy" << endl;
	cout << "9. zakoncz gre" << endl;
	do
	{
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		cin >> menu;
	} while (menu != 1 and menu != 2 and menu!=3 and menu != 4 and menu != 9);

	return menu;
}
void wybierz_predkosc(int& predkosc)
{
	int wybor{};
	clearScreen();
	cout << "Dostepne poziomy trudnosci: " << endl << endl;
	cout << "   predkosc     xxxxxxxxxx" << endl << endl;
	cout << "(1)   wolno               " << endl;
	cout << "(2)   normalnie           " << endl;
	cout << "(3)   szybko              " << endl << endl;
	cout << "Wybierz poziom trudnosci: ";
	do
	{
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		cin >> wybor;
	} while (wybor != 1 and wybor != 2 and wybor != 3);
	if (wybor == 1) predkosc = 70;
	else if (wybor == 2) predkosc = 50;
	else if (wybor == 3) predkosc = 30;

}

int wybierz_plansze()
{
	int wybor{};
	clearScreen();
	cout << "Plansza pierwsza(1)"<<endl<<endl;
	cout << "*******"<<endl;
	cout << "*     *" << endl;
	cout << "*     *" << endl;
	cout << "*     *" << endl;
	cout << "*     *" << endl;
	cout << "*     *" << endl;
	cout << "*******" << endl << endl;
	cout << "plansza druga(2)" << endl << endl;
	cout << "*******" << endl;
	cout << "*     *" << endl;
	cout << "*     *" << endl;
	cout << "*** ***" << endl;
	cout << "*     *" << endl;
	cout << "*     *" << endl;
	cout << "*******" << endl << endl;
	cout << "Wybierz plansze: ";
	do
	{
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		cin >> wybor;
	} while (wybor != 1 and wybor != 2);

	return wybor;
}

void wybierz_rozmiar(int& szerokosc, int& wysokosc)
{
	int wybor{};
	clearScreen();
	cout << "Dostepne rozmiary: " << endl << endl;
	cout << "   szerokosc     wysokosc" << endl<<endl;
	cout << "(1)   30            30   " << endl;
	cout << "(2)   50            50   " << endl;
	cout << "(3)   20            50   " << endl << endl;
	cout << "Wybierz rozmiar: ";
	do
	{
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		cin >> wybor;
	} while (wybor != 1 and wybor != 2 and wybor != 3);
	if (wybor == 1)
	{
		szerokosc = 30;
		wysokosc = 30;
	}
	else if (wybor == 2)
	{
		szerokosc = 50;
		wysokosc = 50;
	}
	else if (wybor == 3)
	{
		szerokosc = 20;
		wysokosc = 50;
	}
}

void ustawienia_okna()
{
	SetConsoleTitle("snake game by Marcin Ciszek");

	HWND pulpit = GetDesktopWindow();
	HWND konsola = GetConsoleWindow();
	HANDLE konsola_out = GetStdHandle(STD_OUTPUT_HANDLE);
	RECT rect;
	GetWindowRect(pulpit, &rect);
	//ustawienia czcionki
	CONSOLE_FONT_INFOEX inf_czcionka;
	inf_czcionka.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(konsola_out, TRUE, &inf_czcionka);
	inf_czcionka.nFont = 2;
	inf_czcionka.dwFontSize.X = 8;
	inf_czcionka.dwFontSize.Y = 8;
	inf_czcionka.FontFamily = 48;
	inf_czcionka.FontWeight = 400;
	wcscpy_s(inf_czcionka.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(konsola_out, TRUE, &inf_czcionka);
	//ustawienia pozycji
	COORD rozmiar;
	rozmiar.X = rect.right / inf_czcionka.dwFontSize.X;
	rozmiar.Y = rect.bottom / inf_czcionka.dwFontSize.Y;
	SetConsoleScreenBufferSize(konsola_out, rozmiar);
	MoveWindow(konsola, rect.left, rect.top, rect.right, rect.bottom, TRUE);
	ShowWindow(konsola, SW_MAXIMIZE);
}
// mechanika***********************************************************************************************************
void ustaw_weza(int szer, int wys, int **plansza)
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

void ustaw_cel(int szer, int wys,bool& ustawiony, int** plansza)
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
	else if (GetAsyncKeyState(VK_UP) * 0x1 and kierunek != 2) kierunek = 1;
	else if (GetAsyncKeyState(VK_DOWN) * 0x1 and kierunek != 1) kierunek = 2;
	else if (GetAsyncKeyState(VK_LEFT) * 0x1 and kierunek != 4) kierunek = 3;
	else if (GetAsyncKeyState(VK_RIGHT) * 0x1 and kierunek != 3) kierunek = 4;
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

void sprawdz_weza(int &dlugosc, bool& koniec,bool& ustawiony, int** plansza)
{
	if (plansza[waz[0][1]][waz[0][0]] == 1 or plansza[waz[0][1]][waz[0][0]] == 2) koniec = true;
	else if ((plansza[waz[0][1]][waz[0][0]] == 3))
	{
		dlugosc++;
		ustawiony = false;
	}
}

void rysuj2(int szer, int wys, int** plansza) //wykorzystanie string duzo przyspiesza wypisywnie
{
	string linia;
	clearScreen_nadpisz();
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
}

void rysuj_weza(int dlugosc, int** plansza)
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
	}
	plansza[waz[0][1]][waz[0][0]] = 4; //glowa oznaczona 4
}

void plansza_1_ramka(int szer, int wys, int** plansza)
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

void plansza_2_ramka_linie(int szer, int wys, int** plansza)
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

void clearScreen_nadpisz()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void clearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}