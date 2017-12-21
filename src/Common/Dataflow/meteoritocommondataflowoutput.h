#ifndef METEORITOCOMMONDATAFLOWOUTPUT_H
#define METEORITOCOMMONDATAFLOWOUTPUT_H

#include <functional>
#include <atomic>
#include <stdexcept>

namespace Esferixis {
    namespace Common {
        namespace Dataflow {
            /**
             * @brief Salida de datagrama tipo D
             */
            template<typename D>
            class Output
            {
            public:
                /**
                 * @post Crea una salida
                 */
                Output();

                /**
                 * @post Destruye la salida
                 */
                ~Output();

                /**
                 * @pre No tiene que haber envío de datagrama pendiente
                 * @post Envía el datagrama especificado, con el lambda de notificación
                 *       de llegada especificado
                 */
                void sendDatagram(D outputDatagram, std::function<void ()> notifyDatagramArrival) {
                    if ( !this->hasPendingDatagramSending.exchange(true) ) {
                        this->sendDatagram_implementation(outputDatagram, [notifyDatagramArrival]() -> void {
                            this->hasPendingDatagramSending = false;
                            notifyDatagramArrival();
                        });
                    }
                    else {
                        throw std::runtime_error("It has been pending datagram sending");
                    }
                }
            protected:
                /**
                 * @pre No hay envío de datagrama pendiente
                 * @post Envía el datagrama especificado, con el lambda de notificación
                 *       de llegada especificado
                 */
                void sendDatagram_implementation(D outputDatagram, std::function<void ()> notifyDatagramArrival);

            private:
                std::atomic<bool> hasPendingDatagramSending;
            };
        }
    }
}

#endif // METEORITOCOMMONDATAFLOWOUTPUT_H
