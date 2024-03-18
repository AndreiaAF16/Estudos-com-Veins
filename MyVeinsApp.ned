package org.car2x.veins.modules.application.traci;  // Declaração do pacote em que a classe está localizada.

import org.car2x.veins.modules.application.ieee80211p.BaseWaveApplLayer;  // Importa a classe BaseWaveApplLayer do pacote org.car2x.veins.modules.application.ieee80211p.

//
// network description file for your Veins Application. Add parameters here
//
// Comentário explicativo sobre o arquivo de descrição da rede para a sua aplicação Veins. Adicione parâmetros aqui.

simple MyVeinsApp extends BaseWaveApplLayer  // Declaração da classe MyVeinsApp que estende a classe BaseWaveApplLayer.
{
    @class(MyVeinsApp);  // Anotação que indica que essa classe corresponde à classe MyVeinsApp no script SUMO.

    string appName = default("My first Veins App!");  // Declaração de uma variável de string chamada appName com um valor padrão "My first Veins App!".
}

