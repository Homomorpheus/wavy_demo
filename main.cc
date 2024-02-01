#include <vector>

#include "Neo-CLA/src/vector.h"
#include "Neo-CLA/src/matrix.h"
namespace cla = Neo_CLA;

#include "raylib/src/raylib.h"

#include <emscripten/emscripten.h>


void UpdateDrawFrame();

const size_t size = 1000;
const size_t amount_funcs = 3;
// lagrange polynomials
cla::Matrix<> L (10, size);
// random interpolation values
cla::Matrix<> randval(amount_funcs, 10);
std::vector<unsigned char> colors ({255, 243, 207,
                                201, 215, 221,
                                99, 122, 159});

int main() {

  InitWindow(size, size, "wavy");

  // compute langrange polynomials
  for (size_t j=0; j < 10; j++){
    for (size_t x=0; x < size; x++){
      L(j, x) = 1.;
      for (size_t k=0; k < 10; k++){
        if (j != k){
          L(j, x) *= (x-(k*100.));
          L(j, x) *= 1/((j*100.)-(k*100.));
        }
      }
    }
  }

  // random interpolation values
  srand (time(NULL));
  for (size_t i=0; i < randval.height(); i++){
    for (size_t j=0; j < randval.width(); j++){
      randval(i, j) = rand() % size;
    }
  }

  emscripten_set_main_loop(UpdateDrawFrame, 0, true);

  CloseWindow();

  return 0;
}

void UpdateDrawFrame(){
  BeginDrawing();
    ClearBackground((Color){232, 200, 114});

    // change interpolation values
    for (size_t i=0; i < randval.height(); i++){
      for (size_t j=0; j < randval.width(); j++){
        randval(i, j)  += rand() % 10 - randval(i, j)/size*10;
      }
    }

    for (size_t x=0; x < size - 1; x++){
      DrawLine(x, (randval*L)(0, x), (x+1), (randval*L)(0, x+1), (Color){255, 243, 207, 255});
      DrawLine(x, (randval*L)(1, x), (x+1), (randval*L)(1, x+1), (Color){201, 215, 221, 255});
      DrawLine(x, (randval*L)(2, x), (x+1), (randval*L)(2, x+1), (Color){99, 122, 159, 255});
    }

  EndDrawing();
}
