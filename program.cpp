#include "splashkit.h"
#include <string>
using namespace std;

void load_resources()
{
    load_sound_effect("hit", "fallbig.ogg");
    load_bitmap("scope", "scope.png");
    load_bitmap("target", "ProfCain.png");
}

void draw_target(double x, double y)
{
    draw_bitmap("target", x, y);
}

void draw_scope(double x, double y)
{
    // Draw scope centred on x,y
    draw_bitmap("scope", 
        x - bitmap_width("scope") / 2 , 
        y - bitmap_height("scope") / 2);
    // draw_circle(COLOR_BLACK, x, y, 20);

    // if ( mouse_down(LEFT_BUTTON) )
    // {
    //     fill_circle(COLOR_BLACK, x, y, 10);
    // }
    // else
    // {
    //     draw_circle(COLOR_BLACK, x, y, 10);
    // }
}

bool mouse_over_target(int target_x, int target_y)
{
    return bitmap_point_collision(bitmap_named("target"), target_x, target_y, mouse_x(), mouse_y());
}

int main()
{
    open_window("Whack IT!", 600, 600);

    load_resources();

    // int x;
    // x = 300;

    int target_x, target_y;
    timer game_timer;
    int wait_time;
    int score = 0;

    game_timer = create_timer("game timer");

    start_timer(game_timer);

    target_x = rnd( screen_width() - bitmap_width("target") );
    target_y = rnd( screen_height() - bitmap_height("target") );
    wait_time = 500 + rnd(3000);

    hide_mouse();

    while ( ! quit_requested() )
    {
        process_events();

        if ( mouse_clicked(LEFT_BUTTON) and mouse_over_target(target_x, target_y) )
        {
            target_x = rnd( screen_width() - bitmap_width("target") );
            target_y = rnd( screen_height() - bitmap_height("target") );

            play_sound_effect("hit");
            score++;
        }

        if ( timer_ticks(game_timer) >= wait_time )
        {
            target_x = rnd( screen_width() - bitmap_width("target") );
            target_y = rnd( screen_height() - bitmap_height("target") );
            wait_time = 500 + rnd(3000);
            reset_timer(game_timer);
        }


        clear_screen(COLOR_PINK);

        // fill_circle(COLOR_BLACK, x, 300, 50);

        draw_text("Score: " + to_string(score), COLOR_BLACK, 0, 0);
        draw_target(target_x, target_y);
        draw_scope(mouse_x(), mouse_y());

        // if ( key_down(RIGHT_KEY) )
        // {
        //     x += 1;
        // }
        // if ( key_down(LEFT_KEY) )
        // {
        //     x -= 1;
        // }

        refresh_screen(60);
    }

    show_mouse();

    return 0;
}