#include "gates.hpp"
#include "functions.hpp"
using namespace std;

// define stuff (code from tsoding)
#define shift(xs, xs_sz) (assert(xs_sz > 0), (void)0, --xs_sz, *xs++)
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define FPS 1
#define IPF 2 // iterations per frame

bool DEBUG = 1;

// main stuff
unordered_map<int32_t, unique_ptr<BaseComponent>> circuit;
set<int16_t> components_to_update;
vector<UpdatePort> ports_to_update;

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
    setup_default_MUL_circuit();
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
        printf("---------\n");
        for (const auto &[key, component] : circuit) {
          printf("%d: ", key);
          component->print_component();
        }
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
      printf("---------\nDrawing components!\n");
    };
    for (auto &i : circuit) {
      i.second->draw_component();
    }
    EndDrawing();
  }

  // De-Initialization
  CloseWindow(); // Close window and OpenGL context

  return 0;
}
