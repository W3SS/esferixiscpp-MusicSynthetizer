/*
BSD 3-Clause License

Copyright (c) 2017, Ariel Favio Carrizo
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef METEORITOCOMMONDATAFLOWINPUT_H
#define METEORITOCOMMONDATAFLOWINPUT_H

#include <functional>
#include <atomic>
#include <stdexcept>
#include "Common/Concurrency/esferixiscommonconcurrencypreventer.h"
#include "esferixiscommondataflowinterfaceelement.h"

namespace Esferixis {
    namespace Common {
        namespace Dataflow {
            /**
             * @brief Entrada con paquete tipo P
             */
            template<typename P>
            class Input : public Esferixis::Common::Dataflow::InterfaceElement
            {
            public:
                /**
                 * @post Crea una entrada
                 */
                Input() {

                }

                /**
                 * @post Destruye la entrada
                 */
                ~Input() {

                }

                /**
                 * @pre No tiene que haber recepción de paquete pendiente ni otra operación
                 *      concurrente
                 * @post Devuelve si va a bloquear si recibe un paquete
                 */
                bool willBlockIfItReceiveAnPacket() {
                    this->concurrencyPreventer.run([this]() -> void {
                        return this->willBlockIfItReceiveAnPacket_implementation();
                    });
                }

                /**
                 * @pre No tiene que haber recepción de paquete pendiente ni otra operación
                 *      concurrente
                 * @post Recibe un paquete en el lambda de notificación de llegada de paquete especificado
                 */
                void receivePacket(std::function<void (P inputPacket)> notifyPacketArrival) {
                    this->concurrencyPreventer.run([this]() -> void {
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
                }

            protected:
                /**
                 * @pre No hay recepción de paquete pendiente ni otra operación
                 *      concurrente
                 * @post Devuelve si va a bloquear si recibe un paquete
                 */
                virtual bool willBlockIfItReceiveAnPacket_implementation() =0;

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
