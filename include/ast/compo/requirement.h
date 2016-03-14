#pragma once

#include <memory>
#include "ast/compo/abstractReqProv.h"

namespace ast {

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
			             const std::vector<std::shared_ptr<ast::compo::CPort>>& ports = std::vector<std::shared_ptr<ast::compo::CPort>>(0));

			/**
			* Virtual print function to call from operator <<
			            * @param os: output stream
			            * @see operator <<()
			            */
			virtual void print(std::ostream& os) const;
		};

	}

}