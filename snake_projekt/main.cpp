#include <iostream>
#include <Windows.h>
#include <random>
#include <string>
#include <limits>

using namespace std;

void petla_gry(int koniec_poziomu, int wysokosc, int szerokosc, int ksztalt_planszy, int predkosc, bool& koniec_gry,int tryb);
void menu_glowne(int& szerokosc, int& wysokosc, int& predkosc, int& ksztalt_planszy, bool& koniec_gry, bool& koniec_programu, int& tryb);
void pkt_wyswietl();
void wybierz_predkosc(int &predkosc);
int wybierz_plansze();
void wybierz_rozmiar(int& szerokosc, int& wysokosc);
void wypisz_informacje();

void ustawienia_okna();

void ustaw_weza(int szer, int wys,int **plansza);
void ustaw_cel(int szer, int wys,bool& ustawiony, int** plansza);
void sterowanie(int& kierunek,bool& koniec);
void ruch_weza(int kierunek);
int sprawdz_weza(int& dlugosc,bool& koniec,bool& ustawiony, int** plansza, int tryb);
void rysuj2(int szer, int wys, int** plansza,int tryb,int zebrano);
void rysuj_weza(int dlugosc, int** plansza);
void plansza_1_ramka(int szer, int wys, int** plansza);
void plansza_2_ramka_linie(int szer, int wys, int** plansza);
void snake_napis();
void clearScreen_nadpisz();
void clearScreen();
void ShowConsoleCursor(bool showFlag);

//wpisany znak po zakonczeniu gry

int waz[2500][2]{};//0=x 1=y
int waz_poprzedni[2500][2]{}; 

int pkt_maks{};
int pkt_ostatnio{};
int pkt_wczesniej{};

int pkt_przygoda_maks{};
int pkt_przygoda_ostatnio{};
int pkt_przygoda_wczesniej{};
int pkt_bonus = 0;

int kroki{};

int main()
{
	ustawienia_okna();
	//domyslne ustawienia
	int wysokosc = 30;
	int szerokosc = 30;
	int predkosc{ 55 };
	int ksztalt_planszy = 1;
	int tryb_gry = 1; //1 normalna, 2 przygoda

	while (true)
	{
		bool koniec_gry = true;
		bool koniec_programu = false;

		menu_glowne(szerokosc, wysokosc, predkosc, ksztalt_planszy, koniec_gry, koniec_programu,tryb_gry);
		
		if (tryb_gry == 1 and koniec_programu == false)
		{
			pkt_ostatnio = 0;
			petla_gry(-1, wysokosc, szerokosc, ksztalt_planszy, predkosc, koniec_gry, tryb_gry);
		}
		else if (tryb_gry == 2 and koniec_programu == false)
		{
			pkt_przygoda_ostatnio = 0;

			if (koniec_gry == false)
			{
				clearScreen();
				cout << endl << endl << "  Poziom 1";
				Sleep(3000);
				petla_gry(20, 50, 50, 1, 55, koniec_gry, tryb_gry);
			}
			if (koniec_gry == false)
			{
				clearScreen();
				cout << endl << endl << "  Poziom 2";
				Sleep(3000);
				pkt_bonus++;
				petla_gry(20, 50, 50, 2, 55, koniec_gry, tryb_gry);
			}
			if (koniec_gry == false)
			{
				clearScreen();
				cout << endl << endl << "  Poziom 3";
				Sleep(3000);
				pkt_bonus++;
				petla_gry(20, 50, 50, 1, 45, koniec_gry, tryb_gry);
			}
			if (koniec_gry == false)
			{
				clearScreen();
				cout << endl << endl << "  Poziom 4";
				Sleep(3000);
				pkt_bonus++;
				petla_gry(20, 50, 50, 2, 45, koniec_gry, tryb_gry);
			}
			if (koniec_gry == false)
			{
				clearScreen();
				cout << endl << endl << "  Poziom 5";
				Sleep(3000);
				pkt_bonus++;
				petla_gry(20, 40, 40, 1, 45, koniec_gry, tryb_gry);
			}
			if (koniec_gry == false)
			{
				clearScreen();
				cout << endl << endl << "  Poziom 6";
				Sleep(3000);
				pkt_bonus++;
				petla_gry(20, 40, 40, 2, 45, koniec_gry, tryb_gry);
			}
			if (koniec_gry == false)
			{
				clearScreen();
				cout << endl << endl << "  Poziom 7";
				Sleep(3000);
				pkt_bonus++;
				petla_gry(15, 40, 40, 1, 40, koniec_gry, tryb_gry);
			}
			if (koniec_gry == false)
			{
				clearScreen();
				cout << endl << endl << "  Poziom 8";
				Sleep(3000);
				pkt_bonus++;
				petla_gry(15, 40, 40, 2, 40, koniec_gry, tryb_gry);
			}
			if (koniec_gry == false)
			{
				clearScreen();
				cout << endl << endl << "  Poziom 9";
				Sleep(3000);
				pkt_bonus++;
				petla_gry(10, 30, 30, 1, 35, koniec_gry, tryb_gry);
			}
			if (koniec_gry == false)
			{
				clearScreen();
				cout << endl << endl << "  Poziom 10";
				Sleep(3000);
				pkt_bonus++;
				petla_gry(10, 30, 30, 2, 35, koniec_gry, tryb_gry);
			}
		}

		if (koniec_programu == true)break;
	}
}

void petla_gry(int koniec_poziomu,int wysokosc,int szerokosc,int ksztalt_planszy,int predkosc,bool& koniec_gry,int tryb)
{
	int kierunek = 0; // 1-gora 2-dol 3-lewo 4-prawo
	int dlugosc_weza = 1;
	bool cel_stawiony = false;
	int zebrano{};
	kroki = 0;


	clearScreen();
	ShowConsoleCursor(false);

	//tworzenie mapy
	int** plansza = new int* [wysokosc];
	for (int i = 0;i < wysokosc;i++)
	{
		*(plansza + i) = new int[szerokosc] {};
	}
	if (ksztalt_planszy == 1) plansza_1_ramka(szerokosc, wysokosc, plansza);
	else if (ksztalt_planszy == 2) plansza_2_ramka_linie(szerokosc, wysokosc, plansza);

	//petla gra
	ustaw_weza(szerokosc, wysokosc, plansza);
	while (koniec_gry == false)
	{
		rysuj_weza(dlugosc_weza, plansza);
		if (cel_stawiony == false) ustaw_cel(szerokosc, wysokosc, cel_stawiony, plansza);
		sterowanie(kierunek, koniec_gry);
		ruch_weza(kierunek);
		zebrano+=sprawdz_weza(dlugosc_weza, koniec_gry, cel_stawiony, plansza, tryb);
		rysuj2(szerokosc, wysokosc, plansza,tryb,zebrano);
		Sleep(predkosc);
		if (kierunek != 0) kroki++;
		if (zebrano == koniec_poziomu) break;
	}
	//sprzatanie
	ShowConsoleCursor(true);
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
}

void menu_glowne(int& szerokosc,int& wysokosc,int& predkosc,int&ksztalt_planszy,bool &koniec_gry,bool& koniec_programu,int& tryb)
{
	int menu{};
	do
	{
	clearScreen();
	snake_napis();
	pkt_wyswietl();
	cout << "  Wpisz odpowiednia cyfre i nacisnij ENTER" << endl << endl;
	cout << "  1. Tryb normalny" << endl;
	cout << "  2. zmien poziom trudnosci" << endl;
	cout << "  3. zmien rodzaj planszy" << endl;
	cout << "  4. zmien rozmiar planszy" << endl;
	cout << "  5. Przygoda" << endl;
	cout << "  8. Informacje" << endl;
	cout << "  9. zakoncz gre" << endl << endl;
	cout << "  Twoj wybor: ";

		cin >> menu;
		cin.clear();
		cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

	} while (menu != 1 and menu != 2 and menu!=3 and menu != 4 and menu!=5 and menu!=8 and menu != 9);
	
	if (menu == 1)
	{
		koniec_gry = false;
		tryb = 1;
	}
	else if (menu == 2) wybierz_predkosc(predkosc);
	else if (menu == 3) ksztalt_planszy = wybierz_plansze();
	else if (menu == 4) wybierz_rozmiar(szerokosc, wysokosc);
	else if (menu == 5)
	{
		koniec_gry = false;
		tryb = 2;
	}
	else if (menu == 8) wypisz_informacje();
	else if (menu == 9) koniec_programu = true;

}

void pkt_wyswietl()
{
	cout << "  Tryb normalny " << endl << endl;
	
	if (pkt_maks < pkt_ostatnio) pkt_maks = pkt_ostatnio;
	cout << "  Najwiecej pkt: " << pkt_maks << endl;
	cout << "  Ostatnie podejscie: " << pkt_ostatnio;
	if (pkt_ostatnio < pkt_wczesniej) cout << " (-" << pkt_wczesniej - pkt_ostatnio <<")"<< endl;
	else cout << " (+" << pkt_ostatnio - pkt_wczesniej << ")" << endl<<endl;
	pkt_wczesniej = pkt_ostatnio;

	cout << endl << "  Tryb przygody " << endl << endl;

	if (pkt_przygoda_maks < pkt_przygoda_ostatnio) pkt_przygoda_maks = pkt_przygoda_ostatnio;
	cout << "  Najwiecej pkt: " << pkt_przygoda_maks << endl;
	cout << "  Ostatnie podejscie: " << pkt_przygoda_ostatnio;
	if (pkt_przygoda_ostatnio < pkt_przygoda_wczesniej) cout << " (-" << pkt_przygoda_wczesniej - pkt_przygoda_ostatnio << ")" << endl;
	else cout << " (+" << pkt_przygoda_ostatnio - pkt_przygoda_wczesniej << ")" << endl << endl;
	pkt_przygoda_wczesniej = pkt_przygoda_ostatnio;
}

void wybierz_predkosc(int& predkosc)
{
	int wybor{};
	do
	{
		clearScreen();
		snake_napis();
		cout << "  Wpisz odpowiednia cyfre i nacisnij ENTER" << endl << endl;
		cout << "  Dostepne poziomy trudnosci: " << endl << endl;
		cout << "       predkosc" << endl << endl;
		cout << "  (1)   wolno               " << endl;
		cout << "  (2)   normalnie           " << endl;
		cout << "  (3)   szybko              " << endl;
		cout << "  (4)   bardzo szybko       " << endl << endl;
		cout << "  Wybierz poziom trudnosci: ";

		cin >> wybor;
		cin.clear();
		cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

	} while (wybor != 1 and wybor != 2 and wybor != 3);
	if (wybor == 1) predkosc = 70;
	else if (wybor == 2) predkosc = 55;
	else if (wybor == 3) predkosc = 40;
	else if (wybor == 4) predkosc = 25;
}

int wybierz_plansze()
{
	int wybor{};
	do
	{
		clearScreen();
		snake_napis();
		cout << "  Wpisz odpowiednia cyfre i nacisnij ENTER" << endl << endl;
		cout << "  Plansza pierwsza(1)" << endl << endl;
		cout << "  *********" << endl;
		cout << "  *       *" << endl;
		cout << "  *       *" << endl;
		cout << "  *       *" << endl;
		cout << "  *       *" << endl;
		cout << "  *       *" << endl;
		cout << "  *       *" << endl;
		cout << "  *       *" << endl;
		cout << "  *********" << endl << endl;
		cout << "  plansza druga(2)" << endl << endl;
		cout << "  *********" << endl;
		cout << "  *       *" << endl;
		cout << "  ***   ***" << endl;
		cout << "  *       *" << endl;
		cout << "  ***   ***" << endl;
		cout << "  *       *" << endl;
		cout << "  ***   ***" << endl;
		cout << "  *       *" << endl;
		cout << "  *********" << endl << endl;
		cout << "  Wybierz plansze: ";
		cin >> wybor;
		cin.clear();
		cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	} while (wybor != 1 and wybor != 2);
	return wybor;
}

void wybierz_rozmiar(int& szerokosc, int& wysokosc)
{
	int wybor{};
	do
	{
		clearScreen();
		snake_napis();
		cout << "  Wpisz odpowiednia cyfre i nacisnij ENTER" << endl << endl;
		cout << "  Dostepne rozmiary: " << endl << endl;
		cout << "     szerokosc     wysokosc" << endl << endl;
		cout << "  (1)   30            30   " << endl;
		cout << "  (2)   40            40   " << endl;
		cout << "  (3)   50            50   " << endl << endl;
		cout << "  Wybierz rozmiar: ";
		cin >> wybor;
		cin.clear();
		cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

	} while (wybor != 1 and wybor != 2 and wybor != 3);
	if (wybor == 1)
	{
		szerokosc = 30;
		wysokosc = 30;
	}
	else if (wybor == 2)
	{
		szerokosc = 40;
		wysokosc = 40;
	}
	else if (wybor == 3)
	{
		szerokosc = 50;
		wysokosc = 50;
	}
}

void wypisz_informacje()
{
	int koniec{};
	do
	{
		clearScreen();
		snake_napis();
		cout << endl << endl;
		cout << "  Sterowanie odbywa sie za pomoca strzalek" << endl << endl;
		cout << "  " <<(char)0x4F << "  To jest glowa Twojego weza" << endl << endl;
		cout << "  " << (char)0xCF << "  To jest element twojego ogona, staraj sie go nie zjesc" << endl << endl;
		cout << "  " << (char)0x24 << "  To sa dolary, kazdy lubi dolary, zbieraj je" << endl << endl;
		cout << endl << "  Wpisz 1 aby powrocic: ";
		cin >> koniec;
		cin.clear();
		cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	} while (koniec != 1);
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
	rozmiar.X = (rect.right / inf_czcionka.dwFontSize.X);
	rozmiar.Y = (rect.bottom / inf_czcionka.dwFontSize.Y);
	SetConsoleScreenBufferSize(konsola_out, rozmiar);
	MoveWindow(konsola, rect.left, rect.top, rect.right, rect.bottom, TRUE);
	ShowWindow(konsola, SW_MAXIMIZE);
}
// ***********************************************************************************************************

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
	//FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	 
	if ((GetAsyncKeyState('E') & 0x8000)) koniec = true;
	else if ((GetAsyncKeyState(VK_UP) & 0x8000) and kierunek != 2) kierunek = 1;
	else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) and kierunek != 1) kierunek = 2;
	else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) and kierunek != 4) kierunek = 3;
	else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) and kierunek != 3) kierunek = 4;
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

int sprawdz_weza(int &dlugosc, bool& koniec,bool& ustawiony, int** plansza, int tryb)
{
	if (plansza[waz[0][1]][waz[0][0]] == 1 or plansza[waz[0][1]][waz[0][0]] == 2) koniec = true;
	else if ((plansza[waz[0][1]][waz[0][0]] == 3))
	{
		dlugosc++;
		ustawiony = false;
		if(tryb==1) pkt_ostatnio+=(1+pkt_bonus);
		else if (tryb == 2) pkt_przygoda_ostatnio += (1 + pkt_bonus);
		return 1;
	}
	return 0;
}

void rysuj2(int szer, int wys, int** plansza,int tryb,int zebrano) //wykorzystanie string duzo przyspiesza wypisywnie
{
	string linia;
	linia += "\n \n";
	for (int i = 0;i < wys;i++)
	{
		linia += "  ";
		for (int j = 0;j < szer;j++)
		{
			if (plansza[i][j] == 1) linia+=(char)0xDB;
			else if (plansza[i][j] == 4) linia += (char)0x4F;
			else if (plansza[i][j] == 2) linia += (char)0xCF;
			else if (plansza[i][j] == 3) linia += (char)0x24;
			else if (plansza[i][j] == 0) linia += " ";
			else linia += plansza[i][j];
		}
		linia += "\n";
	}
	if (tryb == 1)
	{
		linia += "\n  Zebrano: " + to_string(zebrano) + "$";
		linia += "\n  Punkty: " + to_string(pkt_ostatnio);
		linia += "\n  Liczba krokow: "+ to_string(kroki);
	}
	else if (tryb == 2)
	{
		linia += "\n  Zebrano: " + to_string(zebrano) + "$";
		linia += "\n  Punkty: " + to_string(pkt_przygoda_ostatnio);
		linia += "\n  Liczba krokow: " + to_string(kroki);
	}
	clearScreen_nadpisz();
	cout << linia;
	linia.clear();
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

void snake_napis()
{
	cout << endl;
	cout << "   _______  __    _  _______  ___   _  _______" << endl;
	cout << "  |       ||  |  | ||   _   ||   | | ||       |" << endl;
	cout << "  |  _____||   |_| ||  |_|  ||   |_| ||    ___|" << endl;
	cout << "  | |_____ |       ||       ||      _||   |___" << endl;
	cout << "  |_____  ||  _    ||       ||     |_ |    ___|" << endl;
	cout << "   _____| || | |   ||   _   ||    _  ||   |___" << endl;
	cout << "  |_______||_| |__ ||__| |__||___| |_||_______|" << endl;
	cout << endl;
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

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}