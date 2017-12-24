#ifndef METEORITOCOMMONDATAFLOWCONCRETECONNECTION_H
#define METEORITOCOMMONDATAFLOWCONCRETECONNECTION_H

#include "esferixiscommondataflowinput.h"
#include "esferixiscommondataflowoutput.h"
#include "esferixiscommondataflowconnection.h"

namespace Esferixis {
    namespace Common {
        namespace Dataflow {
            template<typename P>
            class ConcreteConnection : Esferixis::Common::Dataflow::Connection
            {
            public:
                /**
                 * @post Crea una conexión con la entrada y salida
                 *       especificados
                 */
                ConcreteConnection(Esferixis::Common::Dataflow::Input<P>& input, Esferixis::Common::Dataflow::Output<P>& output);

                /**
                 * @post Destruye la conexión
                 */
                ~ConcreteConnection();

            protected:
                void receivePacket_implementation(std::function<void ()> notifyPacketArrival) {
                    this->input.receivePacket([this](Ṕ packet) -> void {
                        this->pendingPacketToSend = packet;
                        notifyPacketArrival();
                    });
                }

                void sendReceivedPacket_implementation(std::function<void ()> packetHasBeenCopied, std::function<void ()> notifyPacketArrival) {
                    P pendingPacketToSend_local = this->pendingPacketToSend;
                    packetHasBeenCopied();

                    this->output.sendPacket(pendingPacketToSend_local, [this]() -> void {
                        notifyPacketArrival();
                    });
                }

            private:
                Esferixis::Common::Dataflow::Input<P>& input;
                Esferixis::Common::Dataflow::Output<P>& output;

                P pendingPacketToSend;
            };
        }
    }
}

#endif // METEORITOCOMMONDATAFLOWCONNECTION_H
