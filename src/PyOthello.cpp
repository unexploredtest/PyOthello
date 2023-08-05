#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "headers/Othello.hpp"
#include "headers/OthelloSolver.hpp"

using namespace othello;

namespace py = pybind11;


PYBIND11_MODULE(PyOthello, m) {

    py::class_<Othello> othello(m, "Othello");
    py::class_<Position> position(m, "Position");
    py::enum_<Piece> piece(m, "Piece");
    py::class_<OthelloSolver> othelloSolver(m, "OthelloSolver", othello);
    py::class_<Node> node(m, "Node");

    othello.def(py::init<>())
        .def("initialize_board", &Othello::initializeBoard)
        .def("get_turn", &Othello::getTurn)
        .def("get_piece", &Othello::getPiece)
        .def("get_board", &Othello::getBoard)
        .def("set_turn", &Othello::setTurn)
        .def("set_piece", &Othello::setPiece)
        .def("is_valid_position", &Othello::isValidPosition)
        .def("make_turn_opposite", &Othello::makeTurnOpposite)
        .def("is_legal_move", &Othello::isLegalMove)
        .def("get_legal_moves", &Othello::getLegalMoves)
        .def("place_piece", &Othello::placePiece)
        .def("move", &Othello::move)
        .def("print_board", &Othello::printBoard)
        .def("get_empty_spot_count", &Othello::getEmptySpotCount)
        .def("get_total_piece_count", &Othello::getTotalPieceCount)
        .def("get_white_piece_count", &Othello::getWhitePieceCount)
        .def("get_black_piece_count", &Othello::getBlackPieceCount)
        .def("is_end", &Othello::isEnd)
        .def("get_final_score_of_winner", &Othello::getFinalScoreOfWinner)
        .def("get_winner", &Othello::getWinner);

    position.def(py::init<>())
        .def_readwrite("x", &Position::x)
        .def_readwrite("y", &Position::y);

    
    piece.value("Empty", Piece::Empty)
        .value("Black", Piece::Black)
        .value("White", Piece::White);

    othelloSolver.def(py::init<>())
        .def("evaluate", &OthelloSolver::evaluate)
        .def("mini_max", &OthelloSolver::miniMax)
        .def("solve", &OthelloSolver::solve)
        .def("make_smart_move", &OthelloSolver::makeSmartMove);

    node.def(py::init<>())
        .def_readwrite("x", &Node::positionHierarchy)
        .def_readwrite("y", &Node::score);
}