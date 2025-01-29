/*
 * Streckenende.cpp
 *
 *  Created on: 03.12.2024
 *      Author: annaroessel
 */

#include "Streckenende.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Kreuzung.h"
#include <iostream>

Streckenende::Streckenende(Weg& aWeg, const Fahrzeug& aFzg) :
		Fahrausnahme(aWeg, aFzg)
{
}

Streckenende::~Streckenende()
{
}


void Streckenende::vBearbeiten() const
{
	std::cout << "Exception: Fahrzeug " << p_pFahrzeug.getName() << " auf Weg "
				<< p_pWeg.getName() << " ist am Wegende." << std::endl;

	// Fahrzeug wird aus der Fahrzeugliste entfernt
	std::unique_ptr<Fahrzeug> aFzgTemp = p_pWeg.pAbgabe(p_pFahrzeug);

	// Falls eine Zielkreuzung existiert, wird dort das Fahrzeug getankt und
	// fahrend auf einen zufälligen Weg gesetzt.
	if (p_pWeg.getZielkreuzung() != nullptr)
	{
		std::shared_ptr<Kreuzung> aKreuzung = p_pWeg.getZielkreuzung();
		aKreuzung->vTanken(aFzgTemp.get());
		std::shared_ptr<Weg> aNeuerWeg = aKreuzung->pZufaelligerWeg(p_pWeg);

		std::cout << std::endl;
		std::cout << "ZEIT     : " << dGlobaleZeit << std::endl;
		std::cout << "KREUZUNG : " << aKreuzung->getName() << ", " << aKreuzung->getTankstelle() << " Liter" << std::endl;
		std::cout << "WECHSEL  : " << p_pWeg.getName() << " → " << aNeuerWeg->getName() << std::endl;
		std::cout << "FAHRZEUG : " << p_pFahrzeug.getName() << std::endl << std::endl;

		aNeuerWeg->vAnnahme(std::move(aFzgTemp), -1e6); // Hier wird das Fzg übergeben
	}

}
