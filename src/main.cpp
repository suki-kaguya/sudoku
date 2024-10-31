#include <cstring>
#include <iostream>

// 用于显示帮助信息的函数
static void printHelp() {
    std::cout << std::endl;
    std::cout << "sudoku - a little game in command line" << std::endl
              << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "\t sudoku [-l <progressFile>]" << std::endl << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "\t -l <path> \t specify path of progress file to load, optional." << std::endl
              << std::endl;
}

// 程序的主入口函数
int main(int argc, char **argv)
{
  SetSystemEnv(); // 设置系统环境

  CScene scene; // 创建场景对象

  if (argc == 1) { // 没有传递命令行参数
    InputLanguage(); // 输入语言
    int eraseGridNumber = inputDifficulty(); // 选择难度并获取需要擦除的格子数量
    scene.generate(); // 生成数独题目
    scene.eraseRandomGrids(eraseGridNumber); // 擦除随机格子
  } else if (argc == 3 && !strcmp(argv[1], "-l")) { // 检查是否加载保存的游戏进度
    // load saved game progress
    if (!scene.load(argv[2])) { // 尝试加载进度
      message(I18n::Instance().Get(I18n::Key::LOAD_PROGRESS_FAIL)); // 显示加载失败信息
      return 0;
    }
    InputLanguage(); // 输入语言
  } else { 
    printHelp(); // 打印帮助信息
    return 0;
  }

  scene.setMode(inputKeyMode()); // 设置游戏模式

  scene.play(); // 开始游戏

  return 0;
}