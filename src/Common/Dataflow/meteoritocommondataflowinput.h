#ifndef METEORITOCOMMONDATAFLOWINPUT_H
#define METEORITOCOMMONDATAFLOWINPUT_H

#include <functional>
#include <atomic>
#include <stdexcept>

namespace Esferixis {
    namespace Common {
        namespace Dataflow {
            /**
             * @brief Entrada con datagrama tipo D
             */
            template<typename D>
            class Input
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
                 * @pre No tiene que haber recepción de datagrama pendiente
                 * @post Recibe un datagrama en el lambda de notificación de llegada de datagrama especificado
                 */
                void receiveDatagram(std::function<void (D inputDatagram)> notifyDatagramArrival) {
                    if ( !this->hasPendingDatagramReception.exchange(true) ) {
                        this->receiveDatagram_implementation([notifyDatagramArrival](D inputDatagram) -> void {
                            this->hasPendingDatagramReception = false;
                            notifyDatagramArrival(inputDatagram);
                        });
                    }
                    else {
                        throw std::runtime_error("It has been pending datagram reception");
                    }
                }

            protected:
                /**
                 * @pre No hay recepción de datagrama pendiente
                 * @post Recibe un datagrama en el lambda de notificación de llegada de datagrama especificado
                 */
                virtual void receiveDatagram_implementation(std::function<void (D inputDatagram)> notifyDatagramArrival) =0;

            private:
                std::atomic<bool> hasPendingDatagramReception;
            };
        }
    }
}

#endif // METEORITOCOMMONDATAFLOWINPUT_H
