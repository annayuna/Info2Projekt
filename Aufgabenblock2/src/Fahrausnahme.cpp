/*
 * Fahrausnahme.cpp
 *
 *  Created on: 03.12.2024
 *      Author: annaroessel
 */

#include "Fahrausnahme.h"

Fahrausnahme::Fahrausnahme(Weg& aWeg, const Fahrzeug& aFzg) :
		p_pWeg(aWeg), p_pFahrzeug(aFzg)
{
}

Fahrausnahme::~Fahrausnahme()
{
}
