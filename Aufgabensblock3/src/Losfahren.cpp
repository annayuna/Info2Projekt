/*
 * Losfahren.cpp
 *
 *  Created on: 03.12.2024
 *      Author: annaroessel
 */

#include "Losfahren.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include <iostream>

Losfahren::Losfahren(Weg& aWeg, const Fahrzeug& aFzg) :
		Fahrausnahme(aWeg, aFzg)
{
}

Losfahren::~Losfahren()
{
}


void Losfahren::vBearbeiten() const
{
	std::cout << "Exception: Fahrzeug " << p_pFahrzeug.getName() << " auf Weg "
			<< p_pWeg.getName() << " soll losfahren." << std::endl;


	// Fahrzeug wird aus der Fahrzeugliste entfernt und neu als fahrend eingefügt
	// Es wird sichergestellt, dass kein nullptr an den Weg übergeben wird
	std::unique_ptr<Fahrzeug> aFzgTemp = p_pWeg.pAbgabe(p_pFahrzeug);

	if (aFzgTemp != nullptr)
	{
		p_pWeg.vAnnahme(std::move(aFzgTemp)); //wenn wir der vAnnahme keine Zeit übergeben, wird es als fahrendes Auto angenommen
	}
	else
	{
		std::cout << "Nullptr wurde nicht an den Weg übergeben." << std::endl;
	}
}
