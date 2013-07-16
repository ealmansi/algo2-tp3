#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdlib>

#define		TERMINAR_CON_ERROR(msj)		{ std::cerr << "Error en la función " << __FUNCTION__ << " | " << (msj) << std::endl; std::exit(-1); }

#endif /* UTILS_H */
