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

#ifndef METEORITOCOMMONDATAFLOWCONNECTION_H
#define METEORITOCOMMONDATAFLOWCONNECTION_H

#include <boost/noncopyable.hpp>
#include <atomic>
#include <functional>
#include "Common/Concurrency/esferixiscommonconcurrencypreventer.h"

namespace Esferixis {
    namespace Common {
        namespace Dataflow {
            class Connection : private boost::noncopyable
            {
            public:
                /**
                 * @post Crea una conexión
                 */
                Connection();

                /**
                 * @post Destruye la conexión
                 */
                ~Connection();

                /**
                 * @pre No tiene que haber paquete recibido ni
                 *      recepción de paquete pendiente
                 * @post Recibe un paquete de la entrada y lo guarda
                 */
                void receivePacket(std::function<void ()> notifyPacketArrival);

                /**
                 * @pre Tiene que haber paquete recibido y no tiene que haber
                 *      paquete preparado para enviar
                 * @post Prepara el envío del paquete recibido
                 */
                void prepareReceivedPacketForSending();

                /**
                 * @pre Tiene que haber paquete preparado para enviar y no tiene que
                 *      haber envío de paquete pendiente
                 * @post Envía el paquete recibido, notificando el recibo del envío del paquete preparado
                 *       para enviar
                 */
                void sendReceivedPacket(std::function<void ()> notifyPacketArrival);

            protected:
                /**
                 * @pre No tiene que haber paquete recibido ni
                 *      recepción de paquete pendiente
                 * @post Recibe un paquete de la entrada y lo guarda
                 */
                virtual void receivePacket_implementation(std::function<void ()> notifyPacketArrival) =0;

                /**
                 * @pre Tiene que haber paquete recibido y no tiene que haber
                 *      paquete preparado para enviar
                 * @post Prepara el envío del paquete recibido
                 */
                virtual void prepareReceivedPacketForSending_implementation() =0;

                /**
                 * @pre Tiene que haber paquete preparado para enviar y no tiene que
                 *      haber envío de paquete pendiente
                 * @post Envía el paquete recibido, notificando el recibo del envío del paquete preparado
                 *       para enviar
                 */
                virtual void sendReceivedPacket_implementation(std::function<void ()> notifyPacketArrival) =0;

            private:
                std::atomic<bool> hasReceivingAnPacket;
                std::atomic<bool> hasSendingAnPacket;

                std::atomic<bool> hasReceivedPacket;
                std::atomic<bool> hasPreparedPacketToSend;

                Esferixis::Common::Concurrency::ConcurrencyPreventer prepareReceivedPacketForSendingConcurrencyPreventer;
            };
        }
    }
}

#endif // METEORITOCOMMONDATAFLOWCONNECTION_H
