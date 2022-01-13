#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <unordered_map>
#include <string>

#include <raylib.h>

#include "piece.h"

class Game
{
public:
    Game();
    ~Game();

    int run();

private:
    void init_board();
    void load_textures();

    void draw_pieces();
    void draw_board();

    int window_width = 1920;
    int window_height = 1080;
    int texture_size = 16;
    int texture_scale = 6;

    Vector2 board_size = {8 * texture_size * texture_scale,
                          8 * texture_size* texture_scale};
    // TODO: the board is off center for some reason.
    Vector2 board_pos = {(window_width - board_size.x) / 2,
                         (window_height - board_size.y) / 2};

    std::vector<Piece::Piece> board;
    std::unordered_map<std::string, Texture2D> textures;
};

#endif  // ENGINE_H
