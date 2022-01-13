#include <cstdlib>
#include <memory>
#include <filesystem>

#include "game.h"
#include "piece.h"
#include "raylib.h"
#include "raymath.h"

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
        BeginDrawing();

        ClearBackground(WHITE);

        draw_board();
        draw_pieces();

        EndDrawing();
    }

    return EXIT_SUCCESS;
}

void Game::init_board()
{
    // TODO: convert this into a json file.

    board.push_back(Piece::Piece{Vector2{1, 1}, Piece::Kind::Rook, WHITE, "white_rook"});
    board.push_back(Piece::Piece{Vector2{8, 1}, Piece::Kind::Rook, WHITE, "white_rook"});

    board.push_back(Piece::Piece{Vector2{1, 8}, Piece::Kind::Rook, BLACK, "black_rook"});
    board.push_back(Piece::Piece{Vector2{8, 8}, Piece::Kind::Rook, BLACK, "black_rook"});

    board.push_back(
        Piece::Piece{Vector2{2, 1}, Piece::Kind::Knight, WHITE, "white_knight"});
    board.push_back(
        Piece::Piece{Vector2{7, 1}, Piece::Kind::Knight, WHITE, "white_knight"});

    board.push_back(
        Piece::Piece{Vector2{2, 8}, Piece::Kind::Knight, BLACK, "black_knight"});
    board.push_back(
        Piece::Piece{Vector2{7, 8}, Piece::Kind::Knight, BLACK, "black_knight"});

    board.push_back(
        Piece::Piece{Vector2{3, 1}, Piece::Kind::Bishop, WHITE, "white_bishop"});
    board.push_back(
        Piece::Piece{Vector2{6, 1}, Piece::Kind::Bishop, WHITE, "white_bishop"});

    board.push_back(
        Piece::Piece{Vector2{3, 8}, Piece::Kind::Bishop, BLACK, "black_bishop"});
    board.push_back(
        Piece::Piece{Vector2{6, 8}, Piece::Kind::Bishop, BLACK, "black_bishop"});

    board.push_back(
        Piece::Piece{Vector2{4, 1}, Piece::Kind::Queen, WHITE, "white_queen"});
    board.push_back(
        Piece::Piece{Vector2{4, 8}, Piece::Kind::Queen, BLACK, "black_queen"});

    board.push_back(Piece::Piece{Vector2{5, 1}, Piece::Kind::King, WHITE, "white_king"});
    board.push_back(Piece::Piece{Vector2{5, 8}, Piece::Kind::King, BLACK, "black_king"});

    for (int i = 1; i <= 8; i++)
    {
        board.push_back(
            Piece::Piece{Vector2{i, 2}, Piece::Kind::Pawn, WHITE, "white_pawn"});
        board.push_back(
            Piece::Piece{Vector2{i, 7}, Piece::Kind::Pawn, BLACK, "black_pawn"});
    }
}

void Game::load_textures()
{
    for (const auto& entry : std::filesystem::directory_iterator{"res"})
    {
        textures.insert({entry.path().stem(), LoadTexture(entry.path().c_str())});
    }
}

void Game::draw_pieces()
{
    for (const auto& piece : board)
    {
        // I subtract 1 from piece's position because the rendered position
        // is 1 less than the in-game position.
        DrawTextureEx(
            textures[piece.texture_name],
            Vector2Add(board_pos, Vector2Scale(Vector2SubtractValue(piece.pos, 1),
                                               texture_size * texture_scale)),
            0.0f, texture_scale, WHITE);
    }
}

void Game::draw_board()
{
    for (int x = 0; x <= 7; x++)
    {
        for (int y = 0; y <= 7; y++)
        {
            Color color = DARKGRAY;
            if ((x + y) % 2 == 0)
                color = RAYWHITE;

            Vector2 pos = Vector2Add(
                board_pos, Vector2Scale(Vector2{x, y}, texture_size * texture_scale));
            DrawRectangleV(
                pos, Vector2{texture_size * texture_scale, texture_size * texture_scale},
                color);
        }
    }
}