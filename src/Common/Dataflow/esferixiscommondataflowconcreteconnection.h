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
                        this->receivedPacket = packet;
                        notifyPacketArrival();
                    });
                }

                virtual void prepareReceivedPacketForSending_implementation() {
                    this->preparedPacketToSend = this->receivedPacket;
                }

                void sendReceivedPacket_implementation(std::function<void ()> notifyPacketArrival) {
                    this->output.sendPacket(this->preparedPacketToSend, [this]() -> void {
                        notifyPacketArrival();
                    });
                }

            private:
                Esferixis::Common::Dataflow::Input<P>& input;
                Esferixis::Common::Dataflow::Output<P>& output;

                P receivedPacket;
                P preparedPacketToSend;
            };
        }
    }
}

#endif // METEORITOCOMMONDATAFLOWCONNECTION_H
