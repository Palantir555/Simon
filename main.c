#include <htc.h>;	//Para eeprom_read(adress) y eeprom_write(address, data);
#include "delay.c";	//Librería de retardos de Hi Tech

#define _XTAL_FREQ 8000000;	//Clock freq.

__CONFIG(INTIO & UNPROTECT & CCPRB0 & DEBUGDIS & LVPDIS & BORDIS & MCLRDIS & 
	PWRTDIS & WDTDIS & UNPROTECT);
__CONFIG(FCMDIS & IESODIS);


void Rutina_Inicio (void);
void Inicializacion (void);
void CompruebaPulsado (void);
void reproduce_tono(void);
void reproduce_tono_whilePulsado(void);

unsigned char posibilidades[30];	
unsigned char secuenciasPosibles0[30] = {0x04, 0x02, 0x02, 0x04, 0x08, 0x02, 
	0x04, 0x10, 0x02, 0x08, 0x04, 0x10, 0x08, 0x04, 0x02, 0x10, 0x04, 0x10, 
	0x08, 0x02, 0x04, 0x08, 0x02, 0x10, 0x02, 0x04, 0x08, 0x10, 0x10, 0x02};
unsigned char secuenciasPosibles1[30] = {0x02, 0x10, 0x04, 0x08, 0x08, 0x02, 
	0x04, 0x08, 0x10, 0x02, 0x04, 0x08, 0x04, 0x10, 0x02, 0x08, 0x04, 0x02, 
	0x10, 0x10, 0x02, 0x04, 0x08, 0x02, 0x04, 0x10, 0x08, 0x02, 0x10, 0x04}; 
unsigned char secuenciasPosibles2[30] = {0x08, 0x02, 0x04, 0x08, 0x02, 0x04, 
	0x08, 0x10, 0x02, 0x04, 0x08, 0x08, 0x02, 0x04, 0x10, 0x10, 0x02, 0x08, 
	0x04, 0x04, 0x08, 0x02, 0x10, 0x08, 0x10, 0x02, 0x04, 0x04, 0x10, 0x08};
unsigned char secuenciasPosibles3[30] = {0x02, 0x08, 0x02, 0x10, 0x04, 0x02, 
	0x08, 0x04, 0x10, 0x08, 0x02, 0x04, 0x02, 0x08, 0x04, 0x08, 0x10, 0x02, 
	0x04, 0x10, 0x08, 0x02, 0x04, 0x08, 0x10, 0x02, 0x04, 0x08, 0x10, 0x02};
unsigned char secuenciasPosibles4[30] = {0x10, 0x04, 0x08, 0x02, 0x08, 0x10, 
	0x04, 0x02, 0x08, 0x10, 0x04, 0x02, 0x08, 0x10, 0x08, 0x02, 0x04, 0x08, 
	0x10, 0x04, 0x08, 0x02, 0x04, 0x08, 0x10, 0x02, 0x08, 0x04, 0x10, 0x08};
unsigned char secuenciasPosibles5[30] = {0x02, 0x04, 0x02, 0x10, 0x02, 0x08, 
	0x04, 0x10, 0x08, 0x02, 0x08, 0x04, 0x10, 0x08, 0x02, 0x04, 0x08, 0x10, 
	0x02, 0x08, 0x04, 0x08, 0x10, 0x02, 0x04, 0x08, 0x10, 0x08, 0x02, 0x04};
unsigned char secuenciasPosibles6[30] = {0x08, 0x10, 0x08, 0x04, 0x08, 0x10, 
	0x08, 0x02, 0x04, 0x08, 0x10, 0x02, 0x08, 0x04, 0x08, 0x10, 0x02, 0x04, 
	0x08, 0x02, 0x04, 0x10, 0x08, 0x10, 0x04, 0x02, 0x08, 0x02, 0x08, 0x04};

unsigned char pulsadoPrevioEnmascarado [4] = {0x03, 0x05, 0x09, 0x11};
unsigned int X; 
unsigned char mataRBIF;

void main (void){
	Inicializacion();
	unsigned char posibilidades[30], data, compruebaWHILEsalidas; 
	unsigned char compruebaWHILEentradas;
	unsigned int metePosib = 0;
	int aleatoriador;
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
		case 0: 
			for(metePosib = 0; metePosib <30; metePosib++){
				posibilidades[metePosib] = secuenciasPosibles0[metePosib];
			}
			break;
		case 1: 
			for(metePosib = 0; metePosib <30; metePosib++){
				posibilidades[metePosib] = secuenciasPosibles1[metePosib];
			}
			break;
		case 2: 
			for(metePosib = 0; metePosib <30; metePosib++){
				posibilidades[metePosib] = secuenciasPosibles2[metePosib];
			}
			break;
		case 3: 
			for(metePosib = 0; metePosib <30; metePosib++){
				posibilidades[metePosib] = secuenciasPosibles3[metePosib];
			}
			break;
		case 4: 
			for(metePosib = 0; metePosib <30; metePosib++){
				posibilidades[metePosib] = secuenciasPosibles4[metePosib];
			}
			break;
		case 5: 
			for(metePosib = 0; metePosib <30; metePosib++){
				posibilidades[metePosib] = secuenciasPosibles5[metePosib];
			}
			break;
		default: 
			for(metePosib = 0; metePosib <30; metePosib++){
				posibilidades[metePosib] = secuenciasPosibles0[metePosib];
			}
			break;
	}
	mataRBIF = PORTB;
	RBIF = 0;
	metePosib = 0;

	//Relleno la EEPROM con las combinaciones del juego:
	for(X=50; X<80; X++){	
		eeprom_write(X, posibilidades[metePosib]);
		DelayMs(20);
		metePosib++;
	}

	DelayMs(20); //Espera de seguridad obligatoria antes de un eeprom_read()
	X = 50;											
	data = eeprom_read(X);
	data = (data | 0x01);
	eeprom_write(X, data);	//El flag del primer tono debe estar siempre a 1
	DelayMs(20);

	//Todos los flags de la EEPROM (menos el de la posición 1) a 0
	for (X=51; X<80; X++){
		data = eeprom_read(X);
		data = (data & 0xFE);
 		eeprom_write(X, data);
		DelayMs(20);
	}

	Rutina_Inicio();  //Da la bienvenida al jugador

	//bucle del juego:
	while(1){
		X = 50;
		mataRBIF = PORTB;
		RBIF = 0;
		compruebaWHILEsalidas = eeprom_read(X) & 0x01;

		//Representando la serie (parará cuando encuentre un FLAG=0):
		while(compruebaWHILEsalidas != 0){		
			DelayMs(250);
			PORTA = eeprom_read(X) & 0b00011110; //Get which tone to play
			reproduce_tono();
			PORTA = 0x00;						 //Apágalo
			X++;								 //Next EEPROM address
			compruebaWHILEsalidas = eeprom_read(X) & 0x01;
		}
		X = 50;
		mataRBIF = PORTB;
		RBIF = 0;
		compruebaWHILEentradas = eeprom_read(X) & 0x01;	//EEPROM to 1st tone

		//Recibiendo la serie (parará cuando FLAG=0 o cuando CompruebaPulsado()
		//	termine el juego. Note: Should finish the game from within this loop
		while(compruebaWHILEentradas != 0){
			while(RBIF == 0);	//Wait for the "button pressed" flag
			CompruebaPulsado();	//Check the button pressed. END GAME if wrong.
			compruebaWHILEentradas = eeprom_read(X) & 0x01;
			mataRBIF = PORTB;
			RBIF = 0;
		}

		//Set next flag=1 (increments the length of the sequence):
		data = eeprom_read(X);
		data = (data | 0x01);	
		DelayMs(500);
		eeprom_write(X, data)
		DelayMs(50);
	}
}

void CompruebaPulsado(void){
	unsigned char pulsadoEnmascarado = 0x00, comprobador;
	if(RB7 == 0){pulsadoEnmascarado = pulsadoPrevioEnmascarado [0];}
	if(RB6 == 0){pulsadoEnmascarado = pulsadoPrevioEnmascarado [1];}
	if(RB5 == 0){pulsadoEnmascarado = pulsadoPrevioEnmascarado [2];}
	if(RB4 == 0){pulsadoEnmascarado = pulsadoPrevioEnmascarado [3];}

	comprobador = pulsadoEnmascarado & eeprom_read(X);
	comprobador = comprobador & 0xFE;

	if (comprobador != 0){
		PORTA = comprobador;//LED ON hasta la próx. pulsación
		X++;				//Siguiente dirección de la EEPROM 
	}else{ 					//HAS PERDIDO!
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
		while(RBIF == 0){	//Espera una pulsación blinking los LEDs
			PORTA = ~PORTA;
			DelayMs(500);
		}
		asm("ljmp 0x0000");	//Si pulsas cualquier botón reinicias el sistema.
	}
	reproduce_tono_whilePulsado();
	DelayMs(100);
	PORTA = 0x00;
	mataRBIF = PORTB;
	RBIF = 0;	//Reset del Flag para volver a esperar a la siguiente pulsación
}

void Inicializacion(void){	//Configuración del sistema:
	OSCCON = 0x72;	//Pongo el reloj a 8MHz
	ANSEL = 0x00;	//Todo digital
	TRISA = 0x00;	//PORTA como Output
	OPTION = RBPU;	//RBPU por 0x00 Pull-up resistors de PORTB activadas
	TRISB = 0xFF;	//PORTB como Input
	INTCON = 0x00;	//Deshabilito interrupciones globales y de 
					//periféricos y las de PORTB<7:4> y pongo los flags a 0
	mataRBIF = PORTB;
	RBIF = 0;
}

//Jueguecito de luces para decir "hola" al jugador
void Rutina_Inicio (void){	
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
	//led verde -> 620Hz -> T=1614 us ->T/2=807 us -> 620 cycles
	if((PORTA & 0b00010000) != 0){
		for(contador=0; contador<620; contador++){
			RA0 = ~RA0;
			DelayUs(807);
		}
	}
	//led rojo ---> 440Hz --> T=2273 us --> T/2 = 1136 us --> 440cycles
	if((PORTA & 0b00001000) != 0){
			for(contador=0; contador<440; contador++){
			RA0 = ~RA0;
			DelayUs(1136);
		}
	}
	//led rojo ---> 329,628Hz --> T=3034 us --> T/2 = 1517 us --> 330cycles
	if((PORTA & 0b00000100) != 0){
			for(contador=0; contador<400; contador++){
			RA0 = ~RA0;
			DelayUs(1517);
		}
	}
	//led rojo ---> 220Hz --> T=4545 us --> T/2 = 2273 us --> 220cycles
	if((PORTA & 0b00000010) != 0){
			for(contador=0; contador<400; contador++){
			RA0 = ~RA0;
			DelayUs(2273);
		}
	}
}

void reproduce_tono_whilePulsado(void){
	int contador;
	if((PORTA & 0b00010000) != 0){
		while(PORTB != 0xFF){
			RA0 = ~RA0;
			DelayUs(807);
		}
	}

	if((PORTA & 0b00001000) != 0){
		while(PORTB != 0xFF){
			RA0 = ~RA0;
			DelayUs(1136);
		}
	}

	if((PORTA & 0b00000100) != 0){
		while(PORTB != 0xFF){
			RA0 = ~RA0;
			DelayUs(1517);
		}
	}

	if((PORTA & 0b00000010) != 0){
		while(PORTB != 0xFF){
			RA0 = ~RA0;
			DelayUs(2273);
		}
	}
}