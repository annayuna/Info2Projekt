/*
 * Kreuzung.h
 *
 *  Created on: 25.01.2025
 *      Author: Anna
 */

#ifndef KREUZUNG_H_
#define KREUZUNG_H_

#include <list>
#include <memory>

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "Weg.h"

class Kreuzung: public Simulationsobjekt
{
public:

	virtual ~Kreuzung();

	Kreuzung();
	Kreuzung(const Kreuzung& other);
	Kreuzung(const std::string& sName, const double dTankstelle);

	// Erstellt 2 Wege zwischen 2 Kreuzungen
	static void vVerbinde(std::shared_ptr<Kreuzung> aKreuzungStart, std::shared_ptr<Kreuzung> aKreuzungZiel,
			const double dLaenge, const std::string& sNameHinweg, const std::string& sNameRueckweg,
			const Tempolimit eTempolimit, const bool bUeberholverbot);

	// Tankt Fahrzeuge voll
	void vTanken(Fahrzeug* aFzg);

	// Setzt ein Fahrzeug parkend auf den ersten Weg der Kreuzung
	void vAnnahme(std::unique_ptr<Fahrzeug> pFzg, double dStartzeit);

	// Simuliert alle Wege der Kreuzung
	void vSimulieren() override;

	// Liefert einen zufälligen Weg, der wenn möglich nicht der Rückweg des gegebenen Weges ist
	std::shared_ptr<Weg> pZufaelligerWeg(Weg& aWeg) const;

	// Getter Funktion
	double getTankstelle() const;

	// Einlesefunktion
	//void vEinlesen(std::istream & in) override;

private:

	std::list<std::shared_ptr<Weg>> p_pWege; //Liste mit allen Wegen
	double p_dTankstelle = 0;

};

#endif /* KREUZUNG_H_ */
