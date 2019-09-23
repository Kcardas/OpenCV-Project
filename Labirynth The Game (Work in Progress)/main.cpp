#include "Labirynth.h"

using std::cout;
using std::cin;

int main( int argc, char** argv ){
  bool escolha = true;

  while(escolha){
    cout << "LABIRYNTH THE GAME\n 1-Começar\n 0-Sair\n";
    cin >> escolha;

    cout << ">>>>>>> Digite ESC para forçar uma saida do jogo.\n";

    if(escolha) Labirynth(argc, argv);
  }

  return 0;
}
