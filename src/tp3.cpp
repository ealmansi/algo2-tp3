#include "../include/Driver.h"
#include "../include/aed2_tests.h"

// Auxiliares de testeo

void crearSistema(Driver &d)
{
    d.agregarGremio("UOM", 1000);
    d.agregarGremio("UOCRA", 950);
    d.agregarGremio("AGD", 950);

    d.aliar("UOM", "UOCRA");
    d.aliar("AGD", "UOCRA");
}

void testAliados()
{
    Driver d;
    crearSistema(d);

    ASSERT_EQ(d.aliados("UOCRA").Cardinal(), 2);
    ASSERT_EQ(d.aliados("AGD").Cardinal(), 2);
    ASSERT_EQ(d.aliados("UOM").Cardinal(), 2);
}

void testAcuerdosyReabrir()
{
    Driver d;
    crearSistema(d);

    d.iniciar();

    d.abrirParitaria("AGD", 0, 10);
    d.abrirParitaria("UOM", 1, 11);
    d.cerrarAcuerdo("AGD", 5);
    d.cerrarAcuerdo("UOM", 6);

    ASSERT_EQ(d.acuerdos().Cardinal(), 1);
    ASSERT_EQ(d.paritarias().Cardinal(), 1);
}

void testSistemaLaboral(){
	Driver d;

		if(SHOW_DEBUG_MESSAGES) cout << endl << "test no hay gremios" << endl;
	ASSERT_EQ(d.gremios().Cardinal(), 0);
	d.agregarGremio("UOM", 1000);
		if(SHOW_DEBUG_MESSAGES) cout << "Agrego gremio: UOM" << endl;
	ASSERT_EQ(d.gremios().Cardinal(), 1);
	d.agregarGremio("UOCRA", 900);
		if(SHOW_DEBUG_MESSAGES) cout << "Agrego gremio: UOCRA" << endl;
	ASSERT_EQ(d.gremios().Cardinal(), 2);
	d.agregarGremio("AGD", 800);
		if(SHOW_DEBUG_MESSAGES) cout << "Agrego gremio: AGD" << endl;
	ASSERT_EQ(d.gremios().Cardinal(), 3);
	d.agregarGremio("CGT", 700);
		if(SHOW_DEBUG_MESSAGES) cout << "Agrego gremio: CGT" << endl;
	ASSERT_EQ(d.gremios().Cardinal(), 4);

		if(SHOW_DEBUG_MESSAGES) cout << "Gremios agregados al sistema: " << d.gremios() << endl;

		if(SHOW_DEBUG_MESSAGES) cout << "Test #GrupoAliados " << endl;
	ASSERT_EQ(d.obtenerCantidadGruposDeAliados(), 4);

		if(SHOW_DEBUG_MESSAGES) cout << "Test Todos Sin Aliados" << endl;
	Conj<NombreGremio> gremios = d.gremios();
	Conj<NombreGremio>::const_Iterador itGr = gremios.CrearIt();
	while(itGr.HaySiguiente()){
		ASSERT_EQ(d.aliados(itGr.Siguiente()).Cardinal(), 0);
		itGr.Avanzar();
	}

	/*Conj<NombreGremio>::const_Iterador itGremios = d.gremios().CrearIt();
	while(itGremios.HaySiguiente()){
		cout << itGremios.Siguiente() << endl;
		//ASSERT_EQ(d.aliados(itGremios.Siguiente()).Cardinal(), 0);
		itGremios.Avanzar();
	}*/

		if(SHOW_DEBUG_MESSAGES) cout << "Test Corresponden #afiliados" << endl;
	ASSERT_EQ(d.cantAfiliados("UOM"), 1000);
	ASSERT_EQ(d.cantAfiliados("UOCRA"), 900);
	ASSERT_EQ(d.cantAfiliados("AGD"), 800);
	ASSERT_EQ(d.cantAfiliados("CGT"), 700);

		if(SHOW_DEBUG_MESSAGES) cout << endl << endl << "Test Empresas Vacias" << endl;
	Conj<NombreGremio>::const_Iterador itGr2 = gremios.CrearIt();
	while(itGr2.HaySiguiente()){
		ASSERT_EQ(d.empresas(itGr2.Siguiente()).Cardinal(), 0);
		itGr2.Avanzar();
	}

		if(SHOW_DEBUG_MESSAGES) cout << "Test Agrego 2 Empresas en casos borde (UOM, UOCRA) y veo cardinal 2" << endl;
	Empresa emp1 = "enterprise1";
	d.agregarEmpresa("UOM", emp1);
	Empresa emp2 = "enterprise2";
	d.agregarEmpresa("UOM", emp2);

	Empresa emp3 = "enterprise3";
	d.agregarEmpresa("UOCRA", emp3);
	Empresa emp4 = "enterprise4";
	d.agregarEmpresa("UOCRA", emp4);

	ASSERT_EQ(d.empresas("UOM").Cardinal(), 2);
	ASSERT_EQ(d.empresas("UOCRA").Cardinal(), 2);

	/*d.aliar("UOM", "UOCRA");
	d.aliar("AGD", "UOCRA");

    cout << endl << d.aliados("UOCRA") << endl;
    cout << d.aliados("AGD") << endl;
    cout << d.aliados("UOM") << endl;*/
}

int main()
{
    RUN_TEST(testAliados);
    RUN_TEST(testAcuerdosyReabrir);
    RUN_TEST(testSistemaLaboral);
}

