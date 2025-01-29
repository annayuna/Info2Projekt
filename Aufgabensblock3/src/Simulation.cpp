#include <iostream>

#include "Simulation.h"
#include "Tempolimit.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "SimuClient.h"

/*
extern std::istream& operator>>(std::istream& in, Simulationsobjekt& aFzg);

void Simulation::vKreuzungEinlesen(std::istream& in)
{
	// Kreuzung erstellen
	auto pKreuzung = std::make_shared<Kreuzung>();
	in >> *pKreuzung;

	// prüfen, ob Kreuzung schon existiert. Wenn nein, dann erstellen
	auto it = p_pKreuzungen.find(pKreuzung->getName());
	if (it == p_pKreuzungen.end()) // entspricht "nicht gefunden"
	{
		p_pKreuzungen[pKreuzung->getName()] = pKreuzung;

		if (p_bMitGrafik)
		{
			int iXKorrdinate = 0;
			int iYKorrdinate = 0;
			in >> iXKorrdinate >> iYKorrdinate;
			bZeichneKreuzung(iXKorrdinate, iYKorrdinate);
		}
	}
	else
	{
		throw runtime_error("Eine Kreuzung mit diesem Namen existiert bereits");
	}
}

void Simulation::vStrasseEinlesen(std::istream& in)
{
	std::string sStartKreuzung = "", sZielKreuzung = "", sWeg1 = "", sWeg2 = "";
	double dLaenge = 0;
	int iTempolimit = 0, iUeberholverbot = 1;

	// Wegdaten einlesen
	in >> sStartKreuzung >> sZielKreuzung >> sWeg1 >> sWeg2 >> dLaenge	>> iTempolimit >> iUeberholverbot;

	// Tempolimit und Uberholverbot konvertieren
	Tempolimit eTempolimit = Tempolimit::Autobahn;
	switch (iTempolimit)
	{
	case 1:
		eTempolimit = Tempolimit::Innerorts;
		break;
	case 2:
		eTempolimit = Tempolimit::Landstrasse;
		break;
	case 3:
		eTempolimit = Tempolimit::Autobahn;
		break;
	default:
		throw runtime_error("Das angegebene Tempolimit existiert nicht");
		break;
	}

	bool bUeberholverbot = true;
	switch (iUeberholverbot)
	{
	case 1:
		bUeberholverbot = true;
		break;
	case 0:
		bUeberholverbot = false;
		break;
	default:
		throw runtime_error("Ueberholverbot ist nicht 0 oder 1");
	}

	// Start- und Zielkreuzungspointer finden
	auto itStart = p_pKreuzungen.find(sStartKreuzung);
	if (itStart == p_pKreuzungen.end())
	{
		throw runtime_error("Die Startkreuzung existiert nicht");
	}
	auto itZiel = p_pKreuzungen.find(sZielKreuzung);
	if (itZiel == p_pKreuzungen.end())
	{
		throw runtime_error("Die Zielkreuzung existiert nicht");
	}

	// Wege erzeugen
	Kreuzung::vVerbinde(itStart->second, itZiel->second, dLaenge, sWeg1, sWeg2, eTempolimit, bUeberholverbot);

	// Hier müssen Arrays dynamische erstellt werden, da SimuClient einen Array benötigt, um einen Weg zu zeichnen
	if (p_bMitGrafik)
	{
		int iKoordinatenAnzahl = 0;
		in >> iKoordinatenAnzahl;
		int* iKoordinaten = new int[2*iKoordinatenAnzahl];

		// Koordinaten einlesen
		for (int i = 0; i < 2*iKoordinatenAnzahl; i++)
		{
			int iTemp;
			in >> iTemp;
			iKoordinaten[i] = iTemp;
		}

		bZeichneStrasse(sWeg1, sWeg2, dLaenge, iKoordinatenAnzahl, iKoordinaten);
	}
}

void Simulation::vPKWEinlesen(std::istream& in)
{
	// PKW Daten einlesen
	auto pPKW = std::make_unique<PKW>();
	in >> *pPKW;

	// Kreuzung und Start Daten einlesen
	std::string sStartKreuzung = "";
	double dStartZeit = 0.0;
	in >> sStartKreuzung >> dStartZeit;

	// Kreuzung finden und auf Fehler überprüfen
	auto it = p_pKreuzungen.find(sStartKreuzung);
	if (it == p_pKreuzungen.end())
	{
		throw runtime_error("Die Kreuzung auf die das PKW gesetzt werden soll existiert nicht");
	}
	else
	{
		it->second->vAnnahme(std::move(pPKW), dStartZeit);
	}
}

void Simulation::vFahrradEinlesen(std::istream& in)
{
	// Fahrrad Daten einlesen
	auto pZwischenFahrrad = std::make_unique<Fahrrad>();
	in >> *pZwischenFahrrad;

	// Kreuzung und Start Daten einlesen
	std::string sStartKreuzung = "";
	double dStartZeit = 0.0;
	in >> sStartKreuzung >> dStartZeit;

	// Kreuzung finden und auf Fehler überprüfen
	auto it = p_pKreuzungen.find(sStartKreuzung);
	if (it == p_pKreuzungen.end())
	{
		throw runtime_error("Die Kreuzung auf die das Fahrrad gesetzt werden soll existiert nicht");
	}
	else
	{
		it->second->vAnnahme(std::move(pZwischenFahrrad), dStartZeit);
	}
}



void Simulation::vEinlesen(std::istream& in, bool bMitGrafik)
{
	in.exceptions(ios_base::failbit | ios_base::badbit);

	if (bMitGrafik)
	{
		bInitialisiereGrafik(1100, 1000);
		p_bMitGrafik = bMitGrafik;
	}

	int iFehlerzeile = 0;

	try
	{
		while (!in.eof())
		{
			iFehlerzeile++;

			std::string schluesselwort = "";
			in >> schluesselwort;

			if (schluesselwort == "KREUZUNG") 		{ vKreuzungEinlesen(in); }
			else if (schluesselwort == "STRASSE")	{ vStrasseEinlesen(in); }
			else if (schluesselwort == "PKW")		{ vPKWEinlesen(in); }
			else if (schluesselwort == "FAHRRAD")	{ vFahrradEinlesen(in); }
			else { throw runtime_error("Das Schluesselwort wurde nicht gefunden"); }
		}
	}
	catch (const runtime_error& error)
	{
		std::cout << "Fehler in Zeile " << iFehlerzeile << ": " << error.what() << endl;
		return;
	}
}

void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{
	for (dGlobaleZeit = 0.0; dGlobaleZeit - 1e-6 < dDauer; dGlobaleZeit += dZeitschritt)
	{
		if (p_bMitGrafik)
		{
			vSetzeZeit(dGlobaleZeit);
			std::cout << "Zeit: " << dGlobaleZeit << std::endl;
		}
		// Kreuzungen simulieren
		for (auto& kreuzung : p_pKreuzungen)
		{
			kreuzung.second->vSimulieren();
		}
	}
}*/

