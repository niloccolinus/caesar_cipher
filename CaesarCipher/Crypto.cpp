#include <iostream>
#include <string>
#include "Crypto.h"


Crypto::Crypto() {
	c = 'a'; 
}

string Crypto::LireMessage(string fileName) {
	string message = "";
	fichier_in.open(fileName);

	if (fichier_in.fail()) {
		cout << "Erreur a l'ouverture du fichier..." << endl;
	}
	else {
		string line;

		while (fichier_in) {
			std::getline(fichier_in, line);
			message.append(line + "\n"); // on ajoute chaque ligne au message + un saut de ligne
		}
	}
	fichier_in.close();
	return message;
}

void Crypto::Chiffrer(int key) {
	string origine = LireMessage("origine.txt");
	string output = "";


	for (int i = 0; i < origine.length(); i++)
	{
		// v�rifier si la lettre est une lettre alphab�tique...
		if (isalpha(origine[i]))
		{
			c = origine[i];

			if (isupper(c)) {
				// d�caler la lettre :
				// on utilise le code ASCII du caract�re pour effectuer des op�rations arithm�tiques
				// c - 'A' est l'index dans l'alphabet de la lettre � l'index i (ex : 'I' - 'A' = 73 - 65 = 8)
				// on ajoute le d�calage key
				// le modulo 26 permet d'assurer que l'index sera un index valide de l'alphabet
				// ex pour d�caler Z de 3 : (25 + 3) % 26 = 2 ce qui correspond � C
				// on rajoute 'A' pour obtenir le code ASCII de la lettre chiffr�e
				c = ((c - 'A') + key) % 26 + 'A';
			}
			else {
				// m�me chose pour lettres minuscules
				c = ((c - 'a') + key) % 26 + 'a';
			}
			output += c;

		}
		// ...sinon ajouter la lettre telle quelle au message chiffr�
		else
		{
			output += origine[i];
		}
	}

	// enregistrer dans le fichier message.txt
	if (output.length() != 0) {
		fichier_out.open("message.txt");
		if (fichier_out.fail()) {
			cout << "Erreur a l'ouverture du fichier..." << endl;
		}
		else {
			fichier_out << output;
		}
		fichier_out.close();
	}
}

void Crypto::Dechiffrer(int key) {
	string message = LireMessage("message.txt");
	string decodedMsg;

	for (int i = 0; i < message.length(); i++)
	{

		if (isalpha(message[i]))
		{
			c = message[i];

			if (isupper(c)) {
				// algorithme semblable � celui de Chiffrer mais on enl�ve key au lieu de l'ajouter
				int index = ((c - 'A') - key) % 26;
				if (index < 0) index += 26; // ajustement pour les index n�gatifs
				c = index + 'A';
			}
			else {
				int index = ((c - 'a') - key) % 26;
				if (index < 0) index += 26;
				c = index + 'a';
			}

			decodedMsg += c;
		}
		else
		{
			decodedMsg += message[i];
		}
	}

	// imprimer le message d�cod�
	cout << decodedMsg << endl;
}