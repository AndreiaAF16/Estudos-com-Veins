#include "veins/modules/application/traci/TraCIDemo11p.h"
// Inclui o cabeçalho da classe TraCIDemo11p.

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"
// Inclui o cabeçalho da mensagem específica para a aplicação TraCIDemo11p.

using namespace veins;
// Usa o namespace veins.

Define_Module(veins::TraCIDemo11p);
// Define a classe TraCIDemo11p como um módulo do OMNeT++.

void TraCIDemo11p::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    // Inicializa a classe base DemoBaseApplLayer.

    if (stage == 0) {
        // Se o estágio da inicialização for 0:

        sentMessage = false;
        // Define a variável sentMessage como falso.

        lastDroveAt = simTime();
        // Define a variável lastDroveAt com o tempo atual de simulação.

        currentSubscribedServiceId = -1;
        // Define a variável currentSubscribedServiceId como -1.
    }
}

void TraCIDemo11p::onWSA(DemoServiceAdvertisment* wsa)
{
    if (currentSubscribedServiceId == -1) {
        // Se não estiver inscrito em nenhum serviço:

        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
        // Altera o canal de serviço com base nas informações recebidas no anúncio de serviço.

        currentSubscribedServiceId = wsa->getPsid();
        // Define o ID do serviço atual como o ID do serviço recebido no anúncio.

        if (currentOfferedServiceId != wsa->getPsid()) {
            // Se o ID do serviço oferecido for diferente do ID do serviço recebido:

            stopService();
            // Para o serviço atual.

            startService(static_cast<Channel>(wsa->getTargetChannel()), wsa->getPsid(), "Mirrored Traffic Service");
            // Inicia um novo serviço com base nas informações recebidas no anúncio de serviço.
        }
    }
}

void TraCIDemo11p::onWSM(BaseFrame1609_4* frame)
{
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);
    // Converte o quadro recebido em uma mensagem específica para a aplicação TraCIDemo11p.

    findHost()->getDisplayString
