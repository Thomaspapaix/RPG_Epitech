/*
** EPITECH PROJECT, 2021
** my_rpg [WSL: Ubuntu]
** File description:
** attack_enemy.c
*/

#include "game.h"

int attack_controller(grid_controller_t *controller, engine_t *engine);
int attack_ai(grid_controller_t *controller, object_t *enemy,
    engine_t *engine);

static sfVector2f get_next_position(object_t *object, engine_t *engine,
    object_t *direction)
{
    grid_controller_t *controller = get_addon_data("enemy_ai",
        direction);
    sfVector2f normal = get_normalize_vector(get_position(object),
        get_position(direction));

    if (!controller)
        return get_position(object);
    normal.x = round(normal.x);
    normal.y = round(normal.y);
    normal.x *= 49;
    normal.y *= 49;
    normal.x += get_position(object).x;
    normal.y += get_position(object).y;
    if (equal_vector2f(controller->move_point, normal))
        return get_position(object);
    return normal;
}

int second_ai_attack_enemy(object_t *second, grid_controller_t *controller,
    object_t *direction)
{
    sfVector2f normal = get_normalize_vector(get_position(second),
        controller->move_point);

    normal.x *= 15 * (second->engine->time.delta / 100);
    normal.y *= 15 * (second->engine->time.delta / 100);
    move_vector(second, normal);
    if (equal_vector2f_pov(get_position(second),
        controller->move_point, 1)) {
        set_position_vector(second, controller->move_point);
        controller->move_point = get_next_position(second, second->engine,
            direction);
    }
    if (equal_vector2f(get_position(second), controller->move_point) &&
        controller->time <= 0) {
        attack_ai(controller, direction, second->engine);
        controller->time = 1000;
    }
}
