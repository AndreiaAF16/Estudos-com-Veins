#include "MyVeinsApp.h"                // Inclui o cabeçalho do arquivo MyVeinsApp.h, que contém a declaração da classe MyVeinsApp.

Define_Module(MyVeinsApp);              // Define a classe MyVeinsApp como um módulo do OMNeT++.

void MyVeinsApp::initialize(int stage) {                // Implementação da função initialize da classe MyVeinsApp.
    BaseWaveApplLayer::initialize(stage);               // Chama a função initialize da classe base BaseWaveApplLayer.
    if (stage == 0) {                                   // Verifica se o estágio da inicialização é 0.
        //Initializing members and pointers of your application goes here
        EV << "Initializing " << par("appName").stringValue() << std::endl;  // Imprime uma mensagem de inicialização.
        std::cout << "Initializing" << par("appName").stringValue() << std::endl; // Envia uma mensagem para a saída padrão
    }
    else if (stage == 1) {                              // Verifica se o estágio da inicialização é 1.
        //Initializing members that require initialized other modules goes here
        // Inicializa membros que requerem outros módulos inicializados.
    }
}

void MyVeinsApp::finish() {                            // Implementação da função finish da classe MyVeinsApp.
    BaseWaveApplLayer::finish();                        // Chama a função finish da classe base BaseWaveApplLayer.
    //statistics recording goes here
    // O registro de estatísticas pode ser feito aqui.
}

void MyVeinsApp::onBSM(BasicSafetyMessage* bsm) {      // Implementação da função onBSM da classe MyVeinsApp.
    //Your application has received a beacon message from another car or RSU
    //code for handling the message goes here
    // Seu aplicativo recebeu uma mensagem de beacon de outro carro ou RSU.
    // O código para lidar com a mensagem vai aqui.
}

void MyVeinsApp::onWSM(WaveShortMessage* wsm) {        // Implementação da função onWSM da classe MyVeinsApp.
    //Your application has received a data message from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples
    // Seu aplicativo recebeu uma mensagem de dados de outro carro ou RSU.
    // O código para lidar com a mensagem vai aqui. Veja TraciDemo11p.cc para exemplos.
}

void MyVeinsApp::onWSA(WaveServiceAdvertisment* wsa) { // Implementação da função onWSA da classe MyVeinsApp.
    //Your application has received a service advertisement from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples
    // Seu aplicativo recebeu um anúncio de serviço de outro carro ou RSU.
    // O código para lidar com a mensagem vai aqui. Veja TraciDemo11p.cc para exemplos.
}

void MyVeinsApp::handleSelfMsg(cMessage* msg) {         // Implementação da função handleSelfMsg da classe MyVeinsApp.
    BaseWaveApplLayer::handleSelfMsg(msg);              // Chama a função handleSelfMsg da classe base BaseWaveApplLayer.
    //this method is for self messages (mostly timers)
    //it is important to call the BaseWaveApplLayer function for BSM and WSM transmission
    // Este método é para mensagens próprias (principalmente timers).
    // É 
