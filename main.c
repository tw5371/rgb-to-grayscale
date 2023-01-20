#include <SFML/Graphics.h>
#include <stdio.h>
sfColor RGBtoGrayscale(sfColor c) {
    unsigned char op = (c.r > c.g) << 1 | (c.g > c.b);
    unsigned char min, max, avg;
    switch (op) {
    case 0b00:
        max = c.b;
        min = c.r;
        break;
    case 0b01:
        max = c.g;
        min = c.r > c.b ? c.b : c.r;
        break;
    case 0b10:
        max = c.r > c.b ? c.r : c.g;
        min = c.g;
        break;
    case 0b11:
        max = c.r;
        min = c.b;
        break;
    }
    avg = (min + max) / 2;
    return sfColor_fromRGB(avg,avg,avg);
}
int main(void) {
    printf("Image to convert to grayscale >> ");
    char s[50];
    scanf("%50s",s);
    sfImage* img = sfImage_createFromFile(s);
    sfVector2u imgsize = sfImage_getSize(img);
    for (unsigned int y = 0; y < imgsize.y; y++) for (unsigned int x = 0; x < imgsize.x; x++) sfImage_setPixel(img,x,y,RGBtoGrayscale(sfImage_getPixel(img,x,y)));
    sfRenderWindow* win = sfRenderWindow_create((sfVideoMode){imgsize.x,imgsize.y},"Image to Grayscale",sfClose,0);
    sfSprite* sprite = sfSprite_create();
    sfSprite_setTexture(sprite,sfTexture_createFromImage(img,0),1);
    sfSprite_setPosition(sprite,(sfVector2f){0,0});
    sfEvent ev;
    while (sfRenderWindow_isOpen(win)) {
        while (sfRenderWindow_pollEvent(win,&ev)) {
            switch (ev.type) {
            case sfEvtClosed:
                sfRenderWindow_close(win);
                return 0;
            }
        }
        sfRenderWindow_clear(win,sfBlack);
        sfRenderWindow_drawSprite(win,sprite,0);
        sfRenderWindow_display(win);
    }
    return 1;
}