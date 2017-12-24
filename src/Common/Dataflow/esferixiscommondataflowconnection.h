#ifndef METEORITOCOMMONDATAFLOWCONNECTION_H
#define METEORITOCOMMONDATAFLOWCONNECTION_H

#include <boost/noncopyable.hpp>
#include <atomic>

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
                 * @pre No tiene que haber paquete recibido pendiente de enviar ni
                 *      recepción de paquete pendiente
                 * @post Recibe un paquete de la entrada y lo guarda
                 */
                void receivePacket(std::function<void ()> notifyPacketArrival);

                /**
                 * @pre Tiene que haber paquete recibido pendiente de enviar y no tiene que
                 *      haber envío de paquete pendiente
                 * @post Envía el paquete recibido, notificando la copia del paquete
                 *       pendiente y el envío del paquete
                 */
                void sendReceivedPacket(std::function<void ()> packetHasBeenCopied, std::function<void ()> notifyPacketArrival);

            protected:
                /**
                 * @pre No tiene que haber paquete recibido pendiente de enviar
                 * @post Recibe un paquete de la entrada y lo guarda
                 */
                virtual void receivePacket_implementation(std::function<void ()> notifyPacketArrival) =0;

                /**
                 * @pre Tiene que haber paquete recibido pendiente de enviar
                 * @post Envía el paquete recibido, notificando la copia del paquete
                 *       pendiente y el envío del paquete
                 */
                virtual void sendReceivedPacket_implementation(std::function<void ()> packetHasBeenCopied, std::function<void ()> notifyPacketArrival) =0;

            private:
                std::atomic<bool> hasReceivingAnPacket;
                std::atomic<bool> hasSendingAnPacket;
                std::atomic<bool> hasPendingPacketToSend;
            };
        }
    }
}

#endif // METEORITOCOMMONDATAFLOWCONNECTION_H
