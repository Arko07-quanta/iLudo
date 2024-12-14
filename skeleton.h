#include "iGraphics.h"
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;
#define CELL_SIZE 50
#define IGNC 16777215


Image rolls[6];
Image home, newGame, vsComp, Play2, Play4, settings, ext;

void loadResources(){
    for(int i=0; i<6; i++){
    char num_str[25];
    sprintf(num_str,"assets/dice_roll/%d.png",i+1);
    iLoadImage(&rolls[i],num_str);
    }
    iLoadImage(&home, "assets/home.jpg");
    iLoadImage(&newGame, "assets/game_buttons/newgame.png");
    iLoadImage(&vsComp, "assets/game_buttons/vsComp.png");
    iLoadImage(&Play2, "assets/game_buttons/2player.png");
    iLoadImage(&Play4, "assets/game_buttons/4Player.png");
    iLoadImage(&settings, "assets/game_buttons/settings.png");
    iLoadImage(&ext, "assets/game_buttons/ext.png");
    return;
}

typedef struct{
    int active = 0;
    int path[4][58];
    int cur_pos[4] = {0};
}player;

typedef struct{
    int is_safe = 0;
    double x,y;
    vector<int> piece;
}cell;


char board[] = "assets/ludo_board.bmp";
char color_piece[4][100] = {"assets/red_piece.bmp","assets/green_piece.bmp","assets/yellow_piece.bmp","assets/blue_piece.bmp"};
char place_left[] = "assets/placeholder_left.bmp";
char place_right[] = "assets/placeholder_right.bmp";
char background[] = "assets/iLudo_Background.bmp";
char background_2[] = "assets/background_2.bmp";
char game_background[] = "assets/game_background.bmp";
char start_page[] = "assets/home_page.bmp";
//char rolls[6][25] = {"assets/dice_roll/1.png","assets/dice_roll/2.png","assets/dice_roll/3.png","assets/dice_roll/4.png","assets/dice_roll/5.png","assets/dice_roll/6.png"};

pair<double,double> place_holder[4] = {{100,50},{100,700},{1020,700},{1020,50}};
vector<int> win_list;

cell cells[92];

player players[4];


void drawBoard(){
    iShowBMP(0,0,game_background);
    iShowBMP(200,20,board);
    iShowBMP2(50,20,place_left,IGNC);
    iShowBMP2(50,750+20-100,place_left,IGNC);
    iShowBMP2(200+750+50,20,place_right,IGNC);
    iShowBMP2(200+750+50,750-100+20,place_right,IGNC);
}

void init(int n){
    cells[0].x = 101; cells[0].y = 106; cells[1].x = 201; cells[1].y = 106; cells[2].x = 201; cells[2].y = 206; cells[3].x = 101; cells[3].y = 206; cells[4].x = 101; cells[4].y = 556;
    cells[5].x = 201; cells[5].y = 556; cells[6].x = 201; cells[6].y = 646; cells[7].x = 101; cells[7].y = 646; cells[8].x = 551; cells[8].y = 556; cells[9].x = 651; cells[9].y = 556;
    cells[10].x = 651; cells[10].y = 646; cells[11].x = 551; cells[11].y = 646; cells[12].x = 551; cells[12].y = 106; cells[13].x = 651; cells[13].y = 106; cells[14].x = 651; cells[14].y = 196;
    cells[15].x = 551; cells[15].y = 196;

    cells[16].x = 300; cells[16].y = 50; cells[17].x = 300; cells[17].y = 100; cells[18].x = 300; cells[18].y = 150; cells[19].x = 300; cells[19].y = 200; cells[20].x = 300; cells[20].y = 250;
    cells[21].x = 250; cells[21].y = 300; cells[22].x = 200; cells[22].y = 300; cells[23].x = 150; cells[23].y = 300; cells[24].x = 100; cells[24].y = 300; cells[25].x = 50; cells[25].y = 300;
    cells[26].x = 0; cells[26].y = 300; cells[27].x = 0; cells[27].y = 350; cells[28].x = 0; cells[28].y = 400; cells[29].x = 50; cells[29].y = 400; cells[30].x = 100; cells[30].y = 400;
    cells[31].x = 150; cells[31].y = 400; cells[32].x = 200; cells[32].y = 400; cells[33].x = 250; cells[33].y = 400; cells[34].x = 300; cells[34].y = 450; cells[35].x = 300; cells[35].y = 500;
    cells[36].x = 300; cells[36].y = 550; cells[37].x = 300; cells[37].y = 600; cells[38].x = 300; cells[38].y = 650; cells[39].x = 300; cells[39].y = 700; cells[40].x = 350; cells[40].y = 700;
    cells[41].x = 400; cells[41].y = 700; cells[42].x = 400; cells[42].y = 650; cells[43].x = 400; cells[43].y = 600; cells[44].x = 400; cells[44].y = 550; cells[45].x = 400; cells[45].y = 500;
    cells[46].x = 400; cells[46].y = 450; cells[47].x = 450; cells[47].y = 400; cells[48].x = 500; cells[48].y = 400; cells[49].x = 550; cells[49].y = 400; cells[50].x = 600; cells[50].y = 400;
    cells[51].x = 650; cells[51].y = 400; cells[52].x = 700; cells[52].y = 400; cells[53].x = 700; cells[53].y = 350; cells[54].x = 700; cells[54].y = 300; cells[55].x = 650; cells[55].y = 300;
    cells[56].x = 600; cells[56].y = 300; cells[57].x = 550; cells[57].y = 300; cells[58].x = 500; cells[58].y = 300; cells[59].x = 450; cells[59].y = 300; cells[60].x = 400; cells[60].y = 250;
    cells[61].x = 400; cells[61].y = 200; cells[62].x = 400; cells[62].y = 150; cells[63].x = 400; cells[63].y = 100; cells[64].x = 400; cells[64].y = 50; cells[65].x = 400; cells[65].y = 0;
    cells[66].x = 350; cells[66].y = 0; cells[67].x = 300; cells[67].y = 0;

    cells[68].x = 350; cells[68].y = 50; cells[69].x = 350; cells[69].y = 100; cells[70].x = 350; cells[70].y = 150; cells[71].x = 350; cells[71].y = 200; cells[72].x = 350; cells[72].y = 250;
    cells[73].x = 50; cells[73].y = 350; cells[74].x = 100; cells[74].y = 350; cells[75].x = 150; cells[75].y = 350; cells[76].x = 200; cells[76].y = 350; cells[77].x = 250; cells[77].y = 350;
    cells[78].x = 350; cells[78].y = 650; cells[79].x = 350; cells[79].y = 600; cells[80].x = 350; cells[80].y = 550; cells[81].x = 350; cells[81].y = 500; cells[82].x = 350; cells[82].y = 450;
    cells[83].x = 650; cells[83].y = 350; cells[84].x = 600; cells[84].y = 350; cells[85].x = 550; cells[85].y = 350; cells[86].x = 500; cells[86].y = 350; cells[87].x = 450; cells[87].y = 350;

    cells[88].x = 350; cells[88].y = 300; cells[89].x = 300; cells[89].y = 350; cells[90].x = 350; cells[90].y = 400; cells[91].x = 400; cells[91].y = 350;

    for(int i=0; i<92; i++) cells[i].x += 200, cells[i].y += 20;
    for(int i=0; i<16; i++) cells[i].x -= 25, cells[i].y -= 25;


    players[0].path[0][0] = 0; players[0].path[1][0] = 1; players[0].path[2][0] = 2; players[0].path[3][0] = 3;
    players[1].path[0][0] = 4; players[1].path[1][0] = 5; players[1].path[2][0] = 6; players[1].path[3][0] = 7;
    players[2].path[0][0] = 8; players[2].path[1][0] = 9; players[2].path[2][0] = 10; players[2].path[3][0] = 11;
    players[3].path[0][0] = 12; players[3].path[1][0] = 13; players[3].path[2][0] = 14; players[3].path[3][0] = 15;

    for(int i=1; i<52; i++){
        for(int j=0; j<4; j++) players[0].path[j][i] = 16+i-1;
    }
    for(int i=1; i<52; i++){
        for(int j=0; j<4; j++) players[1].path[j][i] = (13+i-1)%52+16;
    }
    for(int i=1; i<52; i++){
        for(int j=0; j<4; j++) players[2].path[j][i] = (26+i-1)%52+16;
    }
    for(int i=1; i<52; i++){
        for(int j=0; j<4; j++) players[3].path[j][i] = (39+i-1)%52+16;
    }

    for(int i=52; i<57; i++){
        for(int j=0; j<4; j++) players[0].path[j][i] = (68-52+i);
    }
    for(int i=52; i<57; i++){
        for(int j=0; j<4; j++) players[1].path[j][i] = (73-52+i);
    }
    for(int i=52; i<57; i++){
        for(int j=0; j<4; j++) players[2].path[j][i] = (78-52+i);
    }
    for(int i=52; i<57; i++){
        for(int j=0; j<4; j++) players[3].path[j][i] = (83-52+i);
    }

    for(int i=0; i<4; i++) players[0].path[i][57] = 88;
    for(int i=0; i<4; i++) players[1].path[i][57] = 89;
    for(int i=0; i<4; i++) players[2].path[i][57] = 90;
    for(int i=0; i<4; i++) players[3].path[i][57] = 91;

    if(n==4) {
        for(int i=0; i<4; i++) players[i].active = 1;
        for(int i=0; i<16; i++) cells[i].piece.push_back(i/4);
    }
    if(n==3){
        for(int i=0; i<3; i++) players[i].active = 1;
        players[3].active = 0;
        for(int i=0; i<12; i++) cells[i].piece.push_back(i/4);
    }
    if(n==2) {
        players[0].active = 1, players[2].active = 1;
        players[1].active = 0, players[3].active = 0;
        for(int i=0; i<4; i++) cells[i].piece.push_back(0);
        for(int i=8; i<12; i++) cells[i].piece.push_back(2);
    }

    for(int i=0; i<15; i++) cells[i].is_safe = 1;
    cells[16].is_safe = cells[29].is_safe = cells[42].is_safe = cells[55].is_safe = cells[24].is_safe = cells[37].is_safe = cells[50].is_safe = cells[63].is_safe = 1;

}

int player_move(int cur_player, int pi, int dice){
    int pos = players[cur_player].cur_pos[pi];
    //printf("initial pos in the array : %d\n",pos);
    //printf("current pos of player %d : %d\n",pi,players[cur_player].path[pi][pos]);
    if(pos==0){
        if(dice==6){
            if(!cells[players[cur_player].path[pi][pos]].piece.empty()) cells[players[cur_player].path[pi][pos]].piece.pop_back();
            pos += 1;
            players[cur_player].cur_pos[pi] += 1;
            cells[players[cur_player].path[cur_player][pos]].piece.push_back(cur_player);
            return 1;
            //printf("player moved to : %lf %lf\n",cells[players[cur_player].path[cur_player][pos]].x, cells[players[cur_player].path[cur_player][pos]].y);
        }
    }
    else if(pos+dice<=57){
        if(!cells[players[cur_player].path[pi][pos]].piece.empty()) cells[players[cur_player].path[pi][pos]].piece.erase(find(cells[players[cur_player].path[pi][pos]].piece.begin(), cells[players[cur_player].path[pi][pos]].piece.end(),cur_player));
        pos += dice;
        players[cur_player].cur_pos[pi] += dice;
        cells[players[cur_player].path[cur_player][pos]].piece.push_back(cur_player);
        if(pos == 57) return 0;
        return 1;
        //printf("player %d moved to : %lf %lf\n",cur_player, cells[players[cur_player].path[cur_player][pos]].x, cells[players[cur_player].path[cur_player][pos]].y);
    }
    //printf("pos in the arr : %d\n",pos);
    //printf("moved pos of player %d : %d\n",pi,players[cur_player].path[pi][pos]);
    return 0;

}

int collision_check(int cur_player, int pi, int dice){
    int pos = players[cur_player].cur_pos[pi];
    if(pos+dice>57) return 0;
    if(pos == 0) return 0;
    pos += dice;
    if(cells[players[cur_player].path[pi][pos]].is_safe) return 0;
    for(int i=0; i<4; i++){
        if(i==cur_player) continue;
        for(int j=0; j<4; j++){
            if(players[i].path[i][players[i].cur_pos[j]] == players[cur_player].path[pi][pos]){
                players[i].cur_pos[j] = 0;
                cells[players[i].path[j][players[i].cur_pos[j]]].piece.push_back(i);
                cells[players[cur_player].path[pi][pos]].piece.pop_back();
                return 1;
            }
        }
    }
    return 0;
}

int roll_dice(){
    int a = rand()%6 + 1;
    return a;
}

void draw_cell(int n){
    int offset = CELL_SIZE/4 - 4*(cells[n].piece.size()-1);
    for(int i=0; i<cells[n].piece.size(); i++){
        iShowBMP2(cells[n].x+offset,cells[n].y+offset,color_piece[cells[n].piece[i]],IGNC);
        offset += 4;
        //printf("%d ",cells[n].piece[i]);
    }//puts("");
}

void draw_state(){
    for(int i=0; i<92; i++) draw_cell(i);
}

int is_winner(int n){
    for(int i=0; i<4; i++){
        if(players[n].cur_pos[i] != 57) return 0;
    }
    players[n].active = 0;
    return 1;
}

void display_move(int a, int ph){
    for(int i=0; i<6; i++){
        iShowImage(place_holder[ph].first, place_holder[ph].second,&rolls[i]);
    }
    iShowImage(place_holder[ph].first,place_holder[ph].second,&rolls[a-1]);
    return;
}

int get_piece(int mx, int my, int cur_player){

    printf("%d %d\n",mx,my);
    for(int i=0; i<4; i++){
        int x = cells[players[cur_player].path[i][players[cur_player].cur_pos[i]]].x;
        int y = cells[players[cur_player].path[i][players[cur_player].cur_pos[i]]].y;
        //printf("%i %d %d\n",i,x,y);
        if(mx>=x && my>=y && mx<x+CELL_SIZE && my<y+CELL_SIZE){
            //printf("%d \n",i);
            return i;
        }
    }

    return -1;
}


int check_valid_moves(int cur_player, int a){
    if(a==6){
        for(int i=0; i<4; i++){
            if(players[cur_player].cur_pos[i]+a < 58) return 1;
        }
    }

    for(int i=0; i<4; i++){
        if(players[cur_player].cur_pos[i]>0) if(players[cur_player].cur_pos[i]+a<58) return 1;
    }

    return 0;
}





int comp_move(int cur_player, int dice){
    printf("Player %d played his move/\n",cur_player);
    for(int i=0; i<4; i++){
        if(collision_check(cur_player, i, dice)){
            player_move(cur_player, i, dice);
            return 0;
        }
    }
    if(dice == 6){
        for(int i=0; i<4; i++){
            if(players[cur_player].cur_pos[i] == 0){
                player_move(cur_player,i,dice);
                return 0;
            }
        }
        int pi = rand()%4;
        while(players[cur_player].cur_pos[pi]==0 && players[cur_player].cur_pos[pi]+dice>57){
            pi = rand()%4;
        }
        player_move(cur_player,pi,dice);
        return 0;
    }
    for(int i=0; i<4; i++){
        if(players[cur_player].cur_pos[i]+dice == 57){
            player_move(cur_player,i,dice);
            return 0;
        }
    }

    int pi = rand()%4;
    while(players[cur_player].cur_pos[pi]==0 && players[cur_player].cur_pos[pi]+dice>57){
        pi = rand()%4;
    }
    player_move(cur_player,pi,dice);
    return 1;
}

