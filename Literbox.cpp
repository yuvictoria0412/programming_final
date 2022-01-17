#include "Literbox.h"
#include <iostream>
using namespace std;

const int ThumbWidth = 5;
const int ThumbHeight = 5;
Literbox::Literbox(){
    srand(time(NULL));
    al_install_audio( );
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    Font = al_load_ttf_font("./font/Cute Letters.ttf",36,0); // load small font
    LargeFont = al_load_ttf_font("./font/Cute Letters.ttf", 60, 0); //load large font
    box = al_load_bitmap("./literbox/box.jpg");
    ALLEGRO_BITMAP *tmp_poop = al_load_bitmap("./literbox/poop.jpg");
    ALLEGRO_BITMAP *tmp_poop2 = al_load_bitmap("./literbox/poop.jpg");
    poops_pic.reserve(2);
    poops_pic[0]= new std::vector<ALLEGRO_BITMAP*>(poop_state_num);
    poops_pic[1]= new std::vector<ALLEGRO_BITMAP*>(poop_state_num);
//    poops_pic.push_back({tmp_poop, tmp_poop});
//    poops_pic.push_back({tmp_poop2, tmp_poop2});
    (*poops_pic[0])[0] = (tmp_poop);
    (*poops_pic[0])[1] = (tmp_poop);
    (*poops_pic[1])[0] = (tmp_poop2);
    (*poops_pic[1])[1] = (tmp_poop2);

    for( int i = 0; i < 7; i ++){
        Poop new_poop;
        new_poop.appearence = 1;
        new_poop.poop_pic_count = 0;
//        new_poop.pic_buried = tmp_poop;
//        new_poop.pic_half_buried = tmp_poop2;
        new_poop.x = w_bound + rand() %(window_height - w_bound*2);
        new_poop.y = h_bound + rand() %(200) * ( i + 1 );
        if( new_poop.y > window_height - h_bound) new_poop.y -= 80;
        poops.push_back(new_poop);
    }
    ALLEGRO_BITMAP *shovel_tmp = al_load_bitmap("./literbox/shovel.png");
    shovel.push_back(shovel_tmp);
    shovel.push_back(shovel_tmp);

}
Literbox::~Literbox(){

}
void Literbox::Reset(){
    literbox_window_open = false;
}
void Literbox::Draw_box(int mouse_x, int mouse_y, int shovel_state){
    al_draw_scaled_rotated_bitmap(box, al_get_bitmap_width(box)/2, al_get_bitmap_height(box)/2,
                              window_width/2, window_height/2, 1, 1,0,0);
    for( int i = 0, s = poops.size(); i < s; i ++){
        if( poops[i].appearence != 0 ){
            al_draw_scaled_rotated_bitmap((*poops_pic[0])[1], 80, 80,
                             poops[i].x, poops[i].y, 0.1, 0.1,0,0);
        }

    }
    al_draw_scaled_rotated_bitmap( shovel[shovel_state], al_get_bitmap_width(shovel[shovel_state])/4, al_get_bitmap_height(shovel[shovel_state])/4*3,
                              mouse_x, mouse_y, 0.5, 0.5,0,0);
    al_flip_display();
}
void Literbox::game_play(ALLEGRO_EVENT_QUEUE *event_queue){
    int mouse_x = 0, mouse_y = 0;
    //background
    ALLEGRO_EVENT event;
    Draw_box(mouse_x, mouse_y, 0);
    bool redraw = true;
//    while(1){
//
//        al_wait_for_event(event_queue, &event);
//        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
//            if(event.mouse.button == 1) {
//                for( auto popo : poops ){
//                    if( popo.appearence && clicked( mouse_x, mouse_y, popo.x, popo.y, al_get_bitmap_width(popo.pic_half_buried),  al_get_bitmap_height(popo.pic_half_buried))){
//                            popo.appearence += 1;
//                            if( popo.appearence == 2 ) popo.appearence = 0;
//                    }
//                }
//            }
//        }
//        else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
//    //        std::cout << "find bug\n";
//            mouse_x = event.mouse.x;
//            mouse_y = event.mouse.y;
////            Draw_box(mouse_x, mouse_y, 0);
//    //        std::cout << "mouse "<< mouse_x << " " << mouse_y << std::endl;
//        }
//        if( redraw ) Draw_box(mouse_x, mouse_y, 0);
//    }

//    al_rest(30);



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
