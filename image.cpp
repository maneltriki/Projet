#include "image.h"

// Constructeur par defaut
Image ::Image()
{
    _type[0] = 0;
    _type[1] = 0;
    _largeur 0;
    _hauteur = 0;
    _commentaire = "#  ";
    initialiserImage(0);
    initialiserImage(1);
}

// Méthode initialiserImage
void Image::initialiserImage(int num)
{
    for (int i=0; i<HAUTEUR_MAX; i++)
    for (int j=0; j<LARGEUR_MAX; j++)
        _imageIn[i][j] = 0;

    for (int i=0; i<HAUTEUR_MAX; i++)
    for (int j=0; j<LARGEUR_MAX; j++)
        _imageOut[i][j] = 0;
}

// Methode qui affiche image
void Image::afficherInformations()
{
    std::cout << "\t|\t- type = "
              << _type[0] << _type[1] << std::endl;
    std::cout << "\t|\t- hauteur "
              << _hauteur << " lignes" << std::endl;
    std::cout << "\t|\t- largeur = "
              << _largeur << " pixels par ligne" << std::endl;
    std::cout << "\t|\t- nombre de Pixels = "
              << _hauteur * _largeur << std::endl;
}

// Methode qui charge
void Image::load(string fichier)
{
    Image& a;
    int temp;
    std::ifstream ifs;
    ifs.open(fichier, std::ios::in);
    string  inputLine = "";
    // 1e ligne : version
    ifs >> a._type;
    // 2e ligne : width and height
    ifs >> a._largeur >> a._hauteur;;
    // data
    for (int i=0; i<a._hauteur; i++)
    for (int j=0; j<a._largeur; j++)
    {
        ifs >> &temp;
        a._imageIn[i][j] = (unsigned char)temp;
    }
    ifs.close();
}

// Methode qui sauvegarde une image en fichier PGM sur le disque
void Image::sauve(string fichier, const Image& a)
{
    int i, j;

    std::ofstream ofs;
    ofs.open(fichier, std::ios::out);

    ofs >> a._largeur >> a._hauteur;

    for (int i=0; i<_hauteur; i++)
    for (int j=0; j<_largeur; j++)
           ofs << a._imageOut[i][j];

    ofs .close();

}

//fonction inverse pour modifier image
void Image::transfert()
{
    for (int i=0; i<_hauteur; i++)
    for (int j=0; j<_largeur; j++)
        _imageOut[i][j] = _imageIn[i][j];
}

void Image::choixFiltre(string choixFiltre)
{
    if (choixFiltre == "F")
    {
        cout << "\tFlou" << std::endl;
        for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            _filtre[i][j] = 1;
        _coeff = 9;
    }
    else if (choixFiltre == "D")
    {
        cout << "\tDécalage" << std::endl;
        for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            _filtre[i][j] = 0;
        _filtre[0][1] = 1;
        _coeff = 1;
    }
    else if (choixFiltre == "P")
    {
        cout << "\tPrewitt" << std::endl;
        for (int i=0; i<3; i++)
        {
            _filtre[i][0] = -1;
            _filtre[i][1] =  0;
            _filtre[i][2] =  1;
        }
        _coeff = 3;
    }
    else if (choixFiltre == "K")
    {
        std::cout << "\tKirsh" << std::endl;
        _filtre[0][0] = -3; _filtre[0][1] = -3; _filtre[0][2] = 5;
        _filtre[1][0] = -3; _filtre[1][1] =  0; _filtre[1][2] = 5;
        _filtre[2][0] = -3; _filtre[2][1] = -3; _filtre[2][2] = 5;
        _coeff = 15;
    }
    else if (choixFiltre == "Ku")
    {
        std::cout << "\tKuwahara" << std::endl;
        for (int i=0; i<2; i++)
        for (int j=0; j<3; j++)
            _filtre[i][j] = 1;
        for (int i=0; i<3; i++)
        for (int j=3; j<5; j++)
            _filtre[i][j] = 2;
        for (int i=3; i<5; i++)
        for (int j=2; j<5; j++)
            _filtre[i][j] = 3;
        for (int i=2; i<5; i++)
        for (int j=0; j<2; j++)
            _filtre[i][j] = 4;
        _filtre[2][2] = 0;
        _coeff = 60;
    }
    else if (choixFiltre == "SH")
    {
        _filtre[0][0] =  0; _filtre[0][1] = -1; _filtre[0][2] =  0;
        _filtre[1][0] = -1; _filtre[1][1] =  5; _filtre[1][2] = -1;
        _filtre[2][0] =  0; _filtre[2][1] = -1; _filtre[2][2] =  0;
        _coeff = 1;
    }
    else if (choixFiltre == "B")
    {
        for (int i=0; i<5; i++)
        for (int j=0; j<5; j++)
            _filtre[i][j] = 1;
        _coeff = 9;
    }
    else if (choixFiltre == "DD")
    {
        _filtre[0][0] =  1; _filtre[0][1] = 0; _filtre[0][2] = -1;
        _filtre[1][0] =  0; _filtre[1][1] = 0; _filtre[1][2] =  0;
        _filtre[2][0] = -1; _filtre[2][1] = 0; _filtre[2][2] =  1;
        _coeff = 1;
    }
}

void Image::appliquerFiltre()
{
    float coeff_inverse = 1.0f/_coeff;
    for (int ligI=1; ligI<_hauteur-1; ligI++)
    for (int colI=1; colI<_largeur-1; colI++)
    {
        float sommeDeProduit = 0;
        for (int ligF=0; ligF<3; ligF++)
        for (int colF=0; colF<3; colF++)
        {
            float produit = _imageIn[ligI+ligF-1][colI+colF-1]
                          * _filtre[ligF][colF];
            sommeDeProduit += produit;
        }
        sommeDeProduit *= coeff_inverse;
        _imageOut[ligI][colI] = sommeDeProduit;
    }
}
