#pragma once

#include <memory>
#include "nodes/compo/abstractServConstr.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CConstraint
		 * \brief Class for Compo constraint representation.
		 */
		class CConstraint : public CAbstractServConstr {
		  public:
			/**
			* Parametric constructor with default values
			* @param name: Name of constraint
			* @param params: Vector of parameters
			* @param body: Vector of body expressions
			*/
			CConstraint(std::shared_ptr<nodes::procedural::CSymbol> name = nullptr,
                                    const std::vector<std::shared_ptr<nodes::procedural::CSymbol>>& params = std::vector<std::shared_ptr<nodes::procedural::CSymbol>>(0),
                                    std::shared_ptr<nodes::procedural::CCompoundBody> body = nullptr);
                        
                        /**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;
                        
                        /**
			* Temporaries size getter
                        * @return size of temporaries vector
                        */
                        size_t getTemporariesSize() const = delete;
                        
                        /**
			* Adds new body node
			* @param node: shared pointer to node
			*/
                        void addTemporary(std::shared_ptr<nodes::procedural::CSymbol> temporary) = delete;
                        
                        /**
                         * Temporaries getter
                         * @param index: index of wanted temporary
                         * @return shared pointer to temporary symbol name
                         */
                        std::shared_ptr<nodes::procedural::CSymbol> getTemporaryAt (int index) const = delete;
		};

	}

}