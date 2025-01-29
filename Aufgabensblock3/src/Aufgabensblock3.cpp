//============================================================================
// Name        : Aufgabenblock1.cpp
// Author      : anna
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"
#include "Kreuzung.h"
#include <memory>
#include <vector>
#include <iomanip>
#include <random>


double dGlobaleZeit = 0.0;

// Ueberladung des "<<" Operators fuer Klasse Fahrzeug
std::ostream& operator<<(std::ostream& out, Simulationsobjekt& simObj)
{
	simObj.vAusgeben(out);
	return out;
}

// gibt alle Fahrzeug in einem vector aus
void vFahrzeugListeAusgeben(std::vector<std::unique_ptr<Fahrzeug>>& tFahrzeuge)
{
	std::cout << std::endl;
	Fahrzeug::vKopf();
	for (const auto& fahrzeug : tFahrzeuge) //ref, weil unique ptr
	{
		std::cout << *fahrzeug << std::endl;
	}
	std::cout << std::endl;
}

// simuliert alle Fahrzeug in einem vector
void vFahrzeugListeSimulieren(std::vector<std::unique_ptr<Fahrzeug>>& tFahrzeuge)
{
	for (const auto& fahrzeug : tFahrzeuge)
	{
		fahrzeug->vSimulieren();
	}
}

void vFahrzeugListeTanken(std::vector<std::unique_ptr<Fahrzeug>>& tFahrzeuge)
{
	for (const auto& fahrzeug : tFahrzeuge)
	{
		fahrzeug->dTanken();
	}
}

void vAufgabe_1(){

	std::cout << "##################" << std::endl;
	std::cout << "## vAufgabe_1() ##" << std::endl;
	std::cout << "##################" << std::endl << std::endl;

	// Erzeugung von Fahrzeugen auf Stack
	Fahrzeug tFahrzeugA;
	Fahrzeug tFahrzeugB;
	Fahrzeug tFahrzeugC;
	std::cout << std::endl;
	// Erzeugung von Fahrzeugen auf Heap
	Fahrzeug* pFahrzeugD = new Fahrzeug();
	Fahrzeug* pFahrzeugE = new Fahrzeug("FahrzeugE");
	std::cout << std::endl;
	// Löschung von Fahrzeugen auf Heap
	delete pFahrzeugD;
	delete pFahrzeugE;
	std::cout << std::endl;

	// Nutzung von Smartpointern
	std::unique_ptr<Fahrzeug> pFahrzeugF = std::make_unique<Fahrzeug>();
	std::unique_ptr<Fahrzeug> pFahrzeugG = std::make_unique<Fahrzeug>("FahrzeugG");
	std::shared_ptr<Fahrzeug> pFahrzeugH = std::make_shared<Fahrzeug>();
	std::shared_ptr<Fahrzeug> pFahrzeugI = std::make_shared<Fahrzeug>("FahrzeugI");
	std::cout << "FahrzeugI use_count: " << pFahrzeugI.use_count() << std::endl; // use_count = 1
	std::shared_ptr<Fahrzeug> pFahrzeugJ = pFahrzeugI;
	std::cout << "FahrzeugI use_count: " << pFahrzeugI.use_count() << std::endl << std::endl; // use_count = 2

	std::vector<std::unique_ptr<Fahrzeug>> fahrzeugUniqueListe;
	fahrzeugUniqueListe.push_back(std::move(pFahrzeugF));
	fahrzeugUniqueListe.push_back(std::move(pFahrzeugG));
	// nur unique Pointer können im Vektor gespeichert werden
	fahrzeugUniqueListe.clear();
	// Fahrzeug deren unique Pointer im Vektor waren wurden hier gelöscht

	std::vector<std::shared_ptr<Fahrzeug>> fahrzeugSharedListe;
	std::cout << "FahrzeugH use_count: " << pFahrzeugH.use_count() << "   FahrzeugI use_count: " << pFahrzeugI.use_count() << std::endl;
	// FahrzeugH use_count: 1   FahrzeugI use_count: 2
	fahrzeugSharedListe.push_back(pFahrzeugH);
	fahrzeugSharedListe.push_back(std::move(pFahrzeugI));
	std::cout << "FahrzeugH use_count: " << pFahrzeugH.use_count() << "   FahrzeugI use_count: " << pFahrzeugI.use_count() << std::endl;
	// FahrzeugH use_count: 2   FahrzeugI use_count: 0
	std::cout << std::endl;
	fahrzeugSharedListe.clear();

}

void vAufgabe_1a(){

	std::cout << "###################" << std::endl;
	std::cout << "## vAufgabe_1a() ##" << std::endl;
	std::cout << "###################" << std::endl << std::endl;

	std::unique_ptr<Fahrzeug> pFahrzeugA = std::make_unique<Fahrzeug>("FahrzeugA",80);
	std::unique_ptr<Fahrzeug> pFahrzeugB = std::make_unique<Fahrzeug>("FahrzeugB",-20);
	std::unique_ptr<Fahrzeug> pFahrzeugC = std::make_unique<Fahrzeug>("FahrzeugC",100);

	std::vector<std::unique_ptr<Fahrzeug>> fahrzeugListe;

	fahrzeugListe.push_back(std::move(pFahrzeugA));
	fahrzeugListe.push_back(std::move(pFahrzeugB));
	fahrzeugListe.push_back(std::move(pFahrzeugC));

	dGlobaleZeit = 0.0;

	std::cout << std::endl;

	for (int i = 0; i<10; i++){
		dGlobaleZeit += 0.25;
		std::cout << "Zeit: " << dGlobaleZeit << std::endl;
		vFahrzeugListeSimulieren(fahrzeugListe);
		vFahrzeugListeAusgeben(fahrzeugListe);
	}

}

void vAufgabe_2(){

	std::cout << "##################" << std::endl;
	std::cout << "## vAufgabe_2() ##" << std::endl;
	std::cout << "##################" << std::endl << std::endl;

	// Fahrzeuge erzeugen und in Vector speichern
	std::unique_ptr<Fahrzeug> pPKWA = std::make_unique<PKW>("PKW_A", 120, 10);
	std::unique_ptr<Fahrzeug> pPKWB = std::make_unique<PKW>("PKW_B", 150, 20, 80);
	std::unique_ptr<Fahrzeug> pFahrradA = std::make_unique<Fahrrad>("Fahrrad_A", 20);
	std::unique_ptr<Fahrzeug> pFahrradB = std::make_unique<Fahrrad>("Fahrrad_B", 30);
	std::vector<std::unique_ptr<Fahrzeug>> fahrzeugListe;
	fahrzeugListe.push_back(std::move(pPKWA));
	fahrzeugListe.push_back(std::move(pPKWB));
	fahrzeugListe.push_back(std::move(pFahrradA));
	fahrzeugListe.push_back(std::move(pFahrradB));

	dGlobaleZeit = 0.0;
	vFahrzeugListeAusgeben(fahrzeugListe);
	bool bGetankt = false;
	while(dGlobaleZeit < 9.999) // Schleife für Simulation und Ausgabe
	{
		dGlobaleZeit += 0.5;
		std::cout << "Zeit: " << dGlobaleZeit << std::endl;
		vFahrzeugListeSimulieren(fahrzeugListe);
		if (dGlobaleZeit > 2.999 && bGetankt == false)
		{
			vFahrzeugListeTanken(fahrzeugListe);
			bGetankt = true;
		}
		vFahrzeugListeAusgeben(fahrzeugListe);
	}

	fahrzeugListe.clear();
}

void vAufgabe_3()
{
	std::cout << "##################" << std::endl;
	std::cout << "## vAufgabe_3() ##" << std::endl;
	std::cout << "##################" << std::endl << std::endl;

	std::unique_ptr<Fahrzeug> pPKWA = std::make_unique<PKW>("PKW_A", 120, 5);
	std::unique_ptr<Fahrzeug> pPKWB = std::make_unique<PKW>("PKW_B", 150, 5);
	std::unique_ptr<Fahrzeug> pPKWC = std::make_unique<PKW>("PKW_C", 180, 5);
	std::vector<std::unique_ptr<Fahrzeug>> fahrzeugListe;
	fahrzeugListe.push_back(std::move(pPKWA));
	fahrzeugListe.push_back(std::move(pPKWB));
	fahrzeugListe.push_back(std::move(pPKWC));

	dGlobaleZeit = 0.0;
	dGlobaleZeit += 0.5;
	vFahrzeugListeSimulieren(fahrzeugListe);
	vFahrzeugListeAusgeben(fahrzeugListe);
	// C ist schneller als B, B ist schneller als A

	if (*fahrzeugListe[0] < *fahrzeugListe[1])
	{
		std::cout << "PKW_B ist weiter gefahren als PKW_A." << std::endl;
	}
	else
	{
		std::cout << "PKW_A ist weiter gefahren als PKW_B." << std::endl;
	}

	*fahrzeugListe[0] = *fahrzeugListe[2];
	std::cout << "PKW_A hat Werte von PKW_C bekommen." << std::endl;

	if (*fahrzeugListe[0] < *fahrzeugListe[1])
	{
		std::cout << "PKW_B ist weiter gefahren als PKW_A." << std::endl;
	}
	else
	{
		std::cout << "PKW_A ist weiter gefahren als PKW_B." << std::endl;
	}
	std::cout << std::endl;

	fahrzeugListe.clear();
}

void vAufgabe_4()
{
	std::cout << "##################" << std::endl;
	std::cout << "## vAufgabe_4() ##" << std::endl;
	std::cout << "##################" << std::endl << std::endl;

	Weg Weg1 = Weg();
	Weg Weg2 = Weg("A44", 200, Tempolimit::Autobahn);
	Weg::vKopf();
	std::cout << Weg1 << std::endl;
	std::cout << Weg2 << std::endl << std::endl;
}

void vAufgabe_5()
{
	std::cout << "##################" << std::endl;
	std::cout << "## vAufgabe_5() ##" << std::endl;
	std::cout << "##################" << std::endl << std::endl;

	dGlobaleZeit = 0.0;
	Weg Weg1 = Weg("A44", 200, Tempolimit::Autobahn);
	std::unique_ptr<Fahrzeug> pPKWA = std::make_unique<PKW>("PKW_A", 120, 5);
	std::unique_ptr<Fahrzeug> pPKWB = std::make_unique<PKW>("PKW_B", 150, 5);
	std::unique_ptr<Fahrzeug> pPKWC = std::make_unique<PKW>("PKW_C", 180, 5);
	Weg1.vAnnahme(std::move(pPKWA));
	Weg1.vAnnahme(std::move(pPKWB), 1.5);
	Weg1.vAnnahme(std::move(pPKWC));

	std::cout << std::endl;

	while(dGlobaleZeit < 3 - 1e-10) // Schleife für Simulation und Ausgabe
	{
		dGlobaleZeit += 0.25;
		std::cout << "Zeit: " << dGlobaleZeit << std::endl;
		Weg1.vSimulieren();
		std::cout << std::endl;
		Weg::vKopf();
		std::cout << Weg1 << std::endl << std::endl;
	}
}

void vAufgabe_6()
{
	std::cout << "##################" << std::endl;
	std::cout << "## vAufgabe_6() ##" << std::endl;
	std::cout << "##################" << std::endl << std::endl;

	dGlobaleZeit = 0.0;
	Weg Weg1 = Weg("A44", 500, Tempolimit::Autobahn);
	Weg Weg2 = Weg("Feldweg", 500, Tempolimit::Innerorts);
	std::unique_ptr<Fahrzeug> pPKWA = std::make_unique<PKW>("PKW_A", 220, 5);
	std::unique_ptr<Fahrzeug> pPKWB = std::make_unique<PKW>("PKW_B", 150, 5);
	std::unique_ptr<Fahrzeug> pPKWC = std::make_unique<PKW>("PKW_C", 180, 5);
	std::unique_ptr<Fahrzeug> pFahrradA = std::make_unique<Fahrrad>("Fahrrad_A", 20);
	std::unique_ptr<Fahrzeug> pFahrradB = std::make_unique<Fahrrad>("Fahrrad_B", 15);
	Weg1.vAnnahme(std::move(pPKWA));
	Weg1.vAnnahme(std::move(pPKWB), 3);
	Weg1.vAnnahme(std::move(pFahrradA), 1);
	Weg2.vAnnahme(std::move(pPKWC));
	Weg2.vAnnahme(std::move(pFahrradB));

	std::cout << std::endl;

	bInitialisiereGrafik(800, 500);
	int feld[] = { 100 , 200 , 300 , 400 };
	int anzahl = 2;
	bZeichneStrasse("A44", "Feldweg", 500, anzahl, feld);

	bool bPKWDhinzugefuegt = false;
		while(dGlobaleZeit < 42 - 1e-6) // Schleife für Simulation und Ausgabe
		{
			dGlobaleZeit += 0.5;
			std::cout << "Zeit: " << dGlobaleZeit << std::endl;

			// Neuen PKW hinzufügen
			if (dGlobaleZeit > 20 - 1e-6 && bPKWDhinzugefuegt == false)
			{
				std::unique_ptr<Fahrzeug> pPKWD = std::make_unique<PKW>("PKW_D", 200, 5);
				Weg1.vAnnahme(std::move(pPKWD), 6);
				bPKWDhinzugefuegt = true;
			}

			vSetzeZeit(dGlobaleZeit);
			Weg1.vSimulieren();
			Weg1.vZeichnen();
			Weg2.vSimulieren();
			Weg2.vZeichnen();
			std::cout << std::endl;
			Weg::vKopf();
			std::cout << Weg1 << std::endl;
			std::cout << Weg2 << std::endl << std::endl;
		}

		vBeendeGrafik();
		vSleep(500);

		//std::cin.get();

}


void vAufgabe_6a()
{
	std::cout << "###################" << std::endl;
	std::cout << "## vAufgabe_6a() ##" << std::endl;
	std::cout << "###################" << std::endl << std::endl;

	vertagt::VListe<std::unique_ptr<int>> iZufallszahlen;

	// Liste mit Zufallszahlen füllen
	for (int i=0; i<10; i++)
	{
		static std::mt19937 device(0);
		std::uniform_int_distribution<int> dist(1, 10);
		iZufallszahlen.push_back(std::make_unique<int>(dist(device)));
	}
	iZufallszahlen.vAktualisieren();

	std::cout << "Liste ausgeben:" << std::endl;
	for (auto& pZahl : iZufallszahlen)
	{
		std::cout << std::setw(4) << *pZahl;
	}
	std::cout << std::endl;

	std::cout << std::endl << "Zahlen >5 werden gelöscht" << std::endl << std::endl;
	for (vertagt::VListe<std::unique_ptr<int>>::iterator it = iZufallszahlen.begin();it != iZufallszahlen.end();it++)
	{
		if (**it > 5)
		{
			iZufallszahlen.erase(it);
		}
	}

	std::cout << "Liste ausgeben (Zahlen wurden noch nicht gelöscht, da noch nicht aktualisiert):" << std::endl;
	for (auto& pZahl : iZufallszahlen)
	{
		std::cout << std::setw(4) << *pZahl;
	}
	std::cout << std::endl;

	std::cout << std::endl << "Liste wird aktualisiert" << std::endl << std::endl;
	iZufallszahlen.vAktualisieren();

	std::cout << "Liste ausgeben (jetzt wurden Zahlen >5 tatsächlich gelöscht):" << std::endl;
	for (auto& pZahl : iZufallszahlen)
	{
		std::cout << std::setw(4) << *pZahl;
	}
	std::cout << std::endl;
}

void vAufgabe_7()
{
	std::cout << "##################" << std::endl;
	std::cout << "## vAufgabe_7() ##" << std::endl;
	std::cout << "##################" << std::endl << std::endl;

	bInitialisiereGrafik(1000, 700);

	// Kreuzungen erzeugen
	std::shared_ptr<Kreuzung> kr_1 = std::make_shared<Kreuzung>("Kr1", 0);
	std::shared_ptr<Kreuzung> kr_2 = std::make_shared<Kreuzung>("Kr2", 1000);
	std::shared_ptr<Kreuzung> kr_3 = std::make_shared<Kreuzung>("Kr3", 0);
	std::shared_ptr<Kreuzung> kr_4 = std::make_shared<Kreuzung>("Kr4", 0);

	// Kreuzungen zeichnen
	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	// Wege erzeugen
	Kreuzung::vVerbinde(kr_1, kr_2, 40, "W12", "W21", Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde(kr_2, kr_3, 115, "W23a", "W32a", Tempolimit::Autobahn, false);
	Kreuzung::vVerbinde(kr_2, kr_3, 40, "W23b", "W32b", Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde(kr_2, kr_4, 55, "W24", "W42", Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde(kr_3, kr_4, 85, "W34", "W43", Tempolimit::Autobahn, false);
	Kreuzung::vVerbinde(kr_4, kr_4, 130, "W44a", "W44b", Tempolimit::Landstrasse, false);

	// Wegkoordinaten setzen
	int iStrasse1Korrdinaten[4] = { 680,40,680,300 };
	int iStrasse2Korrdinaten[12] = { 680,300,850,300,970,390,970,500,850,570,680,570 };
	int iStrasse3Korrdinaten[4] = { 680,300,680,570 };
	int iStrasse4Korrdinaten[4] = { 680,300,320,300 };
	int iStrasse5Korrdinaten[10] = { 680,570,500,570,350,510,320,420,320,300 };
	int iStrasse6Korrdinaten[14] = { 320,300,170,300,70,250,80,90,200,60,320,150,320,300 };

	// Wege zeichnen
	bZeichneStrasse("W12", "W21", 40, 2,iStrasse1Korrdinaten);
	bZeichneStrasse("W23a", "W32a", 115, 6, iStrasse2Korrdinaten);
	bZeichneStrasse("W23b", "W32b", 40, 2, iStrasse3Korrdinaten);
	bZeichneStrasse("W24", "W42", 55, 2, iStrasse4Korrdinaten);
	bZeichneStrasse("W34", "W43", 85, 5, iStrasse5Korrdinaten);
	bZeichneStrasse("W44a", "W44b", 130, 7, iStrasse6Korrdinaten);

	// Fahrzeuge erzeugen
	std::unique_ptr<Fahrzeug> PKW1 = std::make_unique<PKW>("PKW1", 150, 11);
	std::unique_ptr<Fahrzeug> PKW2 = std::make_unique<PKW>("PKW2", 120, 12, 45.0);
	std::unique_ptr<Fahrzeug> PKW3 = std::make_unique<PKW>("PKW3", 80, 13, 100.0);
	std::unique_ptr<Fahrzeug> Fahrrad1 = std::make_unique<Fahrrad>("Fahrrad1", 30);
	std::unique_ptr<Fahrzeug> Fahrrad2 = std::make_unique<Fahrrad>("Fahrrad2", 20);
	std::unique_ptr<Fahrzeug> Fahrrad3 = std::make_unique<Fahrrad>("Fahrrad3", 12);

	// Fahrzeuge auf Kreuzung 1 setzen
	kr_1->vAnnahme(std::move(PKW1),0.0);
	kr_1->vAnnahme(std::move(PKW2),0.25);
	kr_1->vAnnahme(std::move(PKW3),0.5);
	kr_1->vAnnahme(std::move(Fahrrad1),1.8);
	kr_1->vAnnahme(std::move(Fahrrad2),1.9);
	kr_1->vAnnahme(std::move(Fahrrad3),2.0);

	// Simulieren
	for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += 0.25)
	{
		std::cout << "Zeit: " << dGlobaleZeit << std::endl;
		vSetzeZeit(dGlobaleZeit);
		kr_1->vSimulieren();
		kr_2->vSimulieren();
		kr_3->vSimulieren();
		kr_4->vSimulieren();
	}

	//cin.get();
	vBeendeGrafik();
	//vSleep(500);
	//cin.get();
}

void vAufgabenblock1(){
	std::cout << std::endl << "     ------  Aufgabenblock 1  ------" << std::endl << std::endl << std::endl << std::endl;

	vAufgabe_1();
	std::cout << std::endl << std::endl << std::endl;
	vAufgabe_1a();
	std::cout << std::endl << std::endl << std::endl;
	vAufgabe_2();
	std::cout << std::endl << std::endl << std::endl;
	vAufgabe_3();
	std::cout << std::endl << std::endl << std::endl;
}

void vAufgabenblock2(){
	std::cout << std::endl << "     ------  Aufgabenblock 2  ------" << std::endl << std::endl << std::endl << std::endl;

	vAufgabe_4();
	std::cout << std::endl << std::endl << std::endl;
	vAufgabe_5();
	std::cout << std::endl << std::endl << std::endl;
	vAufgabe_6();
	std::cout << std::endl << std::endl << std::endl;
	vAufgabe_6a();
	std::cout << std::endl << std::endl << std::endl;
}

void vAufgabenblock3()
{
	std::cout << std::endl << "     ------  Aufgabenblock 3  ------" << std::endl << std::endl << std::endl << std::endl;
	vAufgabe_7();
	/*std::cout << std::endl << std::endl << std::endl;
	vAufgabe_8();
	std::cout << std::endl << std::endl << std::endl;
	vAufgabe_9();
	std::cout << std::endl << std::endl << std::endl;
	vAufgabe_9a();*/
}

int main() {

	//vAufgabenblock1();
	//vAufgabenblock2();
	vAufgabenblock3();
	return 0;
}
