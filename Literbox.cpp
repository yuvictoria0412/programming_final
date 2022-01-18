#include "Literbox.h"
#include <iostream>
#include <vector>
using namespace std;

const int ThumbWidth = 5;
const int ThumbHeight = 5;
int size_poop[2] = {0};
float pic_scale = 0.1;
ALLEGRO_BITMAP *tmp_poop;
ALLEGRO_BITMAP *tmp_poop_1;
ALLEGRO_BITMAP *tmp_poop2 ;
ALLEGRO_BITMAP *tmp_poop2_1;
ALLEGRO_SAMPLE_ID *ret_id_l;
ALLEGRO_BITMAP *shovel_tmp;
Literbox::Literbox(){
    srand(time(NULL));
    al_install_audio( );
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    Font = al_load_ttf_font("./font/Cute Letters.ttf",36,0); // load small font
    LargeFont = al_load_ttf_font("./font/Cute Letters.ttf", 60, 0); //load large font
    box = al_load_bitmap("./literbox/box.png");
    tmp_poop = al_load_bitmap("./literbox/poop1_1.png");
    tmp_poop_1 = al_load_bitmap("./literbox/poop1_2.png");
    tmp_poop2 = al_load_bitmap("./literbox/poop2_1.png");
    tmp_poop2_1 = al_load_bitmap("./literbox/poop2_2.png");
    poops_pic.reserve(2);
    poops_pic[0]= new std::vector<ALLEGRO_BITMAP*>(poop_state_num);
    poops_pic[1]= new std::vector<ALLEGRO_BITMAP*>(poop_state_num);
//    poops_pic.push_back({tmp_poop, tmp_poop});
//    poops_pic.push_back({tmp_poop2, tmp_poop2});
    (*poops_pic[0])[0] = (tmp_poop);
    (*poops_pic[0])[1] = (tmp_poop_1);
    (*poops_pic[1])[0] = (tmp_poop2);
    (*poops_pic[1])[1] = (tmp_poop2_1);
    pic_scale = 100/(float)al_get_bitmap_height(tmp_poop);
    size_poop[0] = 100;
    size_poop[1] = 100;
    for( int i = 0; i < poop_how_many; i ++){
        Poop new_poop;
        new_poop.appearence = rand()%2;
        new_poop.poop_pic_count = 0;
//        new_poop.pic_buried = tmp_poop;
//        new_poop.pic_half_buried = tmp_poop2;
        new_poop.x = w_bound + rand() %(window_width - w_bound*2);
        new_poop.y = h_bound + rand() %(200) * ( i + 1 );
        if( new_poop.y > window_height - h_bound) new_poop.y = window_height - h_bound - rand() %150;
        if( new_poop.y > window_width - w_bound) new_poop.x = window_width - w_bound - rand() %150;
        poops.push_back(new_poop);
    }
    shovel_tmp = al_load_bitmap("./literbox/shovel.png");
    shovel.push_back(shovel_tmp);
    shovel.push_back(shovel_tmp);
    sample = al_load_sample("./sound/shovel.wav");
    shuffle_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(shuffle_sound, ALLEGRO_PLAYMODE_ONCE);
    al_reserve_samples(1);

    al_attach_sample_instance_to_mixer(shuffle_sound, al_get_default_mixer());



}
Literbox::~Literbox(){
    al_destroy_bitmap(box);
    for(int i = 0; i < 2; i ++){
        al_destroy_bitmap((shovel[i]));
    }
    for(int i = 0; i < 2; i ++){
        for(int j = 0; j < 2; j ++){
            al_destroy_bitmap((*poops_pic[i])[j]);
        }
    }
    al_destroy_font(Font);
    al_destroy_font(LargeFont);

    al_destroy_sample(sample);
    al_destroy_sample_instance(shuffle_sound);
    al_destroy_bitmap(shovel_tmp);
    al_destroy_bitmap(tmp_poop);
    al_destroy_bitmap(tmp_poop_1);
    al_destroy_bitmap(tmp_poop2);
    al_destroy_bitmap(tmp_poop2_1);

}
void Literbox::Reset(){
    poops.clear();
    for( int i = 0; i < poop_how_many; i ++){
        Poop new_poop;
        new_poop.appearence = rand()%2; // -1 means cleaned
        new_poop.poop_pic_count = 0;
        new_poop.x = w_bound + rand() %(window_width - w_bound*2);
        new_poop.y = h_bound + rand() %(200) * ( i + 1 );
        if( new_poop.y > window_height - h_bound) new_poop.y = window_height - h_bound - rand() %150;
        if( new_poop.y > window_width - w_bound) new_poop.x = window_width - w_bound - rand() %150;
        poops.push_back(new_poop);
    }
    literbox_window_open = false;
}

void Literbox::Draw_box(int mouse_x, int mouse_y, int shovel_state){
    cout << "draw box\n";
    al_clear_to_color(WHITE);
    al_draw_scaled_bitmap(box, 0, 0, al_get_bitmap_width(box), al_get_bitmap_height(box),
                              120, 200, 550,550,0);
                              cout << "draw box pic\n";
    al_draw_text(LargeFont, BLACK,  window_width/2 , 100, ALLEGRO_ALIGN_CENTRE, "C L E A N   P O O P");
    al_draw_text(Font, BLACK,  window_width-180 , 50, ALLEGRO_ALIGN_CENTRE, "E S C   T O   E X I T");
    for( int i = 0, s = poops.size(); i < s; i ++){
        if( poops[i].appearence != -1 ){
//            al_draw_scaled_rotated_bitmap((*poops_pic[poops[i].appearence])[1], 80, 80,
//                             poops[i].x, poops[i].y, 0.1, 0.1,0,0);
            al_draw_scaled_rotated_bitmap((*poops_pic[poops[i].appearence])[poops[i].poop_pic_count], 80, 80,
                             poops[i].x, poops[i].y, pic_scale, pic_scale,0,0);

        }

    }
    cout << "draw poop pic\n";
    al_draw_scaled_rotated_bitmap( shovel[shovel_state], al_get_bitmap_width(shovel[shovel_state])/4, al_get_bitmap_height(shovel[shovel_state])/4*3,
                              mouse_x, mouse_y, 0.5, 0.5,0,0);
    cout << "draw shovel pic\n";
    al_flip_display();
}

bool Literbox::game_play(ALLEGRO_EVENT_QUEUE *event_queue){
    int mouse_x = 0, mouse_y = 0;
    //background

    ALLEGRO_EVENT event;
    Draw_box(mouse_x, mouse_y, 0);
    bool redraw = true;
    int cleaned = 0, to_be_cleaned = poops.size();
    cout << "poop " << to_be_cleaned<<endl;
    while(cleaned < to_be_cleaned){
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(event.mouse.button == 1) {
                if(!usersound)al_play_sample(sample, 4, 0.0, 1, ALLEGRO_PLAYMODE_ONCE, ret_id_l);
                for( int i = 0, s = poops.size(); i < s; i ++ ){
                    if( poops[i].appearence != -1){
                        if(clicked( mouse_x, mouse_y, poops[i].x, poops[i].y, size_poop[poops[i].appearence] * 2,
                                                    size_poop[poops[i].appearence] * 2) ){
                            poops[i].poop_pic_count += 1;
//                            cout << "click poop"<< poops[i].poop_pic_count<<" "<< poops[i].appearence<<"\n";
                            if( poops[i].poop_pic_count == poop_state_num ){
                                poops[i].appearence = -1;
                                poops[i].poop_pic_count;
                                cleaned++;
                            }
                            break;
                        }
                    }
                }
            }
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
    //        std::cout << "find bug\n";
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
//            Draw_box(mouse_x, mouse_y, 0);
    //        std::cout << "mouse "<< mouse_x << " " << mouse_y << std::endl;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                if(usermode){
                    Reset();
                    return true;
                }
                else{
                    Reset();
                    return false;
                }
                break;
            }
        }
        if( redraw ) Draw_box(mouse_x, mouse_y, 0);
    }
    Reset();
    return true;
}
// Detect if cursor hovers over any of tower on menu
// If so, return its type
// Otherwise, return -1
int Literbox::MouseIn(int, int){
    return 1;
}
    // static function that detect if one point is on a line
    // This function is just used to simplify "MouseIn"
bool Literbox::isInRange(int point, int startPos, int length){
    if(point >= startPos - length && point <= startPos + length)
        return true;
    return false;
}
bool Literbox::clicked(int mouse_x, int mouse_y, int x, int y, int w, int h){
//    cout << "shop is opened\n";
    if( isInRange( mouse_x, x, ThumbWidth + w/2) &&
       isInRange( mouse_y, y, ThumbHeight+ h/2)){
        return true;
    }
    else{
        return false;
    }
}
