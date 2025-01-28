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
	Weg(const std::string& s = "", const double l = 0, const Tempolimit t = Tempolimit::Autobahn, const bool ueberholverbot = true);
	virtual ~Weg();

	virtual void vSimulieren() override;
	double getTempolimit() const;

	static void vKopf();
	virtual void vAusgeben(std::ostream& out) const override;

	void vAnnahme(std::unique_ptr<Fahrzeug> pFzg);
	void vAnnahme(std::unique_ptr<Fahrzeug> pFzg, const double dStartZeit);

	double getLaenge() const;
	bool getUeberholverbot() const;
	std::vector<std::vector<double>> getFzgPositions() const;

	void vZeichnen() const;

	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& aFzg);

	void setRueckweg(const std::shared_ptr<Weg>& rueckweg);

	std::shared_ptr<Kreuzung> getZielkreuzung() const;
	std::shared_ptr<Weg> getRueckweg() const;

private:
	const double p_dLaenge = 0;
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	const Tempolimit p_eTempolimit = Tempolimit::Autobahn;
	const bool p_bUeberholverbot;
	const std::weak_ptr<Kreuzung> p_pZielkreuzung;
	std::weak_ptr<Weg> p_pRueckweg;

};

#endif /* WEG_H_ */
