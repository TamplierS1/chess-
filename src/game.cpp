#include <cstdlib>
#include <memory>
#include <filesystem>

#include "game.h"
#include "piece.h"
#include "raylib.h"
#include "raymath.h"

static Color get_tile_color(Vector2 pos)
{
    return static_cast<int>(pos.x + pos.y) % 2 == 0 ? RAYWHITE : DARKGRAY;
}

Game::Game()
{
    InitWindow(window_width, window_height, "chesspp");
    SetTargetFPS(60);

    load_textures();
    init_board();
}

Game::~Game()
{
    for (auto& texture : textures)
    {
        UnloadTexture(texture.second);
    }

    CloseWindow();
}

int Game::run()
{
    while (!WindowShouldClose())
    {
        handle_input();

        BeginDrawing();

        ClearBackground(WHITE);

        draw();

        EndDrawing();
    }

    return EXIT_SUCCESS;
}

void Game::init_board()
{
    // TODO: convert this into a json file.

    board.push_back(Piece{Vector2{1, 1}, Kind::Rook, WHITE, "white_rook"});
    board.push_back(Piece{Vector2{8, 1}, Kind::Rook, WHITE, "white_rook"});

    board.push_back(Piece{Vector2{1, 8}, Kind::Rook, BLACK, "black_rook"});
    board.push_back(Piece{Vector2{8, 8}, Kind::Rook, BLACK, "black_rook"});

    board.push_back(Piece{Vector2{2, 1}, Kind::Knight, WHITE, "white_knight"});
    board.push_back(Piece{Vector2{7, 1}, Kind::Knight, WHITE, "white_knight"});

    board.push_back(Piece{Vector2{2, 8}, Kind::Knight, BLACK, "black_knight"});
    board.push_back(Piece{Vector2{7, 8}, Kind::Knight, BLACK, "black_knight"});

    board.push_back(Piece{Vector2{3, 1}, Kind::Bishop, WHITE, "white_bishop"});
    board.push_back(Piece{Vector2{6, 1}, Kind::Bishop, WHITE, "white_bishop"});

    board.push_back(Piece{Vector2{3, 8}, Kind::Bishop, BLACK, "black_bishop"});
    board.push_back(Piece{Vector2{6, 8}, Kind::Bishop, BLACK, "black_bishop"});

    board.push_back(Piece{Vector2{4, 1}, Kind::Queen, WHITE, "white_queen"});
    board.push_back(Piece{Vector2{4, 8}, Kind::Queen, BLACK, "black_queen"});

    board.push_back(Piece{Vector2{5, 1}, Kind::King, WHITE, "white_king"});
    board.push_back(Piece{Vector2{5, 8}, Kind::King, BLACK, "black_king"});

    for (int i = 1; i <= 8; i++)
    {
        board.push_back(Piece{Vector2{i, 2}, Kind::Pawn, WHITE, "white_pawn"});
        board.push_back(Piece{Vector2{i, 7}, Kind::Pawn, BLACK, "black_pawn"});
    }
}

void Game::load_textures()
{
    for (const auto& entry : std::filesystem::directory_iterator{"res"})
    {
        textures.insert({entry.path().stem(), LoadTexture(entry.path().c_str())});
    }
}

void Game::handle_input()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(GetMousePosition(), Rectangle{board_pos.x, board_pos.y,
                                                             board_size.x, board_size.y}))
    {
        if (selected_piece != nullptr)
        {
            selected_piece->pos = screen2board_pos(GetMousePosition());
        }
        else
        {
            for (auto& piece : board)
            {
                Vector2 piece_pos = board2screen_pos(piece.pos);
                if (CheckCollisionPointRec(
                        GetMousePosition(),
                        Rectangle{piece_pos.x, piece_pos.y, texture_size * texture_scale,
                                  texture_size * texture_scale}))
                {
                    selected_piece = &piece;
                    break;
                }
            }
        }
    }
}

void Game::draw()
{
    draw_board();
    draw_selection();
    draw_pieces();
}

void Game::draw_pieces()
{
    for (const auto& piece : board)
    {
        // I subtract 1 from piece's position because the rendered position
        // is 1 less than the in-game position.
        DrawTextureEx(textures[piece.texture_name], board2screen_pos(piece.pos), 0.0f,
                      texture_scale, WHITE);
    }
}

void Game::draw_board()
{
    for (int x = 1; x <= 8; x++)
    {
        for (int y = 1; y <= 8; y++)
        {
            DrawRectangleV(
                board2screen_pos(Vector2{x, y}),
                Vector2{texture_size * texture_scale, texture_size * texture_scale},
                get_tile_color(Vector2{x, y}));
        }
    }
}

void Game::draw_selection()
{
    if (selected_piece != nullptr)
    {
        DrawRectangleV(
            board2screen_pos(selected_piece->pos),
            Vector2{texture_scale * texture_size, texture_scale * texture_size},
            ColorAlphaBlend(RED, RED, Color{200, 200, 200, 200}));
    }
}

Vector2 Game::board2screen_pos(Vector2 pos) const
{
    // I subtract 1 from piece's position because the rendered position
    // is 1 less than the in-game position.
    return Vector2Add(board_pos, Vector2Scale(Vector2{pos.x - 1, pos.y - 1},
                                              texture_size * texture_scale));
}

Vector2 Game::screen2board_pos(Vector2 pos) const
{
    Vector2 result = Vector2Divide(
        Vector2Subtract(pos, board_pos),
        Vector2{texture_size * texture_scale, texture_size * texture_scale});

    result.x = static_cast<int>(result.x + 1);
    result.y = static_cast<int>(result.y + 1);

    return result;
}