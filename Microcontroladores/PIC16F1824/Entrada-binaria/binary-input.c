/******************************************************************************
 *
 *    File: binary-input.c
 *    PIC:  PIC16F1824
 *         (http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en546901)
 *
 *    Description: Este programa verifica el valor de una señal binaria
 *                 en el puerto RA2 (Pin 11) del PIC16F1824, que condiciona
 *                 el valor de salida en el puerto RC0 (Pin 10) a 1 o 0.
 * 
 *    Copyright (C) 2013  Daniel Mejía Raigosa (https://github.com/Daniel-M)
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <pic16f1824.h>

/* Ajustar la velocidad del reloj a 4 MHz mediante software */
#define _XTAL_FREQ 4000000

/* Configuar FOSC con reloj externo con cristal,
   ver datasheet del PIC16F1824variable FOSC y
   sus respectivos valores */
//#pragma config CP=OFF, WDTE=OFF, PWRTE= OFF, FOSC= XT, LVP=OFF, MCLRE= OFF //Es necesario deshabilitar MCLRE porque se necesita usar RA3 como entrada.

/* Configuar FOSC con reloj interno, ver datasheet del PIC16F1824
   variable FOSC y sus respectivos valores */

#pragma config CP=OFF, WDTE=OFF, PWRTE= OFF, FOSC= INTOSC, LVP=OFF, MCLRE= OFF //Es necesario deshabilitar MCLRE porque se necesita usar RA3 como entrada.


void main(void){

    /* Ajustar el reloj interno */
    OSCCONbits.IRCF = 14;

    /* Ajustar registro TRIS para el puerto RC0 como salida */
    TRISCbits.TRISC0=0;

    /* Ajustar registro TRIS para el puerto RA2 en modo de entrada */
    TRISAbits.TRISA2=1; /*¬SS es entrada*/

    /* Ajustamos el puerto analógico RA2 como una entrada digital
       Esta configuración se requiere para leer valores digitales,
       es decir, binarios 1 ( > 3.5 V ) o 0 ( < 2.5 V)*/
    ANSELAbits.ANSA2=0;


    /* La salida en el puerto RC0 puesta en 1 (5 V en el pin 10) */
    PORTCbits.RC0=1;

    /* bucle infinito */
    while(1)
    {
        /* Si se lee un valor binario igual a 1 ( > 3.5 V ) en el puerto RA2
           Ingresa en el condicinal, de otra manera, continua la ejecución */
        if(RA2==1)
        {
                /* la salida en el puerto RC0 vale 0 (0 V en el pin 10) */
                PORTCbits.RC0=0;
        }
        else
        {
                /* La salida en el puerto RC0 puesta en 1 (5 V en el pin 10) */
                PORTCbits.RC0=1;
        }
    }

}