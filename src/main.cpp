#include "gates.hpp"
#include "raylib.h"
#include <memory>
using namespace std;

// define stuff
#define shift(xs, xs_sz) (assert(xs_sz > 0), (void)0, --xs_sz, *xs++)
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 500
#define FPS 1
#define IPF 2 // iterations per frame

bool DEBUG = 1;

// main stuff
unordered_map<int32_t, unique_ptr<BaseComponent>> circuit;
set<int16_t> components_to_update;
vector<UpdatePort> ports_to_update;

void DrawComponent(BaseComponent &component) {
  // TODOO: draw full component - the rectangle based w/ width and height
  // draw the component as a rectangle, with width and height and colour
  // depending on gate type
  Position position = component.position;

  DrawRectangle(component.position[0], component.position[1], 100, 100,
                RAYWHITE);

  // TODO: draw the ports along with colour
  // draw ports for each component - ins and outs

  // TODOO: write the draw-wires code
  // just draw the wires
  return;
};

void printCircuit(
    const unordered_map<int32_t, unique_ptr<BaseComponent>> &circuit) {
  cout << "---------" << endl;
  for (const auto &[key, component] : circuit) {
    cout << "Component ID: " << key << endl;
    cout << "  Name: " << component->name << endl;
    cout << "  Position: (" << component->position[0] << ", "
         << component->position[1] << ")" << endl;
    cout << "  Inputs: ";
    for (const auto &input : component->inputs) {
      cout << static_cast<int>(input) << " ";
    }
    cout << endl;
    cout << "  Output Targets: ";
    for (const auto &target : component->output_targets) {
      cout << "(" << target[0] << ", " << target[1] << ") ";
    }
    cout << endl;
  }
}

// main
int main(int argc, char **argv) {
  const char *program_name = shift(argv, argc);
  if (argc > 0) {
    // TODO: add handling of external files
    // accept input of name of external file, import them as the input circuit
    const char *command_name = shift(argv, argc);
    cout << "---------" << endl;
    printf("AAAAAAAA what on earth does '%s' mean???\n", command_name);
    return -1;
  } else {
    circuit.insert({0, make_unique<InputGate>("input", Position{0, 0},
                                              vector<Packet>{-1, -1},
                                              vector<Port>{{1, 0}, {2, 0}})});
    circuit.insert({1, make_unique<SplitGate>("split1", Position{100, 0},
                                              vector<Packet>{0},
                                              vector<Port>{{3, 0}, {4, 0}})});
    circuit.insert({2, make_unique<SplitGate>("split2", Position{0, 100},
                                              vector<Packet>{0},
                                              vector<Port>{{3, 1}, {4, 1}})});
    circuit.insert(
        {3, make_unique<MaxGate>("max1", Position{200, 0}, vector<Packet>{0, 0},
                                 vector<Port>{{5, 0}})});
    circuit.insert(
        {4, make_unique<MinGate>("min1", Position{0, 200}, vector<Packet>{0, 0},
                                 vector<Port>{{6, 1}})});
    circuit.insert(
        {5, make_unique<NegGate>("neg", Position{200, 200}, vector<Packet>{0},
                                 vector<Port>{{6, 0}})});
    circuit.insert(
        {6, make_unique<MaxGate>("max2", Position{300, 300}, vector<Packet>{0, 0},
                                 vector<Port>{{-1, 0}})});
    circuit.insert(
        {-1, make_unique<OutputGate>("output", Position{700, 400},
                                     vector<Packet>{0}, vector<Port>{})});
    components_to_update.insert(0);
  }

  // Initialization

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Some raylib program");

  SetTargetFPS(FPS); // Set our game to run at 60 frames-per-second

  // Main game loop
  while (!WindowShouldClose()) { // Detect window close button or ESC key
    // Update
    // TODO: check keypresses: add,remove components interactively, save circuit
    // to file

    // Updating components & ports
    for (int i = 0; i < IPF; i++) {
      if (DEBUG) {
        printCircuit(circuit);
      };
      for (auto i : components_to_update) {
        if (DEBUG) {
          cout << "---------" << endl;
          printf("updating component: %d\n", i);
        }
        circuit[i]->update_outputs();
      }
      components_to_update.clear();

      for (auto i : ports_to_update) {
        if (DEBUG) {
          printf("updating port: %d,%d\n", i.port[0], i.port[1]);
        }
        components_to_update.insert(i.port[0]);
        circuit[i.port[0]]->inputs[i.port[1]] = i.value;
      }
      ports_to_update.clear();
    }

    // Draw
    BeginDrawing();
    ClearBackground(DARKBLUE);
    if (DEBUG) {
      cout << "---------" << endl;
    }
    for (auto &i : circuit) {
      if (DEBUG) {
        cout << "Drawing component: " << i.second->name << endl;
      }
      DrawComponent(*i.second);
    }
    EndDrawing();
  }

  // De-Initialization
  CloseWindow(); // Close window and OpenGL context

  return 0;
}
