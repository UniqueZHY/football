#include "head.h"
#include "game.h"
#define MAX 50

extern struct User *rteam, *bteam;
extern WINDOW *Football;
extern struct Bpoint ball;
extern struct BallStatus ball_status;

void re_draw_player(int team, char *name, struct Point *loc) {
    char p = 'k';
    if (team)
        wattron(Football, COLOR_PAIR(6));
    else
        wattron(Football, COLOR_PAIR(2));
    w_gotoxy_putc(Football, loc->x, loc->y, p);
    w_gotoxy_puts(Football, loc->x + 1, loc->y - 1, name);
}

void re_draw_team(struct User *team) {
    for (int i = 0; i < MAX; i++) {
        if (!team[i].online) continue;
        re_draw_player(team[i].team, team[i].name, &team[i].loc);
    }
}

void re_draw_ball() {
    double t = 0.1;
    if (ball_status.v.x != 0 || ball_status.v.y != 0) {
        ball.x += ball_status.v.x * t + ball_status.a.x * 0.5 * 0.01;
        ball.y += ball_status.v.y * t + ball_status.a.y * 0.5 * 0.01;
        ball_status.v.x += ball_status.a.x * t;
        ball_status.v.y += ball_status.a.y * t;
    }
    w_gotoxy_putc(Football, (int)ball.x, (int)ball.y, 'O');
}

void re_draw() {
    werase(Football_t);
    box(Football_t, 0, 0);
    box(Football, 0, 0);
    re_draw_team(rteam);
    re_draw_team(bteam);
    re_draw_ball();
    wrefresh(Football_t);
}
