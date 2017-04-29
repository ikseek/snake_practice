#include <iostream>

#include <Windows.h>
#include <algorithm>
#include <cassert>
#include <conio.h>
#include <vector>
using namespace std;

struct Point {
  int x;
  int y;
  Point(int x1, int y1) : x(x1), y(y1) {}
  bool operator==(const Point &rhs) { return ((rhs.x == x) && (rhs.y == y)); }
};

bool Find(const vector<Point> &snake, Point &point, int n) {
  for (int k = 0; k < n; k++)
    // if (snake[k] == Point(i, number_of_last_symbol - j ))
    if (point == snake[k])
      return true;
  return false;
}

int move_snake(vector<Point> &snake, Point &point, char &direction,
               char old_direction, bool &game_over) {
  bool is_on_wrong_button = false;
  switch (direction) {
  case 'd': {
    if ((point.y == snake[snake.size() - 2].y) &&
            (snake[snake.size() - 2].x < point.x) ||
        (point.y != snake[snake.size() - 2].y))
      point.x += 1;
    else {
      is_on_wrong_button = true;
    }
  } break;
  case 'a': {
    if ((point.y == snake[snake.size() - 2].y) &&
            (snake[snake.size() - 2].x > point.x) ||
        (point.y != snake[snake.size() - 2].y))
      point.x -= 1;
    else {
      is_on_wrong_button = true;
    }
  } break;
  case 'w': {
    if ((point.x == snake[snake.size() - 2].x) &&
            (snake[snake.size() - 2].y < point.y) ||
        (point.x != snake[snake.size() - 2].x))
      point.y += 1;
    else {
      is_on_wrong_button = true;
    }
  } break;
  case 's': {
    if ((point.x == snake[snake.size() - 2].x) &&
            (snake[snake.size() - 2].y > point.y) ||
        (point.x != snake[snake.size() - 2].x))
      point.y -= 1;
    else {
      is_on_wrong_button = true;
    }
  } break;
  default: {
    is_on_wrong_button = true;
  }
  }
  if (is_on_wrong_button) {
    direction = old_direction;
    move_snake(snake, point, direction, old_direction, game_over);
  }
  if (game_over)
    return 0;
  if (!is_on_wrong_button) {
    snake.push_back(point);
    snake.erase(snake.begin());
  }
  if ((point.x == 0) || (point.y == 0) || (point.x == 14) || (point.y == 14) ||
      Find(snake, point, snake.size() - 3)) {
    game_over = true;
    return 0;
  }
}

void draw_game_block(const vector<Point> &snake, Point& p) {
  if (Find(snake, p, snake.size()))
    cout << 'O';
  else
    cout << ' ';
}

void draw_game(const vector<Point> &snake) {
  int size = 15;
  int number_of_last_symbol = size - 1;
  for (int j = 0; j < size; j++) {
    if ((j != 0) && (j != number_of_last_symbol))
      for (int i = 0; i < size; i++) {
        Point p(i, number_of_last_symbol - j);
        if ((i == 0) || (i == number_of_last_symbol))
          cout << '|';
        else {
          draw_game_block(snake, p);
        }
      }
    else
      for (int i = 0; i < size; i++)
        if (i % 2 == 0)
          cout << '+';
        else
          cout << '-';
    cout << endl;
  }
}

int main() {
  bool game_over = false;
  char direction = 'd';
  vector<Point> snake;
  Point point(2, 2);
  snake.push_back(point);
  for (int j = 0; j < 6; j++) {
    point.x = 2 + j + 1;
    snake.push_back(point);
  }
  //  в следующей строке внес изменение
  Point point1 = snake.back();
  while (true) {
    char old_direction = direction;
    draw_game(snake);
    Sleep(1000);
    system("cls");
    if (kbhit()) {
      direction = getch();
    }
    move_snake(snake, point1, direction, old_direction, game_over);
    if (game_over)
      break;
  }
  system("cls");
  cout << "Game over";
  Sleep(5000);
  return 0;
}