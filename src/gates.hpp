#include "raylib.h"
#include <bits/stdc++.h>
using namespace std;

typedef array<int16_t, 2> Port;
typedef int8_t Packet;
struct UpdatePort {
  Port port;
  int8_t value;
};

// Declare global variables
extern set<int16_t> components_to_update;
extern vector<UpdatePort> ports_to_update;

class BaseComponent {
public:
  BaseComponent(string name = "base component", Vector2 position = {0, 0},
                vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : name(name), position(position), inputs(inputs),
        output_targets(output_targets) {}

  string name;
  Vector2 position;

  vector<Packet> inputs;
  vector<Port> output_targets;

  virtual void update_outputs() {
    for (size_t i = 0; i < inputs.size(); i++) {
      printf("input %zu is %d\n", i, inputs[i]);
    }
  }

  virtual void draw_component() {
    // TODOOO: draw full component - the rectangle based w/ width and height
    // draw the component as a rectangle, with width and height and colour
    // depending on gate type

    DrawRectangle(position.x, position.y, 100, 100, RAYWHITE);

    // TODO: draw the ports along with colour
    // draw ports for each component - ins and outs

    // TODOO: write the draw-wires code
    // just draw the wires
    return;
  };

  virtual void print_component() {
    printf("%s\n", name.c_str());
    printf("  Position: [ %.1f, %.1f ]\n", position.x, position.y);
    printf("  Inputs:   ");
    for (const auto &input : inputs) {
      printf("%d, ", input);
    };
    printf("\n  Targets:  ");
    for (const auto &target : output_targets) {
      printf("(%d,%d), ", target[0], target[1]);
    }
    printf("\n\n");
  };
};

class InputGate : public BaseComponent {
public:
  InputGate(string name = "input", Vector2 position = {0, 0},
            vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    for (size_t i = 0; i < inputs.size(); i++) {
      ports_to_update.push_back({output_targets[i], inputs[i]});
    }
  }
};

class OutputGate : public BaseComponent {
public:
  OutputGate(string name = "input", Vector2 position = {0, 0},
             vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    for (size_t i = 0; i < inputs.size(); i++) {
      printf("OUTPUT %zu: %d\n", i, inputs[i]);
    }
  }
};

class SplitGate : public BaseComponent {
public:
  SplitGate(string name = "split", Vector2 position = {0, 0},
            vector<Packet> inputs = {0}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    for (size_t i = 0; i < output_targets.size(); i++) {
      ports_to_update.push_back({output_targets[i], inputs[0]});
    }
  }
};

class NegGate : public BaseComponent {
public:
  NegGate(string name = "input", Vector2 position = {0, 0},
          vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    for (size_t i = 0; i < inputs.size(); i++) {
      ports_to_update.push_back(
          {output_targets[i], static_cast<int8_t>(-inputs[i])});
    }
  }
};

class AddGate : public BaseComponent {
public:
  AddGate(string name = "input", Vector2 position = {0, 0},
          vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    ports_to_update.push_back(
        {output_targets[0],
         static_cast<int8_t>(accumulate(inputs.begin(), inputs.end(), 0))});
  }
};

class MaxGate : public BaseComponent {
public:
  MaxGate(string name = "input", Vector2 position = {0, 0},
          vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    ports_to_update.push_back(
        {output_targets[0],
         static_cast<int8_t>(*max_element(inputs.begin(), inputs.end()))});
  }
};

class MinGate : public BaseComponent {
public:
  MinGate(string name = "input", Vector2 position = {0, 0},
          vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    ports_to_update.push_back(
        {output_targets[0],
         static_cast<int8_t>(*min_element(inputs.begin(), inputs.end()))});
  }
};

