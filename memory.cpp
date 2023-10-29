#include "memory.hpp"

Memory::Memory(wxTextCtrl* another_display, wxTextCtrl** regs,
               wxTextCtrl** ring) {
  registers = regs;
  ring_buffer = ring;

  display = another_display;
  display->AppendText('0');
  program_memory.resize(60);
  for (int i = 0; i < 9; i++) {
    numbered_registers[i] = 0;
  }
};

float Memory::take_from_display(wxTextCtrl* container) {
  std::string label = container->GetValue().ToStdString();
  float value = std::stof(label);
  return value;
}

std::string remove_trailing_zeros(std::string num) {
  std::string res = num;
  if (res.find('.') == -1) {
    return res;
  }
  while (res[res.size() - 1] == '0') {
    res.erase(res.end() - 1);
  }
  if (res[res.size() - 1] == '.') {
    res.erase(res.end() - 1);
  }

  return res;
}

void Memory::add() {
  if (is_p_pressed) {
    sin();
    is_p_pressed = false;
    return;
  }
  numbered_registers[0] = Memory::take_from_display(registers[0]);

  float x = numbered_registers[0];
  float y = numbered_registers[1];

  numbered_registers[0] = x + y;
  stack[0] = numbered_registers[0];

  std::string str =
      remove_trailing_zeros(std::to_string(numbered_registers[0]));
  display->Clear();
  display->AppendText(str);

  registers[0]->Clear();
  registers[0]->AppendText(str);

  point_pressed = false;
  need_to_clear = true;
}

void Memory::sub() {
  if (is_p_pressed) {
    cos();
    is_p_pressed = false;
    return;
  }
  numbered_registers[0] = Memory::take_from_display(registers[0]);

  float x = numbered_registers[0];
  float y = numbered_registers[1];

  numbered_registers[0] = y - x;
  stack[0] = numbered_registers[0];

  std::string str =
      remove_trailing_zeros(std::to_string(numbered_registers[0]));
  display->Clear();
  display->AppendText(str);

  registers[0]->Clear();
  registers[0]->AppendText(str);

  point_pressed = false;
  need_to_clear = true;
}

void Memory::multiply() {
  if (is_p_pressed) {
    pi();
    is_p_pressed = false;
    return;
  }
  numbered_registers[0] = Memory::take_from_display(registers[0]);
  float x = numbered_registers[0];
  float y = numbered_registers[1];

  numbered_registers[0] = x * y;
  stack[0] = numbered_registers[0];

  std::string str =
      remove_trailing_zeros(std::to_string(numbered_registers[0]));
  display->Clear();
  display->AppendText(str);

  registers[0]->Clear();
  registers[0]->AppendText(str);

  point_pressed = false;
  need_to_clear = true;
}

void Memory::exp() {
  numbered_registers[0] = Memory::take_from_display(registers[0]);
  numbered_registers[0] = std::pow(M_E, numbered_registers[0]);
  stack[0] = numbered_registers[0];
  std::string str =
      remove_trailing_zeros(std::to_string(numbered_registers[0]));
  display->Clear();
  display->AppendText(str);

  registers[0]->Clear();
  registers[0]->AppendText(str);

  point_pressed = false;
  need_to_clear = true;
}

void Memory::div() {
  if (is_p_pressed) {
    exp();
    is_p_pressed = false;
    return;
  }
  numbered_registers[0] = Memory::take_from_display(registers[0]);
  float x = numbered_registers[0];
  float y = numbered_registers[1];
  if (x == 0) {
    display->Clear();
    display->AppendText("Error: div by 0");
    numbered_registers[0] = 0;
    registers[0]->Clear();
    registers[0]->AppendText('0');
    point_pressed = false;
    need_to_clear = true;
    return;
  }

  numbered_registers[0] = y / x;
  stack[0] = numbered_registers[0];

  std::string str =
      remove_trailing_zeros(std::to_string(numbered_registers[0]));
  display->Clear();
  display->AppendText(str);

  registers[0]->Clear();
  registers[0]->AppendText(str);

  point_pressed = false;
  need_to_clear = true;
}

void Memory::press_one() {
  if (is_p_pressed) {
    display->Clear();
    display->AppendText("Error: incorrect input");
    numbered_registers[0] = 0;
    registers[0]->Clear();
    registers[0]->AppendText('0');
    need_to_clear = true;
    is_p_pressed = false;
    return;
  }
  if (is_f_pressed) {
    display->Clear();
    display->AppendText(
        remove_trailing_zeros(std::to_string(take_from_display(registers[1]))));
    is_f_pressed = false;
  } else {
    if (need_to_clear) {
      display->Clear();
      registers[0]->Clear();
      cnt = 0;
      need_to_clear = false;
    }
    if (cnt < max_digits) {
      display->AppendText('1');
      registers[0]->AppendText('1');
      cnt++;
    }
  }
}
void Memory::press_two() {
  if (is_p_pressed) {
    numbered_registers[0] = take_from_display(registers[0]);
    stack[0] = numbered_registers[0];
    display->Clear();
    display->AppendText('0');
    numbered_registers[3] = numbered_registers[0];
    registers[3]->Clear();
    registers[3]->AppendText(
        remove_trailing_zeros(std::to_string(numbered_registers[0])));
    is_p_pressed = false;
    need_to_clear = true;
    return;
  }
  if (is_f_pressed) {
    display->Clear();
    display->AppendText(
        remove_trailing_zeros(std::to_string(take_from_display(registers[2]))));
    is_f_pressed = false;
  } else {
    if (need_to_clear) {
      display->Clear();
      registers[0]->Clear();
      cnt = 0;
      need_to_clear = false;
    }
    if (cnt < max_digits) {
      display->AppendText('2');
      registers[0]->AppendText('2');
      cnt++;
    }
  }
}
void Memory::press_three() {
  if (is_p_pressed) {
    numbered_registers[0] = take_from_display(registers[0]);
    stack[0] = numbered_registers[0];
    display->Clear();
    display->AppendText('0');
    numbered_registers[3] = numbered_registers[0];
    registers[3]->Clear();
    registers[3]->AppendText(
        remove_trailing_zeros(std::to_string(numbered_registers[0])));
    is_p_pressed = false;
    need_to_clear = true;
    return;
  }
  if (is_f_pressed) {
    display->Clear();
    display->AppendText(
        remove_trailing_zeros(std::to_string(take_from_display(registers[3]))));
    is_f_pressed = false;
  } else {
    if (need_to_clear) {
      display->Clear();
      registers[0]->Clear();
      need_to_clear = false;
      cnt = 0;
    }
    if (cnt < max_digits) {
      display->AppendText('3');
      registers[0]->AppendText('3');
      cnt++;
    }
  }
}
void Memory::press_four() {
  if (is_p_pressed) {
    numbered_registers[0] = take_from_display(registers[0]);
    stack[0] = numbered_registers[0];
    display->Clear();
    display->AppendText('0');
    numbered_registers[4] = numbered_registers[0];
    registers[4]->Clear();
    registers[4]->AppendText(
        remove_trailing_zeros(std::to_string(numbered_registers[0])));
    is_p_pressed = false;
    need_to_clear = true;
    return;
  }
  if (is_f_pressed) {
    display->Clear();
    display->AppendText(
        remove_trailing_zeros(std::to_string(take_from_display(registers[4]))));
    is_f_pressed = false;
  } else {
    if (need_to_clear) {
      display->Clear();
      registers[0]->Clear();
      need_to_clear = false;
      cnt = 0;
    }
    if (cnt < max_digits) {
      display->AppendText('4');
      registers[0]->AppendText('4');
      cnt++;
    }
  }
}
void Memory::press_five() {
  if (is_p_pressed) {
    numbered_registers[0] = take_from_display(registers[0]);
    stack[0] = numbered_registers[0];
    display->Clear();
    display->AppendText('0');
    numbered_registers[5] = numbered_registers[0];
    registers[5]->Clear();
    registers[5]->AppendText(
        remove_trailing_zeros(std::to_string(numbered_registers[0])));
    is_p_pressed = false;
    need_to_clear = true;
    return;
  }
  if (is_f_pressed) {
    display->Clear();
    display->AppendText(
        remove_trailing_zeros(std::to_string(take_from_display(registers[5]))));
    is_f_pressed = false;
  } else {
    if (need_to_clear) {
      display->Clear();
      registers[0]->Clear();
      need_to_clear = false;
      cnt = 0;
    }
    if (cnt < max_digits) {
      display->AppendText('5');
      registers[0]->AppendText('5');
      cnt++;
    }
  }
}
void Memory::press_six() {
  if (is_p_pressed) {
    numbered_registers[0] = take_from_display(registers[0]);
    stack[0] = numbered_registers[0];
    display->Clear();
    display->AppendText('0');
    numbered_registers[6] = numbered_registers[0];
    registers[6]->Clear();
    registers[6]->AppendText(
        remove_trailing_zeros(std::to_string(numbered_registers[0])));
    is_p_pressed = false;
    need_to_clear = true;
    return;
  }
  if (is_f_pressed) {
    display->Clear();
    display->AppendText(
        remove_trailing_zeros(std::to_string(take_from_display(registers[6]))));
    is_f_pressed = false;
  } else {
    if (need_to_clear) {
      display->Clear();
      registers[0]->Clear();
      need_to_clear = false;
      cnt = 0;
    }
    if (cnt < max_digits) {
      display->AppendText('6');
      registers[0]->AppendText('6');
      cnt++;
    }
  }
}
void Memory::press_seven() {
  if (is_p_pressed) {
    numbered_registers[0] = take_from_display(registers[0]);
    stack[0] = numbered_registers[0];
    display->Clear();
    display->AppendText('0');
    numbered_registers[7] = numbered_registers[0];
    registers[7]->Clear();
    registers[7]->AppendText(
        remove_trailing_zeros(std::to_string(numbered_registers[0])));
    is_p_pressed = false;
    need_to_clear = true;
    return;
  }
  if (is_f_pressed) {
    display->Clear();
    display->AppendText(
        remove_trailing_zeros(std::to_string(take_from_display(registers[7]))));
    is_f_pressed = false;
  } else {
    if (need_to_clear) {
      display->Clear();
      registers[0]->Clear();
      need_to_clear = false;
      cnt = 0;
    }
    if (cnt < max_digits) {
      cnt++;
      registers[0]->AppendText('7');
      display->AppendText('7');
    }
  }
}
void Memory::press_eight() {
  if (is_p_pressed) {
    display->Clear();
    display->AppendText("Error: invalid input");
    numbered_registers[0] = 0;
    registers[0]->Clear();
    registers[0]->AppendText('0');
    need_to_clear = true;
    is_p_pressed = false;
    return;
  }
  if (is_f_pressed) {
    display->Clear();
    display->AppendText("Error: invalid input");
    numbered_registers[0] = 0;
    registers[0]->Clear();
    registers[0]->AppendText('0');
  } else {
    if (need_to_clear) {
      display->Clear();
      registers[0]->Clear();
      need_to_clear = false;
      cnt = 0;
    }
    if (cnt < max_digits) {
      cnt++;
      display->AppendText('8');
      registers[0]->AppendText('8');
    }
  }
}
void Memory::press_nine() {
  if (is_p_pressed) {
    display->Clear();
    display->AppendText("Error: invalid input");
    numbered_registers[0] = 0;
    registers[0]->Clear();
    registers[0]->AppendText('0');
    need_to_clear = true;
    is_p_pressed = false;
    return;
  }
  if (is_f_pressed) {
    display->Clear();
    display->AppendText("Error: invalid input");
    numbered_registers[0] = 0;
    registers[0]->Clear();
    registers[0]->AppendText('0');
  } else {
    if (need_to_clear) {
      display->Clear();
      registers[0]->Clear();
      need_to_clear = false;
      cnt = 0;
    }
    if (cnt < max_digits) {
      cnt++;
      display->AppendText('9');
      registers[0]->AppendText('9');
    }
  }
}
void Memory::press_zero() {
  if (is_p_pressed) {
    display->Clear();
    display->AppendText("Error: invalid input");
    numbered_registers[0] = 0;
    registers[0]->Clear();
    registers[0]->AppendText('0');
    need_to_clear = true;
    is_p_pressed = false;
    return;
  }
  if (is_f_pressed) {
    display->Clear();
    display->AppendText(
        remove_trailing_zeros(std::to_string(take_from_display(registers[0]))));
    is_f_pressed = false;
  } else {
    if (need_to_clear) {
      display->Clear();
      registers[0]->Clear();
      need_to_clear = false;
      cnt = 0;
    }
    if (cnt < max_digits) {
      cnt++;
      display->AppendText('0');
      registers[0]->AppendText('0');
    }
    // registers[0]->Clear();
  }
}

void Memory::ln() {
  numbered_registers[0] = Memory::take_from_display(registers[0]);
  if (numbered_registers[0] <= 0) {
    display->Clear();
    display->AppendText("Error: incorrect input");
    numbered_registers[0] = 0;
    registers[0]->Clear();
    registers[0]->AppendText('0');
    point_pressed = false;
    need_to_clear = true;
    return;
  }
  numbered_registers[0] = std::log(numbered_registers[0]);
  stack[0] = numbered_registers[0];

  std::string str =
      remove_trailing_zeros(std::to_string(numbered_registers[0]));

  display->Clear();
  display->AppendText(str);

  registers[0]->Clear();
  registers[0]->AppendText(str);

  point_pressed = false;
  need_to_clear = true;
}

void Memory::pi() {
  numbered_registers[0] = M_PI;

  stack[0] = numbered_registers[0];

  std::string str =
      remove_trailing_zeros(std::to_string(numbered_registers[0]));

  display->Clear();
  display->AppendText(str);

  registers[0]->Clear();
  registers[0]->AppendText(str);

  point_pressed = false;
  need_to_clear = true;
}

void Memory::cos() {
  numbered_registers[0] = std::cos(take_from_display(registers[0]));

  stack[0] = numbered_registers[0];

  std::string str =
      remove_trailing_zeros(std::to_string(numbered_registers[0]));
  display->Clear();
  display->AppendText(str);

  registers[0]->Clear();
  registers[0]->AppendText(str);

  point_pressed = false;
  need_to_clear = true;
}

void Memory::sin() {
  numbered_registers[0] = std::sin(take_from_display(registers[0]));
  stack[0] = numbered_registers[0];

  std::string str =
      remove_trailing_zeros(std::to_string(numbered_registers[0]));
  display->Clear();
  display->AppendText(str);

  registers[0]->Clear();
  registers[0]->AppendText(str);

  point_pressed = false;
  need_to_clear = true;
}

void Memory::power() {
  numbered_registers[0] = Memory::take_from_display(registers[0]);
  float y = numbered_registers[0];
  float x = numbered_registers[1];
  numbered_registers[0] = std::pow(x, y);
  stack[0] = numbered_registers[0];

  std::string str =
      remove_trailing_zeros(std::to_string(numbered_registers[0]));
  display->Clear();
  display->AppendText(str);

  registers[0]->Clear();
  registers[0]->AppendText(str);

  point_pressed = false;
  need_to_clear = true;
}

void Memory::square() {
  numbered_registers[0] = Memory::take_from_display(registers[0]);
  numbered_registers[0] = std::pow(numbered_registers[0], 2);
  stack[0] = numbered_registers[0];
  std::string str =
      remove_trailing_zeros(std::to_string(numbered_registers[0]));

  display->Clear();
  display->AppendText(str);

  registers[0]->Clear();
  registers[0]->AppendText(str);

  point_pressed = false;
  need_to_clear = true;
}

void Memory::sqrt() {
  numbered_registers[0] = take_from_display(registers[0]);
  if (numbered_registers[0] < 0) {
    display->Clear();
    display->AppendText("Error: incorrect input");
    numbered_registers[0] = 0;
    registers[0]->Clear();
    registers[0]->AppendText('0');
    point_pressed = false;
    need_to_clear = true;
    return;
  }
  numbered_registers[0] = Memory::take_from_display(registers[0]);
  numbered_registers[0] = std::sqrt(numbered_registers[0]);

  stack[0] = numbered_registers[0];

  std::string str =
      remove_trailing_zeros(std::to_string(numbered_registers[0]));
  display->Clear();
  display->AppendText(str);

  registers[0]->Clear();
  registers[0]->AppendText(str);

  point_pressed = false;
  need_to_clear = true;
}

void Memory::reciprocal() {
  numbered_registers[0] = Memory::take_from_display(registers[0]);

  if (numbered_registers[0] == 0) {
    display->Clear();
    display->AppendText("Error: div by 0");
    numbered_registers[0] = 0;
    registers[0]->Clear();
    registers[0]->AppendText('0');
    point_pressed = false;
    need_to_clear = true;
    return;
  }

  numbered_registers[0] = 1.0 / numbered_registers[0];

  stack[0] = numbered_registers[0];

  std::string str =
      remove_trailing_zeros(std::to_string(numbered_registers[0]));
  display->Clear();
  display->AppendText(str);

  registers[0]->Clear();
  registers[0]->AppendText(str);

  point_pressed = false;
  need_to_clear = true;
}

// Метод для выполнения операции по индексу
// void Memory::execute_operation(int op_index) { operations[op_index](*this); }

// Получить значение из регистра по индексу
// void Memory::get_register(int index) {
//   nubered_registers[0] = nubered_registers[index];
// }

// Установить значение в регистр по индексу
// void Memory::set_register(int index, float value) {
//   nubered_registers[index] = value;
// }

void Memory::arrow_up() {
  if (is_p_pressed) {
    cos();
    return;
  }
  numbered_registers[1] = Memory::take_from_display(registers[0]);

  registers[1]->Clear();
  registers[1]->AppendText(
      remove_trailing_zeros(std::to_string(numbered_registers[1])));

  point_pressed = false;
  need_to_clear = true;
}

void Memory::right_shift() {
  float tmp = stack[6];
  for (int i = 5; i >= 0; i--) {
    stack[i + 1] = stack[i];
  }
  stack[0] = tmp;
}

void Memory::left_shift() {
  float tmp = stack[0];
  for (int i = 0; i <= 5; i++) {
    stack[i] = stack[i + 1];
  }
  stack[6] = tmp;
}

void Memory::swap() {
  if (is_p_pressed) {
    ln();
    is_p_pressed = false;
    return;
  }
  numbered_registers[0] = take_from_display(registers[0]);
  std::swap(numbered_registers[0], numbered_registers[1]);
  stack[0] = numbered_registers[0];

  std::string str_0 =
      remove_trailing_zeros(std::to_string(numbered_registers[0]));
  std::string str_1 =
      remove_trailing_zeros(std::to_string(numbered_registers[1]));

  display->Clear();
  display->AppendText(str_0);

  std::string tmp = registers[1]->GetValue().ToStdString();

  registers[1]->Clear();
  registers[1]->AppendText(registers[0]->GetValue().ToStdString());

  registers[0]->Clear();
  registers[0]->AppendText(tmp);
}

void Memory::sign() {
  if (is_p_pressed) {
    numbered_registers[0] = take_from_display(registers[0]);
    stack[0] = numbered_registers[0];
    float tmp = stack[6];
    for (int i = 5; i >= 0; i--) {
      stack[i + 1] = stack[i];
    }
    stack[0] = tmp;
    numbered_registers[0] = stack[0];
    for (int i = 0; i < 6; i++) {
      ring_buffer[i]->Clear();
      ring_buffer[i]->AppendText(
          remove_trailing_zeros(std::to_string(stack[i + 1])));
    }
    display->Clear();
    display->AppendText(
        remove_trailing_zeros(std::to_string(numbered_registers[0])));
    registers[0]->Clear();
    registers[0]->AppendText(
        remove_trailing_zeros(std::to_string(numbered_registers[0])));
    need_to_clear = true;
    is_p_pressed = false;
    return;
  }
  if (is_f_pressed) {
    square();
    is_f_pressed = false;
    return;
  }

  float value = take_from_display(registers[0]);
  value *= -1;
  std::string new_value = remove_trailing_zeros(std::to_string(value));

  display->Clear();
  display->AppendText(new_value);

  registers[0]->Clear();
  registers[0]->AppendText(new_value);
}

void Memory::vo() {}
void Memory::vp() {
  if (is_f_pressed) {
    sqrt();
    is_f_pressed = false;
    return;
  }
}
void Memory::sp() {}
void Memory::p() { is_p_pressed = true; }
void Memory::pp() {}
void Memory::cx() {
  display->Clear();
  display->AppendText("");
  registers[0]->Clear();
  registers[0]->AppendText("0");
  need_to_clear = true;
  point_pressed = false;
}
void Memory::f() { is_f_pressed = true; }
void Memory::bp() {}
void Memory::pnt() {
  if (is_p_pressed) {
    numbered_registers[0] = take_from_display(registers[0]);
    stack[0] = numbered_registers[0];
    float tmp = stack[0];
    for (int i = 0; i <= 5; i++) {
      stack[i] = stack[i + 1];
    }
    stack[6] = tmp;
    numbered_registers[0] = stack[0];
    for (int i = 0; i < 6; i++) {
      ring_buffer[i]->Clear();
      ring_buffer[i]->AppendText(
          remove_trailing_zeros(std::to_string(stack[i + 1])));
    }
    display->Clear();
    display->AppendText(
        remove_trailing_zeros(std::to_string(numbered_registers[0])));
    registers[0]->Clear();
    registers[0]->AppendText(
        remove_trailing_zeros(std::to_string(numbered_registers[0])));
    need_to_clear = true;
    is_p_pressed = false;
    return;
  }
  if (is_f_pressed) {
    reciprocal();
    is_f_pressed = false;
    return;
  }

  if (need_to_clear) {
    display->Clear();
    registers[0]->Clear();
    need_to_clear = false;
  }

  if (!point_pressed) {
    display->AppendText('.');
    registers[0]->AppendText('.');
    point_pressed = true;
  }
}

void Memory::act(int id) { operations[id](*this); }