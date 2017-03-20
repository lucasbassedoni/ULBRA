/*
TITULO: Biblioteca com funções para calcular o tempo
DATA: 19/Março/2012


ATENÇÃO. Nova função tempo() para Windows. Agora creio que ela funciona.
Testem (mensagem de 2012)
*/

/* AGORA a função funciona com precisão de microssegundos também
 * para o Windows. Testado com SUCESSO no Dev++ (em 2012)
 */
#ifndef __TEMPO__
/* Sempre que se cria uma biblioteca é prudente usar um define para ela.
 * Veja, as definições abaixo só ocorrerão se NÃO HOUVER AINDA a constante
 * __TEMPO__. Isto evita erros com duplas inclusões, ou seja, dois ou mais
 * #include "tempo.h". Apenas o primeiro terá efeito e os demais nada
 * definirão. Todos os .h deveriam usar isto.
 * */
#define __TEMPO__

/* para muitos códigos, um inteiro longo sem sinal é o ideal.
Se for um compilador de 32 bits, isto resultará em um inteiro
de 32 bits. Porém se for um compilador de 64 bits, será um inteiro
de 64 bits.

Crio um typedef pois é muita coisa ficar digitando unsigned long int
Assim, só se coloca ulong
*/

#ifndef LINUX
typedef unsigned int ulong;
#endif

/* Se for usar ela no LINUX, insira um #define LINUX no início do teu código,
 * antes do include para o tempo.h
 * */
#ifdef LINUX
#include <sys/time.h>
#include <termios.h>
#include <time.h>
#define clrscr()    printf("\033[2J")

/* Parte exclusiva do Windows */
#else
#include <conio.h>
#include <time.h>
#include <windows.h>

/* Elgio em Março de 2012 */
/* Função tempo para Windows.
 * Descobri que tem como calcular quantos microssegundos se passaram
 * dentro do mesmo segundo!
 * Aliando isto a função time que retorna quantos segundos, foi possível
 * calcular */
ulong tempo()
{
    LARGE_INTEGER ticksPerSecond;
    static LARGE_INTEGER timeI, timeF;
    static unsigned int usec=0;

    QueryPerformanceFrequency(&ticksPerSecond);
    QueryPerformanceCounter(&timeF);

    /* Primeira invocacao */
    if (usec==0) {
       timeI=timeF;
       usec=1;
       return(0);
    }

    usec = ((double)(timeF.QuadPart-timeI.QuadPart)/ticksPerSecond.QuadPart)*1000000;

    QueryPerformanceCounter(&timeI);

    return usec;

}

#endif
/* Fim da parte exclusiva para Windows */


/* Agora para Linux 
 * Observação: retornará LIXO na primeira invocação, pois
 * tf e ti não foram inicializados (não vejo problema nisto. Seria
 * fácil corrigir, mas desnecessário. Como a função retorna quanto
 * tempo se passou desde a última invocação, na primeira deve-se
 * desconsiderar o retorno mesmo)
 * */
#ifdef LINUX
ulong tempo()
{
    static struct timeval ti, tf;
    ulong ms;

/* pega o tempo atual. */
    gettimeofday(&tf, NULL);

    ms = (tf.tv_sec - ti.tv_sec) * 1000000 + (tf.tv_usec - ti.tv_usec);

    gettimeofday(&ti, NULL); 
    // Ajusta ti que ficará com este valor na próxima invocação, pois ti é estático
    
    /* retorna o tempo que se passou em microsegundos
       1s = 1.000.000 us
     */
    return (ms);
}
#endif

/* Retorna uma string com o tempo formatado em  seg,  mseg e useg */
char *formata(ulong m)
{
    static char tempo[30];
    ulong s, ms, us;

    s = m / 1000000;
    ms = (m % 1000000) / 1000;
    us = (m % 1000);

    sprintf(tempo, "%02lus %03lums %03luus", s, ms, us);
    return (tempo);
}
#endif

/* Disponível como tempo.h
 * Para usar coloque o tempo.h no mesmo diretório do teu código fonte e 
 * inclua ele da seguinte forma:
 * 
 * #include "tempo.h"
 * 
 */
