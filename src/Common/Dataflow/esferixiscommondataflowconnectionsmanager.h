#ifndef ESFERIXISCOMMONDATAFLOWGRAPH_H
#define ESFERIXISCOMMONDATAFLOWGRAPH_H

#include <boost/noncopyable.hpp>
#include <memory>

#include "esferixiscommondataflowconnection.h"

namespace Esferixis {
    namespace Common {
        namespace Dataflow {
            class ConnectionsManager : private boost::noncopyable
            {
            public:
                /**
                 * @post Crea un administrador de conexiones
                 */
                ConnectionsManager();

                /**
                 * @post Destruye el administrador de conexiones
                 */
                ~ConnectionsManager();

                /**
                 * @post Agrega la conexión especificada
                 */
                virtual void addConnection(std::shared_ptr<Esferixis::Common::Dataflow::Connection> connection) =0;

                /**
                 * @post Quita la conexión especificada
                 */
                virtual void removeConnection(std::shared_ptr<Esferixis::Common::Dataflow::Connection> connection) =0;
            };
        }
    }
}

#endif // ESFERIXISCOMMONDATAFLOWGRAPH_H
