/*
BSD 3-Clause License

Copyright (c) 2018, Ariel Favio Carrizo
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

#ifndef ESFERIXISCOMMONDATAFLOWIMPLCONNECTIONSMANAGERBASEDINTASKSLAUNCHERCONNECTIONMANAGER_H
#define ESFERIXISCOMMONDATAFLOWIMPLCONNECTIONSMANAGERBASEDINTASKSLAUNCHERCONNECTIONMANAGER_H

#include <memory>
#include "Common/Dataflow/esferixiscommondataflowconnection.h"
#include "Common/Concurrency/esferixiscommontaskslauncher.h"
#include <atomic>

namespace Esferixis {
    namespace Common {
        namespace DataflowImpl {
            /**
             * @brief Administrador de conexión del administrador de conexiones basado
             *        en lanzador de tareas
             */
            class ConnectionsManagerBasedInTasksLauncherConnectionManager final : private boost::noncopyable
            {
            public:
                /**
                 * @post Crea un administrador de conexión con la conexión y el
                 *       lanzador de tareas especificado
                 */
                ConnectionsManagerBasedInTasksLauncherConnectionManager(std::shared_ptr<Esferixis::Common::Dataflow::Connection> connection);

                /**
                 * @post Destruye el administrador de conexión
                 */
                ~ConnectionsManagerBasedInTasksLauncherConnectionManager();

                /**
                 * @pre No tiene que haberse ordenado la desconexión
                 * @post Realiza la desconexión propiamente dicha, con la función
                 *       de notificación de éxito especificada
                 */
                void disconnect(std::function<void ()> notifySuccess);

            private:
                std::shared_ptr<Esferixis::Common::Dataflow::Connection> connection;
                std::atomic<bool> disconnectCommand;
            };
        }
    }
}

#endif // ESFERIXISCOMMONDATAFLOWIMPLCONNECTIONSMANAGERBASEDINTASKSLAUNCHERCONNECTIONMANAGER_H
