
#include <SFML/Graphics.h>

int main()
{
    sfVideoMode mode = {128*4, 4*64, 32};
    sfRenderWindow* window;
    sfSprite* sprite;

    sfText* text;
    sfEvent event;
	sfRectangleShape *shape = sfRectangleShape_create();
    sfRectangleShape_setFillColor(shape,sfWhite);
	sfVector2f position={10,10};
	sfVector2f scale={40,40};
	sfRectangleShape_setPosition( shape, position);
    sfRectangleShape_setScale(shape, scale);

    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return 1;


    sprite = sfSprite_create();


    /* Create a graphical text to display */

    text = sfText_create();
    sfText_setString(text, "Hello SFML");

    sfText_setCharacterSize(text, 50);



    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        /* Clear the screen */
        sfRenderWindow_clear(window, sfBlack);

        /* Draw the sprite */
        sfRenderWindow_drawSprite(window, sprite, NULL);

        sfRenderWindow_drawRectangleShape(window, shape, NULL);
        /* Draw the text */
        sfRenderWindow_drawText(window, text, NULL);

        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    sfText_destroy(text);

    sfSprite_destroy(sprite);

    sfRenderWindow_destroy(window);

    return 0;
}