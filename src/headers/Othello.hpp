#include <iostream>
#include <vector>
#include <array>

#pragma once

namespace othello {

    enum Piece {
        Empty,
        Black,
        White
    };

    struct Position {
        int x;
        int y;
    };

    class Othello {

        
        public:

            static const int BOARD_SIZE = 8;

            Othello();

            Othello(const Othello& othello);

            /*
            Sets the board to its initial form
            */
            void initializeBoard();

            /*
            Get the turn as a piece
            */
            Piece getTurn() const;

            /*
            Get a piece from a given position
            */
            Piece getPiece(Position position) const;

            /*
            Return the board as a vector
            */
            std::vector<std::vector<Piece>> getBoard() const;

            /*
            Sets the game's turn
            */
            void setTurn(Piece turn);

            /*
            Sets a piece into the given position
            */
            void setPiece(Position position, Piece piece);

            /*
            Checks if a location is outisde the board or not
            */
            bool isValidPosition(Position position) const;

            /*
            Make the turn the opposite of what it already is
            */
            void makeTurnOpposite();

            /*
            Check whether a move is legal or not
            */
            bool isLegalMove(Position position) const;

            /*
            Get all moves that are legal
            */
            std::vector<Position> getLegalMoves() const;

            /*
            Place a piece
            */
            void placePiece(Position position);

            /*
            Make a move and place a piece
            */
            void move(Position position);

            /*
            Print the board and optionally show legal moves
            */
            void printBoard(bool showLegalMoves=false) const;

            /*
            Get the total amount of empty spots
            */
            int getEmptySpotCount() const;

            /*
            Get the total amount of occupied spots
            */
            int getTotalPieceCount() const;

            /*
            Get the total amount of white pieces
            */
            int getWhitePieceCount() const;

            /*
            Get the total amount of black pieces
            */
            int getBlackPieceCount() const;

            /*
            Determine if the game has ended or not. If it has ended then the return value
            is true, else it's false
            */
            bool isEnd();

            /*
            Get the final score of winner, if zero then it's a draw.
            The score of a winner(if there's one) is calculated by not only their current pieces
            but also the reamining empty spots
            Only used when the game has ended.
            */
            int getFinalScoreOfWinner() const;

            /*
            Returns the winner as a piece. If it's a tie then an empty piece is returned
            */
            Piece getWinner() const;

            constexpr static std::array<Position, 8> directions = {
                Position{1, 1}, Position{1, 0}, Position{1, -1}, Position{0, 1},
                Position{0, -1}, Position{-1, 1}, Position{-1, 0}, Position{-1, -1} 
            };

        private:
            Piece m_board[BOARD_SIZE][BOARD_SIZE];

            Piece m_turn;
    };

}
