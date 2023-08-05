#include "headers/OthelloSolver.hpp"

namespace othello {

    int OthelloSolver::evaluate(int prevLegalMoves) {
        if(isEnd()) {
            // The 
            int whiteBlackDiff = getWhitePieceCount() - getBlackPieceCount();
            if(whiteBlackDiff > 0) {
                int whiteScore = whiteBlackDiff + getEmptySpotCount();
                return MINIMAX_INFINITY + whiteScore;
            } else if(whiteBlackDiff < 0) {
                int blackScore = -whiteBlackDiff + getEmptySpotCount();
                return -MINIMAX_INFINITY - blackScore;
            } else {
                return 0;
            }
        } else {
            int currentLegalMoves = getLegalMoves().size();
            if(currentLegalMoves == 0) {
                currentLegalMoves = 1;
            }

            // Mobility ratio is the ratio of the the current available moves and the other
            // player's previous move. If the other player had no moves then it's considered zero
            int mobilityRatio;
            // We also decrease the score from its inverse because if mobility ratio is low, then that
            // means it's bad and we should somehow make it negative if that happens
            int mobilityRatioInverse;


            if(prevLegalMoves == 0) {
                // if the other player had no moves then that means the position is really good
                mobilityRatio = 10000*currentLegalMoves;
                mobilityRatioInverse = 0;
            } else if(getTurn() == Piece::White) {
                if(prevLegalMoves == 0) {
                    mobilityRatio = 10000*currentLegalMoves;
                    mobilityRatioInverse = 0;
                } else {
                    mobilityRatio = (1000*currentLegalMoves) / prevLegalMoves;
                    mobilityRatioInverse = (1000*prevLegalMoves) / currentLegalMoves;
                }
            } else {
                if(prevLegalMoves == 0) {
                    mobilityRatio = 0;
                    mobilityRatioInverse = 10000*currentLegalMoves;
                } else {
                    mobilityRatio = (1000*prevLegalMoves) / currentLegalMoves;
                    mobilityRatioInverse = (1000*currentLegalMoves) / prevLegalMoves;
                }
            }

            int result = getWhitePieceCount() - getBlackPieceCount() + mobilityRatio - mobilityRatioInverse;

            if(getPiece(Position{0, 0}) == Piece::White) {
                result += CORNER_VALUE;
            } else if(getPiece(Position{0, 0}) == Piece::Black) {
                result -= CORNER_VALUE;
            }

            if(getPiece(Position{0, 7}) == Piece::White) {
                result += CORNER_VALUE;
            } else if(getPiece(Position{0, 7}) == Piece::Black) {
                result -= CORNER_VALUE;
            }

            if(getPiece(Position{7, 0}) == Piece::White) {
                result += CORNER_VALUE;
            } else if(getPiece(Position{7, 0}) == Piece::Black) {
                result -= CORNER_VALUE;
            }

            if(getPiece(Position{7, 7}) == Piece::White) {
                result += CORNER_VALUE;
            } else if(getPiece(Position{7, 7}) == Piece::Black) {
                result -= CORNER_VALUE;
            }
            return result;
        }
    }

    Node OthelloSolver::miniMax(OthelloSolver board, int depth, int alpha, int beta, int prevLegalMoves) {
        if(depth == 0 || board.isEnd()) {
            std::vector<Position> positionHierarchy = std::vector<Position>();
            int score = board.evaluate(prevLegalMoves);
            Node lastNode{positionHierarchy, score};
            return lastNode;
        } else {
            std::vector<Position> legalPositions = board.getLegalMoves();
            bool firstNode = true;
            Node extremeNode{std::vector<Position>(), 0};

            for(Position position: legalPositions) {
                OthelloSolver othelloCopy = board;
                othelloCopy.placePiece(position);
                if(othelloCopy.getLegalMoves().size() == 0) {
                    prevLegalMoves = 0;
                } else {
                    othelloCopy.makeTurnOpposite();
                    prevLegalMoves = legalPositions.size();
                }
                Node childNode = miniMax(othelloCopy, depth-1, alpha, beta, prevLegalMoves);
                if(firstNode) {
                    childNode.positionHierarchy.push_back(position);
                    extremeNode = childNode;

                    firstNode = false;
                } else {
                    if(board.getTurn() == Piece::Black) {
                        if(childNode.score < extremeNode.score) {
                            childNode.positionHierarchy.push_back(position);
                            extremeNode = childNode;
                            beta = min(beta, childNode.score);
                        }
                    } else {
                        if(childNode.score > extremeNode.score) {
                            childNode.positionHierarchy.push_back(position);
                            extremeNode = childNode;
                            alpha = max(alpha, childNode.score);
                        }
                    }
                }

                if(beta <= alpha) {
                    break;
                }
            }
            return extremeNode;
        }
    }

    Node OthelloSolver::solve(int depth, int lastMoves) {
        if(getEmptySpotCount() > lastMoves) {
            return miniMax(*this, depth, -MINIMAX_INFINITY, MINIMAX_INFINITY);
        } else {
            return miniMax(*this, -1, -MINIMAX_INFINITY, MINIMAX_INFINITY);
        }
    }

    void OthelloSolver::makeSmartMove(int depth, int lastMoves) {
        Node currentNode = solve(depth, lastMoves);

        // It may be null because the game has ended and it's attempting to use a non-existant node
        if(currentNode.positionHierarchy.size() != 0) {
            Position nextPosition = currentNode.positionHierarchy[currentNode.positionHierarchy.size()-1];
            move(nextPosition);
        }
    }
}