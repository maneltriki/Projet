#include "image.h"


int main(void)
{
    Image monImage;
    std::string rpd ,Filtre ;

    do {
        std::cout << "c   -> Charger un fichier image"    << std::endl;
        std::cout << "a   -> Afficher proprietes l'image" << std::endl;
        std::cout << "P   -> Afficher matrice image"      << std::endl;
        std::cout << "i   -> Inverser image "             << std::endl;
        std::cout << "s   -> Sauvegarder image"           << std::endl;
        std::cout << "ApF -> Appliquer filtre"            << std::endl;
        std::cout << "q   -> Quitter l'application"       << std::endl;
        std::cin >> rpd;
        std::cout << endl;

        if ( rpd == "c" )
        {
            string fImage = "lena.pgm";
            monImage.load(fImage);}
            else if ( rpd == "a" ) {
                monImage.afficherInformations()
            } else if ( cmde == "i" ) {
                monImage.inverser();
            } else if ( cmde == "s" ) {
                string fDest ="lena.pgm";
                monImage.sauvegarder(fDest, monImage);
            }
        } else if ( cmde == "ApF" ) {
            string message;
            string choixFiltre;
            cout << "\n\t F -> Flou";
            cout << "\n\t D -> Décalage";
            cout << "\n\t P -> Prewitt";
            cout << "\n\t K -> Kirsh";
            cout << "\n\t SH -> sharpen";
            cout << "\n\t B -> blur";
            cout << "\n\t DD -> detection";
            cin >> Filtre;
            monImage.choixFiltre(Filtre);
            monImage.appliquerFiltre();
        }
    } while (cmde != "q");
    return 0;
}
