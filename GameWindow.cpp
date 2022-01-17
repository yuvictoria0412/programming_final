#include "GameWindow.h"
#include <iostream>
#include <time.h>
using namespace std;
#define GETW al_get_bitmap_width
#define GETH al_get_bitmap_height
#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))
const int ThumbWidth = 5;
const int ThumbHeight = 5;
ALLEGRO_BITMAP *pop_cat_open = NULL;
ALLEGRO_BITMAP *pop_cat_close = NULL;
char RPY[4];
const int rec_x1 = 250;
const int rec_y1 = 400;
const int rec_h1 = 50;
static std::vector<ALLEGRO_BITMAP*> shop_cat;
int cnt;
ALLEGRO_SAMPLE *popsample;
ALLEGRO_SAMPLE_INSTANCE *popSound;

ALLEGRO_SAMPLE *petsample;
ALLEGRO_SAMPLE_INSTANCE *petSound;

ALLEGRO_SAMPLE *meowsample;
ALLEGRO_SAMPLE_INSTANCE *meowSound;

ALLEGRO_SAMPLE *gamesample;
ALLEGRO_SAMPLE_INSTANCE *gameSound;
ALLEGRO_SAMPLE *winsample;
ALLEGRO_SAMPLE_INSTANCE *winSound;
ALLEGRO_SAMPLE *losesample;
ALLEGRO_SAMPLE_INSTANCE *loseSound;

ALLEGRO_SAMPLE_ID *ret_id;
GameWindow::GameWindow() {
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);

    if(timer == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("./font/Cute Letters.ttf",36,0); // load small font
    Medium_font = al_load_ttf_font("./font/Cute Letters.ttf", 24, 0); //load medium font
    Large_font = al_load_ttf_font("./font/Cute Letters.ttf", 60, 0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    pop_cat_open = al_load_bitmap("./popcat/open.jpg");
    pop_cat_close = al_load_bitmap("./popcat/close.jpg");


    //sound
    sample = al_load_sample("bgm.wav");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_LOOP);
    al_reserve_samples(1);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

    popsample = al_load_sample("./sound/pop.wav");
    popSound = al_create_sample_instance(popsample);
    al_set_sample_instance_playmode(popSound, ALLEGRO_PLAYMODE_ONCE);
    al_reserve_samples(1);
    al_attach_sample_instance_to_mixer(popSound, al_get_default_mixer());

    petsample = al_load_sample("./sound/meow_pet.wav");
    petSound = al_create_sample_instance(petsample);
    al_set_sample_instance_playmode(petSound, ALLEGRO_PLAYMODE_ONCE);
    al_reserve_samples(1);
    al_attach_sample_instance_to_mixer(petSound, al_get_default_mixer());

    meowsample = al_load_sample("./sound/meow.wav");
    meowSound = al_create_sample_instance(meowsample);
    al_set_sample_instance_playmode(meowSound, ALLEGRO_PLAYMODE_ONCE);
    al_reserve_samples(1);
    al_attach_sample_instance_to_mixer(meowSound, al_get_default_mixer());

    gamesample = al_load_sample("./sound/game.wav");
    gameSound = al_create_sample_instance(gamesample);
    al_set_sample_instance_playmode(gameSound, ALLEGRO_PLAYMODE_ONCE);
    al_reserve_samples(1);
    al_attach_sample_instance_to_mixer(gameSound, al_get_default_mixer());
    winsample = al_load_sample("./sound/win.wav");
    winSound = al_create_sample_instance(winsample);
    al_set_sample_instance_playmode(winSound, ALLEGRO_PLAYMODE_ONCE);
    al_reserve_samples(1);
    al_attach_sample_instance_to_mixer(winSound, al_get_default_mixer());

    losesample = al_load_sample("./sound/lose.wav");
    loseSound = al_create_sample_instance(losesample);
    al_set_sample_instance_playmode(loseSound, ALLEGRO_PLAYMODE_ONCE);
    al_reserve_samples(1);
    al_attach_sample_instance_to_mixer(loseSound, al_get_default_mixer());

    game_init();
}
void GameWindow::game_init() {
    RPY[0] = 'R';
    RPY[1] = 'P';
    RPY[2] = 'Y';
    error_message = 0;
    al_set_window_position(display, 0, 0);
    status = new Status();
    shop = new Shop();
    clean_cat = new Literbox();
    char pic_name[19];
    shop_cat.reserve(5);
    for (int i = 1; i <= 5; i++) {
        sprintf(pic_name, "./breed/cat1-%d.png", i);
        shop_cat[i-1] = al_load_bitmap(pic_name);
    }
}

void GameWindow::game_reset() {
    al_stop_timer(timer);
    status->Reset();
}
bool GameWindow::game_play() {
    int msg;

    srand(time(NULL));

    msg = -1;
    game_reset();
    game_begin();

    while(msg != GAME_EXIT)
    {
        msg = game_run();
    }

    show_err_msg(msg);
    return true;
}

void GameWindow::game_begin() {
    draw_running_map();
    al_start_timer(timer);
    draw_running_map();
    al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2, ALLEGRO_ALIGN_CENTRE, "L O A D   G A M E ...");
    al_flip_display();
    for (int i = 0; i < tree_size; i++) {
//        cout << "i" << endl;
        Tree *new_tree = new Tree(rand() % 400 + 400, rand() % 400 + 400);
        trees.push_back(new_tree);
    }
//    draw_running_map();
    Cat *temp = new Cat();
    delete temp;



    if(!usersound)al_play_sample_instance(startSound);
}


int GameWindow::game_update() {
    return GAME_CONTINUE;
}


void GameWindow::game_destroy() {
    game_reset();
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_timer(timer);

    delete status;
    delete shop;
}
void GameWindow::see_cat(int cat_index){
    cout<<"see me\n";
    double start_time = al_get_time(), now_time = start_time;
    int state = 1;
    cats[cat_index]->saw_cat(1);
    if(!usersound) al_play_sample(meowsample, 50, 0.0, 1, ALLEGRO_PLAYMODE_LOOP, ret_id);
    while( state && (now_time - start_time)<5.0){
        now_time = al_get_time();
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                if(usermode) state = 0;
//                else{
//                    state = 0;
//                    status->Gain_Score(cats[cat_index]->reward(SEEME)*-2);
//                }
                break;
            }
        }
        else{//draw
            al_clear_to_color( WHITE );
            al_draw_rectangle(window_width/2 - 125 , window_height/2 - 50, window_width/2 +125, window_height/2 +80, BLACK, 2);
            al_draw_text(font, BLACK,  window_width/2 , window_height/2-20, ALLEGRO_ALIGN_CENTRE, "W A T C H   M E");
            int count_down = 5 - (now_time - start_time);
            char tmp[1];
            tmp[0] = count_down + '0';
            al_draw_text(font, BLACK,  window_width/2 , window_height/2+20, ALLEGRO_ALIGN_CENTRE, tmp);
            cats[cat_index]->Draw();
            al_flip_display();
        }
    }
    status->Gain_Score(cats[cat_index]->reward(SEEME));
    if(!usersound){
        al_stop_samples();
        al_play_sample_instance(startSound);
    }
    draw_running_map();
    cats[cat_index]->saw_cat(0);
}

bool GameWindow::isInRange(int point, int startPos, int length){
    if(point >= startPos - length && point <= startPos + length)
        return true;
    return false;
}
bool GameWindow::clicked(int mouse_x, int mouse_y, int x, int y, int w, int h){
//    cout << "shop is opened\n";
    if( isInRange( mouse_x, x, ThumbWidth + w/2) &&
       isInRange( mouse_y, y, ThumbHeight+ h/2)){
        return true;
    }
    else{
        return false;
    }
}
// each drawing scene function
void GameWindow::draw_running_map() {
    cnt++;
    if (cnt == 50) cnt = 0;
    if( !shop->shop_status() ){ // shop closed
        al_clear_to_color( WHITE );

        for (auto tree : trees) {
            tree->Draw();
        }
//        cout << "tree\n";
        for (auto meow : cats) {
            meow->Draw();
            if (!meow->cat_queue_empty()) {
                meow->draw_cat_status(meow->cat_queue_top());
            }
        }
//        cout << "cats\n";
        if (error_message > 0) {
            error_message--;
            al_draw_filled_rectangle(rec_x1, rec_y1, window_width-rec_x1, rec_y1 + rec_h1, BLACK);
            al_draw_text(Medium_font, WHITE, window_width/2, rec_y1 + rec_h1/2 - 12, ALLEGRO_ALIGN_CENTRE, "C A N ' T    P U T    H E R E ! ! !");
        }
        status->Draw();
        shop->Draw();
    }
    else{ // shop opened
        al_clear_to_color( WHITE );
        status->Draw();
        shop->Draw();
        al_draw_scaled_rotated_bitmap(shop_cat[cnt/10], GETW(shop_cat[cnt/10]), GETH(shop_cat[cnt/10]), 350, 280, 0.5, 0.5, 0, 0);
    }
//    cout << "before flip\n";
    al_flip_display();
}
void GameWindow::touch_me(int cur) {
    int i = 0;
    int a = 0;
    int b = 0;

    while (1) {
        al_clear_to_color(WHITE);
        a = al_get_bitmap_width(cats[cur]->touch_pic(i));
        b = al_get_bitmap_height(cats[cur]->touch_pic(i));
        al_draw_scaled_bitmap(cats[cur]->touch_pic(i), 0, 0, a, b, window_width/2-360, window_height/2-300, 800, 600, 0);
        al_flip_display();

        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (event.mouse.button == 1) {
                if(!usersound &&i < 4) al_play_sample(petsample, 50, 0.0, 1, ALLEGRO_PLAYMODE_ONCE, ret_id);
                if (event.mouse.x >= 100 && event.mouse.x <= window_width - 100) {
                    if (event.mouse.y >= 100 && event.mouse.y <= window_height - 100) {
//                        cout << "touch me little game clicked" << endl;
                        if (++i == 5) break;
                    }
                }
            }
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                if( usermode){
                    status->Gain_Score(cats[cur]->reward(TOUCHME));
                    return;
                }
                else{
                    status->Gain_Score(cats[cur]->reward(TOUCHME)*-1);
                    return;
                }
                break;
            }
        }
    }
    status->Gain_Score(cats[cur]->reward(TOUCHME));
}
void GameWindow::hungry_cat(int cat_index){
    int feed_count = 0;
    if( status->Enough_Food(feed_food)){
        al_draw_scaled_bitmap(pop_cat_open,0,0,
                              al_get_bitmap_width(pop_cat_open), al_get_bitmap_height(pop_cat_open),
                                      0  , 0, window_width, window_height, 0);
        al_flip_display();
        char tmp[3];
        while( feed_count <= feed_food){
            al_wait_for_event(event_queue, &event);
            if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    if(usermode) feed_count += 10;
                    else{
                        status->Gain_Score(cats[cat_index]->reward(HUNGRY)*-2);
                        feed_count += 10;
                    }
                    break;
                }
            }
            else if(event.type == ALLEGRO_EVENT_TIMER) {
                if(event.timer.source == timer) {
                    al_draw_scaled_bitmap(pop_cat_open,0,0,al_get_bitmap_width(pop_cat_open), al_get_bitmap_height(pop_cat_open),
                                          0, 0, window_width, window_height, 0);
                al_draw_filled_rectangle(window_width/2 - 160 , window_height/2 +170, window_width/2 +160, window_height/2 +320, WHITE);
                al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2+180, ALLEGRO_ALIGN_CENTRE, "E A T E N");
                al_draw_filled_circle( mouse_x, mouse_y, 25,YELLOW);
                }
            }
            else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if(event.mouse.button == 1) {
//                    al_play_sample_instance(popSound);
                    if(!usersound) al_play_sample(popsample, 2, 0.0, 1, ALLEGRO_PLAYMODE_ONCE, ret_id);
                    al_draw_scaled_bitmap(pop_cat_close,0,0,al_get_bitmap_width(pop_cat_open), al_get_bitmap_height(pop_cat_open),
                              0, 0, window_width, window_height, 0);
                    al_draw_filled_rectangle(window_width/2 - 160 , window_height/2 +170, window_width/2 +160, window_height/2 +320, WHITE);
                    al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2+180, ALLEGRO_ALIGN_CENTRE, "E A T E N");

                    if( feed_count >= 10){
                        tmp[0] = feed_count /10+ '0';
                        tmp[1] = feed_count %10+ '0';
                    }
                    else tmp[0] = feed_count + '0';
                    al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2+240, ALLEGRO_ALIGN_CENTRE, tmp);
                    al_flip_display();
                    al_rest(0.3);
                    feed_count ++;
                    al_draw_scaled_bitmap(pop_cat_open,0,0,al_get_bitmap_width(pop_cat_open), al_get_bitmap_height(pop_cat_open),
                                      0, 0, window_width, window_height, 0);
                    al_draw_filled_rectangle(window_width/2 - 160 , window_height/2 +170, window_width/2 +160, window_height/2 +320, WHITE);
                        al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2+180, ALLEGRO_ALIGN_CENTRE, "E A T E N");
                }
            }
            else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
                al_draw_scaled_bitmap(pop_cat_open,0,0,al_get_bitmap_width(pop_cat_open), al_get_bitmap_height(pop_cat_open),
                                          0, 0, window_width, window_height, 0);
                al_draw_filled_rectangle(window_width/2 - 160 , window_height/2 +170, window_width/2 +160, window_height/2 +320, WHITE);
                al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2+180, ALLEGRO_ALIGN_CENTRE, "E A T E N");
            }
            if( feed_count >= 10){
                tmp[0] = feed_count /10+ '0';
                tmp[1] = feed_count %10+ '0';
            }
            else tmp[0] = feed_count + '0';
            if( feed_count<= feed_food) al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2+240, ALLEGRO_ALIGN_CENTRE, tmp);
            al_flip_display();
        }

        status->Change_Food(feed_food);
        status->Gain_Score(cats[cat_index]->reward(HUNGRY));
    }
    else{
        al_draw_filled_rectangle(window_width/2 - 125 , window_height/2 - 10, window_width/2 +125, window_height/2 +50, RED);
        al_draw_text(font, WHITE,  window_width/2 , window_height/2, ALLEGRO_ALIGN_CENTRE, "B U Y   F O O D");
        al_flip_display();
        al_rest(1.5);
        shop->change_window_open(true);
    }
}

void GameWindow::rock_paper_scissors(int cat_index){
    int scene = 1;
    int user_choice = -1, cat_choice;
    cat_choice = rand() % 2;
    double time = 4.0;
    al_clear_to_color( WHITE );
     //rock_papper_scissors
    char tmp[1];
    al_draw_filled_rectangle(window_width/2 - 125 , window_height/2-300, window_width/2 +125, window_height/2-30, WHITE);
    al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2-150, ALLEGRO_ALIGN_CENTRE, "T Y P E");
    for( int i = 0; i < 3; i ++){
        tmp[0] = RPY[i];
        al_draw_text(Large_font, BLACK,  window_width/3 * (i+1) -130 , window_height/2-20, ALLEGRO_ALIGN_CENTRE, tmp);
        al_draw_scaled_bitmap(cats[cat_index]->r_p_y_pic(i), 0, 0,al_get_bitmap_width(cats[cat_index]->r_p_y_pic(i)),
                              al_get_bitmap_width(cats[cat_index]->r_p_y_pic(i)),
                              window_width/3 * (i+1) -235, window_height/2+50, 200, 200, 0);
    }
    //choose rock paper scissors
    while( scene == 1 ){
     //cat
     // to cover cat's background
        al_draw_filled_rectangle(window_width/2 - 125 , window_height/2-300, window_width/2 +125, window_height/2-80, WHITE);
        al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2-100, ALLEGRO_ALIGN_CENTRE, "T Y P E");
        cats[cat_index]->Draw();
        al_flip_display();
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                if(usermode){
                  scene++;
                  user_choice = 1;
                  cat_choice = 0;
                  time = 0;
                }
                else{
                    scene++;
                    user_choice = 0;
                    cat_choice = 1;
                    time = 0;
                }
                break;
            case ALLEGRO_KEY_R:
                scene++;
                user_choice = 0;
                break;
            case ALLEGRO_KEY_P:
                scene++;
                user_choice = 1;
                break;
            case ALLEGRO_KEY_Y:
                scene++;
                user_choice = 2;
                break;
            }
//        al_flip_display();
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(event.mouse.button == 1) {
                for( int i = 0; i < 3; i ++){
                    if( clicked( mouse_x, mouse_y, window_width/3 * (i+1) -235, window_height/2+50, al_get_bitmap_width(cats[cat_index]->r_p_y_pic(i))/2,
                              al_get_bitmap_height(cats[cat_index]->r_p_y_pic(i)))){
                        user_choice = i;
                        cout << "click " << i << endl;
                        scene++;
                        i = 3;
                    }
                }
            }
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
        }
    }

    al_clear_to_color( WHITE );

    al_draw_circle(window_width/2, window_height/4+20, 120, BLACK, 5);//outline
    al_draw_circle(window_width/2, window_height/4*3-30, 120, BLACK, 5);//outline
    double now_time = al_get_time(), start_time = now_time;
    int count_down;
    if(!usersound && time ) al_play_sample(gamesample, 50, 0.0, 1, ALLEGRO_PLAYMODE_ONCE, ret_id);
    while( now_time - start_time < time){
        now_time = al_get_time();
        count_down = 4 - (now_time - start_time);
        tmp[0] = count_down + '0';
        al_draw_filled_circle(window_width/2, window_height/4+20, 100, WHITE);
        al_draw_text(Large_font, BLACK,  window_width/2, window_height/4+20-20, ALLEGRO_ALIGN_CENTRE, tmp);
        al_draw_filled_circle(window_width/2, window_height/4*3 -30, 100, WHITE);
        al_draw_text(Large_font, BLACK,  window_width/2, window_height/4*3-30-20, ALLEGRO_ALIGN_CENTRE, tmp);
        al_flip_display();
    }

    //scene 3 reveal choice
    al_clear_to_color( WHITE );
    //cat's choice
    al_draw_text(Large_font, BLACK,  window_width/2, 35, ALLEGRO_ALIGN_CENTRE, "C A T");
    al_draw_scaled_bitmap(cats[cat_index]->r_p_y_pic(cat_choice), 0, 0,al_get_bitmap_width(cats[cat_index]->r_p_y_pic(cat_choice)),
                          al_get_bitmap_width(cats[cat_index]->r_p_y_pic(cat_choice)),
                          window_width/2-122, window_height/4-100, 243, 243, 0);
    //your choice
    al_draw_text(Large_font, BLACK,  window_width/2, window_height-100, ALLEGRO_ALIGN_CENTRE, "Y O U");
    al_draw_scaled_bitmap(cats[cat_index]->r_p_y_pic(user_choice), 0, 0,al_get_bitmap_width(cats[cat_index]->r_p_y_pic(user_choice)),
                          al_get_bitmap_width(cats[cat_index]->r_p_y_pic(user_choice)),
                          window_width/2-122, window_height/4*3-150, 243, 243, 0);
    al_flip_display();
    al_rest(1.2);
    string result;
    //scene 4 result
    if( user_choice == cat_choice){
        if(!usersound) al_play_sample(meowsample, 50, 0.0, 1, ALLEGRO_PLAYMODE_ONCE, ret_id);
        result = "T I E";
    }
    else if ((user_choice == 2 && cat_choice == 1) || ( !cat_choice && user_choice == 1)){
        status->Gain_Score(cats[cat_index]->reward(BORING));
        result = "Y O U   W I N";
        if(!usersound) al_play_sample(winsample, 10, 0.0, 1, ALLEGRO_PLAYMODE_ONCE, ret_id);
    }
    else if ((user_choice == 0 && cat_choice == 1) || ( !cat_choice && user_choice == 2)){
        if(!usersound) al_play_sample(losesample, 20, 0.0, 1, ALLEGRO_PLAYMODE_ONCE, ret_id);
        result = "Y O U   L O S S";
    }
    al_draw_filled_rectangle(window_width/2 - 200 , window_height/2 -40, window_width/2 +200, window_height/2 +40, RED);
    al_draw_text(Large_font, WHITE,  window_width/2, window_height/2-28, ALLEGRO_ALIGN_CENTRE, result.c_str());
    al_flip_display();
    al_rest(2);
    cout << "end of rpy\n";
}
// process of updated event
int GameWindow::process_event() {
    int instruction = GAME_CONTINUE;
    al_wait_for_event(event_queue, &event);
    redraw = false;
    if( status->getScore() >= max_score){
        users_performance = true;
        final_score = status->getScore();
        instruction = GAME_EXIT;
        return instruction;
    }
    else if( status->getScore() <= min_score){
        users_performance = false;
        instruction = GAME_EXIT;
        final_score = status->getScore();
        return instruction;
    }
    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;
             for( int c = 0, s = cats.size(); c < s; c++ ){
                cats[c]->getting_dirty();
                cats[c]->getting_hungry();
                cats[c]->getting_bored();
                cats[c]->see_me();
                cats[c]->touch_me();
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.mouse.button == 1) {
            if( shop->shop_status() ){
//                std::cout << "clicked mouse "<< std::endl;
                int buy_item = -1;
                for( int i = SHOP_EXIT; i <= WATCH_AD; i++){
                    if(shop->shop_clicked( mouse_x, mouse_y, i)){
                        buy_item = i;
//                        std::cout << buy_item<<"buy ";
                    }
                }
                if( buy_item != -1 ){
                    if( buy_item == SHOP_EXIT ){
                        shop->change_window_open(false);
                    }
                    else if ( buy_item == WATCH_AD ){
//                           (rand() % (max - min + 1) + min);
                        if(!usersound) al_stop_sample_instance(startSound);
                        shop->play_video((rand() % (6 - 1 + 1) + 1), display); // 5and 6 good
                        if( !usermode ) status->Change_Coin( shop->costCoin(buy_item));
                        if(!usersound) al_play_sample_instance(startSound);
                    }
                    else if (buy_item == GET_CAT){
                        if( shop->Enough_Coin(status->getCoin(), buy_item)){
                            shop->change_window_open(false);
                            if (!put_a_cat())
                                instruction = GAME_EXIT;
                            status->Change_Coin( shop->costCoin(buy_item));

                        }
                        else{//not enough coin -> watch ad
                            al_draw_filled_rectangle(window_width/2 - 160 , window_height/2 - 10, window_width/2 +160, window_height/2 +50, RED);
                            al_draw_text(font, WHITE,  window_width/2 , window_height/2, ALLEGRO_ALIGN_CENTRE, "M O R E   C O I N  !");
                            al_flip_display();
                            al_rest(1.5);
                        }
                        //create cat object and mouse drag cat to position

                    }
                    else if(buy_item == BUY_FOOD){
//                        std::cout << "cost "<<shop->costCoin(buy_item)<< std::endl;
                        if( shop->Enough_Coin( status->getCoin(), buy_item)){
                            if( !usermode ) status->Change_Coin( shop->costCoin(buy_item));
                            if( buy_item == BUY_FOOD ) status->Change_Food( ADD_FOOD );
                        }
                        else{//not enough coin -> watch ad
                            al_draw_filled_rectangle(window_width/2 - 160 , window_height/2 - 10, window_width/2 +160, window_height/2 +50, RED);
                            al_draw_text(font, WHITE,  window_width/2 , window_height/2, ALLEGRO_ALIGN_CENTRE, "M O R E   C O I N  !");
                            al_flip_display();
                            al_rest(1.5);
                        }
                    }
                }
//                    std::cout << "clicked mouse "<<status->getCoin()<< std::endl;
            }
            else{ // shop closed
                if( shop->shop_clicked( mouse_x, mouse_y, SHOP_ICON)) shop->change_window_open(true);
                else {
                    for( int i = 0, s = cats.size(); i < s; i++){
                        if(  cats[i]->cat_queue_empty() == 0 && clicked(mouse_x, mouse_y, cats[i]->cat_x(), cats[i]->cat_y(),
                                                                         status_image_size + 100, status_image_size + 100)){
                            switch (cats[i]->cat_queue_top()) {
                            case HUNGRY: cats[i]->change_cat_status(HUNGRY, 0);
                                hungry_cat(i);
                                break;
                            case DIRTY: cats[i]->change_cat_status(DIRTY, 0);
                                if(clean_cat->game_play(event_queue))
                                    status->Gain_Score(cats[i]->reward(DIRTY));
                                else status->Gain_Score(-1*cats[i]->reward(DIRTY));
                                break;
                            case BORING: cats[i]->change_cat_status(BORING, 0);
                                cats[i]->saw_cat(1);
                                rock_paper_scissors(i);
                                cats[i]->saw_cat(0);
                                break;
                            case TOUCHME: cats[i]->change_cat_status(TOUCHME, 0);
                                touch_me(i);
                                break;
                            case SEEME: cats[i]->change_cat_status(SEEME, 0);
                                see_cat(i);
                                break;
                            }
                            cats[i]->cat_queue_pop();
                        }
                    }
                }
//                cout << "out\n";
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
//        std::cout << "find bug\n";
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
//        std::cout << "mouse "<< mouse_x << " " << mouse_y << std::endl;
        // shop->MouseIn(mouse_x, mouse_y);

    }
    else if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
        redraw = true;
        if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
            for (auto c : cats)
                c->changeXY(0,-10);
            for (auto t : trees)
                t->changeXY(0,-10);
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
            for (auto c : cats)
                c->changeXY(0,10);
            for (auto t : trees)
                t->changeXY(0,10);
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
            for (auto c : cats)
                c->changeXY(-10,0);
            for (auto t : trees)
                t->changeXY(-10,0);
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
            for (auto c : cats)
                c->changeXY(10,0);
            for (auto t : trees)
                t->changeXY(10,0);
        }
    }
    if(redraw) {
        // update each object in game
        instruction = game_update();
//                std::cout << "find bug redraq\n";
        // Re-draw map
        draw_running_map();
        redraw = false;
    }
    return instruction;
}

bool GameWindow::put_a_cat() {

    Cat *new_cat = new Cat();
    cats.push_back(new_cat);
    bool can_put;
    int cnt = 0;
    while (1) {
        can_put = 1;
        cnt++;
        redraw = false;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES && cnt % 5 == 0) {
            cnt /= 5;
            new_cat->setXY(event.mouse.x, event.mouse.y, 0);
            redraw = true;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int x = event.mouse.x;// - event.mouse.x % 200;
            int y = event.mouse.y;// - event.mouse.y % 200;
            for (auto c : cats) {
                if (c != new_cat) {
                    if (x >= c->cat_x()-200 && x <= c->cat_x()+200) {
                        if (y >= c->cat_y()-200 && y <= c->cat_y()+200) {
                            error_message = 10;
                            can_put = 0;
                            redraw = true;
                            break;
                        }
                    }
                }
            }

            if (can_put) {
                for (auto t : trees) {
                    if (x >= t->getX() + 200 && x <= t->getX() - 200) {
                        if (y >= t->getY() + 200 && y <= t->getY() - 200) {
                            error_message = 10;
                            can_put = 0;
                            redraw = true;
                            break;
                        }
                    }
                }
            }

            if (can_put) {
                new_cat->setXY(x, y, 1);
                redraw = true;
                draw_running_map();
                break;
            }
        }
        if (redraw)
            draw_running_map();
    }
    return true;
}
