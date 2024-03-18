// As 6 classes de C++ que estão contidas no código são:
// TraCIDemo11p = Representa a aplicação de demonstração TraCI 11p;
// DemoBaseApplLayer = É a classe base para a aplicação de camada de aplicação (Application Layer) do Veins framework;
// DemoServiceAdvertisment = Representa anúncios de serviços dentro da aplicação de demonstração esses anúncios de serviço são usados para informar outros veículos na rede sobre os serviços disponíveis em um determinado canal, permitindo assim a comunicação e cooperação entre os veículos;
// BaseFrame1609_4 =  Contém membros e métodos relacionados à construção, manipulação e interpretação dos quadros de comunicação V2V
// TraCIDemo11pMessage = Ela é fundamental para o envio e recebimento de mensagens na aplicação de demonstração TraCI 11p no framework Veins
// cMessage = A classe cMessage fornece uma estrutura básica para representar mensagens que podem ser trocadas entre diferentes componentes da simulação, como nós de rede.

#include "veins/modules/application/traci/TraCIDemo11p.h" // Procura dentro da pasta e inclui o TraCIDemo11p.

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h" // Procura dentro da pasta e inclui o TraCIDemo11pMessage_m.h.

using namespace veins; // Usa o namespace do veins.

Define_Module(veins::TraCIDemo11p); // Define a classe TraCIDemo11p como um módulo do OMNeT++.

void TraCIDemo11p::initialize(int stage) // Configura o estado inicial do código
{
    DemoBaseApplLayer::initialize(stage); // Inicializa a classe base DemoBaseApplLayer.

    if (stage == 0) { // Função de condição se o estágio da inicialização for 0:

        sentMessage = false; // Define a variável sentMessage como falso.

        lastDroveAt = simTime(); // Define a variável lastDroveAt com o tempo atual de simulação.

        currentSubscribedServiceId = -1; // Define a variável currentSubscribedServiceId como -1.
    }
}

void TraCIDemo11p::onWSA(DemoServiceAdvertisment* wsa) // Chama a função onWSA
{
    if (currentSubscribedServiceId == -1) { // Função de condição se não estiver inscrito em nenhum serviço:

        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel())); // Altera o canal de serviço com base nas informações recebidas no anúncio de serviço.

        currentSubscribedServiceId = wsa->getPsid(); // Define o ID do serviço atual como o ID do serviço recebido no anúncio.

        if (currentOfferedServiceId != wsa->getPsid()) { // Função de condição se o ID do serviço oferecido for diferente do ID do serviço recebido.

            stopService(); // Para o serviço atual.

            startService(static_cast<Channel>(wsa->getTargetChannel()), wsa->getPsid(), "Mirrored Traffic Service"); // Inicia um novo serviço com base nas informações recebidas no anúncio de serviço.
        }
    }
}

void TraCIDemo11p::onWSM(BaseFrame1609_4* frame) // Esta função é responsável por lidar com eventos relacionados a mensagens recebidas na aplicação TraCIDemo11p, que são do tipo BaseFrame1609_4
{
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame); // Converte o quadro recebido em uma mensagem específica para a aplicação TraCIDemo11p.

    findHost()->getDisplayString // Atualiza a representação visual

    if (mobility->getRoadId()[0] != ':') traciVehicle->changeRoute(wsm->getDemoData(), 9999); // Se o veículo não estiver em uma interseção, altera a rota do veículo para seguir as informações recebidas.

    if (!sentMessage) { // Função de condição se ainda não foi enviada nenhuma mensagem.

        sentMessage = true; // Define sentMessage como true.

        // Repete a atualização de tráfego recebida uma vez a cada 2 segundos.
        wsm->setSenderAddress(myId);
        wsm->setSerial(3);
        scheduleAt(simTime() + 2 + uniform(0.01, 0.2), wsm->dup());
        // Agenda o envio da mensagem com um atraso aleatório entre 0.01 e 0.2 segundos.
    }
}

void TraCIDemo11p::handleSelfMsg(cMessage* msg) // Lida com mensagens que são destinadas ao próprio módulo, ou seja, mensagens que são enviadas pelo próprio módulo para si mesmo
{
    if (TraCIDemo11pMessage* wsm = dynamic_cast<TraCIDemo11pMessage*>(msg)) { // Se a mensagem recebida for do tipo TraCIDemo11pMessage:
        // Envia esta mensagem no canal de serviço até que o contador seja 3 ou mais.
        // Este código só é executado quando o chaveamento de canal está habilitado.
        sendDown(wsm->dup());
        wsm->setSerial(wsm->getSerial() + 1);
        if (wsm->getSerial() >= 3) {
            // Interrompe os anúncios de serviço.
            stopService();
            delete (wsm);
        }
        else {
            scheduleAt(simTime() + 1, wsm);
        }
    }
    else {
        // Se a mensagem recebida não for do tipo TraCIDemo11pMessage, repassa para a função handleSelfMsg da classe DemoBaseApplLayer.
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}

void TraCIDemo11p::handlePositionUpdate(cObject* obj)     // Chama a função handlePositionUpdate da classe DemoBaseApplLayer para lidar com a atualização de posição.
{
    DemoBaseApplLayer::handlePositionUpdate(obj); //Chama a função handlePositionUpdate da classe base DemoBaseApplLayer

    // Veículo está parado por pelo menos 10s
    if (mobility->getSpeed() < 1) {
        if (simTime() - lastDroveAt >= 10 && sentMessage == false) {
            // Se o veículo está parado por 10 segundos e ainda não enviou nenhuma mensagem:

            findHost()->getDisplayString().setTagArg("i", 1, "red"); // Define a cor do veículo como vermelho na interface gráfica.
            sentMessage = true;
           
            TraCIDemo11pMessage* wsm = new TraCIDemo11pMessage();  // Cria uma nova mensagem TraCIDemo11pMessage.
            // Preenche a mensagem com os dados necessários.
            populateWSM(wsm);
            wsm->setDemoData(mobility->getRoadId().c_str());

            // Função de condição se o chaveamento de canal está habilitado:
            if (dataOnSch) {
                // Inicia o serviço no canal sch2 e faz a publicidade do servidor.
                startService(Channel::sch2, 42, "Traffic Information Service");
                // Inicia o serviço e a publicidade do servidor, agendando a mensagem para ser enviada mais tarde.
                scheduleAt(computeAsynchronousSendingTime(1, ChannelType::service), wsm);
            }
            else {
                // Envia imediatamente no CCH, pois o chaveamento de canal está desabilitado.
                sendDown(wsm);
            }
        }
    }
    else {
        lastDroveAt = simTime(); atribui o tempo de simulação atual (simTime()) à variável lastDroveAt
    }
}

