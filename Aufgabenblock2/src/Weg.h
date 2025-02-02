/*
 * Weg.h
 *
 *  Created on: 03.12.2024
 *      Author: annaroessel
 */

#ifndef WEG_H_
#define WEG_H_

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "Fahrzeug.h"

#include "vertagt_liste.h"


class Weg : public Simulationsobjekt {
public:
	Weg(const std::string& s = "", const double l = 0, const Tempolimit t = Tempolimit::Autobahn);
	virtual ~Weg();

	virtual void vSimulieren() override;
	double getTempolimit() const;

	static void vKopf();
	virtual void vAusgeben(std::ostream& out) const override;

	void vAnnahme(std::unique_ptr<Fahrzeug> pFzg);
	void vAnnahme(std::unique_ptr<Fahrzeug> pFzg, const double dStartZeit);

	double getLaenge() const;

	void vZeichnen() const;

	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& aFzg);

private:
	const double p_dLaenge = 0;
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	const Tempolimit p_eTempolimit = Tempolimit::Autobahn;


};

#endif /* WEG_H_ */
