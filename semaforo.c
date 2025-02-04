#include <stdio.h>
#include "pico/stdlib.h"

//Definindo os LEDs do semáforo.
#define RED_LED_PIN 11
#define YELLOW_LED_PIN 12
#define GREEN_LED_PIN 13

//Estado do LED
volatile int state = 0; 

//função callback.
bool repeating_timer_callback(struct repeating_timer *t){
    //Desliga os LEDs.
    gpio_put(RED_LED_PIN, false);
    gpio_put(YELLOW_LED_PIN, false);
    gpio_put(GREEN_LED_PIN, false);

    //Altera o estado atual do semáforo.
    switch (state){
    //apenas o vermelho ativado.
    case 0:
        gpio_put(RED_LED_PIN, true);
        gpio_put(YELLOW_LED_PIN, false);
        gpio_put(GREEN_LED_PIN, false);
        break;
    //apenas o amarelo ligado.
    case 1:
        gpio_put(RED_LED_PIN, false);
        gpio_put(YELLOW_LED_PIN, true);
        gpio_put(GREEN_LED_PIN, false);
        break;
    //apenas o verde ligado.
    case 2:
        gpio_put(RED_LED_PIN, false);
        gpio_put(YELLOW_LED_PIN, false);
        gpio_put(GREEN_LED_PIN, true);
        break;
    }

    state = (state+1)%3; //sempre vai ficar entre 0,1 e 2.

    return true;
}

int main()
{
    stdio_init_all();

    //iniciando os LEDs.
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);

    gpio_init(YELLOW_LED_PIN);
    gpio_set_dir(YELLOW_LED_PIN, GPIO_OUT);

    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        printf("Semáforo funcionando...\n");
        sleep_ms(1000);
    }
}