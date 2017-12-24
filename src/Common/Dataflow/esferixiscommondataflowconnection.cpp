#include "esferixiscommondataflowconnection.h"
#include <stdexcept>

Esferixis::Common::Dataflow::Connection::Connection() {
    this->hasPendingPacketToSend = false;
}

Esferixis::Common::Dataflow::Connection::~Connection() {

}

void Esferixis::Common::Dataflow::Connection::receivePacket(std::function<void ()> notifyPacketArrival) {
    if ( !this->hasReceivingAnPacket.exchange(true) ) {
        if ( !this->hasPendingPacketToSend ) {
            try {
                this->receivePacket_implementation([this]() -> void {
                    this->hasPendingPacketToSend = true;
                    this->hasReceivingAnPacket = false;
                    notifyPacketArrival();
                });
            }
            catch ( std::runtime_error e ) {
                this->hasReceivingAnPacket = false;
                throw e;
            }
        }
        else {
            this->hasReceivingAnPacket = false;
            throw std::runtime_error("It has pending packet to send");
        }
    }
    else {
        this->hasReceivingAnPacket = false;
        throw std::runtime_error("It has receiving an packet");
    }
}

void Esferixis::Common::Dataflow::Connection::sendReceivedPacket(std::function<void ()> packetHasBeenCopied, std::function<void ()> notifyPacketArrival) {
    if ( !this->hasSendingAnPacket.exchange(true) ) {
        if ( this->hasPendingPacketToSend ) {
            try {
                this->sendReceivedPacket_implementation(
                [this]() -> void {
                    this->hasPendingPacketToSend = false;
                    packetHasBeenCopied();
                },
                [this]() -> void {
                    this->hasSendingAnPacket = false;
                    notifyPacketArrival();
                });
            }
            catch ( std::runtime_error e ) {
                this->hasSendingAnPacket = false;
                throw e;
            }
        }
        else {
            this->hasSendingAnPacket = false;
            throw std::runtime_error("It hasn't pending packet to send");
        }
    }
    else {
        this->hasSendingAnPacket = false;
        throw std::runtime_error("It has sending a packet");
    }
}
