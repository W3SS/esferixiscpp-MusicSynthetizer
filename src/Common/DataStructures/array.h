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

#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>

namespace Esferixis {
    namespace Common {
        namespace DataStructures {
            template<typename T>
            class Array
            {
            public:
                /**
                 * @pre El tamaño tiene que ser positivo o cero
                 * @post Crea un array del tamaño especificado
                 */
                Array(size_t size) {
                    if ( size >= 0 ) {
                        this->size = size;
                        this->elements = new T[size];
                    }
                    else {
                        throw std::runtime_error("Expected non negative size");
                    }
                }

                /**
                 * @post Destruye el array
                 */
                ~Array() {
                    delete[] this->elements;
                }

                /**
                 * @post Devuelve el tamaño
                 */
                size_t getSize() const {
                    return this->size;
                }

                /**
                 * @post Devuelve los elementos
                 */
                T *getElements() {
                    return this->elements;
                }

                /**
                 * @post Devuelve los elementos (Constante)
                 */
                T const *getElements() const {
                    return this->elements;
                }

            private:
                const size_t size;

                T *elements;
            };
        }
    }
}

#endif // ARRAY_H
