// ============================================================
// Board.cpp
// ------------------------------------------------------------
// Board.h で宣言したクラスの実装
// ============================================================
#include "Board.h"
#include <iostream>

// ------------------------------------------------------------
// コンストラクタ：盤面を空の状態で初期化
// ------------------------------------------------------------
Board::Board() {
    reset();
}

// ------------------------------------------------------------
// 盤面をリセット（全マスを Empty にする）
// ------------------------------------------------------------
void Board::reset() {
    cells_.fill(Cell::Empty);
}

// ------------------------------------------------------------
// 指定位置に駒を配置
// ------------------------------------------------------------
bool Board::placeMark(int position, Cell cell) {
    // 範囲チェック（1〜9 以外は拒否）
    if (position < 1 || position > CELL_COUNT) {
        return false;
    }

    // 内部配列のインデックスに変換（1〜9 → 0〜8）
    const int index = position - 1;

    // すでに埋まっているマスには置けない
    if (cells_[index] != Cell::Empty) {
        return false;
    }

    cells_[index] = cell;
    return true;
}

// ------------------------------------------------------------
// 勝敗判定
// ------------------------------------------------------------
GameResult Board::checkResult() const {
    // 勝利条件となる8つのライン（横3・縦3・斜め2）
    static constexpr int winLines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // 横ライン
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // 縦ライン
        {0, 4, 8}, {2, 4, 6}             // 斜めライン
    };

    // 各ラインをチェック
    for (const auto& line : winLines) {
        const Cell a = cells_[line[0]];
        const Cell b = cells_[line[1]];
        const Cell c = cells_[line[2]];

        // 3マスとも同じ駒で、かつ空でない場合は勝利
        if (a != Cell::Empty && a == b && b == c) {
            return (a == Cell::Circle) ? GameResult::CircleWin
                : GameResult::CrossWin;
        }
    }

    // 空マスが1つでもあればゲーム続行中
    for (const Cell& cell : cells_) {
        if (cell == Cell::Empty) {
            return GameResult::InProgress;
        }
    }

    // 勝者なし＆空マスなし → 引き分け
    return GameResult::Draw;
}

// ------------------------------------------------------------
// セルの表示文字を取得
// （空マスには番号を表示することで、プレイヤーが選びやすくする）
// ------------------------------------------------------------
std::string Board::cellToString(int index) const {
    switch (cells_[index]) {
    case Cell::Circle: return "O";
    case Cell::Cross:  return "X";
    case Cell::Empty:  return std::to_string(index + 1); // 番号を表示
    }
    return " "; // ここには到達しないはず
}

// ------------------------------------------------------------
// 盤面をコンソールに表示
// ------------------------------------------------------------
void Board::print() const {
    std::cout << "\n";
    for (int row = 0; row < SIZE; ++row) {
        // マスの内容を1行分表示
        std::cout << "  ";
        for (int col = 0; col < SIZE; ++col) {
            const int index = row * SIZE + col;
            std::cout << " " << cellToString(index) << " ";
            if (col < SIZE - 1) {
                std::cout << "|";
            }
        }
        std::cout << "\n";

        // 行の区切り線（最終行以外）
        if (row < SIZE - 1) {
            std::cout << "  ---+---+---\n";
        }
    }
    std::cout << "\n";
}