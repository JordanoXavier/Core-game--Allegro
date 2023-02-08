#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#define tela_x 800
#define tela_y 600
#define pi 3.1415


struct esferas {
    int tipo, tamanho;
    float posicao_x, posicao_y;
    float posicao_x_inicial, posicao_y_inicial;
    int direcao;
    float distancia;
    float velocidade_individual;
};


void desenhateladeajuda(int mouseX, int mouseY, int *sair_ajuda, int fonte){
            al_draw_filled_rectangle(tela_x/2-200, tela_y/2-180, tela_x/2+200, tela_y/2+180, al_map_rgb(9,102,135));

            al_draw_text(fonte, al_map_rgb(20,220,20), tela_x/2, tela_y/2-168, ALLEGRO_ALIGN_CENTER, "Ajuda");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-185, tela_y/2-145, ALLEGRO_ALIGN_LEFT, "Mouse: controla o circulo de defesa");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-185, tela_y/2-125, ALLEGRO_ALIGN_LEFT, "Clique: atira com o canhao, destruindo as esfe-");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-190, tela_y/2-115, ALLEGRO_ALIGN_LEFT, "ras.");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-185, tela_y/2-95, ALLEGRO_ALIGN_LEFT, "Espaco: ativa o escudo, quando disponivel");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-185, tela_y/2-75, ALLEGRO_ALIGN_LEFT, "Esc: ativa a pausa, quando disponivel");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-185, tela_y/2-35, ALLEGRO_ALIGN_LEFT, "Ao ser atingido por uma esfera vermelha, o raio");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-190, tela_y/2-25, ALLEGRO_ALIGN_LEFT, "do jogador e reduzido.");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-185, tela_y/2-05, ALLEGRO_ALIGN_LEFT, "Ao ser atingido por uma esfera azul, o raio do");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-190, tela_y/2+05, ALLEGRO_ALIGN_LEFT, "jogador e reduzido.");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-185, tela_y/2+25, ALLEGRO_ALIGN_LEFT, "A cada 15 pontos a fase e aumentada");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-185, tela_y/2+35, ALLEGRO_ALIGN_LEFT, "- a cada fase a velocidade aumentada em 1,05x");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-185, tela_y/2+45, ALLEGRO_ALIGN_LEFT, "- e permitida uma pausa por fase");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-185, tela_y/2+55, ALLEGRO_ALIGN_LEFT, "- o escudo pode ser usado a cada 3 fases");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-185, tela_y/2+65, ALLEGRO_ALIGN_LEFT, "- a cada 5 fases uma esfera a mais vira na tela");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-185, tela_y/2+75, ALLEGRO_ALIGN_LEFT, "- a cada 10 fases o jogador ganha uma vida");
            al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2-185, tela_y/2+95, ALLEGRO_ALIGN_LEFT, "A cada 50 pontos o missil especial e ativado");

            al_draw_filled_rectangle(tela_x/2-50, tela_y/2+190, tela_x/2+50, tela_y/2+230, al_map_rgb(9,102,135));
            if (mouseX > tela_x/2-50 && mouseY > tela_y/2+190 && mouseX < tela_x/2+50 && mouseY < tela_y/2+230){
                al_draw_filled_rectangle(tela_x/2-50, tela_y/2+190, tela_x/2+50, tela_y/2+230, al_map_rgb(9,133,135));
                *sair_ajuda = 1;
            }
            al_draw_text(fonte, al_map_rgb(20,220,20), tela_x/2, tela_y/2+205, ALLEGRO_ALIGN_CENTER, "Voltar");
}


float calculadistancia(int x, int y){
    int catetoy = fabs(y - tela_y/2);
    int catetox = fabs(x - tela_x/2);
    float hipotenusa  = sqrt(catetoy*catetoy + catetox*catetox);

    return hipotenusa;
}


void gera_esfera(struct esferas *inimigo){

    inimigo->direcao = rand()%4 + 1;
    switch(inimigo->direcao){
        case 1:
        inimigo->posicao_x = - rand()%500;
        inimigo->posicao_y = rand()%600;
            break;
        case 2:
        inimigo->posicao_x = 800 + rand()%500;
        inimigo->posicao_y = rand()%600;
            break;
        case 3:
        inimigo->posicao_x = rand()%800;
        inimigo->posicao_y = - rand()%500;
            break;
        case 4:
        inimigo->posicao_x = rand()%800;
        inimigo->posicao_y = 600 + rand()%500;
            break;
    }

    inimigo->tipo = rand()%5 + 1;
    inimigo->tamanho = rand()%4 + 4;
    inimigo->velocidade_individual = (rand()%5 + 5)/10.0;

    inimigo->posicao_x_inicial = inimigo->posicao_x;
    inimigo->posicao_y_inicial = inimigo->posicao_y;

    inimigo->distancia =  calculadistancia(inimigo->posicao_x, inimigo->posicao_y);
}


void desenha_esfera(int num_esferas, struct esferas inimigo[30]){

    for (int i=0; i<num_esferas; i++){
        if(inimigo[i].tipo <5){
            al_draw_filled_circle(inimigo[i].posicao_x, inimigo[i].posicao_y, inimigo[i].tamanho, al_map_rgb(180,50,50));
        }
        if(inimigo[i].tipo ==5){
            al_draw_filled_circle(inimigo[i].posicao_x, inimigo[i].posicao_y, inimigo[i].tamanho, al_map_rgb(57,204,253));
        }
    }
}


void movimenta_esfera(struct esferas *inimigo, float velocidade){

    float cateto_inicial_x = fabs(inimigo->posicao_x_inicial - tela_x/2);
    float cateto_inicial_y = fabs(inimigo->posicao_y_inicial - tela_y/2);


    if(inimigo->posicao_x > tela_x/2){
        inimigo->posicao_x = inimigo->posicao_x - (cateto_inicial_x * velocidade * inimigo->velocidade_individual);
    }
    if(inimigo->posicao_x < tela_x/2){
        inimigo->posicao_x = inimigo->posicao_x + (cateto_inicial_x * velocidade * inimigo->velocidade_individual);
    }

    if(inimigo->posicao_y > tela_y/2){
        inimigo->posicao_y = inimigo->posicao_y - (cateto_inicial_y * velocidade * inimigo->velocidade_individual);
    }
    if(inimigo->posicao_y < tela_y/2){
        inimigo->posicao_y = inimigo->posicao_y + (cateto_inicial_y * velocidade * inimigo->velocidade_individual);
    }

}


int calculacolisao(float mouseX, float mouseY, float inimigoX, float inimigoY){
    int colide_arco =0;

    float angulo_arco = atan2(mouseY - tela_y/2, mouseX - tela_x/2);
    float angulo_menor, angulo_maior;
    if(angulo_arco < -pi/2){
        angulo_menor = pi + ((angulo_arco-pi/2) + pi) ;
    }
    else{
        angulo_menor = angulo_arco - pi/2;
    }
    if(angulo_arco > pi/2){
        angulo_maior = (pi - ((angulo_arco+pi/2) - pi)) * -1 ;
    }
    else{
        angulo_maior = angulo_arco + pi/2;
    }

    float angulo_esfera = atan2(inimigoY - tela_y/2, inimigoX - tela_x/2);
    if(angulo_maior<angulo_menor){
        if(angulo_esfera>0){
            if(angulo_esfera > angulo_menor && angulo_esfera <= pi ){
                colide_arco = 1;
            }
        }
        else {
            if(angulo_esfera < angulo_maior && angulo_esfera >= -pi){
                colide_arco = 1;
            }
        }
    }
    else{
        if(angulo_esfera > angulo_menor && angulo_esfera < angulo_maior){
            colide_arco=1;
        }
    }

    return colide_arco;
}


void verifica_colisao_esfera(struct esferas *inimigo, float velocidade, int mouseX, int mouseY, int *pontos_jogador, float *raio_jogador, int ativarescudo, int raio_escudo, int *gera_missil){

    int colide_arco = calculacolisao(mouseX, mouseY, inimigo->posicao_x, inimigo->posicao_y);


    if(inimigo->distancia <= raio_escudo + 3 + inimigo->tamanho && ativarescudo == 1){
        gera_esfera(inimigo);
        *pontos_jogador = *pontos_jogador + 3;
        if(*pontos_jogador%50 >= 0 && *pontos_jogador%50 <= 2){
            if(*pontos_jogador > 2){
                *gera_missil = 1;
            }
        }
    }
    else{
        if(inimigo->distancia >= 47 + inimigo->tamanho    &&    inimigo->distancia <= 53 + inimigo->tamanho    &&    colide_arco==1){
            gera_esfera(inimigo);
            *pontos_jogador = *pontos_jogador + 1;
            if(*pontos_jogador%50 == 0){
                if(*pontos_jogador != 0){
                    *gera_missil = 1;
                }
            }
        }
        else {
            movimenta_esfera(inimigo, velocidade);
            inimigo->distancia =  calculadistancia(inimigo->posicao_x, inimigo->posicao_y);
        }
        if(inimigo->distancia <= *raio_jogador + inimigo->tamanho){
            if (inimigo->tipo ==5){
                *raio_jogador = *raio_jogador + 2;
            }
            else{
                *raio_jogador = *raio_jogador - 2;
            }
            gera_esfera(inimigo);
        }
    }


}


void botaoreset(int *reset, int mouseX, int mouseY, int *pontos_jogador, float *raio_jogador, int *vidas_jogador, int *fase, double *tempo_inicio, int *num_esferas, float *velocidade, int *escudos_disponiveis, int *pausas_disponiveis, int *pararjogo, int *pausado, struct esferas inimigo[30], int fonte, int *ativarescudo, int *tiro_ativo, int *gerar_jogador, int *missil_ativo){
    al_draw_filled_rectangle(tela_x/2-130, tela_y/2+75, tela_x/2+130, tela_y/2+175, al_map_rgb(9,102,135));
    if(mouseX > tela_x/2-130 && mouseX < tela_x/2+130 && mouseY > tela_y/2+75 && mouseY < tela_y/2+175){
        al_draw_filled_rectangle(tela_x/2-130, tela_y/2+75, tela_x/2+130, tela_y/2+175, al_map_rgb(9,133,135));
    }

    al_draw_text(fonte, al_map_rgb(255,255,255), tela_x/2, tela_y/2+125, ALLEGRO_ALIGN_CENTER, "RESET");

    if(*reset == 1){
        for(int i=0; i<*num_esferas; i++){
            gera_esfera(&inimigo[i]);
        }

        *raio_jogador = 1;
        *gerar_jogador = 1;
        *pontos_jogador = 0;
        *vidas_jogador = 3;
        *fase = 1;
        *tempo_inicio = al_get_time();
        *num_esferas = 5;
        *velocidade = 0.004;
        *escudos_disponiveis = 0;
        *ativarescudo = 0;
        *tiro_ativo = 0;
        *missil_ativo = 0;
        *pausas_disponiveis = 1;
        *pararjogo = -1;
        *pausado = -1;
        *reset = 0;
    }
}


void verifapassagemdenivel(int pontos_jogador, int *copiapontos, int *fase, int fonte, int *levelup, float *velocidade, int *num_esferas, int *vidas_jogador, int *pausas_disponiveis, int *escudos_disponiveis, struct esferas *novoinimigo){
    if(pontos_jogador != copiapontos){
        if(pontos_jogador >= *fase *15){
            *pausas_disponiveis = 1;
            *fase = *fase + 1;
            *levelup = 1;
            *velocidade = *velocidade * 1.05;
            if(*fase % 5 == 0){
                *num_esferas = *num_esferas + 1;
                gera_esfera(novoinimigo);
            }
            if(*fase % 10 == 0){
                *vidas_jogador = *vidas_jogador + 1;
            }
            if(*fase % 3 == 0){
                *escudos_disponiveis = 1;
            }
        }
    }

    *copiapontos = pontos_jogador;
}


void funcaoexpirarescudo(int *raio_escudo, int *expiraescudo, int *ativarescudo){
    *raio_escudo = *raio_escudo - 1;
    if(*raio_escudo <= 0){
        *expiraescudo = 0;
        *ativarescudo = 0;
        *raio_escudo = 50;
    }
}


void animacao_gerar_jogador(float *raio_jogador, int *gerar_jogador){
    if(*raio_jogador < 10){
        *raio_jogador = *raio_jogador + 0.1;
    }
    else {
        *raio_jogador = 10;
        *gerar_jogador = 0;
    }

}


void gera_projetil(float *x_inicial_projetil, float *y_inicial_projetil, int mouseX, int mouseY, float *x_projetil, float *y_projetil){

    *x_inicial_projetil = mouseX;
    *y_inicial_projetil = mouseY;

    float cateto_inicial_x = fabs(mouseX - tela_x/2);
    float cateto_inicial_y= fabs(mouseY - tela_y/2);

    float distancia = 999;

    while(distancia > 50){
        if(*x_inicial_projetil > tela_x/2){
            *x_inicial_projetil = *x_inicial_projetil - (cateto_inicial_x * 0.005);
        }
        if(*x_inicial_projetil < tela_x/2){
            *x_inicial_projetil = *x_inicial_projetil + (cateto_inicial_x * 0.005);
        }

        if(*y_inicial_projetil > tela_y/2){
            *y_inicial_projetil = *y_inicial_projetil - (cateto_inicial_y * 0.005);
        }
        if(*y_inicial_projetil < tela_y/2){
            *y_inicial_projetil = *y_inicial_projetil + (cateto_inicial_y * 0.005);
        }
        distancia = sqrt((*x_inicial_projetil - tela_x/2) * (*x_inicial_projetil - tela_x/2)  + (*y_inicial_projetil - tela_y/2) * (*y_inicial_projetil - tela_y/2));
    }


    if(*x_inicial_projetil > tela_x/2){
        *x_inicial_projetil = tela_x/2 - (*x_inicial_projetil - tela_x/2);
    }
    else{
        *x_inicial_projetil = tela_x/2 + (tela_x/2 - *x_inicial_projetil );
    }
    if(*y_inicial_projetil > tela_y/2){
        *y_inicial_projetil = tela_y/2 - (*y_inicial_projetil - tela_y/2);
    }
    else{
        *y_inicial_projetil = tela_y/2 + (tela_y/2 - *y_inicial_projetil );
    }

    *x_projetil = *x_inicial_projetil;
    *y_projetil = *y_inicial_projetil;

}


void movimenta_projetil(float *x_inicial_projetil, float *y_inicial_projetil, float *x_projetil, float *y_projetil){

    float cateto_inicial_x = fabs(*x_inicial_projetil - tela_x/2);
    float cateto_inicial_y= fabs(*y_inicial_projetil - tela_y/2);

    if(*x_projetil > tela_x/2){
        *x_projetil = *x_projetil + (cateto_inicial_x * 0.07);
    }
    if(*x_projetil < tela_x/2){
        *x_projetil = *x_projetil - (cateto_inicial_x * 0.07);
    }

    if(*y_projetil > tela_y/2){
        *y_projetil = *y_projetil + (cateto_inicial_y * 0.07);
    }
    if(*y_projetil < tela_y/2){
        *y_projetil = *y_projetil - (cateto_inicial_y * 0.07);
    }

}


void verifica_colisao_projetil(float *x_projetil, float *y_projetil, struct esferas inimigo[30], int num_esferas, int *tiro_ativo, float *timer_inicial_tiro, int *pontos_jogador, float *raio_jogador, int *gera_missil){

    if(*x_projetil > tela_x || *x_projetil < 0 || *y_projetil > tela_y || *y_projetil < 0){
        *tiro_ativo = 0;
    }

    for(int i=0; i<num_esferas; i++){
        if(*x_projetil >= floor(inimigo[i].posicao_x) - inimigo[i].tamanho - 7 && *x_projetil <= floor(inimigo[i].posicao_x) + inimigo[i].tamanho +7){
            if(*y_projetil >= floor(inimigo[i].posicao_y) - inimigo[i].tamanho - 7 && *y_projetil <= floor(inimigo[i].posicao_y) + inimigo[i].tamanho +7){
                if(inimigo[i].tipo < 5){
                    *pontos_jogador = *pontos_jogador + 2;
                    if(*pontos_jogador%50 == 0 || *pontos_jogador%50 == 1){
                        if(*pontos_jogador != 0 && *pontos_jogador != 1){
                            *gera_missil = 1;
                        }
                    }
                    *raio_jogador = *raio_jogador * 1.02;
                }
                gera_esfera(&inimigo[i]);
                *tiro_ativo = 0;
                *timer_inicial_tiro = al_get_time();
            }
        }
    }

}


void movimenta_missil(float *x_inicial_projetil, float *y_inicial_projetil, float *x_projetil, float *y_projetil, int *direcaox_projetil, int *direcaoy_projetil){

    float cateto_inicial_x = fabs(*x_inicial_projetil - tela_x/2);
    float cateto_inicial_y= fabs(*y_inicial_projetil - tela_y/2);

    if(*x_inicial_projetil > tela_x/2){
        *x_projetil = *x_projetil + (cateto_inicial_x * 0.07 * *direcaox_projetil);
    }
    if(*x_inicial_projetil < tela_x/2){
        *x_projetil = *x_projetil - (cateto_inicial_x * 0.07 * *direcaox_projetil);
    }

    if(*y_inicial_projetil > tela_y/2){
        *y_projetil = *y_projetil + (cateto_inicial_y * 0.07 * *direcaoy_projetil);
    }
    if(*y_inicial_projetil < tela_y/2){
        *y_projetil = *y_projetil - (cateto_inicial_y * 0.07 * *direcaoy_projetil);
    }

}


void verifica_colisao_missil(float *x_projetil, float *y_projetil, struct esferas inimigo[30], int num_esferas, int *missil_ativo, int *pontos_jogador, int *gera_missil, int *direcaox_projetil, int *direcaoy_projetil, int *cont_colisao_inimigo, int *cont_colisao_parede, int *reduzvelocidade, float *tempo_inicial_reducao_velocidade){

    if(*cont_colisao_parede == 5 || *cont_colisao_inimigo == 3){
        *cont_colisao_parede = 0;
        *cont_colisao_inimigo = 0;
        *missil_ativo = 0;
    }


    if(*x_projetil > tela_x-15 || *x_projetil < 15){
        *direcaox_projetil = *direcaox_projetil * -1;
        *cont_colisao_parede = *cont_colisao_parede + 1;
    }
    if(*y_projetil > tela_y-15 || *y_projetil < 15 + 24){
        *direcaoy_projetil = *direcaoy_projetil * -1;
        *cont_colisao_parede = *cont_colisao_parede + 1;
    }


    for(int i=0; i<num_esferas; i++){
        if(*x_projetil >= floor(inimigo[i].posicao_x) - inimigo[i].tamanho - 15 && *x_projetil <= floor(inimigo[i].posicao_x) + inimigo[i].tamanho +15){
            if(*y_projetil >= floor(inimigo[i].posicao_y) - inimigo[i].tamanho - 15 && *y_projetil <= floor(inimigo[i].posicao_y) + inimigo[i].tamanho +15){
                if(inimigo[i].tipo < 5){
                    *pontos_jogador = *pontos_jogador + 5;
                    *cont_colisao_inimigo = *cont_colisao_inimigo + 1;
                    if(*pontos_jogador%50 >= 0 && *pontos_jogador%50 <=4){
                        if(*pontos_jogador > 4){
                            *gera_missil = 1;
                        }
                    }
                }
                else{
                    *reduzvelocidade =1;
                    *tempo_inicial_reducao_velocidade = al_get_time();
                }
                gera_esfera(&inimigo[i]);
            }
        }
    }
}



int main(void) {
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_EVENT_QUEUE *fila_de_eventos = NULL;

    al_init();
    al_init_font_addon();
    al_init_primitives_addon();
    al_install_mouse();
    al_install_keyboard();

    janela = al_create_display(tela_x, tela_y);
    fonte = al_create_builtin_font();
    fila_de_eventos = al_create_event_queue();

    al_register_event_source(fila_de_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_de_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_de_eventos, al_get_keyboard_event_source());

    srand(time(NULL));

    int rodando = 1, mouseX = 0, mouseY = 0;

    int menu= 1;
    int botao = 0, jogo= 0;
    int ajuda = 0, sair_ajuda = 0;
    double tempo_inicio;

    while (rodando && menu) {
        while (!al_is_event_queue_empty(fila_de_eventos)) {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_de_eventos, &evento);

            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                rodando = 0;
            }
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
                mouseX = evento.mouse.x;
                mouseY = evento.mouse.y;
            }
            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (botao == 1) {
                    jogo = 1;
                    menu = 0;
                    tempo_inicio = al_get_time();
                }
                if (botao == 2) {
                    ajuda = 1;
                }
                if(sair_ajuda == 1){
                    ajuda=0;
                }
            }
        }

        al_clear_to_color(al_map_rgb(10, 43, 97));

        al_draw_text(fonte, al_map_rgb(255,255,255), tela_x/2, 20, ALLEGRO_ALIGN_CENTER, "Trabalho Final de Laboratorio de Programacao");
        al_draw_text(fonte, al_map_rgb(255,255,255), tela_x/2, 35, ALLEGRO_ALIGN_CENTER, "Aluno: Jordano Xavier dos Santos");

        botao = 0;

        al_draw_filled_rectangle(tela_x/2-150, tela_y/2-40, tela_x/2+150, tela_y/2-40-80, al_map_rgb(9,102,135));
        if (mouseX > tela_x/2-150 && mouseY < tela_y/2-40 && mouseX < tela_x/2+150 && mouseY > tela_y/2-40-80){
            al_draw_filled_rectangle(tela_x/2-150, tela_y/2-40, tela_x/2+150, tela_y/2-40-80, al_map_rgb(9,133,135));
            botao = 1;
        }
        al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2, tela_y/2-80, ALLEGRO_ALIGN_CENTER, "Jogar");

        al_draw_filled_rectangle(tela_x/2-150, tela_y/2+40, tela_x/2+150, tela_y/2+40+80, al_map_rgb(9,102,135));
        if (mouseX > tela_x/2-150 && mouseY > tela_y/2+40 && mouseX < tela_x/2+150 && mouseY < tela_y/2+40+80){
            al_draw_filled_rectangle(tela_x/2-150, tela_y/2+40, tela_x/2+150, tela_y/2+40+80, al_map_rgb(9,133,135));
            botao = 2;
        }
        al_draw_text(fonte, al_map_rgb(0,0,0), tela_x/2, tela_y/2+80, ALLEGRO_ALIGN_CENTER, "Ajuda");

        sair_ajuda = 0;
        if(ajuda==1){
            desenhateladeajuda(mouseX, mouseY, &sair_ajuda, fonte);
        }

        al_flip_display();
    }



    double tempo_anterior = 0, tempo_atual = 0;

    float raio_jogador = 1;
    int gerar_jogador = 1;
    int pontos_jogador = 0, copiapontos = 0;
    int vidas_jogador = 3, fase = 1;
    int pausas_disponiveis = 1, escudos_disponiveis = 0;
    float velocidade = 0.004;
    int num_esferas = 5;

    int pararjogo = -1, pausado = -1, reset = 0;

    int levelup = 0, ylevelup = -20;

    int ativarescudo = 0, raio_escudo = 50;
    int tempoescudo = rand()%5 + 5, expirarescudo = 0;
    double timer_escudo, timer_inicial_escudo;

    struct esferas inimigos[30];
    for(int i=0; i<num_esferas; i++){
        gera_esfera(&inimigos[i]);
    }

    ALLEGRO_BITMAP* canhao = al_create_bitmap(100, 100);
    al_set_target_bitmap(canhao);
    al_draw_filled_triangle(0, 40, 40, 0, 0, 0, al_map_rgb(20, 120, 20));
    al_set_target_backbuffer(janela);


    int tiro_ativo = 0;
    float x_projetil, y_projetil, x_inicial_projetil, y_inicial_projetil;
    float timer_inicial_tiro = 0, timer_tiro = 0;

    int missil_ativo = 0, gera_missil = 0;
    float x_missil, y_missil, x_inicial_missil, y_inicial_missil;
    int *direcaox_projetil = 1, *direcaoy_projetil = 1;
    int cont_colisao_inimigo = 0, cont_colisao_parede = 0;
    int reduzvelocidade =0;
    float tempo_reducao_velocidade=0, tempo_inicial_reducao_velocidade=0;


    while (rodando && jogo) {
        while (!al_is_event_queue_empty(fila_de_eventos)) {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_de_eventos, &evento);

            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                rodando = 0;
            }
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
                mouseX = evento.mouse.x;
                mouseY = evento.mouse.y;
            }
            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (pararjogo == 1) {
                    if (mouseX > tela_x/2-130 && mouseX < tela_x/2+130 && mouseY > tela_y/2+75 && mouseY < tela_y/2+175){
                       reset = 1;
                    }
                }
                else{
                    if(tiro_ativo == 0){
                        timer_tiro = al_get_time();
                        if(timer_tiro - timer_inicial_tiro >= 1){
                            tiro_ativo = 1;
                            gera_projetil(&x_inicial_projetil, &y_inicial_projetil, mouseX, mouseY, &x_projetil, &y_projetil);
                        }
                    }
                }
            }
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (evento.keyboard.keycode) {

                    case ALLEGRO_KEY_SPACE:
                        if(escudos_disponiveis > 0){
                            ativarescudo = 1;
                            escudos_disponiveis--;
                            tempoescudo = rand()%5 + 5;
                            timer_inicial_escudo = al_get_time();
                        }
                        break;

                    case ALLEGRO_KEY_ESCAPE:
                        if(pararjogo == -1){
                            if(pausas_disponiveis > 0){
                                pausas_disponiveis--;
                                pararjogo = pararjogo * -1;
                                pausado = pausado * -1;
                            }
                        }
                        else{
                                pararjogo = pararjogo * -1;
                                pausado = pausado * -1;
                        }
                        break;
                }
            }

        }

        al_clear_to_color(al_map_rgb(10, 43, 97));

        if(pararjogo<0){
            tempo_anterior = tempo_atual;
            tempo_atual = al_get_time();


            if(ativarescudo == 1){
                al_draw_filled_circle(tela_x/2, tela_y/2, raio_escudo, al_map_rgb(9,133,135));
                timer_escudo = al_get_time();
                if(timer_escudo - timer_inicial_escudo >= tempoescudo){
                    expirarescudo = 1;
                }
            }
            if(expirarescudo == 1){
                funcaoexpirarescudo(&raio_escudo, &expirarescudo, &ativarescudo);
            }


            al_draw_filled_circle(tela_x/2, tela_y/2, raio_jogador, al_map_rgb(57,204,253));
            float angulo = atan2(mouseY - tela_y/2, mouseX - tela_x/2);
            al_draw_arc(tela_x/2, tela_y/2, 50, angulo-pi/2, pi, al_map_rgb(20,200,20), 3);
            al_draw_rotated_bitmap(canhao, 40, 40, tela_x/2, tela_y/2, angulo - pi/4, 0);


            for(int i=0; i<num_esferas; i++){
                verifica_colisao_esfera(&inimigos[i], velocidade, mouseX, mouseY, &pontos_jogador, &raio_jogador, ativarescudo, raio_escudo, &gera_missil);
            }


            verifapassagemdenivel(pontos_jogador, &copiapontos, &fase, fonte, &levelup, &velocidade, &num_esferas, &vidas_jogador, &pausas_disponiveis, &escudos_disponiveis, &inimigos[num_esferas]);
            if(levelup == 1){
                al_draw_text(fonte, al_map_rgb(255,255,255), tela_x/2, ylevelup+=5, ALLEGRO_ALIGN_CENTER, "LEVEL UP!");
            }
            if(ylevelup >= tela_y+20){
                levelup = 0;
                ylevelup = -20;
            }


            if(tiro_ativo==1){
                al_draw_filled_circle(x_projetil, y_projetil, 7, al_map_rgb(20, 120, 20));
                movimenta_projetil(&x_inicial_projetil, &y_inicial_projetil, &x_projetil, &y_projetil);
                verifica_colisao_projetil(&x_projetil, &y_projetil, &inimigos, num_esferas, &tiro_ativo, &timer_inicial_tiro, &pontos_jogador, &raio_jogador, &gera_missil);
            }
            if(gera_missil == 1){
                gera_projetil(&x_inicial_missil, &y_inicial_missil, mouseX, mouseY, &x_missil, &y_missil);
                gera_missil = 0;
                missil_ativo = 1;
            }
            if(missil_ativo==1){
                al_draw_filled_circle(x_missil, y_missil, 15, al_map_rgb(20,200,20));
                movimenta_missil(&x_inicial_missil, &y_inicial_missil, &x_missil, &y_missil, &direcaox_projetil, &direcaoy_projetil);
                verifica_colisao_missil(&x_missil, &y_missil, &inimigos, num_esferas, &missil_ativo, &pontos_jogador, &gera_missil, &direcaox_projetil, &direcaoy_projetil, &cont_colisao_inimigo, &cont_colisao_parede, &reduzvelocidade, &tempo_inicial_reducao_velocidade);
            }
            if(reduzvelocidade ==1){
                velocidade = 0.004 * 0.75;
                tempo_reducao_velocidade = al_get_time();
                if(tempo_reducao_velocidade - tempo_inicial_reducao_velocidade >= 5){
                    reduzvelocidade = 0;
                    velocidade = 0.004;
                }
            }


            if(gerar_jogador == 1){
                animacao_gerar_jogador(&raio_jogador, &gerar_jogador);
            }


            while(tempo_atual - tempo_anterior < 1.0/60){
                tempo_atual = al_get_time();
            }

        }

        desenha_esfera(num_esferas, inimigos);


        if(floor(raio_jogador)<=0){
            vidas_jogador--;
            raio_jogador = 1;
            gerar_jogador = 1;
        }
        if(vidas_jogador == 0){
            pararjogo = 1;
            al_draw_text(fonte, al_map_rgb(255,255,255), tela_x/2, tela_y/2, ALLEGRO_ALIGN_CENTER, "GAME OVER");
           botaoreset(&reset, mouseX, mouseY, &pontos_jogador, &raio_jogador, &vidas_jogador, &fase, &tempo_inicio, &num_esferas, &velocidade, &escudos_disponiveis, &pausas_disponiveis, &pararjogo, &pausado, &inimigos, fonte, &ativarescudo, &tiro_ativo, &gerar_jogador, &missil_ativo);
        }
        if(floor(raio_jogador) >= 50){
            pararjogo = 1;
            al_draw_text(fonte, al_map_rgb(255,255,255), tela_x/2, tela_y/2, ALLEGRO_ALIGN_CENTER, "VOCE VENCEU!");
            botaoreset(&reset, mouseX, mouseY, &pontos_jogador, &raio_jogador, &vidas_jogador, &fase, &tempo_inicio, &num_esferas, &velocidade, &escudos_disponiveis, &pausas_disponiveis, &pararjogo, &pausado, &inimigos, fonte, &ativarescudo, &tiro_ativo, &gerar_jogador, &missil_ativo);
        }
        if(pausado == 1){
            al_draw_text(fonte, al_map_rgb(255,255,255), tela_x/2, tela_y/2, ALLEGRO_ALIGN_CENTER, "JOGO PAUSADO");
            botaoreset(&reset, mouseX, mouseY, &pontos_jogador, &raio_jogador, &vidas_jogador, &fase, &tempo_inicio, &num_esferas, &velocidade, &escudos_disponiveis, &pausas_disponiveis, &pararjogo, &pausado, &inimigos, fonte, &ativarescudo, &tiro_ativo, &gerar_jogador, &missil_ativo);
        }


        al_draw_filled_rectangle(0, 0, tela_x, 25, al_map_rgb(1,1,1));
        al_draw_textf(fonte, al_map_rgb(255,255,255), 10, 10, ALLEGRO_ALIGN_LEFT, "Pontos: %d     Vidas: %d     Fase: %d     Pausa: %d     Escudo: %d    Tempo: %.2fs", pontos_jogador, vidas_jogador, fase, pausas_disponiveis, escudos_disponiveis, tempo_atual - tempo_inicio);
        al_flip_display();
    }

    al_destroy_display(janela);
    al_destroy_event_queue(fila_de_eventos);

    return 0;
}
