#ifndef METEORITOCOMMONDATAFLOWOUTPUT_H
#define METEORITOCOMMONDATAFLOWOUTPUT_H

#include <boost/noncopyable.hpp>
#include <functional>
#include <atomic>
#include <stdexcept>

namespace Esferixis {
    namespace Common {
        namespace Dataflow {
            /**
             * @brief Salida de paquete tipo D
             */
            template<typename P>
            class Output : private boost::noncopyable
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
                 * @pre No tiene que haber envío de paquete pendiente
                 * @post Envía el paquete especificado, con el lambda de notificación
                 *       de llegada especificado
                 */
                void sendPacket(P outputPacket, std::function<void ()> notifyPacketArrival) {
                    if ( !this->hasPendingPacketSending.exchange(true) ) {
                        this->sendPacket_implementation(outputPacket, [notifyPacketArrival]() -> void {
                            this->hasPendingPacketSending = false;
                            notifyDatagramArrival();
                        });
                    }
                    else {
                        this->hasPendingPacketSending = false;
                        throw std::runtime_error("It has been pending datagram sending");
                    }
                }
            protected:
                /**
                 * @pre No hay envío de datagrama pendiente
                 * @post Envía el paquete especificado, con el lambda de notificación
                 *       de llegada especificado
                 */
                void sendPacket_implementation(P outputPacket, std::function<void ()> notifyPacketArrival);

            private:
                std::atomic<bool> hasPendingPacketSending;
            };
        }
    }
}

#endif // METEORITOCOMMONDATAFLOWOUTPUT_H
