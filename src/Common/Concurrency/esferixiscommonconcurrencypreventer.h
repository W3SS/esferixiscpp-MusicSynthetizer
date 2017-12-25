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

#ifndef ESFERIXISCOMMONCONCURRENCYPREVENTER_H
#define ESFERIXISCOMMONCONCURRENCYPREVENTER_H

#include <string>
#include <functional>
#include <atomic>

namespace Esferixis {
    namespace Common {
        namespace Concurrency {
            class ConcurrencyPreventer final
            {
            public:
                /**
                 * @post Crea el prevenidor de concurrencia con el mensaje de
                 *       error especificado
                 */
                ConcurrencyPreventer(std::string errorMessage);

                /**
                 * @pre No tiene que haber un lambda ejecutándose
                 * @post Destruye el prevenidor de concurrencia
                 */
                ~ConcurrencyPreventer();

                /**
                 * @pre No tiene que haber otro lambda ejecutándose
                 * @post Ejecuta el lambda sólo si no hay otro lambda ejecutándose.
                 *
                 *       Si lo hay lanza una excepción con el correspondiente mensaje de error.
                 */
                void run(std::function<void ()> function);

            private:
                const std::string errorMessage;
                std::atomic<bool> hasExecutingAFunction;
            };
        }
    }
}

#endif // ESFERIXISCOMMONCONCURRENCYPREVENTER_H
