#pragma once

#include <memory>
#include "ast/nodes/compo/abstractReqProv.h"

namespace ast {
    
    namespace nodes {

	namespace compo {

		/**
		 * \class CRequirement
		 * \brief Class for Compo requirement node representation.
		 */
		class CRequirement : public CAbstractReqProv {
		  public:
			/**
			* Parametric constructor with default value
			* @param type: Type of visibility
			* @param ports: Vector of ports
			*/
			CRequirement(types::visibilityType type = types::visibilityType::EXTERNAL,
			             const std::vector<std::shared_ptr<compo::CPort>>& ports = std::vector<std::shared_ptr<compo::CPort>>(0));

			/**
			            * Accept method for visitor acceptation.
			            * @param visitor: Pointer to abstract visitor.
			            */
			virtual void accept(visitors::CAbstractVisitor *visitor);
		};

	}
        
    }

}