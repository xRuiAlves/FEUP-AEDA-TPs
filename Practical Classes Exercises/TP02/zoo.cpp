#include "zoo.h"

/////////////////////////////////
///////  VETERINARIO  ///////////
/////////////////////////////////

Veterinario::Veterinario(string nome, int cod): nome(nome), codOrdem(cod){}

string Veterinario::getNome() const {
	return nome;
}

long Veterinario::getCod() const{
	return codOrdem;
}


/////////////////////////////////
////////  ANIMAL  ///////////////
/////////////////////////////////

int Animal::maisJovem = -1;	// inicialmente não há mais jovem

Animal::Animal(string nome, int idade): nome(nome), idade(idade){
	vet = NULL; // no vet yet
	if(maisJovem==-1) // ainda não há mais jovem
		maisJovem = idade;
	else if(idade<maisJovem)
		maisJovem = idade;
}

int Animal::getMaisJovem(){
	return maisJovem;
}

string Animal::getNome() const {
	return nome;
}

int Animal::getIdade() const{
	return idade;
}

void Animal::setVet (Veterinario* vet){
	this->vet = vet;
}


Veterinario* Animal::getVet() const{
	return vet;
}


/////////////////////////////////
//////////  CAO  ////////////////
/////////////////////////////////

Cao::Cao(string nome, int idade, string raca): Animal(nome,idade), raca(raca){}

bool Cao::eJovem() const{
	return idade<5;
}

string Cao::getInformacao() const{
	if (vet==NULL){
		return (nome + ", " + to_string(idade) + ", " + raca);
	}
	else{
		return (nome + ", " + to_string(idade) + ", " + vet->getNome() + ", " + to_string(vet->getCod()) + ", " + raca);

	}
}

/////////////////////////////////
//////////  VOADOR  /////////////
/////////////////////////////////

Voador::Voador(int vmax, int amax): velocidade_max(vmax), altura_max(amax){}

int Voador::getVmax() const{
	return velocidade_max;
}

int Voador::getAmax() const{
	return altura_max;
}


/////////////////////////////////
/////////  MORCEGO  /////////////
/////////////////////////////////

Morcego::Morcego(string nome, int idade, int vmax, int amax): Animal(nome,idade), Voador(vmax,amax){}

bool Morcego::eJovem() const{
	return idade<4;
}

string Morcego::getInformacao() const{
	if(vet==NULL){
		return (nome + ", " + to_string(idade) + ", " + to_string(getVmax()) + ", " + to_string(getAmax()));
	}
	else{
		return (nome + ", " + to_string(idade) + ", " + vet->getNome() + ", " + to_string(vet->getCod()) + ", " + to_string(getVmax()) + ", " + to_string(getAmax()));
	}
}


/////////////////////////////////
///////////  ZOO  ///////////////
/////////////////////////////////


void Zoo::adicionaAnimal(Animal *a1){
	animais.push_back(a1);
}

string Zoo::getInformacao() const{
	string informacao;
	for(unsigned int i=0 ; i<animais.size() ; i++){
		informacao+=animais.at(i)->getInformacao();
		informacao+='\n';
	}
	return informacao;
}

bool Zoo::animalJovem(string nomeA){
	for(unsigned int i=0; i<animais.size() ;i++){
		if(nomeA == animais.at(i)->getNome()){
			return animais.at(i)->eJovem();
		}
	}

	return false;	// animal wasn't found
}

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::alocaVeterinarios(istream &isV){
	// get the vets into the vector
	string name, cod;
	while(getline(isV, name)){
		getline(isV, cod);
		name.erase(name.size()-1,1);	// remove \r character that appears for some reason
		Veterinario *vet = new Veterinario(name, stoi(cod));
		veterinarios.push_back(vet);
	}

	// atribuir vets aos animais
	for(unsigned int i=0 ; i<animais.size() ; i++)
		animais.at(i)->setVet(veterinarios.at(i%veterinarios.size()));
}

bool Zoo::removeVeterinario (string nomeV){
	//find vet
	int indiceVet=-1;
	for(unsigned int i=0 ; i<veterinarios.size() ; i++){
		if(veterinarios.at(i)->getNome() == nomeV){
			indiceVet = i;
		}
	}

	if(indiceVet==-1){		// vet wasn't found
		return false;
	}

	// trocar vet aos animais que tinham este vet
	for(unsigned int i=0 ; i<animais.size() ; i++){
		if(animais.at(i)->getVet()->getNome() == nomeV){
			animais.at(i)->setVet(veterinarios.at((indiceVet+1) % veterinarios.size()));
		}
	}

	// remover vet do vetor
	veterinarios.erase(veterinarios.begin()+indiceVet);

	return true;
}

bool Zoo::operator < (Zoo& zoo2) const{
	int idade1 = 0, idade2 = 0;

	for(unsigned int i=0 ; i<animais.size() ; i++)
		idade1 += animais.at(i)->getIdade();

	for(unsigned int i=0 ; i<zoo2.animais.size() ; i++)
		idade2 += zoo2.animais.at(i)->getIdade();

	return (idade1 < idade2);
}
