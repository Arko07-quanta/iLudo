# include "skeleton.h"


int gamestate = 0;
int cur_player = 0;
int ph = 0;
int a,n;
int flag = 0;
int button_state = 0;
int dice_cnt = 0;
int snd_flag = 1;
int pre_gamestate;


int player_type[4] = {1,0,0,0};



/*
	function iDraw() is called again and again by the system.

	*/
void iDraw() {
	if(gamestate == 0){
		iClear();
		iShowImage(0,0,&home);
		iShowImage(1000,500,&newGame);
		iShowImage(1000,440,&vsComp);
		iShowImage(1000,380,&settings);
	}
	else if(gamestate == 1){
		iClear();
		iShowImage(0,0,&home);
		iShowImage(110,500,&Play2);
		iShowImage(110,440,&Play4);
	}
	else if(gamestate == 2){
		iClear();
		iShowImage(0,0,&home);
		iShowImage(110,500,&Play2);
		iShowImage(110,440,&Play4);
	}
	else if(gamestate == 3){
		if(flag == 0) {
			n = 4;
			init(4);
			flag = 1;
		}
		iClear();
		drawBoard();
		draw_state();
		display_move(a,ph);
	}
	else if(gamestate == 4){
		if(flag == 0) {
			n = 2;
			init(2);
			flag = 1;
		}
		iClear();
		drawBoard();
		draw_state();
		display_move(a,ph);
	}
	else if(gamestate == 5){
		if(flag == 0){
			n = 4;
			init(4);
			for(int i=1; i<4; i++) player_type[i] = 0;
			flag = 1;
		}
		iClear();
		drawBoard();
		draw_state();
		display_move(a,ph);
	}
	else if(gamestate == 6){
		if(flag == 0){
			n = 2;
			init(2);
			flag = 1;
		}
		iClear();
		drawBoard();
		draw_state();
		display_move(a,ph);
	}
	else if(gamestate == 7){
		iClear();
		char winner[30];
		if(win_list[0] == 0) strcpy(winner,"RED");
		else if(win_list[0] == 1) strcpy(winner, "GREEN");
		else if(win_list[0] == 2) strcpy(winner, "YELLOW");
		else strcpy(winner, "BLUE");
		iText(550,350,"The winner is Player ",GLUT_BITMAP_TIMES_ROMAN_24);
		if(win_list[0] == 0) iSetColor(255,0,0);
		else if(win_list[0] == 1) iSetColor(0,255,0);
		else if(win_list[0] == 2) iSetColor(255,255,0);
		else iSetColor(0,0,255);
		iText(770,350,winner,GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if(gamestate == 8) {
		iShowBMP(0,0,game_background);
		iShowImage2(10,720,&back_button, IGNC);
		if(snd_flag) iShowImage2(100,400,&snd_on,IGNC);
		else iShowImage2(100,400,&snd_off,IGNC);
		char ins[100] = "Press b to get back to main menu during games.";
		iSetColor(200,200,200);
		iText(100,300,ins,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(100,250,"Press p to pause the game.",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(100,200,"Press r to resume the game.",GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if(gamestate == 9){
		drawBoard();
		iSetColor(10,10,10);
		iFilledRectangle(500,375,250,100);
		iSetColor(200,200,200);
		iText(525,450,"Game Paused",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(525,400,"Press r to continue",GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	//printf("x = %d, y= %d\n",mx,my);
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
	//printf("%d\n",state);
	//printf("%d %d %d\n",cur_player,ph, players[cur_player].active);
	if(gamestate == 0){
		if(button == GLUT_LEFT_BUTTON ) {
			if(mx>=1000 && my>=500 && mx<=1250 && my<=550) gamestate = 1;
		}
		if(button == GLUT_LEFT_BUTTON ){
			if(mx>=1000 && mx<=1250 && my>=440 && my<=490) gamestate = 2;
		}
		if(button == GLUT_LEFT_BUTTON){
			if(mx >= 1000 && mx <= 1250 && my >= 380 && my<=430) gamestate = 8;
		}
	}
	else if(gamestate == 1){
		if(button == GLUT_LEFT_BUTTON ) if(mx>=110 && mx<=360 && my >= 500 && my <= 550) gamestate = 4;
		if(button == GLUT_LEFT_BUTTON ) if(mx >=110 && mx<=360 && my>=440 && my <= 490) gamestate = 3;
	}
	else if(gamestate == 2){
		if(button == GLUT_LEFT_BUTTON && state ==  GLUT_UP) if(mx>=110 && mx<=360 && my >= 500 && my <= 550) {
			gamestate = 6;
			n = 2;
			init(2);
			flag = 1;
		}
		if(button == GLUT_LEFT_BUTTON ) if(mx>=110 && mx<=360 && my >= 440 && my <= 490) {
			gamestate = 5;
			n = 4;
			init(4);
			flag = 1;
		}
	}
	else if(gamestate == 3 || gamestate == 4) {
		while(players[ph].active == 0){
			ph = (ph+1)%4;
			cur_player = (cur_player+1)%4;
		}
		if(button == GLUT_LEFT_BUTTON ){
			if(button_state == 0){
				while(players[ph].active == 0){
					ph = (ph+1)%4;
					cur_player = (cur_player+1)%4;
				}
				if(place_holder[ph].first<=mx && place_holder[ph].second<=my && place_holder[ph].first+CELL_SIZE>mx && place_holder[ph].second+CELL_SIZE>my){
					a = roll_dice(dice_cnt);
					button_state = 1;
				}
			}

			else if(button_state==1){
				if(!check_valid_moves(cur_player,a)){
					cur_player = (cur_player+1)%4;
					ph = (ph+1)%4;
					while(players[ph].active == 0){
						cur_player = (cur_player+1)%4;
						ph = (ph+1)%4;
					}
					button_state = 0;
				}
				int pi = get_piece(mx,my,cur_player);
				if(pi != -1){
					int x = collision_check(cur_player, pi, a);
					int y = player_move(cur_player,pi,a);
					if(y==1 || y==2) button_state = 0;
					if(is_winner(cur_player)) {
						win_list.push_back(cur_player);
						players[cur_player].active = 0;
					}
					if(win_list.size() == n-1) gamestate = 7;
					if(x == 0 && a != 6 && y==1){
						cur_player = (cur_player+1)%4;
						ph = (ph+1)%4;
						while(players[ph].active == 0){
							cur_player = (cur_player+1)%4;
							ph = (ph+1)%4;
						}
					}
				}
			}
		}
	}
	else if(gamestate == 5 || gamestate == 6) {
		while(players[ph].active == 0){
			cur_player = (cur_player+1)%4;
			ph = (ph+1)%4;
		}
		if (player_type[cur_player]){
			while(players[ph].active == 0){
				cur_player = (cur_player+1)%4;
				ph = (ph+1)%4;
			}
			if(button == GLUT_LEFT_BUTTON ){
				if(button_state == 0){
					while(players[ph].active == 0){
						ph = (ph+1)%4;
						cur_player = (cur_player+1)%4;
					}
					if(place_holder[ph].first<=mx && place_holder[ph].second<=my && place_holder[ph].first+CELL_SIZE>mx && place_holder[ph].second+CELL_SIZE>my){
						a = roll_dice(dice_cnt);
						button_state = 1;
					}
				}

				if(button_state==1){
					if(!check_valid_moves(cur_player,a)){
						cur_player = (cur_player+1)%4;
						ph = (ph+1)%4;
						while(players[ph].active == 0){
							cur_player = (cur_player+1)%4;
							ph = (ph+1)%4;
						}
						button_state = 0;
					}
					int pi = get_piece(mx,my,cur_player);
					if(pi != -1){
						int x = collision_check(cur_player, pi, a);
						int y = player_move(cur_player,pi,a);
						if(y==1 || y==2) button_state = 0;
						if(is_winner(cur_player)) {
							win_list.push_back(cur_player);
							players[cur_player].active = 0;
						}
						if(win_list.size() == n-1) gamestate = 7;
						if(x == 0 && a != 6 && y==1){
							cur_player = (cur_player+1)%4;
							ph = (ph+1)%4;
							while(players[ph].active == 0){
								ph = (ph+1)%4;
								cur_player = (cur_player+1)%4;
							}
						}
					}
				}
			}
		}
		else if(!player_type[cur_player]){
			while(players[ph].active == 0){
				cur_player = (cur_player+1)%4;
				ph = (ph+1)%4;
			}
			a = roll_dice(dice_cnt);
			//Sleep(100);
			if(!check_valid_moves(cur_player,a)){
				cur_player = (cur_player+1)%4;
				ph = (ph+1)%4;
				while(players[ph].active == 0){
					ph = (ph+1)%4;
					cur_player = (cur_player + 1) %4;
				}
			}
			int x;
			if(!player_type[cur_player]) x = comp_move(cur_player,a);
			else x = 1;
			if(is_winner(cur_player)) {
				win_list.push_back(cur_player);
				players[cur_player].active = 0;
			}
			if(win_list.size() == n-1) gamestate = 7;
			if(x == 1){
				cur_player = (cur_player+1)%4;
				ph = (ph+1)%4;
				while(players[ph].active == 0){
					ph = (ph+1)%4;
					cur_player = (cur_player+1)%4;
				}
			}
		}
	}
	else if(gamestate == 7){
		if(button == GLUT_RIGHT_BUTTON){
			gamestate = 0;
			cur_player = 0;
			ph = 0;
			flag = 0;
			button_state = 0;
			n = 0;
			for(int i=0; i<92; i++){
				cells[i].piece.erase(cells[i].piece.begin(),cells[i].piece.end());
			}
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					players[i].cur_pos[j] = 0;
				}
				players[i].active = 0;
			}
		}
		for(int i=0; i<4; i++) player_type[i] = 0;
		//gamestate = 0;
	}
	else if(gamestate == 8){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
			if(mx >= 10 && mx <= 80 && my >= 720 && my <= 750) gamestate = 0;
			else if(mx >= 100 && mx <= 350 && my >= 400 && my <= 650) {
				snd_flag ^= 1;
				if(snd_flag) PlaySound(TEXT("assets\\3B1B.wav"),NULL,SND_ASYNC|SND_LOOP);
				else PlaySound(0,0,0);
			}
		}
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if(gamestate == 0){
		if(key == 'm') gamestate = 1;
		if(key == 's') gamestate = 2;
	}
	else if(gamestate == 1){
		if(key == '2') gamestate = 4;
		if(key == '4') gamestate = 3;
	}
	else if(gamestate == 2){
		if(key == '2') gamestate = 6;
		if(key == '4') gamestate = 5;
	}
	if(key == 'b'){
		gamestate = 0;
		cur_player = 0;
		ph = 0;
		flag = 0;
		button_state = 0;
		n = 0;
		for(int i=0; i<92; i++){
			cells[i].piece.erase(cells[i].piece.begin(),cells[i].piece.end());
		}
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				players[i].cur_pos[j] = 0;
			}
			players[i].active = 0;
		}
		for(int i=0; i<4; i++) player_type[i] = 0;
	}
	if(key == 'p'){
		if(gamestate != 9) pre_gamestate = gamestate;
		gamestate = 9;
	}
	if(key == 'd'){
		if(button_state == 0){
			while(players[ph].active == 0){
				ph = (ph+1)%4;
				cur_player = (cur_player+1)%4;
			}
			a = roll_dice(dice_cnt);
			button_state = 1;
		}
	}
	if(key == 'r'){
		gamestate = pre_gamestate;
	}
	if (key == 'q') {
		exit(0);
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	//place your codes for other keys here
}

void iPassiveMouseMove(int mx, int my){

}


int main() {
	if(snd_flag) PlaySound(TEXT("assets\\3B1B.wav"),NULL,SND_ASYNC|SND_LOOP);
	srand(time((NULL)));
	loadResources();
	//place your own initialization codes here.
	iInitialize(1360, 800, "iLudo");
	return 0;
}
