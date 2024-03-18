#ifndef __VEINS_MYVEINSAPP_H_                         // Diretiva de pré-processador para evitar múltiplas inclusões do arquivo de cabeçalho.
#define __VEINS_MYVEINSAPP_H_                         // Define um identificador único para o arquivo de cabeçalho.

#include <omnetpp.h>                                   // Inclui o cabeçalho principal do OMNeT++.
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"  // Inclui o cabeçalho da classe BaseWaveApplLayer.

using namespace omnetpp;                               // Usa o namespace do OMNeT++.

/**
 * @brief
 * This is a stub for a typical Veins application layer.
 * Most common functions are overloaded.
 * See MyVeinsApp.cc for hints
 *
 * @author David Eckhoff
 *
 */
class MyVeinsApp : public BaseWaveApplLayer {          // Declaração da classe MyVeinsApp que herda da classe BaseWaveApplLayer.
    public:
        virtual void initialize(int stage);            // Declaração da função virtual initialize para inicialização.
        virtual void finish();                         // Declaração da função virtual finish para finalização.
    protected:
        virtual void onBSM(BasicSafetyMessage* bsm);  // Declaração da função virtual onBSM para lidar com mensagens BSM.
        virtual void onWSM(WaveShortMessage* wsm);    // Declaração da função virtual onWSM para lidar com mensagens WSM.
        virtual void onWSA(WaveServiceAdvertisment* wsa);  // Declaração da função virtual onWSA para lidar com anúncios de serviço.
        virtual void handleSelfMsg(cMessage* msg);    // Declaração da função virtual handleSelfMsg para lidar com mensagens próprias.
        virtual void handlePositionUpdate(cObject* obj);  // Declaração da função virtual handlePositionUpdate para lidar com atualizações de posição.
    };

#endif                                                // Fim da diretiva de pré-processador para evitar múltiplas inclusões do arquivo de cabeçalho.
