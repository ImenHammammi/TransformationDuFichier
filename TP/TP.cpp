#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>

struct Produit {
	std::string id_produit;
	std::string description_produit;
	int prix_produit;
};

std::vector<Produit> LireFichier(std::string inputFile)
    {
	std::ifstream lecteur(inputFile);
	std::string id;
	std::string description;
	std::string prix;
	std::vector<Produit> listProduit;

	while (true) {
		// LECTURE
		std::getline(lecteur, id);
		std::getline(lecteur, description);
		std::getline(lecteur, prix);

		// TRAITEMENT
		id.erase(std::remove(id.begin(), id.end(), ':'), id.end());
		//std::cout << id << std::endl;
		Produit produit;
		produit.id_produit = id;
		produit.prix_produit = std::stoi(prix);
		listProduit.push_back(produit);

		// VÉRIFICATION
		if (lecteur.eof() == true) break;
	}
	lecteur.close();
	return listProduit;
	}

void EcrireFichier(std::string outFile, std::vector<Produit> listProduit)
{
	std::ofstream ecrivain(outFile);
	for (int i = 0; i < listProduit.size(); i++){
		ecrivain << listProduit.at(i).id_produit << " " << listProduit.at(i).prix_produit << std::endl;
	}
	ecrivain.close();
}

int main() {

	std::string inputFile= "infacture.txt";
	std::string outFile = "outfacture.txt";
	std::vector<Produit> listProduit;
	std::ifstream ifile;

	do{
	std::cout << "Saisissez le nom du fichier dentree :" << std::endl;
	std::cin >> inputFile;
	ifile.open(inputFile, std::ifstream::in);
	} while (!ifile.is_open());
	ifile.close();
	
	do{
	std::cout << "Saisissez le nom du fichier de sortie :" << std::endl;
	std::cin >> outFile;
	} while(outFile.substr(outFile.find_last_of(".") + 1) != "txt");

	std::cout << "Lecture du fichier dentree..." << std::endl;
	listProduit = LireFichier(inputFile);

	std::cout << "Ecriture du fichier de sortie..." << std::endl;
	EcrireFichier(outFile, listProduit);
}