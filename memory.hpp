#include <wx/defs.h>
#include <wx/sizer.h>
#include <wx/wx.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <iomanip>
#include <regex>
#include <string>
#include <vector>

class Memory {
 private:
  bool point_pressed = false;
  bool need_to_clear = true;
  bool is_p_pressed = false;
  bool is_f_pressed = false;
  unsigned int cnt = 0;
  const unsigned int max_digits = 8;

  wxTextCtrl* display;
  wxTextCtrl** registers;
  wxTextCtrl** ring_buffer;

  float numbered_registers[9];  // Нумерованные регистры
  std::vector<float> stack{7, 0};  // Кольцевой стек регистров
  std::function<void(Memory&)> operations[50] = {
      &Memory::press_zero,  &Memory::press_one,   &Memory::press_two,
      &Memory::press_three, &Memory::press_four,  &Memory::press_five,
      &Memory::press_six,   &Memory::press_seven, &Memory::press_eight,
      &Memory::press_nine,  &Memory::add,         &Memory::sub,
      &Memory::multiply,    &Memory::div,         &Memory::power,
      &Memory::arrow_up,    &Memory::swap,        &Memory::left_shift,
      &Memory::right_shift, &Memory::sign,        &Memory::vo,
      &Memory::vp,          &Memory::sp,          &Memory::p,
      &Memory::pp,          &Memory::cx,          &Memory::f,
      &Memory::bp,          &Memory::pnt};  // Массив операций

  std::vector<float>
      program_memory;  // Специальный раздел памяти для хранения программ
  void press_zero();
  void press_one();
  void press_two();
  void press_three();
  void press_four();
  void press_five();
  void press_six();
  void press_seven();
  void press_eight();
  void press_nine();
  void add();
  void sub();
  void multiply();
  void exp();
  void div();
  void ln();
  void pi();
  void cos();
  void sin();
  void power();
  void square();
  void sqrt();
  void reciprocal();
  void arrow_up();
  void sign();
  void right_shift();
  void left_shift();
  void swap();

  void vo();
  void vp();
  void sp();
  void p();
  void pp();
  void cx();
  void f();
  void bp();
  void pnt();
  float take_from_display(wxTextCtrl*);

 public:
  Memory(wxTextCtrl*, wxTextCtrl**, wxTextCtrl**);
  void act(int);
};