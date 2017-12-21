#ifndef GRAPHNODESCONNECTOR_H
#define GRAPHNODESCONNECTOR_H

namespace Esferixis {
    namespace Common {
        namespace DirectedGraph {
            /**
             * @brief Conector de nodos de grafo dirigido
             */
            template<typename N>
            class NodesConnector
            {
            public:
                /**
                 * @post Crea un conector de nodos
                 */
                NodesConnector();

                /**
                 * @post Destruye el conector de nodos
                 */
                ~NodesConnector();

                /**
                 * @post Conecta el nodo origen con el nodo destino especificado
                 */
                virtual void connect(N& sourceNode, N& destinationNode) =0;

                /**
                 * @post Desconecta el nodo origen del nodo destino especificado
                 */
                virtual void disconnect(N& sourceNode, N& destinationNode) =0;
            };
        }
    }
}

#endif // GRAPHNODESCONNECTOR_H
