#pragma once

#include <memory>
#include "nodes/compo/abstractReqProv.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CProvision
		 * \brief Class for Compo provision node representation.
		 */
		class CProvision : public CAbstractReqProv {
		  public:
			/**
			* Parametric constructor with default value
			* @param type: Type of visibility
			* @param ports: Vector of ports
			*/
			CProvision     ( types::visibilityType type = types::visibilityType::EXTERNAL,
			                 const std::vector<std::shared_ptr<nodes::compo::CPort>>& ports = std::vector<std::shared_ptr<nodes::compo::CPort>>(0));
		};

	}

}