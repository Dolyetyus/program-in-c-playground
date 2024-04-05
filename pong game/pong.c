#include <ncurses.h>
#include <stdlib.h>

#define WIDTH 50
#define HEIGHT 20
#define PADDLE_HEIGHT 5

typedef struct {
    int x, y;
    int dx, dy;
} Ball;

typedef struct {
    int x, y;
} Paddle;

int score = 0;

void draw_border() {
    for (int i = 0; i < HEIGHT; i++) {
        mvaddch(i, 0, '|');
        mvaddch(i, WIDTH, '|');
    }
    for (int i = 0; i < WIDTH; i++) {
        mvaddch(0, i, '-');
        mvaddch(HEIGHT, i, '-');
    }
    mvprintw(0, WIDTH+1, " Score: %d", score);
}

void draw_paddle(Paddle p) {
    for (int i = 0; i < PADDLE_HEIGHT; i++) {
        mvaddch(p.y + i, p.x, '|');
    }
}

void draw_ball(Ball b) {
    mvaddch(b.y, b.x, 'O');
}

void update_ball(Ball* b, Paddle p) {
    b->x += b->dx;
    b->y += b->dy;

    if (b->x <= 1) {
        if (b->y >= p.y && b->y <= p.y + PADDLE_HEIGHT) {
            b->dx *= -1;    // Ball hit the paddle
            score++;
        } 
        else {
            clear();
            mvprintw(HEIGHT / 2, WIDTH / 2 - 4, "Game Over");
            mvprintw(HEIGHT / 2 + 1, WIDTH / 2 - 8, "Press R to restart");
            mvprintw(HEIGHT / 2 + 2, WIDTH / 2 - 8, "Press ESC to exit");
            refresh();

            int ch;
            while (1) {
                ch = getch();
                if (ch == 'r' || ch == 'R') {
                    b->x = WIDTH / 2;
                    b->y = HEIGHT / 2;
                    b->dx = 1;
                    b->dy = 1;
                    score = 0;  // Reset the score
                    return;
                } 
                else if (ch == 27) {
                    endwin();
                    exit(0);
                }
            }
        }
    }

    if (b->x >= WIDTH - 1) {
        b->dx *= -1;
    }
    if (b->y <= 1 || b->y >= HEIGHT - 1) {
        b->dy *= -1;
    }
}

void update_paddle(Paddle* p, int ch) {
    if (ch == KEY_UP && p->y > 1) {
        p->y--;
    } else if (ch == KEY_DOWN && p->y < HEIGHT - PADDLE_HEIGHT) {
        p->y++;
    }
}

int main() {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    Ball ball = {WIDTH / 2, HEIGHT / 2, 1, 1};
    Paddle paddle = {1, HEIGHT / 2};

    while (1) {
        clear();
        draw_border();
        draw_paddle(paddle);
        draw_ball(ball);
        refresh();

        int ch = getch();
        update_paddle(&paddle, ch);
        update_ball(&ball, paddle);
        usleep(1000000 / 12);
    }

    endwin();
    return 0;
}
