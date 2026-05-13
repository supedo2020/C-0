#pragma once

// ============================================================
// Board.h
// ------------------------------------------------------------
// 三目並べの「盤面」を表すクラスの宣言
// - 盤面データの保持
// - マスへの配置
// - 勝敗判定
// - 盤面表示
// ============================================================
#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <string>

// マスの状態を表す列挙型（型安全のため enum class を使用）
enum class Cell {
    Empty,  // 空マス
    Circle, // 〇（プレイヤー1）
    Cross   // ×（プレイヤー2）
};

// ゲームの結果を表す列挙型
enum class GameResult {
    InProgress,  // ゲーム続行中
    CircleWin,   // 〇の勝利
    CrossWin,    // ×の勝利
    Draw         // 引き分け
};

class Board {
public:
    // 盤面のサイズ（3×3）
    static constexpr int SIZE = 3;
    static constexpr int CELL_COUNT = SIZE * SIZE;

    // コンストラクタ：盤面を空の状態で初期化
    Board();

    // 盤面をリセット（再プレイ用）
    void reset();

    // 指定したマスに駒を配置する
    // position : 1〜9 のマス番号
    // cell     : 配置する駒（Circle または Cross）
    // 戻り値   : 配置に成功したら true、失敗（範囲外 or 既に埋まっている）なら false
    bool placeMark(int position, Cell cell);

    // 現在の勝敗状態を判定して返す
    GameResult checkResult() const;

    // 盤面をコンソールに表示する
    void print() const;

private:
    // 盤面データ（1次元配列として扱う：インデックス 0〜8）
    std::array<Cell, CELL_COUNT> cells_;

    // Cell を表示用の文字に変換するヘルパー関数
    // index : マスの位置（空マスの場合は番号を表示するため）
    std::string cellToString(int index) const;
};

#endif // BOARD_H