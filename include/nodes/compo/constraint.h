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
			CConstraint    ( std::shared_ptr<nodes::procedural::CSymbol> name = nullptr,
			                 const std::vector<std::shared_ptr<nodes::procedural::CSymbol>>& params = std::vector<std::shared_ptr<nodes::procedural::CSymbol>>(0),
			                 const std::vector<std::shared_ptr<nodes::CNode>>& body = std::vector<std::shared_ptr<nodes::CNode>>(0));
		};

	}

}