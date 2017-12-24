#ifndef METEORITOCOMMONDATAFLOWINPUT_H
#define METEORITOCOMMONDATAFLOWINPUT_H

#include <boost/noncopyable.hpp>
#include <functional>
#include <atomic>
#include <stdexcept>

namespace Esferixis {
    namespace Common {
        namespace Dataflow {
            /**
             * @brief Entrada con paquete tipo P
             */
            template<typename P>
            class Input : private boost::noncopyable
            {
            public:
                /**
                 * @post Crea una entrada
                 */
                Input();

                /**
                 * @post Destruye la entrada
                 */
                ~Input();

                /**
                 * @pre No tiene que haber recepción de paquete pendiente
                 * @post Recibe un paquete en el lambda de notificación de llegada de paquete especificado
                 */
                void receivePacket(std::function<void (P inputPacket)> notifyPacketArrival) {
                    if ( !this->hasPendingPacketReception.exchange(true) ) {
                        this->receivePacket_implementation([notifyPacketArrival](P inputPacket) -> void {
                            this->hasPendingPacketReception = false;
                            notifyPacketArrival(inputPacket);
                        });
                    }
                    else {
                        this->hasPendingPacketReception = false;
                        throw std::runtime_error("It has been pending packet reception");
                    }
                }

            protected:
                /**
                 * @pre No hay recepción de datagrama pendiente
                 * @post Recibe un paquete en el lambda de notificación de llegada de paquete especificado
                 */
                virtual void receivePacket_implementation(std::function<void (P inputPacket)> notifyPacketArrival) =0;

            private:
                std::atomic<bool> hasPendingPacketReception;
            };
        }
    }
}

#endif // METEORITOCOMMONDATAFLOWINPUT_H
