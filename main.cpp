#include <raylib.h> 
#include <stdlib.h>
#include <ctime>

class Script {
public:    
    char scenes[9][100] = {"", "Ei! Voce! Prestou atencao na aula?", "...", "RESPONDA-ME! OU O COOKIE CLICKER TE ENSINOU MAIS?", "E-Eu... Desculpa... ", "JÁ SEI, VAMOS JOGAR UM JOGO.", "OUÇA-ME BEM. ACERTE TODAS AS QUESTOES E VENÇA. OU...  ", "Ou o quê?", "OU EU TE **** AQUI MESMO, SEU ***** ** ****!"};
    int pointer = 0;
    bool inScene = false;
    
    int getPointer() {
        return this->pointer;
    }
    
    void increasePointer() {
        pointer += 1; 
    }
};

class Game {
public:    
    bool start = false;
    int status = 0;
    int correctAnswers = 0;
    bool changeSound = false;
    
    int getCorrectAswers() {
        return this->correctAnswers;
    }
    
    void increaseCorrectAnswers() {
        this->correctAnswers += 1;
    }
    
    int getStatus() {
        return this->status;
    }
    
    void setStatus(int newStatus) {
        this->status = newStatus;
    }
};


class Character { 
public:
    int x; 
    int y;
    Texture sprite;
    
    void beDrawn() {
        DrawTexture(this->sprite, this->x, this->y, WHITE);
    }
    
    void beDrawn(int x, int y) {
        DrawTexture(this->sprite, x, y, WHITE);
    }
    
    void beDrawn(Texture sprite, int x, int y) {
        DrawTexture(sprite, x, y, WHITE);
    }
    
    void moveFoward(){
        if (x >= 1100) { 
            x = 1100;           /* Auto-mensagem */
        }
        else {
            x += 5; 
        }
    }
    
    void moveBackward() {
        if (x <= -50) {       /* Auto-mensagem */
            x = -50;
        }
        else {
            x -= 5;
        }
        
    }
    
    void moveUp() {
         if (y == 240) {      /* Auto-mensagem */
            y =240;
        }
        
        else {
            y -= 5;
        }
    }
    
    void moveDown() {
        if (y >= 490)  {     /* Auto-mensagem */
            y =490;
        }
        else {
            y += 5;
        }
    }
    
}; 

int main(){
    /* window settings */
    const int widthScreen = 1280;
    const int heightScreen = 720;
    InitWindow(widthScreen, heightScreen, "Jogo Diagrama de Sequencia");
    SetTargetFPS(60); 
    InitAudioDevice();
    
    /* sprites */
    Texture bg, protSprite, profSprite, letSprite, selectedLetSprite;
    bg = LoadTexture("./sprites/scenary/bg.png");
    protSprite = LoadTexture("./sprites/positions/up1.png");
    profSprite = LoadTexture("./sprites/character/professor2.png");
    letSprite = LoadTexture("./sprites/scenary/letter.png");
    selectedLetSprite = LoadTexture("./sprites/scenary/letterSelected.png");
    
    /* objects */
    Script scrpt;
    Character protagonist = {.x=500, .y=600, .sprite=protSprite};           /* Mensagem de criação de participante */
    Character professor = {.x=-10, .y=-10, .sprite=profSprite};             /* Mensagem de criação de participante */
    Character letter1 = {.x=-15, .y=-15, .sprite=letSprite};                /* Mensagem de criação de participante */
    Character letter2 = {.x=-15, .y=-15, .sprite=letSprite};                /* Mensagem de criação de participante */
    Character letter3 = {.x=-15, .y=-15, .sprite=letSprite};                /* Mensagem de criação de participante */
    Game game;                                                              /* Mensagem de criação de participante */
    
    /* sounds */
    Sound siren = LoadSound("./soundtrack/school-bell.mp3");
    Sound speach = LoadSound("./soundtrack/1.wav");
    Sound music = LoadSound("./soundtrack/music.mp3");
    Sound gameover = LoadSound("./soundtrack/gameover.mp3");
    
    /* initial songs  */
    PlaySound(siren);
    PlaySound(music);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        
        
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){         /* Mensagem Síncrona. Condição de guarda: pressionar tecla */
              protagonist.sprite = LoadTexture("./sprites/positions/up2.png");
              protagonist.moveUp();
    }
    
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){                                   /* Mensagem Síncrona */
            protagonist.sprite = LoadTexture("./sprites/positions/down2.png");
            protagonist.moveDown();
    }
    
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){                                  /* Mensagem Síncrona */
            protagonist.sprite = LoadTexture("./sprites/positions/right2.png");
            protagonist.moveFoward();
    }
    
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){                                       /* Mensagem Síncrona */
            protagonist.sprite = LoadTexture("./sprites/positions/left2.png");         
            protagonist.moveBackward();
    }
    
        if (game.start == false) { /* Se o jogo nao tiver começado.. */
        
        if (IsKeyPressed(KEY_SPACE)){                                                         /* Mensagem Síncrona */
            scrpt.increasePointer();
            scrpt.inScene = true;
        }
        
        /* events */
        if (protagonist.x == 1100) {
            protagonist.sprite = LoadTexture("./sprites/positions/left1.png");
            if (scrpt.getPointer() >= 1 ) {
            }
            else {
                PlaySound(speach);
                scrpt.increasePointer();
            }
        }
        
        
        if (scrpt.getPointer() == 1) {                                                  /* Mensagem Síncrona */
            professor.beDrawn(530, 240);
            protagonist.sprite = LoadTexture("./sprites/positions/left1.png");
            DrawText(scrpt.scenes[scrpt.getPointer()],widthScreen/4, 50, 30,BLACK);
            DrawText("aperte espaço para pular",widthScreen/4, 80, 15,BLACK);
            
            
            if (scrpt.inScene == true) {                                                /* Mensagem Síncrona */
                speach = LoadSound("./soundtrack/1.wav");
                PlaySound(speach);
                scrpt.inScene = false; 
            }
            
        }
        
        
        if (scrpt.getPointer() == 2) {                                                  /* Mensagem Síncrona */
            professor.beDrawn(530, 240);
            protagonist.sprite = LoadTexture("./sprites/positions/left1.png");
            DrawText(scrpt.scenes[scrpt.getPointer()],widthScreen/4, 50, 30,WHITE);
            DrawText("aperte espaço para pular",widthScreen/4, 80, 15,BLACK);
            
            if (scrpt.inScene == true) {                                                /* Mensagem Síncrona */
            speach = LoadSound("./soundtrack/2.wav");
            PlaySound(speach);
            scrpt.inScene = false;
            }
        }
        
        if (scrpt.getPointer() == 3) {                                               /* Mensagem Síncrona */
            professor.beDrawn(530, 240);
            protagonist.sprite = LoadTexture("./sprites/positions/left1.png");
            DrawText(scrpt.scenes[scrpt.getPointer()],widthScreen/6, 50, 30,BLACK);
            DrawText("aperte espaço para pular",widthScreen/6, 80, 15,BLACK);
            
            if (scrpt.inScene == true) {                                            /* Mensagem Síncrona */
            speach = LoadSound("./soundtrack/3.wav");
            PlaySound(speach);                                                      /* Mensagem Assíncrona */
            scrpt.inScene = false;
            }
        }
        
         if (scrpt.getPointer() == 4) {                                             /* Mensagem Síncrona */
            professor.beDrawn(530, 240);
            protagonist.sprite = LoadTexture("./sprites/positions/left1.png");
            DrawText(scrpt.scenes[scrpt.getPointer()], 420, 50, 30,WHITE);
            DrawText("aperte espaço para pular",420, 80, 15,BLACK);
            
            
            if (scrpt.inScene == true) {                                            /* Mensagem Síncrona */
            speach = LoadSound("./soundtrack/4.wav");
            PlaySound(speach);                                                      /* Mensagem Assíncrona */
            scrpt.inScene = false;
            }
        }
        
        if (scrpt.getPointer() == 5) {                                             /* Mensagem Síncrona */
            professor.beDrawn(530, 240);
            protagonist.sprite = LoadTexture("./sprites/positions/left1.png");
            DrawText(scrpt.scenes[scrpt.getPointer()],420, 50, 30,BLACK);
            DrawText("aperte espaço para pular",420, 80, 15,BLACK);
            
            if (scrpt.inScene == true) {                                            /* Mensagem Síncrona */
            speach = LoadSound("./soundtrack/5.mp3");
            PlaySound(speach);  /* Mensagem Assíncrona */
            scrpt.inScene = false;
            }
        }
        
        if (scrpt.getPointer() == 6) {                                              /* Mensagem Síncrona */
            professor.beDrawn(530, 240);
            protagonist.sprite = LoadTexture("./sprites/positions/left1.png");
            DrawText(scrpt.scenes[scrpt.getPointer()],widthScreen/7, 50, 30,BLACK);
            DrawText("aperte espaço para pular",widthScreen/7, 80, 15,BLACK);
            
            if (scrpt.inScene == true) {                                            /* Mensagem Síncrona */
            speach = LoadSound("./soundtrack/6.mp3");
            PlaySound(speach); 
            scrpt.inScene = false;
            }
        }
        
        if (scrpt.getPointer() == 7) {                                               /* Mensagem Síncrona */
            professor.beDrawn(530, 240);
            protagonist.sprite = LoadTexture("./sprites/positions/left1.png");
            DrawText(scrpt.scenes[scrpt.getPointer()],420, 50, 30,WHITE);
            DrawText("aperte espaço para pular",420, 80, 15,BLACK);
            
            if (scrpt.inScene == true) {                                              /* Mensagem Síncrona */
            speach = LoadSound("./soundtrack/7.mp3");
            PlaySound(speach); 
            scrpt.inScene = false;
            }
        }
        
        if (scrpt.getPointer() == 8) {                                                  /* Mensagem Síncrona */
            professor.beDrawn(profSprite, 530, 240);
            protagonist.sprite = LoadTexture("./sprites/positions/left1.png");
            DrawText(scrpt.scenes[scrpt.getPointer()],widthScreen/6, 50, 30,RED);
            DrawText("aperte espaço para pular",widthScreen/6, 80, 15,RED);
            
            if (scrpt.inScene == true) {                                            /* Mensagem Síncrona */
            speach = LoadSound("./soundtrack/8.mp3");
            PlaySound(speach); 
            scrpt.inScene = false;
            bg = LoadTexture("./sprites/scenary/bg-game.png");
            profSprite = LoadTexture("./sprites/character/professorAngry2.png");
            } 
        }
        
        protagonist.beDrawn();
        
        if (scrpt.getPointer() == 9) {
            game.start = true;
            }
        }
        
        
    
        else { 
            if (game.getStatus() == 0) {
            professor.beDrawn(profSprite, 200, 240);                            /* Mensagem Assíncrona */
            protagonist.beDrawn();                                              /* Mensagem Assíncrona */
            DrawText("aperte ESPAÇO no item desejado",550, 700, 15,WHITE);
            
            if (game.correctAnswers == 0) {
                DrawText("O que é um diagrama UML?",widthScreen/4, 40, 15,RED);
                DrawText("A) Um método de treinamento de IA. ",widthScreen/4, 60, 14,WHITE);                 
                DrawText("B) Um cálculo complexo para armazenamento de dados e carga. ",widthScreen/4, 80, 14,WHITE);
                DrawText("C) Uma linguagem de notação para uso em projetos de sistema. ",widthScreen/4, 100, 14,WHITE);
            }
            if (game.correctAnswers == 1) {
                DrawText("Qual é o principal objetivo de um diagrama de sequência UML?",widthScreen/4, 40, 15,RED);
                DrawText("A) Representar a estrutura estática de um sistema. ",widthScreen/4, 60, 14,WHITE);                 
                DrawText("B) Descrever a interação entre objetos ao longo do tempo ",widthScreen/4, 80, 14,WHITE);
                DrawText("C) Ilustrar a distribuição física dos componentes do sistema. ",widthScreen/4, 100, 14,WHITE);
            }
            if (game.correctAnswers == 2) {
                DrawText("O que é representado pelos lifelines em um diagrama de sequência UML?",widthScreen/4, 40, 15,RED);
                DrawText("A) Descrever a interação entre objetos ao longo do tempo. ",widthScreen/4, 60, 14,WHITE);                 
                DrawText("B) Os relacionamentos entre as classes no sistema. ",widthScreen/4, 80, 14,WHITE);
                DrawText("C) As classes e seus atributos. ",widthScreen/4, 100, 14,WHITE);
            }
            
            if (protagonist.x <=300 && protagonist.x >= 100) {
                letter1.beDrawn(selectedLetSprite, 300, 120);
                DrawText("A", 328, 240, 40 ,WHITE);
                if (IsKeyPressed(KEY_SPACE)) {
                    if (game.getCorrectAswers() == 2) {
                        game.increaseCorrectAnswers();
                    }
                    else {
                        game.setStatus(1);
                    }
                }
            }
            else {
                letter1.beDrawn(300, heightScreen/3);
            }
            
            if (protagonist.x <=600 && protagonist.x >= 300) {
                letter2.beDrawn(selectedLetSprite, 600, 120);
                DrawText("B", 628, 240, 40 ,WHITE);
                if (IsKeyPressed(KEY_SPACE)) {
                    if (game.getCorrectAswers() == 1) {
                        game.increaseCorrectAnswers();
                    }
                    else {
                        game.setStatus(1);
                    }
                }
            }
            else {
                letter2.beDrawn(600, heightScreen/3);
            }
            
            if (protagonist.x <=900 && protagonist.x >= 600) {
                letter3.beDrawn(selectedLetSprite, 900, 120);
                DrawText("C", 928, 240, 40 ,WHITE);
                if (IsKeyPressed(KEY_SPACE)) {
                    if (game.getCorrectAswers() == 0) {
                        game.increaseCorrectAnswers();
                    }
                    else {
                        game.setStatus(1);
                    }
                }
            }
            else {
                letter3.beDrawn(900, heightScreen/3);
            }
            
            
            if (game.getCorrectAswers() == 3) {
                game.setStatus(2);
            } }
            
            else if (game.getStatus() == 1) {
                DrawText("GAME OVER!", 20, 130, 50, WHITE);
                bg = LoadTexture("./sprites/scenary/gameOver.png");
                
                if (game.changeSound == false) {
                    UnloadSound(music);
                    PlaySound(gameover);
                    game.changeSound = true;
                }
            }
            
            else {
                DrawText("Venceu!", 20, 130, 50, WHITE);
            }
        }   
        
        EndDrawing();
    }
    
    return 0;
     
}