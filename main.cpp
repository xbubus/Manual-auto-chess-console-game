#include "GameHandler.h"
#include "vld.h"
int main()

{
	bool playing = true;
	int choice = 0;
	GameHandler* g=new GameHandler();
	try
	{
		g->createProfessionsFactory();
		
	}
	catch (const char* error) // nie mozna otworzyc pliku, uruchamianie programu nie ma sensu
	{
		
		std::cout << error;
		std::cout << "\nExiting...";
		delete g;
		exit(0); //brak wyciekow wszystko wczesniej zostalo usuniete
	}
	while (playing)
	{
		std::cout << "1->Start new game\n2->Exit\n";
		choice =getValidInput <int>();
		switch (choice)
		{
		case 1:
			system("cls");
			g->resetData();
			g->manageGame();
			break;

		case 2:
			playing = false;
			break;
		default:
			std::cout << "Wrong choice, try again\n";
			break;
		}
	}
	delete g;
}



//WAZNE:
//Z zalozenia uzytkownik nie ma dostepu do pliku ze statystykami, nie moze ich edytowac, tzn. ze w skladni pliku nie moze byc bledow.
//Aby wszystko wyswietlalo sie poprawnie nie wolno korzystac z starszej wersji konsoli. Zalaczylbym screena jak powinno wygladac poprawne wyswietlanie, ale
//za duzo by wazylo.
//Opisy co robi¹ postacie znajduja sie w plikach .h
//Gra jest NIE zbalansowana, pewne kompozycje mog¹ okazaæ siê znacznie mocniejsze od innych. Ciezko jest idealnie zbalansowac taka gre bez zadnych danych,na slepo

//ZALOZENIA:
//Gre chcialem napisac tak aby:

//-Dodawanie nowych postaci nie wymaga³o du¿ej ingerencji w kod - wystarczy dodac wpis w pliku ze statystkami, stworzyc klase i specjalna umiejetnosc,
//dodac define dla nazwy i dodac ja do funkcji konwertujacej

//-Mozliwe bylo dodanie bota bez duzej zmiany w kodzie, co mysle,¿e mi siê uda³o i przerobienie tej gry na coœ w stylu Auto Chess, gdzie kupujemy tylko postacie
//i je ustawiamy na planszy a reszte robia boty lub dodanie trybu kampanii vs bot nie jest du¿ym problemem. AI dla Botow mogloby wygladac tak 1.mozesz uzyc 
//superumiejetnosc to ja uzyj, jesli nie to jesli mozesz zaatakowac to zaatakuj najblizsza jednostke, jesli nie to idz w strone najblizszej jednostki, jesli
//nie mozesz isc to czekaj.

//PRZEBIEG:
//Kazdy gracz kupuje sobie jednostki i rozstawia je na planszy
//Gracze wykonuja akcje swoimi jednostkami,co ture zwieksza im sie mana
//Gra konczy sie gdy umra wszystkie jednostki jednego z graczy


//UZYTE TECHNOLOGIE
//-operatory:
// plik Profession.h, operator << do wyswietlania koordynatow postaci

//-zarzadzanie pamiecia:
// klasa GameHandler przechowuje dynamiczne obiekty Profession i ProfessionFactory, klasa ProfessionFactory-ProfessionLibrary

//-polimorfizm
// abstrakcyjna klasa Profession ma czysto virtualn¹ metodê do u¿ycia umiejetnosci specjalnej

//-wyjatki
// blad otwarcia pliku rzuca wyjatek -ProfessionsLibrary

//-szablony
// Profession.h -> szablon do otrzymania od uzytkownika wartosci, uzywam tylko int ale testowalem dla innych zmiennych i dziala
// GameHandler.h -> szablon do usuwania dynamicznej pamieci z wektora

//-kontenery STL
// wszechobecne zastosowanie wektorow, pair do przechowywania koordynatow jednostki, mapa do przechowywania statystyk z pliku

//-stringi/stringstreamy
// kilka zastosowan, najwiecej w ProfessionsLibrary
