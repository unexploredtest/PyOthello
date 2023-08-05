#include "headers/Othello.hpp"

namespace othello {

    Othello::Othello() {
        initializeBoard();
        m_turn = Piece::Black;
    }

    Othello::Othello(const Othello& othello) {
        for(int y = 0; y < BOARD_SIZE; y++) {
            for(int x = 0; x < BOARD_SIZE; x++) {
                Position position{x, y};
                setPiece(position, othello.getPiece(position));
            }
        }

        m_turn = othello.getTurn();
    }

    void Othello::initializeBoard() {
            // setting all squares to zero
            for(int y = 0; y < BOARD_SIZE; y++) {
                for(int x = 0; x < BOARD_SIZE; x++) {
                    Position position{x, y};
                    setPiece(position, Piece::Empty);
                }
            }

            // setting the initial square
            setPiece(Position{3, 3}, Piece::White);
            setPiece(Position{4, 4}, Piece::White);

            setPiece(Position{4, 3}, Piece::Black);
            setPiece(Position{3, 4}, Piece::Black);
    }

    bool Othello::isValidPosition(Position position) const {
        if(position.x >= BOARD_SIZE || position.y >= BOARD_SIZE
        || position.x < 0 || position.y < 0) {
            return false;
        } else {
            return true;
        }
    }

    Piece Othello::getPiece(Position position) const {
        return m_board[position.y][position.x];
    }

    Piece Othello::getTurn() const {
        return m_turn;
    }

    std::vector<std::vector<Piece>> Othello::getBoard() const {
        std::vector<std::vector<Piece>> board = std::vector<std::vector<Piece>>(BOARD_SIZE);
        for(int i = 0; i < BOARD_SIZE; i++) {
            std::vector<Piece> row = std::vector<Piece>(BOARD_SIZE);
            for(int j = 0; j < BOARD_SIZE; j++) {
                row[j] = m_board[i][j];
            }
            board[i] = row;
        }
        return board;
    }

    void Othello::setTurn(Piece turn) {
        m_turn = turn;
    }

    void Othello::setPiece(Position position, Piece piece) {
        m_board[position.y][position.x] = piece;
    }

    void Othello::makeTurnOpposite() {
        if(m_turn == Piece::Black) {
            m_turn = Piece::White;
        } else {
            m_turn = Piece::Black;
        }
    }

    bool Othello::isLegalMove(Position position) const {
        Piece currentPiece = m_turn;
        Piece oppositePiece;
        if(currentPiece == Piece::Black) {
            oppositePiece = Piece::White;
        } else {
            oppositePiece = Piece::Black;
        }

        // The square should be a valid position
        if(!isValidPosition(position)) {
            return false;
        }

        // There shoudn't be a piece in the current square
        if(getPiece(position) != Piece::Empty) {
            return false;
        }

        for(Position direction: directions) {

            int deltaX = direction.x;
            int deltaY = direction.y;

            Position nextPosition = Position{position.x+deltaX, position.y+deltaY};
            if(!(isValidPosition(nextPosition) && getPiece(nextPosition) == oppositePiece)) {
                continue;
            }

            while(true) {
                nextPosition = Position{nextPosition.x+deltaX, nextPosition.y+deltaY};
                if(!isValidPosition(nextPosition)) {
                    break;
                }
                Piece nextPiece = getPiece(nextPosition);
                if(nextPiece == Piece::Empty) {
                    break;
                } else if(nextPiece == currentPiece) {
                    return true;
                } else {
                    continue;
                }
            }
        }

        // If non are applicable, then it means the current sqaure is not a legal move
        return false;
    }

    std::vector<Position> Othello::getLegalMoves() const {
        std::vector<Position> legalPositions = std::vector<Position>();
        for(int x = 0; x < BOARD_SIZE; x++) {
            for(int y = 0; y < BOARD_SIZE; y++) {
                if(isLegalMove(Position{x, y})) {
                    Position legalPosition = {x, y};
                    legalPositions.push_back(legalPosition);
                }
            }
        }
        return legalPositions;
    } 

    void Othello::placePiece(Position position) {
        Piece currentPiece = m_turn;
        Piece oppositePiece;
        if(currentPiece == Piece::Black) {
            oppositePiece = Piece::White;
        } else {
            oppositePiece = Piece::Black;
        }

        std::vector<Position> piecesToChange;

        for(Position direction: directions) {

            int deltaX = direction.x;
            int deltaY = direction.y;

            Position nextPosition = Position{position.x+deltaX, position.y+deltaY};
            if(!(isValidPosition(nextPosition) && getPiece(nextPosition) == oppositePiece)) {
                continue;
            }

            // while(isValidPosition(nextPosition))
            for(int i = 1; ; i++) {
                nextPosition = Position{nextPosition.x+deltaX, nextPosition.y+deltaY};
                if(!isValidPosition(nextPosition)) {
                    break;
                }
                Piece nextPiece = getPiece(nextPosition);
                if(nextPiece == Piece::Empty) {
                    break;
                } else if(nextPiece == currentPiece) {
                    for(int j = 1; j <= i; j++) {
                        Position pieceToChange = Position();
                        pieceToChange.x = position.x + j*deltaX;
                        pieceToChange.y = position.y + j*deltaY;

                        piecesToChange.push_back(pieceToChange);
                    }
                } else {
                    continue;
                }
            }
        }

        for(Position position: piecesToChange) {
            setPiece(position, currentPiece);
        }

        setPiece(position, currentPiece);
    }

    void Othello::move(Position position) {
        placePiece(position);
        makeTurnOpposite();
        // If the next player has no legal moves but the other player does, then the game 
        // still continues and it would be the other player's turn
        if(getLegalMoves().size() == 0) {
            makeTurnOpposite();
        }
    }


    void Othello::printBoard(bool showLegalMoves) const {
        for(int y = 0; y < BOARD_SIZE; y++) {
            for(int x = 0; x < BOARD_SIZE; x++) {
                Position position = Position{x, y};
                if(getPiece(position) == Piece::Black) {
                    std::cout << "B";
                } else if(getPiece(position) == Piece::White) {
                    std::cout << "W";
                } else if(showLegalMoves && isLegalMove(position)) {
                    std::cout << "X";
                } else {
                    std::cout << "O";
                }
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    int Othello::getEmptySpotCount() const {
        int count = 0;
        for(int y = 0; y < BOARD_SIZE; y++) {
            for(int x = 0; x < BOARD_SIZE; x++) {
                Position position = Position{x, y};
                if(getPiece(position) == Piece::Empty) {
                    count++;
                }
            }
        }
        return count;
    }

    bool Othello::isEnd() {



        // if both players have no legal moves left, then it's over
        if(this->getLegalMoves().size() == 0) {
            // checking whether the second player has any moves left or not
            makeTurnOpposite();
            if(this->getLegalMoves().size() == 0) {
                return true;
            }
            // returning it to the initial turn
            makeTurnOpposite();
        }
        return false;
    }

    int Othello::getTotalPieceCount() const {
        // basically calculating pieces
        int whitePieceCount = 0;
        for(int y = 0; y < BOARD_SIZE; y++) {
            for(int x = 0; x < BOARD_SIZE; x++) {
                Position position = Position{x, y};
                if(getPiece(position) != Piece::Empty) {
                    whitePieceCount++;
                }
            }
        }
        return whitePieceCount;
    }

    int Othello::getWhitePieceCount() const {
        // basically calculating all white's pieces
        int whitePieceCount = 0;
        for(int y = 0; y < BOARD_SIZE; y++) {
            for(int x = 0; x < BOARD_SIZE; x++) {
                Position position = Position{x, y};
                if(getPiece(position) == Piece::White) {
                    whitePieceCount++;
                }
            }
        }
        return whitePieceCount;
    }

    int Othello::getBlackPieceCount() const {
        // basically calculating all black's pieces
        int blackPieceCount = 0;
        for(int y = 0; y < BOARD_SIZE; y++) {
            for(int x = 0; x < BOARD_SIZE; x++) {
                Position position = Position{x, y};
                if(getPiece(position) == Piece::Black) {
                    blackPieceCount++;
                }
            }
        }
        return blackPieceCount;
    }

    int Othello::getFinalScoreOfWinner() const {
        int whitePieceCount = getWhitePieceCount();
        int blackPieceCount = getBlackPieceCount();
        int emptyTiles = 64 - whitePieceCount - blackPieceCount;

        if(whitePieceCount > blackPieceCount) {
            return whitePieceCount + emptyTiles;
        } else if(whitePieceCount < blackPieceCount)  {
            return blackPieceCount + emptyTiles;
        } else {
            return 0;
        }
    }

    Piece Othello::getWinner() const {
        int blackScore = getBlackPieceCount();
        int whiteScore = getWhitePieceCount();
        if(whiteScore > blackScore) {
            return Piece::White;
        } else if(whiteScore < blackScore) {
            return Piece::Black;
        } else {
            return Piece::Empty;
        }
    }

}