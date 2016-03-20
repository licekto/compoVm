#pragma once

#include <memory>
#include "ast/nodes/compo/abstractServConstr.h"

namespace ast {

    namespace nodes {
    
	namespace compo {

		/**
		 * \class CConstraint
		 * \brief Class for Compo constraint representation.
		 */
		class CConstraint : public CAbstractServConstr, public std::enable_shared_from_this<CConstraint> {
		  public:
			/**
			* Parametric constructor with default values
			* @param name: Name of constraint
			* @param params: Vector of parameters
			* @param body: Vector of body expressions
			*/
			CConstraint(std::shared_ptr<compo::CServiceSignature> signature = nullptr,
			            std::shared_ptr<procedural::CCompoundBody> body = nullptr);

			/**
			* Accept method for visitor acceptation.
			* @param visitor: Pointer to abstract visitor.
			*/
			virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

			/**
			* Temporaries size getter
			            * @return size of temporaries vector
			            */
			size_t getTemporariesSize() const = delete;

			/**
			* Adds new body node
			            * @param node: shared pointer to node
			            */
			void addTemporary(std::shared_ptr<procedural::CSymbol> temporary) = delete;

			/**
			 * Temporaries getter
			 * @param index: index of wanted temporary
			 * @return shared pointer to temporary symbol name
			 */
			std::shared_ptr<procedural::CSymbol> getTemporaryAt (int index) const = delete;
		};

	}

    }
        
}