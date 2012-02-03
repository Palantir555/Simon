#include <htc.h>;		//librería para eeprom_read(adress), eeprom_write(address, data);
#include "delay.c";		//librería de retardos de Hi Tech

#define _XTAL_FREQ 8000000;

__CONFIG(INTIO & UNPROTECT & CCPRB0 & DEBUGDIS & LVPDIS & BORDIS & MCLRDIS & PWRTDIS & WDTDIS & UNPROTECT);
__CONFIG(FCMDIS & IESODIS);


void Rutina_Inicio (void);
void Inicializacion (void);
void CompruebaPulsado (void);
void reproduce_tono(void);
void reproduce_tono_whilePulsado(void);

unsigned char posibilidades[30];	
unsigned char secuenciasPosibles0[30] = {0x04, 0x02, 0x02, 0x04, 0x08, 0x02, 0x04, 0x10, 0x02, 0x08, 0x04, 0x10, 0x08, 0x04, 0x02, 0x10, 0x04, 0x10, 0x08, 0x02, 0x04, 0x08, 0x02, 0x10, 0x02, 0x04, 0x08, 0x10, 0x10, 0x02};
unsigned char secuenciasPosibles1[30] = {0x02, 0x10, 0x04, 0x08, 0x08, 0x02, 0x04, 0x08, 0x10, 0x02, 0x04, 0x08, 0x04, 0x10, 0x02, 0x08, 0x04, 0x02, 0x10, 0x10, 0x02, 0x04, 0x08, 0x02, 0x04, 0x10, 0x08, 0x02, 0x10, 0x04}; 
unsigned char secuenciasPosibles2[30] = {0x08, 0x02, 0x04, 0x08, 0x02, 0x04, 0x08, 0x10, 0x02, 0x04, 0x08, 0x08, 0x02, 0x04, 0x10, 0x10, 0x02, 0x08, 0x04, 0x04, 0x08, 0x02, 0x10, 0x08, 0x10, 0x02, 0x04, 0x04, 0x10, 0x08};
unsigned char secuenciasPosibles3[30] = {0x02, 0x08, 0x02, 0x10, 0x04, 0x02, 0x08, 0x04, 0x10, 0x08, 0x02, 0x04, 0x02, 0x08, 0x04, 0x08, 0x10, 0x02, 0x04, 0x10, 0x08, 0x02, 0x04, 0x08, 0x10, 0x02, 0x04, 0x08, 0x10, 0x02};
unsigned char secuenciasPosibles4[30] = {0x10, 0x04, 0x08, 0x02, 0x08, 0x10, 0x04, 0x02, 0x08, 0x10, 0x04, 0x02, 0x08, 0x10, 0x08, 0x02, 0x04, 0x08, 0x10, 0x04, 0x08, 0x02, 0x04, 0x08, 0x10, 0x02, 0x08, 0x04, 0x10, 0x08};
unsigned char secuenciasPosibles5[30] = {0x02, 0x04, 0x02, 0x10, 0x02, 0x08, 0x04, 0x10, 0x08, 0x02, 0x08, 0x04, 0x10, 0x08, 0x02, 0x04, 0x08, 0x10, 0x02, 0x08, 0x04, 0x08, 0x10, 0x02, 0x04, 0x08, 0x10, 0x08, 0x02, 0x04};
unsigned char secuenciasPosibles6[30] = {0x08, 0x10, 0x08, 0x04, 0x08, 0x10, 0x08, 0x02, 0x04, 0x08, 0x10, 0x02, 0x08, 0x04, 0x08, 0x10, 0x02, 0x04, 0x08, 0x02, 0x04, 0x10, 0x08, 0x10, 0x04, 0x02, 0x08, 0x02, 0x08, 0x04};

unsigned char pulsadoPrevioEnmascarado [4] = {0b00000011, 0b00000101, 0b00001001, 0b00010001};
unsigned int X; 
unsigned char mataRBIF;

void main (void){
	unsigned char posibilidades[30], data, compruebaWHILEsalidas, compruebaWHILEentradas;
	unsigned int metePosib = 0;
	int aleatoriador;
	Inicializacion();
	mataRBIF = PORTB;
	RBIF = 0;
	aleatoriador = 0;
	while(RBIF == 0){
		PORTA = 0xFF & 0xFE;
		aleatoriador++;
		if(aleatoriador == 6){
			aleatoriador = 0;
		}
	}
	switch(aleatoriador){
		case 0: for(metePosib = 0; metePosib <30; metePosib++){posibilidades[metePosib] = secuenciasPosibles0[metePosib];}
				break;
		case 1: for(metePosib = 0; metePosib <30; metePosib++){posibilidades[metePosib] = secuenciasPosibles1[metePosib];}
				break;
		case 2: for(metePosib = 0; metePosib <30; metePosib++){posibilidades[metePosib] = secuenciasPosibles2[metePosib];}
				break;
		case 3: for(metePosib = 0; metePosib <30; metePosib++){posibilidades[metePosib] = secuenciasPosibles3[metePosib];}
				break;
		case 4: for(metePosib = 0; metePosib <30; metePosib++){posibilidades[metePosib] = secuenciasPosibles4[metePosib];}
				break;
		case 5: for(metePosib = 0; metePosib <30; metePosib++){posibilidades[metePosib] = secuenciasPosibles5[metePosib];}
				break;
		default: for(metePosib = 0; metePosib <30; metePosib++){posibilidades[metePosib] = secuenciasPosibles0[metePosib];}
				break;
	}
	mataRBIF = PORTB;
	RBIF = 0;
	metePosib = 0;
	for(X=50; X<80; X++){							//|
		eeprom_write(X, posibilidades[metePosib]);	//|-> Relleno la EEPROM con las combinaciones del juego
		DelayMs(20);								//|
		metePosib++;								//|
	}												//|
	DelayMs(20);		//espera de seguridad obligatoria antes de un eeprom_read()
	X = 50;											
	data = eeprom_read(X);						//|
	data = (data | 0x01);						//|->El flag del primer tono debe estar siempre a 1
	eeprom_write(X, data);						//|
	DelayMs(20);		//espera de seguridad obligatoria antes de un eeprom_read()
	for (X=51; X<80; X++){						//|
		data = eeprom_read(X);					//|
		data = (data & 0xFE);					//|->Todos los flags de la EEPROM (menos el de la posición 1) a 0
 		eeprom_write(X, data);					//|
		DelayMs(20);		//espera de seguridad obligatoria antes de un eeprom_read()
	}											//|
	Rutina_Inicio();							//Da la bienvenida al jugador (jueguecito de luces con los LEDs)
	while(1){									//bucle del juego:
		X = 50;
		mataRBIF = PORTB;
		RBIF = 0;
		compruebaWHILEsalidas = eeprom_read(X) & 0x01;
		while(compruebaWHILEsalidas != 0){		//Representando la serie (parará cuando encuentre un FLAG=0)
			DelayMs(250);								//Mantenlo apagado 1s
			PORTA = eeprom_read(X) & 0b00011110;		//Saca el tono de la posición de la EEPROM en que estés
			reproduce_tono();
//			DelayMs(500);								//Mantenlo encendido 1s
			PORTA = 0x00;								//Apágalo
			X++;										//Pasa a la siguiente dirección EEPROM
			compruebaWHILEsalidas = eeprom_read(X) & 0x01;
		}										//Encuentra un FLAG=0, deja de representar
		X = 50;
		mataRBIF = PORTB;
		RBIF = 0;
		compruebaWHILEentradas = eeprom_read(X) & 0x01;										//Devuelve la EEPROM a la primera posición
		while(compruebaWHILEentradas != 0){		//Recibiendo la serie (parará cuando encuentre un FLAG=0)
			while(RBIF == 0){};							//Se queda esperando a que se active el FLAG de botón pulsado
			CompruebaPulsado();							//¿¿Botón pulsado == Botón que había que pulsar?? Si es que NO, no vuelve a salir de la función.
			compruebaWHILEentradas = eeprom_read(X) & 0x01;
			mataRBIF = PORTB;
			RBIF = 0;
		}											//Si encuentra un FLAG=0 sale del while()
		data = eeprom_read(X);						//|
		data = (data | 0x01);							//|->Flag del siguiente = 1 (Incrementa el número de combinaciones de la secuencia en 1)
		DelayMs(500);
		eeprom_write(X, data);						//|
		DelayMs(50);		//espera de seguridad obligatoria antes de un eeprom_read()
	}
}


//****************************************************************
//****************************************************************
//****************************************************************
void CompruebaPulsado(void){
	unsigned char pulsadoEnmascarado = 0x00, comprobador;
	if(RB7 == 0){pulsadoEnmascarado = pulsadoPrevioEnmascarado [0];}
	if(RB6 == 0){pulsadoEnmascarado = pulsadoPrevioEnmascarado [1];}
	if(RB5 == 0){pulsadoEnmascarado = pulsadoPrevioEnmascarado [2];}
	if(RB4 == 0){pulsadoEnmascarado = pulsadoPrevioEnmascarado [3];}

	comprobador = pulsadoEnmascarado & eeprom_read(X);
	comprobador = comprobador & 0xFE;

	if (comprobador != 0){
		PORTA = comprobador;						//dejas encendido el LED correspondiente hasta la próx. pulsación
		X++;											//Pasas a la siguiente dirección de la EEPROM 
	}else{
		PORTA = 0x00;
		DelayMs(150);
		PORTA = 0xFF & 0xFE;		
		DelayMs(500);			
		while(PORTB != 0xFF){}
		DelayMs(100);
		PORTA = 0x00;
		mataRBIF = PORTB;
		RBIF = 0;

		PORTA = 0x06;
		while(RBIF == 0){
			PORTA = ~PORTA;
			DelayMs(500);
		}										//|-->HAS PERDIDO! Qué te tengo dicho de jugar borracho?
		asm("ljmp 0x0000");						//Si pulsas cualquier botón reinicias el sistema.
	}
	reproduce_tono_whilePulsado();
//	while(PORTB != 0xFF){}
	DelayMs(100);
	PORTA = 0x00;
	mataRBIF = PORTB;
	RBIF = 0;										//reinicio el Flag para que vuelva a esperar a la siguiente pulsación
}

//****************************************************************
//****************************************************************
//****************************************************************
void Inicializacion(void){			//Configuración del sistema:
	OSCCON = 0x72;					//Pongo el reloj a 8MHz
	ANSEL = 0x00;					//Todo digital
	TRISA = 0x00;					//PORTA como Output
	OPTION = RBPU;					//RBPU por 0x00Resistencias de Pull-up de PORTB activadas
	TRISB = 0xFF;					//PORTB como Input
	INTCON = 0x00;			//Deshabilito interrupciones globales y de periféricos y las de PORTB<7:4> y pongo los flags a 0
	for(X=50; X<80; X++){				//|
		eeprom_write(X, 0x00);			//|-> Relleno la EEPROM con las combinaciones del juego
		DelayMs(20);
	}			
	mataRBIF = PORTB;
	RBIF = 0;
}


//****************************************************************
//****************************************************************
//****************************************************************
void Rutina_Inicio (void){			//Jueguecito de luces para decir "hola" al jugador
	PORTA = 0b00000010;
	DelayMs(150);

	PORTA = 0b00000100;
	DelayMs(150);
	
	PORTA = 0b00001000;
	DelayMs(150);
	
	PORTA = 0b00010000;
	DelayMs(150);
	
	PORTA = 0x00;
	DelayMs(150);
	
	PORTA = 0b00011110;
	DelayMs(150);

	PORTA = 0x00;
	DelayMs(150);

	PORTA = 0b00011110;
	DelayMs(150);

	PORTA = 0x00;
	DelayMs(150);
}


void reproduce_tono(void){
	int contador;
	if((PORTA & 0b00010000) != 0){		//led verde --> 620Hz -->T/2=807 us -->620 cycles
		for(contador=0; contador<620; contador++){
			RA0 = ~RA0;
			DelayUs(807);
		}
	}
	if((PORTA & 0b00001000) != 0){		//led rojo ---> 440Hz --> T=2273 us --> T/2 = 1136 us --> 440cycles
			for(contador=0; contador<440; contador++){
			RA0 = ~RA0;
			DelayUs(1136);
		}
	}
	if((PORTA & 0b00000100) != 0){		//led rojo ---> 329,628Hz --> T=3034 us --> T/2 = 1517 us --> 330cycles
			for(contador=0; contador<400; contador++){
			RA0 = ~RA0;
			DelayUs(1517);
		}
	}
	if((PORTA & 0b00000010) != 0){		//led rojo ---> 220Hz --> T=4545 us --> T/2 = 2273 us --> 220cycles
			for(contador=0; contador<400; contador++){
			RA0 = ~RA0;
			DelayUs(2273);
		}
	}
}

void reproduce_tono_whilePulsado(void){
	int contador;
	if((PORTA & 0b00010000) != 0){		//led verde --> 620Hz -->T/2=807 us -->620 cycles
		while(PORTB != 0xFF){
			RA0 = ~RA0;
			DelayUs(807);
		}
	}
	if((PORTA & 0b00001000) != 0){		//led rojo ---> 440Hz --> T=2273 us --> T/2 = 1136 us --> 440cycles
		while(PORTB != 0xFF){
			RA0 = ~RA0;
			DelayUs(1136);
		}
	}
	if((PORTA & 0b00000100) != 0){		//led rojo ---> 329,628Hz --> T=3034 us --> T/2 = 1517 us --> 330cycles
		while(PORTB != 0xFF){
			RA0 = ~RA0;
			DelayUs(1517);
		}
	}
	if((PORTA & 0b00000010) != 0){		//led rojo ---> 220Hz --> T=4545 us --> T/2 = 2273 us --> 220cycles
		while(PORTB != 0xFF){
			RA0 = ~RA0;
			DelayUs(2273);
		}
	}
}