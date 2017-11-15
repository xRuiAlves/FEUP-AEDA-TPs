#ifndef BALCAO_H_
#define BALCAO_H_

#include <iostream>
#include <queue>

using namespace std;


class Cliente {
      int numPresentes;
public:
      Cliente();
      int getNumPresentes() const;
};


class Balcao {
      queue<Cliente> clientes;
      const int tempo_embrulho;
      int prox_chegada, prox_saida;
      int tempo_atual;
      int clientes_atendidos;
public:
      Balcao(int te=2);
      int getTempoAtual() const;
      int getProxChegada() const;
      int getClientesAtendidos() const;
      int getTempoEmbrulho() const;
      int getProxSaida() const;
      unsigned int getTamanhoFila() const;
      Cliente & getProxCliente();

      void chegada();
      void saida();
      void proximoEvento();

      friend ostream & operator << (ostream & out, const Balcao & b1);
};

#endif
