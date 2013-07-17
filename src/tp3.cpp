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

		if(SHOW_DEBUG_MESSAGES) cout << "Test Empresas Vacias" << endl;
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

		if(SHOW_DEBUG_MESSAGES) cout << "Test Hago alianza (UOM,UOCRA) y chequeo Sistema Laboral(cantidadGruposDeAliados) e imprimo los aliados de cada gremio" << endl;
	d.aliar("UOM", "UOCRA");
	ASSERT_EQ(d.obtenerCantidadGruposDeAliados(), 3);
	cout << "Aliados de UOCRA " << d.aliados("UOCRA") << endl;
	cout << "Aliados de UOM " << d.aliados("UOM") << endl;
	cout << "Aliados de AGD " << d.aliados("AGD") << endl;
	cout << "Aliados de CGT " << d.aliados("CGT") << endl;

		if(SHOW_DEBUG_MESSAGES) cout << "Test Hago alianza (UOCRA, CGT) y chequeo Sistema Laboral(cantidadGruposDeAliados) e imprimo los aliados de cada gremio(chequear simetria y transitividad)" << endl;
	d.aliar("CGT", "UOCRA");
	ASSERT_EQ(d.obtenerCantidadGruposDeAliados(), 2);
	cout << "Aliados de UOCRA " << d.aliados("UOCRA") << endl;
	cout << "Aliados de UOM " << d.aliados("UOM") << endl;
	cout << "Aliados de AGD " << d.aliados("AGD") << endl;
	cout << "Aliados de CGT " << d.aliados("CGT") << endl;

		if(SHOW_DEBUG_MESSAGES) cout << "Test Hago alianza (AGD, CGT) y chequeo Sistema Laboral(cantidadGruposDeAliados) e imprimo los aliados de cada gremio(chequear simetria y transitividad)" << endl;
	d.aliar("AGD", "CGT");
	ASSERT_EQ(d.obtenerCantidadGruposDeAliados(), 1);
	cout << "Aliados de UOCRA " << d.aliados("UOCRA") << endl;
	cout << "Aliados de UOM " << d.aliados("UOM") << endl;
	cout << "Aliados de AGD " << d.aliados("AGD") << endl;
	cout << "Aliados de CGT " << d.aliados("CGT") << endl;
}

void inicializarMuchosGremiosYAliarVarios(Driver& d) {
	d.agregarGremio("Gremio1", 1000);
	d.agregarGremio("Gremio2", 2000);
	d.agregarGremio("Gremio3", 3000);
	d.agregarGremio("Gremio4", 4000);
	d.agregarGremio("Gremio5", 5000);
	d.agregarGremio("Gremio6", 6000);
	d.agregarGremio("Gremio7", 7000);
	d.agregarGremio("Gremio8", 8000);
	d.agregarGremio("Gremio9", 9000);
	d.agregarGremio("Gremio10", 10000);
	d.agregarGremio("Gremio11", 11000);
	d.agregarGremio("Gremio12", 12000);
	d.aliar("Gremio1", "Gremio2");
	d.aliar("Gremio3", "Gremio4");
	d.aliar("Gremio4", "Gremio5");
	d.aliar("Gremio7", "Gremio8");
	d.aliar("Gremio9", "Gremio10");
	d.aliar("Gremio11", "Gremio12");
}

//--- otros test

void testAlianzasViolentas()
{
	Driver d;
	inicializarMuchosGremiosYAliarVarios(d);
	ASSERT_EQ(d.aliados("Gremio1").Cardinal(), 1);
	ASSERT_EQ(d.aliados("Gremio3").Cardinal(), 2);
	ASSERT_EQ(d.aliados("Gremio6").Cardinal(), 0);
	ASSERT_EQ(d.gremios().Cardinal(), 12);
}

void nuestroTestAcuerdosYReAbrir()
{
	Driver d;
	inicializarMuchosGremiosYAliarVarios(d);
	d.iniciar();
	d.abrirParitaria("Gremio6", 60, 69);
	ASSERT_EQ(d.piso("Gremio6"), 60);
	ASSERT_EQ(d.tope("Gremio6"), 69);
	d.abrirParitaria("Gremio1", 10, 19);
	d.abrirParitaria("Gremio3", 30, 39);
	d.abrirParitaria("Gremio4", 40, 49);
	d.abrirParitaria("Gremio5", 50, 59);
	d.abrirParitaria("Gremio7", 70, 79);
	d.abrirParitaria("Gremio8", 80, 89);
	ASSERT_EQ(d.paritarias().Cardinal(),7);
	d.cerrarAcuerdo("Gremio7", 72);
	d.cerrarAcuerdo("Gremio8", 82);
	d.cerrarAcuerdo("Gremio6", 65);
	d.abrirParitaria("Gremio6", 61, 68);
	d.cerrarAcuerdo("Gremio6", 66);
	ASSERT_EQ(d.acuerdosPrevios("Gremio6"), 2);
	ASSERT_EQ(d.valor("Gremio6"), 66);
	ASSERT_EQ(d.paritarias().Cardinal(),5);
	ASSERT_EQ(d.acuerdos().Cardinal(), 2);
}

int main()
{
    RUN_TEST(testAliados);
    RUN_TEST(testAcuerdosyReabrir);
    RUN_TEST(testSistemaLaboral);
    RUN_TEST(testAlianzasViolentas);
    RUN_TEST(nuestroTestAcuerdosYReAbrir);
}

