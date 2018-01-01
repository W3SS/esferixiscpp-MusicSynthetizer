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
            class Output : public Esferixis::Common::Dataflow::InterfaceElement
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
                 * @pre No tiene que haber envío de paquete pendiente ni otra operación
                 *      concurrente
                 * @post Devuelve si va a procesar en éste thread si envía un paquete
                 */
                bool willProcessInThisThreadIfItSendAnPacket() {
                    this->concurrencyPreventer.run([this]() -> void {
                        return this->willBlockIfItSendAnPacket_implementation();
                    }
                }

                /**
                 * @pre No tiene que haber envío de paquete pendiente ni otra operación
                 *      concurrente
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
                 * @pre No hay envío de paquete pendiente ni otra operación
                 *      concurrente
                 * @post Devuelve si va a bloquear si envía un paquete
                 */
                virtual bool willBlockIfItSendAnPacket_implementation() =0;

                /**
                 * @pre No hay envío de paquete pendiente ni otra operación
                 *      concurrente
                 * @post Envía el paquete especificado, con el lambda de notificación
                 *       de llegada especificado
                 */
                virtual void sendPacket_implementation(P outputPacket, std::function<void ()> notifyPacketArrival) =0;

            private:
                std::atomic<bool> hasPendingPacketSending;
            };
        }
    }
}

#endif // METEORITOCOMMONDATAFLOWOUTPUT_H
