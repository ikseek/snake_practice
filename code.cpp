#include <Windows.h>
#include <algorithm>
#include <cassert>
#include <conio.h>
#include <iostream>
#include <vector>
using namespace std;

struct Point {
  int x;
  int y;
  Point(int x1, int y1) : x(x1), y(y1) {}
  bool operator==(const Point &rhs) { return ((rhs.x == x) && (rhs.y == y)); }
};

bool is_point_in_snake(const vector<Point> &snake, Point &point, int n) {
  for (int k = 0; k < n; k++)
    if (point == snake[k])
      return true;
  return false;
}

void case_d(vector<Point> &snake, Point &point, char &direction,
            char old_direction, bool &is_on_wrong_button, bool &game_over) {
  if ((point.y == snake[snake.size() - 2].y) &&
          (snake[snake.size() - 2].x < point.x) ||
      (point.y != snake[snake.size() - 2].y))
    point.x += 1;
  else
    is_on_wrong_button = true;
}
void case_a(vector<Point> &snake, Point &point, char &direction,
            char old_direction, bool &is_on_wrong_button, bool &game_over) {
  if ((point.y == snake[snake.size() - 2].y) &&
          (snake[snake.size() - 2].x > point.x) ||
      (point.y != snake[snake.size() - 2].y))
    point.x -= 1;
  else
    is_on_wrong_button = true;
}
void case_w(vector<Point> &snake, Point &point, char &direction,
            char old_direction, bool &is_on_wrong_button, bool &game_over) {
  if ((point.x == snake[snake.size() - 2].x) &&
          (snake[snake.size() - 2].y < point.y) ||
      (point.x != snake[snake.size() - 2].x))
    point.y += 1;
  else
    is_on_wroquantity_foodng_button = true;
}
void case_s(vector<Point> &snake, Point &point, char &direction,
            char old_direction, bool &is_on_wrong_button, bool &game_over) {
  if ((point.x == snake[snake.size() - 2].x) &&
          (snake[snake.size() - 2].y > point.y) ||
      (point.x != snake[snake.size() - 2].x))
    point.y -= 1;
  else
    is_on_wrong_button = true;
}

press_button(vector<Point> &snake, Point &point, char &direction,
             char old_direction, bool &is_on_wrong_button, bool &game_over) {
  switch (direction) {
  case 'd':
    case_d(snake, point, direction, old_direction, is_on_wrong_button,
           game_over);
    break;
  case 'a':
    case_a(snake, point, direction, old_direction, is_on_wrong_button,
           game_over);
    break;
  case 'w':
    case_w(snake, point, direction, old_direction, is_on_wrong_button,
           game_over);
    break;
  case 's':
    case_s(snake, point, direction, old_direction, is_on_wrong_button,
           game_over);

    break;
  default:
    is_on_wrong_button = true;
  }
}
int move_snake(vector<Point> &snake, Point &point, char &direction,
               char old_direction, bool &game_over, bool **food, size_t &count,
               size_t &quantity_food) {
  bool is_on_wrong_button = false;
  press_button(snake, point, direction, old_direction, is_on_wrong_button,
               game_over);

  if (game_over)
    return 0;
  if (is_on_wrong_button) {
    direction = old_direction;
    move_snake(snake, point, direction, direction, game_over, food, count,
               quantity_food);
  } else {
    snake.push_back(point);
    if (food[point.y][point.x]) { // assert(false);
      food[point.y][point.x] = false;
      quantity_food--;
      count++;
    } else
      snake.erase(snake.begin());
  }
  if ((point.x == 0) || (point.y == 0) || (point.x == 14) || (point.y == 14) ||
      is_point_in_snake(snake, point, snake.size() - 3)) {
    game_over = true;
    return 0;
  }
}
void draw_game(const vector<Point> &snake, bool **food, size_t &quantity_food) {
  int size = 15;
  quantity_food = 0;
  int number_of_last_symbol = size - 1;
  for (int j = 0; j < size; j++) {
    if ((j != 0) && (j != number_of_last_symbol))
      for (int i = 0; i < size; i++) {
        Point p(i, number_of_last_symbol - j);
        if ((i == 0) || (i == number_of_last_symbol))
          cout << '|';
        else {
          if (is_point_in_snake(snake, p, snake.size()))
            cout << 'O';
          else if (food[number_of_last_symbol - j][i]) {
            cout << '*';
            quantity_food++;
          } else
            cout << ' ';
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
void give_food(bool **food, size_t quantity_food, size_t size_food) {
  for (int i = 0; i < size_food; i++)
    for (int j = 0; j < size_food; j++)
      food[i][j] = false;
  for (int i = 0; i < quantity_food; i++)
    food[rand() % size_food][rand() % size_food] = true;
}
int main() {
  size_t size_food = 15;
  size_t count = 0;
  size_t quantity_food = 5;
  bool **food = new bool *[size_food];
  for (int i = 0; i < size_food; i++)
    food[i] = new bool[size_food];
  for (int i = 0; i < size_food; i++)
    for (int j = 0; j < size_food; j++)
      food[i][j] = false;
  bool game_over = false;
  char direction = 'd';
  vector<Point> snake;
  Point point(2, 2);
  snake.push_back(point);
  for (int j = 0; j < 6; j++) {
    point.x = 2 + j + 1;
    snake.push_back(point);
  }
  Point point1 = snake.back();
  give_food(food, quantity_food, size_food);
  while (true) {
    char old_direction = direction;
    draw_game(snake, food, quantity_food);
    if (quantity_food == 0)
      give_food(food, 5, size_food);
    Sleep(1000);
    system("cls");
    if (kbhit()) {
      direction = getch();
    }
    move_snake(snake, point1, direction, old_direction, game_over, food, count,
               quantity_food);
    if (game_over)
      break;
  }
  system("cls");
  cout << "Game over" << endl;
  cout << count;
  Sleep(5000);
  return 0;
}