// ============================================================
// main.cpp
// ------------------------------------------------------------
// 三目並べ（〇×ゲーム）
// - 2人のプレイヤーが交互に〇と×を置いて遊ぶ
// - 縦・横・斜めに3つ揃えたら勝ち
// - 全マス埋まると引き分け
// ============================================================
#include "Board.h"
#include <iostream>
#include <limits>
#include <string>

// ------------------------------------------------------------
// プレイヤーから入力を受け取る（入力バリデーション付き）
// 戻り値 : 1〜9 の数字
// ------------------------------------------------------------
int readPlayerInput(const std::string& playerName) {
    int position = 0;
    while (true) {
        std::cout << playerName << " のターン : 置きたいマス番号 (1-9) > ";
        std::cin >> position;

        // 数値以外が入力された場合のエラー処理
        if (std::cin.fail()) {
            std::cin.clear(); // エラー状態をクリア
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  [!] 数字を入力してください。\n";
            continue;
        }

        // 範囲チェック
        if (position < 1 || position > 9) {
            std::cout << "  [!] 1〜9 の範囲で入力してください。\n";
            continue;
        }

        return position;
    }
}

// ------------------------------------------------------------
// 「もう一度遊びますか？」の問い合わせ
// ------------------------------------------------------------
bool askPlayAgain() {
    std::cout << "もう一度遊びますか？ (y/n) > ";
    std::string answer;
    std::cin >> answer;
    return (answer == "y" || answer == "Y" || answer == "yes");
}

// ------------------------------------------------------------
// ゲーム結果に応じたメッセージを表示
// ------------------------------------------------------------
void printResult(GameResult result) {
    std::cout << "==============================\n";
    switch (result) {
    case GameResult::CircleWin:
        std::cout << "  Player 1 (O) の勝利！ \n";
        break;
    case GameResult::CrossWin:
        std::cout << "  Player 2 (X) の勝利！ \n";
        break;
    case GameResult::Draw:
        std::cout << "  引き分けです。\n";
        break;
    default:
        break;
    }
    std::cout << "==============================\n";
}

// ------------------------------------------------------------
// 1ゲーム分のメインループ
// ------------------------------------------------------------
void playOneGame() {
    Board board;

    // 現在のプレイヤー（true: 〇, false: ×）
    bool isCirclePlayerTurn = true;

    while (true) {
        // 1. 盤面を表示
        board.print();

        // 2. 現在のプレイヤー情報を準備
        const Cell currentMark = isCirclePlayerTurn ? Cell::Circle : Cell::Cross;
        const std::string playerName =
            isCirclePlayerTurn ? "Player 1 (O)" : "Player 2 (X)";

        // 3. 入力を受け取る
        const int position = readPlayerInput(playerName);

        // 4. マスに配置を試みる
        if (!board.placeMark(position, currentMark)) {
            std::cout << "  [!] そのマスには置けません。別のマスを選んでください。\n";
            continue; // プレイヤーを変えずに再入力
        }

        // 5. 勝敗判定
        const GameResult result = board.checkResult();
        if (result != GameResult::InProgress) {
            board.print();    // 最終盤面を表示
            printResult(result);
            return;           // ゲーム終了
        }

        // 6. プレイヤーを交代
        isCirclePlayerTurn = !isCirclePlayerTurn;
    }
}

// ------------------------------------------------------------
// エントリーポイント
// ------------------------------------------------------------
int main() {
    std::cout << "==============================\n";
    std::cout << "     三目並べ（〇×ゲーム）   \n";
    std::cout << "==============================\n";
    std::cout << "マス番号の配置：\n";
    std::cout << "   1 | 2 | 3\n";
    std::cout << "  ---+---+---\n";
    std::cout << "   4 | 5 | 6\n";
    std::cout << "  ---+---+---\n";
    std::cout << "   7 | 8 | 9\n\n";

    // 「もう一度遊ぶ」を選んでいる間はゲームを繰り返す
    do {
        playOneGame();
    } while (askPlayAgain());

    std::cout << "ご参加ありがとうございました！\n";
    return 0;
}