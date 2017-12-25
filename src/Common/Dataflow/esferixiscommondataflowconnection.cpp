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

#include "esferixiscommondataflowconnection.h"
#include <stdexcept>

Esferixis::Common::Dataflow::Connection::Connection() : prepareReceivedPacketForSendingConcurrencyPreventer("Unexpected concurrency") {
    this->hasReceivingAnPacket = false;
    this->hasSendingAnPacket = false;

    this->hasReceivedPacket = false;
    this->hasPreparedPacketToSend = false;
}

Esferixis::Common::Dataflow::Connection::~Connection() {

}

void Esferixis::Common::Dataflow::Connection::receivePacket(std::function<void ()> notifyPacketArrival) {
    if ( !this->hasReceivingAnPacket.exchange(true) ) {
        try {
            if ( !this->hasReceivedPacket ) {
                try {
                    this->receivePacket_implementation([this, notifyPacketArrival]() -> void {
                        this->hasReceivedPacket = true;
                        this->hasReceivingAnPacket = false;
                        notifyPacketArrival();
                    });
                }
                catch ( std::runtime_error e ) {
                    throw e;
                }
            }
            else {
                throw std::runtime_error("It already has an received packet");
            }
        }
        catch ( std::runtime_error e ) {
            this->hasReceivingAnPacket = false;
            throw e;
        }
    }
    else {
        this->hasReceivingAnPacket = false;
        throw std::runtime_error("It has receiving an packet");
    }
}

void Esferixis::Common::Dataflow::Connection::prepareReceivedPacketForSending() {
    this->prepareReceivedPacketForSendingConcurrencyPreventer.run([this]() -> void {
        if ( this->hasReceivedPacket ) {
            if ( !this->hasPreparedPacketToSend ) {
                this->prepareReceivedPacketForSending_implementation();
            }
            else {
                throw std::runtime_error("Expected that it hasn't prepared packet to send");
            }
        }
        else {
            throw std::runtime_error("Expected that it has received packet");
        }
    });
}

void Esferixis::Common::Dataflow::Connection::sendReceivedPacket(std::function<void ()> notifyPacketArrival) {
    if ( !this->hasSendingAnPacket.exchange(true) ) {
        try {
            if ( this->hasPreparedPacketToSend ) {
                try {
                    this->receivePacket_implementation([this, notifyPacketArrival]() -> void {
                        this->hasPreparedPacketToSend = false;
                        this->hasSendingAnPacket = false;
                        notifyPacketArrival();
                    });
                }
                catch ( std::runtime_error e ) {
                    throw e;
                }
            }
            else {
                throw std::runtime_error("It hasn't a prepared packet to send");
            }
        }
        catch ( std::runtime_error e ) {
            this->hasSendingAnPacket = false;
            throw e;
        }
    }
    else {
        this->hasSendingAnPacket = false;
        throw std::runtime_error("It has receiving an packet");
    }
}
