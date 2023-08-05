#include "Othello.hpp"

#pragma once

namespace othello {

    struct Node {
        std::vector<Position> positionHierarchy;
        int score;
    };

    class OthelloSolver : public Othello {
        public:

            /*
            Infinity is basically a valur that's used in minimax as a number that's bigger than
            any score and used when someone is winning or losing.
            */
            static const int MINIMAX_INFINITY = 10000000;

            /*
            An estimate of the actual value of the corner, basically more than everything other than infinity
            */
            static const int CORNER_VALUE = 1000000;

            /*
            Evaluating the current position, arguement prevLegalMoves is the previous moves
            that was available to the other player. It's used because it can be an indicator
            of how good the current position is
            */
            int evaluate(int prevLegalMoves);

            /*
            More spicifically alpha-beta pruning. prevLegalMoves is used only when the game
            has ended or the max depth has reached and is passed to the evaluate method
            */ 
            Node miniMax(OthelloSolver board, int depth, int alpha, int beta, int prevLegalMoves=0);

            /*
            Finding the best node for the player
            */ 
            Node solve(int depth, int lastMoves);

            /*
            Make the best move availabe
            */ 
            void makeSmartMove(int depth, int lastMoves);

            static int max(int valueOne, int valueTwo) {
                if(valueOne > valueTwo) {
                    return valueOne;
                } else {
                    return valueTwo;
                }
            }
            static int min(int valueOne, int valueTwo) {
                if(valueOne < valueTwo) {
                    return valueOne;
                } else {
                    return valueTwo;
                }
            }
    };
}