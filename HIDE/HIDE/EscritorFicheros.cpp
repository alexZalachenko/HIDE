#include "EscritorFicheros.h"
#include <fstream>
#include <iostream>
#include <cstdlib> 
#include <iomanip>


using namespace std;

EscritorFicheros* EscritorFicheros::ptrInstanciaEscritorFicheros = 0;

EscritorFicheros* EscritorFicheros::dameEscritorFicheros()
{
	if (ptrInstanciaEscritorFicheros == 0)
		ptrInstanciaEscritorFicheros = new EscritorFicheros();
	return ptrInstanciaEscritorFicheros;
}

EscritorFicheros::EscritorFicheros()
{
}

EscritorFicheros::~EscritorFicheros()
{
}

void EscritorFicheros::escribe(std::string p_texto)
{
	ofstream outf("C:\\Users\\Alex\\Desktop\\LogHIDE.txt", ios::app);

	if (!outf)
		exit(1);
	outf << p_texto;
}

void EscritorFicheros::escribenl(std::string p_texto)
{
	ofstream outf("C:\\Users\\Alex\\Desktop\\LogHIDE.txt", ios::app);

	if (!outf)
		exit(1);
	outf << p_texto;
	outf << " \n";
}

void EscritorFicheros::escribe(irr::core::vector3df p_vector)
{
	ofstream outf("C:\\Users\\Alex\\Desktop\\LogHIDE.txt", ios::app);

	if (!outf)
		exit(1);
	outf << std::fixed << std::setprecision(8) << p_vector.X << " " << p_vector.Y << " " << p_vector.Z;

	
}

void EscritorFicheros::escribenl(irr::core::vector3df p_vector)
{
	ofstream outf("C:\\Users\\Alex\\Desktop\\LogHIDE.txt", ios::app);

	if (!outf)
		exit(1);
	outf << std::fixed << std::setprecision(8) << p_vector.X << " " << p_vector.Y << " " << p_vector.Z << endl;


}